#pragma once
#include <ntddk.h>

NTSTATUS SetInlineHook(PVOID targetFunction, PVOID detourFucntion, PVOID* originalFucntion);
NTSTATUS RemoveInlineHook(PVOID targetFunction, PVOID originalFucntion);
