struct_Context_Function *__fastcall patchguard_entry_140B101A0(__int64 a1, struct_Context_Function *a2)
{
  struct_Context_Function *ctx; // rdi
  _KIDTENTRY64 *qword8E0; // rdx
  __int64 v4; // r8
  unsigned __int64 *p_Alignment; // rax
  int v6; // ecx
  int v7; // esi
  struct_Context_Function *v8; // r9
  unsigned int v9; // r10d
  struct_Context_Function *v10; // rax
  __int64 qword818; // r11
  __int64 v12; // r8
  int v13; // ebx
  __int64 v14; // rax
  __int64 v15; // r8
  _QWORD *v16; // r9
  __int64 v17; // r8
  signed __int64 v18; // rcx
  int v19; // edx
  __int64 v20; // rax
  int v21; // r13d
  __int64 v22; // rax
  unsigned __int64 v23; // rdx
  __int64 Pqword_140C0DF08; // rax
  unsigned int v25; // ecx
  unsigned int *v26; // rax
  int v27; // ecx
  unsigned int v28; // ecx
  struct_Context_Function *qwordA78; // r8
  unsigned int v30; // r9d
  struct_Context_Function *v31; // rbx
  __int64 v32; // r10
  unsigned int v33; // ecx
  unsigned int v34; // ecx
  unsigned int v35; // ecx
  unsigned int v36; // ecx
  unsigned int v37; // ecx
  bool v38; // zf
  __int64 v39; // rax
  int v40; // eax
  unsigned int v41; // ecx
  unsigned int v42; // ecx
  unsigned int v43; // ecx
  _QWORD *v44; // r11
  unsigned int v45; // r14d
  unsigned int v46; // eax
  __int64 v47; // r8
  unsigned __int64 v48; // r15
  _QWORD *v49; // r9
  char *v50; // rax
  unsigned __int64 v51; // rsi
  unsigned int v52; // r10d
  __int64 v53; // rax
  __int64 v54; // rsi
  unsigned __int64 v55; // rcx
  __int64 v56; // r8
  unsigned __int64 v57; // rax
  __int64 v58; // rax
  unsigned __int64 i; // rax
  unsigned int v60; // esi
  int v61; // r12d
  __int64 v62; // rcx
  unsigned __int8 CurrentIrql; // r13
  unsigned __int64 v64; // r14
  unsigned __int64 v65; // r15
  int v66; // eax
  __int64 bug_check_code_qword910; // r13
  __int64 qword918; // rbx
  __int64 qword908; // rsi
  __int64 qword900; // r12
  struct _KPRCB *CurrentPrcb; // rdx
  void **v72; // r14
  __int64 v73; // r15
  unsigned __int64 v74; // r12
  char *v75; // r8
  unsigned int v76; // r9d
  unsigned int *v77; // r10
  unsigned int *j; // rdx
  unsigned __int64 v79; // rcx
  __int64 v80; // rcx
  __int64 v81; // rax
  unsigned __int64 v82; // rax
  __int64 v83; // rsi
  unsigned int *v84; // rcx
  char *v85; // r9
  int v86; // r11d
  unsigned __int64 v87; // rbx
  signed __int64 v88; // r9
  unsigned __int64 sub_1403E00B0; // r8
  unsigned __int64 v90; // rcx
  unsigned __int64 v91; // rcx
  struct_Context_Function *qwordA08; // r9
  unsigned __int64 v93; // rax
  unsigned __int128 v94; // rax
  __int64 v95; // rdx
  char *p_oword9A0; // rdx
  _QWORD *v97; // rcx
  __int64 v98; // r8
  char v99; // al
  unsigned __int64 pg_apc_qword9E0; // rdx
  int dword928; // ecx
  int v103; // ecx
  int v104; // ecx
  int v105; // ecx
  int v106; // ecx
  volatile signed __int32 *PAlpcpPortListLock; // rax
  signed __int32 v108[8]; // [rsp+8h] [rbp-79h] BYREF
  __int64 v109; // [rsp+48h] [rbp-39h]
  unsigned int v110; // [rsp+50h] [rbp-31h] BYREF
  __int64 v111; // [rsp+58h] [rbp-29h]
  unsigned __int64 v112; // [rsp+60h] [rbp-21h]
  __int64 v113; // [rsp+68h] [rbp-19h]
  __int16 v114[8]; // [rsp+70h] [rbp-11h] BYREF
  char v115; // [rsp+80h] [rbp-1h] BYREF
  char v116[16]; // [rsp+88h] [rbp+7h] BYREF
  __int64 v117; // [rsp+98h] [rbp+17h]
  unsigned __int64 v118; // [rsp+A0h] [rbp+1Fh]
  unsigned __int64 v119; // [rsp+A8h] [rbp+27h]
  __int64 v120; // [rsp+B0h] [rbp+2Fh]

  ctx = a2;
  if ( (a2->bug_check_flags_int990 & 0x110000) != 0x110000 )
  {
    qword8E0 = (_KIDTENTRY64 *)a2->qword8E0;
    v4 = 38i64;
    p_Alignment = &qword8E0->Alignment;
    v6 = 304;
    do
    {
      *p_Alignment = 0i64;
      v6 -= 8;
      ++p_Alignment;
      --v4;
    }
    while ( v4 );
    for ( ; v6; --v6 )
    {
      *(_BYTE *)p_Alignment = 0;
      p_Alignment = (unsigned __int64 *)((char *)p_Alignment + 1);
    }
    qword8E0[1] = ctx->kidtentry64848;
    qword8E0[2] = ctx->kidtentry64858;
    qword8E0[18] = ctx->kidtentry64868;
    v114[0] = 303;
    *(_QWORD *)&v114[1] = qword8E0;
    qword8E0[1].OffsetLow = (_WORD)ctx + 2168;
    qword8E0[1].OffsetHigh = (unsigned __int64)&ctx->word878 >> 32;
    qword8E0[1].OffsetMiddle = (unsigned int)((_DWORD)ctx + 2168) >> 16;
    _disable();
    if ( ctx->bug_check_flags_int990 >= 0 )
    {
      __sidt(v116);
      __lidt(v114);
      __writedr(7u, 0i64);
      __lidt(v116);
    }
    else
    {
      __writedr(7u, 0i64);
    }
    _enable();
  }
  ctx->dword828 += 1576;
  v7 = *(_DWORD *)&ctx->CmpAppendDllSection[180];
  v8 = ctx;
  v9 = ctx->unsigned_int814;
  v10 = ctx;
  qword818 = ctx->qword818;
  for ( *(_DWORD *)&ctx->CmpAppendDllSection[180] = 0;
        v10 < (struct_Context_Function *)ctx->gap628;
        v10 = (struct_Context_Function *)((char *)v10 + 64) )
  {
    _mm_prefetchnta(v10);
  }
  v12 = qword818;
  v13 = 12;
  do
  {
    v14 = 8i64;
    do
    {
      v15 = *(_QWORD *)&v8->unsigned_int0 ^ v12;
      v16 = &v8->unsigned_int0 + 2;
      v17 = *v16 ^ __ROL8__(v15, v9);
      v8 = (struct_Context_Function *)(v16 + 1);
      v12 = __ROL8__(v17, v9);
      --v14;
    }
    while ( v14 );
    v18 = __ROL8__(qword818 ^ ((char *)v8 - (char *)ctx), 17) ^ qword818 ^ ((char *)v8 - (char *)ctx);
    v117 = ((unsigned __int64)v18 * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v9 = ((unsigned __int8)(v117 ^ v18) ^ (unsigned __int8)v9) & 0x3F;
    if ( !v9 )
      LOBYTE(v9) = 1;
    --v13;
  }
  while ( v13 );
  v19 = 40;
  v20 = 5i64;
  v21 = 64;
  do
  {
    v12 = __ROL8__(*(_QWORD *)&v8->unsigned_int0 ^ v12, v9);
    v8 = (struct_Context_Function *)((char *)v8 + 8);
    v19 -= 8;
    --v20;
  }
  while ( v20 );
  for ( ; v19; --v19 )
  {
    v22 = LOBYTE(v8->unsigned_int0);
    v8 = (struct_Context_Function *)((char *)v8 + 1);
    v12 = __ROL8__(v22 ^ v12, v9);
  }
  v23 = 0xA3A03F5891C8B4E8ui64;
  *(_DWORD *)&ctx->CmpAppendDllSection[180] = v7;
  if ( *(_QWORD *)ctx->gapA20 != v12 )
  {
    Pqword_140C0DF08 = ctx->Pqword_140C0DF08;
    v25 = ctx->unsigned_int7E4;
    *(_QWORD *)Pqword_140C0DF08 = ctx;
    *(_DWORD *)(Pqword_140C0DF08 + 16) = v25;
    if ( !ctx->dword8F8 )
    {
      *(_QWORD *)(ctx->Pqword_140C0DF08 + 24i64) = *(_QWORD *)ctx->gapA20 ^ v12;
      if ( !ctx->dword8F8 )
      {
        ctx->qword908 = 0i64;
        ctx->qword900 = (char *)ctx - 0x5C5FC0A76E374B18i64;
        ctx->bug_check_code_qword910 = 265i64;
        ctx->qword918 = v12;
        ctx->dword8F8 = 1;
        __ba(ctx, 0i64);
      }
    }
  }
  v109 = 0i64;
  v26 = &v110;
  v27 = 4;
  do
  {
    *(_BYTE *)v26 = 0;
    v26 = (unsigned int *)((char *)v26 + 1);
    --v27;
  }
  while ( v27 );
  v28 = 0;
  LODWORD(v111) = 0;
  if ( ctx->dword7E0 )
  {
    while ( 1 )
    {
      qwordA78 = ctx;
      v30 = 0;
      if ( ctx->qwordA78 )
        qwordA78 = (struct_Context_Function *)ctx->qwordA78;
      v31 = (struct_Context_Function *)((char *)qwordA78 + (unsigned int)qwordA78->dword808);
      if ( (_DWORD)v109 && HIDWORD(v109) <= v28 )
      {
        v30 = HIDWORD(v109);
        v31 = (struct_Context_Function *)((char *)qwordA78 + v110);
      }
      if ( v30 != v28 )
        break;
LABEL_58:
      v44 = (_QWORD *)*((_QWORD *)&v31->unsigned_int0 + 1);
      v45 = ctx->unsigned_int814;
      v46 = (_DWORD)v31 - (_DWORD)qwordA78;
      v47 = *(unsigned int *)v31->CmpAppendDllSection;
      ctx->dword828 += v47;
      v48 = ctx->qword818;
      HIDWORD(v109) = v30;
      v49 = v44;
      v110 = v46;
      LODWORD(v109) = 1;
      v50 = (char *)v44;
      if ( v44 < (_QWORD *)((char *)v44 + v47) )
      {
        do
        {
          _mm_prefetchnta(v50);
          v50 += 64;
        }
        while ( v50 < (char *)v44 + v47 );
      }
      v51 = v48;
      v52 = (unsigned int)v47 >> 7;
      if ( (unsigned int)v47 >> 7 )
      {
        do
        {
          v53 = 8i64;
          do
          {
            v54 = v49[1] ^ __ROL8__(*v49 ^ v51, v45);
            v49 += 2;
            v51 = __ROL8__(v54, v45);
            --v53;
          }
          while ( v53 );
          v55 = __ROL8__(v48 ^ ((char *)v49 - (char *)v44), 17) ^ v48 ^ ((char *)v49 - (char *)v44);
          v23 = (v55 * (unsigned __int128)0x7010008004002001ui64) >> 64;
          v118 = v23;
          v45 = ((unsigned __int8)(v23 ^ v55) ^ (unsigned __int8)v45) & 0x3F;
          if ( !v45 )
            LOBYTE(v45) = 1;
          --v52;
        }
        while ( v52 );
        ctx = a2;
      }
      v56 = v47 & 0x7F;
      if ( (unsigned int)v56 >= 8 )
      {
        v57 = (unsigned __int64)(unsigned int)v56 >> 3;
        do
        {
          v51 = __ROL8__(*v49++ ^ v51, v45);
          v56 = (unsigned int)(v56 - 8);
          --v57;
        }
        while ( v57 );
      }
      if ( (_DWORD)v56 )
      {
        do
        {
          v58 = *(unsigned __int8 *)v49;
          v49 = (_QWORD *)((char *)v49 + 1);
          v51 = __ROL8__(v58 ^ v51, v45);
          v38 = (_DWORD)v56 == 1;
          v56 = (unsigned int)(v56 - 1);
        }
        while ( !v38 );
      }
      for ( i = v51; ; LODWORD(v51) = i ^ v51 )
      {
        i >>= 31;
        if ( !i )
          break;
      }
      v60 = v51 & 0x7FFFFFFF;
      v61 = 0;
      if ( v60 != *(_DWORD *)&v31->CmpAppendDllSection[4] )
      {
        if ( !v31->unsigned_int0 && *(_DWORD *)&v31->CmpAppendDllSection[8] )
          v61 = 1;
        v62 = *(unsigned int *)v31->CmpAppendDllSection;
        v23 = *((_QWORD *)&v31->unsigned_int0 + 1);
        if ( *(_DWORD *)v31->CmpAppendDllSection && (ctx->NestedPageProtectionFlags_dword994 & 0x40) != 0 )
        {
          CurrentIrql = KeGetCurrentIrql();
          __writecr8(2ui64);
          v64 = v23 & 0xFFFFFFFFFFFFF000ui64;
          v113 = (v23 + v62 - 1) | 0xFFF;
          v112 = (v23 & 0xFFFFFFFFFFFFF000ui64) - 1;
          while ( 2 )
          {
            v65 = CurrentIrql;
            while ( 1 )
            {
              v66 = ((__int64 (__fastcall *)(unsigned __int64, _QWORD, __int64, _QWORD *))ctx->VslVerifyPage)(
                      v64,
                      0i64,
                      v56,
                      v49);
              if ( v66 != -1073741267 )
                break;
              if ( v61 )
                goto LABEL_102;
              if ( CurrentIrql > 1u )
                goto LABEL_88;
              v65 = CurrentIrql;
              __writecr8(CurrentIrql);
              KeGetCurrentIrql();
              __writecr8(2ui64);
            }
            if ( v66 < 0 )
            {
LABEL_102:
              __writecr8(v65);
              goto LABEL_103;
            }
LABEL_88:
            v23 = 4096i64;
            v64 += 4096i64;
            v112 += 4096i64;
            if ( v112 != v113 )
              continue;
            break;
          }
          __writecr8(v65);
        }
        else
        {
LABEL_103:
          if ( !ctx->dword8F8 )
          {
            *(_QWORD *)(ctx->Pqword_140C0DF08 + 24i64) = v60 ^ (unsigned __int64)*(unsigned int *)&v31->CmpAppendDllSection[4];
            v80 = *((_QWORD *)&v31->unsigned_int0 + 1);
            if ( !ctx->dword8F8 )
            {
              ctx->qword900 = (char *)ctx - 0x5C5FC0A76E374B18i64;
              ctx->qword908 = (char *)v31 - 0x4C48B4211BBACBEBi64;
              v81 = (int)v31->unsigned_int0;
              ctx->qword918 = v80;
              ctx->bug_check_code_qword910 = v81;
              ctx->dword8F8 = 1;
              __ba(ctx, 0i64);
            }
          }
        }
      }
      v21 = 64;
      v28 = v111 + 1;
      LODWORD(v111) = v28;
      if ( v28 >= ctx->dword7E0 )
        goto LABEL_91;
    }
    v32 = v28 - v30;
    v30 = v28;
    while ( 1 )
    {
      v33 = v31->unsigned_int0;
      if ( (int)v31->unsigned_int0 > 28 )
      {
        v41 = v33 - 30;
        if ( !v41 )
        {
          v23 = ((*(_DWORD *)&v31->CmpAppendDllSection[20] != 0 ? *(_DWORD *)&v31->CmpAppendDllSection[20] - 1 : 0)
               / 0xCu
               + 7) & 0xFFFFFFF8;
          v39 = (unsigned int)v23 + 24 * (*(unsigned __int16 *)&v31->CmpAppendDllSection[24] + 2);
          goto LABEL_57;
        }
        v42 = v41 - 3;
        if ( !v42 || (v43 = v42 - 1) == 0 )
        {
          v23 = ((*(_DWORD *)&v31->CmpAppendDllSection[16] & 0xFFF)
               + (unsigned __int64)*(unsigned int *)&v31->CmpAppendDllSection[24]
               + 4095) >> 12;
          v39 = (unsigned int)(20 * v23 + 48);
          goto LABEL_57;
        }
        v38 = v43 == 9;
      }
      else
      {
        if ( v33 == 28 )
        {
          v40 = *(unsigned __int16 *)&v31->CmpAppendDllSection[24];
          goto LABEL_45;
        }
        v34 = v33 - 1;
        if ( !v34 )
          goto LABEL_54;
        v35 = v34 - 6;
        if ( !v35 )
        {
          v39 = (unsigned int)(24 * (*(_DWORD *)&v31->CmpAppendDllSection[8] + 2));
          goto LABEL_57;
        }
        v36 = v35 - 1;
        if ( !v36 )
        {
          v40 = *(unsigned __int16 *)&v31->CmpAppendDllSection[16];
LABEL_45:
          v39 = (v40 + 55) & 0xFFFFFFF8;
          goto LABEL_57;
        }
        v37 = v36 - 2;
        if ( !v37 )
        {
          v39 = (unsigned int)(16 * (*(_DWORD *)&v31->CmpAppendDllSection[12] + 3));
          goto LABEL_57;
        }
        v38 = v37 == 2;
      }
      if ( v38 )
      {
LABEL_54:
        v23 = *(unsigned int *)v31->CmpAppendDllSection / 0xCui64;
        v39 = (unsigned int)(4 * v23 + 48);
        goto LABEL_57;
      }
      v39 = 48i64;
LABEL_57:
      v31 = (struct_Context_Function *)((char *)v31 + v39);
      if ( !--v32 )
        goto LABEL_58;
    }
  }
LABEL_91:
  if ( ctx->dword8F8 )
  {
    bug_check_code_qword910 = ctx->bug_check_code_qword910;
    qword918 = ctx->qword918;
    qword908 = ctx->qword908;
    qword900 = ctx->qword900;
    v113 = qword918;
    v112 = qword908;
    v111 = qword900;
    if ( KeGetCurrentIrql() < 2u )
    {
      KeGetCurrentIrql();
      __writecr8(2ui64);
    }
    CurrentPrcb = KeGetCurrentPrcb();
    v72 = *(void ***)((char *)&CurrentPrcb->MxCsr + *(_QWORD *)&ctx->gap628[24]);
    v73 = *(_QWORD *)((char *)&CurrentPrcb->MxCsr + ctx->qword650);
    if ( !*((_BYTE *)&CurrentPrcb->MxCsr + *(_QWORD *)&ctx->gap628[32])
      || &v115 > (char *)v72
      || &v115 < (char *)v72 - 24576 )
    {
      v72 = *(void ***)(v73 + *(_QWORD *)&ctx->gap678[8]);
    }
    if ( (ctx->bug_check_flags_int990 & 0x8000000) == 0 )
    {
      v74 = __readcr0();
      __writecr0(v74 & 0xFFFFFFFFFFFEFFFFui64);
      v75 = (char *)(&ctx[1].unsigned_int0 + 2);
      v76 = 0;
      v77 = &ctx[1].unsigned_int0 + 4 * ctx[1].unsigned_int0 + 2;
      for ( j = v77; v76 < *(&ctx[1].unsigned_int0 + 1); ++v76 )
      {
        **(_QWORD **)j = *((_QWORD *)j + 1);
        v79 = __readcr4();
        if ( (v79 & 0x20080) != 0 )
        {
          __writecr4(v79 ^ 0x80);
          __writecr4(v79);
        }
        else
        {
          v82 = __readcr3();
          __writecr3(v82);
        }
        j += 4;
      }
      if ( v75 < (char *)v77 )
      {
        do
        {
          v83 = *((unsigned int *)v75 + 2);
          v84 = j;
          v85 = *(char **)v75;
          v86 = v83;
          if ( (unsigned int)v83 >= 8 )
          {
            v87 = (unsigned __int64)(unsigned int)v83 >> 3;
            do
            {
              v86 -= 8;
              *(_QWORD *)v85 = *(_QWORD *)v84;
              v84 += 2;
              v85 += 8;
              --v87;
            }
            while ( v87 );
          }
          if ( v86 )
          {
            v88 = v85 - (char *)v84;
            do
            {
              *((_BYTE *)v84 + v88) = *(_BYTE *)v84;
              v84 = (unsigned int *)((char *)v84 + 1);
              --v86;
            }
            while ( v86 );
          }
          j = (unsigned int *)((char *)j + v83);
          v75 += 16;
        }
        while ( v75 < (char *)v77 );
        qword918 = v113;
        qword908 = v112;
      }
      *(_BYTE *)ctx->DbgPrint = -61;
      __writecr0(v74);
      qword900 = v111;
    }
    dword928 = ctx->dword928;
    if ( dword928 )
    {
      if ( KeGetCurrentIrql() < 2u )
      {
        KeGetCurrentIrql();
        __writecr8(2ui64);
        dword928 = ctx->dword928;
      }
      if ( dword928 )
      {
        v103 = dword928 - 1;
        if ( v103 )
        {
          v104 = v103 - 1;
          if ( v104 )
          {
            v105 = v104 - 1;
            if ( v105 )
            {
              v106 = v105 - 1;
              if ( v106 )
              {
                if ( v106 == 1 )
                  _interlockedbittestandset(
                    *(volatile signed __int32 **)((char *)&KeGetCurrentPrcb()->MxCsr + ctx->qword650),
                    ((unsigned int)ctx->bug_check_flags_int990 >> 10) & 0x1F);
                else
                  _InterlockedOr64((volatile signed __int64 *)(ctx->q_0xFFFFF78000000000 + 832i64), 1ui64);
              }
              else
              {
                _interlockedbittestandset(
                  *(volatile signed __int32 **)(ctx->qword6B0
                                              + *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + ctx->qword650)
                                              + ctx->qword690),
                  ((unsigned int)ctx->bug_check_flags_int990 >> 10) & 0x1F);
              }
              goto LABEL_151;
            }
            PAlpcpPortListLock = (volatile signed __int32 *)ctx->PAlpcpPortListLock;
          }
          else
          {
            PAlpcpPortListLock = (volatile signed __int32 *)ctx->PExpUuidLock;
          }
        }
        else
        {
          PAlpcpPortListLock = (volatile signed __int32 *)ctx->PPspActiveProcessLock;
        }
        _interlockedbittestandset64(PAlpcpPortListLock, 0i64);
      }
    }
LABEL_151:
    *(_QWORD *)(v73 + *(_QWORD *)ctx->gap698) = 0i64;
    *(_QWORD *)(v73 + *(_QWORD *)&ctx->gap698[16]) = 0i64;
    SdbpCheckDll(
      265i64,
      qword900,
      qword908,
      qword918,
      bug_check_code_qword910,
      (__int64 (__fastcall *)(__int64))ctx->KeBugCheckEx,
      v72);
    JUMPOUT(0x140B10CA4i64);
  }
  sub_1403E00B0 = (unsigned __int64)ctx + (unsigned int)ctx->dword7F0;
  if ( (ctx->bug_check_flags_int990 & 0x10000000) != 0 )
  {
    v90 = __rdtsc();
    v91 = __ROR8__(v90, 3) ^ v90;
    v23 = (v91 * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v119 = v23;
    sub_1403E00B0 = (unsigned __int64)KiMachineCheckControl + 16 * (((unsigned __int8)v91 ^ (unsigned __int8)v23) & 0xF);
  }
  qwordA08 = (struct_Context_Function *)ctx->qwordA08;
  if ( qwordA08 )
  {
    v93 = __rdtsc();
    v94 = (__ROR8__(v93, 3) ^ v93) * (unsigned __int128)0x7010008004002001ui64;
    v120 = *((_QWORD *)&v94 + 1);
    *((_QWORD *)&v94 + 1) ^= v94;
    *(_QWORD *)qwordA08->CmpAppendDllSection = *((_QWORD *)&v94 + 1);
    *(_QWORD *)&v94 = sub_1403E00B0 ^ *((_QWORD *)&v94 + 1);
    v23 = (unsigned __int64)ctx ^ *((_QWORD *)&v94 + 1);
    *(_QWORD *)&qwordA08->CmpAppendDllSection[8] = v94;
    *((_QWORD *)&qwordA08->unsigned_int0 + 1) = v23;
    _InterlockedOr(v108, 0);
    sub_1403E00B0 = ctx->sub_1403E00B0;
  }
  else
  {
    qwordA08 = ctx;
  }
  *(_QWORD *)&ctx->pg_WorkItem_gap798[16] = sub_1403E00B0;
  *(_QWORD *)&ctx->pg_WorkItem_gap798[24] = qwordA08;
  *(_QWORD *)ctx->pg_WorkItem_gap798 = 0i64;
  _disable();
  _enable();
  LOBYTE(v95) = ((__int64 (__fastcall *)(_QWORD *, unsigned __int64))ctx->KeAcquireSpinLockRaiseToDpc)(
                  &ctx->qword800,
                  v23);
  ((void (__fastcall *)(_QWORD *, __int64))ctx->KeReleaseSpinLock)(&ctx->qword800, v95);
  switch ( ctx->dword838 )
  {
    case 3:
      _disable();
      ctx->apc_thread_qword998 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + ctx->qword650);
      _enable();
      break;
    case 4:
      pg_apc_qword9E0 = ctx->pg_apc_qword9E0;
      *(_QWORD *)(*(_QWORD *)(pg_apc_qword9E0 + 56) ^ *(_QWORD *)(pg_apc_qword9E0 + 64)) = pg_apc_qword9E0 ^ *(_QWORD *)(pg_apc_qword9E0 + 72) ^ *(_QWORD *)(pg_apc_qword9E0 + 64);
      *(_QWORD *)(pg_apc_qword9E0 + 72) = 0i64;
      *(_QWORD *)(pg_apc_qword9E0 + 56) = 0i64;
      break;
    case 5:
      p_oword9A0 = (char *)&ctx->oword9A0;
      v97 = (_QWORD *)(ctx->apc_thread_qword998 + 8i64);
      v98 = 8i64;
      do
      {
        v21 -= 8;
        *v97 = *(_QWORD *)p_oword9A0;
        p_oword9A0 += 8;
        ++v97;
        --v98;
      }
      while ( v98 );
      for ( ; v21; --v21 )
      {
        v99 = *p_oword9A0++;
        *(_BYTE *)v97 = v99;
        v97 = (_QWORD *)((char *)v97 + 1);
      }
      break;
  }
  _InterlockedOr(v108, 0);
  return ctx;
}