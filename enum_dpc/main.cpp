#include <ntifs.h>
#include <stdarg.h>
#include "ntinternl.h"

ULONGLONG* pKiWaitNever = (ULONGLONG*)0xfffff80303028710;
ULONGLONG* pKiWaitAlways = (ULONGLONG*)0xfffff803030288f8;

static ULONG log_i(PCCH fmt, ...)
{
  ULONG ret = 0;
  va_list ap;
  va_start(ap, fmt);
  ret = vDbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, fmt, ap);
  DbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, "\r\n");
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

  //log_i("DeferredContext %p %p ", dpc->DeferredContext, dpc->DeferredRoutine);
  INT64 SpecialBit = (INT64)dpc->DeferredContext >> 47;
  if(SpecialBit != 0 && SpecialBit != -1)
    return true;

  //SpecialBit = (INT64)dpc->DeferredRoutine >> 47;
  //if (SpecialBit != 0 && SpecialBit != -1)
  //  return true;
  return false;
}


EXTERN_C NTSTATUS DriverEntry() 
{
  KPCR* kpcr =  get_kpcr();
  log_i("kpcr: %p", kpcr);
  log_i("timertable: %p", &kpcr->CurrentPrcb->TimerTable);
  log_i("KiWaitNever:%llX KiWaitAlways:%llX ", *pKiWaitNever, *pKiWaitAlways);
  
  _KTIMER_TABLE* ktimer_table = &kpcr->CurrentPrcb->TimerTable;
  for (int i = 0; i < 256; ++i)
  {
    _KTIMER_TABLE_ENTRY* entry = &ktimer_table->TimerEntries[i];
    int try_count = 4096;
    KIRQL OldIrql;  // ÓÃÓÚ´æ´¢¾ÉµÄIRQL
    KeAcquireSpinLock(&entry->Lock, &OldIrql);
    _LIST_ENTRY* list_entry =  entry->Entry.Flink;
    while (list_entry && list_entry->Flink != &entry->Entry)
    {
      if (try_count <= 0)
      {
        log_i("try count end");
        break;
      }

      PKTIMER timer = CONTAINING_RECORD(list_entry, KTIMER, TimerListEntry);

      log_i("undocde timer:%p dpc:%p(%p) guess_pg:%d", timer, timer->Dpc, decode_dpc(timer), guess_pg(timer) ? 1:0);
      if (guess_pg(timer))
      {
        __debugbreak();
      }
      //__debugbreak();
      try_count--;
      list_entry = list_entry->Flink;
    }
    KeReleaseSpinLock(&entry->Lock, OldIrql);

  }


  log_i("end");
  return STATUS_UNSUCCESSFUL;
}