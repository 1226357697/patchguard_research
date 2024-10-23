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


// Source: http://processhacker.sourceforge.net
typedef enum _SYSTEM_INFORMATION_CLASS
{
  SystemBasicInformation, // q: SYSTEM_BASIC_INFORMATION
  SystemProcessorInformation, // q: SYSTEM_PROCESSOR_INFORMATION
  SystemPerformanceInformation, // q: SYSTEM_PERFORMANCE_INFORMATION
  SystemTimeOfDayInformation, // q: SYSTEM_TIMEOFDAY_INFORMATION
  SystemPathInformation, // not implemented
  SystemProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
  SystemCallCountInformation, // q: SYSTEM_CALL_COUNT_INFORMATION
  SystemDeviceInformation, // q: SYSTEM_DEVICE_INFORMATION
  SystemProcessorPerformanceInformation, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
  SystemFlagsInformation, // q: SYSTEM_FLAGS_INFORMATION
  SystemCallTimeInformation, // not implemented // SYSTEM_CALL_TIME_INFORMATION // 10
  SystemModuleInformation, // q: RTL_PROCESS_MODULES
  SystemLocksInformation, // q: RTL_PROCESS_LOCKS
  SystemStackTraceInformation, // q: RTL_PROCESS_BACKTRACES
  SystemPagedPoolInformation, // not implemented
  SystemNonPagedPoolInformation, // not implemented
  SystemHandleInformation, // q: SYSTEM_HANDLE_INFORMATION
  SystemObjectInformation, // q: SYSTEM_OBJECTTYPE_INFORMATION mixed with SYSTEM_OBJECT_INFORMATION
  SystemPageFileInformation, // q: SYSTEM_PAGEFILE_INFORMATION
  SystemVdmInstemulInformation, // q
  SystemVdmBopInformation, // not implemented // 20
  SystemFileCacheInformation, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemCache)
  SystemPoolTagInformation, // q: SYSTEM_POOLTAG_INFORMATION
  SystemInterruptInformation, // q: SYSTEM_INTERRUPT_INFORMATION
  SystemDpcBehaviorInformation, // q: SYSTEM_DPC_BEHAVIOR_INFORMATION; s: SYSTEM_DPC_BEHAVIOR_INFORMATION (requires SeLoadDriverPrivilege)
  SystemFullMemoryInformation, // not implemented
  SystemLoadGdiDriverInformation, // s (kernel-mode only)
  SystemUnloadGdiDriverInformation, // s (kernel-mode only)
  SystemTimeAdjustmentInformation, // q: SYSTEM_QUERY_TIME_ADJUST_INFORMATION; s: SYSTEM_SET_TIME_ADJUST_INFORMATION (requires SeSystemtimePrivilege)
  SystemSummaryMemoryInformation, // not implemented
  SystemMirrorMemoryInformation, // s (requires license value "Kernel-MemoryMirroringSupported") (requires SeShutdownPrivilege) // 30
  SystemPerformanceTraceInformation, // q; s: (type depends on EVENT_TRACE_INFORMATION_CLASS)
  SystemObsolete0, // not implemented
  SystemExceptionInformation, // q: SYSTEM_EXCEPTION_INFORMATION
  SystemCrashDumpStateInformation, // s (requires SeDebugPrivilege)
  SystemKernelDebuggerInformation, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION
  SystemContextSwitchInformation, // q: SYSTEM_CONTEXT_SWITCH_INFORMATION
  SystemRegistryQuotaInformation, // q: SYSTEM_REGISTRY_QUOTA_INFORMATION; s (requires SeIncreaseQuotaPrivilege)
  SystemExtendServiceTableInformation, // s (requires SeLoadDriverPrivilege) // loads win32k only
  SystemPrioritySeperation, // s (requires SeTcbPrivilege)
  SystemVerifierAddDriverInformation, // s (requires SeDebugPrivilege) // 40
  SystemVerifierRemoveDriverInformation, // s (requires SeDebugPrivilege)
  SystemProcessorIdleInformation, // q: SYSTEM_PROCESSOR_IDLE_INFORMATION
  SystemLegacyDriverInformation, // q: SYSTEM_LEGACY_DRIVER_INFORMATION
  SystemCurrentTimeZoneInformation, // q
  SystemLookasideInformation, // q: SYSTEM_LOOKASIDE_INFORMATION
  SystemTimeSlipNotification, // s (requires SeSystemtimePrivilege)
  SystemSessionCreate, // not implemented
  SystemSessionDetach, // not implemented
  SystemSessionInformation, // not implemented
  SystemRangeStartInformation, // q: SYSTEM_RANGE_START_INFORMATION // 50
  SystemVerifierInformation, // q: SYSTEM_VERIFIER_INFORMATION; s (requires SeDebugPrivilege)
  SystemVerifierThunkExtend, // s (kernel-mode only)
  SystemSessionProcessInformation, // q: SYSTEM_SESSION_PROCESS_INFORMATION
  SystemLoadGdiDriverInSystemSpace, // s (kernel-mode only) (same as SystemLoadGdiDriverInformation)
  SystemNumaProcessorMap, // q
  SystemPrefetcherInformation, // q: PREFETCHER_INFORMATION; s: PREFETCHER_INFORMATION // PfSnQueryPrefetcherInformation
  SystemExtendedProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
  SystemRecommendedSharedDataAlignment, // q
  SystemComPlusPackage, // q; s
  SystemNumaAvailableMemory, // 60
  SystemProcessorPowerInformation, // q: SYSTEM_PROCESSOR_POWER_INFORMATION
  SystemEmulationBasicInformation, // q
  SystemEmulationProcessorInformation,
  SystemExtendedHandleInformation, // q: SYSTEM_HANDLE_INFORMATION_EX
  SystemLostDelayedWriteInformation, // q: ULONG
  SystemBigPoolInformation, // q: SYSTEM_BIGPOOL_INFORMATION
  SystemSessionPoolTagInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION
  SystemSessionMappedViewInformation, // q: SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
  SystemHotpatchInformation, // q; s
  SystemObjectSecurityMode, // q // 70
  SystemWatchdogTimerHandler, // s (kernel-mode only)
  SystemWatchdogTimerInformation, // q (kernel-mode only); s (kernel-mode only)
  SystemLogicalProcessorInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION
  SystemWow64SharedInformationObsolete, // not implemented
  SystemRegisterFirmwareTableInformationHandler, // s (kernel-mode only)
  SystemFirmwareTableInformation, // SYSTEM_FIRMWARE_TABLE_INFORMATION
  SystemModuleInformationEx, // q: RTL_PROCESS_MODULE_INFORMATION_EX
  SystemVerifierTriageInformation, // not implemented
  SystemSuperfetchInformation, // q; s: SUPERFETCH_INFORMATION // PfQuerySuperfetchInformation
  SystemMemoryListInformation, // q: SYSTEM_MEMORY_LIST_INFORMATION; s: SYSTEM_MEMORY_LIST_COMMAND (requires SeProfileSingleProcessPrivilege) // 80
  SystemFileCacheInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (same as SystemFileCacheInformation)
  SystemThreadPriorityClientIdInformation, // s: SYSTEM_THREAD_CID_PRIORITY_INFORMATION (requires SeIncreaseBasePriorityPrivilege)
  SystemProcessorIdleCycleTimeInformation, // q: SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION[]
  SystemVerifierCancellationInformation, // not implemented // name:wow64:whNT32QuerySystemVerifierCancellationInformation
  SystemProcessorPowerInformationEx, // not implemented
  SystemRefTraceInformation, // q; s: SYSTEM_REF_TRACE_INFORMATION // ObQueryRefTraceInformation
  SystemSpecialPoolInformation, // q; s (requires SeDebugPrivilege) // MmSpecialPoolTag, then MmSpecialPoolCatchOverruns != 0
  SystemProcessIdInformation, // q: SYSTEM_PROCESS_ID_INFORMATION
  SystemErrorPortInformation, // s (requires SeTcbPrivilege)
  SystemBootEnvironmentInformation, // q: SYSTEM_BOOT_ENVIRONMENT_INFORMATION // 90
  SystemHypervisorInformation, // q; s (kernel-mode only)
  SystemVerifierInformationEx, // q; s: SYSTEM_VERIFIER_INFORMATION_EX
  SystemTimeZoneInformation, // s (requires SeTimeZonePrivilege)
  SystemImageFileExecutionOptionsInformation, // s: SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION (requires SeTcbPrivilege)
  SystemCoverageInformation, // q; s // name:wow64:whNT32QuerySystemCoverageInformation; ExpCovQueryInformation
  SystemPrefetchPatchInformation, // not implemented
  SystemVerifierFaultsInformation, // s (requires SeDebugPrivilege)
  SystemSystemPartitionInformation, // q: SYSTEM_SYSTEM_PARTITION_INFORMATION
  SystemSystemDiskInformation, // q: SYSTEM_SYSTEM_DISK_INFORMATION
  SystemProcessorPerformanceDistribution, // q: SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION // 100
  SystemNumaProximityNodeInformation, // q
  SystemDynamicTimeZoneInformation, // q; s (requires SeTimeZonePrivilege)
  SystemCodeIntegrityInformation, // q: SYSTEM_CODEINTEGRITY_INFORMATION // SeCodeIntegrityQueryInformation
  SystemProcessorMicrocodeUpdateInformation, // s
  SystemProcessorBrandString, // q // HaliQuerySystemInformation -> HalpGetProcessorBrandString, info class 23
  SystemVirtualAddressInformation, // q: SYSTEM_VA_LIST_INFORMATION[]; s: SYSTEM_VA_LIST_INFORMATION[] (requires SeIncreaseQuotaPrivilege) // MmQuerySystemVaInformation
  SystemLogicalProcessorAndGroupInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX // since WIN7 // KeQueryLogicalProcessorRelationship
  SystemProcessorCycleTimeInformation, // q: SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION[]
  SystemStoreInformation, // q; s // SmQueryStoreInformation
  SystemRegistryAppendString, // s: SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS // 110
  SystemAitSamplingValue, // s: ULONG (requires SeProfileSingleProcessPrivilege)
  SystemVhdBootInformation, // q: SYSTEM_VHD_BOOT_INFORMATION
  SystemCpuQuotaInformation, // q; s // PsQueryCpuQuotaInformation
  SystemNativeBasicInformation, // not implemented
  SystemSpare1, // not implemented
  SystemLowPriorityIoInformation, // q: SYSTEM_LOW_PRIORITY_IO_INFORMATION
  SystemTpmBootEntropyInformation, // q: TPM_BOOT_ENTROPY_NT_RESULT // ExQueryTpmBootEntropyInformation
  SystemVerifierCountersInformation, // q: SYSTEM_VERIFIER_COUNTERS_INFORMATION
  SystemPagedPoolInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypePagedPool)
  SystemSystemPtesInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemPtes) // 120
  SystemNodeDistanceInformation, // q
  SystemAcpiAuditInformation, // q: SYSTEM_ACPI_AUDIT_INFORMATION // HaliQuerySystemInformation -> HalpAuditQueryResults, info class 26
  SystemBasicPerformanceInformation, // q: SYSTEM_BASIC_PERFORMANCE_INFORMATION // name:wow64:whNtQuerySystemInformation_SystemBasicPerformanceInformation
  SystemQueryPerformanceCounterInformation, // q: SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION // since WIN7 SP1
  SystemSessionBigPoolInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION // since WIN8
  SystemBootGraphicsInformation, // q; s: SYSTEM_BOOT_GRAPHICS_INFORMATION (kernel-mode only)
  SystemScrubPhysicalMemoryInformation, // q; s: MEMORY_SCRUB_INFORMATION
  SystemBadPageInformation,
  SystemProcessorProfileControlArea, // q; s: SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA
  SystemCombinePhysicalMemoryInformation, // s: MEMORY_COMBINE_INFORMATION, MEMORY_COMBINE_INFORMATION_EX, MEMORY_COMBINE_INFORMATION_EX2 // 130
  SystemEntropyInterruptTimingCallback,
  SystemConsoleInformation, // q: SYSTEM_CONSOLE_INFORMATION
  SystemPlatformBinaryInformation, // q: SYSTEM_PLATFORM_BINARY_INFORMATION
  SystemThrottleNotificationInformation,
  SystemHypervisorProcessorCountInformation, // q: SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
  SystemDeviceDataInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
  SystemDeviceDataEnumerationInformation,
  SystemMemoryTopologyInformation, // q: SYSTEM_MEMORY_TOPOLOGY_INFORMATION
  SystemMemoryChannelInformation, // q: SYSTEM_MEMORY_CHANNEL_INFORMATION
  SystemBootLogoInformation, // q: SYSTEM_BOOT_LOGO_INFORMATION // 140
  SystemProcessorPerformanceInformationEx, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX // since WINBLUE
  SystemSpare0,
  SystemSecureBootPolicyInformation, // q: SYSTEM_SECUREBOOT_POLICY_INFORMATION
  SystemPageFileInformationEx, // q: SYSTEM_PAGEFILE_INFORMATION_EX
  SystemSecureBootInformation, // q: SYSTEM_SECUREBOOT_INFORMATION
  SystemEntropyInterruptTimingRawInformation,
  SystemPortableWorkspaceEfiLauncherInformation, // q: SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
  SystemFullProcessInformation, // q: SYSTEM_PROCESS_INFORMATION with SYSTEM_PROCESS_INFORMATION_EXTENSION (requires admin)
  SystemKernelDebuggerInformationEx, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
  SystemBootMetadataInformation, // 150
  SystemSoftRebootInformation,
  SystemElamCertificateInformation, // s: SYSTEM_ELAM_CERTIFICATE_INFORMATION
  SystemOfflineDumpConfigInformation,
  SystemProcessorFeaturesInformation, // q: SYSTEM_PROCESSOR_FEATURES_INFORMATION
  SystemRegistryReconciliationInformation,
  SystemEdidInformation,
  SystemManufacturingInformation, // q: SYSTEM_MANUFACTURING_INFORMATION // since THRESHOLD
  SystemEnergyEstimationConfigInformation, // q: SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
  SystemHypervisorDetailInformation, // q: SYSTEM_HYPERVISOR_DETAIL_INFORMATION
  SystemProcessorCycleStatsInformation, // q: SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION // 160
  SystemVmGenerationCountInformation,
  SystemTrustedPlatformModuleInformation, // q: SYSTEM_TPM_INFORMATION
  SystemKernelDebuggerFlags,
  SystemCodeIntegrityPolicyInformation, // q: SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
  SystemIsolatedUserModeInformation, // q: SYSTEM_ISOLATED_USER_MODE_INFORMATION
  SystemHardwareSecurityTestInterfaceResultsInformation,
  SystemSingleModuleInformation, // q: SYSTEM_SINGLE_MODULE_INFORMATION
  SystemAllowedCpuSetsInformation,
  SystemDmaProtectionInformation, // q: SYSTEM_DMA_PROTECTION_INFORMATION
  SystemInterruptCpuSetsInformation, // q: SYSTEM_INTERRUPT_CPU_SET_INFORMATION // 170
  SystemSecureBootPolicyFullInformation, // q: SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION
  SystemCodeIntegrityPolicyFullInformation,
  SystemAffinitizedInterruptProcessorInformation,
  SystemRootSiloInformation, // q: SYSTEM_ROOT_SILO_INFORMATION
  SystemCpuSetInformation, // q: SYSTEM_CPU_SET_INFORMATION // since THRESHOLD2
  SystemCpuSetTagInformation, // q: SYSTEM_CPU_SET_TAG_INFORMATION
  SystemWin32WerStartCallout,
  SystemSecureKernelProfileInformation, // q: SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION
  SystemCodeIntegrityPlatformManifestInformation, // q: SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION // since REDSTONE
  SystemInterruptSteeringInformation, // 180
  SystemSupportedProcessorArchitectures,
  SystemMemoryUsageInformation, // q: SYSTEM_MEMORY_USAGE_INFORMATION
  SystemCodeIntegrityCertificateInformation, // q: SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
  SystemPhysicalMemoryInformation, // q: SYSTEM_PHYSICAL_MEMORY_INFORMATION // since REDSTONE2
  SystemControlFlowTransition,
  SystemKernelDebuggingAllowed,
  SystemActivityModerationExeState, // SYSTEM_ACTIVITY_MODERATION_EXE_STATE
  SystemActivityModerationUserSettings, // SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS
  SystemCodeIntegrityPoliciesFullInformation,
  SystemCodeIntegrityUnlockInformation, // SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION // 190
  SystemIntegrityQuotaInformation,
  SystemFlushInformation, // q: SYSTEM_FLUSH_INFORMATION
  MaxSystemInfoClass
} SYSTEM_INFORMATION_CLASS;

EXTERN_C
NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySystemInformation(
  IN SYSTEM_INFORMATION_CLASS SystemInfoClass,
  OUT PVOID SystemInfoBuffer,
  IN ULONG SystemInfoBufferSize,
  OUT PULONG BytesReturned OPTIONAL
);


typedef struct _SYSTEM_BIGPOOL_ENTRY
{
  union
  {
    PVOID VirtualAddress;
    ULONG_PTR NonPaged : 1;
  };
  SIZE_T SizeInBytes;
  union
  {
    UCHAR Tag[4];
    ULONG TagUlong;
  };
} SYSTEM_BIGPOOL_ENTRY, * PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION
{
  ULONG Count;
  SYSTEM_BIGPOOL_ENTRY AllocatedInfo[1];
} SYSTEM_BIGPOOL_INFORMATION, * PSYSTEM_BIGPOOL_INFORMATION;

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registerPath)
{
  NTSTATUS status;
  ULONG bigpool_info_size = 0x1000;
  PSYSTEM_BIGPOOL_INFORMATION bigpool_info = NULL;
  do
  {
    bigpool_info = ExAllocatePool(PagedPool, bigpool_info_size);

    status = ZwQuerySystemInformation(SystemBigPoolInformation, bigpool_info, bigpool_info_size, &bigpool_info_size);

  } while (status == STATUS_INFO_LENGTH_MISMATCH);

  if(NT_SUCCESS(status) && bigpool_info)
  {
    for (ULONG i = 0; i < bigpool_info->Count; i++)
    {
      PSYSTEM_BIGPOOL_ENTRY entry = &bigpool_info->AllocatedInfo[i];
      log_i("VirtualAddress: %p NonPaged:%d SizeInBytes:%08X Tag:%c%c%c%c\n", 
        entry->VirtualAddress, entry->NonPaged, entry->SizeInBytes, entry->Tag[0], entry->Tag[1], entry->Tag[2], entry->Tag[3]);
    }
  }

  if (bigpool_info)
  {
    ExFreePool(bigpool_info);
  }

  return STATUS_UNSUCCESSFUL;
#if 0



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

 

#endif // 0
  driver_obj->DriverUnload = DriverUnload;
  return STATUS_UNSUCCESSFUL;
}