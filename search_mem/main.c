#include <ntifs.h>
#include <stdarg.h>
#include <stdint.h>
static ULONG log_i(PCCH fmt, ...)
{
  ULONG ret = 0;
  va_list ap;
  va_start(ap, fmt);
  ret = vDbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, fmt, ap);
  va_end(ap);
  return ret;
}

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

typedef struct _ENODE// Size=0x1c0 (Id=96)
{
  //struct _KNODE Ncb;// Offset=0x0 Size=0x180
  char Ncb[0x180];
  struct _WORK_QUEUE_ITEM HotAddProcessorWorkItem;// Offset=0x180 Size=0x20
}ENODE;

typedef struct _EX_WORK_QUEUE// Size=0x2e0 (Id=1153)
{
  // struct _KPRIQUEUE WorkPriQueue;// Offset=0x0 Size=0x2b0
  char WorkPriQueue[0x2b0];
  struct _EX_PARTITION* Partition;// Offset=0x2b0 Size=0x8
  struct _ENODE* Node;// Offset=0x2b8 Size=0x8
  unsigned long WorkItemsProcessed;// Offset=0x2c0 Size=0x4
  unsigned long WorkItemsProcessedLastPass;// Offset=0x2c4 Size=0x4
  long ThreadCount;// Offset=0x2c8 Size=0x4
  long MinThreads : 31;// Offset=0x2cc Size=0x4 BitOffset=0x0 BitSize=0x1f
  unsigned long TryFailed : 1;// Offset=0x2cc Size=0x4 BitOffset=0x1f BitSize=0x1
  long MaxThreads;// Offset=0x2d0 Size=0x4
  enum _EXQUEUEINDEX QueueIndex;// Offset=0x2d4 Size=0x4
  struct _KEVENT* AllThreadsExitedEvent;// Offset=0x2d8 Size=0x8
}EX_WORK_QUEUE;

EX_WORK_QUEUE* ExWorkerQueue = (EX_WORK_QUEUE*)0xffff898b102899a0;


VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
}

void* ExpWorkerThread = (void*)0xfffff80302b72de0;
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registerPath)
{
  driver_obj->DriverUnload = DriverUnload;
  return STATUS_UNSUCCESSFUL;
}