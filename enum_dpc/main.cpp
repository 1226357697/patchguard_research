#include <ntifs.h>
#include <stdarg.h>
#include "ntinternl.h"

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

static ULONG log_i(PCCH fmt, ...)
{
  ULONG ret = 0;
  va_list ap;
  va_start(ap, fmt);
  ret = vDbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, fmt, ap);
  va_end(ap);
  return ret;
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

  //log_i("DeferredContext %p %p \n", dpc->DeferredContext, dpc->DeferredRoutine);
  INT64 SpecialBit = (INT64)dpc->DeferredContext >> 47;
  if(SpecialBit != 0 && SpecialBit != -1)
    return true;

  //SpecialBit = (INT64)dpc->DeferredRoutine >> 47;
  //if (SpecialBit != 0 && SpecialBit != -1)
  //  return true;
  return false;
}


void* ExpWorkerThread = (void*)0xfffff80302b72de0;


PETHREAD LoopupThread(HANDLE tid)
{
  PETHREAD thread = NULL;
  PsLookupThreadByThreadId(tid, &thread);
  return thread;
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
      if (ExpWorkerThread == SatrtAddress && falgs->ActiveExWorker && WaitReason == 4)
      {
        log_i("guess pg worker thead: %p id: %d StartAddress: %p status: %08X\n", thead, i, SatrtAddress, status);
        //__debugbreak();
        count++;
      }
    }

  }

  return count;
}


KPCR* kpcr = NULL;

int  FindDPC()
{
  int count = 0;
  _KTIMER_TABLE* ktimer_table = &kpcr->CurrentPrcb->TimerTable;
  for (int i = 0; i < 256; ++i)
  {
    _KTIMER_TABLE_ENTRY* entry = &ktimer_table->TimerEntries[i];
    int try_count = 4096;
    KIRQL OldIrql;  // ÓÃÓÚ´æ´¢¾ÉµÄIRQL
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

      // log_i("undocde timer:%p dpc:%p(%p) guess_pg:%d\n", timer, timer->Dpc, decode_dpc(timer), guess_pg(timer) ? 1:0);
      if (guess_pg(timer))
      {
        log_i("guess pg timer:%p dpc:%p(%p)\n", timer, timer->Dpc, decode_dpc(timer));
        count++;
        //__debugbreak();
      }
      //__debugbreak();
      try_count--;
      list_entry = list_entry->Flink;
    }
    KeReleaseSpinLock(&entry->Lock, OldIrql);

  }
  return count;
}

void KSleep(LONGLONG milliseconds)
{
  LARGE_INTEGER interval;
  interval.QuadPart = -(10 * 1000 * milliseconds);
  KeDelayExecutionThread(KernelMode, FALSE, &interval);

}

bool working = false;
bool END = false;
VOID WorkerThread( _In_ PVOID StartContext )
{
  working = true;
  END = false;

  while (working)
  {
    int dpc_count = FindDPC();
    log_i("PG DPC count: %d \n", dpc_count);

    int worker_thread_coubt = FindWorkerITemThread();
    log_i("PG worker thread count: %d \n", worker_thread_coubt);

    log_i("PG total count: %d \n", dpc_count + worker_thread_coubt);

    KSleep(1000);
  }

  END = TRUE;
}


VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
  working = false;
  while (!END)
  {
    KSleep(1000);
  }

}
EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registerPath)
{
  kpcr = get_kpcr();
  log_i("kpcr: %p\n", kpcr);
  log_i("timertable: %p\n", &kpcr->CurrentPrcb->TimerTable);
  log_i("KiWaitNever:%llX KiWaitAlways:%llX \n", *pKiWaitNever, *pKiWaitAlways);

  CLIENT_ID       ClientID = { 0 };
  HANDLE thread = NULL;

  driver_obj->DriverUnload = DriverUnload;
  return PsCreateSystemThread(&thread, 0, NULL, NtCurrentProcess(), &ClientID, WorkerThread, NULL);
}