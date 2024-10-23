#pragma once
#include <ntifs.h>
#include <intrin.h>

//0x10 bytes (sizeof)
struct _KDPC_LIST
{
  struct _SINGLE_LIST_ENTRY ListHead;                                     //0x0
  struct _SINGLE_LIST_ENTRY* LastEntry;                                   //0x8
};

//0x28 bytes (sizeof)
struct _KDPC_DATA
{
  struct _KDPC_LIST DpcList;                                              //0x0
  ULONGLONG DpcLock;                                                      //0x10
  volatile LONG DpcQueueDepth;                                            //0x18
  ULONG DpcCount;                                                         //0x1c
  struct _KDPC* volatile ActiveDpc;                                       //0x20
};

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