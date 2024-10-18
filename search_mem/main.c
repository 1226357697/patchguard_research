#include <ntifs.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

//
// APC Environment Types
//
typedef enum _KAPC_ENVIRONMENT
{
  OriginalApcEnvironment,
  AttachedApcEnvironment,
  CurrentApcEnvironment,
  InsertApcEnvironment
} KAPC_ENVIRONMENT;

//
// APC Normal Routine
//
typedef VOID
(NTAPI* PKNORMAL_ROUTINE)(
  _In_ PVOID NormalContext,
  _In_ PVOID SystemArgument1,
  _In_ PVOID SystemArgument2
  );

typedef VOID
(NTAPI* PKKERNEL_ROUTINE)(
  IN struct _KAPC* Apc,
  IN OUT PKNORMAL_ROUTINE* NormalRoutine OPTIONAL,
  IN OUT PVOID* NormalContext OPTIONAL,
  IN OUT PVOID* SystemArgument1 OPTIONAL,
  IN OUT PVOID* SystemArgument2 OPTIONAL);

typedef VOID
(NTAPI* PKRUNDOWN_ROUTINE)(
  IN struct _KAPC* Apc);

VOID
NTAPI
KeInitializeApc(IN PKAPC Apc,
  IN PKTHREAD Thread,
  IN KAPC_ENVIRONMENT TargetEnvironment,
  IN PKKERNEL_ROUTINE KernelRoutine,
  IN PKRUNDOWN_ROUTINE RundownRoutine OPTIONAL,
  IN PKNORMAL_ROUTINE NormalRoutine,
  IN KPROCESSOR_MODE Mode,
  IN PVOID Context);

BOOLEAN
NTAPI
KeInsertQueueApc(IN PKAPC Apc,
  IN PVOID SystemArgument1,
  IN PVOID SystemArgument2,
  IN KPRIORITY PriorityBoost);

typedef
NTSTATUS
(NTAPI *PsSuspendThread_t)(
  IN PETHREAD Thread,
  OUT PULONG PreviousCount OPTIONAL);

typedef
NTSTATUS
(NTAPI *PsResumeThread_t)(
  IN PETHREAD Thread,
  OUT PULONG PreviousCount OPTIONAL
);


static ULONG log_i(PCCH fmt, ...)
{
  ULONG ret = 0;
  va_list ap;
  va_start(ap, fmt);
  ret = vDbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, fmt, ap);
  va_end(ap);
  return ret;
}
void KSleep(LONGLONG milliseconds)
{
  LARGE_INTEGER interval;
  interval.QuadPart = -(10 * 1000 * milliseconds);
  KeDelayExecutionThread(KernelMode, FALSE, &interval);

}



PETHREAD workThread = (PETHREAD)0xFFFF898B14E70040;
PsSuspendThread_t PsSuspendThread = (PsSuspendThread_t)0Xfffff80303190c60;
PsResumeThread_t  PsResumeThread = (PsResumeThread_t)0xfffff8030317a050;


typedef struct _MMPTE_HARDWARE
{
  ULONG64 Valid : 1;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
  ULONG64 Dirty1 : 1;
#else
#ifdef CONFIG_SMP
  ULONG64 Writable : 1;
#else
  ULONG64 Write : 1;
#endif
#endif
  ULONG64 Owner : 1;
  ULONG64 WriteThrough : 1;
  ULONG64 CacheDisable : 1;
  ULONG64 Accessed : 1;
  ULONG64 Dirty : 1;
  ULONG64 LargePage : 1;
  ULONG64 Global : 1;
  ULONG64 CopyOnWrite : 1;
  ULONG64 Prototype : 1;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
  ULONG64 Write : 1;
  ULONG64 PageFrameNumber : 36;
  ULONG64 reserved1 : 4;
#else
#ifdef CONFIG_SMP
  ULONG64 Write : 1;
#else
  ULONG64 reserved0 : 1;
#endif
  ULONG64 PageFrameNumber : 28;
  ULONG64 reserved1 : 12;
#endif
  ULONG64 SoftwareWsIndex : 11;
  ULONG64 NoExecute : 1;
} MMPTE_HARDWARE, * PMMPTE_HARDWARE;

typedef struct _page_table_t 
{
  ULONG64 pxe_base;
  ULONG64 ppe_base;
  ULONG64 pde_base;
  ULONG64 pte_base;
}page_table_t;
page_table_t page_table;

BOOLEAN GetPageTableBase()
{
#define SHIFT_MARK(level) (((level)*9) + 12)
  LONG_PTR cr3 = __readcr3();
  ULONG64 physical_page_base = cr3 & 0xFFFFFFFFFF000;

  ULONG64 self_index = 0;
  for (int i = 1; i < 512; ++i)
  {
    ULONG64 guss_part = 0;
    guss_part |= (ULONG64)i << SHIFT_MARK(0);
    guss_part |= (ULONG64)i << SHIFT_MARK(1);
    guss_part |= (ULONG64)i << SHIFT_MARK(2);
    guss_part |= (ULONG64)i << SHIFT_MARK(3);
    PVOID pxt = (PVOID)(0xffff000000000000 | guss_part);
    PHYSICAL_ADDRESS tmp_phys= MmGetPhysicalAddress(pxt);

    if (tmp_phys.QuadPart == physical_page_base)
    {
      self_index = i;
      break;
    }
  }
  if(self_index == 0)
    return FALSE;

  page_table.pte_base = self_index << SHIFT_MARK(3) | 0xffff000000000000;
  page_table.pde_base = page_table.pte_base | (self_index << SHIFT_MARK(2));
  page_table.ppe_base = page_table.pde_base | (self_index << SHIFT_MARK(1));
  page_table.pxe_base = page_table.ppe_base | (self_index << SHIFT_MARK(0));

  log_i("pte_base:%p\n", page_table.pte_base);
  log_i("pde_base:%p\n", page_table.pde_base);
  log_i("ppe_base:%p\n", page_table.ppe_base);
  log_i("pxe_base:%p\n", page_table.pxe_base);
  return TRUE;
}

#define PXI_SHIFT (12+9*3)
#define PPI_SHIFT (12+9*2)
#define PDI_SHIFT (12+9*1)
#define PTI_SHIFT (12+9*0)

#define PXE_BASE (page_table.pxe_base)
#define PPE_BASE (page_table.ppe_base)
#define PDE_BASE (page_table.pde_base)
#define PTE_BASE (page_table.pte_base)

/* Convert an address to a corresponding PXE */
FORCEINLINE
PMMPTE_HARDWARE
MiAddressToPxe(PVOID Address)
{
  ULONG64 Offset = (ULONG64)Address >> (PXI_SHIFT - 3);
  Offset &= 0x1FF << 3;
  return (PMMPTE_HARDWARE)(PXE_BASE + Offset);
}

/* Convert an address to a corresponding PPE */
FORCEINLINE
PMMPTE_HARDWARE
MiAddressToPpe(PVOID Address)
{
  ULONG64 Offset = (ULONG64)Address >> (PPI_SHIFT - 3);
  Offset &= 0x3FFFF << 3;
  return (PMMPTE_HARDWARE)(PPE_BASE + Offset);
}

/* Convert an address to a corresponding PDE */
FORCEINLINE
PMMPTE_HARDWARE
_MiAddressToPde(PVOID Address)
{
  ULONG64 Offset = (ULONG64)Address >> (PDI_SHIFT - 3);
  Offset &= 0x7FFFFFF << 3;
  return (PMMPTE_HARDWARE)(PDE_BASE + Offset);
}
#define MiAddressToPde(x) _MiAddressToPde((PVOID)(x))

/* Convert an address to a corresponding PTE */
FORCEINLINE
PMMPTE_HARDWARE
_MiAddressToPte(PVOID Address)
{
  ULONG64 Offset = (ULONG64)Address >> (PTI_SHIFT - 3);
  Offset &= 0xFFFFFFFFFULL << 3;
  return (PMMPTE_HARDWARE)(PTE_BASE + Offset);
}
#define MiAddressToPte(x) _MiAddressToPte((PVOID)(x))

#define IS_USER_ADDRESS(address) ((((LONG64)(address)) >> 47) == 0)
#define IS_KERNAL_ADDRESS(address) ((((LONG64)(address)) >> 47) == -1)
#define IS_VALID_ADDRESS(address) (IS_USER_ADDRESS((address)) || IS_KERNAL_ADDRESS((address)))

void PrintAddressPage(PVOID Address)
{
  if (!IS_VALID_ADDRESS(Address))
    return ;

  PMMPTE_HARDWARE pte = MiAddressToPxe(Address);
  if(pte->Valid == 0) return;
  log_i("pxe: %08X\n", pte->PageFrameNumber);

  pte = MiAddressToPpe(Address);
  if (pte->Valid == 0) return;
  log_i("ppe: %08X\n", pte->PageFrameNumber);

  pte = MiAddressToPde(Address);
  if (pte->Valid == 0) return;
  log_i("pde: %08X\n", pte->PageFrameNumber);

  pte = MiAddressToPte(Address);
  if (pte->Valid == 0) return;
  log_i("pte: %08X\n", pte->PageFrameNumber);

  return;
}

BOOLEAN IsLargePage(PVOID Address)
{
  if (!IS_VALID_ADDRESS(Address))
    return FALSE;

  PMMPTE_HARDWARE pte = MiAddressToPxe(Address);
  if (pte->Valid != 0 && pte->LargePage != 0) 
    return TRUE;
  

  pte = MiAddressToPpe(Address);
  if (pte->Valid == 0) return;
  if (pte->Valid != 0 && pte->LargePage != 0)
    return TRUE;

  pte = MiAddressToPde(Address);
  if (pte->Valid == 0) return;
  if (pte->Valid != 0 && pte->LargePage != 0)
    return TRUE;

  pte = MiAddressToPte(Address);
  if (pte->Valid == 0) return;
  if (pte->Valid != 0 && pte->LargePage != 0)
    return TRUE;

  return FALSE;
}

BOOLEAN finc_dec_pg_context(PVOID address)
{
  if (!MmIsAddressValid(address))
  {
    return FALSE;
  }

  int try_count = 0x100 ;//* PAGE_SIZE;
  ULONG64 _address = (ULONG64)address;
  _address = ALIGN_DOWN(_address, PAGE_SIZE);
  while (MmIsAddressValid((PVOID)_address) && try_count > 0)
  {
    _address -= PAGE_SIZE;
    try_count--;
  }
  if(try_count == 0)
    return FALSE;

  _address += PAGE_SIZE;

  ULONG64 max_limit = PAGE_SIZE * 2;

  //------------------------------------------------------------
  //-----------       Created with 010 Editor        -----------
  //------         www.sweetscape.com/010editor/          ------
  //
  // File    : C:\Users\yangzy\Desktop\12
  // Address : 0 (0x0)
  // Size    : 135 (0x87)
  //------------------------------------------------------------
  unsigned char hexData[] = {
      0x2E, 0x48, 0x31, 0x11, 0x48, 0x31, 0x51, 0x08, 0x48, 0x31, 0x51, 0x10, 0x48, 0x31, 0x51, 0x18,
      0x48, 0x31, 0x51, 0x20, 0x48, 0x31, 0x51, 0x28, 0x48, 0x31, 0x51, 0x30, 0x48, 0x31, 0x51, 0x38,
      0x48, 0x31, 0x51, 0x40, 0x48, 0x31, 0x51, 0x48, 0x48, 0x31, 0x51, 0x50, 0x48, 0x31, 0x51, 0x58,
      0x48, 0x31, 0x51, 0x60, 0x48, 0x31, 0x51, 0x68, 0x48, 0x31, 0x51, 0x70, 0x48, 0x31, 0x51, 0x78,
      0x48, 0x83, 0xC1, 0x78, 0x48, 0x31, 0x51, 0x08, 0x48, 0x31, 0x51, 0x10, 0x48, 0x31, 0x51, 0x18,
      0x48, 0x31, 0x51, 0x20, 0x48, 0x31, 0x51, 0x28, 0x48, 0x31, 0x51, 0x30, 0x48, 0x31, 0x51, 0x38,
      0x48, 0x31, 0x51, 0x40, 0x48, 0x31, 0x51, 0x48, 0x48, 0x83, 0xE9, 0x78, 0x31, 0x11, 0x48, 0x8B,
      0xC2, 0x48, 0x8B, 0xD1, 0x8B, 0x8A, 0xC4, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC0
  };


  for (int i = 0; i < max_limit; ++i)
  {
    if (!MmIsAddressValid((PVOID)(_address + i)))
    {
      return FALSE;
    }

    if (memcmp((PVOID)(_address + i), hexData, sizeof(hexData)) == 0)
    {
      return TRUE;
    }

  }

  return FALSE;
}

BOOLEAN InSystemArea(PVOID address)
{
  PVOID start = (PVOID)0xfffff80302ab6000;
  PVOID end = (PVOID)0xfffff8030356b000;
  return address >= start && address < end;
}


NTSTATUS
NTAPI
PsGetContextThread(IN PETHREAD Thread,
  IN OUT PCONTEXT ThreadContext,
  IN KPROCESSOR_MODE PreviousMode);
BOOLEAN is_pg_work = FALSE;
BOOLEAN over = FALSE;
VOID MyKernelApcRoutine(
  PKAPC Apc,
  PKNORMAL_ROUTINE* NormalRoutine,
  PVOID* NormalContext,
  PVOID* SystemArgument1,
  PVOID* SystemArgument2)
{
  // 内核 APC 执行的例子
  PETHREAD thead = KeGetCurrentThread();
  KTRAP_FRAME* frame= *(KTRAP_FRAME**)(((char*)thead) + 0x90);

  //if (MmIsAddressValid(frame))
  {
    //if (frame->PreviousIrql >= DISPATCH_LEVEL)
    {
      //__debugbreak();
      //log_i("frame->PreviousIrql :%d\n", frame->PreviousIrql);
      //log_i("frame->PreviousIrql \n");
      PVOID caller[16];
      ULONG level = RtlWalkFrameChain((PVOID*)&caller, 16, 0);

      for (int i = 1; i < level; ++i)
      {
        if (MmIsAddressValid(caller[i]) && IS_KERNAL_ADDRESS(caller[i]) && !InSystemArea(caller[i]) )
        {
          if (finc_dec_pg_context(caller[i]))
          {

            is_pg_work = TRUE;
          }
          break;
        }
      }

    }
  }


  over = TRUE;
}

BOOLEAN CheckWorkThread(PETHREAD workThread)
{
  is_pg_work = FALSE;
  ULONG count = 0;
  if (NT_SUCCESS(PsSuspendThread(workThread, &count)))
  {
    KIRQL oldIrql;     
    KeRaiseIrql(DISPATCH_LEVEL, &oldIrql);
    
    KAPC apc;
    KeInitializeApc(
      &apc,
      workThread,
      OriginalApcEnvironment,
      MyKernelApcRoutine,
      NULL,
      NULL,
      KernelMode,
      NULL
    );

    over = FALSE;
    BOOLEAN success = KeInsertQueueApc(&apc, NULL, NULL, IO_NO_INCREMENT);
    if (success) {
      int try_count  = 1;
      while (!over)
      {
        if (try_count == 0)
        {
          log_i("KeInsertQueueApc %p\n", workThread);
          break;
        }
        KSleep(300);
        try_count--;
      }
    }


    KeLowerIrql(oldIrql);
    PsResumeThread(workThread, &count);
  }
  return is_pg_work;
}

PETHREAD LoopupThread(HANDLE tid)
{
  PETHREAD thread = NULL;
  PsLookupThreadByThreadId(tid, &thread);
  return thread;
}
int FindPgRun()
{
  PETHREAD currentThread = KeGetCurrentThread();
  int count  = 0;
  for (int i = 0; i < 10000000; i += 4)
  {
    PETHREAD thead = LoopupThread((HANDLE)i);
    if (thead && currentThread != thead)
    {
      UCHAR Running = *(UCHAR*)(((char*)thead) + 0x71);

      if (Running == 1)
      {

        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
        log_i("Running workThread:%p--------------------------------------------------\n", thead);
      }
      //else
      //{
      //  log_i("NO Running workThread:%p\n", thead);
      //}

       //if (CheckWorkThread(thead))
       // {
       //   log_i("FindPgRun :%p-----------------------------------", thead);
       //   count++;

       //   __debugbreak();
       // }
      /* if (Running == 1  && CheckWorkThread(thead))
      {
        log_i("FindPgRun :%p", thead);
        count++;

        __debugbreak();
      }*/
    }

  }
  return count;
}


bool working = false;
bool END = false;
VOID WorkerThread(_In_ PVOID StartContext)
{
  working = true;
  END = false;
  NTSTATUS status;

  while (working)
  {
    int count = FindPgRun();
    if (count > 0)
    {

    }
    else
    {
      //log_i("Not FindPgRun\n");
    }

    KSleep(1000);
  }

  END = TRUE;
}

HANDLE thread = NULL;
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
  working = false;
  while (!END)
  {
    KSleep(1000);
  }
  ZwClose(thread);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registerPath)
{

  driver_obj->DriverUnload = DriverUnload;
  CLIENT_ID       ClientID = { 0 };
  return PsCreateSystemThread(&thread, 0, NULL, NtCurrentProcess(), &ClientID, WorkerThread, NULL);


  log_i("DriverEntry thread:%p\n", KeGetCurrentThread());
  int count = FindPgRun();
  if (count >0)
  {

  }
  else
  {
    log_i("Not FindPgRun\n");
  }
  return STATUS_UNSUCCESSFUL;
  if (!GetPageTableBase())
  {
    log_i("GetPageTableBase Failed\n");
    return STATUS_UNSUCCESSFUL;
  }

  PVOID Address = (PVOID)0xffff898b17078382;
  PrintAddressPage(Address);
  log_i("IsLargePage: %s\n", IsLargePage(Address) != 0 ? "True" : "False");
  log_i("IsNonePage: %s\n", MmIsNonPagedSystemAddressValid(Address) != 0 ? "True" : "False");

  return STATUS_UNSUCCESSFUL;
  ULONG COUNT = 0;
  // __debugbreak();
  if (NT_SUCCESS(PsSuspendThread(workThread, &COUNT)))
  {
    KAPC apc;
    KeInitializeApc(
      &apc,
      workThread,
      OriginalApcEnvironment,
      MyKernelApcRoutine,
      NULL,
      NULL,
      KernelMode,
      NULL
    );

    BOOLEAN success = KeInsertQueueApc(&apc, NULL, NULL, IO_NO_INCREMENT);
    if (success) {
      DbgPrint("Kernel-mode APC successfully injected.\n");
    }
    else {
      DbgPrint("Failed to inject APC.\n");
    }

    while (!over)
    {
      KSleep(1000);
    }
    PsResumeThread(workThread, &COUNT);
  }

 

  driver_obj->DriverUnload = DriverUnload;
  return STATUS_UNSUCCESSFUL;
}