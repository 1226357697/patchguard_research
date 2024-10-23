#include <ntifs.h>
#include <stdarg.h>
#include <stdint.h>
#include "ntinternl.h"
#include "InlineHook.h"


PVOID pg_context = NULL;

#define ALIGN_DOWN(len, align) \
  ((len) & ~((align) -1))

#define ALIGN_UP(len, align) \
  (ALIGN_DOWN( ((len) + (align)-1), (align)))

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
  
EXTERN_C
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

EXTERN_C
BOOLEAN
NTAPI
KeInsertQueueApc(IN PKAPC Apc,
  IN PVOID SystemArgument1,
  IN PVOID SystemArgument2,
  IN KPRIORITY PriorityBoost);


#define  DWORD DWORD32
#define  BYTE CHAR

typedef struct _RUNTIME_FUNCTION {
  DWORD BeginAddress;
  DWORD EndAddress;
  DWORD UnwindData;
} RUNTIME_FUNCTION, * PRUNTIME_FUNCTION;

#define UNWIND_HISTORY_TABLE_SIZE 12

typedef struct _UNWIND_HISTORY_TABLE_ENTRY
{
  DWORD64 ImageBase;
  PRUNTIME_FUNCTION FunctionEntry;
} UNWIND_HISTORY_TABLE_ENTRY, * PUNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE
{
  DWORD Count;
  BYTE  LocalHint;
  BYTE  GlobalHint;
  BYTE  Search;
  BYTE  Once;
  ULONG64 LowAddress;
  ULONG64 HighAddress;
  UNWIND_HISTORY_TABLE_ENTRY Entry[UNWIND_HISTORY_TABLE_SIZE];
} UNWIND_HISTORY_TABLE, * PUNWIND_HISTORY_TABLE;

EXTERN_C
PRUNTIME_FUNCTION
NTAPI
RtlLookupFunctionEntry(
  IN DWORD64 ControlPc,
  OUT PDWORD64 ImageBase,
  OUT PUNWIND_HISTORY_TABLE HistoryTable);

typedef
NTSTATUS
(NTAPI* PsSuspendThread_t)(
  IN PETHREAD Thread,
  OUT PULONG PreviousCount OPTIONAL);

typedef
NTSTATUS
(NTAPI* PsResumeThread_t)(
  IN PETHREAD Thread,
  OUT PULONG PreviousCount OPTIONAL
  );


ULONGLONG* pKiWaitNever = (ULONGLONG*)0xfffff80303028710;
ULONGLONG* pKiWaitAlways = (ULONGLONG*)0xfffff803030288f8;


typedef struct _SameThreadPassiveFlags
{
  ULONG ActiveExWorker : 1;                                         //0x6e4
  ULONG MemoryMaker : 1;                                            //0x6e4
  ULONG StoreLockThread : 2;                                        //0x6e4
  ULONG ClonedThread : 1;                                           //0x6e4
  ULONG KeyedEventInUse : 1;                                        //0x6e4
  ULONG SelfTerminate : 1;                                          //0x6e4
  ULONG RespectIoPriority : 1;                                      //0x6e4
  ULONG ActivePageLists : 1;                                        //0x6e4
  ULONG SecureContext : 1;                                          //0x6e4
  ULONG ZeroPageThread : 1;                                         //0x6e4
  ULONG WorkloadClass : 1;                                          //0x6e4
  ULONG ReservedSameThreadPassiveFlags : 20;                        //0x6e4
}SameThreadPassiveFlags;



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



static ULONG log_i(PCCH fmt, ...)
{
  ULONG ret = 0;
  va_list ap;
  va_start(ap, fmt);
  ret = vDbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, fmt, ap);
  va_end(ap);
  return ret;
}

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
    PHYSICAL_ADDRESS tmp_phys = MmGetPhysicalAddress(pxt);

    if (tmp_phys.QuadPart == physical_page_base)
    {
      self_index = i;
      break;
    }
  }
  if (self_index == 0)
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
    return;

  PMMPTE_HARDWARE pte = MiAddressToPxe(Address);
  if (pte->Valid == 0) return;
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
  if (pte->Valid == 0) return FALSE;
  if (pte->Valid != 0 && pte->LargePage != 0)
    return TRUE;

  pte = MiAddressToPde(Address);
  if (pte->Valid == 0) return FALSE;
  if (pte->Valid != 0 && pte->LargePage != 0)
    return TRUE;

  pte = MiAddressToPte(Address);
  if (pte->Valid == 0) return FALSE;
  if (pte->Valid != 0 && pte->LargePage != 0)
    return TRUE;

  return FALSE;
}



void KSleep(LONGLONG milliseconds)
{
  LARGE_INTEGER interval;
  interval.QuadPart = -(10 * 1000 * milliseconds);
  KeDelayExecutionThread(KernelMode, FALSE, &interval);

}

KPCR* get_kpcr()
{
  return (KPCR*)__readgsqword(0x18);
}

KDPC* decode_dpc(PKTIMER timer) 
{
/*
* enc_dpc = ror(bswap( KiWaitAlways ^ dpc) ^ timer, (char)KiWaitNever) ^ KiWaitNever
* dpc = bswap(rol(enc_dpc ^ KiWaitNever, (char)KiWaitNever) ^ timer) ^ KiWaitAlways
*/
  UINT64 dec_dpc = (UINT64)timer->Dpc;
  return (KDPC*)(_byteswap_uint64(_rotl64( dec_dpc ^ *pKiWaitNever, *(char*)pKiWaitNever) ^ (UINT64)timer) ^ *pKiWaitAlways);
}

bool guess_pg(PKTIMER timer)
{
  if(timer == NULL)
    return false;

  KDPC* dpc = decode_dpc(timer);
  if(dpc == NULL || !MmIsAddressValid(dpc))
    return false;

  if (dpc->DeferredRoutine == (PVOID)0xfffff80302ded770 
    || dpc->DeferredRoutine == (PVOID)0xfffff80302bb2030)
  {

    log_i("dpc->DeferredRoutine: %p\n", dpc->DeferredRoutine);
  }
  uint64_t pg_ptr_xor = *(uint64_t*)(dpc + 1);
  //log_i("DeferredContext %p %p \n", dpc->DeferredContext, dpc->DeferredRoutine);
  INT64 SpecialBit = (INT64)dpc->DeferredContext >> 47;
  if (SpecialBit != 0 && SpecialBit != -1)
  {
    pg_context = (PVOID)((uint64_t)dpc->DeferredContext ^ pg_ptr_xor | 0xFFFF800000000000);
    
    if (MmIsAddressValid(pg_context))
    {

      return true;
    }
  }

  //if (dpc == (KDPC*)0xFFFF898B1032895F || dpc == (KDPC*)0xFFFF898B1033B21B)
  //{
  //  if (dpc == (KDPC*)0xFFFF898B1032895F || dpc == (KDPC*)0xFFFF898B1033B21B)
  //  {
  //    __debugbreak();
  //  }
  //  if (!MmIsAddressValid(dpc->DeferredContext) && MmIsAddressValid((PVOID)(((uint64_t)dpc->DeferredContext ^ pg_ptr_xor) | 0xFFFF800000000000)))
  //  {
  //    log_i("dpc:%p is not general pg xor\n", dpc);
  //    pg_context = (PVOID)((uint64_t)dpc->DeferredContext ^ pg_ptr_xor | 0xFFFF800000000000);
  //    return true;
  //  }
  //}


  return false;
}


void* ExpWorkerThread = (void*)0xfffff80302b72de0;
PsSuspendThread_t PsSuspendThread = (PsSuspendThread_t)0Xfffff80303190c60;
PsResumeThread_t  PsResumeThread = (PsResumeThread_t)0xfffff8030317a050;

PETHREAD LoopupThread(HANDLE tid)
{
  PETHREAD thread = NULL;
  PsLookupThreadByThreadId(tid, &thread);
  return thread;
}

BOOLEAN InSystemArea(PVOID address)
{
  PVOID start = (PVOID)0xfffff80302ab6000 ;
  PVOID end = (PVOID)0xfffff8030356b000;
  return address >= start && address< end;
}

BOOLEAN finc_dec_pg_context(PVOID address)
{
  if (!MmIsAddressValid(address))
  {
    return FALSE;
  }

  ULONG64 _address = (ULONG64)address;
  _address = ALIGN_DOWN(_address, PAGE_SIZE);
  while (MmIsAddressValid((PVOID)_address))
  {
    _address-= PAGE_SIZE;
  }
  _address += PAGE_SIZE;

  ULONG64 max_limit= PAGE_SIZE *2;

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
      pg_context = (PVOID)(_address + i);
      return TRUE;
    }

  }

  return FALSE;
}

BOOLEAN is_pg_work =FALSE;
BOOLEAN over = FALSE;
VOID MyKernelApcRoutine(
  PKAPC Apc,
  PKNORMAL_ROUTINE* NormalRoutine,
  PVOID* NormalContext,
  PVOID* SystemArgument1,
  PVOID* SystemArgument2)
{
  // 内核 APC 执行的例子
  PVOID caller[16];
  ULONG level = RtlWalkFrameChain((PVOID*)&caller, 16, 0);

  for (int i = 1; i < level; ++i)
  {
    // 废案：
    // 某些情况下不是大页， 不能用大页判断， 但一定是非分页内存
    // 不能直接判断地址是否是非分页内存
    // 使用 RtlLookupFunctionEntry 判断是否是模块内的地址

    //__try
    //{
    //  DWORD64 base = 0;
    //  UNWIND_HISTORY_TABLE unwind;
    //  //if (MmIsAddressValid(caller[i]) && RtlLookupFunctionEntry((DWORD64)caller[i], &base, &unwind) == NULL)
    //  if (MmIsAddressValid(caller[i]) && IsLargePage(caller[i]))
    //  {
    //    //__debugbreak();
    //    log_i("walk level: %d, frame:%p\n", i, caller[i]);
    //    // 找解密后的 CmpAppendDllSection
    //    is_pg_work = TRUE;
    //    break;
    //  }
    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) {
    //  log_i("error frame:%p\n", i, caller[i]);
    //}

    if (MmIsAddressValid(caller[i]) && !InSystemArea(caller[i]) && finc_dec_pg_context(caller[i]))
    {
      log_i("walk level: %d, frame:%p\n", i, caller[i]);
      // 找解密后的 CmpAppendDllSection
      is_pg_work = TRUE;
      break;
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
      while (!over)
      {
        KSleep(1000);
      }
    }
 

   
    PsResumeThread(workThread, &count);
  }
  return is_pg_work;
}

int FindPgRun()
{

  for (int i = 0; i < 100000; i += 4)
  {
    PETHREAD thead = LoopupThread((HANDLE)i);
    if (thead)
    {
      CHAR PreviousMode = *(CHAR*)(((char*)thead) + 0x232);
      UCHAR Running = *(UCHAR*)(((char*)thead) + 0x71) ;
      if (Running == 1)
      {
        log_i("FindPgRun :%p", thead);

      }
    }

  }
  return 0;
}

int  FindWorkerITemThread()
{
  int count = 0;
  PEPROCESS systemPorcess = NULL;
  NTSTATUS status;
  status = PsLookupProcessByProcessId((HANDLE)4, &systemPorcess);
  if (!NT_SUCCESS(status))
  {
    return count;
  }

  for (int i = 0; i < 100000; i += 4)
  {
    PETHREAD thead = LoopupThread((HANDLE)i);
    if (thead && IoThreadToProcess(thead) == systemPorcess)
    {
      PVOID SatrtAddress = *(PVOID*)(((char*)thead) + 0x6a0);
      //ULONG returnLenght = 0;
      SameThreadPassiveFlags* falgs = (SameThreadPassiveFlags*)(((char*)thead) + 0x6e4);
      UCHAR WaitReason = *(UCHAR*)(((char*)thead) + 0x283);
      if (ExpWorkerThread == SatrtAddress && falgs->ActiveExWorker)
      {
      //WrQueue
      /*  if (debug && WaitReason != WrQueue)
        {
          log_i("guess pg worker thead: %p id: %d StartAddress: %p reason: %d\n", thead, i, SatrtAddress, WaitReason);

        }
        if (WaitReason == 4)
        {
          log_i("guess pg worker thead: %p id: %d StartAddress: %p hint hint hint hint hint\n", thead, i, SatrtAddress);
          count++;
        }*/
        //__debugbreak();
        if (CheckWorkThread(thead))
        {
          log_i("guess pg worker thead: %p id: %d WaitReason:%d pg_context: %p\n", thead, i, WaitReason, pg_context);
          count++;
        }

      }
    }

  }

  return count;
}
#define USE_REACTOS_DDK

typedef enum _SYSTEM_INFORMATION_CLASS {
  SystemBasicInformation,
  SystemProcessorInformation,
  SystemPerformanceInformation,
  SystemTimeOfDayInformation,
  SystemPathInformation,
  SystemProcessInformation,
  SystemCallCountInformation,
  SystemDeviceInformation,
  SystemProcessorPerformanceInformation,
  SystemFlagsInformation,
  SystemCallTimeInformation,
  SystemModuleInformation,
  SystemLocksInformation,
  SystemStackTraceInformation,
  SystemPagedPoolInformation,
  SystemNonPagedPoolInformation,
  SystemHandleInformation,
  SystemObjectInformation,
  SystemPageFileInformation,
  SystemVdmInstemulInformation,
  SystemVdmBopInformation,
  SystemFileCacheInformation,
  SystemPoolTagInformation,
  SystemInterruptInformation,
  SystemDpcBehaviorInformation,
  SystemFullMemoryInformation,
  SystemLoadGdiDriverInformation,
  SystemUnloadGdiDriverInformation,
  SystemTimeAdjustmentInformation,
  SystemSummaryMemoryInformation,
#ifndef USE_REACTOS_DDK
  SystemNextEventIdInformation,
  SystemEventIdsInformation,
  SystemCrashDumpInformation,
#else
  SystemMirrorMemoryInformation,
  SystemPerformanceTraceInformation,
  SystemObsolete0,
#endif // USE_REACTOS_DDK
  SystemExceptionInformation,
  SystemCrashDumpStateInformation,
  SystemKernelDebuggerInformation,
  SystemContextSwitchInformation,
  SystemRegistryQuotaInformation,
  SystemExtendServiceTableInformation,
  SystemPrioritySeperation,
  SystemPlugPlayBusInformation,
  SystemDockInformation,
#ifdef USE_REACTOS_DDK
  SystemPowerInformationNative,
#elif defined IRP_MN_START_DEVICE
  SystemPowerInformationInfo,
#else
  SystemPowerInformation,
#endif // USE_REACTOS_DDK
  SystemProcessorSpeedInformation,
  SystemCurrentTimeZoneInformation,
  SystemLookasideInformation,
#ifdef USE_REACTOS_DDK
  SystemTimeSlipNotification,
  SystemSessionCreate,
  SystemSessionDetach,
  SystemSessionInformation,
  SystemRangeStartInformation,
  SystemVerifierInformation,
  SystemAddVerifier,
  SystemSessionProcessesInformation,
  SystemLoadGdiDriverInSystemSpaceInformation,
  SystemNumaProcessorMap,
  SystemPrefetcherInformation,
  SystemExtendedProcessInformation,
  SystemRecommendedSharedDataAlignment,
  SystemComPlusPackage,
  SystemNumaAvailableMemory,
  SystemProcessorPowerInformation,
  SystemEmulationBasicInformation,
  SystemEmulationProcessorInformation,
  SystemExtendedHanfleInformation,
  SystemLostDelayedWriteInformation,
  SystemBigPoolInformation,
  SystemSessionPoolTagInformation,
  SystemSessionMappedViewInformation,
  SystemHotpatchInformation,
  SystemObjectSecurityMode,
  SystemWatchDogTimerHandler,
  SystemWatchDogTimerInformation,
  SystemLogicalProcessorInformation,
  SystemWo64SharedInformationObosolete,
  SystemRegisterFirmwareTableInformationHandler,
  SystemFirmwareTableInformation,
  SystemModuleInformationEx,
  SystemVerifierTriageInformation,
  SystemSuperfetchInformation,
  SystemMemoryListInformation,
  SystemFileCacheInformationEx,
  SystemThreadPriorityClientIdInformation,
  SystemProcessorIdleCycleTimeInformation,
  SystemVerifierCancellationInformation,
  SystemProcessorPowerInformationEx,
  SystemRefTraceInformation,
  SystemSpecialPoolInformation,
  SystemProcessIdInformation,
  SystemErrorPortInformation,
  SystemBootEnvironmentInformation,
  SystemHypervisorInformation,
  SystemVerifierInformationEx,
  SystemTimeZoneInformation,
  SystemImageFileExecutionOptionsInformation,
  SystemCoverageInformation,
  SystemPrefetchPathInformation,
  SystemVerifierFaultsInformation,
  MaxSystemInfoClass,
#endif // USE_REACTOS_DDK
} SYSTEM_INFORMATION_CLASS;

int  FindDPC()
{
  int count = 0;
  KPCR* kpcr = NULL;
  int cpu_num = KeNumberProcessors;
  for (int num  =0; num < cpu_num; ++num)
  {
    KeSetSystemAffinityThread(num +1);
    kpcr = get_kpcr();

    KeRevertToUserAffinityThread();

    log_i("kpcr: %p(%d)\n", kpcr, num +1);
    log_i("timertable: %p\n", &kpcr->CurrentPrcb->TimerTable);
    _KTIMER_TABLE* ktimer_table = &kpcr->CurrentPrcb->TimerTable;
    for (int i = 0; i < 256; ++i)
    {
      _KTIMER_TABLE_ENTRY* entry = &ktimer_table->TimerEntries[i];
      int try_count = 8096;
      KIRQL OldIrql;  // 用于存储旧的IRQL
      KeAcquireSpinLock(&entry->Lock, &OldIrql);
      _LIST_ENTRY* list_entry = entry->Entry.Flink;
      while (list_entry && list_entry->Flink != &entry->Entry)
      {
        if (try_count <= 0)
        {
          log_i("try count end\n");
          break;
        }
        
        PKTIMER timer = CONTAINING_RECORD(list_entry, KTIMER, TimerListEntry);
        if (guess_pg(timer))
        {
          log_i("guess pg timer:%p dpc:%p(%p) pg_context:%p\n", timer, timer->Dpc, decode_dpc(timer), pg_context);
          pg_context = 0;
          count++;
          //__debugbreak();
        }
        //__debugbreak();
        try_count--;
        list_entry = list_entry->Flink;
      }
      KeReleaseSpinLock(&entry->Lock, OldIrql);

    }

    
    for (int i = 0; i < 64; ++i)
    {
      _KTIMER* timer = ktimer_table->TimerExpiry[i];
      if (timer)
      {
        log_i("TimerExpiry timer:%p\n", timer);
        if (guess_pg(timer))
        {
          log_i("TimerExpiry guess pg timer:%p dpc:%p(%p) pg_context:%p\n", timer, timer->Dpc, decode_dpc(timer), pg_context);
          pg_context = 0;
          count++;
          __debugbreak();
        }
      }
    }

    _KDPC_DATA* DpcData = (_KDPC_DATA*)(((char*)kpcr->CurrentPrcb) + 0x2e00);
    for (int i = 0; i< 2; ++i)
    { 
      PKDPC dpc = DpcData[i].ActiveDpc;
      if (dpc)
      {
        log_i("DpcData dpc:%p\n", dpc);
        uint64_t pg_ptr_xor = *(uint64_t*)(dpc + 1);
        //log_i("DeferredContext %p %p \n", dpc->DeferredContext, dpc->DeferredRoutine);
        INT64 SpecialBit = (INT64)dpc->DeferredContext >> 47;
        if (SpecialBit != 0 && SpecialBit != -1)
        {

          log_i("DpcData guess pg  dpc:%p\n", dpc);
          __debugbreak();
        }
      }

    }



  }
  

  return count;
}


typedef
BOOLEAN
(*KeInsertQueueDpc_t)(
  _Inout_ PRKDPC Dpc,
  _In_opt_ PVOID SystemArgument1,
  _In_opt_ __drv_aliasesMem PVOID SystemArgument2
);
KeInsertQueueDpc_t  OriginalKeInsertQueueDpc = NULL;

typedef
VOID 
(*ExQueueWorkItem_t)(
  _Inout_ __drv_aliasesMem PWORK_QUEUE_ITEM WorkItem,
  _In_ WORK_QUEUE_TYPE QueueType
);
ExQueueWorkItem_t  OriginalExQueueWorkItem = NULL;

BOOLEAN
DetoursKeInsertQueueDpc(
  _Inout_ PRKDPC Dpc,
  _In_opt_ PVOID SystemArgument1,
  _In_opt_ __drv_aliasesMem PVOID SystemArgument2
)
{
  if (MmIsAddressValid(Dpc))
  {
    //log_i("DeferredContext %p %p \n", dpc->DeferredContext, dpc->DeferredRoutine);
    INT64 SpecialBit = (INT64)Dpc->DeferredContext >> 47;
    if (SpecialBit != 0 && SpecialBit != -1)
    {
      uint64_t pg_ptr_xor = *(uint64_t*)(Dpc + 1);
      PVOID context = (PVOID)((uint64_t)Dpc->DeferredContext ^ pg_ptr_xor | 0xFFFF800000000000);

      __debugbreak();
      if (MmIsAddressValid(context))
      {

        log_i("PG DPC insert \n");
        __debugbreak();
      }
    }
  }


  return OriginalKeInsertQueueDpc(Dpc, SystemArgument1, SystemArgument2);
}

VOID
DetoursExQueueWorkItem(
  _Inout_ __drv_aliasesMem PWORK_QUEUE_ITEM WorkItem,
  _In_ WORK_QUEUE_TYPE QueueType
)
{
  if (QueueType == DelayedWorkQueue)
  {
    
    if (finc_dec_pg_context(WorkItem->Parameter) || finc_dec_pg_context(WorkItem->WorkerRoutine))
    {
      log_i("PG WorkItem insert \n");
      __debugbreak();
    }
  }
  return OriginalExQueueWorkItem(WorkItem, QueueType);
}

BOOLEAN HOOKED_KeINsertQueueDpc = FALSE;
BOOLEAN HOOKED_ExQueueWorkItem = FALSE;

void UnHookFunction()
{
  if (HOOKED_KeINsertQueueDpc)
  {
    RemoveInlineHook(KeInsertQueueDpc, OriginalKeInsertQueueDpc);
  }

  if (HOOKED_ExQueueWorkItem)
  {
    RemoveInlineHook(ExQueueWorkItem, OriginalExQueueWorkItem);
  }
}

void HookFunction()
{
  if (HOOKED_ExQueueWorkItem == FALSE)
  {
    log_i("DetoursExQueueWorkItem\n");
    NTSTATUS status = SetInlineHook(ExQueueWorkItem, DetoursExQueueWorkItem, (PVOID*)&OriginalExQueueWorkItem);
    if (!NT_SUCCESS(status))
    {
      log_i("DetoursExQueueWorkItem Failed \n", status);
      HOOKED_ExQueueWorkItem = FALSE;
    }
    else
    {
      log_i("DetoursExQueueWorkItem Success \n", status);
      HOOKED_ExQueueWorkItem = TRUE;
    }
  }

  if (HOOKED_KeINsertQueueDpc == FALSE)
  {
    log_i("DetoursKeInsertQueueDpc\n");
    NTSTATUS status = SetInlineHook(KeInsertQueueDpc, DetoursKeInsertQueueDpc, (PVOID*)&OriginalKeInsertQueueDpc);
    if (!NT_SUCCESS(status))
    {
      log_i("DetoursKeInsertQueueDpc Failed \n", status);
      HOOKED_KeINsertQueueDpc = FALSE;
    }
    else
    {
      log_i("DetoursKeInsertQueueDpc Success \n", status);
      HOOKED_KeINsertQueueDpc = TRUE;
    }
  }
  
}


bool working = false;
bool END = false;
VOID WorkerThread( _In_ PVOID StartContext )
{
  working = true;
  END = false;
  NTSTATUS status;

  while (working)
  {
    int dpc_count = FindDPC();
    log_i("PG DPC count: %d \n", dpc_count);

    int worker_thread_coubt = FindWorkerITemThread();
    log_i("PG worker thread count: %d \n", worker_thread_coubt);

    log_i("PG total count: %d \n", dpc_count + worker_thread_coubt);


    //int toal_count = (dpc_count + worker_thread_coubt);
    //if (toal_count == 0)
    //{
    //  HookFunction();
    //}
    //else
    //{
    //  // 待执行PG
    //  UnHookFunction();
    //}

    //if ( (dpc_count + worker_thread_coubt) == 0 && HOOKED_KeINsertQueueDpc == FALSE)
    //{
    //  

    //}
    
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

  UnHookFunction();
}


EXTERN_C
NTSTATUS
NTAPI
PsGetContextThread(IN PETHREAD Thread,
  IN OUT PCONTEXT ThreadContext,
  IN KPROCESSOR_MODE PreviousMode);

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registerPath)
{
  if (!GetPageTableBase())
  {
    return STATUS_UNSUCCESSFUL;
  }
  
  log_i("KiWaitNever:%llX KiWaitAlways:%llX \n", *pKiWaitNever, *pKiWaitAlways);

  //HookFunction();

  driver_obj->DriverUnload = DriverUnload;
  CLIENT_ID       ClientID = { 0 };
  return PsCreateSystemThread(&thread, 0, NULL, NtCurrentProcess(), &ClientID, WorkerThread, NULL);
}