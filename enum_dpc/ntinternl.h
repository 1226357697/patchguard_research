#pragma once
#include <ntifs.h>
#include <intrin.h>

//0x20 bytes (sizeof)
struct _KTIMER_TABLE_ENTRY
{
  ULONGLONG Lock;                                                         //0x0
  struct _LIST_ENTRY Entry;                                               //0x8
  union _ULARGE_INTEGER Time;                                             //0x18
};

//0x2200 bytes (sizeof)
struct _KTIMER_TABLE
{
  struct _KTIMER* TimerExpiry[64];                                        //0x0
  struct _KTIMER_TABLE_ENTRY TimerEntries[256];                           //0x200
};

//0x8f00 bytes (sizeof)
struct _KPRCB
{
  char padding_0[0x3680];
  struct _KTIMER_TABLE TimerTable;                                        //0x3680
};