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


typedef struct _LARGE_PAGE_INFO {
  PVOID  BaseAddress;
  SIZE_T RegionSize;
} LARGE_PAGE_INFO, * PLARGE_PAGE_INFO;
#define POOL_BIG_TABLE_ENTRY_FREE 0x1

typedef struct _POOL_TRACKER_BIG_PAGES
{
    void* Va;// Offset=0x0 Size=0x8
    unsigned long Key;// Offset=0x8 Size=0x4
    unsigned long Pattern : 8;// Offset=0xc Size=0x4 BitOffset=0x0 BitSize=0x8
    unsigned long PoolType : 12;// Offset=0xc Size=0x4 BitOffset=0x8 BitSize=0xc
    unsigned long SlushSize : 12;// Offset=0xc Size=0x4 BitOffset=0x14 BitSize=0xc
    unsigned int NumberOfBytes;// Offset=0x10 Size=0x8
}POOL_TRACKER_BIG_PAGES;


LONG* PoolBigPageTableSize = (LONG*)0xfffff80302ee7e58;
POOL_TRACKER_BIG_PAGES* PoolBigPageTable = (POOL_TRACKER_BIG_PAGES*)0xfffff80302ee7e50;

VOID EnumerateLargePageNonPagedMemory()
{
  for (int i = 0; i < *PoolBigPageTableSize / sizeof(POOL_TRACKER_BIG_PAGES); i++)
  {
    POOL_TRACKER_BIG_PAGES* page = &PoolBigPageTable[i];

    if (((uint64_t)page->Va & POOL_BIG_TABLE_ENTRY_FREE) ==0)
    {
      log_i("%d page: %p type:%d NumberOfBytes:%08X \n", i, page->Va, page->PoolType, page->NumberOfBytes);
    }

  }
}


VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registerPath)
{
  EnumerateLargePageNonPagedMemory();
  driver_obj->DriverUnload = DriverUnload;
  return STATUS_UNSUCCESSFUL;
}