__int64 __fastcall FsRtlUninitializeSmallMcb(struct_Context_Function *a1)
{
  struct_Context_Function *CompleteDev_ctx; // rax
  __int64 (__fastcall *v2)(); // rdx
  __int64 v3; // rcx
  void (__fastcall *v4)(__int64); // r8
  __int64 v5; // r10
  __int64 v6; // rbx
  unsigned __int64 v7; // r9
  unsigned __int64 v8; // r9
  unsigned __int64 *v9; // rdx
  unsigned __int64 v10; // r9
  __int64 v12; // [rsp+38h] [rbp-10h] BYREF

  CompleteDev_ctx = FsRtlMdlReadCompleteDevEx(a1);
  if ( CompleteDev_ctx->qword800 )
    return ((__int64 (__fastcall *)(_QWORD *, _QWORD))CompleteDev_ctx->KeReleaseSpinLock)(
             &CompleteDev_ctx->qword800,
             0i64);
  v2 = (__int64 (__fastcall *)())CompleteDev_ctx;
  v3 = CompleteDev_ctx->qword7C8;
  v4 = CompleteDev_ctx->ExFreePool;
  v5 = CompleteDev_ctx->unsigned_int7E4;
  v6 = *(&CompleteDev_ctx->qword7C8 + 1);
  v7 = (unsigned __int64)&v12 ^ v3;
  do
  {
    v8 = *(_QWORD *)v2 ^ v7;
    *(_QWORD *)v2 = v8;
    v7 = __ROR8__(v8, 3);
    v2 = (__int64 (__fastcall *)())((char *)v2 + 8);
  }
  while ( (unsigned __int64)v2 < (unsigned __int64)FsRtlUninitializeSmallMcb );
  v9 = (unsigned __int64 *)&loc_140B115C6;
  do
  {
    v10 = *v9 ^ v7;
    *v9 = v10;
    v7 = __ROR8__(v10, 5);
    ++v9;
  }
  while ( v9 < (unsigned __int64 *)((char *)CompleteDev_ctx + v5 - 7) );
  return ((__int64 (__fastcall *)(__int64, __int64, void (__fastcall *)(__int64), unsigned __int64))v4)(v3, v6, v4, v7);
}