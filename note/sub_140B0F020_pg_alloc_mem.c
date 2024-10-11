struct_Context_Function *__fastcall sub_140B0F020_pg_alloc_mem(struct_Context_Function *a1, unsigned int a2, int a3)
{
  struct_Context_Function *v4; // rdi
  struct_Context_Function *v5; // rbx
  unsigned int v6; // r10d
  int v7; // r12d
  unsigned __int64 v8; // rax
  __int64 v9; // rcx
  int v10; // r15d
  unsigned __int64 v11; // rax
  unsigned __int128 v12; // rax
  unsigned __int64 v13; // rax
  __int64 v14; // rcx
  _QWORD *v15; // r12
  __int64 v16; // r12
  _QWORD *v17; // r8
  int v18; // r11d
  unsigned __int64 v19; // r9
  unsigned __int64 v20; // rax
  unsigned __int128 v21; // rax
  unsigned __int64 v22; // rax
  unsigned __int128 v23; // rax
  unsigned __int64 v24; // rdx
  unsigned int v25; // r11d
  unsigned int v26; // r15d
  _QWORD *v27; // r8
  unsigned __int64 v28; // r11
  unsigned __int64 v29; // rax
  unsigned __int128 v30; // rax
  unsigned __int64 v31; // rax
  unsigned __int128 v32; // rax
  unsigned __int64 v33; // rdx
  __int64 v34; // rcx
  unsigned int v35; // edx
  char *v36; // r8
  unsigned __int64 v37; // r15
  signed __int64 v38; // r8
  int v39; // eax
  unsigned __int64 v41; // rax
  __int64 v42; // rcx
  int v43; // r9d
  unsigned __int64 v44; // rax
  unsigned __int128 v45; // rax
  __int64 v46; // rcx
  __int64 v47; // r8
  __int64 v48; // rcx
  int v49; // r12d
  unsigned __int128 v50; // rax
  __int64 v51; // rax
  _QWORD *v52; // r9
  int v53; // r10d
  unsigned __int64 v54; // r15
  unsigned __int64 v55; // rax
  unsigned __int128 v56; // rax
  unsigned __int64 v57; // rax
  unsigned __int128 v58; // rax
  unsigned __int64 v59; // rdx
  unsigned int v60; // r12d
  _QWORD *v61; // r9
  unsigned __int64 v62; // r10
  unsigned __int64 v63; // rax
  unsigned __int128 v64; // rax
  unsigned __int64 v65; // rax
  unsigned __int128 v66; // rax
  unsigned __int64 v67; // rdx
  __int64 *v68; // r12
  int v69; // ecx
  _QWORD *v70; // rax
  __int64 v71; // rdx
  int v72; // edx
  int bug_check_flags_int990; // eax
  __int64 v74; // rax
  __int64 v75; // rax
  unsigned int v76; // r11d
  _QWORD *v77; // r8
  int v78; // r9d
  unsigned __int64 v79; // r11
  unsigned __int64 v80; // rax
  unsigned __int128 v81; // rax
  unsigned __int64 v82; // rax
  unsigned __int128 v83; // rax
  unsigned __int64 v84; // rdx
  __int64 v85; // rax
  unsigned int v86; // r9d
  unsigned int v87; // r11d
  _QWORD *v88; // r8
  unsigned __int64 v89; // r11
  unsigned __int64 v90; // rax
  unsigned __int128 v91; // rax
  unsigned __int64 v92; // rax
  unsigned __int128 v93; // rax
  unsigned __int64 v94; // rdx
  struct_Context_Function *v95; // rcx
  unsigned int v96; // edx
  char *v97; // r8
  unsigned __int64 v98; // r9
  signed __int64 v99; // r8
  int v100; // eax
  unsigned __int64 v101; // [rsp+40h] [rbp-59h]
  __int64 v102; // [rsp+40h] [rbp-59h]
  __int64 v103; // [rsp+40h] [rbp-59h]
  __int64 v104; // [rsp+40h] [rbp-59h]
  unsigned __int64 v105; // [rsp+48h] [rbp-51h]
  __int64 v106; // [rsp+48h] [rbp-51h]
  unsigned __int64 v107; // [rsp+50h] [rbp-49h]
  __int64 v108; // [rsp+50h] [rbp-49h]
  __int64 v109; // [rsp+50h] [rbp-49h]
  unsigned int v112; // [rsp+110h] [rbp+77h]
  unsigned int v113; // [rsp+118h] [rbp+7Fh]
  __int64 v114; // [rsp+118h] [rbp+7Fh]
  unsigned int v115; // [rsp+118h] [rbp+7Fh]

  v4 = a1;
  if ( a3 != 3 )
  {
    v5 = 0i64;
    v6 = 0;
    v7 = a1->bug_check_flags_int990 & 0x10000000;
    if ( !v7 )
      v6 = a1->unsigned_int924;
    v113 = a1->unsigned_int810;
    v8 = __rdtsc();
    v9 = __ROR8__(v8, 3);
    v10 = ((unsigned __int16)(((v9 ^ v8) * (unsigned __int128)0x7010008004002001ui64) >> 64) ^ (unsigned __int16)(8193 * (v9 ^ v8))) & 0x7FF;
    v11 = __rdtsc();
    v12 = (__ROR8__(v11, 3) ^ v11) * (unsigned __int128)0x7010008004002001ui64;
    v101 = (*((_QWORD *)&v12 + 1) ^ (unsigned __int64)v12) % (unsigned int)(v10 + 1);
    if ( v6 )
    {
      v13 = __rdtsc();
      v14 = __ROR8__(v13, 3);
      v10 += ((((unsigned int)(((v14 ^ v13) * (unsigned __int128)0x7010008004002001ui64) >> 64) ^ (67117057
                                                                                                 * ((unsigned int)v14 ^ (unsigned int)v13))) & 1) << 12)
           + 4096;
      v114 = v10 + a2;
      v15 = (_QWORD *)((__int64 (__fastcall *)(__int64, __int64))v4->MmAllocateIndependentPages)(
                        v114 + 8,
                        0xFFFFFFFFi64);
      if ( !v15 )
        goto LABEL_11;
      if ( !((unsigned __int8 (__fastcall *)(_QWORD *, _QWORD, __int64))v4->MmSetPageProtection)(
              v15,
              ((_DWORD)v114 + 4095) & 0xFFFFF000,
              64i64) )
      {
        ((void (__fastcall *)(_QWORD *, __int64))v4->MmFreeIndependentPages)(v15, v114);
        goto LABEL_11;
      }
      *v15 = v114 + 8;
      v16 = (__int64)(v15 + 1);
    }
    else
    {
      v16 = v4->ExAllocatePool2((-(__int64)(v7 != 0) & 0xFFFFFFFFFFFFFFC0ui64) + 130, v10 + a2, v113);
    }
    if ( v16 )
    {
      v17 = (_QWORD *)v16;
      v18 = v101;
      if ( (unsigned int)v101 >= 8 )
      {
        v19 = (unsigned __int64)(unsigned int)v101 >> 3;
        do
        {
          v20 = __rdtsc();
          v18 -= 8;
          v21 = (__ROR8__(v20, 3) ^ v20) * (unsigned __int128)0x7010008004002001ui64;
          *v17++ = v21 ^ *((_QWORD *)&v21 + 1);
          --v19;
        }
        while ( v19 );
      }
      if ( v18 )
      {
        v22 = __rdtsc();
        v23 = (__ROR8__(v22, 3) ^ v22) * (unsigned __int128)0x7010008004002001ui64;
        v24 = v23 ^ *((_QWORD *)&v23 + 1);
        do
        {
          *(_BYTE *)v17 = v24;
          v17 = (_QWORD *)((char *)v17 + 1);
          v24 >>= 8;
          --v18;
        }
        while ( v18 );
      }
      v25 = a2;
      v26 = v10 - v101;
      v27 = (_QWORD *)((unsigned int)v101 + v16 + a2);
      if ( v26 >= 8 )
      {
        v28 = (unsigned __int64)v26 >> 3;
        do
        {
          v29 = __rdtsc();
          v26 -= 8;
          v30 = (__ROR8__(v29, 3) ^ v29) * (unsigned __int128)0x7010008004002001ui64;
          *v27++ = v30 ^ *((_QWORD *)&v30 + 1);
          --v28;
        }
        while ( v28 );
        v25 = a2;
      }
      if ( v26 )
      {
        v31 = __rdtsc();
        v32 = (__ROR8__(v31, 3) ^ v31) * (unsigned __int128)0x7010008004002001ui64;
        v33 = v32 ^ *((_QWORD *)&v32 + 1);
        do
        {
          *(_BYTE *)v27 = v33;
          v27 = (_QWORD *)((char *)v27 + 1);
          v33 >>= 8;
          --v26;
        }
        while ( v26 );
      }
      v34 = v16 + (unsigned int)v101;
      if ( v34 )
      {
        v35 = v4->unsigned_int7E4;
        v36 = (char *)(v16 + (unsigned int)v101);
        if ( v35 >= 8 )
        {
          v37 = (unsigned __int64)v35 >> 3;
          do
          {
            v35 -= 8;
            *(_QWORD *)v36 = *(_QWORD *)&v4->unsigned_int0;
            v4 = (struct_Context_Function *)((char *)v4 + 8);
            v36 += 8;
            --v37;
          }
          while ( v37 );
        }
        if ( v35 )
        {
          v38 = v36 - (char *)v4;
          do
          {
            *((_BYTE *)&v4->unsigned_int0 + v38) = v4->unsigned_int0;
            v4 = (struct_Context_Function *)((char *)v4 + 1);
            --v35;
          }
          while ( v35 );
        }
        *(_DWORD *)(v34 + 2340) = a3;
        v39 = *(_DWORD *)(v34 + 2448);
        *(_DWORD *)(v34 + 2020) = v25;
        *(_QWORD *)(v34 + 1992) = v16;
        if ( (v39 & 0x10000000) == 0 )
          *(_DWORD *)(v34 + 2448) = v39 | 0x20000000;
        return (struct_Context_Function *)(v16 + (unsigned int)v101);
      }
      return v5;
    }
LABEL_11:
    ++v4->dwordA18;
    return v5;
  }
  v41 = __rdtsc();
  v42 = __ROR8__(v41, 3);
  v43 = ((unsigned __int16)(((v42 ^ v41) * (unsigned __int128)0x7010008004002001ui64) >> 64) ^ (unsigned __int16)(8193 * (v42 ^ v41))) & 0x7FF;
  v44 = __rdtsc();
  v45 = (__ROR8__(v44, 3) ^ v44) * (unsigned __int128)0x7010008004002001ui64;
  v105 = (*((_QWORD *)&v45 + 1) ^ (unsigned __int64)v45) % (unsigned int)(v43 + 1);
  *(_QWORD *)&v45 = __rdtsc();
  v46 = __ROR8__(v45, 3);
  v47 = v4->unsigned_int810;
  v115 = v43
       + ((((unsigned int)(((v46 ^ (unsigned __int64)v45) * (unsigned __int128)0x7010008004002001ui64) >> 64) ^ (67117057 * ((unsigned int)v46 ^ (unsigned int)v45))) & 1) << 12)
       + 4096;
  *(_QWORD *)&v45 = __rdtsc();
  v48 = __ROR8__(v45, 3);
  v49 = ((unsigned __int16)(((v48 ^ (unsigned __int64)v45) * (unsigned __int128)0x7010008004002001ui64) >> 64) ^ (unsigned __int16)(8193 * (v48 ^ v45))) & 0x7FF;
  *(_QWORD *)&v45 = __rdtsc();
  v50 = (__ROR8__(v45, 3) ^ (unsigned __int64)v45) * (unsigned __int128)0x7010008004002001ui64;
  v107 = (*((_QWORD *)&v50 + 1) ^ (unsigned __int64)v50) % (unsigned int)(v49 + 1);
  v51 = v4->ExAllocatePool2(66i64, (unsigned int)(v49 + 32), v47);
  v102 = v51;
  if ( !v51 )
  {
    ++v4->dwordA18;
LABEL_85:
    ++v4->dwordA18;
    return 0i64;
  }
  v52 = (_QWORD *)v51;
  v53 = v107;
  if ( (unsigned int)v107 >= 8 )
  {
    v54 = (unsigned __int64)(unsigned int)v107 >> 3;
    do
    {
      v55 = __rdtsc();
      v53 -= 8;
      v56 = (__ROR8__(v55, 3) ^ v55) * (unsigned __int128)0x7010008004002001ui64;
      *v52++ = v56 ^ *((_QWORD *)&v56 + 1);
      --v54;
    }
    while ( v54 );
  }
  if ( v53 )
  {
    v57 = __rdtsc();
    v58 = (__ROR8__(v57, 3) ^ v57) * (unsigned __int128)0x7010008004002001ui64;
    v59 = v58 ^ *((_QWORD *)&v58 + 1);
    do
    {
      *(_BYTE *)v52 = v59;
      v52 = (_QWORD *)((char *)v52 + 1);
      v59 >>= 8;
      --v53;
    }
    while ( v53 );
  }
  v60 = v49 - v107;
  v61 = (_QWORD *)((unsigned int)v107 + v102 + 32);
  v108 = (unsigned int)v107 + v102;
  if ( v60 >= 8 )
  {
    v62 = (unsigned __int64)v60 >> 3;
    do
    {
      v63 = __rdtsc();
      v60 -= 8;
      v64 = (__ROR8__(v63, 3) ^ v63) * (unsigned __int128)0x7010008004002001ui64;
      *v61++ = v64 ^ *((_QWORD *)&v64 + 1);
      --v62;
    }
    while ( v62 );
  }
  if ( v60 )
  {
    v65 = __rdtsc();
    v66 = (__ROR8__(v65, 3) ^ v65) * (unsigned __int128)0x7010008004002001ui64;
    v67 = v66 ^ *((_QWORD *)&v66 + 1);
    do
    {
      *(_BYTE *)v61 = v67;
      v61 = (_QWORD *)((char *)v61 + 1);
      v67 >>= 8;
      --v60;
    }
    while ( v60 );
  }
  v68 = (__int64 *)v108;
  if ( !v108 )
    goto LABEL_85;
  v69 = 32;
  v70 = (_QWORD *)v108;
  v71 = 4i64;
  do
  {
    *v70 = 0i64;
    v69 -= 8;
    ++v70;
    --v71;
  }
  while ( v71 );
  for ( ; v69; --v69 )
  {
    *(_BYTE *)v70 = 0;
    v70 = (_QWORD *)((char *)v70 + 1);
  }
  v112 = v4->unsigned_int810;
  v72 = 5;
  *(_DWORD *)(v108 + 16) = v112;
  *(_QWORD *)(v108 + 24) = v102;
  bug_check_flags_int990 = v4->bug_check_flags_int990;
  if ( (bug_check_flags_int990 & 0x1000000) != 0 )
    v72 = 21;
  else
    v4->bug_check_flags_int990 = bug_check_flags_int990 | 0x1000000;
  v109 = a2 + v115;
  v74 = ((__int64 (__fastcall *)(_QWORD, __int64, _QWORD, __int64, int, int))v4->MmAllocatePagesForMdlEx)(
          0i64,
          -1i64,
          0i64,
          v109,
          1,
          v72);
  v103 = v74;
  if ( !v74
    || (*v68 = v74, (v75 = ((__int64 (__fastcall *)(__int64, _QWORD))v4->MmAllocateMappingAddress)(v109, v112)) == 0)
    || (v68[1] = v75,
        v104 = ((__int64 (__fastcall *)(__int64, _QWORD, __int64, __int64))v4->MmMapLockedPagesWithReservedMapping)(
                 v75,
                 v112,
                 v103,
                 1i64),
        !((unsigned __int8 (__fastcall *)(__int64, _QWORD, __int64))v4->MmSetPageProtection)(
           v104,
           ((_DWORD)v109 + 4095) & 0xFFFFF000,
           64i64)) )
  {
    v4->sub_1403ED540((__int64)v68);
    goto LABEL_85;
  }
  v76 = v105;
  v77 = (_QWORD *)v104;
  v78 = v105;
  if ( (unsigned int)v105 >= 8 )
  {
    v79 = (unsigned __int64)(unsigned int)v105 >> 3;
    do
    {
      v80 = __rdtsc();
      v78 -= 8;
      v81 = (__ROR8__(v80, 3) ^ v80) * (unsigned __int128)0x7010008004002001ui64;
      *v77++ = v81 ^ *((_QWORD *)&v81 + 1);
      --v79;
    }
    while ( v79 );
    v76 = v105;
  }
  if ( v78 )
  {
    v82 = __rdtsc();
    v83 = (__ROR8__(v82, 3) ^ v82) * (unsigned __int128)0x7010008004002001ui64;
    v84 = v83 ^ *((_QWORD *)&v83 + 1);
    do
    {
      *(_BYTE *)v77 = v84;
      v77 = (_QWORD *)((char *)v77 + 1);
      v84 >>= 8;
      --v78;
    }
    while ( v78 );
  }
  v85 = v76;
  v86 = v115 - v76;
  v87 = a2;
  v106 = v85;
  v88 = (_QWORD *)(v104 + v85 + a2);
  if ( v86 >= 8 )
  {
    v89 = (unsigned __int64)v86 >> 3;
    do
    {
      v90 = __rdtsc();
      v86 -= 8;
      v91 = (__ROR8__(v90, 3) ^ v90) * (unsigned __int128)0x7010008004002001ui64;
      *v88++ = v91 ^ *((_QWORD *)&v91 + 1);
      --v89;
    }
    while ( v89 );
    v87 = a2;
  }
  if ( v86 )
  {
    v92 = __rdtsc();
    v93 = (__ROR8__(v92, 3) ^ v92) * (unsigned __int128)0x7010008004002001ui64;
    v94 = v93 ^ *((_QWORD *)&v93 + 1);
    do
    {
      *(_BYTE *)v88 = v94;
      v88 = (_QWORD *)((char *)v88 + 1);
      v94 >>= 8;
      --v86;
    }
    while ( v86 );
  }
  v95 = (struct_Context_Function *)(v104 + v106);
  if ( v104 + v106 )
  {
    v96 = v4->unsigned_int7E4;
    v97 = (char *)(v104 + v106);
    if ( v96 >= 8 )
    {
      v98 = (unsigned __int64)v96 >> 3;
      do
      {
        v96 -= 8;
        *(_QWORD *)v97 = *(_QWORD *)&v4->unsigned_int0;
        v4 = (struct_Context_Function *)((char *)v4 + 8);
        v97 += 8;
        --v98;
      }
      while ( v98 );
    }
    if ( v96 )
    {
      v99 = v97 - (char *)v4;
      do
      {
        *((_BYTE *)&v4->unsigned_int0 + v99) = v4->unsigned_int0;
        v4 = (struct_Context_Function *)((char *)v4 + 1);
        --v96;
      }
      while ( v96 );
    }
    v100 = v95->bug_check_flags_int990;
    v95->unsigned_int7E4 = v87;
    v95->qword7C8 = v68;
    v95->unsigned_int924 = 3;
    if ( (v100 & 0x10000000) == 0 )
      v95->bug_check_flags_int990 = v100 | 0x20000000;
    return v95;
  }
  return 0i64;
}