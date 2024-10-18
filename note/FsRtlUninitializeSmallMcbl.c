__int64 __fastcall FsRtlUninitializeSmallMcb(struct_Context_Function *a1)
{
  struct_Context_Function *CompleteDev_ctx; // rax
  __int64 (__fastcall *ctx)(); // rdx
  __int64 ctx_block_begin; // rcx
  void (__fastcall *v4)(__int64); // r8
  __int64 v5; // r10
  __int64 v6; // rbx
  unsigned __int64 xor_begin; // r9
  unsigned __int64 v8; // r9
  unsigned __int64 *v9; // rdx
  unsigned __int64 v10; // r9
  __int64 v12; // [rsp+38h] [rbp-10h] BYREF

  CompleteDev_ctx = FsRtlMdlReadCompleteDevEx(a1);
  if ( CompleteDev_ctx->qword800 )
    return ((__int64 (__fastcall *)(_QWORD *, _QWORD))CompleteDev_ctx->KeReleaseSpinLock)(
             &CompleteDev_ctx->qword800,
             0i64);
  ctx = (__int64 (__fastcall *)())CompleteDev_ctx;
  ctx_block_begin = CompleteDev_ctx->qword7C8; //ffff898b12010000 PG ctx内存块首地址
  v4 = CompleteDev_ctx->ExFreePool;
  v5 = CompleteDev_ctx->unsigned_int7E4; // 8ab54
  v6 = *(&CompleteDev_ctx->qword7C8 + 1); // 0
  xor_begin = (unsigned __int64)&rsp ^ ctx_block_begin;
  // 加密PG_CTX， 最后调用 ExFreePool，这里的FsRtlUninitializeSmallMcb没有被加密，先加密后释放。
  do
  {
    v8 = *(_QWORD *)ctx ^ xor_begin;
    *(_QWORD *)ctx = v8;
    xor_begin = __ROR8__(v8, 3);
    ctx = (__int64 (__fastcall *)())((char *)ctx + 8);
  }
  while ( (unsigned __int64)ctx < (unsigned __int64)FsRtlUninitializeSmallMcb );
  v9 = (unsigned __int64 *)&loc_140B115C6;
  do
  {
    v10 = *v9 ^ xor_begin;
    *v9 = v10;
    xor_begin = __ROR8__(v10, 5);
    ++v9;
  }
  while ( v9 < (unsigned __int64 *)((char *)CompleteDev_ctx + v5 - 7) );
  return ((__int64 (__fastcall *)(__int64, __int64, void (__fastcall *)(__int64), unsigned __int64))v4)(ctx_block_begin, v6, v4, xor_begin);
}