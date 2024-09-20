char __fastcall patchguard_startup_140B17730(unsigned int a1, unsigned int a2, unsigned int a3, __int64 a4, int a5)
{

  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v3881 = 5i64;
  v6 = 41;
  if ( a4 )
  {
    if ( a2 > 5 || !_bittest(&v6, a2) )
      a2 = 0;
    v7 = a5 | 4;
  }
  else
  {
    if ( ((a2 - 3) & 0xFFFFFFFD) == 0 )
      a2 = 0;
    v7 = a5;
  }
  LODWORD(v3836) = v7;
  if ( a2 != 7 )
  {
    if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, __int64))KiAreCodePatchesAllowed)(0i64, 41i64) )
    {
      if ( (int)KiSwInterruptPresent() >= 0 )
      {
        if ( (unsigned int)sub_140B32828() )
        {
          LoadOptions = (const char *)KiGetLoadOptions();
          if ( !strstr(LoadOptions, "DISABLE_INTEGRITY_CHECKS") && !strstr(LoadOptions, "TESTSIGNING") )
            return 1;
        }
      }
    }
  }
  v10 = __29;
  v1153 = _bittest(&v10, a2);
  v11 = 0;
  if ( v1153 )
    a2 = 0;
  v4344 = a2;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  if ( KiInitData != 12 )
  {
    v3837[1] = 317;
    KeBugCheckEx(__ROR4__(317, 160), 2ui64, 0i64, KiInitData, 0xCui64);
  }
  v12 = &_ts_87;
  v13 = &_ps_0;
  if ( &_ts_87 == &_ts_z )
  {
    if ( &_ps_0 == &_ps_z )
      goto LABEL_30;
  }
  else
  {
    do
      v11 += *v12++;
    while ( v12 != &_ts_z );
  }
  v14 = 0;
  do
    v14 += *v13++;
  while ( v13 != &_ps_z );
  if ( v11 != v14 )
  {
    v3837[2] = 317;
    KeBugCheckEx(__ROR4__(317, 160), 0xCui64, v11, v14, 0i64);
  }
LABEL_30:
  if ( !__28 )
  {
    v4147 = 0x140000000ui64;
    v15 = 0i64;
    if ( (int)LdrResFindResource(
                0x40000000u,
                10,
                (int)L"FUNCTIONEXTENTLIST",
                0,
                (__int64)BugCheckParameter2,
                (__int64)&v3883,
                0i64,
                0i64,
                0) >= 0
      && (unsigned __int64)(v3883 - 8) <= 0xFFFFFFF7 )
    {
      v3838 = v3883;
      if ( RtlImageNtHeader(0x140000000ui64) )
      {
        LOBYTE(v16) = 1;
        v17 = RtlImageDirectoryEntryToData(0x140000000ui64, v16, 3i64, &v3839);
        if ( v17 )
        {
          Pool2 = 0i64;
          v19 = -1073741823;
          if ( *(_DWORD *)BugCheckParameter2[0] != 1163416643 )
          {
            if ( *(_DWORD *)BugCheckParameter2[0] != 1163416652 )
              goto LABEL_69;
            goto LABEL_93;
          }
          if ( RtlGetCompressionWorkSpaceSize(4u, CompressBufferWorkSpaceSize, &CompressFragmentWorkSpaceSize) >= 0 )
          {
            v25 = *(unsigned int *)(BugCheckParameter2[0] + 4);
            if ( (unsigned int)v25 < 8 )
            {
              v3857 = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0xEui64, BugCheckParameter2[0], 0x140000000ui64, v3838);
            }
            Pool2 = (void *)ExAllocatePool2(0x42i64, CompressBufferWorkSpaceSize[0], tag);
            if ( !Pool2 )
            {
LABEL_68:
              v15 = 0i64;
LABEL_69:
              a2 = v4344;
              goto LABEL_40;
            }
            v15 = (unsigned int *)ExAllocatePool2(66i64, v25, tag);
            if ( !v15 )
            {
LABEL_124:
              ExFreePool(Pool2);
LABEL_125:
              if ( !v15 || v19 >= 0 )
                goto LABEL_69;
              ExFreePool(v15);
              goto LABEL_68;
            }
            v48 = RtlDecompressBufferEx(
                    4,
                    (int)v15,
                    v25,
                    LODWORD(BugCheckParameter2[0]) + 8,
                    v3838 - 8,
                    (__int64)&v3838,
                    (__int64)Pool2);
            if ( v48 < 0 )
            {
              v3816 = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0xFui64, BugCheckParameter2[0], 0x140000000ui64, v48);
            }
LABEL_93:
            if ( !v15 )
            {
              v60 = (unsigned int *)ExAllocatePool2(66i64, v3838 - 4i64, tag);
              v15 = v60;
              if ( !v60 )
                goto LABEL_123;
              memmove(v60, (const void *)(BugCheckParameter2[0] + 4), v3838 - 4i64);
            }
            v61 = 0;
            for ( i = v17 - 0x40000000; v61 < v3839; i += *(_DWORD *)(v17 + 4 * (v63 >> 2)) )
            {
              v63 = v61;
              v61 += 4;
            }
            if ( i != v15[1] )
            {
              v3770 = v15[1];
              v3827 = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0x10ui64, (ULONG_PTR)v15, 0x140000000ui64, i ^ v3770);
            }
            v64 = *v15;
            if ( (unsigned int)v64 >= 0x1FFFFFFF || 8 * v64 > (unsigned __int64)v3838 )
            {
              BugCheckParameter4 = *v15;
              v3828 = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0x11ui64, (ULONG_PTR)v15, 0x140000000ui64, BugCheckParameter4);
            }
            v4149 = v3838;
            v19 = 0;
LABEL_123:
            if ( !Pool2 )
              goto LABEL_125;
            goto LABEL_124;
          }
          a2 = v4344;
        }
      }
    }
LABEL_40:
    v4148 = (ULONG_PTR)v15;
    v20 = &v4147;
    v21 = 24;
    v22 = &__28;
    v23 = 3i64;
    do
    {
      v21 -= 8;
      *v22++ = *v20++;
      --v23;
    }
    while ( v23 );
    for ( ; v21; --v21 )
    {
      v24 = *(_BYTE *)v20;
      v20 = (__int64 *)((char *)v20 + 1);
      *(_BYTE *)v22 = v24;
      v22 = (__int64 *)((char *)v22 + 1);
    }
    goto LABEL_132;
  }
  v65 = 24;
  v66 = &__28;
  v67 = &v4147;
  v68 = 3i64;
  do
  {
    v65 -= 8;
    *v67++ = *v66++;
    --v68;
  }
  while ( v68 );
  for ( ; v65; --v65 )
  {
    v69 = *(_BYTE *)v66;
    v66 = (__int64 *)((char *)v66 + 1);
    *(_BYTE *)v67 = v69;
    v67 = (__int64 *)((char *)v67 + 1);
  }
LABEL_132:
  if ( !RtlPcToFileHeader(FsRtlUninitializeSmallMcb, v3867)
    || (v70 = RtlImageNtHeader(v3867[0])) == 0
    || (v71 = RtlSectionTableFromVirtualAddress(
                v70,
                v3867[0],
                (unsigned int)FsRtlUninitializeSmallMcb - LODWORD(v3867[0]))) == 0 )
  {
    v3856 = 317;
    KeBugCheckEx(__ROR4__(317, 160), 0x1Cui64, 0i64, 0i64, 0i64);
  }
  v72 = (void *)(v3867[0] + *(unsigned int *)(v71 + 12));
  v73 = *(unsigned int *)(v71 + 8);
  v3784 = (unsigned int)FsRtlUninitializeSmallMcb - (unsigned int)v72;
  Src = v72;
  Size = v73;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v3783 = (unsigned int)sub_140B101A0 - (unsigned int)v72;
  v74 = (unsigned int)RtlLookupFunctionEntryEx - (unsigned int)v72;
  v3785 = v74;
  v3791 = (unsigned int)sub_140B10CB0 - (unsigned int)v72;
  if ( (unsigned int)v74 > 0x7FFFFFFF )
  {
    Size_4 = 317;
    KeBugCheckEx(
      __ROR4__(317, 160),
      9ui64,
      (unsigned int)v74,
      v73,
      (unsigned int)FsRtlUninitializeSmallMcb - (unsigned int)v72);
  }
  v75 = 0;
  if ( (unsigned int)MmStrongCodeGuaranteesEnforced() && (unsigned int)((__int64 (*)(void))sub_140B32784)() )
    v75 = 1;
  if ( a2 == 7 )
  {
    v76 = 1;
    v3789 = 1;
LABEL_143:
    v77 = __rdtsc();
    v78 = (__ROR8__(v77, 3) ^ v77) * (unsigned __int128)0x7010008004002001ui64;
    v3867[2] = *((_QWORD *)&v78 + 1);
    if ( ((unsigned __int64)v78 ^ *((_QWORD *)&v78 + 1)) % 0xA >= 2 )
    {
      LODWORD(v3793) = 0;
    }
    else
    {
      v79 = __rdtsc();
      v80 = (__ROR8__(v79, 3) ^ v79) * (unsigned __int128)0x7010008004002001ui64;
      v3867[3] = *((_QWORD *)&v80 + 1);
      v3793 = (DWORD2(v80) ^ (unsigned int)v80) & 1;
    }
    goto LABEL_149;
  }
  v3789 = v75;
  v76 = v75;
  if ( a2 != 3 )
    goto LABEL_143;
  v81 = __rdtsc();
  v3789 = v75;
  v82 = (__ROR8__(v81, 3) ^ v81) * (unsigned __int128)0x7010008004002001ui64;
  v3867[1] = *((_QWORD *)&v82 + 1);
  if ( ((unsigned __int64)v82 ^ *((_QWORD *)&v82 + 1)) % 0xA >= 5 )
    goto LABEL_143;
  LODWORD(v3793) = 3;
  v3789 = v75;
LABEL_149:
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  if ( v76 )
  {
    LODWORD(v3793) = 0;
    if ( a2 - 3 <= 1 )
      a2 = 0;
    v4344 = a2;
  }
  qword_140C00250[0] = (__int64)off_140C019E8;
  *(_OWORD *)P = 0i64;
  v83 = 0;
  v4167 = 0i64;
  v84 = 0;
  v4165 = 0i64;
  v3796 = 0;
  v3797 = 0;
  do
  {
    v85 = qword_140C00250[v83];
    v86 = RtlLookupFunctionTable(v85, &BugCheckParameter3, v3831);
    v4203 = v86;
    if ( !v86 )
    {
      v94 = v4207;
      v88 = v4204;
      v95 = v3799;
      goto LABEL_173;
    }
    v4208 = 0i64;
    if ( v4147 != BugCheckParameter3 )
    {
      v88 = v4204;
      goto LABEL_171;
    }
    v87 = (_DWORD *)v4148;
    v4209 = 0i64;
    v4210 = v4149;
    v4211 = 0;
    v4208 = v4148;
    v88 = RtlLookupFunctionEntry(v85, &BugCheckParameter3, 0i64);
    v4204 = v88;
    if ( !v88 )
      goto LABEL_166;
    v89 = 0;
    v90 = *v87 - 1;
    if ( v90 < 0 )
      goto LABEL_166;
    while ( 1 )
    {
      v91 = (v90 + v89) >> 1;
      v92 = v88 - BugCheckParameter3 - v87[2 * v91 + 2];
      if ( v92 < 0 )
      {
        if ( !v91 )
          goto LABEL_166;
        v90 = v91 - 1;
        goto LABEL_165;
      }
      if ( v92 <= 0 )
        break;
      v89 = v91 + 1;
LABEL_165:
      if ( v90 < v89 )
        goto LABEL_166;
    }
    v93 = v4209;
    if ( v90 >= v89 )
      v93 = (__int64)&v87[2 * ((v90 + v89) >> 1) + 2];
    v4209 = v93;
LABEL_166:
    v86 = v4203;
LABEL_171:
    v94 = v3868;
    v95 = BugCheckParameter3;
    v4202 = v85;
    v3831[0] /= 0xCu;
    v4207 = v3868;
    v3799 = BugCheckParameter3;
    v4206 = v86 + 12i64 * (unsigned int)v3831[0];
LABEL_173:
    while ( v86 && v86 != v4206 )
    {
      if ( v4208 )
      {
        if ( !v88 )
          break;
        if ( v4209 )
        {
          v96 = *(_DWORD *)(v4209 + 4);
          if ( (v96 & 1) != 0 )
          {
            *v94 = BugCheckParameter3 + (v96 & 0xFFFFFFFE);
            v4209 = 0i64;
          }
          else
          {
            v97 = (unsigned int)(v4211 + v96);
            v98 = (unsigned int)v97;
            v99 = v97 + 4;
            if ( v99 < v98 || v99 > v4210 )
            {
              v3831[11] = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0x12ui64, v4208, BugCheckParameter3, v98);
            }
            v100 = *(_DWORD *)(v4208 + v98);
            v4211 += 4;
            v4209 &= -(__int64)((v100 & 1) != 0);
            if ( (v100 & 1) != 0 )
              v100 &= ~1u;
            *v94 = BugCheckParameter3 + v100;
          }
        }
        else
        {
          *v94 = v88;
          v4204 = 0i64;
        }
      }
      else
      {
        while ( 1 )
        {
          v101 = v86;
          v102 = RtlpConvertFunctionEntry(v86, BugCheckParameter3, v94);
          v103 = RtlpSameFunction(v102, BugCheckParameter3, v4202);
          v86 = v4203 + 12;
          v4203 += 12i64;
          if ( v103 )
            break;
          if ( v86 == v4206 )
            goto LABEL_188;
        }
        *v4207 = v101;
      }
      v111 = *(unsigned int *)v3868[0];
      v112 = *(_DWORD *)(v3868[0] + 4) - v111;
      HIDWORD(v4167) += v112;
      v3800 = v84 + 1;
      v113 = (v95 + v111) & 0xFFFFFFFFFFFFF000ui64;
      v3801 = v95 + v111 + v112;
      do
      {
        v114 = v4168;
        v115 = 4i64;
        v116 = MmPteBase + ((v113 >> 9) & 0x7FFFFFFFF8i64);
        do
        {
          *v114++ = v116;
          v116 = MmPteBase + ((v116 >> 9) & 0x7FFFFFFFF8i64);
          --v115;
        }
        while ( v115 );
        v117 = 0;
        v118 = 3;
        do
        {
          v119 = v118;
          if ( v117 )
          {
            v4168[v118] = 0i64;
          }
          else
          {
            if ( !v118 )
              break;
            if ( *(char *)v4168[v118] < 0 )
              v117 = 1;
          }
          --v118;
        }
        while ( v119 );
        v120 = v3797;
        LODWORD(v121) = 4;
        do
        {
          v121 = (unsigned int)(v121 - 1);
          v122 = v4168[v121];
          if ( !v122 )
            break;
          v123 = 0;
          if ( HIDWORD(P[1]) )
          {
            do
            {
              if ( v122 == *((_QWORD *)P[0] + v123) )
                break;
              ++v123;
            }
            while ( v123 < HIDWORD(P[1]) );
            v120 = v3797;
          }
          if ( v123 == HIDWORD(P[1]) )
          {
            if ( HIDWORD(P[1]) == v120 )
            {
              v120 = 2 * v120 + 64;
              v3797 = v120;
              v135 = (char *)ExAllocatePool2(64i64, 8i64 * v120, tag);
              if ( !v135 )
                goto LABEL_5361;
              v136 = P[0];
              if ( P[0] )
              {
                v137 = v135;
                v138 = 8 * HIDWORD(P[1]);
                if ( (unsigned int)(8 * HIDWORD(P[1])) >= 8 )
                {
                  v139 = (unsigned __int64)v138 >> 3;
                  do
                  {
                    v138 -= 8;
                    *(_QWORD *)v137 = *v136++;
                    v137 += 8;
                    --v139;
                  }
                  while ( v139 );
                }
                if ( v138 )
                {
                  v140 = v137 - (char *)v136;
                  do
                  {
                    *((_BYTE *)v136 + v140) = *(_BYTE *)v136;
                    v136 = (_QWORD *)((char *)v136 + 1);
                    --v138;
                  }
                  while ( v138 );
                }
                ExFreePool(P[0]);
              }
              P[0] = v135;
              LODWORD(P[1]) = v120;
            }
            v141 = HIDWORD(P[1]);
            ++HIDWORD(P[1]);
            HIDWORD(v4167) += 16;
            *((_QWORD *)P[0] + v141) = v122;
          }
        }
        while ( (_DWORD)v121 );
        v113 += 4096i64;
      }
      while ( v113 < v3801 );
      v84 = v3800;
      v94 = v4207;
      v88 = v4204;
      v86 = v4203;
      v95 = v3799;
      LODWORD(v4167) = v3800;
    }
LABEL_188:
    v83 = v3796 + 1;
    v3796 = v83;
  }
  while ( v83 < 0xF );
  HIDWORD(v4167) += 8;
  v3800 = v84 + 1;
  v104 = (unsigned __int64)&off_140C019E8 & 0xFFFFFFFFFFFFF000ui64;
  do
  {
    v105 = v4169;
    v106 = MmPteBase + ((v104 >> 9) & 0x7FFFFFFFF8i64);
    v107 = 4i64;
    do
    {
      *v105++ = v106;
      v106 = MmPteBase + ((v106 >> 9) & 0x7FFFFFFFF8i64);
      --v107;
    }
    while ( v107 );
    v108 = 0;
    v109 = 3;
    do
    {
      v110 = v109;
      if ( v108 )
      {
        v4169[v109] = 0i64;
      }
      else
      {
        if ( !v109 )
          break;
        if ( *(char *)v4169[v109] < 0 )
          v108 = 1;
      }
      --v109;
    }
    while ( v110 );
    v142 = v3800;
    LODWORD(v143) = 4;
    do
    {
      v143 = (unsigned int)(v143 - 1);
      v144 = v4169[v143];
      if ( !v144 )
        break;
      v145 = 0;
      if ( HIDWORD(P[1]) )
      {
        do
        {
          if ( v144 == *((_QWORD *)P[0] + v145) )
            break;
          ++v145;
        }
        while ( v145 < HIDWORD(P[1]) );
        v142 = v3800;
      }
      if ( v145 == HIDWORD(P[1]) )
      {
        if ( HIDWORD(P[1]) == v3797 )
        {
          v146 = 2 * v3797 + 64;
          v3797 = v146;
          v158 = (char *)ExAllocatePool2(64i64, 8i64 * v146, tag);
          if ( !v158 )
          {
LABEL_5361:
            v3831[22] = 317;
            KeBugCheckEx(__ROR4__(317, 160), 0x1Bui64, 0i64, 0i64, 0i64);
          }
          v159 = P[0];
          if ( P[0] )
          {
            v160 = v158;
            v161 = 8 * HIDWORD(P[1]);
            if ( (unsigned int)(8 * HIDWORD(P[1])) >= 8 )
            {
              v162 = (unsigned __int64)v161 >> 3;
              do
              {
                v161 -= 8;
                *(_QWORD *)v160 = *v159++;
                v160 += 8;
                --v162;
              }
              while ( v162 );
            }
            if ( v161 )
            {
              v163 = v160 - (char *)v159;
              do
              {
                *((_BYTE *)v159 + v163) = *(_BYTE *)v159;
                v159 = (_QWORD *)((char *)v159 + 1);
                --v161;
              }
              while ( v161 );
            }
            ExFreePool(P[0]);
          }
          LODWORD(P[1]) = v3797;
          P[0] = v158;
        }
        v164 = HIDWORD(P[1]);
        ++HIDWORD(P[1]);
        HIDWORD(v4167) += 16;
        *((_QWORD *)P[0] + v164) = v144;
      }
    }
    while ( (_DWORD)v143 );
    v104 += 4096i64;
  }
  while ( v104 < (unsigned __int64)&qword_140C019F0 );
  LODWORD(v4167) = v142;
  v165 = 16 * v142 + HIDWORD(v4167) + 8;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v166 = v3789;
  if ( v3789 )
  {
    v165 = 0;
    Size = 0;
    v167 = 0;
  }
  else
  {
    v167 = Size;
  }
  v3800 = v165 + 2720;
  v3797 = v165 + 2720 + v167;
  v168 = __rdtsc();
  v169 = __ROR8__(v168, 3);
  v3872 = ((v169 ^ v168) * (unsigned __int128)0x7010008004002001ui64) >> 64;
  v170 = v3797 + (((67117057 * (v169 ^ v168)) ^ v3872) & 0x7FF) + 0x100000;
  v182 = __rdtsc();
  v183 = __ROR8__(v182, 3);
  v3875 = ((v183 ^ v182) * (unsigned __int128)0x7010008004002001ui64) >> 64;
  v184 = (v3875 ^ (67117057 * (v183 ^ v182))) & 0x7FF;
  v185 = __rdtsc();
  v186 = (__ROR8__(v185, 3) ^ v185) * (unsigned __int128)0x7010008004002001ui64;
  v3876 = *((_QWORD *)&v186 + 1);
  v187 = (*((_QWORD *)&v186 + 1) ^ (unsigned __int64)v186) % (unsigned int)(v184 + 1);
  v188 = (__int64 *)ExAllocatePool2(130i64, (unsigned int)(v184 + v170), tag);
  v3798 = v188;
  v189 = v188;
  if ( !v188 )
    return 0;
  v190 = v187;
  v191 = v188;
  if ( (unsigned int)v187 >= 8 )
  {
    v192 = (unsigned __int64)(unsigned int)v187 >> 3;
    do
    {
      v193 = __rdtsc();
      v190 -= 8;
      v194 = (__ROR8__(v193, 3) ^ v193) * (unsigned __int128)0x7010008004002001ui64;
      v3877 = *((_QWORD *)&v194 + 1);
      *v191++ = v194 ^ *((_QWORD *)&v194 + 1);
      --v192;
    }
    while ( v192 );
  }
  if ( v190 )
  {
    v195 = __rdtsc();
    v196 = (__ROR8__(v195, 3) ^ v195) * (unsigned __int128)0x7010008004002001ui64;
    v3878 = *((_QWORD *)&v196 + 1);
    v197 = v196 ^ *((_QWORD *)&v196 + 1);
    do
    {
      *(_BYTE *)v191 = v197;
      v191 = (__int64 *)((char *)v191 + 1);
      v197 >>= 8;
      --v190;
    }
    while ( v190 );
  }
  v198 = v184 - v187;
  v199 = (unsigned int)v187;
  v200 = (__int64 *)((char *)v189 + v170 + (unsigned int)v187);
  if ( v198 >= 8 )
  {
    v201 = (unsigned __int64)v198 >> 3;
    do
    {
      v202 = __rdtsc();
      v198 -= 8;
      v203 = (__ROR8__(v202, 3) ^ v202) * (unsigned __int128)0x7010008004002001ui64;
      v3879 = *((_QWORD *)&v203 + 1);
      *v200++ = v203 ^ *((_QWORD *)&v203 + 1);
      --v201;
    }
    while ( v201 );
  }
  if ( v198 )
  {
    v204 = __rdtsc();
    v205 = (__ROR8__(v204, 3) ^ v204) * (unsigned __int128)0x7010008004002001ui64;
    v3880 = *((_QWORD *)&v205 + 1);
    v206 = v205 ^ *((_QWORD *)&v205 + 1);
    do
    {
      *(_BYTE *)v200 = v206;
      v200 = (_QWORD *)((char *)v200 + 1);
      v206 >>= 8;
      --v198;
    }
    while ( v198 );
  }
  v207 = (char *)v189 + (unsigned int)v187;
  v3792 = (ULONG_PTR)v189 + v199;
  if ( !(__int64 *)((char *)v189 + v199) )
    return 0;
  v208 = v3797;
  v209 = v3797 + 0x100000;
  v3796 = v3797 + 0x100000;
  memset((char *)v189 + v199, 0, v3797 + 0x100000);
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v210 = 0x2000i64;
  v211 = *((_DWORD *)v207 + 612) & 0xEFFFFFFF;
  v212 = v211 | (v166 != 0 ? 0x10000000 : 0);
  *((_DWORD *)v207 + 612) = v212;
  if ( v211 & 0x10000000 | (v166 != 0 ? 0x10000000 : 0) )
  {
    *((_DWORD *)v207 + 612) = v212 | 0x8000000;
    *((_DWORD *)v207 + 613) |= 0x2000u;
  }
  if ( __30 )
    *((_DWORD *)v207 + 613) |= 0x2000u;
  if ( v166 )
    goto LABEL_499;
  v213 = v207 + 2720;
  qword_140C00250[0] = (__int64)off_140C019E8;
  v4169[4] = (__int64)(v207 + 2720);
  v4171 = 0i64;
  v214 = 0;
  v3789 = 0;
  v215 = 0;
  LODWORD(v3801) = 0;
  *(_OWORD *)v4170 = 0i64;
  LODWORD(v3799) = 0;
  while ( 2 )
  {
    v216 = qword_140C00250[v214];
    v217 = RtlLookupFunctionTable(v216, &v4215, v3832);
    v4213 = v217;
    if ( !v217 )
    {
      v225 = v4217;
      v219 = v4214;
      v226 = v3859;
      goto LABEL_360;
    }
    v4218 = 0i64;
    if ( v4147 != v4215 )
    {
      v219 = v4214;
      goto LABEL_358;
    }
    v218 = (_DWORD *)v4148;
    v4219 = 0i64;
    v4220 = v4149;
    v4221 = 0;
    v4218 = v4148;
    v219 = RtlLookupFunctionEntry(v216, &v4215, 0i64);
    v4214 = v219;
    if ( !v219 )
      goto LABEL_353;
    v220 = 0;
    v221 = *v218 - 1;
    if ( v221 < 0 )
      goto LABEL_353;
    while ( 2 )
    {
      v222 = (v221 + v220) >> 1;
      v223 = v219 - v4215 - v218[2 * v222 + 2];
      if ( v223 < 0 )
      {
        if ( !v222 )
          goto LABEL_353;
        v221 = v222 - 1;
LABEL_352:
        if ( v221 < v220 )
          goto LABEL_353;
        continue;
      }
      break;
    }
    if ( v223 > 0 )
    {
      v220 = v222 + 1;
      goto LABEL_352;
    }
    v224 = v4219;
    if ( v221 >= v220 )
      v224 = (__int64)&v218[2 * ((v221 + v220) >> 1) + 2];
    v4219 = v224;
LABEL_353:
    v217 = v4213;
    v215 = v3801;
LABEL_358:
    v225 = (__int64 *)&v3882;
    v4212 = v216;
    v226 = v4215;
    v4217 = (__int64 *)&v3882;
    v3832[0] /= 0xCu;
    v3859 = v4215;
    v4216 = v217 + 12i64 * (unsigned int)v3832[0];
LABEL_360:
    while ( v217 && v217 != v4216 )
    {
      if ( v4218 )
      {
        if ( !v219 )
          break;
        if ( v4219 )
        {
          v227 = *(_DWORD *)(v4219 + 4);
          if ( (v227 & 1) != 0 )
          {
            *v225 = v4215 + (v227 & 0xFFFFFFFE);
            v4219 = 0i64;
          }
          else
          {
            v228 = (unsigned int)(v4221 + v227);
            v229 = (unsigned int)v228;
            v230 = v228 + 4;
            if ( v230 < v229 || v230 > v4220 )
            {
              v3832[11] = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0x12ui64, v4218, v4215, v229);
            }
            v231 = *(_DWORD *)(v4218 + v229);
            v4221 += 4;
            v4219 &= -(__int64)((v231 & 1) != 0);
            if ( (v231 & 1) != 0 )
              v231 &= ~1u;
            *v225 = v4215 + v231;
          }
        }
        else
        {
          *v225 = v219;
          v4214 = 0i64;
        }
      }
      else
      {
        while ( 1 )
        {
          v232 = v217;
          v233 = RtlpConvertFunctionEntry(v217, v4215, v225);
          v234 = RtlpSameFunction(v233, v4215, v4212);
          v217 = v4213 + 12;
          v4213 += 12i64;
          if ( v234 )
            break;
          if ( v217 == v4216 )
            goto LABEL_375;
        }
        *v4217 = v232;
      }
      v243 = *v3882;
      v244 = v3882[1] - v243;
      v245 = v226 + v243;
      if ( v213 )
      {
        v246 = 2i64 * v215;
        v213[2 * v246 + 4] = v244;
        *(_QWORD *)&v213[2 * v246 + 2] = v245;
      }
      HIDWORD(v4171) += v244;
      v247 = v245 & 0xFFFFFFFFFFFFF000ui64;
      LODWORD(v3801) = v215 + 1;
      Timer = (PKTIMER)(v245 + v244);
      do
      {
        v248 = v4172;
        v249 = 4i64;
        v250 = MmPteBase + ((v247 >> 9) & 0x7FFFFFFFF8i64);
        do
        {
          *v248++ = v250;
          v250 = MmPteBase + ((v250 >> 9) & 0x7FFFFFFFF8i64);
          --v249;
        }
        while ( v249 );
        v251 = 0;
        v252 = 3;
        do
        {
          v253 = v252;
          if ( v251 )
          {
            v4172[v252] = 0i64;
          }
          else
          {
            if ( !v252 )
              break;
            if ( *(char *)v4172[v252] < 0 )
              v251 = 1;
          }
          --v252;
        }
        while ( v253 );
        v207 = (_BYTE *)v3792;
        LODWORD(v254) = 4;
        do
        {
          v254 = (unsigned int)(v254 - 1);
          v255 = v4172[v254];
          if ( !v255 )
            break;
          for ( j = 0; j < HIDWORD(v4170[1]); ++j )
          {
            if ( v255 == *((_QWORD *)v4170[0] + j) )
              break;
          }
          if ( j == HIDWORD(v4170[1]) )
          {
            if ( HIDWORD(v4170[1]) == (_DWORD)v3799 )
            {
              v257 = 2 * v3799 + 64;
              LODWORD(v3799) = v257;
              v269 = ExAllocatePool2(64i64, 8i64 * v257, tag);
              v270 = (void *)v269;
              if ( !v269 )
              {
                v213 = v207 + 2720;
                goto LABEL_5364;
              }
              v271 = v4170[0];
              if ( v4170[0] )
              {
                v272 = (char *)v269;
                v273 = 8 * HIDWORD(v4170[1]);
                if ( (unsigned int)(8 * HIDWORD(v4170[1])) >= 8 )
                {
                  v274 = (unsigned __int64)v273 >> 3;
                  do
                  {
                    v273 -= 8;
                    *(_QWORD *)v272 = *v271++;
                    v272 += 8;
                    --v274;
                  }
                  while ( v274 );
                }
                if ( v273 )
                {
                  v275 = v272 - (char *)v271;
                  do
                  {
                    *((_BYTE *)v271 + v275) = *(_BYTE *)v271;
                    v271 = (_QWORD *)((char *)v271 + 1);
                    --v273;
                  }
                  while ( v273 );
                }
                ExFreePool(v4170[0]);
              }
              LODWORD(v4170[1]) = v3799;
              v4170[0] = v270;
            }
            v276 = HIDWORD(v4170[1]);
            ++HIDWORD(v4170[1]);
            HIDWORD(v4171) += 16;
            *((_QWORD *)v4170[0] + v276) = v255;
          }
        }
        while ( (_DWORD)v254 );
        v247 += 4096i64;
      }
      while ( v247 < (unsigned __int64)Timer );
      v215 = v3801;
      v213 = v207 + 2720;
      v225 = v4217;
      v219 = v4214;
      v217 = v4213;
      v226 = v3859;
      LODWORD(v4171) = v3801;
    }
LABEL_375:
    v214 = v3789 + 1;
    v3789 = v214;
    if ( v214 < 0xF )
      continue;
    break;
  }
  if ( v213 )
  {
    v235 = 2i64 * v215;
    v213[2 * v235 + 4] = 8;
    *(_QWORD *)&v213[2 * v235 + 2] = &off_140C019E8;
  }
  HIDWORD(v4171) += 8;
  v236 = (unsigned __int64)&off_140C019E8 & 0xFFFFFFFFFFFFF000ui64;
  LODWORD(v3801) = v215 + 1;
  Timer = (PKTIMER)((unsigned __int64)&off_140C019E8 & 0xFFFFFFFFFFFFF000ui64);
  do
  {
    v237 = v4173;
    v238 = 4i64;
    v239 = MmPteBase + ((v236 >> 9) & 0x7FFFFFFFF8i64);
    do
    {
      *v237++ = v239;
      v239 = MmPteBase + ((v239 >> 9) & 0x7FFFFFFFF8i64);
      --v238;
    }
    while ( v238 );
    v240 = 0;
    v241 = 3;
    do
    {
      v242 = v241;
      if ( v240 )
      {
        v4173[v241] = 0i64;
      }
      else
      {
        if ( !v241 )
          break;
        if ( *(char *)v4173[v241] < 0 )
          v240 = 1;
      }
      --v241;
    }
    while ( v242 );
    v207 = (_BYTE *)v3792;
    LODWORD(v277) = 4;
    do
    {
      v277 = (unsigned int)(v277 - 1);
      v278 = v4173[v277];
      if ( !v278 )
        break;
      for ( k = 0; k < HIDWORD(v4170[1]); ++k )
      {
        if ( v278 == *((_QWORD *)v4170[0] + k) )
          break;
      }
      if ( k == HIDWORD(v4170[1]) )
      {
        if ( HIDWORD(v4170[1]) == (_DWORD)v3799 )
        {
          v280 = 2 * v3799 + 64;
          LODWORD(v3799) = v280;
          v292 = ExAllocatePool2(64i64, 8i64 * v280, tag);
          v293 = (void *)v292;
          if ( !v292 )
          {
LABEL_5364:
            v3832[22] = 317;
            KeBugCheckEx(__ROR4__(317, 160), 0x1Bui64, (ULONG_PTR)v207, (ULONG_PTR)v213, 1ui64);
          }
          v294 = v4170[0];
          if ( v4170[0] )
          {
            v295 = (char *)v292;
            v296 = 8 * HIDWORD(v4170[1]);
            if ( (unsigned int)(8 * HIDWORD(v4170[1])) >= 8 )
            {
              v297 = (unsigned __int64)v296 >> 3;
              do
              {
                v296 -= 8;
                *(_QWORD *)v295 = *v294++;
                v295 += 8;
                --v297;
              }
              while ( v297 );
            }
            if ( v296 )
            {
              v298 = v295 - (char *)v294;
              do
              {
                *((_BYTE *)v294 + v298) = *(_BYTE *)v294;
                v294 = (_QWORD *)((char *)v294 + 1);
                --v296;
              }
              while ( v296 );
            }
            ExFreePool(v4170[0]);
          }
          v4170[0] = v293;
          LODWORD(v4170[1]) = v3799;
        }
        v299 = HIDWORD(v4170[1]);
        ++HIDWORD(v4170[1]);
        HIDWORD(v4171) += 16;
        *((_QWORD *)v4170[0] + v299) = v278;
      }
    }
    while ( (_DWORD)v277 );
    v210 = (__int64)&qword_140C019F0;
    v236 = (unsigned __int64)&Timer[64];
    Timer = (PKTIMER)v236;
  }
  while ( v236 < (unsigned __int64)&qword_140C019F0 );
  v300 = v3801;
  LODWORD(v4171) = v3801;
  if ( v213 )
  {
    v301 = HIDWORD(v4170[1]);
    v302 = (char *)(v213 + 2);
    v213[1] = HIDWORD(v4170[1]);
    v303 = (char *)&v213[4 * v300 + 2];
    v304 = v303;
    if ( v301 )
    {
      v210 = (__int64)v4170[0];
      v305 = v301;
      do
      {
        v306 = *(_QWORD **)v210;
        v210 += 8i64;
        *(_QWORD *)v304 = v306;
        *((_QWORD *)v304 + 1) = *v306;
        v304 += 16;
        --v305;
      }
      while ( v305 );
    }
    if ( v302 < v303 )
    {
      do
      {
        v210 = *((unsigned int *)v302 + 2);
        v307 = v304;
        v308 = *(_QWORD **)v302;
        if ( (unsigned int)v210 >= 8 )
        {
          v309 = (unsigned __int64)(unsigned int)v210 >> 3;
          do
          {
            v210 = (unsigned int)(v210 - 8);
            *(_QWORD *)v307 = *v308++;
            v307 += 8;
            --v309;
          }
          while ( v309 );
        }
        if ( (_DWORD)v210 )
        {
          v310 = v307 - (char *)v308;
          do
          {
            *((_BYTE *)v308 + v310) = *(_BYTE *)v308;
            v308 = (_QWORD *)((char *)v308 + 1);
            v210 = (unsigned int)(v210 - 1);
          }
          while ( (_DWORD)v210 );
        }
        v311 = *((unsigned int *)v302 + 2);
        v302 += 16;
        v304 += v311;
      }
      while ( v302 < v303 );
      v207 = (_BYTE *)v3792;
      v300 = v3801;
    }
    *v213 = v300;
  }
  v208 = v3797;
  v209 = v3796;
LABEL_499:
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  LOBYTE(v210) = 1;
  v312 = (_DWORD *)RtlImageDirectoryEntryToData(0x140000000ui64, v210, 6i64, v3833);
  if ( !v312 )
    goto LABEL_516;
  v314 = &v312[7 * ((unsigned int)v3833[0] / 0x1Cui64)];
  if ( v312 >= v314 )
    goto LABEL_516;
  v313 = 1346849024i64;
  while ( 2 )
  {
    v315 = v312[3];
    if ( v315 == 10 )
    {
      v316 = (_DWORD *)(0x140000000i64 + (unsigned int)v312[5]);
      v317 = &v316[(unsigned __int64)(unsigned int)v312[4] >> 2];
      while ( v316 < v317 )
      {
        if ( *v316 == 1346849024 )
          goto LABEL_515;
        ++v316;
      }
LABEL_513:
      v312 += 7;
      if ( v312 >= v314 )
        goto LABEL_516;
      continue;
    }
    break;
  }
  if ( v315 != 13 )
    goto LABEL_513;
  v318 = (_DWORD *)(0x140000000i64 + (unsigned int)v312[5]);
  if ( v318 == &v318[(unsigned __int64)(unsigned int)v312[4] >> 2] || *v318 != 1346849024 )
    goto LABEL_513;
LABEL_515:
  *((_DWORD *)v207 + 613) |= 0x10000u;
LABEL_516:
  if ( __32 )
    *((_DWORD *)v207 + 613) |= 0x4000u;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  *((_DWORD *)v207 + 505) = v208;
  v319 = v3798;
  *((_DWORD *)v207 + 647) = v209;
  *((_QWORD *)v207 + 249) = v319;
  *((_DWORD *)v207 + 585) = v3793;
  *(_OWORD *)v207 = *(_OWORD *)CmpAppendDllSection;
  *((_OWORD *)v207 + 1) = *((_OWORD *)CmpAppendDllSection + 1);
  *((_OWORD *)v207 + 2) = *((_OWORD *)CmpAppendDllSection + 2);
  *((_OWORD *)v207 + 3) = *((_OWORD *)CmpAppendDllSection + 3);
  *((_OWORD *)v207 + 4) = *((_OWORD *)CmpAppendDllSection + 4);
  *((_OWORD *)v207 + 5) = *((_OWORD *)CmpAppendDllSection + 5);
  *((_OWORD *)v207 + 6) = *((_OWORD *)CmpAppendDllSection + 6);
  *((_OWORD *)v207 + 7) = *((_OWORD *)CmpAppendDllSection + 7);
  *((_OWORD *)v207 + 8) = *((_OWORD *)CmpAppendDllSection + 8);
  *((_OWORD *)v207 + 9) = *((_OWORD *)CmpAppendDllSection + 9);
  *((_OWORD *)v207 + 10) = *((_OWORD *)CmpAppendDllSection + 10);
  *((_OWORD *)v207 + 11) = *((_OWORD *)CmpAppendDllSection + 11);
  *((_DWORD *)v207 + 48) = *((_DWORD *)CmpAppendDllSection + 48);
  v320 = v3800;
  *((_DWORD *)v207 + 508) = v3800 + v3784;
  LODWORD(v319) = v320 + v3783;
  *((_DWORD *)v207 + 510) = v208;
  *((_DWORD *)v207 + 506) = (_DWORD)v319;
  *((_DWORD *)v207 + 507) = v320 + v3785;
  *((_DWORD *)v207 + 509) = v320 + v3791;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  *((_QWORD *)v207 + 27) = KiFreezeDataTableEntry;
  *((_QWORD *)v207 + 28) = ExAcquireResourceSharedLite;
  *((_QWORD *)v207 + 29) = ExAcquireResourceExclusiveLite;
  *((_QWORD *)v207 + 30) = ExAllocatePool2;
  *((_QWORD *)v207 + 31) = ExFreePool;
  *((_QWORD *)v207 + 32) = ExMapHandleToPointer;
  *((_QWORD *)v207 + 33) = ExGetHandlePointer;
  *((_QWORD *)v207 + 34) = ExQueueWorkItem;
  *((_QWORD *)v207 + 35) = ExReleaseResourceLite;
  *((_QWORD *)v207 + 36) = ExUnlockHandleTableEntry;
  *((_QWORD *)v207 + 37) = ExAcquirePushLockExclusiveEx;
  *((_QWORD *)v207 + 38) = ExReleasePushLockExclusiveEx;
  *((_QWORD *)v207 + 39) = ExAcquirePushLockSharedEx;
  *((_QWORD *)v207 + 40) = ExReleasePushLockSharedEx;
  *((_QWORD *)v207 + 41) = KeAcquireInStackQueuedSpinLockAtDpcLevel;
  *((_QWORD *)v207 + 42) = ExAcquireSpinLockSharedAtDpcLevel;
  *((_QWORD *)v207 + 43) = KeBugCheckEx;
  *((_QWORD *)v207 + 44) = KeDelayExecutionThread;
  *((_QWORD *)v207 + 45) = KeEnterCriticalRegionThread;
  *((_QWORD *)v207 + 46) = KeLeaveCriticalRegion;
  *((_QWORD *)v207 + 47) = KeEnterGuardedRegion;
  *((_QWORD *)v207 + 48) = KeLeaveGuardedRegion;
  *((_QWORD *)v207 + 49) = KeReleaseInStackQueuedSpinLockFromDpcLevel;
  *((_QWORD *)v207 + 50) = ExReleaseSpinLockSharedFromDpcLevel;
  *((_QWORD *)v207 + 51) = KeRevertToUserGroupAffinityThread;
  *((_QWORD *)v207 + 52) = KeProcessorGroupAffinity;
  *((_QWORD *)v207 + 53) = KeInitializeAffinityEx2;
  *((_QWORD *)v207 + 54) = KeInitializeEnumerationContext;
  *((_QWORD *)v207 + 55) = KeEnumerateNextProcessor;
  *((_QWORD *)v207 + 56) = KeCountSetBitsAffinityEx;
  *((_QWORD *)v207 + 57) = KeQueryAffinityProcess;
  *((_QWORD *)v207 + 58) = KeSetSystemGroupAffinityThread;
  *((_QWORD *)v207 + 59) = KeSetCoalescableTimer;
  *((_QWORD *)v207 + 63) = RtlImageNtHeader;
  *((_QWORD *)v207 + 66) = RtlSectionTableFromVirtualAddress;
  *((_QWORD *)v207 + 64) = RtlLookupFunctionTableEx;
  *((_QWORD *)v207 + 65) = RtlPcToFileHeader;
  *((_QWORD *)v207 + 60) = ObfDereferenceObject;
  *((_QWORD *)v207 + 61) = &ObReferenceObjectByName;
  *((_QWORD *)v207 + 62) = RtlImageDirectoryEntryToData;
  *((_QWORD *)v207 + 67) = DbgPrint;
  *((_QWORD *)v207 + 68) = MmAllocateIndependentPages;
  *((_QWORD *)v207 + 69) = MmFreeIndependentPages;
  *((_QWORD *)v207 + 70) = MmSetPageProtection;
  *((_QWORD *)v207 + 76) = RtlLookupFunctionEntry;
  *((_QWORD *)v207 + 77) = KeAcquireSpinLockRaiseToDpc;
  *((_QWORD *)v207 + 78) = KeReleaseSpinLock;
  *((_QWORD *)v207 + 79) = MmGetSessionById;
  *((_QWORD *)v207 + 80) = MmGetNextSession;
  *((_QWORD *)v207 + 81) = MmQuitNextSession;
  *((_QWORD *)v207 + 82) = MmAttachSession;
  *((_QWORD *)v207 + 83) = MmDetachSession;
  *((_QWORD *)v207 + 84) = MmGetSessionIdEx;
  *((_QWORD *)v207 + 85) = MmIsSessionAddress;
  *((_QWORD *)v207 + 86) = MmIsAddressValid;
  *((_QWORD *)v207 + 87) = MmSessionGetWin32Callouts;
  *((_QWORD *)v207 + 88) = KeInsertQueueApc;
  *((_QWORD *)v207 + 89) = KeWaitForSingleObject;
  *((_QWORD *)v207 + 91) = ExReferenceCallBackBlock;
  *((_QWORD *)v207 + 92) = ExGetCallBackBlockRoutine;
  *((_QWORD *)v207 + 93) = &ExDereferenceCallBackBlock;
  *((_QWORD *)v207 + 94) = sub_1403E00B0;
  *((_QWORD *)v207 + 95) = PspEnumerateCallback;
  *((_QWORD *)v207 + 96) = CmpEnumerateCallback;
  *((_QWORD *)v207 + 97) = DbgEnumerateCallback;
  *((_QWORD *)v207 + 98) = ExpEnumerateCallback;
  *((_QWORD *)v207 + 99) = ExpGetNextCallback;
  *((_QWORD *)v207 + 100) = xHalTimerWatchdogStop;
  *((_QWORD *)v207 + 101) = KiSchedulerApcTerminate;
  *((_QWORD *)v207 + 102) = KiSchedulerApc;
  *((_QWORD *)v207 + 103) = xHalTimerWatchdogStop;
  *((_QWORD *)v207 + 104) = sub_1403E1170;
  *((_QWORD *)v207 + 105) = MmAllocatePagesForMdlEx;
  *((_QWORD *)v207 + 106) = MmAllocateMappingAddress;
  *((_QWORD *)v207 + 107) = MmMapLockedPagesWithReservedMapping;
  *((_QWORD *)v207 + 108) = MmUnmapReservedMapping;
  *((_QWORD *)v207 + 109) = sub_1403ED540;
  *((_QWORD *)v207 + 110) = sub_1403ED5B0;
  *((_QWORD *)v207 + 111) = MmAcquireLoadLock;
  *((_QWORD *)v207 + 112) = MmReleaseLoadLock;
  *((_QWORD *)v207 + 113) = KeEnumerateQueueApc;
  *((_QWORD *)v207 + 114) = KeIsApcRunningThread;
  *((_QWORD *)v207 + 115) = &sub_1403E1040;
  *((_QWORD *)v207 + 116) = PsAcquireProcessExitSynchronization;
  *((_QWORD *)v207 + 117) = ObDereferenceProcessHandleTable;
  *((_QWORD *)v207 + 118) = PsGetNextProcess;
  *((_QWORD *)v207 + 119) = PsQuitNextProcessThread;
  *((_QWORD *)v207 + 120) = PsGetNextProcessEx;
  *((_QWORD *)v207 + 121) = MmIsSessionLeaderProcess;
  *((_QWORD *)v207 + 122) = PsInvokeWin32Callout;
  *((_QWORD *)v207 + 123) = MmEnumerateAddressSpaceAndReferenceImages;
  *((_QWORD *)v207 + 124) = PsGetProcessProtection;
  *((_QWORD *)v207 + 125) = PsGetProcessSignatureLevel;
  *((_QWORD *)v207 + 126) = PsGetProcessSectionBaseAddress;
  *((_QWORD *)v207 + 127) = SeCompareSigningLevels;
  *((_QWORD *)v207 + 133) = RtlIsMultiSessionSku;
  *((_QWORD *)v207 + 134) = KiEnumerateCallback;
  *((_QWORD *)v207 + 135) = KeStackAttachProcess;
  *((_QWORD *)v207 + 136) = KeUnstackDetachProcess;
  *((_QWORD *)v207 + 137) = KeIpiGenericCall;
  *((_QWORD *)v207 + 138) = sub_1403ED390;
  *((_QWORD *)v207 + 139) = MmGetPhysicalAddress;
  *((_QWORD *)v207 + 140) = MmUnlockPages;
  *((_QWORD *)v207 + 128) = KeComputeSha256;
  *((_QWORD *)v207 + 129) = KeComputeParallelSha256;
  *((_QWORD *)v207 + 130) = KeSetEvent;
  *((_QWORD *)v207 + 141) = VslVerifyPage;
  *((_QWORD *)v207 + 142) = VslVerifySessionSpace;
  *((_QWORD *)v207 + 145) = PsLookupProcessByProcessId;
  *((_QWORD *)v207 + 146) = PsGetProcessId;
  *((_QWORD *)v207 + 147) = MmCheckProcessShadow;
  *((_QWORD *)v207 + 148) = MmGetImageRetpolineCodePage;
  *((_QWORD *)v207 + 300) = &qword_140C0DF40;
  if ( a4 )
    *((_QWORD *)v207 + 90) = *(_QWORD *)(a4 + 8);
  *((_QWORD *)v207 + 131) = RtlpConvertFunctionEntry;
  *((_QWORD *)v207 + 132) = RtlpLookupPrimaryFunctionEntry;
  *((_QWORD *)v207 + 143) = KiGetInterruptObjectAddress;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  *((_DWORD *)v207 + 599) = v208;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v321 = __rdtsc();
  v322 = (__ROR8__(v321, 3) ^ v321) * (unsigned __int128)0x7010008004002001ui64;
  v3888 = *((_QWORD *)&v322 + 1);
  if ( ((unsigned __int64)v322 ^ *((_QWORD *)&v322 + 1)) % 0xA >= 3 )
  {
    v326 = 0;
  }
  else
  {
    *((_DWORD *)v207 + 586) = 4;
    v323 = __rdtsc();
    v324 = (__ROR8__(v323, 3) ^ v323) * (unsigned __int128)0x7010008004002001ui64;
    v3889 = *((_QWORD *)&v324 + 1);
    v325 = v324 ^ *((_QWORD *)&v324 + 1);
    *((_QWORD *)&v324 + 1) = (((unsigned __int64)v324 ^ *((_QWORD *)&v324 + 1))
                            * (unsigned __int128)0x2492492492492493ui64) >> 64;
    v326 = v325 - 7 * ((*((_QWORD *)&v324 + 1) + ((unsigned __int64)(v325 - *((_QWORD *)&v324 + 1)) >> 1)) >> 2);
  }
  *((_DWORD *)v207 + 586) = v326;
  if ( qword_140D815F0 > 0x1F )
  {
    v3833[1] = 317;
    KeBugCheckEx(__ROR4__(317, 160), 3ui64, 0i64, qword_140D815F0, 0i64);
  }
  *((_DWORD *)v207 + 612) ^= (*((_DWORD *)v207 + 612) ^ ((_DWORD)qword_140D815F0 << 10)) & 0x7C00;
  *((_DWORD *)v207 + 596) = dword_140C0DF00++;
  *((_QWORD *)v207 + 256) = 0i64;
  *((char **)v207 + 294) = VfExcludeSections[0];
  *((char **)v207 + 295) = off_140C094B0[0];
  *((char **)v207 + 296) = off_140C094B8[0];
  *((_QWORD *)v207 + 297) = off_140C094C0;
  v327 = __rdtsc();
  v328 = (__ROR8__(v327, 3) ^ v327) * (unsigned __int128)0x7010008004002001ui64;
  v3890 = *((_QWORD *)&v328 + 1);
  v329 = v328 ^ *((_QWORD *)&v328 + 1);
  v330 = (((unsigned __int64)v328 ^ *((_QWORD *)&v328 + 1)) * (unsigned __int128)0x624DD2F1A9FBE77ui64) >> 64;
  if ( v329 - 1000 * ((v330 + ((unsigned __int64)(v329 - v330) >> 1)) >> 9) < 3 )
    *((_DWORD *)v207 + 613) |= 0x400000u;
  *((_QWORD *)v207 + 248) = KeGetPrcb(0i64, v330, v313, 0x2492492492492493i64);
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  *((_DWORD *)v207 + 523) = 0x140000 / a3;
  *((_QWORD *)v207 + 151) = &qword_140C097A0;
  *((_QWORD *)v207 + 152) = &qword_140C0DF28;
  *((_QWORD *)v207 + 153) = &qword_140C0DF30;
  *((_QWORD *)v207 + 154) = &qword_140C0DF38;
  *((_QWORD *)v207 + 155) = PsInitialSystemProcess;
  *((_QWORD *)v207 + 156) = KiWaitAlways;
  *((_QWORD *)v207 + 157) = &KiEntropyTimingRoutine;
  *((_QWORD *)v207 + 158) = &KiProcessListHead;
  *((_QWORD *)v207 + 159) = &KiProcessListLock;
  *((_QWORD *)v207 + 160) = ObpTypeObjectType;
  *((_QWORD *)v207 + 161) = IoDriverObjectType;
  *((_QWORD *)v207 + 162) = PsProcessType;
  *((_QWORD *)v207 + 163) = &PsActiveProcessHead;
  *((_QWORD *)v207 + 164) = &PsInvertedFunctionTable;
  *((_QWORD *)v207 + 165) = &PsLoadedModuleList;
  *((_QWORD *)v207 + 166) = &PsLoadedModuleResource;
  *((_QWORD *)v207 + 167) = &PsLoadedModuleSpinLock;
  *((_QWORD *)v207 + 168) = &PspActiveProcessLock;
  *((_QWORD *)v207 + 169) = &PspCidTable;
  *((_QWORD *)v207 + 170) = &ExpUuidLock;
  *((_QWORD *)v207 + 171) = &AlpcpPortListLock;
  *((_QWORD *)v207 + 172) = &KeServiceDescriptorTable;
  *((_QWORD *)v207 + 173) = &KeServiceDescriptorTableShadow;
  *((_QWORD *)v207 + 174) = &KeServiceDescriptorTableFilter;
  *((_QWORD *)v207 + 175) = &VfThunksExtended;
  *((_QWORD *)v207 + 176) = &PsWin32CallBack;
  *((_QWORD *)v207 + 177) = &qword_140C0DF08;
  *((_QWORD *)v207 + 178) = &KiTableInformation;
  *((_QWORD *)v207 + 179) = &HandleTableListHead;
  *((_QWORD *)v207 + 180) = &HandleTableListLock;
  *((_QWORD *)v207 + 181) = ObpKernelHandleTable;
  *((_QWORD *)v207 + 182) = 0xFFFFF78000000000ui64;
  *((_QWORD *)v207 + 183) = KiWaitNever;
  *((_QWORD *)v207 + 184) = &SeProtectedMapping;
  *((_QWORD *)v207 + 186) = &KiStackProtectNotifyEvent;
  *((_QWORD *)v207 + 187) = MmPteBase;
  *((_QWORD *)v207 + 188) = PsNtosImageBase;
  *((_QWORD *)v207 + 189) = PsHalImageBase;
  *((_QWORD *)v207 + 190) = &KeNumberProcessors_0;
  v331 = v207 + 1592;
  v332 = 2i64;
  *((_QWORD *)v207 + 193) = &MaxDataSize;
  *((_QWORD *)v207 + 194) = &qword_140D1E9D0;
  *((_QWORD *)v207 + 195) = &RtlpInvertedFunctionTable;
  *((_QWORD *)v207 + 185) = KiInterruptThunk;
  v333 = &_ti_a;
  do
  {
    *v331 = *(_OWORD *)v333;
    v331[1] = *((_OWORD *)v333 + 1);
    v331[2] = *((_OWORD *)v333 + 2);
    v331[3] = *((_OWORD *)v333 + 3);
    v331[4] = *((_OWORD *)v333 + 4);
    v331[5] = *((_OWORD *)v333 + 5);
    v331[6] = *((_OWORD *)v333 + 6);
    v331 += 8;
    v334 = *((_OWORD *)v333 + 7);
    v333 += 16;
    *(v331 - 1) = v334;
    --v332;
  }
  while ( v332 );
  *v331 = *(_OWORD *)v333;
  v331[1] = *((_OWORD *)v333 + 1);
  v331[2] = *((_OWORD *)v333 + 2);
  v331[3] = *((_OWORD *)v333 + 3);
  *((_QWORD *)v331 + 8) = v333[8];
  v335 = KxUnexpectedInterrupt0;
  if ( KiKvaShadow )
    v335 = KiIsrThunkShadow;
  *((_QWORD *)v207 + 196) = v335;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  *((_DWORD *)v207 + 514) = v208;
  *((_DWORD *)v207 + 651) = v208;
  *((_DWORD *)v207 + 516) = alloc_tag;
  v347 = __rdtsc();
  v348 = (__ROR8__(v347, 3) ^ v347) * (unsigned __int128)0x7010008004002001ui64;
  v3893 = *((_QWORD *)&v348 + 1);
  v349 = v348 ^ *((_QWORD *)&v348 + 1);
  *((_QWORD *)&v348 + 1) = (((unsigned __int64)v348 ^ *((_QWORD *)&v348 + 1)) * (unsigned __int128)0x410410410410411ui64) >> 64;
  *((_DWORD *)v207 + 517) = v349
                          - 63
                          * ((*((_QWORD *)&v348 + 1) + ((unsigned __int64)(v349 - *((_QWORD *)&v348 + 1)) >> 1)) >> 5)
                          + 1;
  *(_QWORD *)&v348 = __rdtsc();
  v350 = (__ROR8__(v348, 3) ^ (unsigned __int64)v348) * (unsigned __int128)0x7010008004002001ui64;
  v351 = 700 - v208;
  v3894 = *((_QWORD *)&v350 + 1);
  *((_QWORD *)&v350 + 1) ^= v350;
  *((_QWORD *)v207 + 259) = *((_QWORD *)&v350 + 1);
  if ( (DWORD2(v350) & 0x80000000) != 0 )
    v351 = 724 - v208;
  *((_DWORD *)v207 + 599) = (*((_DWORD *)v207 + 599) + v351) ^ 0xBC2A27DB;
  v352 = __rdtsc();
  v353 = (__ROR8__(v352, 3) ^ v352) * (unsigned __int128)0x7010008004002001ui64;
  v3895 = *((_QWORD *)&v353 + 1);
  if ( ((unsigned __int64)v353 ^ *((_QWORD *)&v353 + 1)) % 0xA < 3 )
    *((_DWORD *)v207 + 612) |= 8u;
  v354 = __rdtsc();
  v355 = (__ROR8__(v354, 3) ^ v354) * (unsigned __int128)0x7010008004002001ui64;
  v3896 = *((_QWORD *)&v355 + 1);
  if ( ((unsigned __int64)v355 ^ *((_QWORD *)&v355 + 1)) % 0xA < 3 )
    *((_DWORD *)v207 + 612) |= 0x4000000u;
  v356 = v4344;
  if ( v4344 == 7
    || (v357 = __rdtsc(),
        v358 = (__ROR8__(v357, 3) ^ v357) * (unsigned __int128)0x7010008004002001ui64,
        v3897 = *((_QWORD *)&v358 + 1),
        ((unsigned __int64)v358 ^ *((_QWORD *)&v358 + 1)) % 0xA < 2) )
  {
    *((_DWORD *)v207 + 613) |= 8u;
  }
  v359 = __rdtsc();
  v360 = (__ROR8__(v359, 3) ^ v359) * (unsigned __int128)0x7010008004002001ui64;
  v3898 = *((_QWORD *)&v360 + 1);
  if ( !(((unsigned __int64)v360 ^ *((_QWORD *)&v360 + 1)) % 0xA) )
    *((_DWORD *)v207 + 612) |= 0x8000u;
  v361 = __rdtsc();
  v362 = (__ROR8__(v361, 3) ^ v361) * (unsigned __int128)0x7010008004002001ui64;
  v3899 = *((_QWORD *)&v362 + 1);
  if ( ((unsigned __int64)v362 ^ *((_QWORD *)&v362 + 1)) % 0xA < 3 )
    *((_DWORD *)v207 + 612) |= 0x400000u;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v363 = __rdtsc();
  v364 = (__ROR8__(v363, 3) ^ v363) * (unsigned __int128)0x7010008004002001ui64;
  v3900 = *((_QWORD *)&v364 + 1);
  if ( !(((unsigned __int64)v364 ^ *((_QWORD *)&v364 + 1)) % 0xA) )
    *((_DWORD *)v207 + 612) |= 0x8000000u;
  v365 = __rdtsc();
  v366 = (__ROR8__(v365, 3) ^ v365) * (unsigned __int128)0x7010008004002001ui64;
  v3901 = *((_QWORD *)&v366 + 1);
  if ( ((unsigned __int64)v366 ^ *((_QWORD *)&v366 + 1)) % 0xA < 3 )
    *((_DWORD *)v207 + 612) |= 0x800000u;
  if ( a4 )
  {
    if ( (v3836 & 1) != 0 && v4344 != 4 )
    {
      v367 = __rdtsc();
      v368 = (__ROR8__(v367, 3) ^ v367) * (unsigned __int128)0x7010008004002001ui64;
      v3902 = *((_QWORD *)&v368 + 1);
      if ( ((unsigned __int64)v368 ^ *((_QWORD *)&v368 + 1)) % 0xA < 6 )
        *((_DWORD *)v207 + 613) |= 1u;
    }
  }
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v369 = __rdtsc();
  v370 = (__ROR8__(v369, 3) ^ v369) * (unsigned __int128)0x7010008004002001ui64;
  v3903 = *((_QWORD *)&v370 + 1);
  v371 = *((_QWORD *)&v370 + 1) ^ v370;
  *((_QWORD *)&v370 + 1) = ((*((_QWORD *)&v370 + 1) ^ (unsigned __int64)v370) * (unsigned __int128)0x47AE147AE147AE15ui64) >> 64;
  if ( v371 == 100 * ((*((_QWORD *)&v370 + 1) + ((unsigned __int64)(v371 - *((_QWORD *)&v370 + 1)) >> 1)) >> 6) )
    *((_DWORD *)v207 + 613) |= 0x20000u;
  if ( (*((unsigned __int8 (**)(void))v207 + 133))() )
    *((_DWORD *)v207 + 613) |= 2u;
  if ( (unsigned int)HvlIsHypervisorPresent() )
    *((_DWORD *)v207 + 613) |= 0x40000u;
  if ( (unsigned __int8)MiIsRetpolineEnabled() )
    *((_DWORD *)v207 + 613) |= 0x100000u;
  v372 = __rdtsc();
  v373 = (__ROR8__(v372, 3) ^ v372) * (unsigned __int128)0x7010008004002001ui64;
  v3904 = *((_QWORD *)&v373 + 1);
  if ( !(((unsigned __int64)v373 ^ *((_QWORD *)&v373 + 1)) % 0xA) )
    *((_DWORD *)v207 + 613) |= 0x80u;
  if ( v4344 == 7 )
  {
    *((_DWORD *)v207 + 612) = *((_DWORD *)v207 + 612) & 0xBBFFFFF7 | 0x40000000;
    *((_DWORD *)v207 + 598) = 1;
  }
  if ( (int)KiSwInterruptPresent() >= 0 )
  {
    *((_DWORD *)v207 + 612) |= 0x80000000;
    *((_DWORD *)v207 + 613) |= 0x2000u;
  }
  *((_QWORD *)v207 + 338) = KeComputeParallelSha256StateSize();
  v385 = (*((__int64 (__fastcall **)(__int64, _QWORD, _QWORD))ExAllocatePool2))(64i64, *((_QWORD *)v207 + 338), tag);
  *((_QWORD *)v207 + 337) = v385;
  if ( !v385 )
    return 0;
  if ( !__2a )
  {
    v397 = (_QWORD *)(*((__int64 (__fastcall **)(__int64, __int64, _QWORD))ExAllocatePool2))(64i64, 8i64, tag);
    __2a = (__int64)v397;
    if ( !v397 )
      return 0;
    *v397 = 0i64;
  }
  *((_QWORD *)v207 + 320) = __2a;
  if ( (unsigned int)KiIsKernelCfgActive() )
    *((_DWORD *)v207 + 613) |= 0x10u;
  if ( (unsigned int)((__int64 (__fastcall *)(__int64, __int64))KiAreCodePatchesAllowed)(v399, v398) )
    *((_DWORD *)v207 + 613) |= 0x40u;
  *((_DWORD *)v207 + 526) = v4344;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v400 = __cpuid(-2147483640, 0);
  v4114 = EAX(v400);
  v401 = v4114 >> 8;
  v207[2336] = BYTE1(v4114);
  v4115 = EBX(v400);
  v4116 = ECX(v400);
  v4117 = EDX(v400);
  v402 = __rdtsc();
  v403 = (__ROR8__(v402, 3) ^ v402) * (unsigned __int128)0x7010008004002001ui64;
  v3909 = *((_QWORD *)&v403 + 1);
  if ( ((unsigned __int64)v403 ^ *((_QWORD *)&v403 + 1)) % 0xA < 3 )
    *((_DWORD *)v207 + 613) |= 0x100u;
  if ( (unsigned __int8)v401 > 0x3Fu )
  {
    v3833[32] = 317;
    KeBugCheckEx(__ROR4__(317, 160), 0i64, 0i64, 0i64, 0i64);
  }
  LODWORD(v3799) = v3836 & 1;
  if ( (v3836 & 1) != 0 )
  {
    v404 = (unsigned __int64)&qword_140C0DF50;
    v405 = (unsigned __int64)&qword_140C0DF50 & 0x3F;
    LODWORD(v3801) = (unsigned __int64)&qword_140C0DF50 & 0x3F;
    RtlImageNtHeader(0x140000000ui64);
    RtlCaptureImageExceptionValues(0x140000000ui64, &v4222, v3834);
    v407 = v4222;
    v4223 = 0x140000000ui64;
    v408 = 0x140000000ui64;
    v3834[0] /= 0xCu;
    v409 = v4222 + 12i64 * (unsigned int)v3834[0];
    v4224 = v409;
    v4225 = v3910;
    while ( v407 && v407 != v409 )
    {
      v410 = RtlpConvertFunctionEntry(v407, v408, v406);
      LOBYTE(v411) = v405;
      *v4225 = v410;
      v407 = v4222 + 12;
      v4222 += 12i64;
      v412 = *(unsigned int *)v3910[0];
      v413 = *(_DWORD *)(v3910[0] + 4) - v412;
      v414 = (_QWORD *)(0x140000000i64 + v412);
      v415 = 0x140000000i64 + v412 + v413;
      v406 = v414;
      v416 = (char *)v414;
      if ( (unsigned __int64)v414 < v415 )
      {
        do
        {
          _mm_prefetchnta(v416);
          v416 += 64;
        }
        while ( (unsigned __int64)v416 < v415 );
      }
      v417 = (__int64 *)v404;
      v418 = v413 >> 7;
      if ( v413 >> 7 )
      {
        do
        {
          v419 = 8i64;
          do
          {
            v420 = v406[1] ^ __ROL8__(*v406 ^ (unsigned __int64)v417, v411);
            v406 += 2;
            v417 = (__int64 *)__ROL8__(v420, v411);
            --v419;
          }
          while ( v419 );
          v421 = (__ROL8__(v404 ^ ((char *)v406 - (char *)v414), 17) ^ v404 ^ ((char *)v406 - (char *)v414))
               * (unsigned __int128)0x7010008004002001ui64;
          v3910[1] = *((_QWORD *)&v421 + 1);
          v411 = (BYTE8(v421) ^ (unsigned __int8)(v421 ^ v411)) & 0x3F;
          if ( !v411 )
            LOBYTE(v411) = 1;
          --v418;
        }
        while ( v418 );
        LOBYTE(v405) = v3801;
      }
      v422 = v413 & 0x7F;
      if ( v422 >= 8 )
      {
        v423 = (unsigned __int64)v422 >> 3;
        do
        {
          v417 = (__int64 *)__ROL8__(*v406++ ^ (unsigned __int64)v417, v411);
          v422 -= 8;
          --v423;
        }
        while ( v423 );
      }
      for ( ; v422; --v422 )
      {
        v424 = *(unsigned __int8 *)v406;
        v406 = (_QWORD *)((char *)v406 + 1);
        v417 = (__int64 *)__ROL8__(v424 ^ (unsigned __int64)v417, v411);
      }
      v409 = v4224;
      v404 = (unsigned __int64)v417;
      v408 = v4223;
    }
    v207 = (_BYTE *)v3792;
    v425 = *(_DWORD *)(v3792 + 2448) & 0xFFFBFFFF | (qword_140C0DF50 != v404 ? 0x40000 : 0);
    *(_DWORD *)(v3792 + 2448) = v425;
    if ( (v425 & 0x40000) != 0 && !*((_DWORD *)v207 + 574) )
      *(_QWORD *)(*((_QWORD *)v207 + 177) + 24i64) = qword_140C0DF50 ^ v404;
    v356 = v4344;
  }
  v426 = __rdtsc();
  v427 = (__ROR8__(v426, 3) ^ v426) * (unsigned __int128)0x7010008004002001ui64;
  v3910[2] = *((_QWORD *)&v427 + 1);
  if ( ((unsigned __int64)v427 ^ *((_QWORD *)&v427 + 1)) % 0xA < 2 && v356 != 3 )
  {
    v428 = *((unsigned int *)v207 + 516);
    v429 = __rdtsc();
    v430 = __ROR8__(v429, 3);
    v3911 = ((v430 ^ v429) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v431 = ((unsigned __int16)v3911 ^ (unsigned __int16)(8193 * (v430 ^ v429))) & 0x7FF;
    v432 = __rdtsc();
    v433 = (__ROR8__(v432, 3) ^ v432) * (unsigned __int128)0x7010008004002001ui64;
    v3912 = *((_QWORD *)&v433 + 1);
    v434 = (*((_QWORD *)&v433 + 1) ^ (unsigned __int64)v433) % (unsigned int)(v431 + 1);
    v435 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v431 + 32), v428);
    if ( v435 )
    {
      v437 = v434;
      v438 = (_QWORD *)v435;
      if ( (unsigned int)v434 >= 8 )
      {
        v439 = (unsigned __int64)(unsigned int)v434 >> 3;
        do
        {
          v440 = __rdtsc();
          v437 -= 8;
          v441 = (__ROR8__(v440, 3) ^ v440) * (unsigned __int128)0x7010008004002001ui64;
          v3913 = *((_QWORD *)&v441 + 1);
          *v438++ = v441 ^ *((_QWORD *)&v441 + 1);
          --v439;
        }
        while ( v439 );
      }
      if ( v437 )
      {
        v442 = __rdtsc();
        v443 = (__ROR8__(v442, 3) ^ v442) * (unsigned __int128)0x7010008004002001ui64;
        v3914 = *((_QWORD *)&v443 + 1);
        v444 = v443 ^ *((_QWORD *)&v443 + 1);
        do
        {
          *(_BYTE *)v438 = v444;
          v438 = (_QWORD *)((char *)v438 + 1);
          v444 >>= 8;
          --v437;
        }
        while ( v437 );
      }
      v445 = v431 - v434;
      v436 = v435 + (unsigned int)v434;
      v446 = (_QWORD *)(v436 + 32);
      if ( v445 >= 8 )
      {
        v447 = (unsigned __int64)v445 >> 3;
        do
        {
          v448 = __rdtsc();
          v445 -= 8;
          v449 = (__ROR8__(v448, 3) ^ v448) * (unsigned __int128)0x7010008004002001ui64;
          v3915 = *((_QWORD *)&v449 + 1);
          *v446++ = v449 ^ *((_QWORD *)&v449 + 1);
          --v447;
        }
        while ( v447 );
      }
      if ( v445 )
      {
        v450 = __rdtsc();
        v451 = (__ROR8__(v450, 3) ^ v450) * (unsigned __int128)0x7010008004002001ui64;
        v3916 = *((_QWORD *)&v451 + 1);
        v452 = v451 ^ *((_QWORD *)&v451 + 1);
        do
        {
          *(_BYTE *)v446 = v452;
          v446 = (_QWORD *)((char *)v446 + 1);
          v452 >>= 8;
          --v445;
        }
        while ( v445 );
      }
    }
    else
    {
      ++*((_DWORD *)v207 + 646);
      v436 = 0i64;
    }
    *((_QWORD *)v207 + 321) = v436;
    if ( !v436 )
      return 0;
  }
  v453 = __rdtsc();
  v454 = (__ROR8__(v453, 3) ^ v453) * (unsigned __int128)0x7010008004002001ui64;
  v3917 = *((_QWORD *)&v454 + 1);
  if ( ((unsigned __int64)v454 ^ *((_QWORD *)&v454 + 1)) % 0xA < 2 && (*((_DWORD *)v207 + 612) & 0x40000000) == 0 )
  {
    v455 = *((unsigned int *)v207 + 516);
    v456 = __rdtsc();
    v457 = __ROR8__(v456, 3);
    v3918 = ((v457 ^ v456) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v458 = ((unsigned __int16)v3918 ^ (unsigned __int16)(8193 * (v457 ^ v456))) & 0x7FF;
    v459 = __rdtsc();
    v460 = (__ROR8__(v459, 3) ^ v459) * (unsigned __int128)0x7010008004002001ui64;
    v3919 = *((_QWORD *)&v460 + 1);
    v461 = (*((_QWORD *)&v460 + 1) ^ (unsigned __int64)v460) % (unsigned int)(v458 + 1);
    v462 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v458 + 514), v455);
    if ( !v462 )
    {
      ++*((_DWORD *)v207 + 646);
      goto LABEL_5367;
    }
    v463 = v461;
    v464 = (_QWORD *)v462;
    if ( (unsigned int)v461 >= 8 )
    {
      v465 = (unsigned __int64)(unsigned int)v461 >> 3;
      do
      {
        v466 = __rdtsc();
        v463 -= 8;
        v467 = (__ROR8__(v466, 3) ^ v466) * (unsigned __int128)0x7010008004002001ui64;
        v3920 = *((_QWORD *)&v467 + 1);
        *v464++ = v467 ^ *((_QWORD *)&v467 + 1);
        --v465;
      }
      while ( v465 );
      v207 = (_BYTE *)v3792;
    }
    if ( v463 )
    {
      v468 = __rdtsc();
      v469 = (__ROR8__(v468, 3) ^ v468) * (unsigned __int128)0x7010008004002001ui64;
      v3921 = *((_QWORD *)&v469 + 1);
      v470 = v469 ^ *((_QWORD *)&v469 + 1);
      do
      {
        *(_BYTE *)v464 = v470;
        v464 = (_QWORD *)((char *)v464 + 1);
        v470 >>= 8;
        --v463;
      }
      while ( v463 );
    }
    v471 = v458 - v461;
    v472 = v462 + (unsigned int)v461;
    v473 = (_QWORD *)(v472 + 514);
    if ( v471 >= 8 )
    {
      v474 = (unsigned __int64)v471 >> 3;
      do
      {
        v475 = __rdtsc();
        v471 -= 8;
        v476 = (__ROR8__(v475, 3) ^ v475) * (unsigned __int128)0x7010008004002001ui64;
        v3922 = *((_QWORD *)&v476 + 1);
        *v473++ = v476 ^ *((_QWORD *)&v476 + 1);
        --v474;
      }
      while ( v474 );
    }
    if ( v471 )
    {
      v477 = __rdtsc();
      v478 = (__ROR8__(v477, 3) ^ v477) * (unsigned __int128)0x7010008004002001ui64;
      v3923 = *((_QWORD *)&v478 + 1);
      v479 = v478 ^ *((_QWORD *)&v478 + 1);
      do
      {
        *(_BYTE *)v473 = v479;
        v473 = (_QWORD *)((char *)v473 + 1);
        v479 >>= 8;
        --v471;
      }
      while ( v471 );
    }
    if ( !v472 )
    {
LABEL_5367:
      v3834[1] = 317;
      KeBugCheckEx(__ROR4__(317, 160), 0x1Aui64, (ULONG_PTR)v207, 0i64, 0i64);
    }
    v480 = __rdtsc();
    v481 = (_BYTE *)(v472 + 2);
    v482 = (_BYTE *)(v472 + 2);
    v483 = (__ROR8__(v480, 3) ^ v480) * (unsigned __int128)0x7010008004002001ui64;
    v3924 = *((_QWORD *)&v483 + 1);
    v3925[0] = v483 ^ *((_QWORD *)&v483 + 1);
    for ( m = 0; m < 0x100; ++m )
      *v482++ = m;
    v485 = 256i64;
    v486 = 0;
    do
    {
      v486 += *((_BYTE *)v3925 + ((-2 - (_BYTE)v472 + (_BYTE)v481) & 7)) + *v481;
      v487 = *(_BYTE *)(v486 + v472 + 2);
      *(_BYTE *)(v486 + v472 + 2) = *v481;
      *v481++ = v487;
      --v485;
    }
    while ( v485 );
    v488 = 256;
    v489 = (_QWORD *)(v472 + 258);
    v490 = 32i64;
    do
    {
      v491 = __rdtsc();
      v488 -= 8;
      v492 = (__ROR8__(v491, 3) ^ v491) * (unsigned __int128)0x7010008004002001ui64;
      v3925[1] = *((_QWORD *)&v492 + 1);
      *v489++ = v492 ^ *((_QWORD *)&v492 + 1);
      --v490;
    }
    while ( v490 );
    if ( v488 )
    {
      v493 = __rdtsc();
      v494 = (__ROR8__(v493, 3) ^ v493) * (unsigned __int128)0x7010008004002001ui64;
      v3925[2] = *((_QWORD *)&v494 + 1);
      v495 = v494 ^ *((_QWORD *)&v494 + 1);
      do
      {
        *(_BYTE *)v489 = v495;
        v489 = (_QWORD *)((char *)v489 + 1);
        v495 >>= 8;
        --v488;
      }
      while ( v488 );
    }
    *((_QWORD *)v207 + 334) = v472;
  }
  v496 = __rdtsc();
  v497 = (__ROR8__(v496, 3) ^ v496) * (unsigned __int128)0x7010008004002001ui64;
  v3925[3] = *((_QWORD *)&v497 + 1);
  if ( !((*((_QWORD *)&v497 + 1) ^ (unsigned __int64)v497) % 0xA) && (((v4344 - 3) & 0xFFFFFFFA) != 0 || v4344 == 8) )
  {
    for ( n = 0; n < 0x10; ++n )
    {
      v511 = ExAllocatePool2(66i64, 64i64, tag);
      v4246[n] = v511;
      if ( !v511 )
        goto LABEL_5368;
    }
    v512 = __rdtsc();
    v513 = __ROR8__(v512, 3);
    v514 = 15;
    v3927 = ((v513 ^ v512) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v515 = ((unsigned int)v3927 ^ (67117057 * ((unsigned int)v513 ^ (unsigned int)v512))) & 0xF;
    v516 = &v4246[v515];
    v517 = *v516;
    memmove(v516, &v4246[(unsigned int)(v515 + 1)], 8i64 * (unsigned int)(15 - v515));
    v518 = (unsigned __int64)&qword_140C0DF08 ^ ((v517 ^ ((v517 ^ 0xE5D49100ui64) >> 4)) >> 4);
    v519 = v518 & 0xF;
    if ( (v518 & 0xF) == 0 )
      v519 = 1;
    v520 = v517;
    do
    {
      v521 = (__int64 *)(v520 + (v518 & 0xF));
      v522 = __rdtsc();
      v523 = v514;
      v524 = (__ROR8__(v522, 3) ^ v522) * (unsigned __int128)0x7010008004002001ui64;
      --v514;
      v3928 = *((_QWORD *)&v524 + 1);
      DWORD2(v524) = (*((_QWORD *)&v524 + 1) ^ (unsigned __int64)v524) % v523;
      v525 = &v4246[DWORD2(v524)];
      v520 = *v525;
      memmove(v525, &v4246[DWORD2(v524) + 1], 8i64 * (v514 - DWORD2(v524)));
      *v521 = v520;
      v518 ^= (v520 ^ ((v520 ^ 0x1E5200ui64) >> 4)) >> 4;
      --v519;
    }
    while ( v519 );
    v538 = ExAllocatePool2(66i64, 64i64, tag);
    v207 = (_BYTE *)v3792;
    if ( !v538 )
    {
LABEL_5368:
      v3834[22] = 317;
      KeBugCheckEx(__ROR4__(317, 160), 0x19ui64, (ULONG_PTR)v207, 0i64, 0i64);
    }
    *(_BYTE *)v538 = 19;
    *(_BYTE *)(v538 + 1) = 1;
    *(_WORD *)(v538 + 2) = 0;
    *(_QWORD *)(v538 + 24) = sub_1403E1090;
    *(_QWORD *)(v538 + 32) = v517;
    *(_QWORD *)(v538 + 56) = 0i64;
    *(_QWORD *)(v538 + 16) = 0i64;
    *((_QWORD *)v207 + 339) = v538;
  }
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v539 = __rdtsc();
  v540 = (__ROR8__(v539, 3) ^ v539) * (unsigned __int128)0x7010008004002001ui64;
  v3931 = *((_QWORD *)&v540 + 1);
  if ( (*((_QWORD *)&v540 + 1) ^ (unsigned __int64)v540) % 0xA < 5 )
    *((_DWORD *)v207 + 612) |= 0x1000000u;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v548 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v544 + 136), v541);
  v549 = v548;
  if ( !v548 )
  {
LABEL_789:
    ++*((_DWORD *)v207 + 646);
    return 0;
  }
  v550 = v547;
  v551 = (_QWORD *)v548;
  v558 = v544 - v547;
  v559 = (struct _KTIMER *)(v549 + (unsigned int)v547);
  Timer = v559;
  p_WaitListHead = &v559[2].Header.WaitListHead;
  if ( v558 >= 8 )
  {
    v561 = (unsigned __int64)v558 >> 3;
    do
    {
      v558 -= 8;
      v562 = __rdtsc();
      v563 = (__ROR8__(v562, 3) ^ v562) * (unsigned __int128)0x7010008004002001ui64;
      v3936 = *((_QWORD *)&v563 + 1);
      p_WaitListHead->Flink = (_LIST_ENTRY *)(v563 ^ *((_QWORD *)&v563 + 1));
      p_WaitListHead = (_LIST_ENTRY *)((char *)p_WaitListHead + 8);
      --v561;
    }
    while ( v561 );
    v559 = Timer;
  }
  if ( v558 )
  {
    v564 = __rdtsc();
    v565 = (__ROR8__(v564, 3) ^ v564) * (unsigned __int128)0x7010008004002001ui64;
    v3937 = *((_QWORD *)&v565 + 1);
    v566 = v565 ^ *((_QWORD *)&v565 + 1);
    do
    {
      LOBYTE(p_WaitListHead->Flink) = v566;
      p_WaitListHead = (_LIST_ENTRY *)((char *)p_WaitListHead + 1);
      v566 >>= 8;
      --v558;
    }
    while ( v558 );
  }
  if ( !v559 )
    return 0;
  *((_QWORD *)v207 + 241) = v559;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v567 = __rdtsc();
  v568 = (__ROR8__(v567, 3) ^ v567) * (unsigned __int128)0x7010008004002001ui64;
  v3938 = *((_QWORD *)&v568 + 1);
  if ( ((unsigned __int64)v568 ^ *((_QWORD *)&v568 + 1)) % 0xA >= 3 )
  {
    v587 = (ULONG_PTR)&v559[1];
    v3859 = v587;
  }
  else
  {
    v569 = *((unsigned int *)v207 + 516);
    v570 = __rdtsc();
    v571 = __ROR8__(v570, 3);
    v3939 = ((v571 ^ v570) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v572 = ((unsigned __int16)(8193 * (v571 ^ v570)) ^ (unsigned __int16)v3939) & 0x7FF;
    v573 = __rdtsc();
    v574 = (__ROR8__(v573, 3) ^ v573) * (unsigned __int128)0x7010008004002001ui64;
    v3940 = *((_QWORD *)&v574 + 1);
    v575 = (*((_QWORD *)&v574 + 1) ^ (unsigned __int64)v574) % (unsigned int)(v572 + 1);
    v576 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v572 + 72), v569);
    v577 = v576;
    if ( !v576 )
      goto LABEL_789;
    v578 = v575;
    v579 = (_QWORD *)v576;
    if ( (unsigned int)v575 >= 8 )
    {
      v580 = (unsigned __int64)(unsigned int)v575 >> 3;
      do
      {
        v581 = __rdtsc();
        v578 -= 8;
        v582 = (__ROR8__(v581, 3) ^ v581) * (unsigned __int128)0x7010008004002001ui64;
        v3941 = *((_QWORD *)&v582 + 1);
        *v579++ = v582 ^ *((_QWORD *)&v582 + 1);
        --v580;
      }
      while ( v580 );
    }
    if ( v578 )
    {
      v583 = __rdtsc();
      v584 = (__ROR8__(v583, 3) ^ v583) * (unsigned __int128)0x7010008004002001ui64;
      v3942 = *((_QWORD *)&v584 + 1);
      v585 = v584 ^ *((_QWORD *)&v584 + 1);
      do
      {
        *(_BYTE *)v579 = v585;
        v579 = (_QWORD *)((char *)v579 + 1);
        v585 >>= 8;
        --v578;
      }
      while ( v578 );
    }
    v586 = v572 - v575;
    v587 = v577 + (unsigned int)v575;
    v3859 = v587;
    v588 = (_QWORD *)(v587 + 72);
    if ( v586 >= 8 )
    {
      v589 = (unsigned __int64)v586 >> 3;
      do
      {
        v590 = __rdtsc();
        v586 -= 8;
        v591 = (__ROR8__(v590, 3) ^ v590) * (unsigned __int128)0x7010008004002001ui64;
        v3943 = *((_QWORD *)&v591 + 1);
        *v588++ = v591 ^ *((_QWORD *)&v591 + 1);
        --v589;
      }
      while ( v589 );
      v587 = v3859;
    }
    if ( v586 )
    {
      v592 = __rdtsc();
      v593 = (__ROR8__(v592, 3) ^ v592) * (unsigned __int128)0x7010008004002001ui64;
      v3944 = *((_QWORD *)&v593 + 1);
      v594 = v593 ^ *((_QWORD *)&v593 + 1);
      do
      {
        *(_BYTE *)v588 = v594;
        v588 = (_QWORD *)((char *)v588 + 1);
        v594 >>= 8;
        --v586;
      }
      while ( v586 );
    }
    if ( !v587 )
      return 0;
  }
  *((_QWORD *)v207 + 242) = v587;
  if ( v4344 == 4 )
  {
    v595 = *((unsigned int *)v207 + 516);
    v596 = __rdtsc();
    v597 = __ROR8__(v596, 3);
    v3945 = ((v597 ^ v596) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v598 = ((unsigned __int16)(8193 * (v597 ^ v596)) ^ (unsigned __int16)v3945) & 0x7FF;
    v599 = __rdtsc();
    v600 = (__ROR8__(v599, 3) ^ v599) * (unsigned __int128)0x7010008004002001ui64;
    v3946 = *((_QWORD *)&v600 + 1);
    v601 = (*((_QWORD *)&v600 + 1) ^ (unsigned __int64)v600) % (unsigned int)(v598 + 1);
    v602 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v598 + 88), v595);
    if ( !v602 )
    {
      ++*((_DWORD *)v207 + 646);
      goto LABEL_5369;
    }
    v603 = v601;
    v604 = (_QWORD *)v602;
    if ( (unsigned int)v601 >= 8 )
    {
      v605 = (unsigned __int64)(unsigned int)v601 >> 3;
      do
      {
        v606 = __rdtsc();
        v603 -= 8;
        v607 = (__ROR8__(v606, 3) ^ v606) * (unsigned __int128)0x7010008004002001ui64;
        v3947 = *((_QWORD *)&v607 + 1);
        *v604++ = v607 ^ *((_QWORD *)&v607 + 1);
        --v605;
      }
      while ( v605 );
    }
    if ( v603 )
    {
      v608 = __rdtsc();
      v609 = (__ROR8__(v608, 3) ^ v608) * (unsigned __int128)0x7010008004002001ui64;
      v3948 = *((_QWORD *)&v609 + 1);
      v610 = v609 ^ *((_QWORD *)&v609 + 1);
      do
      {
        *(_BYTE *)v604 = v610;
        v604 = (_QWORD *)((char *)v604 + 1);
        v610 >>= 8;
        --v603;
      }
      while ( v603 );
    }
    v611 = v598 - v601;
    v612 = v602 + (unsigned int)v601;
    v613 = (_QWORD *)(v612 + 88);
    if ( v611 >= 8 )
    {
      v614 = (unsigned __int64)v611 >> 3;
      do
      {
        v615 = __rdtsc();
        v611 -= 8;
        v616 = (__ROR8__(v615, 3) ^ v615) * (unsigned __int128)0x7010008004002001ui64;
        v3949 = *((_QWORD *)&v616 + 1);
        *v613++ = v616 ^ *((_QWORD *)&v616 + 1);
        --v614;
      }
      while ( v614 );
    }
    if ( v611 )
    {
      v617 = __rdtsc();
      v618 = (__ROR8__(v617, 3) ^ v617) * (unsigned __int128)0x7010008004002001ui64;
      v3950 = *((_QWORD *)&v618 + 1);
      v619 = v618 ^ *((_QWORD *)&v618 + 1);
      do
      {
        *(_BYTE *)v613 = v619;
        v613 = (_QWORD *)((char *)v613 + 1);
        v619 >>= 8;
        --v611;
      }
      while ( v611 );
    }
    if ( !v612 )
      goto LABEL_5369;
    *((_QWORD *)v207 + 316) = v612;
    *((_DWORD *)v207 + 612) |= 8u;
    v620 = __rdtsc();
    v621 = ((__ROR8__(v620, 3) ^ v620) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    *((_QWORD *)v207 + 307) = 0i64;
    v622 = *((_QWORD *)v207 + 202);
    v3951 = v621;
    PsEnumProcessThreads(
      *(_QWORD *)(*((_QWORD *)v207 + 214)
                + *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + v622)
                + *((_QWORD *)v207 + 210)),
      sub_140B32730,
      v207);
    if ( !*((_QWORD *)v207 + 307) )
    {
LABEL_5369:
      v3834[23] = 317;
      KeBugCheckEx(__ROR4__(317, 160), 0x16ui64, (ULONG_PTR)v207, 0i64, 0i64);
    }
    *((_QWORD *)v207 + 317) = KiDispatchCallout;
    *((_QWORD *)v207 + 318) = xHalTimerWatchdogStop;
    *((_DWORD *)v207 + 597) = -1115657675;
  }
  else if ( v4344 == 5 )
  {
    v623 = *((unsigned int *)v207 + 516);
    v624 = __rdtsc();
    v625 = __ROR8__(v624, 3);
    v3952 = ((v625 ^ v624) * (unsigned __int128)0x7010008004002001ui64) >> 64;
    v626 = ((unsigned __int16)(8193 * (v625 ^ v624)) ^ (unsigned __int16)v3952) & 0x7FF;
    v627 = __rdtsc();
    v628 = (__ROR8__(v627, 3) ^ v627) * (unsigned __int128)0x7010008004002001ui64;
    v3953 = *((_QWORD *)&v628 + 1);
    v629 = (*((_QWORD *)&v628 + 1) ^ (unsigned __int64)v628) % (unsigned int)(v626 + 1);
    v630 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v626 + 80), v623);
    if ( v630 )
    {
      v632 = v629;
      v633 = (_QWORD *)v630;
      if ( (unsigned int)v629 >= 8 )
      {
        v634 = (unsigned __int64)(unsigned int)v629 >> 3;
        do
        {
          v635 = __rdtsc();
          v632 -= 8;
          v636 = (__ROR8__(v635, 3) ^ v635) * (unsigned __int128)0x7010008004002001ui64;
          v3954 = *((_QWORD *)&v636 + 1);
          *v633++ = v636 ^ *((_QWORD *)&v636 + 1);
          --v634;
        }
        while ( v634 );
      }
      if ( v632 )
      {
        v637 = __rdtsc();
        v638 = (__ROR8__(v637, 3) ^ v637) * (unsigned __int128)0x7010008004002001ui64;
        v3955 = *((_QWORD *)&v638 + 1);
        v639 = v638 ^ *((_QWORD *)&v638 + 1);
        do
        {
          *(_BYTE *)v633 = v639;
          v633 = (_QWORD *)((char *)v633 + 1);
          v639 >>= 8;
          --v632;
        }
        while ( v632 );
      }
      v640 = v626 - v629;
      v631 = (_DWORD *)(v630 + (unsigned int)v629);
      v641 = v631 + 20;
      if ( v640 >= 8 )
      {
        v642 = (unsigned __int64)v640 >> 3;
        do
        {
          v643 = __rdtsc();
          v640 -= 8;
          v644 = (__ROR8__(v643, 3) ^ v643) * (unsigned __int128)0x7010008004002001ui64;
          v3956 = *((_QWORD *)&v644 + 1);
          *v641++ = v644 ^ *((_QWORD *)&v644 + 1);
          --v642;
        }
        while ( v642 );
      }
      if ( v640 )
      {
        v645 = __rdtsc();
        v646 = (__ROR8__(v645, 3) ^ v645) * (unsigned __int128)0x7010008004002001ui64;
        v3957 = *((_QWORD *)&v646 + 1);
        v647 = v646 ^ *((_QWORD *)&v646 + 1);
        do
        {
          *(_BYTE *)v641 = v647;
          v641 = (_QWORD *)((char *)v641 + 1);
          v647 >>= 8;
          --v640;
        }
        while ( v640 );
      }
    }
    else
    {
      ++*((_DWORD *)v207 + 646);
      v631 = 0i64;
    }
    *((_QWORD *)v207 + 307) = v631;
    if ( !v631 )
    {
      v3834[24] = 317;
      KeBugCheckEx(__ROR4__(317, 160), 0x18ui64, (ULONG_PTR)v207, 0i64, 0i64);
    }
    *v631 = 0;
    v648 = *((_QWORD *)v207 + 307);
    v649 = *(_QWORD *)(a4 + 24);
    *(_OWORD *)(v648 + 8) = *(_OWORD *)v649;
    *(_OWORD *)(v648 + 24) = *(_OWORD *)(v649 + 16);
    *(_OWORD *)(v648 + 40) = *(_OWORD *)(v649 + 32);
    *(_OWORD *)(v648 + 56) = *(_OWORD *)(v649 + 48);
    v650 = KeAcquireSpinLockRaiseToDpc(&KiHardwareTriggerLock);
    _InterlockedExchange64((volatile __int64 *)(v649 + 24), (__int64)sub_1403ED400);
    *(_QWORD *)(v649 + 32) = v648;
    KeReleaseSpinLock(&KiHardwareTriggerLock, v650);
    v651 = *((_QWORD *)v207 + 307);
    *((_OWORD *)v207 + 154) = *(_OWORD *)(v651 + 8);
    *((_OWORD *)v207 + 155) = *(_OWORD *)(v651 + 24);
    *((_OWORD *)v207 + 156) = *(_OWORD *)(v651 + 40);
    *((_OWORD *)v207 + 157) = *(_OWORD *)(v651 + 56);
  }
  v652 = __rdtsc();
  v653 = (__ROR8__(v652, 3) ^ v652) * (unsigned __int128)0x7010008004002001ui64;
  v3958 = *((_QWORD *)&v653 + 1);
  if ( !(((unsigned __int64)v653 ^ *((_QWORD *)&v653 + 1)) % 0xA) )
    *((_DWORD *)v207 + 612) |= 2u;
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v654 = __rdtsc();
  v655 = (__ROR8__(v654, 3) ^ v654) * (unsigned __int128)0x7010008004002001ui64;
  v3959 = *((_QWORD *)&v655 + 1);
  if ( ((unsigned __int64)v655 ^ *((_QWORD *)&v655 + 1)) % 0xA < 7 )
  {
    v656 = *((_DWORD *)v207 + 612);
    if ( (v656 & 0x40000000) == 0 )
      *((_DWORD *)v207 + 612) = v656 | 0x80;
  }
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  v657 = __rdtsc();
  v658 = (__ROR8__(v657, 3) ^ v657) * (unsigned __int128)0x7010008004002001ui64;
  v3960 = *((_QWORD *)&v658 + 1);
  if ( ((unsigned __int64)v658 ^ *((_QWORD *)&v658 + 1)) % 0xA < 7 )
  {
    v659 = __rdtsc();
    v660 = (__ROR8__(v659, 3) ^ v659) * (unsigned __int128)0x7010008004002001ui64;
    v3961 = *((_QWORD *)&v660 + 1);
    if ( ((unsigned __int64)v660 ^ *((_QWORD *)&v660 + 1)) % 0xA >= 7 )
    {
      v686 = ExAllocateTimer(0i64, 0i64, 8i64);
      if ( v686 )
      {
        *((_QWORD *)v207 + 319) = v686;
        v687 = __rdtsc();
        v3968 = ((__ROR8__(v687, 3) ^ v687) * (unsigned __int128)0x7010008004002001ui64) >> 64;
        ExSetTimer(v686);
        goto LABEL_889;
      }
    }
    else
    {
      v661 = *((unsigned int *)v207 + 516);
      v662 = __rdtsc();
      v663 = __ROR8__(v662, 3);
      v3962 = ((v663 ^ v662) * (unsigned __int128)0x7010008004002001ui64) >> 64;
      v664 = ((unsigned __int16)(8193 * (v663 ^ v662)) ^ (unsigned __int16)v3962) & 0x7FF;
      v665 = __rdtsc();
      v666 = (__ROR8__(v665, 3) ^ v665) * (unsigned __int128)0x7010008004002001ui64;
      v3963 = *((_QWORD *)&v666 + 1);
      v667 = (*((_QWORD *)&v666 + 1) ^ (unsigned __int64)v666) % (unsigned int)(v664 + 1);
      v668 = (*((__int64 (__fastcall **)(__int64, _QWORD, __int64))ExAllocatePool2))(66i64, (unsigned int)(v664 + 24), v661);
      if ( !v668 )
      {
        ++*((_DWORD *)v207 + 646);
        goto LABEL_5371;
      }
      v669 = v667;
      v670 = (_QWORD *)v668;
      if ( (unsigned int)v667 >= 8 )
      {
        v671 = (unsigned __int64)(unsigned int)v667 >> 3;
        do
        {
          v672 = __rdtsc();
          v669 -= 8;
          v673 = (__ROR8__(v672, 3) ^ v672) * (unsigned __int128)0x7010008004002001ui64;
          v3964 = *((_QWORD *)&v673 + 1);
          *v670++ = v673 ^ *((_QWORD *)&v673 + 1);
          --v671;
        }
        while ( v671 );
      }
      if ( v669 )
      {
        v674 = __rdtsc();
        v675 = (__ROR8__(v674, 3) ^ v674) * (unsigned __int128)0x7010008004002001ui64;
        v3965 = *((_QWORD *)&v675 + 1);
        v676 = v675 ^ *((_QWORD *)&v675 + 1);
        do
        {
          *(_BYTE *)v670 = v676;
          v670 = (_QWORD *)((char *)v670 + 1);
          v676 >>= 8;
          --v669;
        }
        while ( v669 );
      }
      v677 = v664 - v667;
      v678 = (struct _KEVENT *)(v668 + (unsigned int)v667);
      v679 = v678 + 1;
      if ( v677 >= 8 )
      {
        v680 = (unsigned __int64)v677 >> 3;
        do
        {
          v681 = __rdtsc();
          v677 -= 8;
          v682 = (__ROR8__(v681, 3) ^ v681) * (unsigned __int128)0x7010008004002001ui64;
          v3966 = *((_QWORD *)&v682 + 1);
          *(_QWORD *)&v679->Header.Lock = v682 ^ *((_QWORD *)&v682 + 1);
          v679 = (struct _KEVENT *)((char *)v679 + 8);
          --v680;
        }
        while ( v680 );
      }
      if ( v677 )
      {
        v683 = __rdtsc();
        v684 = (__ROR8__(v683, 3) ^ v683) * (unsigned __int128)0x7010008004002001ui64;
        v3967 = *((_QWORD *)&v684 + 1);
        v685 = v684 ^ *((_QWORD *)&v684 + 1);
        do
        {
          v679->Header.Type = v685;
          v679 = (struct _KEVENT *)((char *)v679 + 1);
          v685 >>= 8;
          --v677;
        }
        while ( v677 );
      }
      if ( v678 )
      {
        KeInitializeEvent(v678, NotificationEvent, 0);
        *((_QWORD *)v207 + 319) = v678;
        goto LABEL_889;
      }
    }
LABEL_5371:
    v3834[25] = 317;
    KeBugCheckEx(__ROR4__(317, 160), 0x17ui64, (ULONG_PTR)v207, 0i64, 0i64);
  }
LABEL_889:
  v688 = __rdtsc();
  v689 = (__ROR8__(v688, 3) ^ v688) * (unsigned __int128)0x7010008004002001ui64;
  v3969 = *((_QWORD *)&v689 + 1);
  if ( ((unsigned __int64)v689 ^ *((_QWORD *)&v689 + 1)) % 0xA < 2 && *((int *)v207 + 612) >= 0 )
    *((_DWORD *)v207 + 613) |= 0x200u;
  v690 = Size;
  v691 = &v207[v3800];
  v692 = (int)Src;
  memmove(v691, Src, Size);
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  if ( Size )
    *(_WORD *)&v691[(unsigned int)KeGuardDispatchICall - (unsigned int)Src] = -7937;
  if ( v690 )
    v691[(unsigned int)KeGuardCheckICall - v692] = -61;
  *((_QWORD *)v207 + 281) = 0x140000000ui64;
  v693 = RtlImageNtHeader(0x140000000ui64);
  *((_QWORD *)v207 + 283) = v693;
  *((_QWORD *)v207 + 282) = 0x140000000i64 + *(unsigned int *)(v693 + 80);
  *((_DWORD *)v207 + 555) = dword_140D815E0;
  *((_DWORD *)v207 + 556) = dword_140D81618;
  *((_DWORD *)v207 + 557) = KeIstStackSize;
  if ( (_DWORD)qword_140D815E8 != 8 )
  {
    v3834[26] = 317;
    KeBugCheckEx(__ROR4__(317, 160), 4ui64, 0i64, qword_140D815E8, 8ui64);
  }
  CurrentIrql = KeGetCurrentIrql();
  __writecr8(0xFui64);
  *((_QWORD *)v207 + 279) = *(_QWORD *)(*((unsigned int *)v207 + 556)
                                      + *(_QWORD *)(*((__int64 (__fastcall **)(__int64))KiGetInterruptObjectAddress))(254i64));
  __writecr8(CurrentIrql);
  *((_WORD *)v207 + 1084) = -12472;
  IdtBase = KeGetPcr()->IdtBase;
  *(_KIDTENTRY64 *)(v207 + 2120) = IdtBase[1];
  *(_KIDTENTRY64 *)(v207 + 2136) = IdtBase[2];
  *(_KIDTENTRY64 *)(v207 + 2152) = IdtBase[18];
  v708 = (*((__int64 (__fastcall **)(__int64, __int64, _QWORD))ExAllocatePool2))(64i64, 432i64, tag);
  *((_QWORD *)v207 + 284) = v708;
  if ( !v708 )
    return 0;
  *((_QWORD *)v207 + 284) = (v708 + 128) & 0xFFFFFFFFFFFFFF80ui64;
  v207[2174] = 72;
  v207[2175] = -121;
  v207[2176] = 12;
  v207[2177] = 36;
  v207[2178] = -127;
  v207[2179] = 100;
  v207[2180] = 36;
  v207[2181] = 16;
  v207[2182] = -1;
  v207[2183] = -2;
  v207[2184] = -1;
  v207[2185] = -1;
  v207[2186] = 72;
  v207[2187] = -49;
  *((_WORD *)v207 + 1086) = 1295;
  v207[2170] = -61;
  v709 = 0;
  v710 = *((_QWORD *)v207 + 248);
  if ( *(_BYTE *)(v710 + *((_QWORD *)v207 + 206)) == v207[1656] )
  {
    v711 = __cpuid(0, 0);
    v4120 = ECX(v711);
    v712 = *((_QWORD *)v207 + 205);
    v4118 = EAX(v711);
    v4119 = EBX(v711);
    v4121 = EDX(v711);
    v713 = *(_BYTE *)(v710 + v712);
    v714 = *(_BYTE *)(v710 + *((_QWORD *)v207 + 204));
    if ( v4118 >= 7 )
    {
      v717 = __cpuid(7, 0);
      v716 = ECX(v717);
      v715 = EDX(v717);
      v4118 = EAX(v717);
      v4119 = EBX(v717);
      if ( (v4119 & 0x800) != 0 )
        v709 = 1;
      v4120 = v716;
      v4121 = v715;
    }
    if ( (*(_BYTE *)(v710 + *((_QWORD *)v207 + 203)) != 6
       || (v713 != 60 || v714 != 3)
       && (v713 != 63 || v714 != 2)
       && (v713 != 69 || v714 != 1)
       && (v713 != 70 || v714 != 1))
      && v709 )
    {
      v207[2171] |= 4u;
    }
  }
  if ( (unsigned int)KeKvaShadowingActive() )
    v207[2171] |= 8u;
  v207[2188] = 72;
  v207[2189] = -125;
  v207[2190] = 44;
  v207[2191] = 36;
  v207[2192] = 2;
  v207[2193] = 72;
  v207[2194] = -49;
  v718 = KUSER_SHARED_DATA.ProcessorFeatures[21] != 0;
  if ( (NtBuildNumber & 0xF0000000) == 0xC0000000 )
    v718 = 1;
  if ( (*((_DWORD *)v207 + 612) & 0x10000000) == 0 )
  {
   
  }
  if ( dword_140D81088 )
  {
   
  }
  v736 = 0;
  if ( KUSER_SHARED_DATA.ProcessorFeatures[21] && (v207[2171] & 4) != 0 )
    v736 = 1;
  if ( (NtBuildNumber & 0xF0000000) == 0xC0000000 || v736 )
  {
    v737 = *((_DWORD *)v207 + 612);
    if ( (v737 & 0x10000000) == 0 && v737 >= 0 && *((_DWORD *)v207 + 526) != 7 )
    {
      v738 = *((_DWORD *)v207 + 613);
      if ( (v738 & 0x10000) == 0 )
      {

        if ( random()< 3 )
        {
          v741 = qword_140D81080;
          if ( !qword_140D81080 )
          {
            v755 = 64i64;
            v756 = 5248;
            v757 = (_QWORD *)(*((__int64 (__fastcall **)(__int64, __int64, __int64))ExAllocatePool2))(64i64, 5248i64, tag);
            qword_140D81080 = v757;
            if ( !v757 )
              return 0;
            v758 = 656i64;
            do
            {
              *v757 = 0i64;
              v756 -= 8;
              ++v757;
              --v758;
            }
            while ( v758 );
            for ( ; v756; --v756 )
            {
              *(_BYTE *)v757 = 0;
              v757 = (_QWORD *)((char *)v757 + 1);
            }
            PhysicalAddress = MmGetPhysicalAddress(qword_140D81080);
            v760 = (unsigned __int64 *)qword_140D81080;
            v761 = 512;
            v762 = IdtBase;
            *((_QWORD *)qword_140D81080 + 643) = (unsigned __int64)PhysicalAddress.QuadPart >> 12;
            do
            {
              v761 -= 8;
              *v760 = v762->Alignment;
              v762 = (_KIDTENTRY64 *)((char *)v762 + 8);
              ++v760;
              --v755;
            }
            while ( v755 );
            for ( ; v761; --v761 )
            {
              OffsetLow = v762->OffsetLow;
              v762 = (_KIDTENTRY64 *)((char *)v762 + 1);
              *(_BYTE *)v760 = OffsetLow;
              v760 = (unsigned __int64 *)((char *)v760 + 1);
            }
            v764 = 512;
            v765 = (char *)qword_140D81080 + 512;
            v766 = 64i64;
            do
            {
              v764 -= 8;
              *(_QWORD *)v765 = IdtBase->Alignment;
              IdtBase = (_KIDTENTRY64 *)((char *)IdtBase + 8);
              v765 += 8;
              --v766;
            }
            while ( v766 );
            for ( ; v764; --v764 )
            {
              v767 = IdtBase->OffsetLow;
              IdtBase = (_KIDTENTRY64 *)((char *)IdtBase + 1);
              *v765++ = v767;
            }
            v741 = qword_140D81080;
            *((_WORD *)qword_140D81080 + 34) &= ~0x8000u;
            v741[32] = (_WORD)v741;
            v741[35] = WORD1(v741);
            *((_DWORD *)v741 + 18) = HIDWORD(v741);
            v738 = *((_DWORD *)v207 + 613);
          }
          v768 = (unsigned int)KiMceThunk - (_DWORD)Src;
          *((_DWORD *)v207 + 613) = v738 | 0x8000;
          *((_QWORD *)v207 + 280) = v741;
          *((_DWORD *)v207 + 573) = (_DWORD)v691 - (_DWORD)v207 + v768;
          v207[2195] = 72;
          v207[2196] = -125;
          v207[2197] = -20;
          v207[2198] = 40;
          v207[2199] = -1;
          v207[2200] = 17;
          v207[2201] = 72;
          v207[2202] = -125;
          v207[2203] = -60;
          v207[2204] = 40;
          v207[2205] = -61;
        }
      }
    }
  }
  v769 = *((_DWORD *)v207 + 612);
  if ( v769 < 0 )
    *((_DWORD *)v207 + 612) = v769 | 0x8000000;
  if ( (_DWORD)KeNumberProcessors_0 == 1 )
    *((_DWORD *)v207 + 612) |= 0x40u;
  if ( (*(_BYTE *)((*((unsigned int *)v207 + 599) ^ 0xBC2A27DBi64) - 0x88000000000i64) & 2) != 0 )
    *((_DWORD *)v207 + 505) += 4096;
  v875 = *((_DWORD *)v207 + 526) == 7;
  v3981 = v207;
  if ( v875 )
    goto LABEL_1166;
  v4259[0] = (ULONG_PTR)ExQueueWorkItem;
  v4260 = 0i64;
  v4259[1] = (ULONG_PTR)ExpWorkerThread;
  v4259[2] = (ULONG_PTR)KiDebugTrapOrFault;
  v4259[3] = (ULONG_PTR)KiExceptionDispatch;
  v4259[4] = (ULONG_PTR)KiDispatchException;
  v4259[5] = 0i64;
  v4267 = RtlDispatchException;
  v4268 = KeContextToKframes;
  v4270 = sub_1403E1170;
  v4271 = KeAcquireSpinLockRaiseToDpc;
  v4272 = KeReleaseSpinLock;
  v4273 = KeProcessorGroupAffinity;
  v4274 = KeSetSystemGroupAffinityThread;
  v4275 = KeRevertToUserGroupAffinityThread;
  v4276 = (__int64 (__fastcall *)())MmGetSessionIdEx;
  v4277 = sub_14066A740;
  v4278 = sub_1403E00B0;
  v4279 = memmove;
  v4280 = qword_1403ED4F0;
  v4281 = KiCommitThreadWait;
  v4282 = KeDelayExecutionThread;
  v4283 = KeWaitForSingleObject;
  v4284 = KeRemovePriQueue;
  v4285 = KiAttemptFastRemovePriQueue;
  v4286 = KiExitThreadWait;
  v4287 = EtwTraceThreadWorkItem;
  v4288 = ExIsSafeWorkItem;
  v4289 = sub_1403ED390;
  v4290 = KeIpiGenericCall;
  v4291 = _guard_dispatch_icall_fptr[0];
  v4292 = guard_wrap_icall_retpoline_exit;
  v4293 = guard_wrap_icall_jmp;
  v4294 = PerfInfoLogIpiSend;
  v4295 = PerfInfoLogIpiReceive;
  v4296 = ExGetHandlePointer;
  v4261 = 0i64;
  v4262 = 0i64;
  v4263 = 0i64;
  v4264 = 0i64;
  v4265 = 0i64;
  v4266 = 0i64;
  v4269 = 0i64;
  v770 = 0i64;
  v771 = 0;
  v3797 = 0;
  LODWORD(v3801) = 0;
  while ( 2 )
  {
    v772 = v4259[v770];
    v3792 = v772;
    if ( !v772 )
      goto LABEL_1137;
    RtlPcToFileHeader(v772, &v3982);
    v773 = RtlImageNtHeader(v3982);
    v774 = (_DWORD *)(*((__int64 (__fastcall **)(__int64, ULONG_PTR, _QWORD))RtlSectionTableFromVirtualAddress))(
                       v773,
                       v3982,
                       (unsigned int)(v772 - v3982));
    if ( v774 )
    {
      if ( *v774 == 1414090313 && v774[1] == 1195525195 )
      {
        if ( (*((_DWORD *)v207 + 613) & 0x2000) == 0 )
          goto LABEL_5373;
      }
      else if ( (v774[9] & 0x2000000) != 0 || (unsigned int)MmImageSectionPagable() )
      {
LABEL_5373:
        v3835[1] = 317;
        KeBugCheckEx(__ROR4__(317, 160), 1ui64, v770, v772, v3982);
      }
    }
    v3796 = 0;
    v775 = RtlLookupFunctionTable(v772, &v4229, v3835);
    v4227 = v775;
    if ( !v775 )
    {
      v783 = v4231;
      v777 = v4228;
      goto LABEL_1051;
    }
    v4232 = 0i64;
    if ( v4147 != v4229 )
    {
      v777 = v4228;
      goto LABEL_1049;
    }
    v776 = (_DWORD *)v4148;
    v4233 = 0i64;
    v4234 = v4149;
    v4235 = 0;
    v4232 = v4148;
    v777 = RtlLookupFunctionEntry(v772, &v4229, 0i64);
    v4228 = v777;
    if ( !v777 )
      goto LABEL_1044;
    v778 = 0;
    v779 = *v776 - 1;
    if ( v779 < 0 )
      goto LABEL_1044;
    while ( 2 )
    {
      v780 = (v779 + v778) >> 1;
      v781 = v777 - v4229 - v776[2 * v780 + 2];
      if ( v781 < 0 )
      {
        if ( !v780 )
          goto LABEL_1044;
        v779 = v780 - 1;
LABEL_1043:
        if ( v779 < v778 )
          goto LABEL_1044;
        continue;
      }
      break;
    }
    if ( v781 > 0 )
    {
      v778 = v780 + 1;
      goto LABEL_1043;
    }
    v782 = v4233;
    if ( v779 >= v778 )
      v782 = (__int64)&v776[2 * ((v779 + v778) >> 1) + 2];
    v4233 = v782;
LABEL_1044:
    v775 = v4227;
    v771 = v3801;
LABEL_1049:
    v783 = v3983;
    v4226 = v772;
    v4231 = v3983;
    v3835[0] /= 0xCu;
    v3982 = v4229;
    v4230 = v775 + 12i64 * (unsigned int)v3835[0];
LABEL_1051:
    while ( v775 && v775 != v4230 )
    {
      if ( v4232 )
      {
        if ( !v777 )
          break;
        if ( v4233 )
        {
          v784 = *(_DWORD *)(v4233 + 4);
          if ( (v784 & 1) != 0 )
          {
            *v783 = v4229 + (v784 & 0xFFFFFFFE);
            v4233 = 0i64;
          }
          else
          {
            v785 = (unsigned int)(v4235 + v784);
            v786 = (unsigned int)v785;
            v787 = v785 + 4;
            if ( v787 < v786 || v787 > v4234 )
            {
              v3835[2] = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0x12ui64, v4232, v4229, v786);
            }
            v788 = *(_DWORD *)(v4232 + v786);
            v4235 += 4;
            v4233 &= -(__int64)((v788 & 1) != 0);
            if ( (v788 & 1) != 0 )
              v788 &= ~1u;
            *v783 = v4229 + v788;
          }
        }
        else
        {
          *v783 = v777;
          v4228 = 0i64;
        }
      }
      else
      {
        while ( 1 )
        {
          v789 = v775;
          v790 = RtlpConvertFunctionEntry(v775, v4229, v777);
          v791 = RtlpSameFunction(v790, v4229, v4226);
          v775 = v4227 + 12;
          v4227 += 12i64;
          if ( v791 )
            break;
          if ( v775 == v4230 )
            goto LABEL_1066;
        }
        *v4231 = v789;
      }
      _disable();
      if ( !(_BYTE)KdDebuggerNotPresent )
      {
        while ( 1 )
          ;
      }
      _enable();
      v801 = *((unsigned int *)v207 + 585);
      v3796 = 1;
      v802 = *((unsigned int *)v207 + 505);
      v803 = v3982 + *(unsigned int *)v3983[0];
      v804 = *(_DWORD *)(v3983[0] + 4) - *(_DWORD *)v3983[0];
      v805 = v802 + 48;
      if ( (unsigned int)(v802 + 48) <= *((_DWORD *)v207 + 647) )
      {
        v806 = (__int64)v207;
        *((_DWORD *)v207 + 505) = v805;
      }
      else
      {
        v806 = sub_140B0F020(v207, v805, v801);
        if ( !v806 )
          return 0;
        v807 = *((_DWORD *)v207 + 612);
        if ( (v807 & 4) == 0 )
        {
          v808 = *((_DWORD *)v207 + 505);
          v809 = *((_QWORD *)v207 + 249);
          v810 = (v807 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
          if ( v808 >= 8 )
          {
            v811 = (unsigned __int64)v808 >> 3;
            do
            {
              *(_QWORD *)v207 = 0i64;
              v808 -= 8;
              v207 += 8;
              --v811;
            }
            while ( v811 );
          }
          for ( ; v808; --v808 )
            *v207++ = 0;
          v812 = *(_DWORD *)(v806 + 2340);
          *(_DWORD *)(v806 + 2340) = v810;
          if ( v810 == 3 )
          {
            (*(void (__fastcall **)(__int64))(v806 + 872))(v809);
          }
          else if ( (*(_DWORD *)(v806 + 2448) & 0x10000000) != 0 || !v810 )
          {
            (*(void (__fastcall **)(__int64))(v806 + 248))(v809);
          }
          else
          {
            (*(void (__fastcall **)(__int64, _QWORD))(v806 + 552))(v809 - 8, *(_QWORD *)(v809 - 8));
          }
          *(_DWORD *)(v806 + 2340) = v812;
        }
        *(_DWORD *)(v806 + 2448) &= ~4u;
      }
      ++*(_DWORD *)(v806 + 2060);
      v813 = (__int64 *)(v806 + v802);
      v814 = 48;
      v3798 = (__int64 *)(v806 + v802);
      v815 = (_QWORD *)(v806 + v802);
      v816 = 6i64;
      do
      {
        *v815 = 0i64;
        v814 -= 8;
        ++v815;
        --v816;
      }
      while ( v816 );
      for ( ; v814; --v814 )
      {
        *(_BYTE *)v815 = 0;
        v815 = (_QWORD *)((char *)v815 + 1);
      }
      *(_DWORD *)v813 = 0;
      v817 = v803 + v804;
      v813[1] = v803;
      v818 = (_QWORD *)v803;
      *((_DWORD *)v813 + 4) = v804;
      v819 = (char *)v803;
      *(_DWORD *)(v806 + 2088) += v804;
      v820 = *(_DWORD *)(v806 + 2068);
      v821 = *(_QWORD *)(v806 + 2072);
      if ( v803 < v817 )
      {
        do
        {
          _mm_prefetchnta(v819);
          v819 += 64;
        }
        while ( (unsigned __int64)v819 < v817 );
      }
      v822 = *(_QWORD *)(v806 + 2072);
      v823 = v804 >> 7;
      if ( v804 >> 7 )
      {
        do
        {
          v824 = 8i64;
          do
          {
            v825 = v818[1] ^ __ROL8__(*v818 ^ v822, v820);
            v818 += 2;
            v822 = __ROL8__(v825, v820);
            --v824;
          }
          while ( v824 );
          v826 = (__ROL8__(v821 ^ ((unsigned __int64)v818 - v803), 17) ^ v821 ^ ((unsigned __int64)v818 - v803))
               * (unsigned __int128)0x7010008004002001ui64;
          v3983[1] = *((_QWORD *)&v826 + 1);
          v820 = ((unsigned __int8)v826 ^ (unsigned __int8)(BYTE8(v826) ^ v820)) & 0x3F;
          if ( !v820 )
            LOBYTE(v820) = 1;
          --v823;
        }
        while ( v823 );
        v813 = v3798;
      }
      v827 = v804 & 0x7F;
      if ( v827 >= 8 )
      {
        v828 = (unsigned __int64)(v804 & 0x7F) >> 3;
        do
        {
          v822 = __ROL8__(*v818++ ^ v822, v820);
          v827 -= 8;
          --v828;
        }
        while ( v828 );
      }
      for ( ; v827; --v827 )
      {
        v829 = *(unsigned __int8 *)v818;
        v818 = (_QWORD *)((char *)v818 + 1);
        v822 = __ROL8__(v829 ^ v822, v820);
      }
      for ( ii = v822; ; LODWORD(v822) = ii ^ v822 )
      {
        ii >>= 31;
        if ( !ii )
          break;
      }
      v831 = v3801;
      *((_DWORD *)v813 + 5) = v822 & 0x7FFFFFFF;
      v207 = (_BYTE *)v806;
      *(_DWORD *)(v806 + 2088) += v804;
      *((_DWORD *)v813 + 6) = 1;
      v771 = v831 + 1;
      v783 = v4231;
      v777 = v4228;
      v775 = v4227;
      LODWORD(v3801) = v771;
    }
LABEL_1066:
    if ( !v3796 )
    {
      v792 = *((unsigned int *)v207 + 505);
      v793 = v792 + 48;
      if ( (unsigned int)(v792 + 48) <= *((_DWORD *)v207 + 647) )
      {
        v794 = (__int64)v207;
        *((_DWORD *)v207 + 505) = v793;
      }
      else
      {
        v794 = sub_140B0F020(v207, v793, *((_DWORD *)v207 + 585));
        if ( !v794 )
          return 0;
        v795 = *((_DWORD *)v207 + 612);
        if ( (v795 & 4) == 0 )
        {
          v796 = *((_DWORD *)v207 + 505);
          v797 = *((_QWORD *)v207 + 249);
          v798 = (v795 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
          if ( v796 >= 8 )
          {
            v799 = (unsigned __int64)v796 >> 3;
            do
            {
              *(_QWORD *)v207 = 0i64;
              v796 -= 8;
              v207 += 8;
              --v799;
            }
            while ( v799 );
          }
          for ( ; v796; --v796 )
            *v207++ = 0;
          v800 = *(_DWORD *)(v794 + 2340);
          *(_DWORD *)(v794 + 2340) = v798;
          if ( v798 == 3 )
          {
            (*(void (__fastcall **)(__int64))(v794 + 872))(v797);
          }
          else if ( (*(_DWORD *)(v794 + 2448) & 0x10000000) != 0 || !v798 )
          {
            (*(void (__fastcall **)(__int64))(v794 + 248))(v797);
          }
          else
          {
            (*(void (__fastcall **)(__int64, _QWORD))(v794 + 552))(v797 - 8, *(_QWORD *)(v797 - 8));
          }
          *(_DWORD *)(v794 + 2340) = v800;
        }
        *(_DWORD *)(v794 + 2448) &= ~4u;
      }
      ++*(_DWORD *)(v794 + 2060);
      v832 = v794 + v792;
      v833 = 48;
      v834 = (_QWORD *)(v794 + v792);
      v835 = 6i64;
      do
      {
        *v834 = 0i64;
        v833 -= 8;
        ++v834;
        --v835;
      }
      while ( v835 );
      for ( ; v833; --v833 )
      {
        *(_BYTE *)v834 = 0;
        v834 = (_QWORD *)((char *)v834 + 1);
      }
      v836 = (unsigned __int8 *)v3792;
      *(_DWORD *)v832 = 0;
      *(_QWORD *)(v832 + 8) = v836;
      v837 = v836;
      *(_DWORD *)(v832 + 16) = 4;
      *(_DWORD *)(v794 + 2088) += 4;
      v838 = *(_QWORD *)(v794 + 2072);
      if ( v836 < v836 + 4 )
      {
        do
        {
          _mm_prefetchnta(v837);
          v837 += 64;
        }
        while ( v837 < v836 + 4 );
      }
      v839 = 4;
      do
      {
        v840 = *v836++;
        v838 = __ROL8__(v840 ^ v838, *(_DWORD *)(v794 + 2068));
        --v839;
      }
      while ( v839 );
      for ( jj = v838; ; LODWORD(v838) = jj ^ v838 )
      {
        jj >>= 31;
        if ( !jj )
          break;
      }
      v842 = v3801;
      *(_DWORD *)(v832 + 20) = v838 & 0x7FFFFFFF;
      v207 = (_BYTE *)v794;
      *(_DWORD *)(v794 + 2088) += 4;
      v771 = v842 + 1;
      *(_DWORD *)(v832 + 24) = 1;
      LODWORD(v3801) = v771;
    }
LABEL_1137:
    v770 = v3797 + 1;
    v3797 = v770;
    if ( (unsigned int)v770 < 0x33 )
      continue;
    break;
  }
  if ( (*((_DWORD *)v207 + 612) & 0x40000000) == 0 )
  {
    v843 = *((unsigned int *)v207 + 505);
    v844 = v843 + 48;
    if ( (unsigned int)(v843 + 48) <= *((_DWORD *)v207 + 647) )
    {
      v845 = (__int64)v207;
      *((_DWORD *)v207 + 505) = v844;
    }
    else
    {
      v845 = sub_140B0F020(v207, v844, *((_DWORD *)v207 + 585));
      if ( !v845 )
        return 0;
      v846 = *((_DWORD *)v207 + 612);
      if ( (v846 & 4) == 0 )
      {
        v847 = *((_DWORD *)v207 + 505);
        v848 = *((_QWORD *)v207 + 249);
        v849 = (v846 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
        if ( v847 >= 8 )
        {
          v850 = (unsigned __int64)v847 >> 3;
          do
          {
            *(_QWORD *)v207 = 0i64;
            v847 -= 8;
            v207 += 8;
            --v850;
          }
          while ( v850 );
        }
        for ( ; v847; --v847 )
          *v207++ = 0;
        v851 = *(_DWORD *)(v845 + 2340);
        *(_DWORD *)(v845 + 2340) = v849;
        if ( v849 == 3 )
        {
          (*(void (__fastcall **)(__int64))(v845 + 872))(v848);
        }
        else if ( (*(_DWORD *)(v845 + 2448) & 0x10000000) != 0 || !v849 )
        {
          (*(void (__fastcall **)(__int64))(v845 + 248))(v848);
        }
        else
        {
          (*(void (__fastcall **)(__int64, _QWORD))(v845 + 552))(v848 - 8, *(_QWORD *)(v848 - 8));
        }
        *(_DWORD *)(v845 + 2340) = v851;
      }
      *(_DWORD *)(v845 + 2448) &= ~4u;
    }
    ++*(_DWORD *)(v845 + 2060);
    v852 = v845 + v843;
    v853 = 48;
    v854 = (_QWORD *)(v845 + v843);
    v855 = 6i64;
    do
    {
      *v854 = 0i64;
      v853 -= 8;
      ++v854;
      --v855;
    }
    while ( v855 );
    for ( ; v853; --v853 )
    {
      *(_BYTE *)v854 = 0;
      v854 = (_QWORD *)((char *)v854 + 1);
    }
    *(_DWORD *)v852 = 0;
    *(_QWORD *)(v852 + 8) = 0i64;
    *(_DWORD *)(v852 + 16) = 0;
    v856 = *(_QWORD *)(v845 + 2072);
    for ( kk = v856; ; LODWORD(v856) = kk ^ v856 )
    {
      kk >>= 31;
      if ( !kk )
        break;
    }
    v771 = v3801;
    *(_DWORD *)(v852 + 20) = v856 & 0x7FFFFFFF;
    v207 = (_BYTE *)v845;
    v3983[4] = v852;
    *(_DWORD *)(v845 + 2600) = v852 - v845;
    *(_DWORD *)(v845 + 2604) += 48;
  }
  *((_DWORD *)v207 + 504) = v771;
  *((_DWORD *)v207 + 651) += 48 * v771;
LABEL_1166:
  v3981 = v207;
  if ( !v207 )
    return 0;
  v858 = *((_DWORD *)v207 + 612);
  LODWORD(v3801) = *((_DWORD *)v207 + 505);
  v859 = 0;
  v3797 = 0;
  v860 = 0;
  if ( (v858 & 0x40000000) == 0 && !(_DWORD)v3799 )
  {
    v861 = __rdtsc();
    v862 = (__ROR8__(v861, 3) ^ v861) * (unsigned __int128)0x7010008004002001ui64;
    v3983[5] = *((_QWORD *)&v862 + 1);
    if ( !(((unsigned __int64)v862 ^ *((_QWORD *)&v862 + 1)) % 0xA) )
    {
      v860 = 1;
      v3797 = 1;
      v863 = __rdtsc();
      v864 = (__ROR8__(v863, 3) ^ v863) * (unsigned __int128)0x7010008004002001ui64;
      v3983[6] = *((_QWORD *)&v864 + 1);
      if ( ((unsigned __int64)v864 ^ *((_QWORD *)&v864 + 1)) % 0xA < 3 )
      {
        v865 = v858 | 0x10000;
        *((_DWORD *)v207 + 612) = v865;
        v866 = __rdtsc();
        v867 = (__ROR8__(v866, 3) ^ v866) * (unsigned __int128)0x7010008004002001ui64;
        v3983[7] = *((_QWORD *)&v867 + 1);
        if ( ((unsigned __int64)v867 ^ *((_QWORD *)&v867 + 1)) % 0xA < 3 )
          *((_DWORD *)v207 + 612) = v865 | 0x100000;
      }
    }
    v859 = 0;
  }
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  LODWORD(v3799) = 0;
LABEL_1177:
  v868 = &qword_140B9BB80[3 * v859];
  if ( (v868[2] & 0xE0000000) == 0x80000000 || !v860 )
  {
    v869 = v868[1];
    v3984 = v869;
    switch ( v869 )
    {
      case 0ui64:
        v870 = 0x140000000ui64;
        v3984 = 0x140000000ui64;
        break;
      case 1ui64:
        v870 = PsHalImageBase;
        goto LABEL_1212;
      case 2ui64:
        v871 = 0i64;
        v870 = 0i64;
        v3984 = 0i64;
        if ( (v3836 & 6) != 0 )
          goto LABEL_2146;
        v872 = (_QWORD *)PspPicoProviderRanges;
        if ( !PspPicoProviderRanges )
          goto LABEL_2146;
        v873 = 0i64;
        v874 = 0;
        v875 = *(_QWORD *)(PspPicoProviderRanges + 8) == 0i64;
        if ( !*(_QWORD *)(PspPicoProviderRanges + 8) )
          goto LABEL_1192;
        do
        {
          v873 = (ULONG_PTR *)(*v872 + 16 * v871);
          if ( v873[1] )
          {
            (*((void (__fastcall **)(ULONG_PTR, ULONG_PTR *))v207 + 65))(*v873, &v3984);
            v870 = v3984;
            if ( v3984 )
              goto LABEL_1213;
          }
          v872 = (_QWORD *)PspPicoProviderRanges;
          v871 = ++v874;
        }
        while ( (unsigned __int64)v874 < *(_QWORD *)(PspPicoProviderRanges + 8) );
        if ( !v870 )
        {
          v875 = *(_QWORD *)(PspPicoProviderRanges + 8) == 0i64;
LABEL_1192:
          if ( !v875 )
          {
            v3771 = *v873;
            v3845[1] = 317;
            KeBugCheckEx(__ROR4__(317, 160), 0x13ui64, (ULONG_PTR)v872, v3771, (ULONG_PTR)v873);
          }
          goto LABEL_2146;
        }
        break;
      case 3ui64:
        v876 = 0i64;
        v870 = 0i64;
        v3984 = 0i64;
        if ( (v3836 & 6) != 0 )
          goto LABEL_2146;
        v877 = (_QWORD *)__27;
        if ( !__27 )
          goto LABEL_2146;
        v878 = 0i64;
        v879 = 0;
        v880 = *(_QWORD *)(__27 + 8) == 0i64;
        if ( *(_QWORD *)(__27 + 8) )
        {
          do
          {
            v878 = (ULONG_PTR *)(*v877 + 16 * v876);
            if ( v878[1] )
            {
              (*((void (__fastcall **)(ULONG_PTR, ULONG_PTR *))v207 + 65))(*v878, &v3984);
              v870 = v3984;
              if ( v3984 )
                goto LABEL_1213;
            }
            v877 = (_QWORD *)__27;
            v876 = ++v879;
          }
          while ( (unsigned __int64)v879 < *(_QWORD *)(__27 + 8) );
          if ( v870 )
            break;
          v880 = *(_QWORD *)(__27 + 8) == 0i64;
        }
        if ( !v880 )
        {
          v3772 = *v878;
          v3845[2] = 317;
          KeBugCheckEx(__ROR4__(317, 160), 0x14ui64, (ULONG_PTR)v877, v3772, (ULONG_PTR)v878);
        }
        goto LABEL_2146;
      default:
        v870 = 0i64;
        _disable();
        v207 = v3981;
        v881 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + *((_QWORD *)v3981 + 202));
        _enable();
        (*((void (__fastcall **)(__int64))v207 + 45))(v881);
        LOBYTE(v882) = 1;
        (*((void (__fastcall **)(_QWORD, __int64))v207 + 28))(*((_QWORD *)v207 + 166), v882);
        for ( mm = (PVOID *)PsLoadedModuleList; ; mm = (PVOID *)*mm )
        {
          if ( mm == &PsLoadedModuleList )
            goto LABEL_1211;
          v884 = (char *)mm - *((_QWORD *)v207 + 234);
          if ( RtlEqualUnicodeString((PCUNICODE_STRING)v868, (PCUNICODE_STRING)&v884[*((_QWORD *)v207 + 237)], 1u) )
            break;
        }
        v870 = *(_QWORD *)&v884[*((_QWORD *)v207 + 235)];
LABEL_1211:
        (*((void (__fastcall **)(_QWORD))v207 + 35))(*((_QWORD *)v207 + 166));
        (*((void (**)(void))v207 + 46))();
LABEL_1212:
        v3984 = v870;
        if ( !v870 )
          goto LABEL_2146;
        break;
    }
LABEL_1213:
    v885 = *((_DWORD *)v868 + 4);
    v3796 = v885 & 1;
    if ( (v885 & 4) != 0 )
    {
      v875 = (*((_DWORD *)v207 + 613) & 0x400) == 0;
      v3796 = v885 & 1;
      if ( !v875 )
        v3796 = v885 & 1 | 0x10;
    }
    if ( (v885 & 2) == 0 || v3797 )
      goto LABEL_1517;
    v886 = (__int64 (__fastcall *)(ULONG_PTR, char *))*((_QWORD *)v207 + 64);
    v887 = v207;
    v3985 = v207;
    v3792 = v886(v870, v4150);
    v3789 = v4152;
    v3798 = v4151;
    if ( !v4151 )
    {
      if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
      {
        v3845[12] = 317;
        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v870, 5ui64, 0i64);
      }
      return 0;
    }
    v888 = (int *)&v4105;
    v4104 = 0i64;
    v889 = 4;
    do
    {
      *(_BYTE *)v888 = 0;
      v888 = (int *)((char *)v888 + 1);
      --v889;
    }
    while ( v889 );
    v890 = 0;
    LODWORD(v3793) = 0;
    if ( *((_DWORD *)v207 + 515) )
    {
      v891 = v4105;
      v892 = HIDWORD(v4104);
      v893 = v4104;
      while ( 1 )
      {
        v894 = (unsigned int *)v207;
        if ( *((_QWORD *)v207 + 335) )
          v894 = (unsigned int *)*((_QWORD *)v207 + 335);
        Src = v894;
        v895 = 0;
        v896 = (int *)((char *)v894 + v894[514]);
        if ( v893 && v892 <= v890 )
        {
          v895 = v892;
          v896 = (int *)((char *)v894 + v891);
        }
        if ( v895 != v890 )
          break;
LABEL_1253:
        LODWORD(v4104) = 1;
        v891 = (_DWORD)v896 - (_DWORD)v894;
        HIDWORD(v4104) = v895;
        v4105 = (_DWORD)v896 - (_DWORD)v894;
        v893 = 1;
        v909 = *v896;
        v892 = v895;
        if ( (unsigned int)v909 <= 0x2B
          && (v910 = 0x80000001002i64, _bittest64(&v910, v909))
          && *((_QWORD *)v896 + 1) == v3792
          && v896[4] == v3789
          || (unsigned int)(v909 - 33) <= 1 && *((__int64 **)v896 + 4) == v3798 )
        {
          if ( v896 )
            goto LABEL_1517;
          goto LABEL_1262;
        }
        LODWORD(v3793) = ++v890;
        if ( v890 >= *((_DWORD *)v207 + 515) )
          goto LABEL_1262;
      }
      v897 = v890 - v895;
      v895 = v890;
      while ( 2 )
      {
        v898 = *v896;
        if ( *v896 > 28 )
        {
          v906 = v898 - 30;
          if ( !v906 )
          {
            v904 = (((v896[9] != 0 ? v896[9] - 1 : 0) / 0xCu + 7) & 0xFFFFFFF8)
                 + 24 * (*((unsigned __int16 *)v896 + 20) + 2);
            goto LABEL_1251;
          }
          v907 = v906 - 3;
          if ( !v907 || (v908 = v907 - 1) == 0 )
          {
            v904 = 20 * (unsigned int)(((v896[8] & 0xFFF) + (unsigned __int64)(unsigned int)v896[10] + 4095) >> 12) + 48;
            goto LABEL_1251;
          }
          v903 = v908 == 9;
LABEL_1246:
          if ( !v903 )
          {
            v904 = 48i64;
            goto LABEL_1251;
          }
        }
        else
        {
          if ( v898 == 28 )
          {
            v905 = *((unsigned __int16 *)v896 + 20);
            goto LABEL_1239;
          }
          v899 = v898 - 1;
          if ( v899 )
          {
            v900 = v899 - 6;
            if ( !v900 )
            {
              v904 = (unsigned int)(24 * (v896[6] + 2));
              goto LABEL_1251;
            }
            v901 = v900 - 1;
            if ( v901 )
            {
              v902 = v901 - 2;
              if ( v902 )
              {
                v903 = v902 == 2;
                goto LABEL_1246;
              }
              v904 = (unsigned int)(16 * (v896[7] + 3));
LABEL_1251:
              v896 = (int *)((char *)v896 + v904);
              if ( !--v897 )
              {
                LODWORD(v894) = (_DWORD)Src;
                v890 = v3793;
                goto LABEL_1253;
              }
              continue;
            }
            v905 = *((unsigned __int16 *)v896 + 16);
LABEL_1239:
            v904 = (v905 + 55) & 0xFFFFFFF8;
            goto LABEL_1251;
          }
        }
        break;
      }
      v904 = 4 * (v896[4] / 0xCu) + 48;
      goto LABEL_1251;
    }
LABEL_1262:
    v911 = v3796;
    v912 = (__int64 (__fastcall *)(ULONG_PTR, char *))*((_QWORD *)v207 + 64);
    LODWORD(v3793) = v3796;
    v3986[0] = (__int64)v207;
    v3792 = v912(v870, v4153);
    v3789 = v4155;
    v3837[0] = v4155;
    v3794 = v4154;
    if ( !v4154 )
    {
      if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
      {
        v3845[3] = 317;
        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v870, 5ui64, 0i64);
      }
      goto LABEL_1264;
    }
    v913 = 4;
    v4106 = 0i64;
    v914 = 0i64;
    v915 = &v4107;
    do
    {
      *(_BYTE *)v915 = 0;
      v915 = (int *)((char *)v915 + 1);
      --v913;
    }
    while ( v913 );
    v916 = 0;
    LODWORD(v3791) = 0;
    if ( *((_DWORD *)v207 + 515) )
    {
      LODWORD(v914) = v4107;
      v917 = HIDWORD(v4106);
      v918 = v4106;
      while ( 1 )
      {
        v919 = (unsigned int *)v207;
        if ( *((_QWORD *)v207 + 335) )
          v919 = (unsigned int *)*((_QWORD *)v207 + 335);
        Src = v919;
        v920 = 0;
        v921 = (int *)((char *)v919 + v919[514]);
        if ( v918 && v917 <= v916 )
        {
          v920 = v917;
          v921 = (int *)((char *)v919 + (unsigned int)v914);
        }
        if ( v920 != v916 )
          break;
LABEL_1299:
        LODWORD(v4106) = 1;
        v914 = (unsigned int)((_DWORD)v921 - (_DWORD)v919);
        HIDWORD(v4106) = v920;
        v4107 = (_DWORD)v921 - (_DWORD)v919;
        v918 = 1;
        v934 = *v921;
        v917 = v920;
        if ( (unsigned int)v934 <= 0x2B
          && (v935 = 0x80000001002i64, _bittest64(&v935, v934))
          && *((_QWORD *)v921 + 1) == v3792
          && v921[4] == v3789
          || (unsigned int)(v934 - 33) <= 1 && *((_QWORD *)v921 + 4) == v3794 )
        {
          if ( !v921 )
          {
LABEL_1308:
            v911 = v3793;
            goto LABEL_1309;
          }
LABEL_1724:
          v3981 = v887;
LABEL_1725:
          v1222 = (*((__int64 (__fastcall **)(__int64 *))v887 + 63))(v3798);
          v1223 = *(unsigned int *)(v1222 + 148);
          if ( (unsigned int)v1223 >= 0x14 )
          {
            v1224 = *(unsigned int *)(v1222 + 144);
            v1225 = (char *)v3798 + v1223 + v1224;
            for ( nn = (char *)v3798 + v1224; nn != v1225; nn += 20 )
            {
              if ( !*((_DWORD *)nn + 3) )
                break;
              v1227 = *((unsigned int *)nn + 4);
              if ( !(_DWORD)v1227 )
                break;
              v1228 = *(__int64 *)((char *)v3798 + v1227);
              if ( v1228 )
              {
                v1229 = sub_140B0B7A8(&v3985, v1228, v3796 & 0x7FFFFFEF | 0x80000000);
                v207 = v3985;
                v3981 = v3985;
                if ( (int)(v1229 + 0x80000000) >= 0 && v1229 != -1073741554 )
                  return 0;
              }
            }
          }
LABEL_1517:
          _disable();
          if ( !(_BYTE)KdDebuggerNotPresent )
          {
            while ( 1 )
              ;
          }
          _enable();
          v1078 = v3984;
          v1079 = (__int64 (__fastcall *)(ULONG_PTR, char *))*((_QWORD *)v207 + 64);
          HalExtensionList = v3984;
          v3999 = v207;
          v1080 = v1079(v3984, v4157);
          v1081 = v4158;
          v1082 = v4159;
          v3788 = v1080;
          LODWORD(Src) = v4159;
          v3843 = v4159;
          v3787 = v4158;
          if ( !v4158 )
          {
            if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
            {
              v3845[21] = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1078, 5ui64, 0i64);
            }
            return 0;
          }
          v4108 = 0i64;
          v1083 = &v4109;
          LODWORD(v1084) = 4;
          do
          {
            *(_BYTE *)v1083 = 0;
            v1083 = (int *)((char *)v1083 + 1);
            v875 = (_DWORD)v1084 == 1;
            v1084 = (unsigned int)(v1084 - 1);
          }
          while ( !v875 );
          v1085 = 0;
          if ( *((_DWORD *)v207 + 515) )
          {
            LODWORD(v1084) = v4109;
            v1086 = HIDWORD(v4108);
            v1087 = v4108;
            while ( 1 )
            {
              v1088 = v207;
              if ( *((_QWORD *)v207 + 335) )
                v1088 = (_BYTE *)*((_QWORD *)v207 + 335);
              v1089 = 0;
              v1090 = (int *)&v1088[*((unsigned int *)v1088 + 514)];
              if ( v1087 && v1086 <= v1085 )
              {
                v1089 = v1086;
                v1090 = (int *)&v1088[(unsigned int)v1084];
              }
              if ( v1089 != v1085 )
                break;
LABEL_1750:
              LODWORD(v4108) = 1;
              v1084 = (unsigned int)((_DWORD)v1090 - (_DWORD)v1088);
              HIDWORD(v4108) = v1089;
              v4109 = (_DWORD)v1090 - (_DWORD)v1088;
              v1087 = 1;
              v1235 = *v1090;
              v1086 = v1089;
              if ( (unsigned int)v1235 <= 0x2B
                && (v1236 = 0x80000001002i64, _bittest64(&v1236, v1235))
                && *((_QWORD *)v1090 + 1) == v3788
                && v1090[4] == v1082
                || (unsigned int)(v1235 - 33) <= 1 && *((_QWORD *)v1090 + 4) == v3787 )
              {
                if ( !v1090 )
                {
LABEL_1759:
                  v1081 = v3787;
                  goto LABEL_1760;
                }
LABEL_2146:
                v859 = v3799 + 1;
                LODWORD(v3799) = v859;
                if ( v859 < 0x11 )
                {
                  v860 = v3797;
                  goto LABEL_1177;
                }
                goto LABEL_2156;
              }
              if ( ++v1085 >= *((_DWORD *)v207 + 515) )
                goto LABEL_1759;
            }
            v1091 = v1085 - v1089;
            v1089 = v1085;
            while ( 2 )
            {
              v1092 = *v1090;
              if ( *v1090 > 28 )
              {
                v1232 = v1092 - 30;
                if ( !v1232 )
                {
                  v1230 = (((v1090[9] != 0 ? v1090[9] - 1 : 0) / 0xCu + 7) & 0xFFFFFFF8)
                        + 24 * (*((unsigned __int16 *)v1090 + 20) + 2);
                  goto LABEL_1748;
                }
                v1233 = v1232 - 3;
                if ( !v1233 || (v1234 = v1233 - 1) == 0 )
                {
                  v1230 = 20
                        * (unsigned int)(((v1090[8] & 0xFFF) + (unsigned __int64)(unsigned int)v1090[10] + 4095) >> 12)
                        + 48;
                  goto LABEL_1748;
                }
                v1097 = v1234 == 9;
LABEL_1743:
                if ( !v1097 )
                {
                  v1230 = 48i64;
                  goto LABEL_1748;
                }
              }
              else
              {
                if ( v1092 == 28 )
                {
                  v1231 = *((unsigned __int16 *)v1090 + 20);
                  goto LABEL_1736;
                }
                v1093 = v1092 - 1;
                if ( v1093 )
                {
                  v1094 = v1093 - 6;
                  if ( !v1094 )
                  {
                    v1230 = (unsigned int)(24 * (v1090[6] + 2));
                    goto LABEL_1748;
                  }
                  v1095 = v1094 - 1;
                  if ( v1095 )
                  {
                    v1096 = v1095 - 2;
                    if ( v1096 )
                    {
                      v1097 = v1096 == 2;
                      goto LABEL_1743;
                    }
                    v1230 = (unsigned int)(16 * (v1090[7] + 3));
LABEL_1748:
                    v1090 = (int *)((char *)v1090 + v1230);
                    if ( !--v1091 )
                    {
                      v1078 = HalExtensionList;
                      v1082 = (int)Src;
                      goto LABEL_1750;
                    }
                    continue;
                  }
                  v1231 = *((unsigned __int16 *)v1090 + 16);
LABEL_1736:
                  v1230 = (v1231 + 55) & 0xFFFFFFF8;
                  goto LABEL_1748;
                }
              }
              break;
            }
            v1230 = 4 * (v1090[4] / 0xCu) + 48;
            goto LABEL_1748;
          }
LABEL_1760:
          v1237 = v3796;
          v1238 = (*((__int64 (__fastcall **)(__int64, __int64))v207 + 85))(v1078, v1084);
          LODWORD(Src) = v1238;
          LODWORD(v3784) = v3843;
          if ( (v3796 & 0x10) != 0 )
          {
            if ( (*((_DWORD *)v207 + 613) & 0x400) == 0 )
            {
              v1237 = v3796 & 0xFFFFFFEF;
              v3796 &= ~0x10u;
            }
            if ( (v1237 & 0x10) != 0 && !(unsigned int)sub_140B100E0(v207, v1081) )
            {
              v1237 &= ~0x10u;
              v3796 = v1237;
            }
          }
          v1239 = (char **)*((_QWORD *)v207 + 165);
          LODWORD(v3783) = v1237 & 1;
          _disable();
          v1240 = v3981;
          v1241 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + *((_QWORD *)v3981 + 202));
          _enable();
          (*((void (__fastcall **)(__int64))v1240 + 45))(v1241);
          LOBYTE(v1242) = 1;
          (*((void (__fastcall **)(_QWORD, __int64))v1240 + 29))(*((_QWORD *)v1240 + 166), v1242);
          v1243 = *v1239;
          if ( *v1239 != (char *)v1239 )
          {
            v1244 = *((_QWORD *)v1240 + 234);
            while ( 1 )
            {
              v1245 = *(_QWORD *)&v1243[*((_QWORD *)v1240 + 235) - v1244];
              if ( v3787 >= v1245 && v3787 < v1245 + *(unsigned int *)&v1243[*((_QWORD *)v1240 + 236) - v1244] )
                break;
              v1243 = *(char **)v1243;
              if ( v1243 == (char *)v1239 )
                goto LABEL_1773;
            }
            (*((void (__fastcall **)(char *, _QWORD))KiFreezeDataTableEntry))(&v1243[-v1244], (unsigned int)!(v1237 & 1) + 1);
LABEL_1773:
            v1237 = v3796;
          }
          (*((void (__fastcall **)(_QWORD))v1240 + 35))(*((_QWORD *)v1240 + 166));
          (*((void (**)(void))v1240 + 46))();
          if ( (*((_DWORD *)v1240 + 612) & 0x40000000) != 0 )
          {
            v1247 = sub_140B16070(&v3981, v3787, v1237);
            v207 = v3981;
            goto LABEL_1955;
          }
          v1248 = v3787;
          v4194 = 0i64;
          LOBYTE(v1246) = 1;
          v4160[4] = 0;
          v4191 = (*((__int64 (__fastcall **)(ULONG_PTR, __int64, _QWORD, int *))RtlImageDirectoryEntryToData))(
                    v3787,
                    v1246,
                    0i64,
                    &v3843);
          v1249 = v3843 & (unsigned int)-(v4191 != 0);
          v3843 = v1249;
          v1250 = (__int64 (__fastcall *)(ULONG_PTR, __int64, __int64, int *))*((_QWORD *)RtlImageDirectoryEntryToData);
          v4160[1] = v1249;
          LOBYTE(v1249) = 1;
          v1251 = v1250(v3787, v1249, 12i64, &v3843);
          v1252 = v1251;
          HalExtensionList = v1251;
          v4192 = v1251;
          LOBYTE(v1252) = 1;
          v3843 &= -(v1251 != 0);
          v1253 = (__int64 (__fastcall *)(ULONG_PTR, __int64, __int64, int *))*((_QWORD *)RtlImageDirectoryEntryToData);
          LODWORD(v3785) = v3843;
          v4160[2] = v3843;
          v4193 = v1253(v3787, v1252, 10i64, &v3843);
          v3843 &= -(v4193 != 0);
          v1254 = (__int64 (__fastcall *)(ULONG_PTR))*((_QWORD *)v1240 + 63);
          v4160[3] = v3843;
          v1255 = v1254(v3787);
          if ( !v1255 )
          {
            if ( (*((_DWORD *)v1240 + 612) & 0x200000) == 0 )
            {
              v3845[20] = 317;
              KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, 7ui64, 0i64);
            }
            if ( !*((_DWORD *)v1240 + 574) )
            {
              *((_QWORD *)v1240 + 288) = v1240 - 0x5C5FC0A76E374B18i64;
              *((_QWORD *)v1240 + 289) = 0i64;
              *((_QWORD *)v1240 + 290) = 271i64;
              *((_QWORD *)v1240 + 291) = v1248;
              *((_DWORD *)v1240 + 574) = 1;
              __ba(v1240, 0i64);
            }
            return 0;
          }
          v1256 = (*((__int64 (__fastcall **)(ULONG_PTR, int *))v1240 + 148))(v3787, &v4000);
          v1257 = *((unsigned int *)v1240 + 505);
          v1258 = *((unsigned int *)v1240 + 585);
          v4195 = v1256;
          v4160[0] = *(_DWORD *)(v1255 + 84);
          v4160[5] = v4000;
          v1259 = v1257 + 288;
          v4190 = v3787;
          v1260 = v1238 != 0 ? 0xB : 0;
          LODWORD(v3791) = v1260;
          if ( (unsigned int)(v1257 + 288) <= *((_DWORD *)v1240 + 647) )
          {
            v207 = v1240;
            *((_DWORD *)v1240 + 505) = v1259;
          }
          else
          {
            v207 = (_BYTE *)sub_140B0F020(v1240, v1259, v1258);
            if ( !v207 )
              return 0;
            v1261 = *((_DWORD *)v1240 + 612);
            if ( (v1261 & 4) == 0 )
            {
              v1262 = *((_DWORD *)v1240 + 505);
              v1263 = *((_QWORD *)v1240 + 249);
              v1264 = (v1261 & 0x20000000) != 0 ? *((_DWORD *)v1240 + 585) : 0;
              if ( v1262 >= 8 )
              {
                v1265 = (unsigned __int64)v1262 >> 3;
                do
                {
                  *(_QWORD *)v1240 = 0i64;
                  v1262 -= 8;
                  v1240 += 8;
                  --v1265;
                }
                while ( v1265 );
              }
              for ( ; v1262; --v1262 )
                *v1240++ = 0;
              v1266 = *((_DWORD *)v207 + 585);
              *((_DWORD *)v207 + 585) = v1264;
              if ( v1264 == 3 )
              {
                (*((void (__fastcall **)(__int64))v207 + 109))(v1263);
              }
              else if ( (*((_DWORD *)v207 + 612) & 0x10000000) != 0 || !v1264 )
              {
                (*((void (__fastcall **)(__int64))ExFreePool))(v1263);
              }
              else
              {
                (*((void (__fastcall **)(__int64, _QWORD))v207 + 69))(v1263 - 8, *(_QWORD *)(v1263 - 8));
              }
              v1260 = v3791;
              *((_DWORD *)v207 + 585) = v1266;
            }
            *((_DWORD *)v207 + 612) &= ~4u;
          }
          v1267 = (__int64 *)&v4190;
          *((_DWORD *)v207 + 515) += 6;
          v1268 = v4160;
          v1269 = (unsigned __int64)&v207[v1257];
          v3790 = (__int64)&v4190;
          v3786 = v1269;
          v3794 = (ULONG_PTR)v4160;
          v3792 = 6i64;
          do
          {
            v1270 = (unsigned int)*v1268;
            v1271 = 48;
            v1272 = (_QWORD *)*v1267;
            v1273 = (_QWORD *)v1269;
            LODWORD(v3793) = *v1268;
            v1274 = 6i64;
            do
            {
              *v1273 = 0i64;
              v1271 -= 8;
              ++v1273;
              --v1274;
            }
            while ( v1274 );
            for ( ; v1271; --v1271 )
            {
              *(_BYTE *)v1273 = 0;
              v1273 = (_QWORD *)((char *)v1273 + 1);
            }
            *(_DWORD *)v1269 = v1260;
            *(_QWORD *)(v1269 + 8) = v1272;
            v1275 = v1272;
            *(_DWORD *)(v1269 + 16) = v1270;
            v1276 = (char *)v1272;
            *((_DWORD *)v207 + 522) += v1270;
            v1277 = *((_DWORD *)v207 + 517);
            v1278 = *((_QWORD *)v207 + 259);
            if ( v1272 < (_QWORD *)((char *)v1272 + v1270) )
            {
              do
              {
                _mm_prefetchnta(v1276);
                v1276 += 64;
              }
              while ( v1276 < (char *)v1272 + v1270 );
            }
            v1279 = *((_QWORD *)v207 + 259);
            v1280 = (unsigned int)v1270 >> 7;
            if ( (unsigned int)v1270 >> 7 )
            {
              do
              {
                v1281 = 8i64;
                do
                {
                  v1282 = v1275[1] ^ __ROL8__(*v1275 ^ v1279, v1277);
                  v1275 += 2;
                  v1279 = __ROL8__(v1282, v1277);
                  --v1281;
                }
                while ( v1281 );
                v1283 = (__ROL8__(v1278 ^ ((char *)v1275 - (char *)v1272), 17) ^ v1278 ^ (unsigned __int64)((char *)v1275 - (char *)v1272))
                      * (unsigned __int128)0x7010008004002001ui64;
                v4001 = *((_QWORD *)&v1283 + 1);
                v1277 = ((unsigned __int8)v1283 ^ (unsigned __int8)(BYTE8(v1283) ^ v1277)) & 0x3F;
                if ( !v1277 )
                  LOBYTE(v1277) = 1;
                --v1280;
              }
              while ( v1280 );
              LODWORD(v1270) = v3793;
              v1267 = (__int64 *)v3790;
              v1268 = (int *)v3794;
            }
            v1284 = v1270 & 0x7F;
            if ( v1284 >= 8 )
            {
              v1285 = (unsigned __int64)(v1270 & 0x7F) >> 3;
              do
              {
                v1279 = __ROL8__(*v1275++ ^ v1279, v1277);
                v1284 -= 8;
                --v1285;
              }
              while ( v1285 );
            }
            for ( ; v1284; --v1284 )
            {
              v1286 = *(unsigned __int8 *)v1275;
              v1275 = (_QWORD *)((char *)v1275 + 1);
              v1279 = __ROL8__(v1286 ^ v1279, v1277);
            }
            for ( i1 = v1279 >> 31; i1; i1 >>= 31 )
              LODWORD(v1279) = i1 ^ v1279;
            v1260 = v3791;
            *(_DWORD *)(v1269 + 20) = v1279 & 0x7FFFFFFF;
            ++v1268;
            *((_DWORD *)v207 + 522) += v1270;
            ++v1267;
            v3794 = (ULONG_PTR)v1268;
            v1269 += 48i64;
            v3790 = (__int64)v1267;
            --v3792;
          }
          while ( v3792 );
          v1288 = v3786;
          v1289 = v3787;
          *(_DWORD *)v3786 = 44;
          *(_QWORD *)(v1288 + 24) = v1289;
          v1290 = *((_DWORD *)v207 + 612);
          if ( (v1290 & 0x10000000) != 0 || (v1290 & 0x200000) != 0 )
          {
            v1291 = (int)Src;
            if ( !(_DWORD)Src )
              goto LABEL_1825;
          }
          else
          {
            v1291 = (int)Src;
            if ( !(_DWORD)Src )
            {
              if ( (*((_DWORD *)v207 + 613) & 0x8000) != 0 )
              {
                *(_DWORD *)(v1288 + 32) |= 1u;
                if ( (unsigned int)sub_140B100E0(v207, v1289) )
                  *(_DWORD *)(v1288 + 32) |= 4u;
              }
LABEL_1825:
              v3999 = v207;
              v3981 = v207;
              v1247 = sub_140B0D838((int)&v3999, v3788, v3784, v1289, v1291, v3796, (__int64)v3845, (__int64)&v3844);
              if ( v1247 < 0 )
                goto LABEL_1956;
              v1292 = v3999;
              v1293 = 48;
              v1294 = 6i64;
              v1295 = v3844 - v3845[0];
              v3981 = v3999;
              v1296 = v3999 - v207 + v1288;
              v1297 = (char *)(v1289 + (unsigned int)v3845[0]);
              v3786 = v1296;
              v1298 = (_DWORD *)(v1296 + 192);
              v3790 = v1296 + 192;
              v1299 = (_QWORD *)(v1296 + 192);
              do
              {
                *v1299 = 0i64;
                v1293 -= 8;
                ++v1299;
                --v1294;
              }
              while ( v1294 );
              for ( ; v1293; --v1293 )
              {
                *(_BYTE *)v1299 = 0;
                v1299 = (_QWORD *)((char *)v1299 + 1);
              }
              v1300 = (__int64)v1297;
              *v1298 = v3791;
              v1301 = v1297;
              *(_QWORD *)(v1296 + 200) = v1297;
              *(_DWORD *)(v1296 + 208) = v1295;
              *((_DWORD *)v1292 + 522) += v1295;
              v1302 = *((_DWORD *)v1292 + 517);
              v1303 = *((_QWORD *)v1292 + 259);
              v1304 = (unsigned __int64)&v1297[v1295];
              if ( (unsigned __int64)v1297 < v1304 )
              {
                do
                {
                  v1301 += 64;
                }
                while ( (unsigned __int64)v1301 < v1304 );
              }
              v1305 = *((_QWORD *)v1292 + 259);
              v1306 = v1295 >> 7;
              if ( v1295 >> 7 )
              {
                do
                {
                  v1307 = 8i64;
                  do
                  {
                    v1308 = *(_QWORD *)(v1300 + 8) ^ __ROL8__(*(_QWORD *)v1300 ^ v1305, v1302);
                    v1300 += 16i64;
                    v1305 = __ROL8__(v1308, v1302);
                    --v1307;
                  }
                  while ( v1307 );
                  v1309 = (__ROL8__(v1303 ^ (v1300 - (_QWORD)v1297), 17) ^ v1303 ^ (unsigned __int64)(v1300 - (_QWORD)v1297))
                        * (unsigned __int128)0x7010008004002001ui64;
                  v4002 = *((_QWORD *)&v1309 + 1);
                  v1302 = ((unsigned __int8)(v1309 ^ BYTE8(v1309)) ^ (unsigned __int8)v1302) & 0x3F;
                  if ( !v1302 )
                    LOBYTE(v1302) = 1;
                  --v1306;
                }
                while ( v1306 );
                v1298 = (_DWORD *)v3790;
              }
              v1310 = v1295 & 0x7F;
              if ( (unsigned int)v1310 >= 8 )
              {
                v1311 = (unsigned __int64)(unsigned int)v1310 >> 3;
                do
                {
                  v1305 = __ROL8__(*(_QWORD *)v1300 ^ v1305, v1302);
                  v1300 += 8i64;
                  v1310 = (unsigned int)(v1310 - 8);
                  --v1311;
                }
                while ( v1311 );
              }
              if ( (_DWORD)v1310 )
              {
                do
                {
                  v1312 = *(unsigned __int8 *)v1300++;
                  v1305 = __ROL8__(v1312 ^ v1305, v1302);
                  v875 = (_DWORD)v1310 == 1;
                  v1310 = (unsigned int)(v1310 - 1);
                }
                while ( !v875 );
              }
              v1313 = v1305 >> 31;
              v1314 = 0;
              while ( v1313 )
              {
                LODWORD(v1305) = v1313 ^ v1305;
                v1313 >>= 31;
              }
              v1315 = v3786;
              v1298[5] = v1305 & 0x7FFFFFFF;
              v1316 = (int)Src;
              *(_DWORD *)(v1315 + 240) = 48;
              if ( *(_DWORD *)(v1315 + 256) )
              {
                LOBYTE(v1314) = v1316 != 0;
                *(_DWORD *)(v1315 + 264) = *(_DWORD *)(v1315 + 264) & 0xFFFFFFFE | v1314;
              }
              v3981 = v1292;
              v1317 = (_BYTE *)(v1315 + 96);
              v1318 = (v1316 != 0) + 13;
              if ( v1315 == -96i64 )
              {
                v1319 = *((unsigned int *)v1292 + 505);
                v1320 = v1319 + 48;
                if ( (unsigned int)(v1319 + 48) <= *((_DWORD *)v1292 + 647) )
                {
                  v207 = v1292;
                  *((_DWORD *)v1292 + 505) = v1320;
                }
                else
                {
                  v207 = (_BYTE *)sub_140B0F020(v1292, v1320, *((_DWORD *)v1292 + 585));
                  if ( !v207 )
                    return 0;
                  v1321 = *((_DWORD *)v1292 + 612);
                  if ( (v1321 & 4) == 0 )
                  {
                    v1322 = *((_DWORD *)v1292 + 505);
                    v1323 = *((_QWORD *)v1292 + 249);
                    v1324 = (v1321 & 0x20000000) != 0 ? *((_DWORD *)v1292 + 585) : 0;
                    if ( v1322 >= 8 )
                    {
                      v1325 = (unsigned __int64)v1322 >> 3;
                      do
                      {
                        *(_QWORD *)v1292 = 0i64;
                        v1322 -= 8;
                        v1292 += 8;
                        --v1325;
                      }
                      while ( v1325 );
                    }
                    for ( ; v1322; --v1322 )
                      *v1292++ = 0;
                    v1326 = *((_DWORD *)v207 + 585);
                    *((_DWORD *)v207 + 585) = v1324;
                    if ( v1324 == 3 )
                    {
                      (*((void (__fastcall **)(__int64))v207 + 109))(v1323);
                    }
                    else if ( (*((_DWORD *)v207 + 612) & 0x10000000) != 0 || !v1324 )
                    {
                      (*((void (__fastcall **)(__int64))ExFreePool))(v1323);
                    }
                    else
                    {
                      (*((void (__fastcall **)(__int64, _QWORD))v207 + 69))(v1323 - 8, *(_QWORD *)(v1323 - 8));
                    }
                    *((_DWORD *)v207 + 585) = v1326;
                  }
                  *((_DWORD *)v207 + 612) &= ~4u;
                }
                ++*((_DWORD *)v207 + 515);
                v1317 = &v207[v1319];
                v1327 = 48;
                v1328 = v1317;
                v1329 = 6i64;
                do
                {
                  *v1328 = 0i64;
                  v1327 -= 8;
                  ++v1328;
                  --v1329;
                }
                while ( v1329 );
                for ( ; v1327; --v1327 )
                {
                  *(_BYTE *)v1328 = 0;
                  v1328 = (_QWORD *)((char *)v1328 + 1);
                }
                v1330 = (unsigned int)v3785;
                *(_DWORD *)v1317 = v1318;
                v1331 = HalExtensionList;
                *((_QWORD *)v1317 + 1) = HalExtensionList;
                v1332 = (_QWORD *)v1331;
                *((_DWORD *)v1317 + 4) = v1330;
                *((_DWORD *)v207 + 522) += v1330;
                v1300 = *((unsigned int *)v207 + 517);
                v1333 = *((_QWORD *)v207 + 259);
                if ( v1331 < v1331 + v1330 )
                {
                  v1334 = (char *)v1331;
                  do
                  {
                    v1334 += 64;
                  }
                  while ( (unsigned __int64)v1334 < v1331 + v1330 );
                }
                v1335 = *((_QWORD *)v207 + 259);
                v1310 = (unsigned int)v1330 >> 7;
                if ( (_DWORD)v1310 )
                {
                  do
                  {
                    v1336 = 8i64;
                    do
                    {
                      v1337 = v1332[1] ^ __ROL8__(*v1332 ^ v1335, v1300);
                      v1332 += 2;
                      v1335 = __ROL8__(v1337, v1300);
                      --v1336;
                    }
                    while ( v1336 );
                    v1338 = (__ROL8__(v1333 ^ ((unsigned __int64)v1332 - v1331), 17) ^ v1333 ^ ((unsigned __int64)v1332
                                                                                              - v1331))
                          * (unsigned __int128)0x7010008004002001ui64;
                    v4003 = *((_QWORD *)&v1338 + 1);
                    v1300 = ((unsigned __int8)v1338 ^ (unsigned __int8)(BYTE8(v1338) ^ v1300)) & 0x3F;
                    if ( !(_DWORD)v1300 )
                      v1300 = 1i64;
                    v875 = (_DWORD)v1310 == 1;
                    v1310 = (unsigned int)(v1310 - 1);
                  }
                  while ( !v875 );
                  LODWORD(v1330) = v3785;
                }
                v1315 = v1330 & 0x7F;
                if ( (unsigned int)v1315 >= 8 )
                {
                  v1339 = (unsigned __int64)(v1330 & 0x7F) >> 3;
                  do
                  {
                    v1335 = __ROL8__(*v1332++ ^ v1335, v1300);
                    v1315 = (unsigned int)(v1315 - 8);
                    --v1339;
                  }
                  while ( v1339 );
                }
                if ( (_DWORD)v1315 )
                {
                  do
                  {
                    v1340 = *(unsigned __int8 *)v1332;
                    v1332 = (_QWORD *)((char *)v1332 + 1);
                    v1335 = __ROL8__(v1340 ^ v1335, v1300);
                    v875 = (_DWORD)v1315 == 1;
                    v1315 = (unsigned int)(v1315 - 1);
                  }
                  while ( !v875 );
                }
                for ( i2 = v1335; ; LODWORD(v1335) = i2 ^ v1335 )
                {
                  i2 >>= 31;
                  if ( !i2 )
                    break;
                }
                *((_DWORD *)v1317 + 5) = v1335 & 0x7FFFFFFF;
                *((_DWORD *)v207 + 522) += v1330;
                v1316 = (int)Src;
              }
              else
              {
                LODWORD(v1330) = v3785;
                v207 = v1292;
                *(_DWORD *)v1317 = v1318;
                v1331 = HalExtensionList;
              }
              if ( (*((_DWORD *)v207 + 612) & 0x40000000) != 0 && (_DWORD)v1330 )
                sub_1403ED6CC(v207, v1331, (unsigned int)v1330, v1317 + 28);
              *((_DWORD *)v1317 + 6) = 0;
              if ( (_DWORD)v3783 )
                *((_DWORD *)v1317 + 6) = 1;
              v1342 = v3786;
              v3981 = v207;
              *(_DWORD *)(v3786 + 144) = 35;
              *(_DWORD *)(v1342 + 184) = *(_DWORD *)(v1342 + 184) & 0xFFFFFFFE | (v1316 != 0);
              if ( *(_DWORD *)(v1342 + 160) >= 0x94u )
              {
                v1343 = v3787;
                v1344 = *(_QWORD *)(v1342 + 152);
                v1345 = (*((__int64 (__fastcall **)(ULONG_PTR, unsigned __int64, __int64, __int64))v207 + 63))(
                          v3787,
                          v1315,
                          v1310,
                          v1300);
                if ( !v1345 )
                  return 0;
                v1346 = v3787 + *(unsigned int *)(v1345 + 80);
                v1315 = *(_DWORD *)(v1342 + 184) | 2u;
                *(_DWORD *)(v1342 + 184) = v1315;
                v1347 = v1315;
                v1348 = *(_QWORD **)(v1344 + 112);
                if ( (unsigned __int64)v1348 >= v1343 && (unsigned __int64)v1348 < v1346 )
                {
                  v1347 = v1315 | 4;
                  *(_QWORD *)(v1342 + 168) = *v1348;
                  *(_DWORD *)(v1342 + 184) = v1315 | 4;
                }
                v1349 = *(_QWORD **)(v1344 + 120);
                if ( (unsigned __int64)v1349 >= v1343 && (unsigned __int64)v1349 < v1346 )
                {
                  *(_QWORD *)(v1342 + 176) = *v1349;
                  *(_DWORD *)(v1342 + 184) = v1347 | 8;
                }
              }
              v875 = (*((_DWORD *)v207 + 612) & 0x400000) == 0;
              v3999 = v207;
              if ( v875 )
                goto LABEL_2145;
              v1350 = v3787;
              HalExtensionList = (*((__int64 (__fastcall **)(ULONG_PTR, unsigned __int64, __int64, __int64))v207 + 63))(
                                   v3787,
                                   v1315,
                                   v1310,
                                   v1300);
              if ( !HalExtensionList )
                goto LABEL_1906;
              v1351 = *(unsigned __int16 *)(HalExtensionList + 6);
              v3786 = (unsigned int)v3784 / 0xCui64;
              LOWORD(v3789) = v1351;
              if ( !(_WORD)v1351 )
              {
                if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                {
                  v3845[13] = 317;
                  KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, 0i64, 0i64);
                }
                goto LABEL_1909;
              }
              v1352 = v1351;
              v1353 = (unsigned int *)v3788;
              LODWORD(v3785) = v1351;
              v1354 = v3788 + 12i64 * ((unsigned int)v3784 / 0xC);
              LODWORD(v3783) = 0;
              v1355 = 0;
              v1356 = *(unsigned __int16 *)(HalExtensionList + 20) + 24i64;
              v3790 = v1354;
              v1357 = HalExtensionList + v1356;
              v3794 = v1357;
              v1358 = v3787;
              while ( 2 )
              {
                v1359 = 5i64 * v1355;
                v1360 = *(_DWORD *)(v1357 + 40i64 * v1355 + 16);
                v1361 = *(_DWORD *)(v1357 + 40i64 * v1355 + 12);
                if ( v1360 <= *(_DWORD *)(v1357 + 40i64 * v1355 + 8) )
                  v1360 = *(_DWORD *)(v1357 + 40i64 * v1355 + 8);
                v3792 = 5i64 * v1355;
                v1362 = v1361 + v1360;
                LODWORD(v3791) = v1361;
                if ( v1355 )
                {
                  if ( v1362 >= *(_DWORD *)(v1357 + 40i64 * (v1355 - 1) + 12) )
                  {
                    v1355 = v3783;
                    goto LABEL_1918;
                  }
                  if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                  {
                    v3845[14] = 317;
                    KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, 1ui64, 0i64);
                  }
LABEL_1945:
                  if ( !*((_DWORD *)v207 + 574) )
                  {
                    *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                    *((_QWORD *)v207 + 289) = 0i64;
                    v1376 = v3787;
                    *((_QWORD *)v207 + 290) = 271i64;
                    *((_QWORD *)v207 + 291) = v1376;
                    *((_DWORD *)v207 + 574) = 1;
LABEL_1911:
                    __ba(v207, 0i64);
                  }
LABEL_1906:
                  v1247 = -1073741701;
LABEL_1955:
                  if ( v1247 >= 0 )
                    goto LABEL_2146;
LABEL_1956:
                  if ( v1247 != -1073741554 )
                    return 0;
                  goto LABEL_2146;
                }
LABEL_1918:
                if ( v1353 != (unsigned int *)v1354 )
                {
                  do
                  {
                    v1363 = v1353[1];
                    if ( *v1353 >= v1362 || v1363 <= v1361 )
                      break;
                    if ( *v1353 < v1361 || v1363 > v1362 )
                    {
                      if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                      {
                        v3845[17] = 317;
                        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, 2ui64, 0i64);
                      }
                      goto LABEL_1945;
                    }
                    v1364 = v1353[2];
                    if ( (v1364 & 1) != 0 || (*(_BYTE *)(v1364 + v1358) & 0x20) != 0 )
                    {
                      v1365 = *(_DWORD *)(v1357 + 8 * v1359 + 16);
                      v1366 = *(_DWORD *)(v1357 + 8 * v1359 + 12);
                      if ( v1365 <= *(_DWORD *)(v1357 + 8 * v1359 + 8) )
                        v1365 = *(_DWORD *)(v1357 + 8 * v1359 + 8);
                      v1367 = v1366 + v1365;
                      v1368 = (unsigned int *)(*((__int64 (__fastcall **)(unsigned int *, ULONG_PTR, ULONG_PTR, __int64))RtlpConvertFunctionEntry))(
                                                v1353,
                                                v1358,
                                                v1357,
                                                v1352);
                      v1369 = v1368;
                      if ( *v1368 < v1366 || v1368[1] > v1367 )
                      {
                        v1370 = v3787;
                        if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                        {
                          v3845[16] = 317;
                          KeBugCheckEx(
                            __ROR4__(317, 160),
                            0xAui64,
                            v3787,
                            ((_DWORD)v1368 - (_DWORD)v3787) | 0x80000000,
                            0i64);
                        }
                        if ( !*((_DWORD *)v207 + 574) )
                        {
                          *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                          *((_QWORD *)v207 + 289) = 0i64;
                          *((_QWORD *)v207 + 290) = 271i64;
                          *((_QWORD *)v207 + 291) = v1370;
                          *((_DWORD *)v207 + 574) = 1;
                          __ba(v207, 0i64);
                        }
                      }
                      v1371 = (unsigned int *)(*((__int64 (__fastcall **)(unsigned int *, ULONG_PTR, ULONG_PTR))RtlpLookupPrimaryFunctionEntry))(
                                                v1369,
                                                v3787,
                                                v3787 + *v1369);
                      if ( *v1371 < v1366 || v1371[1] > v1367 )
                      {
                        v1372 = v3787;
                        v1373 = ((_DWORD)v1371 - v3787) | 0x80000000;
                        if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                        {
                          v3845[15] = 317;
                          KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, v1373, 0i64);
                        }
                        if ( !*((_DWORD *)v207 + 574) )
                        {
                          *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                          *((_QWORD *)v207 + 289) = 0i64;
                          *((_QWORD *)v207 + 290) = 271i64;
                          *((_QWORD *)v207 + 291) = v1372;
                          *((_DWORD *)v207 + 574) = 1;
                          __ba(v207, 0i64);
                        }
                      }
                      v1359 = v3792;
                      v1361 = v3791;
                      v1357 = v3794;
                      v1354 = v3790;
                      v1358 = v3787;
                    }
                    v1353 += 3;
                  }
                  while ( v1353 != (unsigned int *)v1354 );
                  v1355 = v3783;
                  v1352 = (unsigned int)v3785;
                }
                LODWORD(v3783) = ++v1355;
                if ( v1355 < (unsigned int)v1352 )
                  continue;
                break;
              }
              v1374 = v3786;
              v1375 = HalExtensionList;
              v1350 = v3787;
              if ( v1353 != (unsigned int *)v1354 )
              {
                if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                {
                  v3845[18] = 317;
                  KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, 3ui64, 0i64);
                }
LABEL_1909:
                if ( !*((_DWORD *)v207 + 574) )
                {
                  *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                  *((_QWORD *)v207 + 289) = 0i64;
                  *((_QWORD *)v207 + 290) = 271i64;
                  *((_QWORD *)v207 + 291) = v1350;
                  *((_DWORD *)v207 + 574) = 1;
                  goto LABEL_1911;
                }
                goto LABEL_1906;
              }
              v1377 = (_DWORD)v3786 ? (v3786 + 6) & 0xFFFFFFF8 : 0;
              v1378 = *((unsigned int *)v207 + 505);
              v1379 = v1378 + v1377 + 24 * (v1352 + 2);
              if ( v1379 <= *((_DWORD *)v207 + 647) )
              {
                v1380 = (__int64)v207;
                HalExtensionList = (ULONG_PTR)v207;
                *((_DWORD *)v207 + 505) = v1379;
              }
              else
              {
                HalExtensionList = sub_140B0F020(v207, v1379, *((_DWORD *)v207 + 585));
                v1380 = HalExtensionList;
                if ( !HalExtensionList )
                {
                  v1247 = -1073741670;
                  goto LABEL_1955;
                }
                v1381 = *((_DWORD *)v207 + 612);
                if ( (v1381 & 4) == 0 )
                {
                  v1382 = *((_DWORD *)v207 + 505);
                  v1383 = *((_QWORD *)v207 + 249);
                  v1384 = (v1381 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
                  if ( v1382 >= 8 )
                  {
                    v1385 = (unsigned __int64)v1382 >> 3;
                    do
                    {
                      *(_QWORD *)v207 = 0i64;
                      v1382 -= 8;
                      v207 += 8;
                      --v1385;
                    }
                    while ( v1385 );
                  }
                  for ( ; v1382; --v1382 )
                    *v207++ = 0;
                  v1386 = *(_DWORD *)(v1380 + 2340);
                  *(_DWORD *)(v1380 + 2340) = v1384;
                  if ( v1384 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v1380 + 872))(v1383);
                  }
                  else if ( (*(_DWORD *)(v1380 + 2448) & 0x10000000) != 0 || !v1384 )
                  {
                    (*(void (__fastcall **)(__int64))(v1380 + 248))(v1383);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v1380 + 552))(v1383 - 8, *(_QWORD *)(v1383 - 8));
                  }
                  v1380 = HalExtensionList;
                  v1374 = v3786;
                  *(_DWORD *)(HalExtensionList + 2340) = v1386;
                }
                *(_DWORD *)(v1380 + 2448) &= ~4u;
                LODWORD(v1352) = v3785;
                v1354 = v3790;
              }
              ++*(_DWORD *)(v1380 + 2060);
              v1387 = v1380 + v1378;
              v1388 = 48;
              v1389 = (_QWORD *)(v1380 + v1378);
              v1390 = 6i64;
              do
              {
                *v1389 = 0i64;
                v1388 -= 8;
                ++v1389;
                --v1390;
              }
              while ( v1390 );
              for ( ; v1388; --v1388 )
              {
                *(_BYTE *)v1389 = 0;
                v1389 = (_QWORD *)((char *)v1389 + 1);
              }
              v1391 = v3788;
              *(_DWORD *)v1387 = 30;
              *(_QWORD *)(v1387 + 8) = v1391;
              *(_DWORD *)(v1387 + 16) = 0;
              v1392 = *(_QWORD *)(v1380 + 2072);
              for ( i3 = v1392; ; LODWORD(v1392) = i3 ^ v1392 )
              {
                i3 >>= 31;
                if ( !i3 )
                  break;
              }
              v1394 = v3787;
              v1395 = (unsigned __int16)v3789;
              *(_DWORD *)(v1387 + 20) = v1392 & 0x7FFFFFFF;
              v207 = (_BYTE *)v1380;
              *(_QWORD *)(v1387 + 24) = v1394;
              *(_DWORD *)(v1387 + 32) = *(_DWORD *)(v1375 + 80);
              *(_DWORD *)(v1387 + 36) = v3784;
              v875 = (_DWORD)Src == 0;
              *(_WORD *)(v1387 + 40) = v1395;
              LOWORD(v1394) = *(_WORD *)(v1387 + 42) & 0xFFFE;
              v3999 = (_BYTE *)v1380;
              *(_WORD *)(v1387 + 42) = v1394 | !v875;
              v3786 = v1387 + 48;
              if ( v1374 )
                v1396 = (__int64 *)(v1387 + 48 + (((unsigned int)(v1374 - 1) + 7i64) & 0xFFFFFFFFFFFFFFF8ui64));
              else
                v1396 = (__int64 *)(v1387 + 48);
              v1397 = (unsigned int *)v3788;
              v3792 = (ULONG_PTR)v1396;
              v1398 = &v1396[3 * v1395];
              v3798 = v1398;
              if ( v1374 )
                v3791 = v3788 + 12;
              else
                v3791 = v1354;
              if ( (_DWORD)v1352 )
              {
                v1399 = (unsigned int)v1352;
                v1400 = v1396 + 1;
                do
                {
                  v1401 = 2i64;
                  do
                  {
                    *(v1400 - 2) = 0;
                    *(v1400 - 1) = 0;
                    *v1400 = 0x80000000;
                    v1400 += 3;
                    --v1401;
                  }
                  while ( v1401 );
                  --v1399;
                }
                while ( v1399 );
                v1397 = (unsigned int *)v3788;
              }
              if ( v1396 == v1398 )
              {
LABEL_2145:
                v3981 = v207;
                goto LABEL_2146;
              }
              v1402 = (_DWORD *)v3794;
              while ( 2 )
              {
                v875 = (v1402[9] & 0x2000000) == 0;
                v1403 = 0;
                LODWORD(Src) = 0;
                if ( !v875 )
                  goto LABEL_1997;
                v1404 = *v1402;
                if ( *v1402 == 1414090313 )
                {
                  if ( v1402[1] == 1195525195 )
                    goto LABEL_1997;
LABEL_2003:
                  if ( v1404 != 1095914053 || *((_WORD *)v1402 + 2) != 16724 )
                    goto LABEL_2005;
LABEL_1997:
                  v1403 = 1;
                  LODWORD(Src) = 1;
                }
                else
                {
                  if ( v1404 != 1162297680 )
                    goto LABEL_2003;
                  v1405 = *((_WORD *)v1402 + 2);
                  if ( v1405 == 30839 || v1405 == 29303 || v1405 == 30583 )
                    goto LABEL_1997;
LABEL_2005:
                  v1406 = *(char **)(v1380 + 2352);
                  v1407 = 7;
                  v1408 = *(__int64 **)(v1380 + 2360);
                  v1409 = (char *)v1402 - v1406;
                  v1410 = *(char **)(HalExtensionList + 2368);
                  v1411 = *(char **)(HalExtensionList + 2376);
                  while ( 1 )
                  {
                    v1412 = (unsigned __int8)v1406[v1409];
                    v1413 = (unsigned __int8)*v1406++;
                    if ( v1412 != v1413 )
                      break;
                    if ( !--v1407 )
                    {
LABEL_2023:
                      v1403 = 1;
                      LODWORD(Src) = 1;
                      goto LABEL_2024;
                    }
                  }
                  v1414 = 8;
                  v1415 = (__int64 *)v1402;
                  while ( 1 )
                  {
                    v1416 = *v1415++;
                    v1417 = *v1408++;
                    if ( v1416 != v1417 )
                      break;
                    v1414 -= 8;
                    if ( v1414 < 8 )
                    {
                      if ( !v1414 )
                        goto LABEL_2023;
                      while ( 1 )
                      {
                        v1418 = *(unsigned __int8 *)v1415;
                        v1415 = (__int64 *)((char *)v1415 + 1);
                        v1419 = *(unsigned __int8 *)v1408;
                        v1408 = (__int64 *)((char *)v1408 + 1);
                        if ( v1418 != v1419 )
                          goto LABEL_2016;
                        if ( !--v1414 )
                          goto LABEL_2023;
                      }
                    }
                  }
LABEL_2016:
                  v1420 = 4;
                  v1421 = (char *)v1402 - v1410;
                  while ( 1 )
                  {
                    v1422 = (unsigned __int8)v1410[v1421];
                    v1423 = (unsigned __int8)*v1410++;
                    if ( v1422 != v1423 )
                      break;
                    if ( !--v1420 )
                      goto LABEL_2023;
                  }
                  v1424 = 6;
                  v1425 = (char *)v1402 - v1411;
                  while ( 1 )
                  {
                    v1426 = (unsigned __int8)v1411[v1425];
                    v1427 = (unsigned __int8)*v1411++;
                    if ( v1426 != v1427 )
                      break;
                    if ( !--v1424 )
                      goto LABEL_2023;
                  }
LABEL_2024:
                  v1396 = (__int64 *)v3792;
                  v1380 = HalExtensionList;
                }
                v1428 = v1402[9];
                if ( v1428 < 0 )
                {
                  v1403 = 1;
                  LODWORD(Src) = 1;
                  goto LABEL_2028;
                }
                if ( v1403 )
                {
LABEL_2028:
                  if ( *v1402 == 1414090313 && v1402[1] == 1195525195 )
                  {
                    if ( (*(_DWORD *)(v1380 + 2452) & 0x2000) != 0 )
                      v1403 = 0;
                    LODWORD(Src) = v1403;
                  }
                }
                v1429 = v3787;
                if ( (*(_DWORD *)(v1380 + 2452) & 0x4000) != 0
                  && (v1428 & 0x20000000) != 0
                  && (v3787 == *(_QWORD *)(v1380 + 1504) || v3787 == *(_QWORD *)(v1380 + 1512)) )
                {
                  v1403 = 1;
                  LODWORD(Src) = 1;
                }
                v1430 = v1402[4];
                v1431 = (unsigned int)v1402[3];
                v1432 = v3790;
                if ( v1430 <= v1402[2] )
                  v1430 = v1402[2];
                v1433 = v1431 + v1430;
                LODWORD(v3784) = v1402[3];
                LODWORD(v3783) = v1433;
                if ( v1397 == (unsigned int *)v3790 )
                {
                  v1436 = 0;
                  v1438 = (_DWORD)v1431 != 0;
                  v1437 = v1431;
                }
                else
                {
                  v1434 = *v1397;
                  v1435 = v1397[1];
                  v1436 = v1435;
                  v1437 = v1431;
                  v1438 = v1434 < (unsigned int)v1431;
                  if ( v1434 > (unsigned int)v1431 )
                  {
                    if ( v1435 > v1433 )
                      goto LABEL_2070;
                    if ( v1403 )
                    {
                      v1457 = v3788;
                      goto LABEL_2074;
                    }
                    *(_DWORD *)v1396 = v1431;
                    v1437 = v1434;
                    *((_DWORD *)v1396 + 1) = v1434;
                    v1439 = (char *)(v1429 + v1431);
                    LODWORD(v3785) = v1435;
                    v1440 = v1434 - v1431;
                    v1441 = (unsigned __int64)&v1439[v1434 - (unsigned int)v1431];
                    v1442 = 0;
                    while ( 1 )
                    {
                      v1443 = *(&v4190 + v1442);
                      if ( (unsigned __int64)v1439 < v1443 + (unsigned int)v4160[v1442] && v1441 > v1443 )
                        break;
                      if ( ++v1442 >= 6 )
                      {
                        *(_DWORD *)(v1380 + 2088) += v1440;
                        v1444 = v1439;
                        v1445 = *(_DWORD *)(v1380 + 2068);
                        v1446 = *(_QWORD *)(v1380 + 2072);
                        for ( i4 = v1439; (unsigned __int64)v1444 < v1441; v1444 += 64 )
                          _mm_prefetchnta(v1444);
                        v1448 = v1446;
                        v1449 = v1440 >> 7;
                        if ( v1440 >> 7 )
                        {
                          do
                          {
                            v1450 = 8i64;
                            do
                            {
                              v1451 = i4[1] ^ __ROL8__(*i4 ^ v1448, v1445);
                              i4 += 2;
                              v1448 = __ROL8__(v1451, v1445);
                              --v1450;
                            }
                            while ( v1450 );
                            v1452 = __ROL8__(v1446 ^ ((char *)i4 - v1439), 17) ^ v1446 ^ ((char *)i4 - v1439);
                            v4004 = (v1452 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                            v1445 = ((unsigned __int8)v1452 ^ (unsigned __int8)(v4004 ^ v1445)) & 0x3F;
                            if ( !v1445 )
                              LOBYTE(v1445) = 1;
                            --v1449;
                          }
                          while ( v1449 );
                          v1436 = v3785;
                        }
                        v1453 = v1440 & 0x7F;
                        if ( v1453 >= 8 )
                        {
                          v1454 = (unsigned __int64)v1453 >> 3;
                          do
                          {
                            v1448 = __ROL8__(*i4++ ^ v1448, v1445);
                            v1453 -= 8;
                            --v1454;
                          }
                          while ( v1454 );
                        }
                        for ( ; v1453; --v1453 )
                        {
                          v1455 = *(unsigned __int8 *)i4;
                          i4 = (_QWORD *)((char *)i4 + 1);
                          v1448 = __ROL8__(v1455 ^ v1448, v1445);
                        }
                        for ( i5 = v1448 >> 31; i5; i5 >>= 31 )
                          LODWORD(v1448) = i5 ^ v1448;
                        v1433 = v3783;
                        v1403 = (int)Src;
                        v1380 = HalExtensionList;
                        *(_DWORD *)(v3792 + 8) = v1448 & 0x7FFFFFFF;
                        break;
                      }
                    }
                    v1432 = v3790;
LABEL_2070:
                    if ( v1436 <= v1433 )
                    {
                      v1457 = v3788;
                      if ( v3788 != v1432 )
                      {
LABEL_2074:
                        v1458 = (unsigned int *)v3791;
                        v1459 = *(_DWORD *)(v3791 + 4);
                        LODWORD(v3785) = v1459;
                        if ( v1459 <= v1433 )
                        {
                          while ( v1458 != (unsigned int *)v1432 )
                          {
                            if ( v1403 )
                            {
                              v1460 = 0x80;
                            }
                            else
                            {
                              v1461 = *(unsigned int *)(v1457 + 4);
                              v1437 = *v1458;
                              if ( *v1458 < (unsigned int)v1461 )
                              {
                                if ( (*(_DWORD *)(v1380 + 2448) & 0x200000) == 0 )
                                {
                                  v3845[19] = 317;
                                  KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3787, 6ui64, 0i64);
                                }
                                if ( !*(_DWORD *)(v1380 + 2296) )
                                {
                                  *(_QWORD *)(v1380 + 2304) = v1380 - 0x5C5FC0A76E374B18i64;
                                  *(_QWORD *)(v1380 + 2312) = 0i64;
                                  v1462 = v3787;
                                  *(_QWORD *)(v1380 + 2320) = 271i64;
                                  *(_QWORD *)(v1380 + 2328) = v1462;
                                  *(_DWORD *)(v1380 + 2296) = 1;
                                  __ba(v1380, 0i64);
                                }
                              }
                              v1463 = (_QWORD *)(v3787 + v1461);
                              v1464 = v1437 - v1461;
                              v1465 = v3787 + v1461 + v1437 - (unsigned int)v1461;
                              for ( i6 = 0; i6 < 6; ++i6 )
                              {
                                v1467 = *(&v4190 + i6);
                                if ( (unsigned __int64)v1463 < v1467 + (unsigned int)v4160[i6] && v1465 > v1467 )
                                  goto LABEL_2107;
                              }
                              if ( v1464 < 4 )
                              {
LABEL_2107:
                                v1460 = 0x80;
                                goto LABEL_2108;
                              }
                              v1468 = HalExtensionList;
                              v1469 = v1463;
                              *(_DWORD *)(HalExtensionList + 2088) += v1464;
                              v1470 = *(_DWORD *)(v1468 + 2068);
                              v1471 = *(_QWORD *)(v1468 + 2072);
                              v1472 = (char *)v1463;
                              if ( (unsigned __int64)v1463 < v1465 )
                              {
                                do
                                {
                                  v1472 += 64;
                                }
                                while ( (unsigned __int64)v1472 < v1465 );
                              }
                              v1473 = v1471;
                              v1474 = v1464 >> 7;
                              if ( v1464 >> 7 )
                              {
                                do
                                {
                                  v1475 = 8i64;
                                  do
                                  {
                                    v1476 = v1469[1] ^ __ROL8__(*v1469 ^ v1473, v1470);
                                    v1469 += 2;
                                    v1473 = __ROL8__(v1476, v1470);
                                    --v1475;
                                  }
                                  while ( v1475 );
                                  v1477 = (__ROL8__(v1471 ^ ((char *)v1469 - (char *)v1463), 17) ^ v1471 ^ ((char *)v1469 - (char *)v1463))
                                        * (unsigned __int128)0x7010008004002001ui64;
                                  v4005 = *((_QWORD *)&v1477 + 1);
                                  v1470 = ((unsigned __int8)(v1477 ^ BYTE8(v1477)) ^ (unsigned __int8)v1470) & 0x3F;
                                  if ( !v1470 )
                                    LOBYTE(v1470) = 1;
                                  --v1474;
                                }
                                while ( v1474 );
                                v1459 = v3785;
                              }
                              v1478 = v1464 & 0x7F;
                              if ( v1478 >= 8 )
                              {
                                v1479 = (unsigned __int64)v1478 >> 3;
                                do
                                {
                                  v1473 = __ROL8__(*v1469++ ^ v1473, v1470);
                                  v1478 -= 8;
                                  --v1479;
                                }
                                while ( v1479 );
                              }
                              for ( ; v1478; --v1478 )
                              {
                                v1480 = *(unsigned __int8 *)v1469;
                                v1469 = (_QWORD *)((char *)v1469 + 1);
                                v1473 = __ROL8__(v1480 ^ v1473, v1470);
                              }
                              for ( i7 = v1473 >> 7; i7; i7 >>= 7 )
                                LOBYTE(v1473) = i7 ^ v1473;
                              v1403 = (int)Src;
                              v1460 = v1473 & 0x7F;
LABEL_2108:
                              v1457 = v3788;
                              v1433 = v3783;
                            }
                            v1482 = (_BYTE *)v3786;
                            v1457 += 12i64;
                            ++v3786;
                            v3788 = v1457;
                            *v1482 = v1460;
                            v1432 = v3790;
                            v1458 = (unsigned int *)(v3791 + 12);
                            v3791 = (ULONG_PTR)v1458;
                            if ( v1458 != (unsigned int *)v3790 )
                            {
                              v1459 = v1458[1];
                              LODWORD(v3785) = v1459;
                            }
                            if ( v1459 > v1433 )
                              break;
                            v1380 = HalExtensionList;
                          }
                        }
                      }
                    }
LABEL_2112:
                    v1483 = v3792;
                    if ( !v1403 && v1437 != v1433 )
                    {
                      v1484 = v3787;
                      *(_DWORD *)(v3792 + 12) = v1437;
                      *(_DWORD *)(v1483 + 16) = v1433;
                      v1485 = *(unsigned int *)(v1483 + 12);
                      v1486 = v1433 - v1485;
                      v1487 = (_QWORD *)(v1485 + v1484);
                      v1488 = (unsigned __int64)v1487 + v1433 - (unsigned int)v1485;
                      LODWORD(Src) = v1486;
                      v1489 = 0;
                      while ( 1 )
                      {
                        v1490 = *(&v4190 + v1489);
                        if ( (unsigned __int64)v1487 < v1490 + (unsigned int)v4160[v1489] && v1488 > v1490 )
                          break;
                        if ( ++v1489 >= 6 )
                        {
                          v1491 = HalExtensionList;
                          v1492 = v1487;
                          *(_DWORD *)(HalExtensionList + 2088) += v1486;
                          v1493 = *(_DWORD *)(v1491 + 2068);
                          v1494 = *(_QWORD *)(v1491 + 2072);
                          v1495 = (char *)v1487;
                          if ( (unsigned __int64)v1487 < v1488 )
                          {
                            do
                            {
                              v1495 += 64;
                            }
                            while ( (unsigned __int64)v1495 < v1488 );
                          }
                          v1496 = v1494;
                          v1497 = v1486 >> 7;
                          if ( v1486 >> 7 )
                          {
                            do
                            {
                              v1498 = 8i64;
                              do
                              {
                                v1499 = v1492[1] ^ __ROL8__(*v1492 ^ v1496, v1493);
                                v1492 += 2;
                                v1496 = __ROL8__(v1499, v1493);
                                --v1498;
                              }
                              while ( v1498 );
                              v1500 = __ROL8__(v1494 ^ ((char *)v1492 - (char *)v1487), 17) ^ v1494 ^ ((char *)v1492 - (char *)v1487);
                              v4006 = (v1500 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                              v1493 = ((unsigned __int8)(v1500 ^ v4006) ^ (unsigned __int8)v1493) & 0x3F;
                              if ( !v1493 )
                                LOBYTE(v1493) = 1;
                              --v1497;
                            }
                            while ( v1497 );
                            LOBYTE(v1486) = (_BYTE)Src;
                          }
                          v1501 = v1486 & 0x7F;
                          if ( v1501 >= 8 )
                          {
                            v1502 = (unsigned __int64)v1501 >> 3;
                            do
                            {
                              v1496 = __ROL8__(*v1492++ ^ v1496, v1493);
                              v1501 -= 8;
                              --v1502;
                            }
                            while ( v1502 );
                          }
                          for ( ; v1501; --v1501 )
                          {
                            v1503 = *(unsigned __int8 *)v1492;
                            v1492 = (_QWORD *)((char *)v1492 + 1);
                            v1496 = __ROL8__(v1503 ^ v1496, v1493);
                          }
                          for ( i8 = v1496; ; LODWORD(v1496) = i8 ^ v1496 )
                          {
                            i8 >>= 31;
                            if ( !i8 )
                              break;
                          }
                          v1483 = v3792;
                          *(_DWORD *)(v3792 + 20) = v1496 & 0x7FFFFFFF;
                          break;
                        }
                      }
                      v1433 = v3783;
                    }
                    v1397 = (unsigned int *)v3788;
                    if ( v3788 != v3790 && *(_DWORD *)v3788 >= (unsigned int)v3784 && *(_DWORD *)(v3788 + 4) <= v1433 )
                    {
                      v1505 = v3791;
                      if ( v3791 != v3790 )
                      {
                        v1506 = v3786;
                        *(_BYTE *)v3786 = 0x80;
                        v3786 = v1506 + 1;
                        v3791 = v1505 + 12;
                      }
                      v1397 += 3;
                      v3788 = (ULONG_PTR)v1397;
                    }
                    v1396 = (__int64 *)(v1483 + 24);
                    v1380 = HalExtensionList;
                    v1402 = (_DWORD *)(v3794 + 40);
                    v3792 = (ULONG_PTR)v1396;
                    v3794 += 40i64;
                    if ( v1396 == v3798 )
                    {
                      v207 = v3999;
                      goto LABEL_2145;
                    }
                    continue;
                  }
                }
                break;
              }
              if ( !v1438 )
                goto LABEL_2070;
              goto LABEL_2112;
            }
          }
          *(_DWORD *)(v1288 + 32) |= 2u;
          goto LABEL_1825;
        }
        LODWORD(v3791) = ++v916;
        if ( v916 >= *((_DWORD *)v207 + 515) )
          goto LABEL_1308;
      }
      v922 = v916 - v920;
      v920 = v916;
      while ( 2 )
      {
        v923 = *v921;
        if ( *v921 > 28 )
        {
          v931 = v923 - 30;
          if ( !v931 )
          {
            v929 = (((v921[9] != 0 ? v921[9] - 1 : 0) / 0xCu + 7) & 0xFFFFFFF8)
                 + 24 * (*((unsigned __int16 *)v921 + 20) + 2);
            goto LABEL_1297;
          }
          v932 = v931 - 3;
          if ( !v932 || (v933 = v932 - 1) == 0 )
          {
            v929 = 20 * (unsigned int)(((v921[8] & 0xFFF) + (unsigned __int64)(unsigned int)v921[10] + 4095) >> 12) + 48;
            goto LABEL_1297;
          }
          v928 = v933 == 9;
LABEL_1292:
          if ( !v928 )
          {
            v929 = 48i64;
            goto LABEL_1297;
          }
        }
        else
        {
          if ( v923 == 28 )
          {
            v930 = *((unsigned __int16 *)v921 + 20);
            goto LABEL_1285;
          }
          v924 = v923 - 1;
          if ( v924 )
          {
            v925 = v924 - 6;
            if ( !v925 )
            {
              v929 = (unsigned int)(24 * (v921[6] + 2));
              goto LABEL_1297;
            }
            v926 = v925 - 1;
            if ( v926 )
            {
              v927 = v926 - 2;
              if ( v927 )
              {
                v928 = v927 == 2;
                goto LABEL_1292;
              }
              v929 = (unsigned int)(16 * (v921[7] + 3));
LABEL_1297:
              v921 = (int *)((char *)v921 + v929);
              if ( !--v922 )
              {
                LODWORD(v919) = (_DWORD)Src;
                v916 = v3791;
                goto LABEL_1299;
              }
              continue;
            }
            v930 = *((unsigned __int16 *)v921 + 16);
LABEL_1285:
            v929 = (v930 + 55) & 0xFFFFFFF8;
            goto LABEL_1297;
          }
        }
        break;
      }
      v929 = 4 * (v921[4] / 0xCu) + 48;
      goto LABEL_1297;
    }
LABEL_1309:
    v936 = (*((__int64 (__fastcall **)(ULONG_PTR, __int64))v207 + 85))(v870, v914);
    LODWORD(v3791) = v936;
    LODWORD(v3785) = v3837[0];
    if ( (v3796 & 0x10) != 0 && (*((_DWORD *)v207 + 613) & 0x400) == 0 )
    {
      v911 = v3796 & 0xFFFFFFEF;
      LODWORD(v3793) = v3796 & 0xFFFFFFEF;
    }
    if ( (v911 & 0x10) != 0 && !(unsigned int)sub_140B100E0(v207, v3794) )
    {
      v911 &= ~0x10u;
      LODWORD(v3793) = v911;
    }
    v937 = (char **)*((_QWORD *)v207 + 165);
    v3789 = v911 & 1;
    v938 = !(v911 & 1) + 1;
    _disable();
    v939 = v3981;
    v940 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + *((_QWORD *)v3981 + 202));
    _enable();
    (*((void (__fastcall **)(__int64))v939 + 45))(v940);
    LOBYTE(v941) = 1;
    (*((void (__fastcall **)(_QWORD, __int64))v939 + 29))(*((_QWORD *)v939 + 166), v941);
    v942 = *v937;
    if ( *v937 != (char *)v937 )
    {
      v943 = *((_QWORD *)v939 + 234);
      while ( 1 )
      {
        v944 = *(_QWORD *)&v942[*((_QWORD *)v939 + 235) - v943];
        if ( v3794 >= v944 && v3794 < v944 + *(unsigned int *)&v942[*((_QWORD *)v939 + 236) - v943] )
          break;
        v942 = *(char **)v942;
        if ( v942 == (char *)v937 )
          goto LABEL_1322;
      }
      (*((void (__fastcall **)(char *, _QWORD))v939 + 27))(&v942[-v943], v938);
    }
LABEL_1322:
    (*((void (__fastcall **)(_QWORD))v939 + 35))(*((_QWORD *)v939 + 166));
    (*((void (**)(void))v939 + 46))();
    if ( (*((_DWORD *)v939 + 612) & 0x40000000) != 0 )
    {
      v946 = sub_140B16070(&v3985, v3794, (unsigned int)v3793);
      v887 = v3985;
      goto LABEL_1514;
    }
    v947 = v3794;
    v4188 = 0i64;
    LOBYTE(v945) = 1;
    v4156[4] = 0;
    v4185 = (*((__int64 (__fastcall **)(ULONG_PTR, __int64, _QWORD, int *))v939 + 62))(v3794, v945, 0i64, v3837);
    v948 = v3837[0] & (unsigned int)-(v4185 != 0);
    v3837[0] = v948;
    v949 = (__int64 (__fastcall *)(ULONG_PTR, __int64, __int64, int *))*((_QWORD *)v939 + 62);
    v4156[1] = v948;
    LOBYTE(v948) = 1;
    v950 = v949(v3794, v948, 12i64, v3837);
    v951 = v950;
    v3790 = v950;
    v4186 = v950;
    LOBYTE(v951) = 1;
    v3837[0] &= -(v950 != 0);
    v952 = (__int64 (__fastcall *)(ULONG_PTR, __int64, __int64, int *))*((_QWORD *)v939 + 62);
    LODWORD(v3783) = v3837[0];
    v4156[2] = v3837[0];
    v4187 = v952(v3794, v951, 10i64, v3837);
    v3837[0] &= -(v4187 != 0);
    v953 = (__int64 (__fastcall *)(ULONG_PTR))*((_QWORD *)v939 + 63);
    v4156[3] = v3837[0];
    v954 = v953(v3794);
    if ( !v954 )
    {
      if ( (*((_DWORD *)v939 + 612) & 0x200000) == 0 )
      {
        v3845[4] = 317;
        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 7ui64, 0i64);
      }
      if ( !*((_DWORD *)v939 + 574) )
      {
        *((_QWORD *)v939 + 288) = v939 - 0x5C5FC0A76E374B18i64;
        *((_QWORD *)v939 + 289) = 0i64;
        *((_QWORD *)v939 + 290) = 271i64;
        *((_QWORD *)v939 + 291) = v947;
        *((_DWORD *)v939 + 574) = 1;
        __ba(v939, 0i64);
      }
LABEL_1328:
      v955 = (__int64)v3985;
LABEL_1329:
      v3981 = (_BYTE *)v955;
      return 0;
    }
    v956 = (*((__int64 (__fastcall **)(ULONG_PTR, int *))v939 + 148))(v3794, &v3988);
    v957 = *((unsigned int *)v939 + 585);
    v4189 = v956;
    v4156[5] = v3988;
    v4156[0] = *(_DWORD *)(v954 + 84);
    v4184 = v3794;
    v958 = *((unsigned int *)v939 + 505);
    v959 = v936 != 0 ? 0xB : 0;
    LODWORD(v3784) = v959;
    v960 = v958 + 288;
    if ( (unsigned int)(v958 + 288) <= *((_DWORD *)v939 + 647) )
    {
      v887 = v939;
      *((_DWORD *)v939 + 505) = v960;
    }
    else
    {
      v887 = (_BYTE *)sub_140B0F020(v939, v960, v957);
      if ( !v887 )
      {
        v3986[0] = 0i64;
        goto LABEL_1328;
      }
      v961 = *((_DWORD *)v939 + 612);
      if ( (v961 & 4) == 0 )
      {
        v962 = *((_DWORD *)v939 + 505);
        v963 = *((_QWORD *)v939 + 249);
        v964 = (v961 & 0x20000000) != 0 ? *((_DWORD *)v939 + 585) : 0;
        if ( v962 >= 8 )
        {
          v965 = (unsigned __int64)v962 >> 3;
          do
          {
            *(_QWORD *)v939 = 0i64;
            v962 -= 8;
            v939 += 8;
            --v965;
          }
          while ( v965 );
        }
        for ( ; v962; --v962 )
          *v939++ = 0;
        v966 = *((_DWORD *)v887 + 585);
        *((_DWORD *)v887 + 585) = v964;
        if ( v964 == 3 )
        {
          (*((void (__fastcall **)(__int64))v887 + 109))(v963);
        }
        else if ( (*((_DWORD *)v887 + 612) & 0x10000000) != 0 || !v964 )
        {
          (*((void (__fastcall **)(__int64))v887 + 31))(v963);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v887 + 69))(v963 - 8, *(_QWORD *)(v963 - 8));
        }
        *((_DWORD *)v887 + 585) = v966;
      }
      *((_DWORD *)v887 + 612) &= ~4u;
      v959 = v3784;
    }
    v967 = &v887[v958];
    *((_DWORD *)v887 + 515) += 6;
    v968 = (__int64 *)&v4184;
    v969 = v4156;
    v3786 = (unsigned __int64)&v887[v958];
    v3787 = (ULONG_PTR)&v4184;
    v3788 = (ULONG_PTR)v4156;
    HalExtensionList = 6i64;
    do
    {
      v970 = (unsigned int)*v969;
      v971 = 48;
      v972 = (_QWORD *)*v968;
      v973 = v967;
      v974 = 6i64;
      do
      {
        *v973 = 0i64;
        v971 -= 8;
        ++v973;
        --v974;
      }
      while ( v974 );
      for ( ; v971; --v971 )
      {
        *(_BYTE *)v973 = 0;
        v973 = (_QWORD *)((char *)v973 + 1);
      }
      *(_DWORD *)v967 = v959;
      *((_QWORD *)v967 + 1) = v972;
      v975 = v972;
      *((_DWORD *)v967 + 4) = v970;
      v976 = (char *)v972;
      *((_DWORD *)v887 + 522) += v970;
      v977 = *((_DWORD *)v887 + 517);
      v978 = *((_QWORD *)v887 + 259);
      if ( v972 < (_QWORD *)((char *)v972 + v970) )
      {
        do
        {
          _mm_prefetchnta(v976);
          v976 += 64;
        }
        while ( v976 < (char *)v972 + v970 );
      }
      v979 = *((_QWORD *)v887 + 259);
      v980 = (unsigned int)v970 >> 7;
      if ( (unsigned int)v970 >> 7 )
      {
        do
        {
          v981 = 8i64;
          do
          {
            v982 = v975[1] ^ __ROL8__(*v975 ^ v979, v977);
            v975 += 2;
            v979 = __ROL8__(v982, v977);
            --v981;
          }
          while ( v981 );
          v983 = (__ROL8__(v978 ^ ((char *)v975 - (char *)v972), 17) ^ v978 ^ (unsigned __int64)((char *)v975
                                                                                               - (char *)v972))
               * (unsigned __int128)0x7010008004002001ui64;
          v3993 = *((_QWORD *)&v983 + 1);
          v977 = ((unsigned __int8)v983 ^ (unsigned __int8)(BYTE8(v983) ^ v977)) & 0x3F;
          if ( !v977 )
            LOBYTE(v977) = 1;
          --v980;
        }
        while ( v980 );
        v968 = (__int64 *)v3787;
      }
      v984 = v970 & 0x7F;
      if ( v984 >= 8 )
      {
        v985 = (unsigned __int64)(v970 & 0x7F) >> 3;
        do
        {
          v979 = __ROL8__(*v975++ ^ v979, v977);
          v984 -= 8;
          --v985;
        }
        while ( v985 );
      }
      for ( ; v984; --v984 )
      {
        v986 = *(unsigned __int8 *)v975;
        v975 = (_QWORD *)((char *)v975 + 1);
        v979 = __ROL8__(v986 ^ v979, v977);
      }
      for ( i9 = v979 >> 31; i9; i9 >>= 31 )
        LODWORD(v979) = i9 ^ v979;
      v988 = v3788;
      v959 = v3784;
      ++v968;
      *((_DWORD *)v967 + 5) = v979 & 0x7FFFFFFF;
      v967 += 48;
      *((_DWORD *)v887 + 522) += v970;
      v969 = (int *)(v988 + 4);
      v3787 = (ULONG_PTR)v968;
      v875 = HalExtensionList-- == 1;
      v3788 = (ULONG_PTR)v969;
    }
    while ( !v875 );
    v989 = v3786;
    v990 = v3794;
    *(_DWORD *)v3786 = 44;
    *(_QWORD *)(v989 + 24) = v990;
    v991 = *((_DWORD *)v887 + 612);
    if ( (v991 & 0x10000000) != 0 || (v991 & 0x200000) != 0 )
    {
      v992 = v3791;
      if ( !(_DWORD)v3791 )
        goto LABEL_1379;
    }
    else
    {
      v992 = v3791;
      if ( !(_DWORD)v3791 )
      {
        if ( (*((_DWORD *)v887 + 613) & 0x8000) != 0 )
        {
          *(_DWORD *)(v989 + 32) |= 1u;
          if ( (unsigned int)sub_140B100E0(v887, v990) )
            *(_DWORD *)(v989 + 32) |= 4u;
        }
LABEL_1379:
        v3986[0] = (__int64)v887;
        v3985 = v887;
        v946 = sub_140B0D838((int)v3986, v3792, v3785, v990, v992, v3793, (__int64)&v3842, (__int64)&v3841);
        if ( v946 < 0 )
        {
          v207 = v887;
          v3981 = v887;
          goto LABEL_1515;
        }
        v955 = v3986[0];
        v993 = 48;
        v994 = v3841 - v3842;
        v995 = v3986[0] - (_QWORD)v887 + v989;
        v996 = (_QWORD *)(v990 + v3842);
        v3786 = v995;
        v3985 = (_BYTE *)v3986[0];
        v997 = 6i64;
        v998 = (_DWORD *)(v995 + 192);
        HalExtensionList = v995 + 192;
        v999 = (_QWORD *)(v995 + 192);
        do
        {
          *v999 = 0i64;
          v993 -= 8;
          ++v999;
          --v997;
        }
        while ( v997 );
        for ( ; v993; --v993 )
        {
          *(_BYTE *)v999 = 0;
          v999 = (_QWORD *)((char *)v999 + 1);
        }
        v1000 = v996;
        *v998 = v3784;
        v1001 = (char *)v996;
        *(_QWORD *)(v995 + 200) = v996;
        *(_DWORD *)(v995 + 208) = v994;
        *(_DWORD *)(v955 + 2088) += v994;
        v1002 = *(unsigned int *)(v955 + 2068);
        v1003 = *(_QWORD *)(v955 + 2072);
        v1004 = (unsigned __int64)v996 + v994;
        if ( (unsigned __int64)v996 < v1004 )
        {
          do
          {
            _mm_prefetchnta(v1001);
            v1001 += 64;
          }
          while ( (unsigned __int64)v1001 < v1004 );
        }
        v1005 = *(_QWORD *)(v955 + 2072);
        v1006 = v994 >> 7;
        if ( v994 >> 7 )
        {
          do
          {
            v1007 = 8i64;
            do
            {
              v1008 = v1000[1] ^ __ROL8__(*v1000 ^ v1005, v1002);
              v1000 += 2;
              v1005 = __ROL8__(v1008, v1002);
              --v1007;
            }
            while ( v1007 );
            v1009 = (__ROL8__(v1003 ^ ((char *)v1000 - (char *)v996), 17) ^ v1003 ^ (unsigned __int64)((char *)v1000 - (char *)v996))
                  * (unsigned __int128)0x7010008004002001ui64;
            v3994 = *((_QWORD *)&v1009 + 1);
            v1002 = ((unsigned __int8)v1009 ^ (unsigned __int8)(BYTE8(v1009) ^ v1002)) & 0x3F;
            if ( !(_DWORD)v1002 )
              v1002 = 1i64;
            --v1006;
          }
          while ( v1006 );
          v998 = (_DWORD *)HalExtensionList;
        }
        v1010 = v994 & 0x7F;
        if ( v1010 >= 8 )
        {
          v1011 = (unsigned __int64)v1010 >> 3;
          do
          {
            v1005 = __ROL8__(*v1000++ ^ v1005, v1002);
            v1010 -= 8;
            --v1011;
          }
          while ( v1011 );
        }
        for ( ; v1010; --v1010 )
        {
          v1012 = *(unsigned __int8 *)v1000;
          v1000 = (_QWORD *)((char *)v1000 + 1);
          v1005 = __ROL8__(v1012 ^ v1005, v1002);
        }
        v1013 = v1005 >> 31;
        v1014 = 0;
        while ( v1013 )
        {
          LODWORD(v1005) = v1013 ^ v1005;
          v1013 >>= 31;
        }
        v1015 = v3786;
        v1016 = v3791;
        v998[5] = v1005 & 0x7FFFFFFF;
        *(_DWORD *)(v1015 + 240) = 48;
        if ( *(_DWORD *)(v1015 + 256) )
        {
          LOBYTE(v1014) = v1016 != 0;
          *(_DWORD *)(v1015 + 264) = *(_DWORD *)(v1015 + 264) & 0xFFFFFFFE | v1014;
        }
        v3985 = (_BYTE *)v955;
        v1017 = (_BYTE *)(v1015 + 96);
        v1018 = (v1016 != 0) + 13;
        if ( v1015 == -96i64 )
        {
          v1019 = *(unsigned int *)(v955 + 2020);
          v1020 = v1019 + 48;
          if ( (unsigned int)(v1019 + 48) <= *(_DWORD *)(v955 + 2588) )
          {
            v887 = (_BYTE *)v955;
            *(_DWORD *)(v955 + 2020) = v1020;
          }
          else
          {
            v887 = (_BYTE *)sub_140B0F020((_DWORD *)v955, v1020, *(_DWORD *)(v955 + 2340));
            if ( !v887 )
            {
              v3986[0] = 0i64;
              goto LABEL_1329;
            }
            v1021 = *(_DWORD *)(v955 + 2448);
            if ( (v1021 & 4) == 0 )
            {
              v1022 = *(_DWORD *)(v955 + 2020);
              v1023 = *(_QWORD *)(v955 + 1992);
              v1024 = (v1021 & 0x20000000) != 0 ? *(_DWORD *)(v955 + 2340) : 0;
              if ( v1022 >= 8 )
              {
                v1025 = (unsigned __int64)v1022 >> 3;
                do
                {
                  *(_QWORD *)v955 = 0i64;
                  v1022 -= 8;
                  v955 += 8i64;
                  --v1025;
                }
                while ( v1025 );
              }
              for ( ; v1022; --v1022 )
                *(_BYTE *)v955++ = 0;
              v1026 = *((_DWORD *)v887 + 585);
              *((_DWORD *)v887 + 585) = v1024;
              if ( v1024 == 3 )
              {
                (*((void (__fastcall **)(__int64))v887 + 109))(v1023);
              }
              else if ( (*((_DWORD *)v887 + 612) & 0x10000000) != 0 || !v1024 )
              {
                (*((void (__fastcall **)(__int64))v887 + 31))(v1023);
              }
              else
              {
                (*((void (__fastcall **)(__int64, _QWORD))v887 + 69))(v1023 - 8, *(_QWORD *)(v1023 - 8));
              }
              *((_DWORD *)v887 + 585) = v1026;
            }
            *((_DWORD *)v887 + 612) &= ~4u;
          }
          ++*((_DWORD *)v887 + 515);
          v1017 = &v887[v1019];
          v1027 = 48;
          v1028 = v1017;
          v1029 = 6i64;
          do
          {
            *v1028 = 0i64;
            v1027 -= 8;
            ++v1028;
            --v1029;
          }
          while ( v1029 );
          for ( ; v1027; --v1027 )
          {
            *(_BYTE *)v1028 = 0;
            v1028 = (_QWORD *)((char *)v1028 + 1);
          }
          v955 = (unsigned int)v3783;
          *(_DWORD *)v1017 = v1018;
          v1030 = v3790;
          *((_QWORD *)v1017 + 1) = v3790;
          v1000 = (_QWORD *)v1030;
          *((_DWORD *)v1017 + 4) = v955;
          *((_DWORD *)v887 + 522) += v955;
          v1002 = *((unsigned int *)v887 + 517);
          v1031 = *((_QWORD *)v887 + 259);
          if ( v1030 < v1030 + v955 )
          {
            v1032 = (char *)v1030;
            do
            {
              _mm_prefetchnta(v1032);
              v1032 += 64;
            }
            while ( (unsigned __int64)v1032 < v1030 + v955 );
          }
          v1033 = *((_QWORD *)v887 + 259);
          v1034 = (unsigned int)v955 >> 7;
          if ( (unsigned int)v955 >> 7 )
          {
            do
            {
              v1035 = 8i64;
              do
              {
                v1036 = v1000[1] ^ __ROL8__(*v1000 ^ v1033, v1002);
                v1000 += 2;
                v1033 = __ROL8__(v1036, v1002);
                --v1035;
              }
              while ( v1035 );
              v1037 = (__ROL8__(v1031 ^ ((unsigned __int64)v1000 - v1030), 17) ^ v1031 ^ ((unsigned __int64)v1000 - v1030))
                    * (unsigned __int128)0x7010008004002001ui64;
              v3995 = *((_QWORD *)&v1037 + 1);
              v1002 = ((unsigned __int8)v1037 ^ (unsigned __int8)(BYTE8(v1037) ^ v1002)) & 0x3F;
              if ( !(_DWORD)v1002 )
                v1002 = 1i64;
              --v1034;
            }
            while ( v1034 );
            LODWORD(v955) = v3783;
          }
          v1015 = v955 & 0x7F;
          if ( (unsigned int)v1015 >= 8 )
          {
            v1038 = (unsigned __int64)(v955 & 0x7F) >> 3;
            do
            {
              v1033 = __ROL8__(*v1000++ ^ v1033, v1002);
              v1015 = (unsigned int)(v1015 - 8);
              --v1038;
            }
            while ( v1038 );
          }
          if ( (_DWORD)v1015 )
          {
            do
            {
              v1039 = *(unsigned __int8 *)v1000;
              v1000 = (_QWORD *)((char *)v1000 + 1);
              v1033 = __ROL8__(v1039 ^ v1033, v1002);
              v875 = (_DWORD)v1015 == 1;
              v1015 = (unsigned int)(v1015 - 1);
            }
            while ( !v875 );
          }
          for ( i10 = v1033; ; LODWORD(v1033) = i10 ^ v1033 )
          {
            i10 >>= 31;
            if ( !i10 )
              break;
          }
          *((_DWORD *)v1017 + 5) = v1033 & 0x7FFFFFFF;
          *((_DWORD *)v887 + 522) += v955;
          v1016 = v3791;
        }
        else
        {
          v887 = (_BYTE *)v955;
          *(_DWORD *)v1017 = v1018;
          LODWORD(v955) = v3783;
          v1030 = v3790;
        }
        if ( (*((_DWORD *)v887 + 612) & 0x40000000) != 0 && (_DWORD)v955 )
          sub_1403ED6CC(v887, v1030, (unsigned int)v955, v1017 + 28);
        *((_DWORD *)v1017 + 6) = 0;
        if ( v3789 )
          *((_DWORD *)v1017 + 6) = 1;
        v1041 = v3786;
        v3985 = v887;
        *(_DWORD *)(v3786 + 144) = 35;
        *(_DWORD *)(v1041 + 184) = *(_DWORD *)(v1041 + 184) & 0xFFFFFFFE | (v1016 != 0);
        if ( *(_DWORD *)(v1041 + 160) < 0x94u )
        {
          v1050 = v3794;
        }
        else
        {
          v1042 = v3794;
          v1043 = *(_QWORD *)(v1041 + 152);
          v1044 = (*((__int64 (__fastcall **)(ULONG_PTR, unsigned __int64, _QWORD *, __int64))v887 + 63))(
                    v3794,
                    v1015,
                    v1000,
                    v1002);
          if ( !v1044 )
          {
            v3986[0] = 0i64;
LABEL_1264:
            v3981 = v887;
            return 0;
          }
          v1045 = v3794 + *(unsigned int *)(v1044 + 80);
          v1046 = *(_DWORD *)(v1041 + 184) | 2;
          *(_DWORD *)(v1041 + 184) = v1046;
          v1047 = v1046;
          v1048 = *(_QWORD **)(v1043 + 112);
          if ( (unsigned __int64)v1048 >= v1042 && (unsigned __int64)v1048 < v1045 )
          {
            v1047 = v1046 | 4;
            *(_QWORD *)(v1041 + 168) = *v1048;
            *(_DWORD *)(v1041 + 184) = v1046 | 4;
          }
          v1049 = *(_QWORD **)(v1043 + 120);
          v1050 = v3794;
          if ( (unsigned __int64)v1049 >= v3794 && (unsigned __int64)v1049 < v1045 )
          {
            *(_QWORD *)(v1041 + 176) = *v1049;
            *(_DWORD *)(v1041 + 184) = v1047 | 8;
          }
        }
        v875 = (*((_DWORD *)v887 + 612) & 0x400000) == 0;
        v3986[0] = (__int64)v887;
        if ( v875 )
          goto LABEL_1723;
        HalExtensionList = (*((__int64 (__fastcall **)(ULONG_PTR))v887 + 63))(v1050);
        if ( !HalExtensionList )
          goto LABEL_1464;
        v1051 = *(unsigned __int16 *)(HalExtensionList + 6);
        v3788 = (unsigned int)v3785 / 0xCui64;
        LOWORD(v3789) = v1051;
        if ( !(_WORD)v1051 )
        {
          if ( (*((_DWORD *)v887 + 612) & 0x200000) == 0 )
          {
            v3845[5] = 317;
            KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1050, 0i64, 0i64);
          }
          goto LABEL_1467;
        }
        v1052 = v1051;
        v1053 = (unsigned int *)v3792;
        LODWORD(v3784) = v1051;
        v1054 = v3792 + 12i64 * ((unsigned int)v3785 / 0xC);
        LODWORD(Src) = 0;
        v1055 = 0;
        v1056 = *(unsigned __int16 *)(HalExtensionList + 20) + 24i64;
        v3787 = v1054;
        v1057 = HalExtensionList + v1056;
        v3786 = v1057;
        while ( 1 )
        {
          v1058 = 5i64 * v1055;
          v1059 = *(_DWORD *)(v1057 + 40i64 * v1055 + 16);
          v1060 = *(_DWORD *)(v1057 + 40i64 * v1055 + 12);
          if ( v1059 <= *(_DWORD *)(v1057 + 40i64 * v1055 + 8) )
            v1059 = *(_DWORD *)(v1057 + 40i64 * v1055 + 8);
          v3790 = 5i64 * v1055;
          v1061 = v1060 + v1059;
          LODWORD(v3783) = v1060;
          if ( v1055 )
          {
            if ( v1061 < *(_DWORD *)(v1057 + 40i64 * (v1055 - 1) + 12) )
            {
              if ( (*((_DWORD *)v887 + 612) & 0x200000) == 0 )
              {
                v3845[6] = 317;
                KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1050, 1ui64, 0i64);
              }
LABEL_1504:
              if ( !*((_DWORD *)v887 + 574) )
              {
                *((_QWORD *)v887 + 288) = v887 - 0x5C5FC0A76E374B18i64;
                *((_QWORD *)v887 + 289) = 0i64;
                *((_QWORD *)v887 + 290) = 271i64;
                *((_QWORD *)v887 + 291) = v1050;
                *((_DWORD *)v887 + 574) = 1;
LABEL_1469:
                __ba(v887, 0i64);
              }
LABEL_1464:
              v946 = -1073741701;
LABEL_1514:
              v3981 = v887;
              v207 = v887;
              if ( v946 >= 0 )
                goto LABEL_1725;
LABEL_1515:
              if ( v946 != -1073741554 )
                return 0;
              goto LABEL_1725;
            }
            v1055 = (unsigned int)Src;
          }
          if ( v1053 != (unsigned int *)v1054 )
          {
            do
            {
              v1062 = v1053[1];
              if ( *v1053 >= v1061 || v1062 <= v1060 )
                break;
              if ( *v1053 < v1060 || v1062 > v1061 )
              {
                if ( (*((_DWORD *)v887 + 612) & 0x200000) == 0 )
                {
                  v3845[9] = 317;
                  KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1050, 2ui64, 0i64);
                }
                goto LABEL_1504;
              }
              v1063 = v1053[2];
              if ( (v1063 & 1) != 0 || (*(_BYTE *)(v1063 + v1050) & 0x20) != 0 )
              {
                v1064 = *(_DWORD *)(v1057 + 8 * v1058 + 16);
                v1065 = *(_DWORD *)(v1057 + 8 * v1058 + 12);
                if ( v1064 <= *(_DWORD *)(v1057 + 8 * v1058 + 8) )
                  v1064 = *(_DWORD *)(v1057 + 8 * v1058 + 8);
                v1066 = v1065 + v1064;
                v1067 = (unsigned int *)(*((__int64 (__fastcall **)(unsigned int *, ULONG_PTR, unsigned __int64, __int64))RtlpConvertFunctionEntry))(
                                          v1053,
                                          v1050,
                                          v1057,
                                          v1052);
                v1068 = v1067;
                if ( *v1067 < v1065 || v1067[1] > v1066 )
                {
                  v1069 = v3794;
                  if ( (*((_DWORD *)v887 + 612) & 0x200000) == 0 )
                  {
                    v3845[8] = 317;
                    KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, ((_DWORD)v1067 - (_DWORD)v3794) | 0x80000000, 0i64);
                  }
                  if ( !*((_DWORD *)v887 + 574) )
                  {
                    *((_QWORD *)v887 + 288) = v887 - 0x5C5FC0A76E374B18i64;
                    *((_QWORD *)v887 + 289) = 0i64;
                    *((_QWORD *)v887 + 290) = 271i64;
                    *((_QWORD *)v887 + 291) = v1069;
                    *((_DWORD *)v887 + 574) = 1;
                    __ba(v887, 0i64);
                  }
                }
                v1070 = (unsigned int *)(*((__int64 (__fastcall **)(unsigned int *, ULONG_PTR, ULONG_PTR))RtlpLookupPrimaryFunctionEntry))(
                                          v1068,
                                          v3794,
                                          v3794 + *v1068);
                if ( *v1070 >= v1065 && v1070[1] <= v1066 )
                {
                  v1050 = v3794;
                }
                else
                {
                  v1050 = v3794;
                  v1071 = ((_DWORD)v1070 - v3794) | 0x80000000;
                  if ( (*((_DWORD *)v887 + 612) & 0x200000) == 0 )
                  {
                    v3845[7] = 317;
                    KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, v1071, 0i64);
                  }
                  if ( !*((_DWORD *)v887 + 574) )
                  {
                    *((_QWORD *)v887 + 288) = v887 - 0x5C5FC0A76E374B18i64;
                    *((_QWORD *)v887 + 289) = 0i64;
                    *((_QWORD *)v887 + 290) = 271i64;
                    *((_QWORD *)v887 + 291) = v1050;
                    *((_DWORD *)v887 + 574) = 1;
                    __ba(v887, 0i64);
                  }
                }
                v1058 = v3790;
                v1060 = v3783;
                v1057 = v3786;
                v1054 = v3787;
              }
              v1053 += 3;
            }
            while ( v1053 != (unsigned int *)v1054 );
            v1055 = (unsigned int)Src;
            v1052 = (unsigned int)v3784;
          }
          LODWORD(Src) = ++v1055;
          if ( v1055 >= (unsigned int)v1052 )
          {
            v1072 = v3788;
            v1073 = HalExtensionList;
            if ( v1053 != (unsigned int *)v1054 )
            {
              if ( (*((_DWORD *)v887 + 612) & 0x200000) == 0 )
              {
                v3845[10] = 317;
                KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1050, 3ui64, 0i64);
              }
LABEL_1467:
              if ( !*((_DWORD *)v887 + 574) )
              {
                *((_QWORD *)v887 + 288) = v887 - 0x5C5FC0A76E374B18i64;
                *((_QWORD *)v887 + 289) = 0i64;
                *((_QWORD *)v887 + 290) = 271i64;
                *((_QWORD *)v887 + 291) = v1050;
                *((_DWORD *)v887 + 574) = 1;
                goto LABEL_1469;
              }
              goto LABEL_1464;
            }
            if ( (_DWORD)v3788 )
              v1074 = (v3788 + 6) & 0xFFFFFFF8;
            else
              v1074 = 0;
            v1075 = *((unsigned int *)v887 + 505);
            v1076 = v1074 + 24 * v1052 + v1075 + 48;
            if ( v1076 <= *((_DWORD *)v887 + 647) )
            {
              v1077 = (__int64)v887;
              HalExtensionList = (ULONG_PTR)v887;
              *((_DWORD *)v887 + 505) = v1076;
            }
            else
            {
              HalExtensionList = sub_140B0F020(v887, v1076, *((_DWORD *)v887 + 585));
              v1077 = HalExtensionList;
              if ( !HalExtensionList )
              {
                v946 = -1073741670;
                goto LABEL_1514;
              }
              v1098 = *((_DWORD *)v887 + 612);
              if ( (v1098 & 4) == 0 )
              {
                v1099 = *((_DWORD *)v887 + 505);
                v1100 = *((_QWORD *)v887 + 249);
                v1101 = (v1098 & 0x20000000) != 0 ? *((_DWORD *)v887 + 585) : 0;
                if ( v1099 >= 8 )
                {
                  v1102 = (unsigned __int64)v1099 >> 3;
                  do
                  {
                    *(_QWORD *)v887 = 0i64;
                    v1099 -= 8;
                    v887 += 8;
                    --v1102;
                  }
                  while ( v1102 );
                }
                for ( ; v1099; --v1099 )
                  *v887++ = 0;
                v1103 = *(_DWORD *)(v1077 + 2340);
                *(_DWORD *)(v1077 + 2340) = v1101;
                if ( v1101 == 3 )
                {
                  (*(void (__fastcall **)(__int64))(v1077 + 872))(v1100);
                }
                else if ( (*(_DWORD *)(v1077 + 2448) & 0x10000000) != 0 || !v1101 )
                {
                  (*(void (__fastcall **)(__int64))(v1077 + 248))(v1100);
                }
                else
                {
                  (*(void (__fastcall **)(__int64, _QWORD))(v1077 + 552))(v1100 - 8, *(_QWORD *)(v1100 - 8));
                }
                v1077 = HalExtensionList;
                v1072 = v3788;
                *(_DWORD *)(HalExtensionList + 2340) = v1103;
              }
              *(_DWORD *)(v1077 + 2448) &= ~4u;
              LODWORD(v1052) = v3784;
              v1054 = v3787;
            }
            ++*(_DWORD *)(v1077 + 2060);
            v1104 = v1077 + v1075;
            v1105 = 48;
            v1106 = (_QWORD *)(v1077 + v1075);
            v1107 = 6i64;
            do
            {
              *v1106 = 0i64;
              v1105 -= 8;
              ++v1106;
              --v1107;
            }
            while ( v1107 );
            for ( ; v1105; --v1105 )
            {
              *(_BYTE *)v1106 = 0;
              v1106 = (_QWORD *)((char *)v1106 + 1);
            }
            v1108 = v3792;
            *(_DWORD *)v1104 = 30;
            *(_QWORD *)(v1104 + 8) = v1108;
            *(_DWORD *)(v1104 + 16) = 0;
            v1109 = *(_QWORD *)(v1077 + 2072);
            for ( i11 = v1109; ; LODWORD(v1109) = i11 ^ v1109 )
            {
              i11 >>= 31;
              if ( !i11 )
                break;
            }
            v1111 = v3794;
            v1112 = (unsigned __int16)v3789;
            *(_DWORD *)(v1104 + 20) = v1109 & 0x7FFFFFFF;
            v887 = (_BYTE *)v1077;
            *(_QWORD *)(v1104 + 24) = v1111;
            *(_DWORD *)(v1104 + 32) = *(_DWORD *)(v1073 + 80);
            *(_DWORD *)(v1104 + 36) = v3785;
            v875 = (_DWORD)v3791 == 0;
            *(_WORD *)(v1104 + 40) = v1112;
            LOWORD(v1111) = *(_WORD *)(v1104 + 42) & 0xFFFE;
            v3986[0] = v1077;
            *(_WORD *)(v1104 + 42) = v1111 | !v875;
            v3788 = v1104 + 48;
            if ( v1072 )
              v1113 = v1104 + 48 + (((unsigned int)(v1072 - 1) + 7i64) & 0xFFFFFFFFFFFFFFF8ui64);
            else
              v1113 = v1104 + 48;
            v3790 = v1113;
            v1114 = v1113 + 24 * v1112;
            v3791 = v1114;
            if ( v1072 )
              v3793 = v1108 + 12;
            else
              v3793 = v1054;
            if ( (_DWORD)v1052 )
            {
              v1115 = (unsigned int)v1052;
              v1116 = (_DWORD *)(v1113 + 8);
              do
              {
                v1117 = 2i64;
                do
                {
                  *(v1116 - 2) = 0;
                  *(v1116 - 1) = 0;
                  *v1116 = 0x80000000;
                  v1116 += 3;
                  --v1117;
                }
                while ( v1117 );
                --v1115;
              }
              while ( v1115 );
              v1077 = HalExtensionList;
            }
            if ( v1113 == v1114 )
            {
LABEL_1723:
              v3985 = v887;
              v207 = v887;
              goto LABEL_1724;
            }
            v1118 = (_DWORD *)v3786;
            while ( 2 )
            {
              v875 = (v1118[9] & 0x2000000) == 0;
              LODWORD(Src) = 0;
              if ( !v875 )
                goto LABEL_1576;
              v1119 = *v1118;
              if ( *v1118 == 1414090313 )
              {
                if ( v1118[1] == 1195525195 )
                  goto LABEL_1576;
LABEL_1582:
                if ( v1119 != 1095914053 || *((_WORD *)v1118 + 2) != 16724 )
                  goto LABEL_1584;
LABEL_1576:
                v1120 = 1;
                LODWORD(Src) = 1;
              }
              else
              {
                if ( v1119 != 1162297680 )
                  goto LABEL_1582;
                v1121 = *((_WORD *)v1118 + 2);
                if ( v1121 == 30839 || v1121 == 29303 || v1121 == 30583 )
                  goto LABEL_1576;
LABEL_1584:
                v1122 = *(char **)(v1077 + 2352);
                v1123 = 7;
                v1124 = *(__int64 **)(v1077 + 2360);
                v1125 = (char *)v1118 - v1122;
                v1126 = *(char **)(v1077 + 2368);
                v1127 = *(char **)(HalExtensionList + 2376);
                while ( 1 )
                {
                  v1128 = (unsigned __int8)v1122[v1125];
                  v1129 = (unsigned __int8)*v1122++;
                  if ( v1128 != v1129 )
                    break;
                  if ( !--v1123 )
                    goto LABEL_1602;
                }
                v1130 = 8;
                v1131 = (__int64 *)v1118;
                do
                {
                  v1132 = *v1131++;
                  v1133 = *v1124++;
                  if ( v1132 != v1133 )
                    goto LABEL_1595;
                  v1130 -= 8;
                }
                while ( v1130 >= 8 );
                if ( v1130 )
                {
                  while ( 1 )
                  {
                    v1134 = *(unsigned __int8 *)v1131;
                    v1131 = (__int64 *)((char *)v1131 + 1);
                    v1135 = *(unsigned __int8 *)v1124;
                    v1124 = (__int64 *)((char *)v1124 + 1);
                    if ( v1134 != v1135 )
                      break;
                    if ( !--v1130 )
                      goto LABEL_1602;
                  }
LABEL_1595:
                  v1136 = 4;
                  v1137 = (char *)v1118 - v1126;
                  while ( 1 )
                  {
                    v1138 = (unsigned __int8)v1126[v1137];
                    v1139 = (unsigned __int8)*v1126++;
                    if ( v1138 != v1139 )
                      break;
                    if ( !--v1136 )
                      goto LABEL_1602;
                  }
                  v1140 = 6;
                  v1141 = (char *)v1118 - v1127;
                  while ( 1 )
                  {
                    v1142 = (unsigned __int8)v1127[v1141];
                    v1143 = (unsigned __int8)*v1127++;
                    if ( v1142 != v1143 )
                      break;
                    if ( !--v1140 )
                      goto LABEL_1602;
                  }
                  v1120 = (int)Src;
                }
                else
                {
LABEL_1602:
                  v1120 = 1;
                  LODWORD(Src) = 1;
                }
                v1077 = HalExtensionList;
              }
              v1144 = v1118[9];
              if ( v1144 < 0 )
              {
                v1120 = 1;
                LODWORD(Src) = 1;
                goto LABEL_1608;
              }
              if ( v1120 )
              {
LABEL_1608:
                if ( *v1118 == 1414090313 && v1118[1] == 1195525195 )
                {
                  if ( (*(_DWORD *)(v1077 + 2452) & 0x2000) != 0 )
                    v1120 = 0;
                  LODWORD(Src) = v1120;
                }
              }
              if ( (*(_DWORD *)(v1077 + 2452) & 0x4000) != 0
                && (v1144 & 0x20000000) != 0
                && (v3794 == *(_QWORD *)(v1077 + 1504) || v3794 == *(_QWORD *)(v1077 + 1512)) )
              {
                v1120 = 1;
                LODWORD(Src) = 1;
              }
              v1145 = v1118[4];
              v1146 = (unsigned int)v1118[3];
              v1147 = v3787;
              if ( v1145 <= v1118[2] )
                v1145 = v1118[2];
              v1148 = v3792;
              v1149 = v1146 + v1145;
              LODWORD(v3784) = v1118[3];
              LODWORD(v3783) = v1149;
              v1150 = v1146;
              if ( v3792 == v3787 )
              {
                v1152 = 0;
                v1153 = (_DWORD)v1146 != 0;
              }
              else
              {
                v1151 = *(_DWORD *)v3792;
                v1152 = *(_DWORD *)(v3792 + 4);
                v1153 = *(_DWORD *)v3792 < (unsigned int)v1146;
                if ( *(_DWORD *)v3792 > (unsigned int)v1146 )
                {
                  if ( *(_DWORD *)(v3792 + 4) > v1149 )
                    goto LABEL_1650;
                  if ( v1120 )
                    goto LABEL_1652;
                  v1154 = v3790;
                  v1155 = (_QWORD *)(v3794 + v1146);
                  LODWORD(v3785) = *(_DWORD *)(v3792 + 4);
                  v1156 = v1151 - v1146;
                  v1150 = v1151;
                  *(_DWORD *)v3790 = v1146;
                  v1157 = (unsigned __int64)v1155 + (unsigned int)(v1151 - v1146);
                  *(_DWORD *)(v1154 + 4) = v1151;
                  for ( i12 = 0; i12 < 6; ++i12 )
                  {
                    v1159 = *(&v4184 + i12);
                    if ( (unsigned __int64)v1155 < v1159 + (unsigned int)v4156[i12] && v1157 > v1159 )
                      goto LABEL_1649;
                  }
                  *(_DWORD *)(v1077 + 2088) += v1156;
                  v1160 = v1155;
                  v1161 = (char *)v1155;
                  v1162 = *(_DWORD *)(v1077 + 2068);
                  v1163 = *(_QWORD *)(HalExtensionList + 2072);
                  if ( (unsigned __int64)v1155 < v1157 )
                  {
                    do
                    {
                      _mm_prefetchnta(v1161);
                      v1161 += 64;
                    }
                    while ( (unsigned __int64)v1161 < v1157 );
                  }
                  v1164 = *(_QWORD *)(HalExtensionList + 2072);
                  v1165 = v1156 >> 7;
                  if ( v1156 >> 7 )
                  {
                    do
                    {
                      v1166 = 8i64;
                      do
                      {
                        v1167 = v1160[1] ^ __ROL8__(*v1160 ^ v1164, v1162);
                        v1160 += 2;
                        v1164 = __ROL8__(v1167, v1162);
                        --v1166;
                      }
                      while ( v1166 );
                      v1168 = (__ROL8__(v1163 ^ ((char *)v1160 - (char *)v1155), 17) ^ v1163 ^ (unsigned __int64)((char *)v1160 - (char *)v1155))
                            * (unsigned __int128)0x7010008004002001ui64;
                      v3996 = *((_QWORD *)&v1168 + 1);
                      v1162 = ((unsigned __int8)v1168 ^ (unsigned __int8)(BYTE8(v1168) ^ v1162)) & 0x3F;
                      if ( !v1162 )
                        LOBYTE(v1162) = 1;
                      --v1165;
                    }
                    while ( v1165 );
                    v1152 = v3785;
                  }
                  v1169 = v1156 & 0x7F;
                  if ( v1169 >= 8 )
                  {
                    v1170 = (unsigned __int64)v1169 >> 3;
                    do
                    {
                      v1164 = __ROL8__(*v1160++ ^ v1164, v1162);
                      v1169 -= 8;
                      --v1170;
                    }
                    while ( v1170 );
                  }
                  for ( ; v1169; --v1169 )
                  {
                    v1171 = *(unsigned __int8 *)v1160;
                    v1160 = (_QWORD *)((char *)v1160 + 1);
                    v1164 = __ROL8__(v1171 ^ v1164, v1162);
                  }
                  for ( i13 = v1164 >> 31; i13; i13 >>= 31 )
                    LODWORD(v1164) = i13 ^ v1164;
                  v1149 = v3783;
                  v1077 = HalExtensionList;
                  v1147 = v3787;
                  *(_DWORD *)(v3790 + 8) = v1164 & 0x7FFFFFFF;
LABEL_1649:
                  v1148 = v3792;
                  v1120 = (int)Src;
LABEL_1650:
                  if ( v1152 <= v1149 && v1148 != v1147 )
                  {
LABEL_1652:
                    v1173 = (int *)v3793;
                    v1174 = *(_DWORD *)(v3793 + 4);
                    LODWORD(v3785) = v1174;
                    if ( v1174 <= v1149 )
                    {
                      while ( v1173 != (int *)v1147 )
                      {
                        if ( v1120 )
                        {
                          v1175 = 0x80;
                        }
                        else
                        {
                          v1176 = *(unsigned int *)(v1148 + 4);
                          v1150 = *v1173;
                          if ( *v1173 < (unsigned int)v1176 )
                          {
                            if ( (*(_DWORD *)(v1077 + 2448) & 0x200000) == 0 )
                            {
                              v3845[11] = 317;
                              KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 6ui64, 0i64);
                            }
                            if ( !*(_DWORD *)(v1077 + 2296) )
                            {
                              *(_QWORD *)(v1077 + 2304) = v1077 - 0x5C5FC0A76E374B18i64;
                              *(_QWORD *)(v1077 + 2312) = 0i64;
                              v1177 = v3794;
                              *(_QWORD *)(v1077 + 2320) = 271i64;
                              *(_QWORD *)(v1077 + 2328) = v1177;
                              *(_DWORD *)(v1077 + 2296) = 1;
                              __ba(v1077, 0i64);
                              v1147 = v3787;
                            }
                          }
                          v1178 = (_QWORD *)(v3794 + v1176);
                          v1179 = v1150 - v1176;
                          v1180 = v3794 + v1176 + (unsigned int)(v1150 - v1176);
                          for ( i14 = 0; i14 < 6; ++i14 )
                          {
                            v1182 = *(&v4184 + i14);
                            if ( (unsigned __int64)v1178 < v1182 + (unsigned int)v4156[i14] && v1180 > v1182 )
                            {
                              v1175 = 0x80;
                              goto LABEL_1688;
                            }
                          }
                          if ( v1179 < 4 )
                          {
                            v1175 = 0x80;
                          }
                          else
                          {
                            v1183 = HalExtensionList;
                            v1184 = v1178;
                            v1185 = (char *)v1178;
                            *(_DWORD *)(HalExtensionList + 2088) += v1179;
                            v1186 = *(_DWORD *)(v1183 + 2068);
                            v1187 = *(_QWORD *)(v1183 + 2072);
                            if ( (unsigned __int64)v1178 < v1180 )
                            {
                              do
                              {
                                _mm_prefetchnta(v1185);
                                v1185 += 64;
                              }
                              while ( (unsigned __int64)v1185 < v1180 );
                            }
                            v1188 = v1187;
                            v1189 = v1179 >> 7;
                            if ( v1179 >> 7 )
                            {
                              do
                              {
                                v1190 = 8i64;
                                do
                                {
                                  v1191 = v1184[1] ^ __ROL8__(*v1184 ^ v1188, v1186);
                                  v1184 += 2;
                                  v1188 = __ROL8__(v1191, v1186);
                                  --v1190;
                                }
                                while ( v1190 );
                                v1192 = (__ROL8__(v1187 ^ ((char *)v1184 - (char *)v1178), 17) ^ v1187 ^ ((char *)v1184 - (char *)v1178))
                                      * (unsigned __int128)0x7010008004002001ui64;
                                v3997 = *((_QWORD *)&v1192 + 1);
                                v1186 = ((unsigned __int8)v1192 ^ (unsigned __int8)(BYTE8(v1192) ^ v1186)) & 0x3F;
                                if ( !v1186 )
                                  LOBYTE(v1186) = 1;
                                --v1189;
                              }
                              while ( v1189 );
                              v1174 = v3785;
                            }
                            v1193 = v1179 & 0x7F;
                            if ( v1193 >= 8 )
                            {
                              v1194 = (unsigned __int64)v1193 >> 3;
                              do
                              {
                                v1188 = __ROL8__(*v1184++ ^ v1188, v1186);
                                v1193 -= 8;
                                --v1194;
                              }
                              while ( v1194 );
                            }
                            for ( ; v1193; --v1193 )
                            {
                              v1195 = *(unsigned __int8 *)v1184;
                              v1184 = (_QWORD *)((char *)v1184 + 1);
                              v1188 = __ROL8__(v1195 ^ v1188, v1186);
                            }
                            for ( i15 = v1188 >> 7; i15; i15 >>= 7 )
                              LOBYTE(v1188) = i15 ^ v1188;
                            v1149 = v3783;
                            v1175 = v1188 & 0x7F;
                          }
                          v1147 = v3787;
LABEL_1688:
                          v1148 = v3792;
                          v1120 = (int)Src;
                        }
                        v1197 = (_BYTE *)v3788;
                        v1148 += 12i64;
                        ++v3788;
                        v3792 = v1148;
                        *v1197 = v1175;
                        v1173 = (int *)(v3793 + 12);
                        v3793 = (__int64)v1173;
                        if ( v1173 != (int *)v1147 )
                        {
                          v1174 = v1173[1];
                          LODWORD(v3785) = v1174;
                        }
                        if ( v1174 > v1149 )
                          break;
                        v1077 = HalExtensionList;
                      }
                    }
                  }
LABEL_1692:
                  v1198 = (unsigned int *)v3790;
                  if ( !v1120 && v1150 != v1149 )
                  {
                    *(_DWORD *)(v3790 + 12) = v1150;
                    v1198[4] = v1149;
                    v1199 = v1198[3];
                    v1200 = v1149 - v1199;
                    v1201 = (_QWORD *)(v3794 + v1199);
                    v1202 = (unsigned __int64)v1201 + v1200;
                    for ( i16 = 0; i16 < 6; ++i16 )
                    {
                      v1204 = *(&v4184 + i16);
                      if ( (unsigned __int64)v1201 < v1204 + (unsigned int)v4156[i16] && v1202 > v1204 )
                        goto LABEL_1715;
                    }
                    v1205 = HalExtensionList;
                    v1206 = v1201;
                    *(_DWORD *)(HalExtensionList + 2088) += v1200;
                    v1207 = *(_DWORD *)(v1205 + 2068);
                    v1208 = *(_QWORD *)(v1205 + 2072);
                    v1209 = (char *)v1201;
                    if ( (unsigned __int64)v1201 < v1202 )
                    {
                      do
                      {
                        _mm_prefetchnta(v1209);
                        v1209 += 64;
                      }
                      while ( (unsigned __int64)v1209 < v1202 );
                    }
                    v1210 = v1208;
                    for ( i17 = v1200 >> 7; i17; --i17 )
                    {
                      v1212 = 8i64;
                      do
                      {
                        v1213 = v1206[1] ^ __ROL8__(*v1206 ^ v1210, v1207);
                        v1206 += 2;
                        v1210 = __ROL8__(v1213, v1207);
                        --v1212;
                      }
                      while ( v1212 );
                      v1214 = (__ROL8__(v1208 ^ ((char *)v1206 - (char *)v1201), 17) ^ v1208 ^ ((char *)v1206
                                                                                              - (char *)v1201))
                            * (unsigned __int128)0x7010008004002001ui64;
                      v3998 = *((_QWORD *)&v1214 + 1);
                      v1207 = ((unsigned __int8)v1214 ^ (unsigned __int8)(BYTE8(v1214) ^ v1207)) & 0x3F;
                      if ( !v1207 )
                        LOBYTE(v1207) = 1;
                    }
                    v1215 = v1200 & 0x7F;
                    if ( v1215 >= 8 )
                    {
                      v1216 = (unsigned __int64)v1215 >> 3;
                      do
                      {
                        v1210 = __ROL8__(*v1206++ ^ v1210, v1207);
                        v1215 -= 8;
                        --v1216;
                      }
                      while ( v1216 );
                    }
                    for ( ; v1215; --v1215 )
                    {
                      v1217 = *(unsigned __int8 *)v1206;
                      v1206 = (_QWORD *)((char *)v1206 + 1);
                      v1210 = __ROL8__(v1217 ^ v1210, v1207);
                    }
                    for ( i18 = v1210; ; LODWORD(v1210) = i18 ^ v1210 )
                    {
                      i18 >>= 31;
                      if ( !i18 )
                        break;
                    }
                    v1149 = v3783;
                    v1198[5] = v1210 & 0x7FFFFFFF;
                  }
LABEL_1715:
                  v1219 = v3792;
                  if ( v3792 != v3787 && *(_DWORD *)v3792 >= (unsigned int)v3784 && *(_DWORD *)(v3792 + 4) <= v1149 )
                  {
                    v1220 = v3793;
                    if ( v3793 != v3787 )
                    {
                      v1221 = v3788;
                      *(_BYTE *)v3788 = 0x80;
                      v3788 = v1221 + 1;
                      v3793 = v1220 + 12;
                    }
                    v3792 = v1219 + 12;
                  }
                  v1077 = HalExtensionList;
                  v1118 = (_DWORD *)(v3786 + 40);
                  v3790 = (__int64)(v1198 + 6);
                  v3786 += 40i64;
                  if ( v1198 + 6 == (unsigned int *)v3791 )
                  {
                    v887 = (_BYTE *)v3986[0];
                    goto LABEL_1723;
                  }
                  continue;
                }
              }
              break;
            }
            if ( !v1153 )
              goto LABEL_1650;
            goto LABEL_1692;
          }
        }
      }
    }
    *(_DWORD *)(v989 + 32) |= 2u;
    goto LABEL_1379;
  }
LABEL_2156:
  _disable();
  if ( !(_BYTE)KdDebuggerNotPresent )
  {
    while ( 1 )
      ;
  }
  _enable();
  HalExtensionList = KiGetHalExtensionList();
  v1507 = *(_QWORD *)HalExtensionList;
  v3788 = v1507;
  if ( v1507 != HalExtensionList )
  {
LABEL_2159:
    HalExtensionModuleFromLinks = KiGetHalExtensionModuleFromLinks(v1507);
    if ( !HalExtensionModuleFromLinks )
      goto LABEL_2584;
    v1509 = v207 + 1880;
    v4007 = v207;
    v1510 = *((_QWORD *)v207 + 235);
    v3787 = (ULONG_PTR)(v207 + 1880);
    v1511 = *(_QWORD *)(HalExtensionModuleFromLinks + v1510);
    v1512 = (__int64 (__fastcall *)(ULONG_PTR, char *))*((_QWORD *)v207 + 64);
    v3786 = v1511;
    v1513 = v1512(v1511, v4161);
    v1514 = v4163;
    v3790 = v1513;
    LODWORD(Src) = v4163;
    v3846 = v4163;
    v3794 = v4162;
    if ( !v4162 )
    {
      if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
      {
        v3848[9] = 317;
        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1511, 5ui64, 0i64);
      }
      return 0;
    }
    v1515 = &v4111;
    v4110 = 0i64;
    LODWORD(v1516) = 4;
    do
    {
      *(_BYTE *)v1515 = 0;
      v1515 = (int *)((char *)v1515 + 1);
      v875 = (_DWORD)v1516 == 1;
      v1516 = (unsigned int)(v1516 - 1);
    }
    while ( !v875 );
    v1517 = 0;
    if ( *((_DWORD *)v207 + 515) )
    {
      LODWORD(v1516) = v4111;
      v1518 = HIDWORD(v4110);
      v1519 = v4110;
      while ( 1 )
      {
        v1520 = v207;
        if ( *((_QWORD *)v207 + 335) )
          v1520 = (_BYTE *)*((_QWORD *)v207 + 335);
        v1521 = 0;
        v1522 = (int *)&v1520[*((unsigned int *)v1520 + 514)];
        if ( v1519 && v1518 <= v1517 )
        {
          v1521 = v1518;
          v1522 = (int *)&v1520[(unsigned int)v1516];
        }
        if ( v1521 != v1517 )
          break;
LABEL_2195:
        LODWORD(v4110) = 1;
        v1516 = (unsigned int)((_DWORD)v1522 - (_DWORD)v1520);
        HIDWORD(v4110) = v1521;
        v4111 = (_DWORD)v1522 - (_DWORD)v1520;
        v1519 = 1;
        v1535 = *v1522;
        v1518 = v1521;
        if ( (unsigned int)v1535 <= 0x2B
          && (v1536 = 0x80000001002i64, _bittest64(&v1536, v1535))
          && *((_QWORD *)v1522 + 1) == v3790
          && v1522[4] == v1514
          || (unsigned int)(v1535 - 33) <= 1 && *((_QWORD *)v1522 + 4) == v3794 )
        {
          if ( !v1522 )
          {
LABEL_2204:
            v1509 = (_QWORD *)v3787;
            goto LABEL_2205;
          }
LABEL_2584:
          v1507 = *(_QWORD *)v3788;
          v3788 = v1507;
          if ( v1507 == HalExtensionList )
            goto LABEL_2591;
          goto LABEL_2159;
        }
        if ( ++v1517 >= *((_DWORD *)v207 + 515) )
          goto LABEL_2204;
      }
      v1523 = v1517 - v1521;
      v1521 = v1517;
      while ( 2 )
      {
        v1524 = *v1522;
        if ( *v1522 > 28 )
        {
          v1532 = v1524 - 30;
          if ( !v1532 )
          {
            v1530 = (((v1522[9] != 0 ? v1522[9] - 1 : 0) / 0xCu + 7) & 0xFFFFFFF8)
                  + 24 * (*((unsigned __int16 *)v1522 + 20) + 2);
            goto LABEL_2193;
          }
          v1533 = v1532 - 3;
          if ( !v1533 || (v1534 = v1533 - 1) == 0 )
          {
            v1530 = 20 * (unsigned int)(((v1522[8] & 0xFFF) + (unsigned __int64)(unsigned int)v1522[10] + 4095) >> 12)
                  + 48;
            goto LABEL_2193;
          }
          v1529 = v1534 == 9;
LABEL_2188:
          if ( !v1529 )
          {
            v1530 = 48i64;
            goto LABEL_2193;
          }
        }
        else
        {
          if ( v1524 == 28 )
          {
            v1531 = *((unsigned __int16 *)v1522 + 20);
            goto LABEL_2181;
          }
          v1525 = v1524 - 1;
          if ( v1525 )
          {
            v1526 = v1525 - 6;
            if ( !v1526 )
            {
              v1530 = (unsigned int)(24 * (v1522[6] + 2));
              goto LABEL_2193;
            }
            v1527 = v1526 - 1;
            if ( v1527 )
            {
              v1528 = v1527 - 2;
              if ( v1528 )
              {
                v1529 = v1528 == 2;
                goto LABEL_2188;
              }
              v1530 = (unsigned int)(16 * (v1522[7] + 3));
LABEL_2193:
              v1522 = (int *)((char *)v1522 + v1530);
              if ( !--v1523 )
              {
                v1511 = v3786;
                v1514 = (int)Src;
                goto LABEL_2195;
              }
              continue;
            }
            v1531 = *((unsigned __int16 *)v1522 + 16);
LABEL_2181:
            v1530 = (v1531 + 55) & 0xFFFFFFF8;
            goto LABEL_2193;
          }
        }
        break;
      }
      v1530 = 4 * (v1522[4] / 0xCu) + 48;
      goto LABEL_2193;
    }
LABEL_2205:
    v1537 = (*((__int64 (__fastcall **)(ULONG_PTR, __int64))v207 + 85))(v1511, v1516);
    v1538 = (char **)*((_QWORD *)v207 + 165);
    v1539 = v1537;
    LODWORD(Src) = v1537;
    LODWORD(v3784) = v3846;
    _disable();
    v1540 = v3981;
    v1541 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + *((_QWORD *)v3981 + 202));
    _enable();
    (*((void (__fastcall **)(__int64))v1540 + 45))(v1541);
    LOBYTE(v1542) = 1;
    (*((void (__fastcall **)(_QWORD, __int64))v1540 + 29))(*((_QWORD *)v1540 + 166), v1542);
    v1543 = *v1538;
    v1544 = v3794;
    if ( *v1538 != (char *)v1538 )
    {
      v1545 = *((_QWORD *)v1540 + 234);
      while ( 1 )
      {
        v1546 = *(_QWORD *)&v1543[*v1509 - v1545];
        if ( v3794 >= v1546 && v3794 < v1546 + *(unsigned int *)&v1543[*((_QWORD *)v1540 + 236) - v1545] )
          break;
        v1543 = *(char **)v1543;
        if ( v1543 == (char *)v1538 )
          goto LABEL_2212;
      }
      (*((void (__fastcall **)(char *, __int64))v1540 + 27))(&v1543[-v1545], 2i64);
    }
LABEL_2212:
    (*((void (__fastcall **)(_QWORD))v1540 + 35))(*((_QWORD *)v1540 + 166));
    (*((void (**)(void))v1540 + 46))();
    if ( (*((_DWORD *)v1540 + 612) & 0x40000000) != 0 )
    {
      v1548 = sub_140B16070(&v3981, v3794, 0i64);
      v207 = v3981;
      goto LABEL_2393;
    }
    v4200 = 0i64;
    LOBYTE(v1547) = 1;
    v4164[4] = 0;
    v4197 = (*((__int64 (__fastcall **)(ULONG_PTR, __int64, _QWORD, int *))v1540 + 62))(v3794, v1547, 0i64, &v3846);
    v1549 = v3846 & (unsigned int)-(v4197 != 0);
    v3846 = v1549;
    v1550 = (__int64 (__fastcall *)(ULONG_PTR, __int64, __int64, int *))*((_QWORD *)v1540 + 62);
    v4164[1] = v1549;
    LOBYTE(v1549) = 1;
    v1551 = v1550(v3794, v1549, 12i64, &v3846);
    v1552 = v1551;
    v3787 = v1551;
    v4198 = v1551;
    LOBYTE(v1552) = 1;
    v3846 &= -(v1551 != 0);
    v1553 = (__int64 (__fastcall *)(ULONG_PTR, ULONG_PTR, __int64, int *))*((_QWORD *)v1540 + 62);
    LODWORD(v3783) = v3846;
    v4164[2] = v3846;
    v4199 = v1553(v3794, v1552, 10i64, &v3846);
    v3846 &= -(v4199 != 0);
    v1554 = (__int64 (__fastcall *)(ULONG_PTR))*((_QWORD *)v1540 + 63);
    v4164[3] = v3846;
    v1555 = v1554(v3794);
    if ( !v1555 )
    {
      if ( (*((_DWORD *)v1540 + 612) & 0x200000) == 0 )
      {
        v3848[8] = 317;
        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 7ui64, 0i64);
      }
      if ( !*((_DWORD *)v1540 + 574) )
      {
        *((_QWORD *)v1540 + 288) = v1540 - 0x5C5FC0A76E374B18i64;
        *((_QWORD *)v1540 + 289) = 0i64;
        *((_QWORD *)v1540 + 290) = 271i64;
        *((_QWORD *)v1540 + 291) = v1544;
        *((_DWORD *)v1540 + 574) = 1;
        __ba(v1540, 0i64);
      }
      return 0;
    }
    v1556 = (*((__int64 (__fastcall **)(ULONG_PTR, int *))v1540 + 148))(v3794, &v4008);
    v1557 = *((unsigned int *)v1540 + 585);
    v4201 = v1556;
    v4164[0] = *(_DWORD *)(v1555 + 84);
    LODWORD(v1556) = v1539;
    v1558 = *((unsigned int *)v1540 + 505);
    v4164[5] = v4008;
    v4196 = v3794;
    v1559 = (_DWORD)v1556 != 0 ? 0xB : 0;
    v1560 = v1558 + 288;
    LODWORD(v3785) = v1559;
    if ( (unsigned int)(v1558 + 288) <= *((_DWORD *)v1540 + 647) )
    {
      v1561 = (__int64)v1540;
      v3786 = (unsigned __int64)v1540;
      *((_DWORD *)v1540 + 505) = v1560;
      goto LABEL_2232;
    }
    v1561 = sub_140B0F020(v1540, v1560, v1557);
    v3786 = v1561;
    v1562 = 0i64;
    if ( !v1561 )
      goto LABEL_2586;
    v1563 = *((_DWORD *)v1540 + 612);
    if ( (v1563 & 4) == 0 )
    {
      v1564 = *((_DWORD *)v1540 + 505);
      v1565 = *((_QWORD *)v1540 + 249);
      v1566 = (v1563 & 0x20000000) != 0 ? *((_DWORD *)v1540 + 585) : 0;
      if ( v1564 >= 8 )
      {
        v1567 = (unsigned __int64)v1564 >> 3;
        do
        {
          *(_QWORD *)v1540 = 0i64;
          v1564 -= 8;
          v1540 += 8;
          --v1567;
        }
        while ( v1567 );
      }
      for ( ; v1564; --v1564 )
        *v1540++ = 0;
      v1568 = *(_DWORD *)(v1561 + 2340);
      *(_DWORD *)(v1561 + 2340) = v1566;
      if ( v1566 == 3 )
      {
        (*(void (__fastcall **)(__int64))(v1561 + 872))(v1565);
      }
      else if ( (*(_DWORD *)(v1561 + 2448) & 0x10000000) != 0 || !v1566 )
      {
        (*(void (__fastcall **)(__int64))(v1561 + 248))(v1565);
      }
      else
      {
        (*(void (__fastcall **)(__int64, _QWORD))(v1561 + 552))(v1565 - 8, *(_QWORD *)(v1565 - 8));
      }
      *(_DWORD *)(v1561 + 2340) = v1568;
    }
    *(_DWORD *)(v1561 + 2448) &= ~4u;
    v1559 = v3785;
LABEL_2232:
    v1569 = 6i64;
    v1570 = (__int64 *)&v4196;
    *(_DWORD *)(v1561 + 2060) += 6;
    v1571 = v4164;
    v1572 = v1561 + v1558;
    v3798 = (__int64 *)&v4196;
    v3792 = v1572;
    v3793 = 6i64;
    do
    {
      v1573 = (unsigned int)*v1571;
      v1574 = 48;
      v1575 = (_QWORD *)*v1570;
      v1576 = (_QWORD *)v1572;
      do
      {
        *v1576 = 0i64;
        v1574 -= 8;
        ++v1576;
        --v1569;
      }
      while ( v1569 );
      for ( ; v1574; --v1574 )
      {
        *(_BYTE *)v1576 = 0;
        v1576 = (_QWORD *)((char *)v1576 + 1);
      }
      *(_DWORD *)v1572 = v1559;
      *(_QWORD *)(v1572 + 8) = v1575;
      v1577 = v1575;
      *(_DWORD *)(v1572 + 16) = v1573;
      v1578 = (char *)v1575;
      *(_DWORD *)(v1561 + 2088) += v1573;
      v1579 = *(_DWORD *)(v1561 + 2068);
      v1580 = *(_QWORD *)(v1561 + 2072);
      if ( v1575 < (_QWORD *)((char *)v1575 + v1573) )
      {
        do
        {
          _mm_prefetchnta(v1578);
          v1578 += 64;
        }
        while ( v1578 < (char *)v1575 + v1573 );
      }
      v1581 = *(_QWORD *)(v1561 + 2072);
      v1582 = (unsigned int)v1573 >> 7;
      if ( (unsigned int)v1573 >> 7 )
      {
        do
        {
          v1583 = 8i64;
          do
          {
            v1584 = v1577[1] ^ __ROL8__(*v1577 ^ v1581, v1579);
            v1577 += 2;
            v1581 = __ROL8__(v1584, v1579);
            --v1583;
          }
          while ( v1583 );
          v1585 = (__ROL8__(v1580 ^ ((char *)v1577 - (char *)v1575), 17) ^ v1580 ^ (unsigned __int64)((char *)v1577 - (char *)v1575))
                * (unsigned __int128)0x7010008004002001ui64;
          v4009 = *((_QWORD *)&v1585 + 1);
          v1579 = ((unsigned __int8)v1585 ^ (unsigned __int8)(BYTE8(v1585) ^ v1579)) & 0x3F;
          if ( !v1579 )
            LOBYTE(v1579) = 1;
          --v1582;
        }
        while ( v1582 );
        v1561 = v3786;
        v1570 = v3798;
      }
      v1586 = v1573 & 0x7F;
      if ( v1586 >= 8 )
      {
        v1587 = (unsigned __int64)(v1573 & 0x7F) >> 3;
        do
        {
          v1581 = __ROL8__(*v1577++ ^ v1581, v1579);
          v1586 -= 8;
          --v1587;
        }
        while ( v1587 );
      }
      for ( ; v1586; --v1586 )
      {
        v1588 = *(unsigned __int8 *)v1577;
        v1577 = (_QWORD *)((char *)v1577 + 1);
        v1581 = __ROL8__(v1588 ^ v1581, v1579);
      }
      for ( i19 = v1581 >> 31; i19; i19 >>= 31 )
        LODWORD(v1581) = i19 ^ v1581;
      v1559 = v3785;
      v1569 = 6i64;
      *(_DWORD *)(v1572 + 20) = v1581 & 0x7FFFFFFF;
      ++v1570;
      *(_DWORD *)(v1561 + 2088) += v1573;
      v1572 += 48i64;
      v3798 = v1570;
      ++v1571;
      --v3793;
    }
    while ( v3793 );
    v1590 = v3792;
    v1591 = v3794;
    *(_DWORD *)v3792 = 44;
    *(_QWORD *)(v1590 + 24) = v1591;
    v1592 = *(_DWORD *)(v1561 + 2448);
    if ( (v1592 & 0x10000000) != 0 || (v1592 & 0x200000) != 0 )
    {
      v1593 = (int)Src;
      if ( !(_DWORD)Src )
        goto LABEL_2263;
    }
    else
    {
      v1593 = (int)Src;
      if ( !(_DWORD)Src )
      {
        if ( (*(_DWORD *)(v1561 + 2452) & 0x8000) != 0 )
        {
          *(_DWORD *)(v1590 + 32) |= 1u;
          if ( (unsigned int)sub_140B100E0(v1561, v1591) )
            *(_DWORD *)(v1590 + 32) |= 4u;
        }
LABEL_2263:
        v4007 = (_BYTE *)v1561;
        v207 = (_BYTE *)v1561;
        v3981 = (_BYTE *)v1561;
        v1548 = sub_140B0D838((int)&v4007, v3790, v3784, v1591, v1593, 0, (__int64)v3848, (__int64)&v3847);
        if ( v1548 < 0 )
          goto LABEL_2394;
        v207 = v4007;
        v1594 = 48;
        v1595 = &v4007[-v1561];
        v3981 = v4007;
        v1596 = v3847 - v3848[0];
        *((_QWORD *)&v1599 + 1) = 6i64;
        v1597 = (char *)(v1591 + (unsigned int)v3848[0]);
        v3792 = (ULONG_PTR)&v1595[v1590];
        v1598 = (__int64)&v1595[v1590 + 192];
        v3786 = v1598;
        *(_QWORD *)&v1599 = v1598;
        do
        {
          *(_QWORD *)v1599 = 0i64;
          v1594 -= 8;
          *(_QWORD *)&v1599 = v1599 + 8;
          --*((_QWORD *)&v1599 + 1);
        }
        while ( *((_QWORD *)&v1599 + 1) );
        for ( ; v1594; --v1594 )
        {
          *(_BYTE *)v1599 = 0;
          *(_QWORD *)&v1599 = v1599 + 1;
        }
        v1600 = (__int64)v1597;
        *(_DWORD *)v1598 = v3785;
        v1601 = v1597;
        *(_QWORD *)(v1598 + 8) = v1597;
        *(_DWORD *)(v1598 + 16) = v1596;
        *((_DWORD *)v207 + 522) += v1596;
        v1602 = *((_DWORD *)v207 + 517);
        v1603 = *((_QWORD *)v207 + 259);
        v1604 = (unsigned __int64)&v1597[v1596];
        if ( (unsigned __int64)v1597 < v1604 )
        {
          do
          {
            _mm_prefetchnta(v1601);
            v1601 += 64;
          }
          while ( (unsigned __int64)v1601 < v1604 );
        }
        v1605 = *((_QWORD *)v207 + 259);
        v1606 = v1596 >> 7;
        if ( v1596 >> 7 )
        {
          do
          {
            v1607 = 8i64;
            do
            {
              v1608 = *(_QWORD *)(v1600 + 8) ^ __ROL8__(*(_QWORD *)v1600 ^ v1605, v1602);
              v1600 += 16i64;
              v1605 = __ROL8__(v1608, v1602);
              --v1607;
            }
            while ( v1607 );
            v1599 = (__ROL8__(v1603 ^ (v1600 - (_QWORD)v1597), 17) ^ v1603 ^ (unsigned __int64)(v1600 - (_QWORD)v1597))
                  * (unsigned __int128)0x7010008004002001ui64;
            v4010 = *((_QWORD *)&v1599 + 1);
            v1602 = ((unsigned __int8)v1599 ^ (unsigned __int8)(BYTE8(v1599) ^ v1602)) & 0x3F;
            if ( !v1602 )
              LOBYTE(v1602) = 1;
            --v1606;
          }
          while ( v1606 );
          v1598 = v3786;
          v1593 = (int)Src;
        }
        v1609 = v1596 & 0x7F;
        if ( v1609 >= 8 )
        {
          v1610 = (unsigned __int64)v1609 >> 3;
          do
          {
            v1605 = __ROL8__(*(_QWORD *)v1600 ^ v1605, v1602);
            v1600 += 8i64;
            v1609 -= 8;
            --v1610;
          }
          while ( v1610 );
        }
        for ( ; v1609; --v1609 )
        {
          v1611 = *(unsigned __int8 *)v1600++;
          v1605 = __ROL8__(v1611 ^ v1605, v1602);
        }
        v1612 = v1605 >> 31;
        v1613 = 0;
        while ( v1612 )
        {
          LODWORD(v1605) = v1612 ^ v1605;
          v1612 >>= 31;
        }
        v1614 = v3792;
        *(_DWORD *)(v1598 + 20) = v1605 & 0x7FFFFFFF;
        *(_DWORD *)(v1614 + 240) = 48;
        if ( *(_DWORD *)(v1614 + 256) )
        {
          LOBYTE(v1613) = v1593 != 0;
          *(_DWORD *)(v1614 + 264) = *(_DWORD *)(v1614 + 264) & 0xFFFFFFFE | v1613;
        }
        v3981 = v207;
        v1615 = v1614 + 96;
        v1616 = (v1593 != 0) + 13;
        if ( v1614 != -96i64 )
        {
          *(_DWORD *)v1615 = v1616;
          LODWORD(v1631) = v3783;
          goto LABEL_2329;
        }
        v1617 = *((unsigned int *)v207 + 505);
        v1618 = v1617 + 48;
        if ( (unsigned int)(v1617 + 48) <= *((_DWORD *)v207 + 647) )
        {
          v1619 = (__int64)v207;
          *((_DWORD *)v207 + 505) = v1618;
          goto LABEL_2305;
        }
        v1619 = sub_140B0F020(v207, v1618, *((_DWORD *)v207 + 585));
        v1562 = 0i64;
        if ( v1619 )
        {
          v1620 = *((_DWORD *)v207 + 612);
          if ( (v1620 & 4) == 0 )
          {
            v1621 = *((_DWORD *)v207 + 505);
            v1622 = *((_QWORD *)v207 + 249);
            v1623 = (v1620 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
            if ( v1621 >= 8 )
            {
              v1624 = (unsigned __int64)v1621 >> 3;
              do
              {
                *(_QWORD *)v207 = 0i64;
                v1621 -= 8;
                v207 += 8;
                --v1624;
              }
              while ( v1624 );
            }
            for ( ; v1621; --v1621 )
              *v207++ = 0;
            v1625 = *(_DWORD *)(v1619 + 2340);
            *(_DWORD *)(v1619 + 2340) = v1623;
            if ( v1623 == 3 )
            {
              (*(void (__fastcall **)(__int64))(v1619 + 872))(v1622);
            }
            else if ( (*(_DWORD *)(v1619 + 2448) & 0x10000000) != 0 || !v1623 )
            {
              (*(void (__fastcall **)(__int64))(v1619 + 248))(v1622);
            }
            else
            {
              (*(void (__fastcall **)(__int64, _QWORD))(v1619 + 552))(v1622 - 8, *(_QWORD *)(v1622 - 8));
            }
            *(_DWORD *)(v1619 + 2340) = v1625;
          }
          *(_DWORD *)(v1619 + 2448) &= ~4u;
LABEL_2305:
          ++*(_DWORD *)(v1619 + 2060);
          v1615 = v1619 + v1617;
          v1626 = 48;
          v3786 = v1615;
          v1627 = (_QWORD *)v1615;
          v1628 = 6i64;
          do
          {
            *v1627 = 0i64;
            v1626 -= 8;
            ++v1627;
            --v1628;
          }
          while ( v1628 );
          for ( ; v1626; --v1626 )
          {
            *(_BYTE *)v1627 = 0;
            v1627 = (_QWORD *)((char *)v1627 + 1);
          }
          v1629 = (char *)v3787;
          *(_DWORD *)v1615 = v1616;
          v1630 = v1629;
          v1631 = (unsigned int)v3783;
          *(_QWORD *)(v1615 + 8) = v1629;
          *(_DWORD *)(v1615 + 16) = v1631;
          *(_DWORD *)(v1619 + 2088) += v1631;
          v1600 = *(unsigned int *)(v1619 + 2068);
          v1632 = &v1629[v1631];
          v1633 = *(_QWORD *)(v1619 + 2072);
          while ( v1629 < v1632 )
          {
            _mm_prefetchnta(v1629);
            v1629 += 64;
          }
          v1634 = *(_QWORD *)(v1619 + 2072);
          v1635 = (unsigned int)v1631 >> 7;
          if ( (unsigned int)v1631 >> 7 )
          {
            do
            {
              v1636 = 8i64;
              do
              {
                v1637 = *v1630 ^ v1634;
                v1638 = v1630 + 1;
                v1639 = *v1638 ^ __ROL8__(v1637, v1600);
                v1630 = v1638 + 1;
                v1634 = __ROL8__(v1639, v1600);
                --v1636;
              }
              while ( v1636 );
              v1640 = (__ROL8__(v1633 ^ ((unsigned __int64)v1630 - v3787), 17) ^ v1633 ^ ((unsigned __int64)v1630 - v3787))
                    * (unsigned __int128)0x7010008004002001ui64;
              v4011 = *((_QWORD *)&v1640 + 1);
              v1600 = ((unsigned __int8)v1640 ^ (unsigned __int8)(BYTE8(v1640) ^ v1600)) & 0x3F;
              if ( !(_DWORD)v1600 )
                v1600 = 1i64;
              --v1635;
            }
            while ( v1635 );
            v1615 = v3786;
            LODWORD(v1631) = v3783;
          }
          *((_QWORD *)&v1599 + 1) = v1631 & 0x7F;
          if ( DWORD2(v1599) >= 8 )
          {
            *(_QWORD *)&v1599 = (unsigned __int64)(v1631 & 0x7F) >> 3;
            do
            {
              v1634 = __ROL8__(*v1630++ ^ v1634, v1600);
              *((_QWORD *)&v1599 + 1) = (unsigned int)(DWORD2(v1599) - 8);
              *(_QWORD *)&v1599 = v1599 - 1;
            }
            while ( (_QWORD)v1599 );
          }
          if ( DWORD2(v1599) )
          {
            do
            {
              *(_QWORD *)&v1599 = *(unsigned __int8 *)v1630;
              v1630 = (_QWORD *)((char *)v1630 + 1);
              v1634 = __ROL8__(v1599 ^ v1634, v1600);
              v875 = DWORD2(v1599) == 1;
              *((_QWORD *)&v1599 + 1) = (unsigned int)(DWORD2(v1599) - 1);
            }
            while ( !v875 );
          }
          for ( i20 = v1634; ; LODWORD(v1634) = i20 ^ v1634 )
          {
            i20 >>= 31;
            if ( !i20 )
              break;
          }
          v207 = (_BYTE *)v1619;
          *(_DWORD *)(v1615 + 20) = v1634 & 0x7FFFFFFF;
          *(_DWORD *)(v1619 + 2088) += v1631;
          v1614 = v3792;
LABEL_2329:
          if ( (*((_DWORD *)v207 + 612) & 0x40000000) != 0 && (_DWORD)v1631 )
            sub_1403ED6CC(v207, v3787, (unsigned int)v1631, v1615 + 28);
          v875 = (_DWORD)Src == 0;
          *(_DWORD *)(v1615 + 24) = 0;
          v1642 = v3794;
          *(_DWORD *)(v1614 + 144) = 35;
          v1643 = *(_DWORD *)(v1614 + 184) & 0xFFFFFFFE;
          v3981 = v207;
          *(_DWORD *)(v1614 + 184) = v1643 | !v875;
          if ( *(_DWORD *)(v1614 + 160) < 0x94u )
          {
LABEL_2340:
            v875 = (*((_DWORD *)v207 + 612) & 0x400000) == 0;
            v4007 = v207;
            if ( v875 )
              goto LABEL_2583;
            v3787 = (*((__int64 (__fastcall **)(unsigned __int64, _QWORD, __int64))v207 + 63))(
                      v1642,
                      *((_QWORD *)&v1599 + 1),
                      v1600);
            if ( !v3787 )
              goto LABEL_2342;
            v1648 = *(unsigned __int16 *)(v3787 + 6);
            v3786 = (unsigned int)v3784 / 0xCui64;
            LOWORD(v3789) = v1648;
            if ( !(_WORD)v1648 )
            {
              if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
              {
                v3848[1] = 317;
                KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v1642, 0i64, 0i64);
              }
              if ( !*((_DWORD *)v207 + 574) )
              {
                *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                *((_QWORD *)v207 + 289) = 0i64;
                *((_QWORD *)v207 + 290) = 271i64;
                *((_QWORD *)v207 + 291) = v1642;
                goto LABEL_2347;
              }
              goto LABEL_2342;
            }
            v1649 = v1648;
            v1650 = (unsigned int *)v3790;
            v1651 = (__int64 *)(v3787 + *(unsigned __int16 *)(v3787 + 20) + 24i64);
            LODWORD(v3785) = v1648;
            v3798 = v1651;
            LODWORD(v3783) = 0;
            v1652 = v3790 + 12i64 * ((unsigned int)v3784 / 0xC);
            v3792 = v1652;
            v1653 = 0;
            v1654 = v3794;
            while ( 1 )
            {
              v1655 = 5i64 * v1653;
              v1656 = v1651[5 * v1653 + 2];
              v1657 = HIDWORD(v1651[5 * v1653 + 1]);
              if ( v1656 <= LODWORD(v1651[5 * v1653 + 1]) )
                v1656 = v1651[5 * v1653 + 1];
              v3793 = 5i64 * v1653;
              v1658 = v1657 + v1656;
              LODWORD(v3791) = v1657;
              if ( v1653 )
              {
                if ( v1658 < *((_DWORD *)&v1651[5 * v1653 - 3] - 1) )
                {
                  if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                  {
                    v3848[2] = 317;
                    KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 1ui64, 0i64);
                  }
LABEL_2382:
                  if ( !*((_DWORD *)v207 + 574) )
                  {
                    *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                    *((_QWORD *)v207 + 289) = 0i64;
                    v1672 = v3794;
                    *((_QWORD *)v207 + 290) = 271i64;
                    *((_QWORD *)v207 + 291) = v1672;
                    *((_DWORD *)v207 + 574) = 1;
                    goto LABEL_2348;
                  }
LABEL_2342:
                  v1548 = -1073741701;
LABEL_2393:
                  if ( v1548 >= 0 )
                    goto LABEL_2584;
LABEL_2394:
                  if ( v1548 == -1073741554 )
                    goto LABEL_2584;
                  return 0;
                }
                v1653 = v3783;
              }
              if ( v1650 != (unsigned int *)v1652 )
              {
                do
                {
                  v1659 = v1650[1];
                  if ( *v1650 >= v1658 || v1659 <= v1657 )
                    break;
                  if ( *v1650 < v1657 || v1659 > v1658 )
                  {
                    if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                    {
                      v3848[5] = 317;
                      KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 2ui64, 0i64);
                    }
                    if ( !*((_DWORD *)v207 + 574) )
                    {
                      *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                      *((_QWORD *)v207 + 289) = 0i64;
                      v1673 = v3794;
                      *((_QWORD *)v207 + 290) = 271i64;
                      *((_QWORD *)v207 + 291) = v1673;
LABEL_2347:
                      *((_DWORD *)v207 + 574) = 1;
LABEL_2348:
                      __ba(v207, 0i64);
                    }
                    goto LABEL_2342;
                  }
                  v1660 = v1650[2];
                  if ( (v1660 & 1) != 0 || (*(_BYTE *)(v1660 + v1654) & 0x20) != 0 )
                  {
                    v1661 = v1651[v1655 + 2];
                    v1662 = HIDWORD(v1651[v1655 + 1]);
                    if ( v1661 <= LODWORD(v1651[v1655 + 1]) )
                      v1661 = v1651[v1655 + 1];
                    v1663 = v1662 + v1661;
                    v1664 = (unsigned int *)(*((__int64 (__fastcall **)(unsigned int *, ULONG_PTR, __int64 *, __int64))RtlpConvertFunctionEntry))(
                                              v1650,
                                              v1654,
                                              v1651,
                                              v1649);
                    v1665 = v1664;
                    if ( *v1664 < v1662 || v1664[1] > v1663 )
                    {
                      v1666 = v3794;
                      if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                      {
                        v3848[4] = 317;
                        KeBugCheckEx(
                          __ROR4__(317, 160),
                          0xAui64,
                          v3794,
                          ((_DWORD)v1664 - (_DWORD)v3794) | 0x80000000,
                          0i64);
                      }
                      if ( !*((_DWORD *)v207 + 574) )
                      {
                        *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                        *((_QWORD *)v207 + 289) = 0i64;
                        *((_QWORD *)v207 + 290) = 271i64;
                        *((_QWORD *)v207 + 291) = v1666;
                        *((_DWORD *)v207 + 574) = 1;
                        __ba(v207, 0i64);
                      }
                    }
                    v1667 = (unsigned int *)(*((__int64 (__fastcall **)(unsigned int *, ULONG_PTR, ULONG_PTR))RtlpLookupPrimaryFunctionEntry))(
                                              v1665,
                                              v3794,
                                              v3794 + *v1665);
                    if ( *v1667 < v1662 || v1667[1] > v1663 )
                    {
                      v1668 = v3794;
                      v1669 = ((_DWORD)v1667 - v3794) | 0x80000000;
                      if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                      {
                        v3848[3] = 317;
                        KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, v1669, 0i64);
                      }
                      if ( !*((_DWORD *)v207 + 574) )
                      {
                        *((_QWORD *)v207 + 288) = v207 - 0x5C5FC0A76E374B18i64;
                        *((_QWORD *)v207 + 289) = 0i64;
                        *((_QWORD *)v207 + 290) = 271i64;
                        *((_QWORD *)v207 + 291) = v1668;
                        *((_DWORD *)v207 + 574) = 1;
                        __ba(v207, 0i64);
                      }
                    }
                    v1655 = v3793;
                    v1657 = v3791;
                    v1651 = v3798;
                    v1652 = v3792;
                    v1654 = v3794;
                  }
                  v1650 += 3;
                }
                while ( v1650 != (unsigned int *)v1652 );
                v1653 = v3783;
                v1649 = (unsigned int)v3785;
              }
              LODWORD(v3783) = ++v1653;
              if ( v1653 >= (unsigned int)v1649 )
              {
                v1670 = v3786;
                v1671 = v3787;
                if ( v1650 != (unsigned int *)v1652 )
                {
                  if ( (*((_DWORD *)v207 + 612) & 0x200000) == 0 )
                  {
                    v3848[6] = 317;
                    KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 3ui64, 0i64);
                  }
                  goto LABEL_2382;
                }
                if ( (_DWORD)v3786 )
                  v1674 = (v3786 + 6) & 0xFFFFFFF8;
                else
                  v1674 = 0;
                v1675 = *((unsigned int *)v207 + 505);
                v1676 = v1674 + 24 * v1649 + v1675 + 48;
                if ( v1676 <= *((_DWORD *)v207 + 647) )
                {
                  v1677 = (ULONG_PTR)v207;
                  v3787 = (ULONG_PTR)v207;
                  *((_DWORD *)v207 + 505) = v1676;
                }
                else
                {
                  v3787 = sub_140B0F020(v207, v1676, *((_DWORD *)v207 + 585));
                  v1677 = v3787;
                  if ( !v3787 )
                  {
                    v1548 = -1073741670;
                    goto LABEL_2393;
                  }
                  v1678 = *((_DWORD *)v207 + 612);
                  if ( (v1678 & 4) == 0 )
                  {
                    v1679 = *((_DWORD *)v207 + 505);
                    v1680 = *((_QWORD *)v207 + 249);
                    v1681 = (v1678 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
                    if ( v1679 >= 8 )
                    {
                      v1682 = (unsigned __int64)v1679 >> 3;
                      do
                      {
                        *(_QWORD *)v207 = 0i64;
                        v1679 -= 8;
                        v207 += 8;
                        --v1682;
                      }
                      while ( v1682 );
                    }
                    for ( ; v1679; --v1679 )
                      *v207++ = 0;
                    v1683 = *(_DWORD *)(v1677 + 2340);
                    *(_DWORD *)(v1677 + 2340) = v1681;
                    if ( v1681 == 3 )
                    {
                      (*(void (__fastcall **)(__int64))(v1677 + 872))(v1680);
                    }
                    else if ( (*(_DWORD *)(v1677 + 2448) & 0x10000000) != 0 || !v1681 )
                    {
                      (*(void (__fastcall **)(__int64))(v1677 + 248))(v1680);
                    }
                    else
                    {
                      (*(void (__fastcall **)(__int64, _QWORD))(v1677 + 552))(v1680 - 8, *(_QWORD *)(v1680 - 8));
                    }
                    v1677 = v3787;
                    v1670 = v3786;
                    *(_DWORD *)(v3787 + 2340) = v1683;
                  }
                  *(_DWORD *)(v1677 + 2448) &= ~4u;
                  LODWORD(v1649) = v3785;
                  v1652 = v3792;
                }
                ++*(_DWORD *)(v1677 + 2060);
                v1684 = v1677 + v1675;
                v1685 = 48;
                v1686 = (_QWORD *)(v1677 + v1675);
                v1687 = 6i64;
                do
                {
                  *v1686 = 0i64;
                  v1685 -= 8;
                  ++v1686;
                  --v1687;
                }
                while ( v1687 );
                for ( ; v1685; --v1685 )
                {
                  *(_BYTE *)v1686 = 0;
                  v1686 = (_QWORD *)((char *)v1686 + 1);
                }
                v1688 = v3790;
                *(_DWORD *)v1684 = 30;
                *(_QWORD *)(v1684 + 8) = v1688;
                *(_DWORD *)(v1684 + 16) = 0;
                v1689 = *(_QWORD *)(v1677 + 2072);
                for ( i21 = v1689; ; LODWORD(v1689) = i21 ^ v1689 )
                {
                  i21 >>= 31;
                  if ( !i21 )
                    break;
                }
                v1691 = v3794;
                v1692 = (unsigned __int16)v3789;
                *(_DWORD *)(v1684 + 20) = v1689 & 0x7FFFFFFF;
                v207 = (_BYTE *)v1677;
                *(_QWORD *)(v1684 + 24) = v1691;
                *(_DWORD *)(v1684 + 32) = *(_DWORD *)(v1671 + 80);
                *(_DWORD *)(v1684 + 36) = v3784;
                v875 = (_DWORD)Src == 0;
                *(_WORD *)(v1684 + 40) = v1692;
                LOWORD(v1691) = *(_WORD *)(v1684 + 42) & 0xFFFE;
                v4007 = (_BYTE *)v1677;
                *(_WORD *)(v1684 + 42) = v1691 | !v875;
                v3786 = v1684 + 48;
                if ( v1670 )
                  v1693 = (_DWORD *)(v1684 + 48 + (((unsigned int)(v1670 - 1) + 7i64) & 0xFFFFFFFFFFFFFFF8ui64));
                else
                  v1693 = (_DWORD *)(v1684 + 48);
                v1694 = (unsigned int *)v3790;
                v3791 = (ULONG_PTR)v1693;
                v1695 = (__int64)&v1693[6 * v1692];
                v3793 = v1695;
                if ( v1670 )
                  v3799 = v3790 + 12;
                else
                  v3799 = v1652;
                if ( (_DWORD)v1649 )
                {
                  v1696 = (unsigned int)v1649;
                  v1697 = v1693 + 2;
                  do
                  {
                    v1698 = 2i64;
                    do
                    {
                      *(v1697 - 2) = 0;
                      *(v1697 - 1) = 0;
                      *v1697 = 0x80000000;
                      v1697 += 3;
                      --v1698;
                    }
                    while ( v1698 );
                    --v1696;
                  }
                  while ( v1696 );
                  v1694 = (unsigned int *)v3790;
                }
                if ( v1693 == (_DWORD *)v1695 )
                {
LABEL_2583:
                  v3981 = v207;
                  goto LABEL_2584;
                }
                v1699 = v3798;
                while ( 2 )
                {
                  v875 = (*((_DWORD *)v1699 + 9) & 0x2000000) == 0;
                  v1700 = 0;
                  LODWORD(Src) = 0;
                  if ( !v875 )
                    goto LABEL_2435;
                  v1701 = *(_DWORD *)v1699;
                  if ( *(_DWORD *)v1699 == 1414090313 )
                  {
                    if ( *((_DWORD *)v1699 + 1) == 1195525195 )
                      goto LABEL_2435;
LABEL_2441:
                    if ( v1701 != 1095914053 || *((_WORD *)v1699 + 2) != 16724 )
                      goto LABEL_2443;
LABEL_2435:
                    v1700 = 1;
                    LODWORD(Src) = 1;
                  }
                  else
                  {
                    if ( v1701 != 1162297680 )
                      goto LABEL_2441;
                    v1702 = *((_WORD *)v1699 + 2);
                    if ( v1702 == 30839 || v1702 == 29303 || v1702 == 30583 )
                      goto LABEL_2435;
LABEL_2443:
                    v1703 = *(char **)(v1677 + 2352);
                    v1704 = 7;
                    v1705 = *(__int64 **)(v1677 + 2360);
                    v1706 = (char *)v1699 - v1703;
                    v1707 = *(char **)(v3787 + 2368);
                    v1708 = *(char **)(v3787 + 2376);
                    while ( 1 )
                    {
                      v1709 = (unsigned __int8)v1703[v1706];
                      v1710 = (unsigned __int8)*v1703++;
                      if ( v1709 != v1710 )
                        break;
                      if ( !--v1704 )
                      {
LABEL_2461:
                        v1700 = 1;
                        LODWORD(Src) = 1;
                        goto LABEL_2462;
                      }
                    }
                    v1711 = 8;
                    v1712 = v1699;
                    while ( 1 )
                    {
                      v1713 = *v1712++;
                      v1714 = *v1705++;
                      if ( v1713 != v1714 )
                        break;
                      v1711 -= 8;
                      if ( v1711 < 8 )
                      {
                        if ( !v1711 )
                          goto LABEL_2461;
                        while ( 1 )
                        {
                          v1715 = *(unsigned __int8 *)v1712;
                          v1712 = (__int64 *)((char *)v1712 + 1);
                          v1716 = *(unsigned __int8 *)v1705;
                          v1705 = (__int64 *)((char *)v1705 + 1);
                          if ( v1715 != v1716 )
                            goto LABEL_2454;
                          if ( !--v1711 )
                            goto LABEL_2461;
                        }
                      }
                    }
LABEL_2454:
                    v1717 = 4;
                    v1718 = (char *)v1699 - v1707;
                    while ( 1 )
                    {
                      v1719 = (unsigned __int8)v1707[v1718];
                      v1720 = (unsigned __int8)*v1707++;
                      if ( v1719 != v1720 )
                        break;
                      if ( !--v1717 )
                        goto LABEL_2461;
                    }
                    v1721 = 6;
                    v1722 = (char *)v1699 - v1708;
                    while ( 1 )
                    {
                      v1723 = (unsigned __int8)v1708[v1722];
                      v1724 = (unsigned __int8)*v1708++;
                      if ( v1723 != v1724 )
                        break;
                      if ( !--v1721 )
                        goto LABEL_2461;
                    }
LABEL_2462:
                    v1693 = (_DWORD *)v3791;
                    v1677 = v3787;
                  }
                  v1725 = *((_DWORD *)v1699 + 9);
                  if ( v1725 < 0 )
                  {
                    v1700 = 1;
                    LODWORD(Src) = 1;
                    goto LABEL_2466;
                  }
                  if ( v1700 )
                  {
LABEL_2466:
                    if ( *(_DWORD *)v1699 == 1414090313 && *((_DWORD *)v1699 + 1) == 1195525195 )
                    {
                      if ( (*(_DWORD *)(v1677 + 2452) & 0x2000) != 0 )
                        v1700 = 0;
                      LODWORD(Src) = v1700;
                    }
                  }
                  v1726 = v3794;
                  if ( (*(_DWORD *)(v1677 + 2452) & 0x4000) != 0
                    && (v1725 & 0x20000000) != 0
                    && (v3794 == *(_QWORD *)(v1677 + 1504) || v3794 == *(_QWORD *)(v1677 + 1512)) )
                  {
                    v1700 = 1;
                    LODWORD(Src) = 1;
                  }
                  v1727 = *((_DWORD *)v1699 + 4);
                  v1728 = *((unsigned int *)v1699 + 3);
                  v1729 = v3792;
                  if ( v1727 <= *((_DWORD *)v1699 + 2) )
                    v1727 = *((_DWORD *)v1699 + 2);
                  v1730 = v1728 + v1727;
                  LODWORD(v3784) = *((_DWORD *)v1699 + 3);
                  LODWORD(v3783) = v1730;
                  if ( v1694 == (unsigned int *)v3792 )
                  {
                    v1733 = 0;
                    v1735 = (_DWORD)v1728 != 0;
                    v1734 = v1728;
                  }
                  else
                  {
                    v1731 = *v1694;
                    v1732 = v1694[1];
                    v1733 = v1732;
                    v1734 = v1728;
                    v1735 = v1731 < (unsigned int)v1728;
                    if ( v1731 > (unsigned int)v1728 )
                    {
                      if ( v1732 > v1730 )
                        goto LABEL_2508;
                      if ( v1700 )
                      {
                        v1754 = v3790;
                        goto LABEL_2512;
                      }
                      *v1693 = v1728;
                      v1734 = v1731;
                      v1693[1] = v1731;
                      v1736 = (char *)(v1726 + v1728);
                      LODWORD(v3785) = v1732;
                      v1737 = v1731 - v1728;
                      v1738 = (unsigned __int64)&v1736[v1731 - (unsigned int)v1728];
                      v1739 = 0;
                      while ( 1 )
                      {
                        v1740 = *(&v4196 + v1739);
                        if ( (unsigned __int64)v1736 < v1740 + (unsigned int)v4164[v1739] && v1738 > v1740 )
                          break;
                        if ( ++v1739 >= 6 )
                        {
                          *(_DWORD *)(v1677 + 2088) += v1737;
                          v1741 = v1736;
                          v1742 = *(_DWORD *)(v1677 + 2068);
                          v1743 = *(_QWORD *)(v1677 + 2072);
                          for ( i22 = v1736; (unsigned __int64)v1741 < v1738; v1741 += 64 )
                            _mm_prefetchnta(v1741);
                          v1745 = v1743;
                          v1746 = v1737 >> 7;
                          if ( v1737 >> 7 )
                          {
                            do
                            {
                              v1747 = 8i64;
                              do
                              {
                                v1748 = i22[1] ^ __ROL8__(*i22 ^ v1745, v1742);
                                i22 += 2;
                                v1745 = __ROL8__(v1748, v1742);
                                --v1747;
                              }
                              while ( v1747 );
                              v1749 = (__ROL8__(v1743 ^ ((char *)i22 - v1736), 17) ^ v1743 ^ ((char *)i22 - v1736))
                                    * (unsigned __int128)0x7010008004002001ui64;
                              v4012 = *((_QWORD *)&v1749 + 1);
                              v1742 = ((unsigned __int8)v1749 ^ (unsigned __int8)(BYTE8(v1749) ^ v1742)) & 0x3F;
                              if ( !v1742 )
                                LOBYTE(v1742) = 1;
                              --v1746;
                            }
                            while ( v1746 );
                            v1733 = v3785;
                          }
                          v1750 = v1737 & 0x7F;
                          if ( v1750 >= 8 )
                          {
                            v1751 = (unsigned __int64)v1750 >> 3;
                            do
                            {
                              v1745 = __ROL8__(*i22++ ^ v1745, v1742);
                              v1750 -= 8;
                              --v1751;
                            }
                            while ( v1751 );
                          }
                          for ( ; v1750; --v1750 )
                          {
                            v1752 = *(unsigned __int8 *)i22;
                            i22 = (_QWORD *)((char *)i22 + 1);
                            v1745 = __ROL8__(v1752 ^ v1745, v1742);
                          }
                          for ( i23 = v1745 >> 31; i23; i23 >>= 31 )
                            LODWORD(v1745) = i23 ^ v1745;
                          v1730 = v3783;
                          v1700 = (int)Src;
                          v1677 = v3787;
                          *(_DWORD *)(v3791 + 8) = v1745 & 0x7FFFFFFF;
                          break;
                        }
                      }
                      v1729 = v3792;
LABEL_2508:
                      if ( v1733 <= v1730 )
                      {
                        v1754 = v3790;
                        if ( v3790 != v1729 )
                        {
LABEL_2512:
                          v1755 = (unsigned int *)v3799;
                          v1756 = *(_DWORD *)(v3799 + 4);
                          LODWORD(v3785) = v1756;
                          if ( v1756 <= v1730 )
                          {
                            while ( v1755 != (unsigned int *)v1729 )
                            {
                              if ( v1700 )
                              {
                                v1757 = 0x80;
                              }
                              else
                              {
                                v1758 = *(unsigned int *)(v1754 + 4);
                                v1734 = *v1755;
                                if ( *v1755 < (unsigned int)v1758 )
                                {
                                  if ( (*(_DWORD *)(v1677 + 2448) & 0x200000) == 0 )
                                  {
                                    v3848[7] = 317;
                                    KeBugCheckEx(__ROR4__(317, 160), 0xAui64, v3794, 6ui64, 0i64);
                                  }
                                  if ( !*(_DWORD *)(v1677 + 2296) )
                                  {
                                    *(_QWORD *)(v1677 + 2304) = v1677 - 0x5C5FC0A76E374B18i64;
                                    *(_QWORD *)(v1677 + 2312) = 0i64;
                                    v1759 = v3794;
                                    *(_QWORD *)(v1677 + 2320) = 271i64;
                                    *(_QWORD *)(v1677 + 2328) = v1759;
                                    *(_DWORD *)(v1677 + 2296) = 1;
                                    __ba(v1677, 0i64);
                                  }
                                }
                                v1760 = (_QWORD *)(v3794 + v1758);
                                v1761 = v1734 - v1758;
                                v1762 = v3794 + v1758 + v1734 - (unsigned int)v1758;
                                for ( i24 = 0; i24 < 6; ++i24 )
                                {
                                  v1764 = *(&v4196 + i24);
                                  if ( (unsigned __int64)v1760 < v1764 + (unsigned int)v4164[i24] && v1762 > v1764 )
                                    goto LABEL_2545;
                                }
                                if ( v1761 < 4 )
                                {
LABEL_2545:
                                  v1757 = 0x80;
                                  goto LABEL_2546;
                                }
                                v1765 = v3787;
                                v1766 = v1760;
                                *(_DWORD *)(v3787 + 2088) += v1761;
                                v1767 = *(_DWORD *)(v1765 + 2068);
                                v1768 = *(_QWORD *)(v1765 + 2072);
                                v1769 = (char *)v1760;
                                if ( (unsigned __int64)v1760 < v1762 )
                                {
                                  do
                                  {
                                    _mm_prefetchnta(v1769);
                                    v1769 += 64;
                                  }
                                  while ( (unsigned __int64)v1769 < v1762 );
                                }
                                v1770 = v1768;
                                v1771 = v1761 >> 7;
                                if ( v1761 >> 7 )
                                {
                                  do
                                  {
                                    v1772 = 8i64;
                                    do
                                    {
                                      v1773 = v1766[1] ^ __ROL8__(*v1766 ^ v1770, v1767);
                                      v1766 += 2;
                                      v1770 = __ROL8__(v1773, v1767);
                                      --v1772;
                                    }
                                    while ( v1772 );
                                    v1774 = (__ROL8__(v1768 ^ ((char *)v1766 - (char *)v1760), 17) ^ v1768 ^ ((char *)v1766 - (char *)v1760))
                                          * (unsigned __int128)0x7010008004002001ui64;
                                    v4013 = *((_QWORD *)&v1774 + 1);
                                    v1767 = ((unsigned __int8)v1774 ^ (unsigned __int8)(BYTE8(v1774) ^ v1767)) & 0x3F;
                                    if ( !v1767 )
                                      LOBYTE(v1767) = 1;
                                    --v1771;
                                  }
                                  while ( v1771 );
                                  v1756 = v3785;
                                }
                                v1775 = v1761 & 0x7F;
                                if ( v1775 >= 8 )
                                {
                                  v1776 = (unsigned __int64)v1775 >> 3;
                                  do
                                  {
                                    v1770 = __ROL8__(*v1766++ ^ v1770, v1767);
                                    v1775 -= 8;
                                    --v1776;
                                  }
                                  while ( v1776 );
                                }
                                for ( ; v1775; --v1775 )
                                {
                                  v1777 = *(unsigned __int8 *)v1766;
                                  v1766 = (_QWORD *)((char *)v1766 + 1);
                                  v1770 = __ROL8__(v1777 ^ v1770, v1767);
                                }
                                for ( i25 = v1770 >> 7; i25; i25 >>= 7 )
                                  LOBYTE(v1770) = i25 ^ v1770;
                                v1700 = (int)Src;
                                v1757 = v1770 & 0x7F;
LABEL_2546:
                                v1754 = v3790;
                                v1730 = v3783;
                              }
                              v1779 = (_BYTE *)v3786;
                              v1754 += 12i64;
                              ++v3786;
                              *v1779 = v1757;
                              v1729 = v3792;
                              v1755 = (unsigned int *)(v3799 + 12);
                              v3790 = v1754;
                              v3799 = (ULONG_PTR)v1755;
                              if ( v1755 != (unsigned int *)v3792 )
                              {
                                v1756 = v1755[1];
                                LODWORD(v3785) = v1756;
                              }
                              if ( v1756 > v1730 )
                                break;
                              v1677 = v3787;
                            }
                          }
                        }
                      }
LABEL_2550:
                      v1780 = v3791;
                      if ( !v1700 && v1734 != v1730 )
                      {
                        v1781 = v3794;
                        *(_DWORD *)(v3791 + 12) = v1734;
                        *(_DWORD *)(v1780 + 16) = v1730;
                        v1782 = *(unsigned int *)(v1780 + 12);
                        v1783 = v1730 - v1782;
                        v1784 = (_QWORD *)(v1782 + v1781);
                        v1785 = (unsigned __int64)v1784 + v1730 - (unsigned int)v1782;
                        LODWORD(Src) = v1783;
                        v1786 = 0;
                        while ( 1 )
                        {
                          v1787 = *(&v4196 + v1786);
                          if ( (unsigned __int64)v1784 < v1787 + (unsigned int)v4164[v1786] && v1785 > v1787 )
                            break;
                          if ( ++v1786 >= 6 )
                          {
                            v1788 = v3787;
                            v1789 = v1784;
                            *(_DWORD *)(v3787 + 2088) += v1783;
                            v1790 = *(_DWORD *)(v1788 + 2068);
                            v1791 = *(_QWORD *)(v1788 + 2072);
                            v1792 = (char *)v1784;
                            if ( (unsigned __int64)v1784 < v1785 )
                            {
                              do
                              {
                                _mm_prefetchnta(v1792);
                                v1792 += 64;
                              }
                              while ( (unsigned __int64)v1792 < v1785 );
                            }
                            v1793 = v1791;
                            v1794 = v1783 >> 7;
                            if ( v1783 >> 7 )
                            {
                              do
                              {
                                v1795 = 8i64;
                                do
                                {
                                  v1796 = v1789[1] ^ __ROL8__(*v1789 ^ v1793, v1790);
                                  v1789 += 2;
                                  v1793 = __ROL8__(v1796, v1790);
                                  --v1795;
                                }
                                while ( v1795 );
                                v1797 = (__ROL8__(v1791 ^ ((char *)v1789 - (char *)v1784), 17) ^ v1791 ^ ((char *)v1789 - (char *)v1784))
                                      * (unsigned __int128)0x7010008004002001ui64;
                                v4014 = *((_QWORD *)&v1797 + 1);
                                v1790 = ((unsigned __int8)v1797 ^ (unsigned __int8)(BYTE8(v1797) ^ v1790)) & 0x3F;
                                if ( !v1790 )
                                  LOBYTE(v1790) = 1;
                                --v1794;
                              }
                              while ( v1794 );
                              LOBYTE(v1783) = (_BYTE)Src;
                            }
                            v1798 = v1783 & 0x7F;
                            if ( v1798 >= 8 )
                            {
                              v1799 = (unsigned __int64)v1798 >> 3;
                              do
                              {
                                v1793 = __ROL8__(*v1789++ ^ v1793, v1790);
                                v1798 -= 8;
                                --v1799;
                              }
                              while ( v1799 );
                            }
                            for ( ; v1798; --v1798 )
                            {
                              v1800 = *(unsigned __int8 *)v1789;
                              v1789 = (_QWORD *)((char *)v1789 + 1);
                              v1793 = __ROL8__(v1800 ^ v1793, v1790);
                            }
                            for ( i26 = v1793; ; LODWORD(v1793) = i26 ^ v1793 )
                            {
                              i26 >>= 31;
                              if ( !i26 )
                                break;
                            }
                            v1780 = v3791;
                            *(_DWORD *)(v3791 + 20) = v1793 & 0x7FFFFFFF;
                            break;
                          }
                        }
                        v1730 = v3783;
                      }
                      v1694 = (unsigned int *)v3790;
                      if ( v3790 != v3792 && *(_DWORD *)v3790 >= (unsigned int)v3784 && *(_DWORD *)(v3790 + 4) <= v1730 )
                      {
                        v1802 = v3799;
                        if ( v3799 != v3792 )
                        {
                          v1803 = v3786;
                          *(_BYTE *)v3786 = 0x80;
                          v3786 = v1803 + 1;
                          v3799 = v1802 + 12;
                        }
                        v1694 += 3;
                        v3790 = (__int64)v1694;
                      }
                      v1693 = (_DWORD *)(v1780 + 24);
                      v1677 = v3787;
                      v1699 = v3798 + 5;
                      v3791 = (ULONG_PTR)v1693;
                      v3798 += 5;
                      if ( v1693 == (_DWORD *)v3793 )
                      {
                        v207 = v4007;
                        goto LABEL_2583;
                      }
                      continue;
                    }
                  }
                  break;
                }
                if ( !v1735 )
                  goto LABEL_2508;
                goto LABEL_2550;
              }
            }
          }
          v1644 = *(_QWORD *)(v1614 + 152);
          v1562 = (*((__int64 (__fastcall **)(unsigned __int64, _QWORD, __int64))v207 + 63))(
                    v1642,
                    *((_QWORD *)&v1599 + 1),
                    v1600);
          if ( v1562 )
          {
            v1645 = v1642 + *(unsigned int *)(v1562 + 80);
            *((_QWORD *)&v1599 + 1) = *(_DWORD *)(v1614 + 184) | 2u;
            *(_DWORD *)(v1614 + 184) = DWORD2(v1599);
            v1646 = DWORD2(v1599);
            *(_QWORD *)&v1599 = *(_QWORD *)(v1644 + 112);
            if ( (unsigned __int64)v1599 >= v1642 && (unsigned __int64)v1599 < v1645 )
            {
              v1646 = DWORD2(v1599) | 4;
              *(_QWORD *)(v1614 + 168) = *(_QWORD *)v1599;
              *(_DWORD *)(v1614 + 184) = DWORD2(v1599) | 4;
            }
            v1647 = *(_QWORD **)(v1644 + 120);
            if ( (unsigned __int64)v1647 >= v1642 && (unsigned __int64)v1647 < v1645 )
            {
              *(_QWORD *)(v1614 + 176) = *v1647;
              *(_DWORD *)(v1614 + 184) = v1646 | 8;
            }
            goto LABEL_2340;
          }
        }
LABEL_2586:
        v4007 = (_BYTE *)v1562;
        return 0;
      }
    }
    *(_DWORD *)(v1590 + 32) |= 2u;
    goto LABEL_2263;
  }
LABEL_2591:
  v1804 = __rdtsc();
  v1805 = (__ROR8__(v1804, 3) ^ v1804) * (unsigned __int128)0x7010008004002001ui64;
  v4015 = *((_QWORD *)&v1805 + 1);
  v1806 = *((_QWORD *)&v1805 + 1) ^ v1805;
  *((_QWORD *)&v1805 + 1) = ((*((_QWORD *)&v1805 + 1) ^ (unsigned __int64)v1805)
                           * (unsigned __int128)0x47AE147AE147AE15ui64) >> 64;
  if ( v1806 - 100 * ((*((_QWORD *)&v1805 + 1) + ((unsigned __int64)(v1806 - *((_QWORD *)&v1805 + 1)) >> 1)) >> 6) < 2 )
    *((_DWORD *)v207 + 612) |= 0x20000u;
  v1807 = *((_QWORD *)v207 + 172);
  v1808 = 32;
  v1809 = *((_DWORD *)v207 + 526);
  v1810 = *((unsigned int *)v207 + 505);
  v1811 = *((unsigned int *)v207 + 585);
  v1812 = *(_QWORD **)v1807;
  v1813 = 4 * *(_DWORD *)(v1807 + 16);
  HalExtensionList = v1807;
  LODWORD(Src) = v1809;
  if ( v1809 != 7 )
    v1808 = 0;
  v1814 = v1810 + 48;
  LODWORD(v3784) = v1808;
  if ( (unsigned int)(v1810 + 48) <= *((_DWORD *)v207 + 647) )
  {
    v1815 = v207;
    *((_DWORD *)v207 + 505) = v1814;
  }
  else
  {
    v1815 = (_BYTE *)sub_140B0F020(v207, v1814, v1811);
    if ( !v1815 )
      return 0;
    v1816 = *((_DWORD *)v207 + 612);
    if ( (v1816 & 4) == 0 )
    {
      v1817 = *((_DWORD *)v207 + 505);
      v1818 = *((_QWORD *)v207 + 249);
      v1819 = (v1816 & 0x20000000) != 0 ? *((_DWORD *)v207 + 585) : 0;
      if ( v1817 >= 8 )
      {
        v1820 = (unsigned __int64)v1817 >> 3;
        do
        {
          *(_QWORD *)v207 = 0i64;
          v1817 -= 8;
          v207 += 8;
          --v1820;
        }
        while ( v1820 );
      }
      for ( ; v1817; --v1817 )
        *v207++ = 0;
      v1821 = *((_DWORD *)v1815 + 585);
      *((_DWORD *)v1815 + 585) = v1819;
      if ( v1819 == 3 )
      {
        (*((void (__fastcall **)(__int64))v1815 + 109))(v1818);
      }
      else if ( (*((_DWORD *)v1815 + 612) & 0x10000000) != 0 || !v1819 )
      {
        (*((void (__fastcall **)(__int64))v1815 + 31))(v1818);
      }
      else
      {
        (*((void (__fastcall **)(__int64, _QWORD))v1815 + 69))(v1818 - 8, *(_QWORD *)(v1818 - 8));
      }
      v1808 = v3784;
      *((_DWORD *)v1815 + 585) = v1821;
    }
    *((_DWORD *)v1815 + 612) &= ~4u;
    v1809 = (int)Src;
  }
  ++*((_DWORD *)v1815 + 515);
  v1822 = (ULONG_PTR)&v1815[v1810];
  v1823 = 48;
  v3788 = (ULONG_PTR)&v1815[v1810];
  v1824 = &v1815[v1810];
  v1825 = 6i64;
  do
  {
    *v1824 = 0i64;
    v1823 -= 8;
    ++v1824;
    --v1825;
  }
  while ( v1825 );
  for ( ; v1823; --v1823 )
  {
    *(_BYTE *)v1824 = 0;
    v1824 = (_QWORD *)((char *)v1824 + 1);
  }
  *(_DWORD *)v1822 = v1808;
  *(_QWORD *)(v1822 + 8) = v1812;
  if ( v1809 == 7 && v1813 )
    sub_1403ED6CC(v1815, v1812, v1813, v1822 + 24);
  *(_DWORD *)(v1822 + 16) = v1813;
  v1826 = v1812;
  *((_DWORD *)v1815 + 522) += v1813;
  v1827 = (char *)v1812;
  v1828 = *((_DWORD *)v1815 + 517);
  v1829 = *((_QWORD *)v1815 + 259);
  v1830 = (unsigned __int64)v1812 + v1813;
  if ( (unsigned __int64)v1812 < v1830 )
  {
    do
    {
      _mm_prefetchnta(v1827);
      v1827 += 64;
    }
    while ( (unsigned __int64)v1827 < v1830 );
  }
  v1831 = *((_QWORD *)v1815 + 259);
  v1832 = v1813 >> 7;
  if ( v1813 >> 7 )
  {
    do
    {
      v1833 = 8i64;
      do
      {
        v1834 = v1826[1] ^ __ROL8__(*v1826 ^ v1831, v1828);
        v1826 += 2;
        v1831 = __ROL8__(v1834, v1828);
        --v1833;
      }
      while ( v1833 );
      v1835 = (__ROL8__(v1829 ^ ((char *)v1826 - (char *)v1812), 17) ^ v1829 ^ (unsigned __int64)((char *)v1826
                                                                                                - (char *)v1812))
            * (unsigned __int128)0x7010008004002001ui64;
      v4016 = *((_QWORD *)&v1835 + 1);
      v1828 = (BYTE8(v1835) ^ (unsigned __int8)(v1835 ^ v1828)) & 0x3F;
      if ( !v1828 )
        LOBYTE(v1828) = 1;
      --v1832;
    }
    while ( v1832 );
    v1822 = v3788;
  }
  v1836 = v1813 & 0x7F;
  if ( v1836 >= 8 )
  {
    v1837 = (unsigned __int64)(v1813 & 0x7F) >> 3;
    do
    {
      v1831 = __ROL8__(*v1826++ ^ v1831, v1828);
      v1836 -= 8;
      --v1837;
    }
    while ( v1837 );
  }
  for ( ; v1836; --v1836 )
  {
    v1838 = *(unsigned __int8 *)v1826;
    v1826 = (_QWORD *)((char *)v1826 + 1);
    v1831 = __ROL8__(v1838 ^ v1831, v1828);
  }
  for ( i27 = v1831; ; LODWORD(v1831) = i27 ^ v1831 )
  {
    i27 >>= 31;
    if ( !i27 )
      break;
  }
  v3981 = v1815;
  v4122[0] = 32;
  *(_DWORD *)(v1822 + 20) = v1831 & 0x7FFFFFFF;
  *((_DWORD *)v1815 + 522) += v1813;
  v1840 = 32;
  v1841 = *((_DWORD *)v1815 + 526);
  v1842 = *((unsigned int *)v1815 + 505);
  v1843 = *((unsigned int *)v1815 + 585);
  v4174[0] = (__int64)&KeServiceDescriptorTable;
  v4174[1] = (__int64)&xmmword_140E018E0;
  v4174[2] = (__int64)&KeServiceDescriptorTableShadow;
  v4174[3] = (__int64)&KeServiceDescriptorTableFilter;
  if ( v1841 != 7 )
    v1840 = 0;
  v4122[1] = 32;
  v1844 = v1842 + 192;
  v4122[2] = 32;
  v4122[3] = 32;
  LODWORD(Src) = 4;
  LODWORD(v3784) = v1841;
  LODWORD(v3783) = v1840;
  if ( (unsigned int)(v1842 + 192) <= *((_DWORD *)v1815 + 647) )
  {
    v1845 = v1815;
    *((_DWORD *)v1815 + 505) = v1844;
    v3788 = (ULONG_PTR)v1815;
  }
  else
  {
    v3788 = sub_140B0F020(v1815, v1844, v1843);
    v1845 = (_BYTE *)v3788;
    if ( !v3788 )
      return 0;
    v1846 = *((_DWORD *)v1815 + 612);
    if ( (v1846 & 4) == 0 )
    {
      v1847 = *((_DWORD *)v1815 + 505);
      v1848 = *((_QWORD *)v1815 + 249);
      v1849 = (v1846 & 0x20000000) != 0 ? *((_DWORD *)v1815 + 585) : 0;
      if ( v1847 >= 8 )
      {
        v1850 = (unsigned __int64)v1847 >> 3;
        do
        {
          *(_QWORD *)v1815 = 0i64;
          v1847 -= 8;
          v1815 += 8;
          --v1850;
        }
        while ( v1850 );
      }
      for ( ; v1847; --v1847 )
        *v1815++ = 0;
      v1851 = *((_DWORD *)v1845 + 585);
      *((_DWORD *)v1845 + 585) = v1849;
      if ( v1849 == 3 )
      {
        (*((void (__fastcall **)(__int64))v1845 + 109))(v1848);
      }
      else if ( (*((_DWORD *)v1845 + 612) & 0x10000000) != 0 || !v1849 )
      {
        (*((void (__fastcall **)(__int64))v1845 + 31))(v1848);
      }
      else
      {
        (*((void (__fastcall **)(__int64, _QWORD))v1845 + 69))(v1848 - 8, *(_QWORD *)(v1848 - 8));
      }
      *((_DWORD *)v1845 + 585) = v1851;
    }
    *((_DWORD *)v1845 + 612) &= ~4u;
    v1841 = v3784;
    v1840 = v3783;
  }
  *((_DWORD *)v1845 + 515) += 4;
  v1852 = v4174;
  v1853 = (ULONG_PTR)&v1845[v1842];
  v3786 = (unsigned __int64)v4174;
  v3787 = v1853;
  v1854 = v4122;
  v3790 = 4i64;
  do
  {
    v1855 = (unsigned int)*v1854;
    v1856 = 48;
    v1857 = (_QWORD *)*v1852;
    v1858 = (_QWORD *)v1853;
    v1859 = 6i64;
    do
    {
      *v1858 = 0i64;
      v1856 -= 8;
      ++v1858;
      --v1859;
    }
    while ( v1859 );
    for ( ; v1856; --v1856 )
    {
      *(_BYTE *)v1858 = 0;
      v1858 = (_QWORD *)((char *)v1858 + 1);
    }
    *(_DWORD *)v1853 = v1840;
    *(_QWORD *)(v1853 + 8) = v1857;
    if ( v1841 == 7 && (_DWORD)v1855 )
      sub_1403ED6CC(v1845, v1857, (unsigned int)v1855, v1853 + 24);
    *(_DWORD *)(v1853 + 16) = v1855;
    *((_DWORD *)v1845 + 522) += v1855;
    v1860 = v1857;
    v1861 = *((_DWORD *)v1845 + 517);
    v1862 = (char *)v1857;
    v1863 = *((_QWORD *)v1845 + 259);
    if ( v1857 < (_QWORD *)((char *)v1857 + v1855) )
    {
      do
      {
        _mm_prefetchnta(v1862);
        v1862 += 64;
      }
      while ( v1862 < (char *)v1857 + v1855 );
    }
    v1864 = *((_QWORD *)v1845 + 259);
    v1865 = (unsigned int)v1855 >> 7;
    if ( (unsigned int)v1855 >> 7 )
    {
      do
      {
        v1866 = 8i64;
        do
        {
          v1867 = v1860[1] ^ __ROL8__(*v1860 ^ v1864, v1861);
          v1860 += 2;
          v1864 = __ROL8__(v1867, v1861);
          --v1866;
        }
        while ( v1866 );
        v1868 = (__ROL8__(v1863 ^ ((char *)v1860 - (char *)v1857), 17) ^ v1863 ^ (unsigned __int64)((char *)v1860
                                                                                                  - (char *)v1857))
              * (unsigned __int128)0x7010008004002001ui64;
        v4017 = *((_QWORD *)&v1868 + 1);
        v1861 = (BYTE8(v1868) ^ (unsigned __int8)(v1868 ^ v1861)) & 0x3F;
        if ( !v1861 )
          LOBYTE(v1861) = 1;
        --v1865;
      }
      while ( v1865 );
      v1845 = (_BYTE *)v3788;
      v1852 = (__int64 *)v3786;
    }
    v1869 = v1855 & 0x7F;
    if ( v1869 >= 8 )
    {
      v1870 = (unsigned __int64)(v1855 & 0x7F) >> 3;
      do
      {
        v1864 = __ROL8__(*v1860++ ^ v1864, v1861);
        v1869 -= 8;
        --v1870;
      }
      while ( v1870 );
    }
    for ( ; v1869; --v1869 )
    {
      v1871 = *(unsigned __int8 *)v1860;
      v1860 = (_QWORD *)((char *)v1860 + 1);
      v1864 = __ROL8__(v1871 ^ v1864, v1861);
    }
    for ( i28 = v1864 >> 31; i28; i28 >>= 31 )
      LODWORD(v1864) = i28 ^ v1864;
    v1841 = v3784;
    v1840 = v3783;
    ++v1852;
    *(_DWORD *)(v1853 + 20) = v1864 & 0x7FFFFFFF;
    ++v1854;
    *((_DWORD *)v1845 + 522) += v1855;
    v1853 += 48i64;
    v875 = v3790-- == 1;
    v3786 = (unsigned __int64)v1852;
  }
  while ( !v875 );
  v1873 = v3787;
  if ( v1841 == 7 )
  {
    v1874 = (int)Src;
    do
    {
      *(_DWORD *)(v1873 + 40) |= 1u;
      v1873 += 48i64;
      --v1874;
    }
    while ( v1874 );
  }
  v1875 = 0;
  v3981 = v1845;
  v3788 = *(_QWORD *)HalExtensionList;
  if ( (*((_DWORD *)v1845 + 612) & 0x40000000) != 0 )
    goto LABEL_2728;
  v1876 = 0;
  if ( !*(_DWORD *)(HalExtensionList + 16) )
    goto LABEL_2728;
  do
  {
    if ( !(*((__int64 (__fastcall **)(ULONG_PTR, char *, _QWORD))v1845 + 76))(
            v3788 + ((__int64)*(int *)(v3788 + 4i64 * v1876) >> 4),
            v4018,
            0i64) )
      ++v1875;
    ++v1876;
  }
  while ( v1876 < *(_DWORD *)(HalExtensionList + 16) );
  if ( !v1875 )
  {
LABEL_2728:
    v3981 = v1845;
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    v1901 = *((unsigned int *)v1845 + 505);
    v1902 = v1901 + 48;
    if ( (unsigned int)(v1901 + 48) <= *((_DWORD *)v1845 + 647) )
    {
      v1903 = v1845;
      *((_DWORD *)v1845 + 505) = v1902;
    }
    else
    {
      v1903 = (_BYTE *)sub_140B0F020(v1845, v1902, *((_DWORD *)v1845 + 585));
      if ( !v1903 )
        return 0;
      v1904 = *((_DWORD *)v1845 + 612);
      if ( (v1904 & 4) == 0 )
      {
        v1905 = *((_DWORD *)v1845 + 505);
        v1906 = *((_QWORD *)v1845 + 249);
        v1907 = (v1904 & 0x20000000) != 0 ? *((_DWORD *)v1845 + 585) : 0;
        if ( v1905 >= 8 )
        {
          v1908 = (unsigned __int64)v1905 >> 3;
          do
          {
            *(_QWORD *)v1845 = 0i64;
            v1905 -= 8;
            v1845 += 8;
            --v1908;
          }
          while ( v1908 );
        }
        for ( ; v1905; --v1905 )
          *v1845++ = 0;
        v1909 = *((_DWORD *)v1903 + 585);
        *((_DWORD *)v1903 + 585) = v1907;
        if ( v1907 == 3 )
        {
          (*((void (__fastcall **)(__int64))v1903 + 109))(v1906);
        }
        else if ( (*((_DWORD *)v1903 + 612) & 0x10000000) != 0 || !v1907 )
        {
          (*((void (__fastcall **)(__int64))v1903 + 31))(v1906);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v1903 + 69))(v1906 - 8, *(_QWORD *)(v1906 - 8));
        }
        *((_DWORD *)v1903 + 585) = v1909;
      }
      *((_DWORD *)v1903 + 612) &= ~4u;
    }
    ++*((_DWORD *)v1903 + 515);
    v1910 = &v1903[v1901];
    v1911 = 48;
    v1912 = v1910;
    v1913 = 6i64;
    do
    {
      *v1912 = 0i64;
      v1911 -= 8;
      ++v1912;
      --v1913;
    }
    while ( v1913 );
    for ( ; v1911; --v1911 )
    {
      *(_BYTE *)v1912 = 0;
      v1912 = (_QWORD *)((char *)v1912 + 1);
    }
    *(_DWORD *)v1910 = 36;
    *((_QWORD *)v1910 + 1) = &xmmword_140E00030;
    v1914 = &xmmword_140E00030;
    *((_DWORD *)v1910 + 4) = 24;
    *((_DWORD *)v1903 + 522) += 24;
    v1915 = *((_DWORD *)v1903 + 517);
    v1916 = *((_QWORD *)v1903 + 259);
    _mm_prefetchnta(&xmmword_140E00030);
    v1917 = 3i64;
    LODWORD(v1918) = 24;
    do
    {
      v1918 = (unsigned int)(v1918 - 8);
      v1916 = __ROL8__(*(_QWORD *)v1914 ^ v1916, v1915);
      v1914 = (__int128 *)((char *)v1914 + 8);
      --v1917;
    }
    while ( v1917 );
    if ( (_DWORD)v1918 )
    {
      do
      {
        v1919 = *(unsigned __int8 *)v1914;
        v1914 = (__int128 *)((char *)v1914 + 1);
        v1916 = __ROL8__(v1919 ^ v1916, v1915);
        v875 = (_DWORD)v1918 == 1;
        v1918 = (unsigned int)(v1918 - 1);
      }
      while ( !v875 );
    }
    for ( i29 = v1916; ; v1916 = (unsigned int)i29 ^ (unsigned int)v1916 )
    {
      i29 >>= 31;
      if ( !i29 )
        break;
    }
    LODWORD(v1916) = v1916 & 0x7FFFFFFF;
    v1921 = v1910 + 24;
    *((_DWORD *)v1910 + 5) = v1916;
    v1922 = -1073741275;
    *((_DWORD *)v1903 + 522) += 24;
    v1923 = PsHalImageBase;
    v1924 = *((_QWORD *)v1903 + 167);
    v1925 = KeGetCurrentIrql();
    __writecr8(0xFui64);
    (*((void (__fastcall **)(__int64, unsigned __int64, __int64, __int64))v1903 + 42))(
      v1924,
      v1916,
      v1918,
      4294967288i64);
    v1926 = (unsigned int *)**((_QWORD **)v1903 + 195);
    v1927 = (unsigned __int64)(v1926 + 4);
    while ( *(_QWORD *)(v1927 + 8) != v1923 )
    {
      v1927 += 24i64;
      if ( v1927 >= (unsigned __int64)&v1926[6 * *v1926 + 4] )
        goto LABEL_2765;
    }
    v1922 = 0;
    *v1921 = *(_OWORD *)v1927;
    *((_QWORD *)v1910 + 5) = *(_QWORD *)(v1927 + 16);
LABEL_2765:
    (*((void (__fastcall **)(_QWORD))v1903 + 50))(*((_QWORD *)v1903 + 167));
    __writecr8(v1925);
    if ( v1922 < 0 )
    {
      v1928 = 24;
      v1929 = 3i64;
      do
      {
        *(_QWORD *)v1921 = 0i64;
        v1928 -= 8;
        v1921 = (_OWORD *)((char *)v1921 + 8);
        --v1929;
      }
      while ( v1929 );
      for ( ; v1928; --v1928 )
      {
        *(_BYTE *)v1921 = 0;
        v1921 = (_OWORD *)((char *)v1921 + 1);
      }
      *((_QWORD *)v1910 + 3) = 1i64;
    }
    v3981 = v1903;
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    v1930 = *((unsigned int *)v1903 + 505);
    v1931 = v1930 + 48;
    if ( (unsigned int)(v1930 + 48) <= *((_DWORD *)v1903 + 647) )
    {
      v1932 = v1903;
      *((_DWORD *)v1903 + 505) = v1931;
    }
    else
    {
      v1932 = (_BYTE *)sub_140B0F020(v1903, v1931, *((_DWORD *)v1903 + 585));
      if ( !v1932 )
        return 0;
      v1933 = *((_DWORD *)v1903 + 612);
      if ( (v1933 & 4) == 0 )
      {
        v1934 = *((_DWORD *)v1903 + 505);
        v1935 = *((_QWORD *)v1903 + 249);
        v1936 = (v1933 & 0x20000000) != 0 ? *((_DWORD *)v1903 + 585) : 0;
        if ( v1934 >= 8 )
        {
          v1937 = (unsigned __int64)v1934 >> 3;
          do
          {
            *(_QWORD *)v1903 = 0i64;
            v1934 -= 8;
            v1903 += 8;
            --v1937;
          }
          while ( v1937 );
        }
        for ( ; v1934; --v1934 )
          *v1903++ = 0;
        v1938 = *((_DWORD *)v1932 + 585);
        *((_DWORD *)v1932 + 585) = v1936;
        if ( v1936 == 3 )
        {
          (*((void (__fastcall **)(__int64))v1932 + 109))(v1935);
        }
        else if ( (*((_DWORD *)v1932 + 612) & 0x10000000) != 0 || !v1936 )
        {
          (*((void (__fastcall **)(__int64))v1932 + 31))(v1935);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v1932 + 69))(v1935 - 8, *(_QWORD *)(v1935 - 8));
        }
        *((_DWORD *)v1932 + 585) = v1938;
      }
      *((_DWORD *)v1932 + 612) &= ~4u;
    }
    ++*((_DWORD *)v1932 + 515);
    v1939 = &v1932[v1930];
    v1940 = 48;
    v1941 = &v1932[v1930];
    v1942 = 6i64;
    do
    {
      *v1941 = 0i64;
      v1940 -= 8;
      ++v1941;
      --v1942;
    }
    while ( v1942 );
    for ( ; v1940; --v1940 )
    {
      *(_BYTE *)v1941 = 0;
      v1941 = (_QWORD *)((char *)v1941 + 1);
    }
    *(_DWORD *)v1939 = 4;
    *((_QWORD *)v1939 + 1) = 0i64;
    *((_DWORD *)v1939 + 4) = 0;
    v1943 = *((_QWORD *)v1932 + 259);
    for ( i30 = v1943; ; LODWORD(v1943) = i30 ^ v1943 )
    {
      i30 >>= 31;
      if ( !i30 )
        break;
    }
    v3981 = v1932;
    *((_DWORD *)v1939 + 5) = v1943 & 0x7FFFFFFF;
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    v1945 = *((unsigned int *)v1932 + 505);
    v1946 = v1945 + 48;
    if ( (unsigned int)(v1945 + 48) <= *((_DWORD *)v1932 + 647) )
    {
      v1947 = v1932;
      *((_DWORD *)v1932 + 505) = v1946;
    }
    else
    {
      v1947 = (_BYTE *)sub_140B0F020(v1932, v1946, *((_DWORD *)v1932 + 585));
      if ( !v1947 )
        return 0;
      v1948 = *((_DWORD *)v1932 + 612);
      if ( (v1948 & 4) == 0 )
      {
        v1949 = *((_DWORD *)v1932 + 505);
        v1950 = *((_QWORD *)v1932 + 249);
        v1951 = (v1948 & 0x20000000) != 0 ? *((_DWORD *)v1932 + 585) : 0;
        if ( v1949 >= 8 )
        {
          v1952 = (unsigned __int64)v1949 >> 3;
          do
          {
            *(_QWORD *)v1932 = 0i64;
            v1949 -= 8;
            v1932 += 8;
            --v1952;
          }
          while ( v1952 );
        }
        for ( ; v1949; --v1949 )
          *v1932++ = 0;
        v1953 = *((_DWORD *)v1947 + 585);
        *((_DWORD *)v1947 + 585) = v1951;
        if ( v1951 == 3 )
        {
          (*((void (__fastcall **)(__int64))v1947 + 109))(v1950);
        }
        else if ( (*((_DWORD *)v1947 + 612) & 0x10000000) != 0 || !v1951 )
        {
          (*((void (__fastcall **)(__int64))v1947 + 31))(v1950);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v1947 + 69))(v1950 - 8, *(_QWORD *)(v1950 - 8));
        }
        *((_DWORD *)v1947 + 585) = v1953;
      }
      *((_DWORD *)v1947 + 612) &= ~4u;
    }
    ++*((_DWORD *)v1947 + 515);
    v1954 = &v1947[v1945];
    v1955 = 48;
    v1956 = &v1947[v1945];
    v1957 = 6i64;
    do
    {
      *v1956 = 0i64;
      v1955 -= 8;
      ++v1956;
      --v1957;
    }
    while ( v1957 );
    for ( ; v1955; --v1955 )
    {
      *(_BYTE *)v1956 = 0;
      v1956 = (_QWORD *)((char *)v1956 + 1);
    }
    *(_DWORD *)v1954 = 5;
    *((_QWORD *)v1954 + 1) = 0i64;
    *((_DWORD *)v1954 + 4) = 0;
    v1958 = *((_QWORD *)v1947 + 259);
    for ( i31 = v1958; ; LODWORD(v1958) = i31 ^ v1958 )
    {
      i31 >>= 31;
      if ( !i31 )
        break;
    }
    v3981 = v1947;
    *((_DWORD *)v1954 + 5) = v1958 & 0x7FFFFFFF;
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    v1960 = *((unsigned int *)v1947 + 505);
    v1961 = v1960 + 48;
    if ( (unsigned int)(v1960 + 48) <= *((_DWORD *)v1947 + 647) )
    {
      v1962 = v1947;
      *((_DWORD *)v1947 + 505) = v1961;
    }
    else
    {
      v1962 = (_BYTE *)sub_140B0F020(v1947, v1961, *((_DWORD *)v1947 + 585));
      if ( !v1962 )
        return 0;
      v1963 = *((_DWORD *)v1947 + 612);
      if ( (v1963 & 4) == 0 )
      {
        v1964 = *((_DWORD *)v1947 + 505);
        v1965 = *((_QWORD *)v1947 + 249);
        v1966 = (v1963 & 0x20000000) != 0 ? *((_DWORD *)v1947 + 585) : 0;
        if ( v1964 >= 8 )
        {
          v1967 = (unsigned __int64)v1964 >> 3;
          do
          {
            *(_QWORD *)v1947 = 0i64;
            v1964 -= 8;
            v1947 += 8;
            --v1967;
          }
          while ( v1967 );
        }
        for ( ; v1964; --v1964 )
          *v1947++ = 0;
        v1968 = *((_DWORD *)v1962 + 585);
        *((_DWORD *)v1962 + 585) = v1966;
        if ( v1966 == 3 )
        {
          (*((void (__fastcall **)(__int64))v1962 + 109))(v1965);
        }
        else if ( (*((_DWORD *)v1962 + 612) & 0x10000000) != 0 || !v1966 )
        {
          (*((void (__fastcall **)(__int64))v1962 + 31))(v1965);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v1962 + 69))(v1965 - 8, *(_QWORD *)(v1965 - 8));
        }
        *((_DWORD *)v1962 + 585) = v1968;
      }
      *((_DWORD *)v1962 + 612) &= ~4u;
    }
    ++*((_DWORD *)v1962 + 515);
    v1969 = &v1962[v1960];
    v1970 = 48;
    v1971 = &v1962[v1960];
    v1972 = 6i64;
    do
    {
      *v1971 = 0i64;
      v1970 -= 8;
      ++v1971;
      --v1972;
    }
    while ( v1972 );
    for ( ; v1970; --v1970 )
    {
      *(_BYTE *)v1971 = 0;
      v1971 = (_QWORD *)((char *)v1971 + 1);
    }
    *(_DWORD *)v1969 = 25;
    *((_QWORD *)v1969 + 1) = 0i64;
    *((_DWORD *)v1969 + 4) = 0;
    v1973 = *((_QWORD *)v1962 + 259);
    for ( i32 = v1973; ; LODWORD(v1973) = i32 ^ v1973 )
    {
      i32 >>= 31;
      if ( !i32 )
        break;
    }
    v3981 = v1962;
    *((_DWORD *)v1969 + 5) = v1973 & 0x7FFFFFFF;
    v1975 = 0;
    if ( ExpInitializeCallback[0] )
    {
      do
        ++v1975;
      while ( ExpInitializeCallback[2 * v1975] );
    }
    v1976 = *((unsigned int *)v1962 + 505);
    v1977 = 16 * v1975;
    v1978 = v1976 + 48;
    if ( (unsigned int)(v1976 + 48) <= *((_DWORD *)v1962 + 647) )
    {
      v1979 = v1962;
      *((_DWORD *)v1962 + 505) = v1978;
    }
    else
    {
      v1979 = (_BYTE *)sub_140B0F020(v1962, v1978, *((_DWORD *)v1962 + 585));
      if ( !v1979 )
        return 0;
      v1980 = *((_DWORD *)v1962 + 612);
      if ( (v1980 & 4) == 0 )
      {
        v1981 = *((_DWORD *)v1962 + 505);
        v1982 = *((_QWORD *)v1962 + 249);
        v1983 = (v1980 & 0x20000000) != 0 ? *((_DWORD *)v1962 + 585) : 0;
        if ( v1981 >= 8 )
        {
          v1984 = (unsigned __int64)v1981 >> 3;
          do
          {
            *(_QWORD *)v1962 = 0i64;
            v1981 -= 8;
            v1962 += 8;
            --v1984;
          }
          while ( v1984 );
        }
        for ( ; v1981; --v1981 )
          *v1962++ = 0;
        v1985 = *((_DWORD *)v1979 + 585);
        *((_DWORD *)v1979 + 585) = v1983;
        if ( v1983 == 3 )
        {
          (*((void (__fastcall **)(__int64))v1979 + 109))(v1982);
        }
        else if ( (*((_DWORD *)v1979 + 612) & 0x10000000) != 0 || !v1983 )
        {
          (*((void (__fastcall **)(__int64))v1979 + 31))(v1982);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v1979 + 69))(v1982 - 8, *(_QWORD *)(v1982 - 8));
        }
        *((_DWORD *)v1979 + 585) = v1985;
      }
      *((_DWORD *)v1979 + 612) &= ~4u;
    }
    ++*((_DWORD *)v1979 + 515);
    v1986 = (ULONG_PTR)&v1979[v1976];
    v1987 = 48;
    HalExtensionList = (ULONG_PTR)&v1979[v1976];
    v1988 = &v1979[v1976];
    v1989 = 6i64;
    do
    {
      *v1988 = 0i64;
      v1987 -= 8;
      ++v1988;
      --v1989;
    }
    while ( v1989 );
    for ( ; v1987; --v1987 )
    {
      *(_BYTE *)v1988 = 0;
      v1988 = (_QWORD *)((char *)v1988 + 1);
    }
    *(_DWORD *)v1986 = 29;
    v1990 = ExpInitializeCallback;
    *(_QWORD *)(v1986 + 8) = ExpInitializeCallback;
    v1991 = ExpInitializeCallback;
    *(_DWORD *)(v1986 + 16) = v1977;
    *((_DWORD *)v1979 + 522) += v1977;
    v1992 = *((_DWORD *)v1979 + 517);
    v1993 = *((_QWORD *)v1979 + 259);
    v1994 = &ExpInitializeCallback[v1977 / 8];
    if ( ExpInitializeCallback < v1994 )
    {
      do
      {
        _mm_prefetchnta(v1991);
        v1991 += 8;
      }
      while ( v1991 < v1994 );
    }
    v1995 = *((_QWORD *)v1979 + 259);
    v1996 = v1977 >> 7;
    if ( v1977 >> 7 )
    {
      do
      {
        v1997 = 8i64;
        do
        {
          v1998 = *v1990 ^ v1995;
          v1999 = v1990 + 1;
          v2000 = *v1999 ^ __ROL8__(v1998, v1992);
          v1990 = v1999 + 1;
          v1995 = __ROL8__(v2000, v1992);
          --v1997;
        }
        while ( v1997 );
        v2001 = (__ROL8__(v1993 ^ ((char *)v1990 - (char *)ExpInitializeCallback), 17) ^ v1993 ^ (unsigned __int64)((char *)v1990 - (char *)ExpInitializeCallback))
              * (unsigned __int128)0x7010008004002001ui64;
        v4019 = *((_QWORD *)&v2001 + 1);
        v1992 = (BYTE8(v2001) ^ (unsigned __int8)(v2001 ^ v1992)) & 0x3F;
        if ( !v1992 )
          LOBYTE(v1992) = 1;
        --v1996;
      }
      while ( v1996 );
      v1986 = HalExtensionList;
    }
    v2002 = v1977 & 0x7F;
    if ( v2002 >= 8 )
    {
      v2003 = (unsigned __int64)(v1977 & 0x7F) >> 3;
      do
      {
        v1995 = __ROL8__(*v1990++ ^ v1995, v1992);
        v2002 -= 8;
        --v2003;
      }
      while ( v2003 );
    }
    for ( ; v2002; --v2002 )
    {
      v2004 = *(unsigned __int8 *)v1990;
      v1990 = (__int64 *)((char *)v1990 + 1);
      v1995 = __ROL8__(v2004 ^ v1995, v1992);
    }
    for ( i33 = v1995 >> 31; i33; i33 >>= 31 )
      LODWORD(v1995) = i33 ^ v1995;
    *(_DWORD *)(v1986 + 20) = v1995 & 0x7FFFFFFF;
    *((_DWORD *)v1979 + 522) += v1977;
    if ( (*((_DWORD *)v1979 + 612) & 0x40000000) != 0 )
    {
      v2006 = *((unsigned int *)v1979 + 505);
      v2007 = *(unsigned int *)(v1986 + 16);
      v2008 = *(_QWORD **)(v1986 + 8);
      v2009 = v2006 + 48;
      if ( (unsigned int)(v2006 + 48) <= *((_DWORD *)v1979 + 647) )
      {
        v2010 = (__int64)v1979;
        *((_DWORD *)v1979 + 505) = v2009;
      }
      else
      {
        v2010 = sub_140B0F020(v1979, v2009, *((_DWORD *)v1979 + 585));
        if ( !v2010 )
          return 0;
        v2011 = *((_DWORD *)v1979 + 612);
        if ( (v2011 & 4) == 0 )
        {
          v2012 = *((_DWORD *)v1979 + 505);
          v2013 = *((_QWORD *)v1979 + 249);
          v2014 = (v2011 & 0x20000000) != 0 ? *((_DWORD *)v1979 + 585) : 0;
          if ( v2012 >= 8 )
          {
            v2015 = (unsigned __int64)v2012 >> 3;
            do
            {
              *(_QWORD *)v1979 = 0i64;
              v2012 -= 8;
              v1979 += 8;
              --v2015;
            }
            while ( v2015 );
          }
          for ( ; v2012; --v2012 )
            *v1979++ = 0;
          v2016 = *(_DWORD *)(v2010 + 2340);
          *(_DWORD *)(v2010 + 2340) = v2014;
          if ( v2014 == 3 )
          {
            (*(void (__fastcall **)(__int64))(v2010 + 872))(v2013);
          }
          else if ( (*(_DWORD *)(v2010 + 2448) & 0x10000000) != 0 || !v2014 )
          {
            (*(void (__fastcall **)(__int64))(v2010 + 248))(v2013);
          }
          else
          {
            (*(void (__fastcall **)(__int64, _QWORD))(v2010 + 552))(v2013 - 8, *(_QWORD *)(v2013 - 8));
          }
          *(_DWORD *)(v2010 + 2340) = v2016;
        }
        *(_DWORD *)(v2010 + 2448) &= ~4u;
      }
      ++*(_DWORD *)(v2010 + 2060);
      v2017 = v2010 + v2006;
      HalExtensionList = v2017;
      v2018 = (_QWORD *)v2017;
      v2019 = 48;
      v2020 = 6i64;
      do
      {
        *v2018 = 0i64;
        v2019 -= 8;
        ++v2018;
        --v2020;
      }
      while ( v2020 );
      for ( ; v2019; --v2019 )
      {
        *(_BYTE *)v2018 = 0;
        v2018 = (_QWORD *)((char *)v2018 + 1);
      }
      *(_DWORD *)v2017 = 32;
      *(_QWORD *)(v2017 + 8) = v2008;
      if ( (_DWORD)v2007 )
        sub_1403ED6CC(v2010, v2008, (unsigned int)v2007, v2017 + 24);
      *(_DWORD *)(v2017 + 16) = v2007;
      *(_DWORD *)(v2010 + 2088) += v2007;
      v2021 = v2008;
      v2022 = *(_DWORD *)(v2010 + 2068);
      v2023 = (char *)v2008;
      v2024 = *(_QWORD *)(v2010 + 2072);
      if ( v2008 < (_QWORD *)((char *)v2008 + v2007) )
      {
        do
        {
          _mm_prefetchnta(v2023);
          v2023 += 64;
        }
        while ( v2023 < (char *)v2008 + v2007 );
      }
      v2025 = *(_QWORD *)(v2010 + 2072);
      v2026 = (unsigned int)v2007 >> 7;
      if ( (unsigned int)v2007 >> 7 )
      {
        do
        {
          v2027 = 8i64;
          do
          {
            v2028 = v2021[1] ^ __ROL8__(*v2021 ^ v2025, v2022);
            v2021 += 2;
            v2025 = __ROL8__(v2028, v2022);
            --v2027;
          }
          while ( v2027 );
          v2029 = (__ROL8__(v2024 ^ ((char *)v2021 - (char *)v2008), 17) ^ v2024 ^ (unsigned __int64)((char *)v2021 - (char *)v2008))
                * (unsigned __int128)0x7010008004002001ui64;
          v4020 = *((_QWORD *)&v2029 + 1);
          v2022 = (BYTE8(v2029) ^ (unsigned __int8)(v2029 ^ v2022)) & 0x3F;
          if ( !v2022 )
            LOBYTE(v2022) = 1;
          --v2026;
        }
        while ( v2026 );
        v2017 = HalExtensionList;
      }
      v2030 = v2007 & 0x7F;
      if ( v2030 >= 8 )
      {
        v2031 = (unsigned __int64)(v2007 & 0x7F) >> 3;
        do
        {
          v2025 = __ROL8__(*v2021++ ^ v2025, v2022);
          v2030 -= 8;
          --v2031;
        }
        while ( v2031 );
      }
      for ( ; v2030; --v2030 )
      {
        v2032 = *(unsigned __int8 *)v2021;
        v2021 = (_QWORD *)((char *)v2021 + 1);
        v2025 = __ROL8__(v2032 ^ v2025, v2022);
      }
      for ( i34 = v2025; ; LODWORD(v2025) = i34 ^ v2025 )
      {
        i34 >>= 31;
        if ( !i34 )
          break;
      }
      v1979 = (_BYTE *)v2010;
      *(_DWORD *)(v2017 + 20) = v2025 & 0x7FFFFFFF;
      *(_DWORD *)(v2010 + 2088) += v2007;
      *(_DWORD *)(v2017 + 40) = 0;
    }
    v3981 = v1979;
    if ( !v1979 )
      return 0;
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    v2034 = 32;
    v2035 = *((_DWORD *)v1979 + 526);
    v2036 = *((unsigned int *)v1979 + 505);
    v2037 = *((unsigned int *)v1979 + 585);
    LODWORD(Src) = *(_DWORD *)((char *)ObpTypeObjectType + *((_QWORD *)v1979 + 222));
    v2038 = 8 * (_DWORD)Src;
    LODWORD(v3784) = 8 * (_DWORD)Src;
    if ( v2035 != 7 )
      v2034 = 0;
    v2039 = v2036 + 48;
    if ( (unsigned int)(v2036 + 48) <= *((_DWORD *)v1979 + 647) )
    {
      v2040 = v1979;
      *((_DWORD *)v1979 + 505) = v2039;
    }
    else
    {
      v2040 = (_BYTE *)sub_140B0F020(v1979, v2039, v2037);
      if ( !v2040 )
        return 0;
      v2041 = *((_DWORD *)v1979 + 612);
      if ( (v2041 & 4) == 0 )
      {
        v2042 = *((_DWORD *)v1979 + 505);
        v2043 = *((_QWORD *)v1979 + 249);
        v2044 = (v2041 & 0x20000000) != 0 ? *((_DWORD *)v1979 + 585) : 0;
        if ( v2042 >= 8 )
        {
          v2045 = (unsigned __int64)v2042 >> 3;
          do
          {
            *(_QWORD *)v1979 = 0i64;
            v2042 -= 8;
            v1979 += 8;
            --v2045;
          }
          while ( v2045 );
        }
        for ( ; v2042; --v2042 )
          *v1979++ = 0;
        v2046 = *((_DWORD *)v2040 + 585);
        *((_DWORD *)v2040 + 585) = v2044;
        if ( v2044 == 3 )
        {
          (*((void (__fastcall **)(__int64))v2040 + 109))(v2043);
        }
        else if ( (*((_DWORD *)v2040 + 612) & 0x10000000) != 0 || !v2044 )
        {
          (*((void (__fastcall **)(__int64))v2040 + 31))(v2043);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v2040 + 69))(v2043 - 8, *(_QWORD *)(v2043 - 8));
        }
        *((_DWORD *)v2040 + 585) = v2046;
      }
      *((_DWORD *)v2040 + 612) &= ~4u;
    }
    v2047 = (ULONG_PTR)&v2040[v2036];
    ++*((_DWORD *)v2040 + 515);
    v2048 = (_QWORD *)v2047;
    HalExtensionList = v2047;
    v2049 = 48;
    v2050 = 6i64;
    do
    {
      *v2048 = 0i64;
      v2049 -= 8;
      ++v2048;
      --v2050;
    }
    while ( v2050 );
    for ( ; v2049; --v2049 )
    {
      *(_BYTE *)v2048 = 0;
      v2048 = (_QWORD *)((char *)v2048 + 1);
    }
    *(_DWORD *)v2047 = v2034;
    *(_QWORD *)(v2047 + 8) = ObpObjectTypes;
    if ( v2035 == 7 && v2038 )
      sub_1403ED6CC(v2040, ObpObjectTypes, v2038, v2047 + 24);
    *(_DWORD *)(v2047 + 16) = v2038;
    v2051 = ObpObjectTypes;
    *((_DWORD *)v2040 + 522) += v2038;
    v2052 = ObpObjectTypes;
    v2053 = *((_DWORD *)v2040 + 517);
    v2054 = *((_QWORD *)v2040 + 259);
    v2055 = (__int64 *)((char *)ObpObjectTypes + v2038);
    if ( ObpObjectTypes < v2055 )
    {
      do
      {
        _mm_prefetchnta(v2052);
        v2052 += 8;
      }
      while ( v2052 < v2055 );
    }
    v2056 = *((_QWORD *)v2040 + 259);
    v2057 = v2038 >> 7;
    if ( v2038 >> 7 )
    {
      do
      {
        v2058 = 8i64;
        do
        {
          v2059 = v2051[1] ^ __ROL8__(*v2051 ^ v2056, v2053);
          v2051 += 2;
          v2056 = __ROL8__(v2059, v2053);
          --v2058;
        }
        while ( v2058 );
        v2060 = (__ROL8__(v2054 ^ ((char *)v2051 - (char *)ObpObjectTypes), 17) ^ v2054 ^ (unsigned __int64)((char *)v2051 - (char *)ObpObjectTypes))
              * (unsigned __int128)0x7010008004002001ui64;
        v4021 = *((_QWORD *)&v2060 + 1);
        v2053 = (BYTE8(v2060) ^ (unsigned __int8)(v2060 ^ v2053)) & 0x3F;
        if ( !v2053 )
          LOBYTE(v2053) = 1;
        --v2057;
      }
      while ( v2057 );
      v2047 = HalExtensionList;
      v2038 = v3784;
    }
    v2061 = v2038 & 0x7F;
    if ( v2061 >= 8 )
    {
      v2062 = (unsigned __int64)(v2038 & 0x7F) >> 3;
      do
      {
        v2056 = __ROL8__(*v2051++ ^ v2056, v2053);
        v2061 -= 8;
        --v2062;
      }
      while ( v2062 );
    }
    for ( ; v2061; --v2061 )
    {
      v2063 = *(unsigned __int8 *)v2051;
      v2051 = (__int64 *)((char *)v2051 + 1);
      v2056 = __ROL8__(v2063 ^ v2056, v2053);
    }
    for ( i35 = v2056 >> 31; i35; i35 >>= 31 )
      LODWORD(v2056) = i35 ^ v2056;
    LODWORD(v3785) = 0;
    *(_DWORD *)(v2047 + 20) = v2056 & 0x7FFFFFFF;
    *((_DWORD *)v2040 + 522) += v2038;
    v2065 = (unsigned int)Src;
    v2066 = *((_DWORD *)v2040 + 452);
    v2067 = *((_DWORD *)v2040 + 454);
    LODWORD(v3784) = v2066;
    LODWORD(v3783) = v2067;
    if ( (_DWORD)Src )
    {
      do
      {
        v2068 = ObpObjectTypes[(unsigned int)i35];
        if ( v2068 )
        {
          if ( (*(_BYTE *)(v2068 - 48 + 26) & 2) != 0 )
          {
            v2069 = v2068 - 48 - ObpInfoMaskToOffset[*(_BYTE *)(v2068 - 48 + 26) & 3];
            if ( v2069 )
            {
              v2070 = *(unsigned __int16 *)(v2069 + 8);
              if ( (_WORD)v2070 )
              {
                if ( *(_BYTE *)(v2068 + 40) != v2040[1824] )
                {
                  v2071 = *((unsigned int *)v2040 + 505);
                  v2072 = *((unsigned int *)v2040 + 585);
                  LODWORD(v3791) = v2070 + 26;
                  v2073 = v2071 + ((v2070 + 33) & 0xFFFFFFF8) + 48;
                  v2074 = (_QWORD *)(v2068 + v2066);
                  if ( v2073 <= *((_DWORD *)v2040 + 647) )
                  {
                    v2075 = v2040;
                    *((_DWORD *)v2040 + 505) = v2073;
                  }
                  else
                  {
                    v2075 = (_BYTE *)sub_140B0F020(v2040, v2073, v2072);
                    if ( !v2075 )
                      return 0;
                    v2076 = *((_DWORD *)v2040 + 612);
                    if ( (v2076 & 4) == 0 )
                    {
                      v2077 = *((_DWORD *)v2040 + 505);
                      v2078 = *((_QWORD *)v2040 + 249);
                      v2079 = (v2076 & 0x20000000) != 0 ? *((_DWORD *)v2040 + 585) : 0;
                      if ( v2077 >= 8 )
                      {
                        v2080 = (unsigned __int64)v2077 >> 3;
                        do
                        {
                          *(_QWORD *)v2040 = 0i64;
                          v2077 -= 8;
                          v2040 += 8;
                          --v2080;
                        }
                        while ( v2080 );
                      }
                      for ( ; v2077; --v2077 )
                        *v2040++ = 0;
                      v2081 = *((_DWORD *)v2075 + 585);
                      *((_DWORD *)v2075 + 585) = v2079;
                      if ( v2079 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2075 + 109))(v2078);
                      }
                      else if ( (*((_DWORD *)v2075 + 612) & 0x10000000) != 0 || !v2079 )
                      {
                        (*((void (__fastcall **)(__int64))v2075 + 31))(v2078);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2075 + 69))(v2078 - 8, *(_QWORD *)(v2078 - 8));
                      }
                      *((_DWORD *)v2075 + 585) = v2081;
                    }
                    *((_DWORD *)v2075 + 612) &= ~4u;
                    v2067 = v3783;
                  }
                  v2082 = (ULONG_PTR)&v2075[v2071];
                  ++*((_DWORD *)v2075 + 515);
                  v2083 = &v2075[v2071];
                  v3788 = (ULONG_PTR)&v2075[v2071];
                  v2084 = 48;
                  v2085 = 6i64;
                  do
                  {
                    *v2083 = 0i64;
                    v2084 -= 8;
                    ++v2083;
                    --v2085;
                  }
                  while ( v2085 );
                  for ( ; v2084; --v2084 )
                  {
                    *(_BYTE *)v2083 = 0;
                    v2083 = (_QWORD *)((char *)v2083 + 1);
                  }
                  *(_DWORD *)v2082 = 8;
                  v2086 = v2074;
                  *(_QWORD *)(v2082 + 8) = v2074;
                  v2087 = (char *)v2074;
                  *(_DWORD *)(v2082 + 16) = v2067;
                  *((_DWORD *)v2075 + 522) += v2067;
                  v2088 = *((_DWORD *)v2075 + 517);
                  v2089 = *((_QWORD *)v2075 + 259);
                  v2090 = (unsigned __int64)v2074 + v2067;
                  if ( (unsigned __int64)v2074 < v2090 )
                  {
                    do
                    {
                      _mm_prefetchnta(v2087);
                      v2087 += 64;
                    }
                    while ( (unsigned __int64)v2087 < v2090 );
                  }
                  v2091 = v2067 >> 7;
                  v2092 = *((_QWORD *)v2075 + 259);
                  if ( v2091 )
                  {
                    do
                    {
                      v2093 = 8i64;
                      do
                      {
                        v2094 = v2086[1] ^ __ROL8__(*v2086 ^ v2092, v2088);
                        v2086 += 2;
                        v2092 = __ROL8__(v2094, v2088);
                        --v2093;
                      }
                      while ( v2093 );
                      v2095 = (__ROL8__(v2089 ^ ((char *)v2086 - (char *)v2074), 17) ^ v2089 ^ (unsigned __int64)((char *)v2086 - (char *)v2074))
                            * (unsigned __int128)0x7010008004002001ui64;
                      v4022 = *((_QWORD *)&v2095 + 1);
                      v2088 = (BYTE8(v2095) ^ (unsigned __int8)(v2095 ^ v2088)) & 0x3F;
                      if ( !v2088 )
                        LOBYTE(v2088) = 1;
                      --v2091;
                    }
                    while ( v2091 );
                    v2082 = v3788;
                  }
                  v2096 = v3783;
                  v2097 = v3783 & 0x7F;
                  if ( v2097 >= 8 )
                  {
                    v2098 = (v3783 & 0x7F) >> 3;
                    do
                    {
                      v2092 = __ROL8__(*v2086++ ^ v2092, v2088);
                      v2097 -= 8;
                      --v2098;
                    }
                    while ( v2098 );
                  }
                  for ( ; v2097; --v2097 )
                  {
                    v2099 = *(unsigned __int8 *)v2086;
                    v2086 = (_QWORD *)((char *)v2086 + 1);
                    v2092 = __ROL8__(v2099 ^ v2092, v2088);
                  }
                  for ( i36 = v2092; ; LODWORD(v2092) = i36 ^ v2092 )
                  {
                    i36 >>= 31;
                    if ( !i36 )
                      break;
                  }
                  v2101 = v3791;
                  v2102 = 26;
                  *(_DWORD *)(v2082 + 20) = v2092 & 0x7FFFFFFF;
                  v2103 = (_QWORD *)(v2082 + 48);
                  *((_DWORD *)v2075 + 522) += v2096;
                  v2040 = v2075;
                  v2104 = *((_QWORD *)v2075 + 223);
                  *(_QWORD *)(v2082 + 24) = v2068;
                  v2105 = 3i64;
                  *(_WORD *)(v2082 + 32) = v2101;
                  *(_WORD *)(v2082 + 34) = *(_WORD *)(v2068 + v2104 + *((_QWORD *)v2075 + 229));
                  v2106 = L"\\ObjectTypes\\";
                  do
                  {
                    v2102 -= 8;
                    *v2103 = *(_QWORD *)v2106;
                    v2106 += 4;
                    ++v2103;
                    --v2105;
                  }
                  while ( v2105 );
                  for ( ; v2102; --v2102 )
                  {
                    v2107 = *(_BYTE *)v2106;
                    v2106 = (const wchar_t *)((char *)v2106 + 1);
                    *(_BYTE *)v2103 = v2107;
                    v2103 = (_QWORD *)((char *)v2103 + 1);
                  }
                  v2108 = *(unsigned __int16 *)(v2069 + 8);
                  v2109 = (char *)(v2082 + 74);
                  v2110 = *(_QWORD **)(v2069 + 16);
                  if ( v2108 >= 8 )
                  {
                    v2111 = (unsigned __int64)*(unsigned __int16 *)(v2069 + 8) >> 3;
                    do
                    {
                      v2108 -= 8;
                      *(_QWORD *)v2109 = *v2110++;
                      v2109 += 8;
                      --v2111;
                    }
                    while ( v2111 );
                  }
                  if ( v2108 )
                  {
                    v2112 = v2109 - (char *)v2110;
                    do
                    {
                      *((_BYTE *)v2110 + v2112) = *(_BYTE *)v2110;
                      v2110 = (_QWORD *)((char *)v2110 + 1);
                      --v2108;
                    }
                    while ( v2108 );
                  }
                  if ( (*((_DWORD *)v2075 + 612) & 0x40000000) != 0 )
                  {
                    v2113 = *((unsigned int *)v2075 + 505);
                    v2114 = *(unsigned int *)(v2082 + 16);
                    v2115 = *(_QWORD **)(v2082 + 8);
                    v2116 = v2113 + 48;
                    if ( (unsigned int)(v2113 + 48) <= *((_DWORD *)v2075 + 647) )
                    {
                      *((_DWORD *)v2075 + 505) = v2116;
                    }
                    else
                    {
                      v2040 = (_BYTE *)sub_140B0F020(v2075, v2116, *((_DWORD *)v2075 + 585));
                      if ( !v2040 )
                        return 0;
                      v2117 = *((_DWORD *)v2075 + 612);
                      if ( (v2117 & 4) == 0 )
                      {
                        v2118 = *((_DWORD *)v2075 + 505);
                        v2119 = *((_QWORD *)v2075 + 249);
                        v2120 = (v2117 & 0x20000000) != 0 ? *((_DWORD *)v2075 + 585) : 0;
                        if ( v2118 >= 8 )
                        {
                          v2121 = (unsigned __int64)v2118 >> 3;
                          do
                          {
                            *(_QWORD *)v2075 = 0i64;
                            v2118 -= 8;
                            v2075 += 8;
                            --v2121;
                          }
                          while ( v2121 );
                        }
                        for ( ; v2118; --v2118 )
                          *v2075++ = 0;
                        v2122 = *((_DWORD *)v2040 + 585);
                        *((_DWORD *)v2040 + 585) = v2120;
                        if ( v2120 == 3 )
                        {
                          (*((void (__fastcall **)(__int64))v2040 + 109))(v2119);
                        }
                        else if ( (*((_DWORD *)v2040 + 612) & 0x10000000) != 0 || !v2120 )
                        {
                          (*((void (__fastcall **)(__int64))v2040 + 31))(v2119);
                        }
                        else
                        {
                          (*((void (__fastcall **)(__int64, _QWORD))v2040 + 69))(v2119 - 8, *(_QWORD *)(v2119 - 8));
                        }
                        *((_DWORD *)v2040 + 585) = v2122;
                      }
                      *((_DWORD *)v2040 + 612) &= ~4u;
                    }
                    v2123 = (ULONG_PTR)&v2040[v2113];
                    ++*((_DWORD *)v2040 + 515);
                    v2124 = (_QWORD *)v2123;
                    HalExtensionList = v2123;
                    v2125 = 48;
                    v2126 = 6i64;
                    do
                    {
                      *v2124 = 0i64;
                      v2125 -= 8;
                      ++v2124;
                      --v2126;
                    }
                    while ( v2126 );
                    for ( ; v2125; --v2125 )
                    {
                      *(_BYTE *)v2124 = 0;
                      v2124 = (_QWORD *)((char *)v2124 + 1);
                    }
                    *(_DWORD *)v2123 = 32;
                    *(_QWORD *)(v2123 + 8) = v2115;
                    if ( (_DWORD)v2114 )
                      sub_1403ED6CC(v2040, v2115, (unsigned int)v2114, v2123 + 24);
                    *(_DWORD *)(v2123 + 16) = v2114;
                    *((_DWORD *)v2040 + 522) += v2114;
                    v2127 = v2115;
                    v2128 = *((_DWORD *)v2040 + 517);
                    v2129 = (char *)v2115;
                    v2130 = *((_QWORD *)v2040 + 259);
                    if ( v2115 < (_QWORD *)((char *)v2115 + v2114) )
                    {
                      do
                      {
                        _mm_prefetchnta(v2129);
                        v2129 += 64;
                      }
                      while ( v2129 < (char *)v2115 + v2114 );
                    }
                    v2131 = *((_QWORD *)v2040 + 259);
                    v2132 = (unsigned int)v2114 >> 7;
                    if ( (unsigned int)v2114 >> 7 )
                    {
                      do
                      {
                        v2133 = 8i64;
                        do
                        {
                          v2134 = v2127[1] ^ __ROL8__(*v2127 ^ v2131, v2128);
                          v2127 += 2;
                          v2131 = __ROL8__(v2134, v2128);
                          --v2133;
                        }
                        while ( v2133 );
                        v2135 = (__ROL8__(v2130 ^ ((char *)v2127 - (char *)v2115), 17) ^ v2130 ^ (unsigned __int64)((char *)v2127 - (char *)v2115))
                              * (unsigned __int128)0x7010008004002001ui64;
                        v4023 = *((_QWORD *)&v2135 + 1);
                        v2128 = (BYTE8(v2135) ^ (unsigned __int8)(v2135 ^ v2128)) & 0x3F;
                        if ( !v2128 )
                          LOBYTE(v2128) = 1;
                        --v2132;
                      }
                      while ( v2132 );
                      v2123 = HalExtensionList;
                    }
                    v2136 = v2114 & 0x7F;
                    if ( v2136 >= 8 )
                    {
                      v2137 = (unsigned __int64)(v2114 & 0x7F) >> 3;
                      do
                      {
                        v2131 = __ROL8__(*v2127++ ^ v2131, v2128);
                        v2136 -= 8;
                        --v2137;
                      }
                      while ( v2137 );
                    }
                    for ( ; v2136; --v2136 )
                    {
                      v2138 = *(unsigned __int8 *)v2127;
                      v2127 = (_QWORD *)((char *)v2127 + 1);
                      v2131 = __ROL8__(v2138 ^ v2131, v2128);
                    }
                    for ( i37 = v2131; ; LODWORD(v2131) = i37 ^ v2131 )
                    {
                      i37 >>= 31;
                      if ( !i37 )
                        break;
                    }
                    *(_DWORD *)(v2123 + 20) = v2131 & 0x7FFFFFFF;
                    *((_DWORD *)v2040 + 522) += v2114;
                    *(_DWORD *)(v2123 + 40) = 1;
                  }
                  v2065 = (unsigned int)Src;
                  v2066 = v3784;
                  v2067 = v3783;
                }
              }
            }
          }
        }
        LODWORD(i35) = v3785 + 1;
        LODWORD(v3785) = i35;
      }
      while ( (unsigned int)i35 < v2065 );
    }
    v3981 = v2040;
    v2140 = *((unsigned int *)v2040 + 505);
    v2141 = v2140 + 48;
    if ( (unsigned int)(v2140 + 48) <= *((_DWORD *)v2040 + 647) )
    {
      v2142 = v2040;
      *((_DWORD *)v2040 + 505) = v2141;
    }
    else
    {
      v2142 = (_BYTE *)sub_140B0F020(v2040, v2141, *((_DWORD *)v2040 + 585));
      if ( !v2142 )
        return 0;
      v2143 = *((_DWORD *)v2040 + 612);
      if ( (v2143 & 4) == 0 )
      {
        v2144 = *((_DWORD *)v2040 + 505);
        v2145 = *((_QWORD *)v2040 + 249);
        v2146 = (v2143 & 0x20000000) != 0 ? *((_DWORD *)v2040 + 585) : 0;
        if ( v2144 >= 8 )
        {
          v2147 = (unsigned __int64)v2144 >> 3;
          do
          {
            *(_QWORD *)v2040 = 0i64;
            v2144 -= 8;
            v2040 += 8;
            --v2147;
          }
          while ( v2147 );
        }
        for ( ; v2144; --v2144 )
          *v2040++ = 0;
        v2148 = *((_DWORD *)v2142 + 585);
        *((_DWORD *)v2142 + 585) = v2146;
        if ( v2146 == 3 )
        {
          (*((void (__fastcall **)(__int64))v2142 + 109))(v2145);
        }
        else if ( (*((_DWORD *)v2142 + 612) & 0x10000000) != 0 || !v2146 )
        {
          (*((void (__fastcall **)(__int64))v2142 + 31))(v2145);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v2142 + 69))(v2145 - 8, *(_QWORD *)(v2145 - 8));
        }
        *((_DWORD *)v2142 + 585) = v2148;
      }
      *((_DWORD *)v2142 + 612) &= ~4u;
    }
    ++*((_DWORD *)v2142 + 515);
    v2149 = &v2142[v2140];
    v2150 = 48;
    v2151 = &v2142[v2140];
    v2152 = 6i64;
    do
    {
      *v2151 = 0i64;
      v2150 -= 8;
      ++v2151;
      --v2152;
    }
    while ( v2152 );
    for ( ; v2150; --v2150 )
    {
      *(_BYTE *)v2151 = 0;
      v2151 = (_QWORD *)((char *)v2151 + 1);
    }
    *(_DWORD *)v2149 = 39;
    *((_QWORD *)v2149 + 1) = 0i64;
    *((_DWORD *)v2149 + 4) = 0;
    v2153 = *((_QWORD *)v2142 + 259);
    for ( i38 = v2153; ; LODWORD(v2153) = i38 ^ v2153 )
    {
      i38 >>= 31;
      if ( !i38 )
        break;
    }
    v2155 = Size;
    *((_DWORD *)v2149 + 5) = v2153 & 0x7FFFFFFF;
    v2156 = v3800;
    *((_DWORD *)v2149 + 8) = v3800;
    *((_DWORD *)v2149 + 9) = v2155;
    *((_DWORD *)v2142 + 522) += v2155;
    v2157 = *((_DWORD *)v2142 + 517);
    v2158 = &v2142[v2156];
    v2159 = *((_QWORD *)v2142 + 259);
    v2160 = &v2142[v2156 + v2155];
    v2161 = v2158;
    for ( i39 = v2158; i39 < v2160; i39 += 64 )
      _mm_prefetchnta(i39);
    v2163 = *((_QWORD *)v2142 + 259);
    v2164 = (unsigned int)v2155 >> 7;
    if ( (unsigned int)v2155 >> 7 )
    {
      do
      {
        v2165 = 8i64;
        do
        {
          v2166 = v2161[1] ^ __ROL8__(*v2161 ^ v2163, v2157);
          v2161 += 2;
          v2163 = __ROL8__(v2166, v2157);
          --v2165;
        }
        while ( v2165 );
        v2167 = (__ROL8__(v2159 ^ ((char *)v2161 - v2158), 17) ^ v2159 ^ (unsigned __int64)((char *)v2161 - v2158))
              * (unsigned __int128)0x7010008004002001ui64;
        v4024 = *((_QWORD *)&v2167 + 1);
        v2157 = (BYTE8(v2167) ^ (unsigned __int8)(v2167 ^ v2157)) & 0x3F;
        if ( !v2157 )
          LOBYTE(v2157) = 1;
        --v2164;
      }
      while ( v2164 );
      LOBYTE(v2155) = Size;
    }
    v2168 = v2155 & 0x7F;
    if ( v2168 >= 8 )
    {
      v2169 = (unsigned __int64)v2168 >> 3;
      do
      {
        v2163 = __ROL8__(*v2161++ ^ v2163, v2157);
        v2168 -= 8;
        --v2169;
      }
      while ( v2169 );
    }
    for ( ; v2168; --v2168 )
    {
      v2170 = *(unsigned __int8 *)v2161;
      v2161 = (_QWORD *)((char *)v2161 + 1);
      v2163 = __ROL8__(v2170 ^ v2163, v2157);
    }
    *((_QWORD *)v2149 + 3) = v2163;
    v875 = (*((_DWORD *)v2142 + 612) & 0x8000000) == 0;
    v3981 = v2142;
    if ( v875 )
    {
      v2171 = *((unsigned int *)v2142 + 505);
      v2172 = *((unsigned int *)v2142 + 585);
      v2173 = 16 * *((_DWORD *)v2142 + 680) + (_DWORD)v2142 + 2728;
      v2174 = 16 * *((_DWORD *)v2142 + 681);
      v2175 = v2173;
      LODWORD(v3784) = v2174;
      v2176 = v2173 - ((_DWORD)v2142 + 2720);
      LODWORD(Src) = v2175 - (_DWORD)v2142;
      v2177 = v2171 + 48;
      if ( (unsigned int)(v2171 + 48) <= *((_DWORD *)v2142 + 647) )
      {
        v2178 = v2142;
        *((_DWORD *)v2142 + 505) = v2177;
      }
      else
      {
        v2178 = (_BYTE *)sub_140B0F020(v2142, v2177, v2172);
        if ( !v2178 )
          return 0;
        v2179 = *((_DWORD *)v2142 + 612);
        if ( (v2179 & 4) == 0 )
        {
          v2180 = *((_DWORD *)v2142 + 505);
          v2181 = *((_QWORD *)v2142 + 249);
          v2182 = (v2179 & 0x20000000) != 0 ? *((_DWORD *)v2142 + 585) : 0;
          if ( v2180 >= 8 )
          {
            v2183 = (unsigned __int64)v2180 >> 3;
            do
            {
              *(_QWORD *)v2142 = 0i64;
              v2180 -= 8;
              v2142 += 8;
              --v2183;
            }
            while ( v2183 );
          }
          for ( ; v2180; --v2180 )
            *v2142++ = 0;
          v2184 = *((_DWORD *)v2178 + 585);
          *((_DWORD *)v2178 + 585) = v2182;
          if ( v2182 == 3 )
          {
            (*((void (__fastcall **)(__int64))v2178 + 109))(v2181);
          }
          else if ( (*((_DWORD *)v2178 + 612) & 0x10000000) != 0 || !v2182 )
          {
            (*((void (__fastcall **)(__int64))v2178 + 31))(v2181);
          }
          else
          {
            (*((void (__fastcall **)(__int64, _QWORD))v2178 + 69))(v2181 - 8, *(_QWORD *)(v2181 - 8));
          }
          *((_DWORD *)v2178 + 585) = v2184;
        }
        *((_DWORD *)v2178 + 612) &= ~4u;
      }
      v2185 = (ULONG_PTR)&v2178[v2171];
      ++*((_DWORD *)v2178 + 515);
      v2186 = &v2178[v2171];
      HalExtensionList = (ULONG_PTR)&v2178[v2171];
      v2187 = 48;
      v2188 = 6i64;
      do
      {
        *v2186 = 0i64;
        v2187 -= 8;
        ++v2186;
        --v2188;
      }
      while ( v2188 );
      for ( ; v2187; --v2187 )
      {
        *(_BYTE *)v2186 = 0;
        v2186 = (_QWORD *)((char *)v2186 + 1);
      }
      *(_DWORD *)v2185 = 40;
      *(_QWORD *)(v2185 + 8) = 0i64;
      *(_DWORD *)(v2185 + 16) = 0;
      v2189 = *((_QWORD *)v2178 + 259);
      for ( i40 = v2189; ; LODWORD(v2189) = i40 ^ v2189 )
      {
        i40 >>= 31;
        if ( !i40 )
          break;
      }
      *(_DWORD *)(v2185 + 20) = v2189 & 0x7FFFFFFF;
      *(_DWORD *)(v2185 + 32) = 2720;
      v2191 = v2178 + 2720;
      *(_DWORD *)(v2185 + 36) = v2176;
      v2192 = v2178 + 2720;
      *((_DWORD *)v2178 + 522) += v2176;
      v2193 = *((_DWORD *)v2178 + 517);
      v2194 = *((_QWORD *)v2178 + 259);
      v2195 = (unsigned __int64)&v2178[v2176 + 2720];
      if ( (unsigned __int64)(v2178 + 2720) < v2195 )
      {
        do
        {
          _mm_prefetchnta(v2192);
          v2192 += 64;
        }
        while ( (unsigned __int64)v2192 < v2195 );
      }
      v2196 = *((_QWORD *)v2178 + 259);
      v2197 = v2176 >> 7;
      if ( v2176 >> 7 )
      {
        do
        {
          v2198 = 8i64;
          do
          {
            v2199 = v2191[1] ^ __ROL8__(*v2191 ^ v2196, v2193);
            v2191 += 2;
            v2196 = __ROL8__(v2199, v2193);
            --v2198;
          }
          while ( v2198 );
          v2200 = (__ROL8__(v2194 ^ ((char *)v2191 - (v2178 + 2720)), 17) ^ v2194 ^ (unsigned __int64)((char *)v2191 - (v2178 + 2720)))
                * (unsigned __int128)0x7010008004002001ui64;
          v4025 = *((_QWORD *)&v2200 + 1);
          v2193 = ((unsigned __int8)v2200 ^ (unsigned __int8)(BYTE8(v2200) ^ v2193)) & 0x3F;
          if ( !v2193 )
            LOBYTE(v2193) = 1;
          --v2197;
        }
        while ( v2197 );
        v2185 = HalExtensionList;
      }
      v2201 = v2176 & 0x7F;
      if ( v2201 >= 8 )
      {
        v2202 = (unsigned __int64)v2201 >> 3;
        do
        {
          v2196 = __ROL8__(*v2191++ ^ v2196, v2193);
          v2201 -= 8;
          --v2202;
        }
        while ( v2202 );
      }
      for ( ; v2201; --v2201 )
      {
        v2203 = *(unsigned __int8 *)v2191;
        v2191 = (_QWORD *)((char *)v2191 + 1);
        v2196 = __ROL8__(v2203 ^ v2196, v2193);
      }
      *(_QWORD *)(v2185 + 24) = v2196;
      v2204 = *((unsigned int *)v2178 + 505);
      v2205 = *((unsigned int *)v2178 + 585);
      v3981 = v2178;
      v2206 = v2204 + 48;
      if ( (unsigned int)(v2204 + 48) <= *((_DWORD *)v2178 + 647) )
      {
        v2207 = (__int64)v2178;
        *((_DWORD *)v2178 + 505) = v2206;
      }
      else
      {
        v2207 = sub_140B0F020(v2178, v2206, v2205);
        if ( !v2207 )
          return 0;
        v2208 = *((_DWORD *)v2178 + 612);
        if ( (v2208 & 4) == 0 )
        {
          v2209 = *((_DWORD *)v2178 + 505);
          v2210 = *((_QWORD *)v2178 + 249);
          v2211 = (v2208 & 0x20000000) != 0 ? *((_DWORD *)v2178 + 585) : 0;
          if ( v2209 >= 8 )
          {
            v2212 = (unsigned __int64)v2209 >> 3;
            do
            {
              *(_QWORD *)v2178 = 0i64;
              v2209 -= 8;
              v2178 += 8;
              --v2212;
            }
            while ( v2212 );
          }
          for ( ; v2209; --v2209 )
            *v2178++ = 0;
          v2213 = *(_DWORD *)(v2207 + 2340);
          *(_DWORD *)(v2207 + 2340) = v2211;
          if ( v2211 == 3 )
          {
            (*(void (__fastcall **)(__int64))(v2207 + 872))(v2210);
          }
          else if ( (*(_DWORD *)(v2207 + 2448) & 0x10000000) != 0 || !v2211 )
          {
            (*(void (__fastcall **)(__int64))(v2207 + 248))(v2210);
          }
          else
          {
            (*(void (__fastcall **)(__int64, _QWORD))(v2207 + 552))(v2210 - 8, *(_QWORD *)(v2210 - 8));
          }
          *(_DWORD *)(v2207 + 2340) = v2213;
        }
        *(_DWORD *)(v2207 + 2448) &= ~4u;
      }
      ++*(_DWORD *)(v2207 + 2060);
      v2214 = v2207 + v2204;
      v2215 = 48;
      v2216 = (_QWORD *)(v2207 + v2204);
      v2217 = 6i64;
      do
      {
        *v2216 = 0i64;
        v2215 -= 8;
        ++v2216;
        --v2217;
      }
      while ( v2217 );
      for ( ; v2215; --v2215 )
      {
        *(_BYTE *)v2216 = 0;
        v2216 = (_QWORD *)((char *)v2216 + 1);
      }
      *(_DWORD *)v2214 = 41;
      *(_QWORD *)(v2214 + 8) = 0i64;
      *(_DWORD *)(v2214 + 16) = 0;
      v2218 = *(_QWORD *)(v2207 + 2072);
      for ( i41 = v2218; ; LODWORD(v2218) = i41 ^ v2218 )
      {
        i41 >>= 31;
        if ( !i41 )
          break;
      }
      v2220 = (unsigned int)Src;
      *(_DWORD *)(v2214 + 20) = v2218 & 0x7FFFFFFF;
      *(_DWORD *)(v2214 + 32) = v2220;
      *(_DWORD *)(v2214 + 36) = v2174;
      *(_DWORD *)(v2207 + 2088) += v2174;
      v2221 = (_QWORD *)(v2207 + v2220);
      v2222 = *(_DWORD *)(v2207 + 2068);
      v2223 = v2221;
      v2224 = *(_QWORD *)(v2207 + 2072);
      v2225 = (char *)(v2207 + v2220);
      v2226 = (unsigned __int64)v2221 + v2174;
      if ( (unsigned __int64)v2221 < v2226 )
      {
        do
        {
          _mm_prefetchnta(v2225);
          v2225 += 64;
        }
        while ( (unsigned __int64)v2225 < v2226 );
      }
      v2227 = *(_QWORD *)(v2207 + 2072);
      v2228 = v2174 >> 7;
      if ( v2174 >> 7 )
      {
        do
        {
          v2229 = 8i64;
          do
          {
            v2230 = v2223[1] ^ __ROL8__(*v2223 ^ v2227, v2222);
            v2223 += 2;
            v2227 = __ROL8__(v2230, v2222);
            --v2229;
          }
          while ( v2229 );
          v2231 = (__ROL8__(v2224 ^ ((char *)v2223 - (char *)v2221), 17) ^ v2224 ^ (unsigned __int64)((char *)v2223 - (char *)v2221))
                * (unsigned __int128)0x7010008004002001ui64;
          v4026 = *((_QWORD *)&v2231 + 1);
          v2222 = ((unsigned __int8)v2231 ^ (unsigned __int8)(BYTE8(v2231) ^ v2222)) & 0x3F;
          if ( !v2222 )
            LOBYTE(v2222) = 1;
          --v2228;
        }
        while ( v2228 );
        LOBYTE(v2174) = v3784;
      }
      v2232 = v2174 & 0x7F;
      if ( v2232 >= 8 )
      {
        v2233 = (unsigned __int64)v2232 >> 3;
        do
        {
          v2227 = __ROL8__(*v2223++ ^ v2227, v2222);
          v2232 -= 8;
          --v2233;
        }
        while ( v2233 );
      }
      for ( ; v2232; --v2232 )
      {
        v2234 = *(unsigned __int8 *)v2223;
        v2223 = (_QWORD *)((char *)v2223 + 1);
        v2227 = __ROL8__(v2234 ^ v2227, v2222);
      }
      *(_QWORD *)(v2214 + 24) = v2227;
      v3981 = (_BYTE *)v2207;
    }
    HalExtensionList = (ULONG_PTR)v3981;
    v2235 = (unsigned int)(((*((_DWORD *)v3981 + 612) >> 30) & 1) == 0) + 6;
    if ( ((int (__fastcall *)(__int64, __int64, __int64 *, char *))off_140C020E8[0])(37i64, 16i64, &v4123, v3849) < 0 )
      v4124 = 0i64;
    else
      v2235 = (unsigned int)(v4124 + v2235);
    LODWORD(Src) = v3836 & 6;
    if ( (v3836 & 6) == 0 )
    {
      if ( PspPicoProviderRanges )
        LODWORD(v2235) = *(_DWORD *)(PspPicoProviderRanges + 8) + v2235;
      if ( __27 )
        LODWORD(v2235) = *(_DWORD *)(__27 + 8) + v2235;
      v2235 = (unsigned int)(qword_140C064E0 + v2235);
    }

    v3788 = ExAllocatePool2(64i64, 8 * v2235, tag);
    v2248 = (_QWORD *)v3788;
    if ( !v3788 )
      return 0;
    v2261 = (_DWORD *)ExAllocatePool2(64i64, 4 * v2235, tag);
    v3787 = (ULONG_PTR)v2261;
    v2262 = v2261;
    if ( !v2261 )
    {
      v2263 = (void *)v3788;
LABEL_3247:
      ExFreePool(v2263);
      return 0;
    }
    v2264 = dword_140D815C8;
    v2265 = 1;
    *(_QWORD *)v3788 = (unsigned int)dword_140D815C8 - 0x88000000000i64;
    *v2261 = 4096 - v2264;
    LODWORD(v3784) = v3836 & 2;
    if ( (v3836 & 2) == 0 )
    {
      v2265 = 2;
      v2248[1] = &InitSafeBootMode;
      v2261[1] = 4;
    }
    v2266 = (int)Src;
    v2267 = v2265;
    v2268 = v2265 + 1;
    v2248[v2267] = &RtlpUnwindHistoryTable;
    v2262[v2267] = 216;
    v2248[v2268] = &xmmword_140E00030;
    v2262[v2268] = 24;
    v2269 = (unsigned int)(v2268 + 1);
    LODWORD(v3783) = v2269;
    if ( v2266 )
    {
      v4032[0] = 0i64;
      v4031 = 0i64;
    }
    else
    {
      MmQueryApiSetSchema(v4032, &v4031);
      v2266 = (int)Src;
      v2248[v2269] = v4032[0];
      v2262[v2269] = 8;
      v2270 = (unsigned int)(v2269 + 1);
      v2248[v2270] = v4031;
      v2271 = HalExtensionList;
      v2262[v2270] = 8;
      v2269 = (unsigned int)(v2270 + 1);
      LODWORD(v3783) = v2269;
      if ( (*(_DWORD *)(v2271 + 2448) & 0x40000000) == 0 )
      {
        v2248[v2269] = *(_QWORD *)v4032[0];
        v2262[v2269] = *v4031;
        v2269 = (unsigned int)(v2269 + 1);
        LODWORD(v3783) = v2269;
      }
    }
    v2272 = 0;
    if ( v4124 )
    {
      v2273 = 0i64;
      do
      {
        v2274 = 2 * v2273;
        ++v2272;
        v2248[v2269] = *(_QWORD *)(v4123 + 8 * v2274);
        v2262[v2269] = *(_DWORD *)(v4123 + 8 * v2274 + 8);
        v2269 = (unsigned int)(v2269 + 1);
        v2273 = v2272;
      }
      while ( v2272 < v4124 );
      LODWORD(v3783) = v2269;
    }
    if ( !v2266 )
    {
      v2275 = (_QWORD *)PspPicoProviderRanges;
      if ( PspPicoProviderRanges )
      {
        v2276 = 0;
        if ( *(_QWORD *)(PspPicoProviderRanges + 8) )
        {
          v2277 = 0i64;
          do
          {
            v2278 = 2 * v2277;
            ++v2276;
            v2248[v2269] = *(_QWORD *)(*v2275 + 8 * v2278);
            v2262[v2269] = *(_DWORD *)(*(_QWORD *)PspPicoProviderRanges + 8 * v2278 + 8);
            v2269 = (unsigned int)(v2269 + 1);
            v2275 = (_QWORD *)PspPicoProviderRanges;
            v2277 = v2276;
          }
          while ( (unsigned __int64)v2276 < *(_QWORD *)(PspPicoProviderRanges + 8) );
          LODWORD(v3783) = v2269;
        }
      }
      v2279 = (_QWORD *)__27;
      if ( __27 )
      {
        v2280 = 0;
        if ( *(_QWORD *)(__27 + 8) )
        {
          v2281 = 0i64;
          do
          {
            v2282 = 2 * v2281;
            ++v2280;
            v2248[v2269] = *(_QWORD *)(*v2279 + 8 * v2282);
            v2262[v2269] = *(_DWORD *)(*(_QWORD *)__27 + 8 * v2282 + 8);
            v2269 = (unsigned int)(v2269 + 1);
            v2279 = (_QWORD *)__27;
            v2281 = v2280;
          }
          while ( (unsigned __int64)v2280 < *(_QWORD *)(__27 + 8) );
          LODWORD(v3783) = v2269;
        }
      }
      v2283 = 0;
      if ( qword_140C064E0 )
      {
        v2284 = 0i64;
        do
        {
          v2285 = 2 * v2284;
          ++v2283;
          v2248[v2269] = PspKernelRanges[v2285];
          v2262[v2269] = PspKernelRanges[v2285 + 1];
          v2269 = (unsigned int)(v2269 + 1);
          v2284 = v2283;
        }
        while ( v2283 < (unsigned __int64)qword_140C064E0 );
        LODWORD(v3783) = v2269;
      }
    }
    v2286 = v3981;
    if ( (*(_BYTE *)((*((unsigned int *)v3981 + 599) ^ 0xBC2A27DBi64) - 0x88000000000i64) & 2) != 0 )
      *((_DWORD *)v3981 + 505) += 4096;
    v2288 = 32;
    v2289 = *((unsigned int *)v2286 + 505);
    v2290 = *((unsigned int *)v2286 + 585);
    LODWORD(v3785) = *((_DWORD *)v2286 + 526);
    v2287 = v3785;
    if ( (_DWORD)v3785 != 7 )
      v2288 = 0;
    v2291 = v2289 + 48 * v2269;
    LODWORD(v3791) = v2288;
    if ( v2291 <= *((_DWORD *)v2286 + 647) )
    {
      v2292 = v2286;
      v3786 = (unsigned __int64)v2286;
      *((_DWORD *)v2286 + 505) = v2291;
    }
    else
    {
      v2292 = (_BYTE *)sub_140B0F020(v2286, v2291, v2290);
      v3786 = (unsigned __int64)v2292;
      if ( !v2292 )
      {
        v2292 = 0i64;
        goto LABEL_3326;
      }
      v2293 = *(_DWORD *)(HalExtensionList + 2448);
      if ( (v2293 & 4) == 0 )
      {
        v2294 = *((_DWORD *)v2286 + 505);
        v2295 = *((_QWORD *)v2286 + 249);
        v2296 = (v2293 & 0x20000000) != 0 ? *((_DWORD *)v2286 + 585) : 0;
        if ( v2294 >= 8 )
        {
          v2297 = (unsigned __int64)v2294 >> 3;
          do
          {
            *(_QWORD *)v2286 = 0i64;
            v2294 -= 8;
            v2286 += 8;
            --v2297;
          }
          while ( v2297 );
        }
        for ( ; v2294; --v2294 )
          *v2286++ = 0;
        v2298 = *((_DWORD *)v2292 + 585);
        *((_DWORD *)v2292 + 585) = v2296;
        if ( v2296 == 3 )
        {
          (*((void (__fastcall **)(__int64))v2292 + 109))(v2295);
        }
        else if ( (*((_DWORD *)v2292 + 612) & 0x10000000) != 0 || !v2296 )
        {
          (*((void (__fastcall **)(__int64))v2292 + 31))(v2295);
        }
        else
        {
          (*((void (__fastcall **)(__int64, _QWORD))v2292 + 69))(v2295 - 8, *(_QWORD *)(v2295 - 8));
        }
        *((_DWORD *)v2292 + 585) = v2298;
      }
      *((_DWORD *)v2292 + 612) &= ~4u;
      v2288 = v3791;
      v2287 = v3785;
    }
    *((_DWORD *)v2292 + 515) += v2269;
    v2299 = &v2292[v2289];
    v2300 = (ULONG_PTR)&v2292[v2289];
    HalExtensionList = (ULONG_PTR)&v2292[v2289];
    if ( (_DWORD)v2269 )
    {
      v2301 = v2248;
      v3794 = (unsigned int)v2269;
      v2302 = v2262;
      v3790 = (__int64)v2262;
      do
      {
        v2303 = (unsigned int)*v2302;
        v2304 = 48;
        v2305 = (_QWORD *)*v2301;
        v2306 = v2299;
        LODWORD(v3793) = *v2302;
        v2307 = 6i64;
        do
        {
          *v2306 = 0i64;
          v2304 -= 8;
          ++v2306;
          --v2307;
        }
        while ( v2307 );
        for ( ; v2304; --v2304 )
        {
          *(_BYTE *)v2306 = 0;
          v2306 = (_QWORD *)((char *)v2306 + 1);
        }
        *(_DWORD *)v2299 = v2288;
        *((_QWORD *)v2299 + 1) = v2305;
        if ( v2287 == 7 && (_DWORD)v2303 )
          sub_1403ED6CC(v2292, v2305, (unsigned int)v2303, v2299 + 24);
        *((_DWORD *)v2299 + 4) = v2303;
        *((_DWORD *)v2292 + 522) += v2303;
        v2308 = v2305;
        v2309 = *((_DWORD *)v2292 + 517);
        v2310 = (char *)v2305;
        v2311 = *((_QWORD *)v2292 + 259);
        if ( v2305 < (_QWORD *)((char *)v2305 + v2303) )
        {
          do
          {
            _mm_prefetchnta(v2310);
            v2310 += 64;
          }
          while ( v2310 < (char *)v2305 + v2303 );
        }
        v2312 = *((_QWORD *)v2292 + 259);
        v2313 = (unsigned int)v2303 >> 7;
        if ( (unsigned int)v2303 >> 7 )
        {
          do
          {
            v2314 = 8i64;
            do
            {
              v2315 = v2308[1] ^ __ROL8__(*v2308 ^ v2312, v2309);
              v2308 += 2;
              v2312 = __ROL8__(v2315, v2309);
              --v2314;
            }
            while ( v2314 );
            v2316 = (__ROL8__(v2311 ^ ((char *)v2308 - (char *)v2305), 17) ^ v2311 ^ (unsigned __int64)((char *)v2308 - (char *)v2305))
                  * (unsigned __int128)0x7010008004002001ui64;
            v4032[1] = *((_QWORD *)&v2316 + 1);
            v2309 = ((unsigned __int8)v2316 ^ (unsigned __int8)(BYTE8(v2316) ^ v2309)) & 0x3F;
            if ( !v2309 )
              LOBYTE(v2309) = 1;
            --v2313;
          }
          while ( v2313 );
          v2292 = (_BYTE *)v3786;
          LODWORD(v2303) = v3793;
          v2302 = (_DWORD *)v3790;
        }
        v2317 = v2303 & 0x7F;
        if ( v2317 >= 8 )
        {
          v2318 = (unsigned __int64)(v2303 & 0x7F) >> 3;
          do
          {
            v2312 = __ROL8__(*v2308++ ^ v2312, v2309);
            v2317 -= 8;
            --v2318;
          }
          while ( v2318 );
        }
        for ( ; v2317; --v2317 )
        {
          v2319 = *(unsigned __int8 *)v2308;
          v2308 = (_QWORD *)((char *)v2308 + 1);
          v2312 = __ROL8__(v2319 ^ v2312, v2309);
        }
        for ( i42 = v2312 >> 31; i42; i42 >>= 31 )
          LODWORD(v2312) = i42 ^ v2312;
        v2288 = v3791;
        v2287 = v3785;
        ++v2302;
        *((_DWORD *)v2299 + 5) = v2312 & 0x7FFFFFFF;
        ++v2301;
        *((_DWORD *)v2292 + 522) += v2303;
        v2299 += 48;
        v875 = v3794-- == 1;
        v3790 = (__int64)v2302;
      }
      while ( !v875 );
      LODWORD(v2269) = v3783;
      v2262 = (_DWORD *)v3787;
      v2248 = (_QWORD *)v3788;
      v2300 = HalExtensionList;
    }
    if ( (_DWORD)v3785 == 7 && (_DWORD)v2269 )
    {
      do
      {
        *(_DWORD *)(v2300 + 40) |= 1u;
        v2300 += 48i64;
        LODWORD(v2269) = v2269 - 1;
      }
      while ( (_DWORD)v2269 );
    }
LABEL_3326:
    v3981 = v2292;
    ExFreePool(v2262);
    ExFreePool(v2248);
    if ( !v2292 )
      return 0;
    if ( (*((_DWORD *)v2292 + 612) & 0x40000000) != 0 && v4032[0] )
    {
      v2321 = 32;
      v2322 = *((_DWORD *)v2292 + 526);
      v2323 = *((unsigned int *)v2292 + 505);
      v2324 = *(_QWORD **)v4032[0];
      v2325 = (unsigned int)*v4031;
      v2326 = *((unsigned int *)v2292 + 585);
      if ( v2322 != 7 )
        v2321 = 0;
      v2327 = v2323 + 48;
      LODWORD(v3783) = *((_DWORD *)v2292 + 526);
      LODWORD(v3785) = v2321;
      if ( (unsigned int)(v2323 + 48) <= *((_DWORD *)v2292 + 647) )
      {
        v2328 = (__int64)v2292;
        *((_DWORD *)v2292 + 505) = v2327;
      }
      else
      {
        v2328 = sub_140B0F020(v2292, v2327, v2326);
        if ( !v2328 )
          return 0;
        v2329 = *((_DWORD *)v2292 + 612);
        if ( (v2329 & 4) == 0 )
        {
          v2330 = *((_DWORD *)v2292 + 505);
          v2331 = *((_QWORD *)v2292 + 249);
          v2332 = (v2329 & 0x20000000) != 0 ? *((_DWORD *)v2292 + 585) : 0;
          if ( v2330 >= 8 )
          {
            v2333 = (unsigned __int64)v2330 >> 3;
            do
            {
              *(_QWORD *)v2292 = 0i64;
              v2330 -= 8;
              v2292 += 8;
              --v2333;
            }
            while ( v2333 );
          }
          for ( ; v2330; --v2330 )
            *v2292++ = 0;
          v2334 = *(_DWORD *)(v2328 + 2340);
          *(_DWORD *)(v2328 + 2340) = v2332;
          if ( v2332 == 3 )
          {
            (*(void (__fastcall **)(__int64))(v2328 + 872))(v2331);
          }
          else if ( (*(_DWORD *)(v2328 + 2448) & 0x10000000) != 0 || !v2332 )
          {
            (*(void (__fastcall **)(__int64))(v2328 + 248))(v2331);
          }
          else
          {
            (*(void (__fastcall **)(__int64, _QWORD))(v2328 + 552))(v2331 - 8, *(_QWORD *)(v2331 - 8));
          }
          v2321 = v3785;
          *(_DWORD *)(v2328 + 2340) = v2334;
        }
        *(_DWORD *)(v2328 + 2448) &= ~4u;
        v2322 = v3783;
      }
      v2335 = v2328 + v2323;
      ++*(_DWORD *)(v2328 + 2060);
      v2336 = (_QWORD *)v2335;
      HalExtensionList = v2335;
      v2337 = 48;
      v2338 = 6i64;
      do
      {
        *v2336 = 0i64;
        v2337 -= 8;
        ++v2336;
        --v2338;
      }
      while ( v2338 );
      for ( ; v2337; --v2337 )
      {
        *(_BYTE *)v2336 = 0;
        v2336 = (_QWORD *)((char *)v2336 + 1);
      }
      *(_DWORD *)v2335 = v2321;
      *(_QWORD *)(v2335 + 8) = v2324;
      if ( v2322 == 7 && (_DWORD)v2325 )
        sub_1403ED6CC(v2328, v2324, (unsigned int)v2325, v2335 + 24);
      *(_DWORD *)(v2335 + 16) = v2325;
      *(_DWORD *)(v2328 + 2088) += v2325;
      v2339 = v2324;
      v2340 = *(_DWORD *)(v2328 + 2068);
      v2341 = (char *)v2324;
      v2342 = *(_QWORD *)(v2328 + 2072);
      if ( v2324 < (_QWORD *)((char *)v2324 + v2325) )
      {
        do
        {
          _mm_prefetchnta(v2341);
          v2341 += 64;
        }
        while ( v2341 < (char *)v2324 + v2325 );
      }
      v2343 = *(_QWORD *)(v2328 + 2072);
      v2344 = (unsigned int)v2325 >> 7;
      if ( (unsigned int)v2325 >> 7 )
      {
        do
        {
          v2345 = 8i64;
          do
          {
            v2346 = v2339[1] ^ __ROL8__(*v2339 ^ v2343, v2340);
            v2339 += 2;
            v2343 = __ROL8__(v2346, v2340);
            --v2345;
          }
          while ( v2345 );
          v2347 = __ROL8__(v2342 ^ ((char *)v2339 - (char *)v2324), 17) ^ v2342 ^ ((char *)v2339 - (char *)v2324);
          v4033 = (v2347 * (unsigned __int128)0x7010008004002001ui64) >> 64;
          v2340 = ((unsigned __int8)(v2347 ^ v4033) ^ (unsigned __int8)v2340) & 0x3F;
          if ( !v2340 )
            LOBYTE(v2340) = 1;
          --v2344;
        }
        while ( v2344 );
        v2335 = HalExtensionList;
      }
      v2348 = v2325 & 0x7F;
      if ( v2348 >= 8 )
      {
        v2349 = (unsigned __int64)(v2325 & 0x7F) >> 3;
        do
        {
          v2343 = __ROL8__(*v2339++ ^ v2343, v2340);
          v2348 -= 8;
          --v2349;
        }
        while ( v2349 );
      }
      for ( ; v2348; --v2348 )
      {
        v2350 = *(unsigned __int8 *)v2339;
        v2339 = (_QWORD *)((char *)v2339 + 1);
        v2343 = __ROL8__(v2350 ^ v2343, v2340);
      }
      for ( i43 = v2343; ; LODWORD(v2343) = i43 ^ v2343 )
      {
        i43 >>= 31;
        if ( !i43 )
          break;
      }
      v3981 = (_BYTE *)v2328;
      *(_DWORD *)(v2335 + 20) = v2343 & 0x7FFFFFFF;
      v2292 = (_BYTE *)v2328;
      *(_DWORD *)(v2328 + 2088) += v2325;
    }
    _disable();
    if ( !(_BYTE)KdDebuggerNotPresent )
    {
      while ( 1 )
        ;
    }
    _enable();
    v4125[0] = 8;
    v4175 = &HvlpHypercallCodeVa;
    LODWORD(v3783) = -1;
    v2352 = 1;
    if ( HvlpHypercallCodeVa )
    {
      if ( *((_DWORD *)v2292 + 526) != 7
        && (*((int *)v2292 + 612) < 0 || (unsigned __int8)HvlIsHypercallOverlayLocked()) )
      {
LABEL_3390:
        v2360 = *((_DWORD *)v2292 + 526);
        v2361 = *((unsigned int *)v2292 + 505);
        LODWORD(v2362) = 32;
        v2363 = *((unsigned int *)v2292 + 585);
        v2364 = v2352;
        v2365 = v2352 + 1;
        LODWORD(v3785) = v2365;
        LODWORD(v3791) = v2360;
        (&v4175)[v2364] = (PVOID *)&HvlpVsmVtlCallVa;
        v4125[v2364] = 8;
        if ( v2360 != 7 )
          LODWORD(v2362) = 0;
        v2366 = v2361 + 48 * v2365;
        LODWORD(v3793) = v2362;
        if ( v2366 <= *((_DWORD *)v2292 + 647) )
        {
          v2367 = v2292;
          HalExtensionList = (ULONG_PTR)v2292;
          *((_DWORD *)v2292 + 505) = v2366;
        }
        else
        {
          HalExtensionList = sub_140B0F020(v2292, v2366, v2363);
          v2367 = (_BYTE *)HalExtensionList;
          if ( !HalExtensionList )
            return 0;
          v2368 = *((_DWORD *)v2292 + 612);
          if ( (v2368 & 4) == 0 )
          {
            v2369 = *((_DWORD *)v2292 + 505);
            v2370 = *((_QWORD *)v2292 + 249);
            v2371 = (v2368 & 0x20000000) != 0 ? *((_DWORD *)v2292 + 585) : 0;
            if ( v2369 >= 8 )
            {
              v2372 = (unsigned __int64)v2369 >> 3;
              do
              {
                *(_QWORD *)v2292 = 0i64;
                v2369 -= 8;
                v2292 += 8;
                --v2372;
              }
              while ( v2372 );
            }
            for ( ; v2369; --v2369 )
              *v2292++ = 0;
            v2373 = *((_DWORD *)v2367 + 585);
            *((_DWORD *)v2367 + 585) = v2371;
            if ( v2371 == 3 )
            {
              (*((void (__fastcall **)(__int64))v2367 + 109))(v2370);
            }
            else if ( (*((_DWORD *)v2367 + 612) & 0x10000000) != 0 || !v2371 )
            {
              (*((void (__fastcall **)(__int64))v2367 + 31))(v2370);
            }
            else
            {
              (*((void (__fastcall **)(__int64, _QWORD))v2367 + 69))(v2370 - 8, *(_QWORD *)(v2370 - 8));
            }
            v2365 = v3785;
            *((_DWORD *)v2367 + 585) = v2373;
          }
          *((_DWORD *)v2367 + 612) &= ~4u;
          LODWORD(v2362) = v3793;
          v2360 = v3791;
        }
        *((_DWORD *)v2367 + 515) += v2365;
        v2374 = (__int64 *)&v4175;
        v2375 = (unsigned __int64)&v2367[v2361];
        v3788 = (ULONG_PTR)&v4175;
        v2376 = v4125;
        v3787 = v2365;
        v3786 = v2375;
        do
        {
          v2377 = (unsigned int)*v2376;
          v2378 = 48;
          v2379 = (_QWORD *)*v2374;
          v2380 = (_QWORD *)v2375;
          LODWORD(v3799) = *v2376;
          v2381 = 6i64;
          do
          {
            *v2380 = 0i64;
            v2378 -= 8;
            ++v2380;
            --v2381;
          }
          while ( v2381 );
          for ( ; v2378; --v2378 )
          {
            *(_BYTE *)v2380 = 0;
            v2380 = (_QWORD *)((char *)v2380 + 1);
          }
          *(_DWORD *)v2375 = v2362;
          *(_QWORD *)(v2375 + 8) = v2379;
          if ( v2360 == 7 && (_DWORD)v2377 )
          {
            sub_1403ED6CC(v2367, v2379, (unsigned int)v2377, v2375 + 24);
            v2374 = (__int64 *)v3788;
          }
          *(_DWORD *)(v2375 + 16) = v2377;
          v2382 = (unsigned __int64)v2379 + v2377;
          *((_DWORD *)v2367 + 522) += v2377;
          v2383 = v2379;
          v2384 = *((_DWORD *)v2367 + 517);
          v2385 = (char *)v2379;
          v2386 = *((_QWORD *)v2367 + 259);
          if ( v2379 < (_QWORD *)((char *)v2379 + v2377) )
          {
            do
            {
              _mm_prefetchnta(v2385);
              v2385 += 64;
            }
            while ( (unsigned __int64)v2385 < v2382 );
          }
          v2387 = *((_QWORD *)v2367 + 259);
          v2388 = (unsigned int)v2377 >> 7;
          if ( (unsigned int)v2377 >> 7 )
          {
            do
            {
              v2389 = 8i64;
              do
              {
                v2390 = v2383[1] ^ __ROL8__(*v2383 ^ v2387, v2384);
                v2383 += 2;
                v2387 = __ROL8__(v2390, v2384);
                --v2389;
              }
              while ( v2389 );
              v2382 = __ROL8__(v2386 ^ ((char *)v2383 - (char *)v2379), 17) ^ v2386 ^ ((char *)v2383 - (char *)v2379);
              v4034 = (v2382 * (unsigned __int128)0x7010008004002001ui64) >> 64;
              v2384 = ((unsigned __int8)v2382 ^ (unsigned __int8)(v4034 ^ v2384)) & 0x3F;
              if ( !v2384 )
                v2384 = 1;
              --v2388;
            }
            while ( v2388 );
            v2367 = (_BYTE *)HalExtensionList;
            LODWORD(v2377) = v3799;
            v2374 = (__int64 *)v3788;
          }
          v2391 = v2377 & 0x7F;
          if ( v2391 >= 8 )
          {
            v2392 = (unsigned __int64)(v2377 & 0x7F) >> 3;
            do
            {
              v2382 = v2384;
              v2387 = __ROL8__(*v2383++ ^ v2387, v2384);
              v2391 -= 8;
              --v2392;
            }
            while ( v2392 );
          }
          for ( ; v2391; --v2391 )
          {
            v2393 = *(unsigned __int8 *)v2383;
            v2382 = v2384;
            v2383 = (_QWORD *)((char *)v2383 + 1);
            v2387 = __ROL8__(v2393 ^ v2387, v2384);
          }
          v2394 = v2387 >> 31;
          v2395 = 0i64;
          while ( v2394 )
          {
            LODWORD(v2387) = v2394 ^ v2387;
            v2394 >>= 31;
          }
          v2362 = (unsigned int)v3793;
          v2360 = v3791;
          *(_DWORD *)(v2375 + 20) = v2387 & 0x7FFFFFFF;
          ++v2374;
          *((_DWORD *)v2367 + 522) += v2377;
          v2375 += 48i64;
          ++v2376;
          v3788 = (ULONG_PTR)v2374;
          --v3787;
        }
        while ( v3787 );
        v2396 = v3786;
        if ( v2360 == 7 )
        {
          LODWORD(v2382) = v3785;
          v2397 = v3786;
          do
          {
            *(_DWORD *)(v2397 + 40) |= 1u;
            v2397 += 48i64;
            v875 = (_DWORD)v2382 == 1;
            v2382 = (unsigned int)(v2382 - 1);
          }
          while ( !v875 );
        }
        if ( (_DWORD)v3783 != -1 )
        {
          v2382 = 6i64 * (unsigned int)v3783;
          if ( *(_DWORD *)(v2396 + 48i64 * (unsigned int)v3783) == 32 )
            *(_DWORD *)(v2396 + 48i64 * (unsigned int)v3783 + 40) |= 4u;
        }
        v3981 = v2367;
        _disable();
        LODWORD(i46) = 0;
        if ( !(_BYTE)KdDebuggerNotPresent )
        {
          while ( 1 )
            ;
        }
        _enable();
        if ( (_DWORD)v3784 )
          goto LABEL_3545;
        v2399 = 7;
        LODWORD(v3784) = v3836 & 4;
        if ( (v3836 & 4) == 0 )
          v2399 = SeCiStateElementCount + 7;
        v2412 = v2399;
        HalExtensionList = ExAllocatePool2(64i64, 8i64 * v2399, tag);
        v2413 = (_QWORD *)HalExtensionList;
        if ( !HalExtensionList )
          return 0;
        v2426 = (_DWORD *)ExAllocatePool2(64i64, 4 * v2412, tag);
        v3788 = (ULONG_PTR)v2426;
        v2427 = v2426;
        if ( !v2426 )
        {
          v2263 = (void *)HalExtensionList;
          goto LABEL_3247;
        }
        *(_QWORD *)HalExtensionList = &SeCiCallbacks;
        v2428 = 4;
        *v2426 = dword_140D815D0;
        v2413[1] = &SeMsMinTCBList;
        v2426[1] = dword_140D81600;
        v2413[2] = RtlProtectedAccess;
        v2426[2] = dword_140D81608;
        v2413[3] = &SeProtectedMapping;
        v2426[3] = dword_140D81610;
        if ( !(_DWORD)v3784 )
        {
          v2413[4] = SeSecureBootPolicyBlobHeader;
          v2428 = 7;
          v2426[4] = SeSecureBootPolicyBlobHeaderSize;
          v2413[5] = &SeILSigningPolicy;
          v2426[5] = 1;
          v2413[6] = &SeCiDebugOptions;
          v2426[6] = 4;
          for ( i44 = 0; i44 < SeCiStateElementCount; v2426[v2430] = *(_DWORD *)(SeCiStateElements + 8 * v2431 + 8) )
          {
            v2430 = v2428++;
            v2431 = i44++;
            v2431 *= 2i64;
            v2413[v2430] = *(_QWORD *)(SeCiStateElements + 8 * v2431);
          }
        }
        v2432 = *((_DWORD *)v2367 + 526);
        v2433 = 32;
        v2434 = *((_DWORD *)v2367 + 505);
        v2435 = *((unsigned int *)v2367 + 585);
        if ( v2432 != 7 )
          v2433 = 0;
        LODWORD(v3784) = *((_DWORD *)v2367 + 526);
        LODWORD(v3783) = v2433;
        v2436 = v2434 + 48 * v2428;
        LODWORD(v3785) = v2434;
        if ( v2436 <= *((_DWORD *)v2367 + 647) )
        {
          v2437 = (__int64)v2367;
          v3787 = (ULONG_PTR)v2367;
          *((_DWORD *)v2367 + 505) = v2436;
        }
        else
        {
          v2437 = sub_140B0F020(v2367, v2436, v2435);
          v3787 = v2437;
          if ( !v2437 )
          {
            v2367 = 0i64;
LABEL_3543:
            ExFreePool(v2427);
            ExFreePool(v2413);
            LODWORD(i46) = 0;
            if ( !v2367 )
              return 0;
            v3981 = v2367;
LABEL_3545:
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            if ( !(_DWORD)Src )
            {
              if ( (unsigned int)SeMinTcbLowering(v2382, v2396, v2395, v2362) )
              {
                LODWORD(i46) = 0;
              }
              else
              {
                _disable();
                if ( !(_BYTE)KdDebuggerNotPresent )
                {
                  while ( 1 )
                    ;
                }
                _enable();
                v2464 = *((unsigned int *)v2367 + 505);
                v2465 = v2464 + 48;
                if ( (unsigned int)(v2464 + 48) <= *((_DWORD *)v2367 + 647) )
                {
                  v2466 = v2367;
                  *((_DWORD *)v2367 + 505) = v2465;
                }
                else
                {
                  v2466 = (_BYTE *)sub_140B0F020(v2367, v2465, *((_DWORD *)v2367 + 585));
                  if ( !v2466 )
                    return 0;
                  v2467 = *((_DWORD *)v2367 + 612);
                  if ( (v2467 & 4) == 0 )
                  {
                    v2468 = *((_DWORD *)v2367 + 505);
                    v2469 = *((_QWORD *)v2367 + 249);
                    v2470 = (v2467 & 0x20000000) != 0 ? *((_DWORD *)v2367 + 585) : 0;
                    if ( v2468 >= 8 )
                    {
                      v2471 = (unsigned __int64)v2468 >> 3;
                      do
                      {
                        *(_QWORD *)v2367 = 0i64;
                        v2468 -= 8;
                        v2367 += 8;
                        --v2471;
                      }
                      while ( v2471 );
                    }
                    for ( ; v2468; --v2468 )
                      *v2367++ = 0;
                    v2472 = *((_DWORD *)v2466 + 585);
                    *((_DWORD *)v2466 + 585) = v2470;
                    if ( v2470 == 3 )
                    {
                      (*((void (__fastcall **)(__int64))v2466 + 109))(v2469);
                    }
                    else if ( (*((_DWORD *)v2466 + 612) & 0x10000000) != 0 || !v2470 )
                    {
                      (*((void (__fastcall **)(__int64))v2466 + 31))(v2469);
                    }
                    else
                    {
                      (*((void (__fastcall **)(__int64, _QWORD))v2466 + 69))(v2469 - 8, *(_QWORD *)(v2469 - 8));
                    }
                    *((_DWORD *)v2466 + 585) = v2472;
                  }
                  *((_DWORD *)v2466 + 612) &= ~4u;
                }
                ++*((_DWORD *)v2466 + 515);
                v2473 = &v2466[v2464];
                v2474 = 48;
                v2475 = &v2466[v2464];
                v2476 = 6i64;
                do
                {
                  *v2475 = 0i64;
                  v2474 -= 8;
                  ++v2475;
                  --v2476;
                }
                while ( v2476 );
                for ( ; v2474; --v2474 )
                {
                  *(_BYTE *)v2475 = 0;
                  v2475 = (_QWORD *)((char *)v2475 + 1);
                }
                *(_DWORD *)v2473 = 31;
                *((_QWORD *)v2473 + 1) = 0i64;
                *((_DWORD *)v2473 + 4) = 0;
                v2477 = *((_QWORD *)v2466 + 259);
                for ( i45 = v2477; ; LODWORD(v2477) = i45 ^ v2477 )
                {
                  i45 >>= 31;
                  if ( !i45 )
                    break;
                }
                v3981 = v2466;
                *((_DWORD *)v2473 + 5) = v2477 & 0x7FFFFFFF;
                _disable();
                if ( !(_BYTE)KdDebuggerNotPresent )
                {
                  while ( 1 )
                    ;
                }
                _enable();
                v2479 = *((unsigned int *)v2466 + 505);
                v2480 = v2479 + 48;
                if ( (unsigned int)(v2479 + 48) <= *((_DWORD *)v2466 + 647) )
                {
                  v2367 = v2466;
                  *((_DWORD *)v2466 + 505) = v2480;
                }
                else
                {
                  v2367 = (_BYTE *)sub_140B0F020(v2466, v2480, *((_DWORD *)v2466 + 585));
                  if ( !v2367 )
                    return 0;
                  v2481 = *((_DWORD *)v2466 + 612);
                  if ( (v2481 & 4) == 0 )
                  {
                    v2482 = *((_DWORD *)v2466 + 505);
                    v2483 = *((_QWORD *)v2466 + 249);
                    v2484 = (v2481 & 0x20000000) != 0 ? *((_DWORD *)v2466 + 585) : 0;
                    if ( v2482 >= 8 )
                    {
                      v2485 = (unsigned __int64)v2482 >> 3;
                      do
                      {
                        *(_QWORD *)v2466 = 0i64;
                        v2482 -= 8;
                        v2466 += 8;
                        --v2485;
                      }
                      while ( v2485 );
                    }
                    for ( ; v2482; --v2482 )
                      *v2466++ = 0;
                    v2486 = *((_DWORD *)v2367 + 585);
                    *((_DWORD *)v2367 + 585) = v2484;
                    if ( v2484 == 3 )
                    {
                      (*((void (__fastcall **)(__int64))v2367 + 109))(v2483);
                    }
                    else if ( (*((_DWORD *)v2367 + 612) & 0x10000000) != 0 || !v2484 )
                    {
                      (*((void (__fastcall **)(__int64))v2367 + 31))(v2483);
                    }
                    else
                    {
                      (*((void (__fastcall **)(__int64, _QWORD))v2367 + 69))(v2483 - 8, *(_QWORD *)(v2483 - 8));
                    }
                    *((_DWORD *)v2367 + 585) = v2486;
                  }
                  *((_DWORD *)v2367 + 612) &= ~4u;
                }
                ++*((_DWORD *)v2367 + 515);
                v2487 = &v2367[v2479];
                v2488 = 48;
                v2489 = &v2367[v2479];
                v2490 = 6i64;
                do
                {
                  *v2489 = 0i64;
                  v2488 -= 8;
                  ++v2489;
                  --v2490;
                }
                while ( v2490 );
                for ( ; v2488; --v2488 )
                {
                  *(_BYTE *)v2489 = 0;
                  v2489 = (_QWORD *)((char *)v2489 + 1);
                }
                *(_DWORD *)v2487 = 37;
                *((_QWORD *)v2487 + 1) = 0i64;
                *((_DWORD *)v2487 + 4) = 0;
                v2491 = *((_QWORD *)v2367 + 259);
                for ( i46 = v2491; ; LODWORD(v2491) = i46 ^ v2491 )
                {
                  i46 >>= 31;
                  if ( !i46 )
                    break;
                }
                v3981 = v2367;
                *((_DWORD *)v2487 + 5) = v2491 & 0x7FFFFFFF;
              }
            }
            if ( *((_DWORD *)v2367 + 612) < (int)i46 && (*((_DWORD *)v2367 + 613) & 0x40) != 0 )
            {
              _disable();
              if ( !(_BYTE)KdDebuggerNotPresent )
              {
                while ( 1 )
                  ;
              }
              _enable();
              v2492 = *((unsigned int *)v2367 + 505);
              v2493 = v2492 + 48;
              if ( (unsigned int)(v2492 + 48) <= *((_DWORD *)v2367 + 647) )
              {
                v2494 = (__int64)v2367;
                *((_DWORD *)v2367 + 505) = v2493;
              }
              else
              {
                v2494 = sub_140B0F020(v2367, v2493, *((_DWORD *)v2367 + 585));
                if ( !v2494 )
                  return 0;
                v2495 = *((_DWORD *)v2367 + 612);
                if ( (v2495 & 4) == 0 )
                {
                  v2496 = *((_DWORD *)v2367 + 505);
                  v2497 = *((_QWORD *)v2367 + 249);
                  v2498 = (v2495 & 0x20000000) != 0 ? *((_DWORD *)v2367 + 585) : 0;
                  if ( v2496 >= 8 )
                  {
                    v2499 = (unsigned __int64)v2496 >> 3;
                    do
                    {
                      *(_QWORD *)v2367 = 0i64;
                      v2496 -= 8;
                      v2367 += 8;
                      --v2499;
                    }
                    while ( v2499 );
                  }
                  for ( ; v2496; --v2496 )
                    *v2367++ = 0;
                  v2500 = *(_DWORD *)(v2494 + 2340);
                  *(_DWORD *)(v2494 + 2340) = v2498;
                  if ( v2498 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v2494 + 872))(v2497);
                  }
                  else if ( (*(_DWORD *)(v2494 + 2448) & 0x10000000) != 0 || !v2498 )
                  {
                    (*(void (__fastcall **)(__int64))(v2494 + 248))(v2497);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v2494 + 552))(v2497 - 8, *(_QWORD *)(v2497 - 8));
                  }
                  *(_DWORD *)(v2494 + 2340) = v2500;
                }
                *(_DWORD *)(v2494 + 2448) &= ~4u;
              }
              ++*(_DWORD *)(v2494 + 2060);
              v2501 = v2494 + v2492;
              v2502 = 48;
              v2503 = (_QWORD *)(v2494 + v2492);
              v2504 = 6i64;
              do
              {
                *v2503 = 0i64;
                v2502 -= 8;
                ++v2503;
                --v2504;
              }
              while ( v2504 );
              for ( ; v2502; --v2502 )
              {
                *(_BYTE *)v2503 = 0;
                v2503 = (_QWORD *)((char *)v2503 + 1);
              }
              *(_DWORD *)v2501 = 49;
              *(_QWORD *)(v2501 + 8) = 0i64;
              *(_DWORD *)(v2501 + 16) = 0;
              v2505 = *(_QWORD *)(v2494 + 2072);
              for ( i47 = v2505; ; LODWORD(v2505) = i47 ^ v2505 )
              {
                i47 >>= 31;
                if ( !i47 )
                  break;
              }
              v3981 = (_BYTE *)v2494;
              *(_DWORD *)(v2501 + 20) = v2505 & 0x7FFFFFFF;
              v2367 = (_BYTE *)v2494;
            }
            v2507 = *((_DWORD *)v2367 + 526);
            v2508 = *((unsigned int *)v2367 + 505);
            v2509 = KxUnexpectedInterrupt0;
            v2510 = *((unsigned int *)v2367 + 585);
            if ( KiKvaShadow )
              v2509 = KiIsrThunkShadow;
            HalExtensionList = (ULONG_PTR)v2509;
            v2511 = 32;
            if ( v2507 != 7 )
              v2511 = 0;
            v2512 = v2508 + 48;
            if ( (unsigned int)(v2508 + 48) <= *((_DWORD *)v2367 + 647) )
            {
              v2513 = v2367;
              *((_DWORD *)v2367 + 505) = v2512;
            }
            else
            {
              v2513 = (_BYTE *)sub_140B0F020(v2367, v2512, v2510);
              if ( !v2513 )
              {
LABEL_3638:
                v2513 = 0i64;
                goto LABEL_4241;
              }
              v2514 = *((_DWORD *)v2367 + 612);
              if ( (v2514 & 4) == 0 )
              {
                v2515 = *((_DWORD *)v2367 + 505);
                v2516 = *((_QWORD *)v2367 + 249);
                v2517 = (v2514 & 0x20000000) != 0 ? *((_DWORD *)v2367 + 585) : 0;
                if ( v2515 >= 8 )
                {
                  v2518 = (unsigned __int64)v2515 >> 3;
                  do
                  {
                    *(_QWORD *)v2367 = 0i64;
                    v2515 -= 8;
                    v2367 += 8;
                    --v2518;
                  }
                  while ( v2518 );
                }
                for ( ; v2515; --v2515 )
                  *v2367++ = 0;
                v2519 = *((_DWORD *)v2513 + 585);
                *((_DWORD *)v2513 + 585) = v2517;
                if ( v2517 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v2513 + 109))(v2516);
                }
                else if ( (*((_DWORD *)v2513 + 612) & 0x10000000) != 0 || !v2517 )
                {
                  (*((void (__fastcall **)(__int64))v2513 + 31))(v2516);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v2513 + 69))(v2516 - 8, *(_QWORD *)(v2516 - 8));
                }
                *((_DWORD *)v2513 + 585) = v2519;
              }
              *((_DWORD *)v2513 + 612) &= ~4u;
              v2509 = (__int64 (__fastcall *)())HalExtensionList;
            }
            v2520 = &v2513[v2508];
            ++*((_DWORD *)v2513 + 515);
            v2521 = &v2513[v2508];
            v3788 = (ULONG_PTR)&v2513[v2508];
            v2522 = 48;
            v2523 = 6i64;
            do
            {
              *v2521 = 0i64;
              v2522 -= 8;
              ++v2521;
              --v2523;
            }
            while ( v2523 );
            for ( ; v2522; --v2522 )
            {
              *(_BYTE *)v2521 = 0;
              v2521 = (_QWORD *)((char *)v2521 + 1);
            }
            *(_DWORD *)v2520 = v2511;
            *((_QWORD *)v2520 + 1) = v2509;
            if ( v2507 == 7 )
            {
              sub_1403ED6CC(v2513, v2509, 2048i64, v2520 + 24);
              v2509 = (__int64 (__fastcall *)())HalExtensionList;
            }
            *((_DWORD *)v2520 + 4) = 2048;
            *((_DWORD *)v2513 + 522) += 2048;
            v2524 = v2509;
            LODWORD(v2525) = *((_DWORD *)v2513 + 517);
            v2526 = v2509;
            for ( i48 = *((_QWORD *)v2513 + 259);
                  (unsigned __int64)v2526 < (unsigned __int64)v2509 + 2048;
                  v2526 = (__int64 (__fastcall *)())((char *)v2526 + 64) )
            {
              _mm_prefetchnta(v2526);
            }
            v2528 = 16;
            v2529 = *((_QWORD *)v2513 + 259);
            do
            {
              v2530 = 8i64;
              do
              {
                v2531 = *((_QWORD *)v2524 + 1) ^ __ROL8__(*(_QWORD *)v2524 ^ v2529, v2525);
                v2524 = (__int64 (__fastcall *)())((char *)v2524 + 16);
                v2529 = __ROL8__(v2531, v2525);
                --v2530;
              }
              while ( v2530 );
              v2532 = (__ROL8__(i48 ^ ((unsigned __int64)v2524 - HalExtensionList), 17) ^ i48 ^ ((unsigned __int64)v2524
                                                                                               - HalExtensionList))
                    * (unsigned __int128)0x7010008004002001ui64;
              v4040 = *((_QWORD *)&v2532 + 1);
              v2525 = ((unsigned __int8)v2532 ^ (unsigned __int8)(BYTE8(v2532) ^ v2525)) & 0x3F;
              if ( !(_DWORD)v2525 )
                v2525 = 1i64;
              --v2528;
            }
            while ( v2528 );
            for ( i49 = v2529 >> 31; i49; i49 >>= 31 )
              LODWORD(v2529) = i49 ^ v2529;
            *(_DWORD *)(v3788 + 20) = v2529 & 0x7FFFFFFF;
            *((_DWORD *)v2513 + 522) += 2048;
            *((_QWORD *)v2513 + 322) = qword_140D81090;
            *((_DWORD *)v2513 + 572) = -1;
            if ( (*((_DWORD *)v2513 + 612) & 0x10000) == 0 )
            {
              Prcb = KeGetPrcb(0i64, 0xFFFFFFFFi64, v2525, v2524);
              v2535 = &v4247;
              v2536 = 11i64;
              do
              {
                *((_QWORD *)v2535 - 1) = -1i64;
                *(_QWORD *)v2535 = 0i64;
                v2535 += 24;
                --v2536;
              }
              while ( v2536 );
              v4248[0] = -1073741694;
              v4249 = -1073741695;
              v2538 = __cpuid(-2147483647, 0);
              v2537 = EBX(v2538);
              v4132 = EDX(v2538);
              v2539 = (v4132 >> 27) & 1;
              v4129 = EAX(v2538);
              v2540 = v4258;
              v4131 = ECX(v2538);
              if ( v2539 )
                v2540 = -1073741565;
              v4250 = -1073741693;
              v2541 = *((_QWORD *)v2513 + 206);
              v2542 = v2539 + 9;
              v4258 = v2540;
              v2543 = v2513[1656];
              v4251 = 27;
              v4252 = 372;
              v4253 = 373;
              v4254 = 374;
              v4255 = -1073741692;
              v4257 = -1073741696;
              v4256 = -4097i64;
              v4130 = v2537;
              LODWORD(Src) = v2542;
              if ( *(_BYTE *)(Prcb + v2541) == v2543 )
              {
                v2544 = 3 * v2542;
                v4248[2 * v2544] = 416;
                v4246[v2544 + 16] = 0x400440000i64;
                LODWORD(Src) = v2542 + 1;
              }
              LODWORD(v3784) = 0;
              v2545 = 0;

              if ( (_DWORD)KeNumberProcessors_0 )
              {
                HalExtensionList = v4041;
                v3788 = v4042;
                do
                {
                  v2546 = (void (__fastcall *)(char *))*((_QWORD *)v2513 + 51);
                  (*((void (__fastcall **)(char *, _QWORD))v2513 + 52))(v4133, v2545);
                  (*((void (__fastcall **)(char *, char *))v2513 + 58))(v4133, v4134);
                  KiGetGdtIdt(&v4099, v4098);
                  v2547 = (__int64)v4100;
                  v2548 = &dword_140013E8C;
                  v2549 = 7i64;
                  do
                  {
                    v2550 = *(unsigned __int8 *)v2548;
                    v2551 = *(_DWORD *)(v2550 + v2547 + 4);
                    if ( (v2551 & 0x100) == 0 )
                      *(_DWORD *)(v2550 + v2547 + 4) = v2551 | 0x100;
                    v2548 = (int *)((char *)v2548 + 1);
                    --v2549;
                  }
                  while ( v2549 );
                  v2552 = *(_DWORD *)(v2547 + 68);
                  if ( (v2552 & 0x200) == 0 )
                    *(_DWORD *)(v2547 + 68) = v2552 | 0x200;
                  v2553 = *((unsigned int *)v2513 + 505);
                  v2554 = v4100;
                  v2555 = v2553 + 48;
                  if ( (unsigned int)(v2553 + 48) <= *((_DWORD *)v2513 + 647) )
                  {
                    v2556 = v2513;
                    *((_DWORD *)v2513 + 505) = v2555;
                  }
                  else
                  {
                    v2556 = (_BYTE *)sub_140B0F020(v2513, v2555, *((_DWORD *)v2513 + 585));
                    if ( !v2556 )
                    {
                      v2557 = HalExtensionList;
                      v2556 = 0i64;
                      goto LABEL_3718;
                    }
                    v2558 = *((_DWORD *)v2513 + 612);
                    if ( (v2558 & 4) == 0 )
                    {
                      v2559 = *((_DWORD *)v2513 + 505);
                      v2560 = *((_QWORD *)v2513 + 249);
                      v2561 = (v2558 & 0x20000000) != 0 ? *((_DWORD *)v2513 + 585) : 0;
                      if ( v2559 >= 8 )
                      {
                        v2562 = (unsigned __int64)v2559 >> 3;
                        do
                        {
                          *(_QWORD *)v2513 = 0i64;
                          v2559 -= 8;
                          v2513 += 8;
                          --v2562;
                        }
                        while ( v2562 );
                      }
                      for ( ; v2559; --v2559 )
                        *v2513++ = 0;
                      v2563 = *((_DWORD *)v2556 + 585);
                      *((_DWORD *)v2556 + 585) = v2561;
                      if ( v2561 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2556 + 109))(v2560);
                      }
                      else if ( (*((_DWORD *)v2556 + 612) & 0x10000000) != 0 || !v2561 )
                      {
                        (*((void (__fastcall **)(__int64))v2556 + 31))(v2560);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2556 + 69))(v2560 - 8, *(_QWORD *)(v2560 - 8));
                      }
                      *((_DWORD *)v2556 + 585) = v2563;
                    }
                    *((_DWORD *)v2556 + 612) &= ~4u;
                  }
                  ++*((_DWORD *)v2556 + 515);
                  v2557 = (ULONG_PTR)&v2556[v2553];
                  v2564 = 48;
                  HalExtensionList = v2557;
                  v2565 = (_QWORD *)v2557;
                  v2566 = 6i64;
                  do
                  {
                    *v2565 = 0i64;
                    v2564 -= 8;
                    ++v2565;
                    --v2566;
                  }
                  while ( v2566 );
                  for ( ; v2564; --v2564 )
                  {
                    *(_BYTE *)v2565 = 0;
                    v2565 = (_QWORD *)((char *)v2565 + 1);
                  }
                  *(_DWORD *)v2557 = 3;
                  *(_QWORD *)(v2557 + 8) = v2554;
                  *(_DWORD *)(v2557 + 16) = 80;
                  v2567 = (char *)v2554;
                  *((_DWORD *)v2556 + 522) += 80;
                  v2568 = *((_DWORD *)v2556 + 517);
                  v2569 = *((_QWORD *)v2556 + 259);
                  if ( v2554 < v2554 + 10 )
                  {
                    do
                    {
                      _mm_prefetchnta(v2567);
                      v2567 += 64;
                    }
                    while ( v2567 < (char *)v2554 + 80 );
                  }
                  v2570 = 80;
                  v2571 = 10i64;
                  do
                  {
                    v2569 = __ROL8__(*v2554++ ^ v2569, v2568);
                    v2570 -= 8;
                    --v2571;
                  }
                  while ( v2571 );
                  for ( ; v2570; --v2570 )
                  {
                    v2572 = *(unsigned __int8 *)v2554;
                    v2554 = (_QWORD *)((char *)v2554 + 1);
                    v2569 = __ROL8__(v2572 ^ v2569, v2568);
                  }
                  for ( i50 = v2569; ; LODWORD(v2569) = i50 ^ v2569 )
                  {
                    i50 >>= 31;
                    if ( !i50 )
                      break;
                  }
                  *(_DWORD *)(v2557 + 20) = v2569 & 0x7FFFFFFF;
                  *((_DWORD *)v2556 + 522) += 80;
LABEL_3718:
                  v2546(v4134);
                  if ( !v2556 )
                    goto LABEL_4243;
                  v2574 = (unsigned int)v3784;
                  *(_DWORD *)(v2557 + 40) = v3784;
                  *(_WORD *)(v2557 + 44) = v4099;
                  v2575 = (void (__fastcall *)(char *))*((_QWORD *)v2556 + 51);
                  v2576 = 0;
                  (*((void (__fastcall **)(char *, __int64))v2556 + 52))(v4135, v2574);
                  (*((void (__fastcall **)(char *, char *))v2556 + 58))(v4135, v4136);
                  KiGetGdtIdt(v4103, &v4101);
                  v2577 = *((unsigned int *)v2556 + 505);
                  v2578 = v4102;
                  v2579 = v2577 + 48;
                  if ( (unsigned int)(v2577 + 48) <= *((_DWORD *)v2556 + 647) )
                  {
                    v2580 = v2556;
                    *((_DWORD *)v2556 + 505) = v2579;
                  }
                  else
                  {
                    v2580 = (_BYTE *)sub_140B0F020(v2556, v2579, *((_DWORD *)v2556 + 585));
                    if ( !v2580 )
                    {
                      v2580 = 0i64;
                      goto LABEL_3766;
                    }
                    v2581 = *((_DWORD *)v2556 + 612);
                    if ( (v2581 & 4) == 0 )
                    {
                      v2582 = *((_DWORD *)v2556 + 505);
                      v2583 = *((_QWORD *)v2556 + 249);
                      v2584 = (v2581 & 0x20000000) != 0 ? *((_DWORD *)v2556 + 585) : 0;
                      if ( v2582 >= 8 )
                      {
                        v2585 = (unsigned __int64)v2582 >> 3;
                        do
                        {
                          *(_QWORD *)v2556 = 0i64;
                          v2582 -= 8;
                          v2556 += 8;
                          --v2585;
                        }
                        while ( v2585 );
                      }
                      for ( ; v2582; --v2582 )
                        *v2556++ = 0;
                      v2586 = *((_DWORD *)v2580 + 585);
                      *((_DWORD *)v2580 + 585) = v2584;
                      if ( v2584 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2580 + 109))(v2583);
                      }
                      else if ( (*((_DWORD *)v2580 + 612) & 0x10000000) != 0 || !v2584 )
                      {
                        (*((void (__fastcall **)(__int64))v2580 + 31))(v2583);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2580 + 69))(v2583 - 8, *(_QWORD *)(v2583 - 8));
                      }
                      *((_DWORD *)v2580 + 585) = v2586;
                    }
                    *((_DWORD *)v2580 + 612) &= ~4u;
                  }
                  ++*((_DWORD *)v2580 + 515);
                  v2587 = &v2580[v2577];
                  v2588 = 48;
                  v3788 = (ULONG_PTR)&v2580[v2577];
                  v2589 = &v2580[v2577];
                  v2590 = 6;
                  v2591 = 6i64;
                  do
                  {
                    *v2589 = 0i64;
                    v2588 -= 8;
                    ++v2589;
                    --v2591;
                  }
                  while ( v2591 );
                  for ( ; v2588; --v2588 )
                  {
                    *(_BYTE *)v2589 = 0;
                    v2589 = (_QWORD *)((char *)v2589 + 1);
                  }
                  *(_DWORD *)v2587 = 2;
                  *((_QWORD *)v2587 + 1) = v2578;
                  *((_DWORD *)v2587 + 4) = 848;
                  v2592 = (_QWORD *)v2578;
                  *((_DWORD *)v2580 + 522) += 848;
                  v2593 = (char *)v2578;
                  v2594 = *((_DWORD *)v2580 + 517);
                  v2595 = *((_QWORD *)v2580 + 259);
                  if ( v2578 < (unsigned __int64)(v2578 + 848) )
                  {
                    do
                    {
                      _mm_prefetchnta(v2593);
                      v2593 += 64;
                    }
                    while ( (unsigned __int64)v2593 < v2578 + 848 );
                  }
                  v2596 = *((_QWORD *)v2580 + 259);
                  do
                  {
                    v2597 = 8i64;
                    do
                    {
                      v2598 = v2592[1] ^ __ROL8__(*v2592 ^ v2596, v2594);
                      v2592 += 2;
                      v2596 = __ROL8__(v2598, v2594);
                      --v2597;
                    }
                    while ( v2597 );
                    v2599 = (__ROL8__(v2595 ^ ((unsigned __int64)v2592 - v2578), 17) ^ v2595 ^ ((unsigned __int64)v2592
                                                                                              - v2578))
                          * (unsigned __int128)0x7010008004002001ui64;
                    v4043 = *((_QWORD *)&v2599 + 1);
                    v2594 = ((unsigned __int8)v2599 ^ (unsigned __int8)(BYTE8(v2599) ^ v2594)) & 0x3F;
                    if ( !v2594 )
                      LOBYTE(v2594) = 1;
                    --v2590;
                  }
                  while ( v2590 );
                  v2600 = 80;
                  v2601 = 10i64;
                  do
                  {
                    v2596 = __ROL8__(*v2592++ ^ v2596, v2594);
                    v2600 -= 8;
                    --v2601;
                  }
                  while ( v2601 );
                  for ( ; v2600; --v2600 )
                  {
                    v2602 = *(unsigned __int8 *)v2592;
                    v2592 = (_QWORD *)((char *)v2592 + 1);
                    v2596 = __ROL8__(v2602 ^ v2596, v2594);
                  }
                  for ( i51 = v2596; ; LODWORD(v2596) = i51 ^ v2596 )
                  {
                    i51 >>= 31;
                    if ( !i51 )
                      break;
                  }
                  *((_DWORD *)v2587 + 5) = v2596 & 0x7FFFFFFF;
                  *((_DWORD *)v2580 + 522) += 848;
                  v2604 = v4102;
                  *((_DWORD *)v2580 + 522) += 16;
                  v2605 = (_QWORD *)(v2604 + 3600);
                  v2606 = *((_DWORD *)v2580 + 517);
                  v2607 = (char *)v2605;
                  v2608 = *((_QWORD *)v2580 + 259);
                  if ( v2605 < v2605 + 2 )
                  {
                    do
                    {
                      _mm_prefetchnta(v2607);
                      v2607 += 64;
                    }
                    while ( v2607 < (char *)v2605 + 16 );
                  }
                  v2609 = 16;
                  v2610 = 2i64;
                  do
                  {
                    v2608 = __ROL8__(*v2605++ ^ v2608, v2606);
                    v2609 -= 8;
                    --v2610;
                  }
                  while ( v2610 );
                  for ( ; v2609; --v2609 )
                  {
                    v2611 = *(unsigned __int8 *)v2605;
                    v2605 = (_QWORD *)((char *)v2605 + 1);
                    v2608 = __ROL8__(v2611 ^ v2608, v2606);
                  }
                  for ( i52 = v2608; ; LODWORD(v2608) = i52 ^ v2608 )
                  {
                    i52 >>= 31;
                    if ( !i52 )
                      break;
                  }
                  v2576 = v2608 & 0x7FFFFFFF;
LABEL_3766:
                  v2575(v4136);
                  if ( !v2580 )
                    goto LABEL_3638;
                  v2613 = v3788;
                  v2614 = v3784;
                  v2615 = (unsigned int)Src;
                  *(_QWORD *)(v3788 + 24) = v2576;
                  *(_DWORD *)(v2613 + 40) = v2614;
                  *(_WORD *)(v2613 + 44) = v4101;
                  v2616 = *((unsigned int *)v2580 + 505);
                  v2617 = v2616 + 24 * (v2615 + 2);
                  if ( v2617 <= *((_DWORD *)v2580 + 647) )
                  {
                    v2618 = v2580;
                    *((_DWORD *)v2580 + 505) = v2617;
                  }
                  else
                  {
                    v2618 = (_BYTE *)sub_140B0F020(v2580, v2617, *((_DWORD *)v2580 + 585));
                    if ( !v2618 )
                      goto LABEL_3638;
                    v2619 = *((_DWORD *)v2580 + 612);
                    if ( (v2619 & 4) == 0 )
                    {
                      v2620 = *((_DWORD *)v2580 + 505);
                      v2621 = *((_QWORD *)v2580 + 249);
                      v2622 = (v2619 & 0x20000000) != 0 ? *((_DWORD *)v2580 + 585) : 0;
                      if ( v2620 >= 8 )
                      {
                        v2623 = (unsigned __int64)v2620 >> 3;
                        do
                        {
                          *(_QWORD *)v2580 = 0i64;
                          v2620 -= 8;
                          v2580 += 8;
                          --v2623;
                        }
                        while ( v2623 );
                      }
                      for ( ; v2620; --v2620 )
                        *v2580++ = 0;
                      v2624 = *((_DWORD *)v2618 + 585);
                      *((_DWORD *)v2618 + 585) = v2622;
                      if ( v2622 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2618 + 109))(v2621);
                      }
                      else if ( (*((_DWORD *)v2618 + 612) & 0x10000000) != 0 || !v2622 )
                      {
                        (*((void (__fastcall **)(__int64))v2618 + 31))(v2621);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2618 + 69))(v2621 - 8, *(_QWORD *)(v2621 - 8));
                      }
                      *((_DWORD *)v2618 + 585) = v2624;
                    }
                    *((_DWORD *)v2618 + 612) &= ~4u;
                  }
                  ++*((_DWORD *)v2618 + 515);
                  v2625 = &v2618[v2616];
                  v2626 = 48;
                  v2627 = &v2618[v2616];
                  v2628 = 6i64;
                  do
                  {
                    *v2627 = 0i64;
                    v2626 -= 8;
                    ++v2627;
                    --v2628;
                  }
                  while ( v2628 );
                  for ( ; v2626; --v2626 )
                  {
                    *(_BYTE *)v2627 = 0;
                    v2627 = (_QWORD *)((char *)v2627 + 1);
                  }
                  *(_DWORD *)v2625 = 7;
                  *((_QWORD *)v2625 + 1) = 0i64;
                  *((_DWORD *)v2625 + 4) = 0;
                  v2629 = *((_QWORD *)v2618 + 259);
                  for ( i53 = v2629; ; LODWORD(v2629) = i53 ^ v2629 )
                  {
                    i53 >>= 31;
                    if ( !i53 )
                      break;
                  }
                  v2631 = v2625 + 48;
                  *((_DWORD *)v2625 + 5) = v2629 & 0x7FFFFFFF;
                  *((_DWORD *)v2625 + 6) = v2615;
                  *((_DWORD *)v2625 + 7) = v2614;
                  (*((void (__fastcall **)(char *, _QWORD, _QWORD))v2618 + 52))(v4137, v2614, 0i64);
                  (*((void (__fastcall **)(char *, char *))v2618 + 58))(v4137, v4138);
                  v2633 = v2615;
                  v2634 = v2631 - (_BYTE *)v4248;
                  v2635 = v4248;
                  do
                  {
                    v2636 = *((_QWORD *)v2635 - 2);
                    v2637 = *v2635;
                    *(_QWORD *)((char *)v2635 + v2634) = v2636;
                    *(unsigned int *)((char *)v2635 + v2634 + 16) = v2637;
                    if ( (v2618[2171] & 2) != 0
                      && v2637 == -1073741694
                      && HIDWORD(KeGetPcr()[1].LockArray) == *((_DWORD *)v2618 + 572) )
                    {
                      v2638 = *((_QWORD *)v2618 + 285);
                    }
                    else
                    {
                      v2638 = __readmsr(v2637);
                      v2632 = (unsigned __int64)HIDWORD(v2638) << 32;
                    }
                    *(_QWORD *)((char *)v2635 + v2634 + 8) = v2636 & v2638;
                    v2635 += 6;
                    --v2633;
                  }
                  while ( v2633 );
                  (*((void (__fastcall **)(char *, unsigned __int64))v2618 + 51))(v4138, v2632);
                  v2639 = *((unsigned int *)v2618 + 505);
                  v2640 = v2639 + 48;
                  if ( (unsigned int)(v2639 + 48) <= *((_DWORD *)v2618 + 647) )
                  {
                    v2641 = v2618;
                    *((_DWORD *)v2618 + 505) = v2640;
                  }
                  else
                  {
                    v2641 = (_BYTE *)sub_140B0F020(v2618, v2640, *((_DWORD *)v2618 + 585));
                    if ( !v2641 )
                      goto LABEL_3638;
                    v2642 = *((_DWORD *)v2618 + 612);
                    if ( (v2642 & 4) == 0 )
                    {
                      v2643 = *((_DWORD *)v2618 + 505);
                      v2644 = *((_QWORD *)v2618 + 249);
                      v2645 = (v2642 & 0x20000000) != 0 ? *((_DWORD *)v2618 + 585) : 0;
                      if ( v2643 >= 8 )
                      {
                        v2646 = (unsigned __int64)v2643 >> 3;
                        do
                        {
                          *(_QWORD *)v2618 = 0i64;
                          v2643 -= 8;
                          v2618 += 8;
                          --v2646;
                        }
                        while ( v2646 );
                      }
                      for ( ; v2643; --v2643 )
                        *v2618++ = 0;
                      v2647 = *((_DWORD *)v2641 + 585);
                      *((_DWORD *)v2641 + 585) = v2645;
                      if ( v2645 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2641 + 109))(v2644);
                      }
                      else if ( (*((_DWORD *)v2641 + 612) & 0x10000000) != 0 || !v2645 )
                      {
                        (*((void (__fastcall **)(__int64))v2641 + 31))(v2644);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2641 + 69))(v2644 - 8, *(_QWORD *)(v2644 - 8));
                      }
                      *((_DWORD *)v2641 + 585) = v2647;
                    }
                    *((_DWORD *)v2641 + 612) &= ~4u;
                  }
                  ++*((_DWORD *)v2641 + 515);
                  v2648 = &v2641[v2639];
                  v2649 = 48;
                  v2650 = &v2641[v2639];
                  v2651 = 6i64;
                  do
                  {
                    *v2650 = 0i64;
                    v2649 -= 8;
                    ++v2650;
                    --v2651;
                  }
                  while ( v2651 );
                  for ( ; v2649; --v2649 )
                  {
                    *(_BYTE *)v2650 = 0;
                    v2650 = (_QWORD *)((char *)v2650 + 1);
                  }
                  *(_DWORD *)v2648 = 21;
                  *((_QWORD *)v2648 + 1) = 0i64;
                  *((_DWORD *)v2648 + 4) = 0;
                  v2652 = *((_QWORD *)v2641 + 259);
                  for ( i54 = v2652 >> 31; i54; i54 >>= 31 )
                    LODWORD(v2652) = i54 ^ v2652;
                  *((_DWORD *)v2648 + 5) = v2652 & 0x7FFFFFFF;
                  *((_DWORD *)v2648 + 10) = 0;
                  *((_QWORD *)v2648 + 3) = 2147549185i64;
                  *((_DWORD *)v2648 + 11) = v2614;
                  (*((void (__fastcall **)(char *, _QWORD))v2641 + 52))(v4139, v2614);
                  (*((void (__fastcall **)(char *, char *))v2641 + 58))(v4139, v4140);
                  v2654 = __readcr0();
                  (*((void (__fastcall **)(char *))v2641 + 51))(v4140);
                  *((_QWORD *)v2648 + 4) = v2654 & 0x80010001;
                  v2655 = *((unsigned int *)v2641 + 505);
                  v2656 = v2655 + 48;
                  if ( (unsigned int)(v2655 + 48) <= *((_DWORD *)v2641 + 647) )
                  {
                    v2657 = v2641;
                    *((_DWORD *)v2641 + 505) = v2656;
                  }
                  else
                  {
                    v2657 = (_BYTE *)sub_140B0F020(v2641, v2656, *((_DWORD *)v2641 + 585));
                    if ( !v2657 )
                      goto LABEL_3638;
                    v2658 = *((_DWORD *)v2641 + 612);
                    if ( (v2658 & 4) == 0 )
                    {
                      v2659 = *((_DWORD *)v2641 + 505);
                      v2660 = *((_QWORD *)v2641 + 249);
                      v2661 = (v2658 & 0x20000000) != 0 ? *((_DWORD *)v2641 + 585) : 0;
                      if ( v2659 >= 8 )
                      {
                        v2662 = (unsigned __int64)v2659 >> 3;
                        do
                        {
                          *(_QWORD *)v2641 = 0i64;
                          v2659 -= 8;
                          v2641 += 8;
                          --v2662;
                        }
                        while ( v2662 );
                      }
                      for ( ; v2659; --v2659 )
                        *v2641++ = 0;
                      v2663 = *((_DWORD *)v2657 + 585);
                      *((_DWORD *)v2657 + 585) = v2661;
                      if ( v2661 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2657 + 109))(v2660);
                      }
                      else if ( (*((_DWORD *)v2657 + 612) & 0x10000000) != 0 || !v2661 )
                      {
                        (*((void (__fastcall **)(__int64))v2657 + 31))(v2660);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2657 + 69))(v2660 - 8, *(_QWORD *)(v2660 - 8));
                      }
                      *((_DWORD *)v2657 + 585) = v2663;
                    }
                    *((_DWORD *)v2657 + 612) &= ~4u;
                  }
                  ++*((_DWORD *)v2657 + 515);
                  v2664 = &v2657[v2655];
                  v2665 = 48;
                  v2666 = &v2657[v2655];
                  v2667 = 6i64;
                  do
                  {
                    *v2666 = 0i64;
                    v2665 -= 8;
                    ++v2666;
                    --v2667;
                  }
                  while ( v2667 );
                  for ( ; v2665; --v2665 )
                  {
                    *(_BYTE *)v2666 = 0;
                    v2666 = (_QWORD *)((char *)v2666 + 1);
                  }
                  *(_DWORD *)v2664 = 21;
                  *((_QWORD *)v2664 + 1) = 0i64;
                  *((_DWORD *)v2664 + 4) = 0;
                  v2668 = *((_QWORD *)v2657 + 259);
                  for ( i55 = v2668; ; LODWORD(v2668) = i55 ^ v2668 )
                  {
                    i55 >>= 31;
                    if ( !i55 )
                      break;
                  }
                  *((_DWORD *)v2664 + 5) = v2668 & 0x7FFFFFFF;
                  *((_DWORD *)v2664 + 10) = 4;
                  *((_QWORD *)v2664 + 3) = -8641i64;
                  *((_DWORD *)v2664 + 11) = v2614;
                  (*((void (__fastcall **)(char *, _QWORD))v2657 + 52))(v4141, v2614);
                  (*((void (__fastcall **)(char *, char *))v2657 + 58))(v4141, v4142);
                  v2670 = __readcr4();
                  (*((void (__fastcall **)(char *))v2657 + 51))(v4142);
                  *((_QWORD *)v2664 + 4) = v2670 & 0xFFFFFFFFFFFFDE3Fui64;
                  if ( RtlGetEnabledExtendedFeatures(0xFFFFFFFFFFFFFFFFui64) )
                  {
                    v2671 = *((unsigned int *)v2657 + 505);
                    v2672 = v2671 + 48;
                    if ( (unsigned int)(v2671 + 48) <= *((_DWORD *)v2657 + 647) )
                    {
                      v2673 = (__int64)v2657;
                      *((_DWORD *)v2657 + 505) = v2672;
                    }
                    else
                    {
                      v2673 = sub_140B0F020(v2657, v2672, *((_DWORD *)v2657 + 585));
                      if ( !v2673 )
                        goto LABEL_3638;
                      v2674 = *((_DWORD *)v2657 + 612);
                      if ( (v2674 & 4) == 0 )
                      {
                        v2675 = *((_DWORD *)v2657 + 505);
                        v2676 = *((_QWORD *)v2657 + 249);
                        v2677 = (v2674 & 0x20000000) != 0 ? *((_DWORD *)v2657 + 585) : 0;
                        if ( v2675 >= 8 )
                        {
                          v2678 = (unsigned __int64)v2675 >> 3;
                          do
                          {
                            *(_QWORD *)v2657 = 0i64;
                            v2675 -= 8;
                            v2657 += 8;
                            --v2678;
                          }
                          while ( v2678 );
                        }
                        for ( ; v2675; --v2675 )
                          *v2657++ = 0;
                        v2679 = *(_DWORD *)(v2673 + 2340);
                        *(_DWORD *)(v2673 + 2340) = v2677;
                        if ( v2677 == 3 )
                        {
                          (*(void (__fastcall **)(__int64))(v2673 + 872))(v2676);
                        }
                        else if ( (*(_DWORD *)(v2673 + 2448) & 0x10000000) != 0 || !v2677 )
                        {
                          (*(void (__fastcall **)(__int64))(v2673 + 248))(v2676);
                        }
                        else
                        {
                          (*(void (__fastcall **)(__int64, _QWORD))(v2673 + 552))(v2676 - 8, *(_QWORD *)(v2676 - 8));
                        }
                        *(_DWORD *)(v2673 + 2340) = v2679;
                      }
                      *(_DWORD *)(v2673 + 2448) &= ~4u;
                    }
                    ++*(_DWORD *)(v2673 + 2060);
                    v2680 = v2673 + v2671;
                    v2681 = 48;
                    v2682 = (_QWORD *)(v2673 + v2671);
                    v2683 = 6i64;
                    do
                    {
                      *v2682 = 0i64;
                      v2681 -= 8;
                      ++v2682;
                      --v2683;
                    }
                    while ( v2683 );
                    for ( ; v2681; --v2681 )
                    {
                      *(_BYTE *)v2682 = 0;
                      v2682 = (_QWORD *)((char *)v2682 + 1);
                    }
                    *(_DWORD *)v2680 = 38;
                    *(_QWORD *)(v2680 + 8) = 0i64;
                    *(_DWORD *)(v2680 + 16) = 0;
                    v2684 = *(_QWORD *)(v2673 + 2072);
                    for ( i56 = v2684 >> 31; i56; i56 >>= 31 )
                      LODWORD(v2684) = i56 ^ v2684;
                    *(_DWORD *)(v2680 + 20) = v2684 & 0x7FFFFFFF;
                    *(_DWORD *)(v2680 + 40) = 0;
                    *(_QWORD *)(v2680 + 24) = -1i64;
                    *(_DWORD *)(v2680 + 44) = v2614;
                    (*(void (__fastcall **)(char *, _QWORD))(v2673 + 416))(v4143, v2614);
                    v2686 = (*(__int64 (__fastcall **)(char *, char *))(v2673 + 464))(v4143, v4144);
                    LODWORD(v2686) = _xgetbv(0);
                    v2688 = v2686 | (v2687 << 32);
                    (*(void (__fastcall **)(char *))(v2673 + 408))(v4144);
                    *(_QWORD *)(v2680 + 32) = v2688;
                    v2657 = (_BYTE *)v2673;
                  }
                  (*((void (__fastcall **)(char *, _QWORD))v2657 + 52))(v4145, v2614);
                  (*((void (__fastcall **)(char *, char *))v2657 + 58))(v4145, v4146);
                  v2689 = *((_QWORD *)v2657 + 322);
                  if ( v2689 )
                  {
                    v2690 = *(_DWORD *)(v2689 + 800);
                    v2691 = *((_QWORD *)v2657 + 322);
                    if ( v2691 )
                    {
                      v2692 = *(_DWORD *)(v2691 + 832);
                      goto LABEL_3877;
                    }
                  }
                  else
                  {
                    v2690 = __readmsr(0x832u);
                  }
                  v2693 = __readmsr(0x834u);
                  v2692 = v2693;
LABEL_3877:
                  (*((void (__fastcall **)(char *))v2657 + 51))(v4146);
                  v2695 = *((unsigned int *)v2657 + 505);
                  v2696 = v2690 & 0xFFFCEF00;
                  v2697 = v2692 & 0xFFFEE800;
                  v2698 = v2695 + 48;
                  if ( (unsigned int)(v2695 + 48) <= *((_DWORD *)v2657 + 647) )
                  {
                    v2699 = v2657;
                    *((_DWORD *)v2657 + 505) = v2698;
                  }
                  else
                  {
                    v2699 = (_BYTE *)sub_140B0F020(v2657, v2698, *((_DWORD *)v2657 + 585));
                    if ( !v2699 )
                      goto LABEL_3638;
                    v2700 = *((_DWORD *)v2657 + 612);
                    if ( (v2700 & 4) == 0 )
                    {
                      v2701 = *((_DWORD *)v2657 + 505);
                      v2702 = *((_QWORD *)v2657 + 249);
                      v2703 = (v2700 & 0x20000000) != 0 ? *((_DWORD *)v2657 + 585) : 0;
                      if ( v2701 >= 8 )
                      {
                        v2704 = (unsigned __int64)v2701 >> 3;
                        do
                        {
                          *(_QWORD *)v2657 = 0i64;
                          v2701 -= 8;
                          v2657 += 8;
                          --v2704;
                        }
                        while ( v2704 );
                      }
                      for ( ; v2701; --v2701 )
                        *v2657++ = 0;
                      v2705 = *((_DWORD *)v2699 + 585);
                      *((_DWORD *)v2699 + 585) = v2703;
                      if ( v2703 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2699 + 109))(v2702);
                      }
                      else if ( (*((_DWORD *)v2699 + 612) & 0x10000000) != 0 || !v2703 )
                      {
                        (*((void (__fastcall **)(__int64))v2699 + 31))(v2702);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2699 + 69))(v2702 - 8, *(_QWORD *)(v2702 - 8));
                      }
                      *((_DWORD *)v2699 + 585) = v2705;
                    }
                    *((_DWORD *)v2699 + 612) &= ~4u;
                  }
                  ++*((_DWORD *)v2699 + 515);
                  v2706 = &v2699[v2695];
                  v2707 = 48;
                  v2708 = &v2699[v2695];
                  v2709 = 6i64;
                  do
                  {
                    *v2708 = 0i64;
                    v2707 -= 8;
                    ++v2708;
                    --v2709;
                  }
                  while ( v2709 );
                  for ( ; v2707; --v2707 )
                  {
                    *(_BYTE *)v2708 = 0;
                    v2708 = (_QWORD *)((char *)v2708 + 1);
                  }
                  *(_DWORD *)v2706 = 23;
                  *((_QWORD *)v2706 + 1) = 0i64;
                  *((_DWORD *)v2706 + 4) = 0;
                  v2710 = *((_QWORD *)v2699 + 259);
                  for ( i57 = v2710; ; v2710 = (unsigned int)i57 ^ (unsigned int)v2710 )
                  {
                    i57 >>= 31;
                    if ( !i57 )
                      break;
                  }
                  v2712 = (unsigned int)v3784;
                  LODWORD(v2710) = v2710 & 0x7FFFFFFF;
                  *((_DWORD *)v2706 + 5) = v2710;
                  *((_DWORD *)v2706 + 6) = v2696;
                  *((_DWORD *)v2706 + 7) = -200960;
                  *((_DWORD *)v2706 + 8) = v2697;
                  *((_DWORD *)v2706 + 9) = -71680;
                  *((_DWORD *)v2706 + 10) = v2712;
                  v2713 = KeGetPrcb(v2712, v2710, 0i64, v2694) - 384;
                  v3787 = v2713;
                  if ( (NtBuildNumber & 0xF0000000) == -268435456 )
                    *(_QWORD *)(v2713 + 264) = 0i64;
                  v2714 = *((_DWORD *)v2699 + 526);
                  v2715 = (char *)(v2713 + 264);
                  v2716 = *((unsigned int *)v2699 + 505);
                  v2717 = 32;
                  if ( v2714 != 7 )
                    v2717 = 0;
                  v2718 = v2716 + 48;
                  if ( (unsigned int)(v2716 + 48) <= *((_DWORD *)v2699 + 647) )
                  {
                    v2719 = v2699;
                    *((_DWORD *)v2699 + 505) = v2718;
                  }
                  else
                  {
                    v2719 = (_BYTE *)sub_140B0F020(v2699, v2718, *((_DWORD *)v2699 + 585));
                    if ( !v2719 )
                      goto LABEL_3638;
                    v2720 = *((_DWORD *)v2699 + 612);
                    if ( (v2720 & 4) == 0 )
                    {
                      v2721 = *((_DWORD *)v2699 + 505);
                      v2722 = *((_QWORD *)v2699 + 249);
                      v2723 = (v2720 & 0x20000000) != 0 ? *((_DWORD *)v2699 + 585) : 0;
                      if ( v2721 >= 8 )
                      {
                        v2724 = (unsigned __int64)v2721 >> 3;
                        do
                        {
                          *(_QWORD *)v2699 = 0i64;
                          v2721 -= 8;
                          v2699 += 8;
                          --v2724;
                        }
                        while ( v2724 );
                      }
                      for ( ; v2721; --v2721 )
                        *v2699++ = 0;
                      v2725 = *((_DWORD *)v2719 + 585);
                      *((_DWORD *)v2719 + 585) = v2723;
                      if ( v2723 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2719 + 109))(v2722);
                      }
                      else if ( (*((_DWORD *)v2719 + 612) & 0x10000000) != 0 || !v2723 )
                      {
                        (*((void (__fastcall **)(__int64))v2719 + 31))(v2722);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2719 + 69))(v2722 - 8, *(_QWORD *)(v2722 - 8));
                      }
                      *((_DWORD *)v2719 + 585) = v2725;
                    }
                    *((_DWORD *)v2719 + 612) &= ~4u;
                  }
                  v2726 = &v2719[v2716];
                  ++*((_DWORD *)v2719 + 515);
                  v2727 = &v2719[v2716];
                  v2728 = 48;
                  v2729 = 6i64;
                  do
                  {
                    *v2727 = 0i64;
                    v2728 -= 8;
                    ++v2727;
                    --v2729;
                  }
                  while ( v2729 );
                  for ( ; v2728; --v2728 )
                  {
                    *(_BYTE *)v2727 = 0;
                    v2727 = (_QWORD *)((char *)v2727 + 1);
                  }
                  *(_DWORD *)v2726 = v2717;
                  *((_QWORD *)v2726 + 1) = v2715;
                  if ( v2714 == 7 )
                    sub_1403ED6CC(v2719, v2715, 8i64, v2726 + 24);
                  *((_DWORD *)v2726 + 4) = 8;
                  *((_DWORD *)v2719 + 522) += 8;
                  for ( i58 = v2715; i58 < v2715 + 8; i58 += 64 )
                    _mm_prefetchnta(i58);
                  v2731 = __ROL8__(*(_QWORD *)v2715 ^ *((_QWORD *)v2719 + 259), *((_DWORD *)v2719 + 517));
                  for ( i59 = v2731; ; LODWORD(v2731) = i59 ^ v2731 )
                  {
                    i59 >>= 31;
                    if ( !i59 )
                      break;
                  }
                  v2733 = 32;
                  v2734 = (char *)(v3787 + 56);
                  *((_DWORD *)v2726 + 5) = v2731 & 0x7FFFFFFF;
                  *((_DWORD *)v2719 + 522) += 8;
                  v2735 = *((unsigned int *)v2719 + 505);
                  v2736 = *((_DWORD *)v2719 + 526);
                  if ( v2736 != 7 )
                    v2733 = 0;
                  v2737 = v2735 + 48;
                  if ( (unsigned int)(v2735 + 48) <= *((_DWORD *)v2719 + 647) )
                  {
                    v2738 = v2719;
                    *((_DWORD *)v2719 + 505) = v2737;
                  }
                  else
                  {
                    v2738 = (_BYTE *)sub_140B0F020(v2719, v2737, *((_DWORD *)v2719 + 585));
                    if ( !v2738 )
                      goto LABEL_3638;
                    v2739 = *((_DWORD *)v2719 + 612);
                    if ( (v2739 & 4) == 0 )
                    {
                      v2740 = *((_DWORD *)v2719 + 505);
                      v2741 = *((_QWORD *)v2719 + 249);
                      v2742 = (v2739 & 0x20000000) != 0 ? *((_DWORD *)v2719 + 585) : 0;
                      if ( v2740 >= 8 )
                      {
                        v2743 = (unsigned __int64)v2740 >> 3;
                        do
                        {
                          *(_QWORD *)v2719 = 0i64;
                          v2740 -= 8;
                          v2719 += 8;
                          --v2743;
                        }
                        while ( v2743 );
                      }
                      for ( ; v2740; --v2740 )
                        *v2719++ = 0;
                      v2744 = *((_DWORD *)v2738 + 585);
                      *((_DWORD *)v2738 + 585) = v2742;
                      if ( v2742 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2738 + 109))(v2741);
                      }
                      else if ( (*((_DWORD *)v2738 + 612) & 0x10000000) != 0 || !v2742 )
                      {
                        (*((void (__fastcall **)(__int64))v2738 + 31))(v2741);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2738 + 69))(v2741 - 8, *(_QWORD *)(v2741 - 8));
                      }
                      *((_DWORD *)v2738 + 585) = v2744;
                    }
                    *((_DWORD *)v2738 + 612) &= ~4u;
                  }
                  v2745 = &v2738[v2735];
                  ++*((_DWORD *)v2738 + 515);
                  v2746 = &v2738[v2735];
                  v2747 = 48;
                  v2748 = 6i64;
                  do
                  {
                    *v2746 = 0i64;
                    v2747 -= 8;
                    ++v2746;
                    --v2748;
                  }
                  while ( v2748 );
                  for ( ; v2747; --v2747 )
                  {
                    *(_BYTE *)v2746 = 0;
                    v2746 = (_QWORD *)((char *)v2746 + 1);
                  }
                  *(_DWORD *)v2745 = v2733;
                  *((_QWORD *)v2745 + 1) = v2734;
                  if ( v2736 == 7 )
                    sub_1403ED6CC(v2738, v2734, 8i64, v2745 + 24);
                  *((_DWORD *)v2745 + 4) = 8;
                  *((_DWORD *)v2738 + 522) += 8;
                  for ( i60 = v2734; i60 < v2734 + 8; i60 += 64 )
                    _mm_prefetchnta(i60);
                  v2750 = __ROL8__(*(_QWORD *)v2734 ^ *((_QWORD *)v2738 + 259), *((_DWORD *)v2738 + 517));
                  for ( i61 = v2750; ; LODWORD(v2750) = i61 ^ v2750 )
                  {
                    i61 >>= 31;
                    if ( !i61 )
                      break;
                  }
                  v2752 = 32;
                  *((_DWORD *)v2745 + 5) = v2750 & 0x7FFFFFFF;
                  *((_DWORD *)v2738 + 522) += 8;
                  v2753 = *((unsigned int *)v2738 + 505);
                  v2754 = *((_DWORD *)v2738 + 526);
                  if ( v2754 != 7 )
                    v2752 = 0;
                  v2755 = v2753 + 48;
                  if ( (unsigned int)(v2753 + 48) <= *((_DWORD *)v2738 + 647) )
                  {
                    v2756 = v2738;
                    *((_DWORD *)v2738 + 505) = v2755;
                  }
                  else
                  {
                    v2756 = (_BYTE *)sub_140B0F020(v2738, v2755, *((_DWORD *)v2738 + 585));
                    if ( !v2756 )
                      goto LABEL_3638;
                    v2757 = *((_DWORD *)v2738 + 612);
                    if ( (v2757 & 4) == 0 )
                    {
                      v2758 = *((_DWORD *)v2738 + 505);
                      v2759 = *((_QWORD *)v2738 + 249);
                      v2760 = (v2757 & 0x20000000) != 0 ? *((_DWORD *)v2738 + 585) : 0;
                      if ( v2758 >= 8 )
                      {
                        v2761 = (unsigned __int64)v2758 >> 3;
                        do
                        {
                          *(_QWORD *)v2738 = 0i64;
                          v2758 -= 8;
                          v2738 += 8;
                          --v2761;
                        }
                        while ( v2761 );
                      }
                      for ( ; v2758; --v2758 )
                        *v2738++ = 0;
                      v2762 = *((_DWORD *)v2756 + 585);
                      *((_DWORD *)v2756 + 585) = v2760;
                      if ( v2760 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2756 + 109))(v2759);
                      }
                      else if ( (*((_DWORD *)v2756 + 612) & 0x10000000) != 0 || !v2760 )
                      {
                        (*((void (__fastcall **)(__int64))v2756 + 31))(v2759);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2756 + 69))(v2759 - 8, *(_QWORD *)(v2759 - 8));
                      }
                      *((_DWORD *)v2756 + 585) = v2762;
                    }
                    *((_DWORD *)v2756 + 612) &= ~4u;
                  }
                  v2763 = &v2756[v2753];
                  ++*((_DWORD *)v2756 + 515);
                  v2764 = &v2756[v2753];
                  v2765 = 48;
                  v2766 = 6i64;
                  do
                  {
                    *v2764 = 0i64;
                    v2765 -= 8;
                    ++v2764;
                    --v2766;
                  }
                  while ( v2766 );
                  for ( ; v2765; --v2765 )
                  {
                    *(_BYTE *)v2764 = 0;
                    v2764 = (_QWORD *)((char *)v2764 + 1);
                  }
                  v2767 = (char *)v3787;
                  *(_DWORD *)v2763 = v2752;
                  *((_QWORD *)v2763 + 1) = v2767;
                  if ( v2754 == 7 )
                    sub_1403ED6CC(v2756, v2767, 8i64, v2763 + 24);
                  *((_DWORD *)v2763 + 4) = 8;
                  v2768 = v2767 + 8;
                  *((_DWORD *)v2756 + 522) += 8;
                  v2769 = v2767;
                  v2770 = *((_DWORD *)v2756 + 517);
                  v2771 = *((_QWORD *)v2756 + 259);
                  v3787 = (ULONG_PTR)(v2767 + 8);
                  if ( v2767 < v2767 + 8 )
                  {
                    do
                    {
                      _mm_prefetchnta(v2769);
                      v2769 += 64;
                    }
                    while ( v2769 < v2768 );
                  }
                  v2772 = __ROL8__(*(_QWORD *)v2767 ^ v2771, v2770);
                  for ( i62 = v2772; ; LODWORD(v2772) = i62 ^ v2772 )
                  {
                    i62 >>= 31;
                    if ( !i62 )
                      break;
                  }
                  v2774 = 32;
                  *((_DWORD *)v2763 + 5) = v2772 & 0x7FFFFFFF;
                  *((_DWORD *)v2756 + 522) += 8;
                  v2775 = *((unsigned int *)v2756 + 505);
                  v2776 = *((_DWORD *)v2756 + 526);
                  if ( v2776 != 7 )
                    v2774 = 0;
                  v2777 = v2775 + 48;
                  if ( (unsigned int)(v2775 + 48) <= *((_DWORD *)v2756 + 647) )
                  {
                    v2778 = v2756;
                    *((_DWORD *)v2756 + 505) = v2777;
                  }
                  else
                  {
                    v2778 = (_BYTE *)sub_140B0F020(v2756, v2777, *((_DWORD *)v2756 + 585));
                    if ( !v2778 )
                      goto LABEL_4243;
                    v2779 = *((_DWORD *)v2756 + 612);
                    if ( (v2779 & 4) == 0 )
                    {
                      v2780 = *((_DWORD *)v2756 + 505);
                      v2781 = *((_QWORD *)v2756 + 249);
                      v2782 = (v2779 & 0x20000000) != 0 ? *((_DWORD *)v2756 + 585) : 0;
                      if ( v2780 >= 8 )
                      {
                        v2783 = (unsigned __int64)v2780 >> 3;
                        do
                        {
                          *(_QWORD *)v2756 = 0i64;
                          v2780 -= 8;
                          v2756 += 8;
                          --v2783;
                        }
                        while ( v2783 );
                      }
                      for ( ; v2780; --v2780 )
                        *v2756++ = 0;
                      v2784 = *((_DWORD *)v2778 + 585);
                      *((_DWORD *)v2778 + 585) = v2782;
                      if ( v2782 == 3 )
                      {
                        (*((void (__fastcall **)(__int64))v2778 + 109))(v2781);
                      }
                      else if ( (*((_DWORD *)v2778 + 612) & 0x10000000) != 0 || !v2782 )
                      {
                        (*((void (__fastcall **)(__int64))v2778 + 31))(v2781);
                      }
                      else
                      {
                        (*((void (__fastcall **)(__int64, _QWORD))v2778 + 69))(v2781 - 8, *(_QWORD *)(v2781 - 8));
                      }
                      *((_DWORD *)v2778 + 585) = v2784;
                    }
                    *((_DWORD *)v2778 + 612) &= ~4u;
                    v2768 = (char *)v3787;
                  }
                  ++*((_DWORD *)v2778 + 515);
                  v2785 = &v2778[v2775];
                  v2786 = 48;
                  v2787 = &v2778[v2775];
                  v2788 = 6i64;
                  do
                  {
                    *v2787 = 0i64;
                    v2786 -= 8;
                    ++v2787;
                    --v2788;
                  }
                  while ( v2788 );
                  for ( ; v2786; --v2786 )
                  {
                    *(_BYTE *)v2787 = 0;
                    v2787 = (_QWORD *)((char *)v2787 + 1);
                  }
                  *(_DWORD *)v2785 = v2774;
                  *((_QWORD *)v2785 + 1) = v2768;
                  if ( v2776 == 7 )
                  {
                    sub_1403ED6CC(v2778, v2768, 8i64, v2785 + 24);
                    v2768 = (char *)v3787;
                  }
                  *((_DWORD *)v2785 + 4) = 8;
                  *((_DWORD *)v2778 + 522) += 8;
                  for ( i63 = v2768; i63 < v2768 + 8; i63 += 64 )
                    _mm_prefetchnta(i63);
                  v2790 = __ROL8__(*(_QWORD *)v2768 ^ *((_QWORD *)v2778 + 259), *((_DWORD *)v2778 + 517));
                  for ( i64 = v2790; ; LODWORD(v2790) = i64 ^ v2790 )
                  {
                    i64 >>= 31;
                    if ( !i64 )
                      break;
                  }
                  *((_DWORD *)v2785 + 5) = v2790 & 0x7FFFFFFF;
                  *((_DWORD *)v2778 + 522) += 8;
                  v875 = (v2778[2171] & 8) == 0;
                  v2792 = *((unsigned int *)v2778 + 505);
                  v2793 = *((_DWORD *)v2778 + 526);
                  v2794 = *(_QWORD **)v2768;
                  v2795 = *((unsigned int *)v2778 + 585);
                  v2796 = v2792 + 48;
                  LODWORD(v3783) = v2793;
                  if ( v875 )
                  {
                    v2817 = (_QWORD *)((char *)v2794 + 12);
                    v2818 = 32;
                    if ( v2793 != 7 )
                      v2818 = 0;
                    if ( v2796 <= *((_DWORD *)v2778 + 647) )
                    {
                      v2513 = v2778;
                      *((_DWORD *)v2778 + 505) = v2796;
                    }
                    else
                    {
                      v2513 = (_BYTE *)sub_140B0F020(v2778, v2796, v2795);
                      if ( !v2513 )
                      {
LABEL_4028:
                        v2513 = 0i64;
                        goto LABEL_4096;
                      }
                      v2819 = *((_DWORD *)v2778 + 612);
                      if ( (v2819 & 4) == 0 )
                      {
                        v2820 = *((_DWORD *)v2778 + 505);
                        v2821 = *((_QWORD *)v2778 + 249);
                        v2822 = (v2819 & 0x20000000) != 0 ? *((_DWORD *)v2778 + 585) : 0;
                        if ( v2820 >= 8 )
                        {
                          v2823 = (unsigned __int64)v2820 >> 3;
                          do
                          {
                            *(_QWORD *)v2778 = 0i64;
                            v2820 -= 8;
                            v2778 += 8;
                            --v2823;
                          }
                          while ( v2823 );
                        }
                        for ( ; v2820; --v2820 )
                          *v2778++ = 0;
                        v2824 = *((_DWORD *)v2513 + 585);
                        *((_DWORD *)v2513 + 585) = v2822;
                        if ( v2822 == 3 )
                        {
                          (*((void (__fastcall **)(__int64))v2513 + 109))(v2821);
                        }
                        else if ( (*((_DWORD *)v2513 + 612) & 0x10000000) != 0 || !v2822 )
                        {
                          (*((void (__fastcall **)(__int64))v2513 + 31))(v2821);
                        }
                        else
                        {
                          (*((void (__fastcall **)(__int64, _QWORD))v2513 + 69))(v2821 - 8, *(_QWORD *)(v2821 - 8));
                        }
                        *((_DWORD *)v2513 + 585) = v2824;
                      }
                      *((_DWORD *)v2513 + 612) &= ~4u;
                      v2793 = v3783;
                    }
                    ++*((_DWORD *)v2513 + 515);
                    v2804 = &v2513[v2792];
                    v2825 = v2804;
                    v2826 = 48;
                    v2827 = 6i64;
                    do
                    {
                      *v2825 = 0i64;
                      v2826 -= 8;
                      ++v2825;
                      --v2827;
                    }
                    while ( v2827 );
                    for ( ; v2826; --v2826 )
                    {
                      *(_BYTE *)v2825 = 0;
                      v2825 = (_QWORD *)((char *)v2825 + 1);
                    }
                    *(_DWORD *)v2804 = v2818;
                    *((_QWORD *)v2804 + 1) = v2817;
                    if ( v2793 == 7 )
                      sub_1403ED6CC(v2513, (char *)v2794 + 12, 92i64, v2804 + 24);
                    v2808 = 92;
                    *((_DWORD *)v2804 + 4) = 92;
                    v2828 = (char *)v2794 + 12;
                    *((_DWORD *)v2513 + 522) += 92;
                    v2829 = *((_DWORD *)v2513 + 517);
                    v2830 = *((_QWORD *)v2513 + 259);
                    if ( v2817 < v2794 + 13 )
                    {
                      do
                      {
                        _mm_prefetchnta(v2828);
                        v2828 += 64;
                      }
                      while ( v2828 < (char *)v2794 + 104 );
                    }
                    v2831 = 92;
                    v2832 = 11i64;
                    do
                    {
                      v2830 = __ROL8__(*v2817++ ^ v2830, v2829);
                      v2831 -= 8;
                      --v2832;
                    }
                    while ( v2832 );
                    for ( ; v2831; --v2831 )
                    {
                      v2833 = *(unsigned __int8 *)v2817;
                      v2817 = (_QWORD *)((char *)v2817 + 1);
                      v2830 = __ROL8__(v2833 ^ v2830, v2829);
                    }
                    for ( i65 = v2830; ; LODWORD(v2830) = i65 ^ v2830 )
                    {
                      i65 >>= 31;
                      if ( !i65 )
                        break;
                    }
                    v2816 = v2830 & 0x7FFFFFFF;
                  }
                  else
                  {
                    v2797 = 32;
                    if ( v2793 != 7 )
                      v2797 = 0;
                    if ( v2796 <= *((_DWORD *)v2778 + 647) )
                    {
                      v2513 = v2778;
                      *((_DWORD *)v2778 + 505) = v2796;
                    }
                    else
                    {
                      v2513 = (_BYTE *)sub_140B0F020(v2778, v2796, v2795);
                      if ( !v2513 )
                        goto LABEL_4028;
                      v2798 = *((_DWORD *)v2778 + 612);
                      if ( (v2798 & 4) == 0 )
                      {
                        v2799 = *((_DWORD *)v2778 + 505);
                        v2800 = *((_QWORD *)v2778 + 249);
                        v2801 = (v2798 & 0x20000000) != 0 ? *((_DWORD *)v2778 + 585) : 0;
                        if ( v2799 >= 8 )
                        {
                          v2802 = (unsigned __int64)v2799 >> 3;
                          do
                          {
                            *(_QWORD *)v2778 = 0i64;
                            v2799 -= 8;
                            v2778 += 8;
                            --v2802;
                          }
                          while ( v2802 );
                        }
                        for ( ; v2799; --v2799 )
                          *v2778++ = 0;
                        v2803 = *((_DWORD *)v2513 + 585);
                        *((_DWORD *)v2513 + 585) = v2801;
                        if ( v2801 == 3 )
                        {
                          (*((void (__fastcall **)(__int64))v2513 + 109))(v2800);
                        }
                        else if ( (*((_DWORD *)v2513 + 612) & 0x10000000) != 0 || !v2801 )
                        {
                          (*((void (__fastcall **)(__int64))v2513 + 31))(v2800);
                        }
                        else
                        {
                          (*((void (__fastcall **)(__int64, _QWORD))v2513 + 69))(v2800 - 8, *(_QWORD *)(v2800 - 8));
                        }
                        *((_DWORD *)v2513 + 585) = v2803;
                      }
                      *((_DWORD *)v2513 + 612) &= ~4u;
                      v2793 = v3783;
                    }
                    ++*((_DWORD *)v2513 + 515);
                    v2804 = &v2513[v2792];
                    v2805 = v2804;
                    v2806 = 48;
                    v2807 = 6i64;
                    do
                    {
                      *v2805 = 0i64;
                      v2806 -= 8;
                      ++v2805;
                      --v2807;
                    }
                    while ( v2807 );
                    for ( ; v2806; --v2806 )
                    {
                      *(_BYTE *)v2805 = 0;
                      v2805 = (_QWORD *)((char *)v2805 + 1);
                    }
                    *(_DWORD *)v2804 = v2797;
                    *((_QWORD *)v2804 + 1) = v2794;
                    if ( v2793 == 7 )
                      sub_1403ED6CC(v2513, v2794, 104i64, v2804 + 24);
                    v2808 = 104;
                    *((_DWORD *)v2804 + 4) = 104;
                    v2809 = (char *)v2794;
                    *((_DWORD *)v2513 + 522) += 104;
                    v2810 = *((_DWORD *)v2513 + 517);
                    v2811 = *((_QWORD *)v2513 + 259);
                    if ( v2794 < v2794 + 13 )
                    {
                      do
                      {
                        _mm_prefetchnta(v2809);
                        v2809 += 64;
                      }
                      while ( v2809 < (char *)v2794 + 104 );
                    }
                    v2812 = 104;
                    v2813 = 13i64;
                    do
                    {
                      v2811 = __ROL8__(*v2794++ ^ v2811, v2810);
                      v2812 -= 8;
                      --v2813;
                    }
                    while ( v2813 );
                    for ( ; v2812; --v2812 )
                    {
                      v2814 = *(unsigned __int8 *)v2794;
                      v2794 = (_QWORD *)((char *)v2794 + 1);
                      v2811 = __ROL8__(v2814 ^ v2811, v2810);
                    }
                    for ( i66 = v2811; ; LODWORD(v2811) = i66 ^ v2811 )
                    {
                      i66 >>= 31;
                      if ( !i66 )
                        break;
                    }
                    v2816 = v2811 & 0x7FFFFFFF;
                  }
                  *((_DWORD *)v2804 + 5) = v2816;
                  *((_DWORD *)v2513 + 522) += v2808;
LABEL_4096:
                  if ( !v2513 )
                  {
LABEL_4243:
                    v2513 = 0i64;
                    break;
                  }
                  if ( (v2513[2171] & 8) != 0 )
                  {
                    v2835 = 1;
                    LODWORD(v3783) = 1;
                    do
                    {
                      v2836 = *(_QWORD **)(*(_QWORD *)v3787 + 8i64 * v2835 + 28);
                      if ( v2836 )
                      {
                        v2837 = *((_DWORD *)v2513 + 526);
                        v2838 = 32;
                        v2839 = *((unsigned int *)v2513 + 505);
                        if ( v2837 != 7 )
                          v2838 = 0;
                        v2840 = v2839 + 48;
                        if ( (unsigned int)(v2839 + 48) <= *((_DWORD *)v2513 + 647) )
                        {
                          v2841 = v2513;
                          *((_DWORD *)v2513 + 505) = v2840;
                        }
                        else
                        {
                          v2841 = (_BYTE *)sub_140B0F020(v2513, v2840, *((_DWORD *)v2513 + 585));
                          if ( !v2841 )
                            goto LABEL_3638;
                          v2842 = *((_DWORD *)v2513 + 612);
                          if ( (v2842 & 4) == 0 )
                          {
                            v2843 = *((_DWORD *)v2513 + 505);
                            v2844 = *((_QWORD *)v2513 + 249);
                            v2845 = (v2842 & 0x20000000) != 0 ? *((_DWORD *)v2513 + 585) : 0;
                            if ( v2843 >= 8 )
                            {
                              v2846 = (unsigned __int64)v2843 >> 3;
                              do
                              {
                                *(_QWORD *)v2513 = 0i64;
                                v2843 -= 8;
                                v2513 += 8;
                                --v2846;
                              }
                              while ( v2846 );
                            }
                            for ( ; v2843; --v2843 )
                              *v2513++ = 0;
                            v2847 = *((_DWORD *)v2841 + 585);
                            *((_DWORD *)v2841 + 585) = v2845;
                            if ( v2845 == 3 )
                            {
                              (*((void (__fastcall **)(__int64))v2841 + 109))(v2844);
                            }
                            else if ( (*((_DWORD *)v2841 + 612) & 0x10000000) != 0 || !v2845 )
                            {
                              (*((void (__fastcall **)(__int64))v2841 + 31))(v2844);
                            }
                            else
                            {
                              (*((void (__fastcall **)(__int64, _QWORD))v2841 + 69))(v2844 - 8, *(_QWORD *)(v2844 - 8));
                            }
                            *((_DWORD *)v2841 + 585) = v2847;
                          }
                          *((_DWORD *)v2841 + 612) &= ~4u;
                        }
                        v2848 = &v2841[v2839];
                        ++*((_DWORD *)v2841 + 515);
                        v2849 = v2848;
                        v2850 = 48;
                        v2851 = 6i64;
                        do
                        {
                          *v2849 = 0i64;
                          v2850 -= 8;
                          ++v2849;
                          --v2851;
                        }
                        while ( v2851 );
                        for ( ; v2850; --v2850 )
                        {
                          *(_BYTE *)v2849 = 0;
                          v2849 = (_QWORD *)((char *)v2849 + 1);
                        }
                        *(_DWORD *)v2848 = v2838;
                        *((_QWORD *)v2848 + 1) = v2836;
                        if ( v2837 == 7 )
                          sub_1403ED6CC(v2841, v2836, 16i64, v2848 + 24);
                        *((_DWORD *)v2848 + 4) = 16;
                        *((_DWORD *)v2841 + 522) += 16;
                        v2852 = v2836;
                        v2853 = *((_DWORD *)v2841 + 517);
                        v2854 = (char *)v2836;
                        v2855 = *((_QWORD *)v2841 + 259);
                        if ( v2836 < v2836 + 2 )
                        {
                          do
                          {
                            _mm_prefetchnta(v2854);
                            v2854 += 64;
                          }
                          while ( v2854 < (char *)v2836 + 16 );
                        }
                        v2856 = 16;
                        v2857 = 2i64;
                        do
                        {
                          v2855 = __ROL8__(*v2852++ ^ v2855, v2853);
                          v2856 -= 8;
                          --v2857;
                        }
                        while ( v2857 );
                        for ( ; v2856; --v2856 )
                        {
                          v2858 = *(unsigned __int8 *)v2852;
                          v2852 = (_QWORD *)((char *)v2852 + 1);
                          v2855 = __ROL8__(v2858 ^ v2855, v2853);
                        }
                        for ( i67 = v2855 >> 31; i67; i67 >>= 31 )
                          LODWORD(v2855) = i67 ^ v2855;
                        v2860 = 32;
                        *((_DWORD *)v2848 + 5) = v2855 & 0x7FFFFFFF;
                        *((_DWORD *)v2841 + 522) += 16;
                        v2861 = (char *)v2836[1];
                        v2862 = *((unsigned int *)v2841 + 505);
                        v2863 = *((_DWORD *)v2841 + 526);
                        if ( v2863 != 7 )
                          v2860 = 0;
                        v2864 = v2862 + 48;
                        if ( (unsigned int)(v2862 + 48) <= *((_DWORD *)v2841 + 647) )
                        {
                          v2513 = v2841;
                          *((_DWORD *)v2841 + 505) = v2864;
                        }
                        else
                        {
                          v2513 = (_BYTE *)sub_140B0F020(v2841, v2864, *((_DWORD *)v2841 + 585));
                          if ( !v2513 )
                            goto LABEL_3638;
                          v2865 = *((_DWORD *)v2841 + 612);
                          if ( (v2865 & 4) == 0 )
                          {
                            v2866 = *((_DWORD *)v2841 + 505);
                            v2867 = *((_QWORD *)v2841 + 249);
                            v2868 = (v2865 & 0x20000000) != 0 ? *((_DWORD *)v2841 + 585) : 0;
                            if ( v2866 >= 8 )
                            {
                              v2869 = (unsigned __int64)v2866 >> 3;
                              do
                              {
                                *(_QWORD *)v2841 = 0i64;
                                v2866 -= 8;
                                v2841 += 8;
                                --v2869;
                              }
                              while ( v2869 );
                            }
                            for ( ; v2866; --v2866 )
                              *v2841++ = 0;
                            v2870 = *((_DWORD *)v2513 + 585);
                            *((_DWORD *)v2513 + 585) = v2868;
                            if ( v2868 == 3 )
                            {
                              (*((void (__fastcall **)(__int64))v2513 + 109))(v2867);
                            }
                            else if ( (*((_DWORD *)v2513 + 612) & 0x10000000) != 0 || !v2868 )
                            {
                              (*((void (__fastcall **)(__int64))v2513 + 31))(v2867);
                            }
                            else
                            {
                              (*((void (__fastcall **)(__int64, _QWORD))v2513 + 69))(v2867 - 8, *(_QWORD *)(v2867 - 8));
                            }
                            *((_DWORD *)v2513 + 585) = v2870;
                          }
                          *((_DWORD *)v2513 + 612) &= ~4u;
                        }
                        ++*((_DWORD *)v2513 + 515);
                        v2871 = &v2513[v2862];
                        v2872 = 48;
                        v2873 = &v2513[v2862];
                        v2874 = 6i64;
                        do
                        {
                          *v2873 = 0i64;
                          v2872 -= 8;
                          ++v2873;
                          --v2874;
                        }
                        while ( v2874 );
                        for ( ; v2872; --v2872 )
                        {
                          *(_BYTE *)v2873 = 0;
                          v2873 = (_QWORD *)((char *)v2873 + 1);
                        }
                        *(_DWORD *)v2871 = v2860;
                        *((_QWORD *)v2871 + 1) = v2861;
                        if ( v2863 == 7 )
                          sub_1403ED6CC(v2513, v2861, 8i64, v2871 + 24);
                        *((_DWORD *)v2871 + 4) = 8;
                        *((_DWORD *)v2513 + 522) += 8;
                        for ( i68 = v2861; i68 < v2861 + 8; i68 += 64 )
                          _mm_prefetchnta(i68);
                        v2876 = __ROL8__(*(_QWORD *)v2861 ^ *((_QWORD *)v2513 + 259), *((_DWORD *)v2513 + 517));
                        for ( i69 = v2876; ; LODWORD(v2876) = i69 ^ v2876 )
                        {
                          i69 >>= 31;
                          if ( !i69 )
                            break;
                        }
                        *((_DWORD *)v2871 + 5) = v2876 & 0x7FFFFFFF;
                        *((_DWORD *)v2513 + 522) += 8;
                      }
                      v2835 = v3783 + 1;
                      LODWORD(v3783) = v2835;
                    }
                    while ( v2835 < 8 );
                  }
                  v2878 = (char *)qword_140D81080;
                  if ( qword_140D81080 )
                  {
                    v2879 = *((_DWORD *)v2513 + 526);
                    v2880 = 32;
                    v2881 = *((unsigned int *)v2513 + 505);
                    if ( v2879 != 7 )
                      v2880 = 0;
                    v2882 = v2881 + 48;
                    if ( (unsigned int)(v2881 + 48) <= *((_DWORD *)v2513 + 647) )
                    {
                      v2883 = v2513;
                      *((_DWORD *)v2513 + 505) = v2882;
                    }
                    else
                    {
                      v2883 = (_BYTE *)sub_140B0F020(v2513, v2882, *((_DWORD *)v2513 + 585));
                      if ( !v2883 )
                        goto LABEL_3638;
                      v2884 = *((_DWORD *)v2513 + 612);
                      if ( (v2884 & 4) == 0 )
                      {
                        v2885 = *((_DWORD *)v2513 + 505);
                        v2886 = *((_QWORD *)v2513 + 249);
                        v2887 = (v2884 & 0x20000000) != 0 ? *((_DWORD *)v2513 + 585) : 0;
                        if ( v2885 >= 8 )
                        {
                          v2888 = (unsigned __int64)v2885 >> 3;
                          do
                          {
                            *(_QWORD *)v2513 = 0i64;
                            v2885 -= 8;
                            v2513 += 8;
                            --v2888;
                          }
                          while ( v2888 );
                        }
                        for ( ; v2885; --v2885 )
                          *v2513++ = 0;
                        v2889 = *((_DWORD *)v2883 + 585);
                        *((_DWORD *)v2883 + 585) = v2887;
                        if ( v2887 == 3 )
                        {
                          (*((void (__fastcall **)(__int64))v2883 + 109))(v2886);
                        }
                        else if ( (*((_DWORD *)v2883 + 612) & 0x10000000) != 0 || !v2887 )
                        {
                          (*((void (__fastcall **)(__int64))v2883 + 31))(v2886);
                        }
                        else
                        {
                          (*((void (__fastcall **)(__int64, _QWORD))v2883 + 69))(v2886 - 8, *(_QWORD *)(v2886 - 8));
                        }
                        *((_DWORD *)v2883 + 585) = v2889;
                      }
                      *((_DWORD *)v2883 + 612) &= ~4u;
                    }
                    v2890 = (ULONG_PTR)&v2883[v2881];
                    ++*((_DWORD *)v2883 + 515);
                    v2891 = (_QWORD *)v2890;
                    v3787 = v2890;
                    v2892 = 48;
                    v2893 = 6i64;
                    do
                    {
                      *v2891 = 0i64;
                      v2892 -= 8;
                      ++v2891;
                      --v2893;
                    }
                    while ( v2893 );
                    for ( ; v2892; --v2892 )
                    {
                      *(_BYTE *)v2891 = 0;
                      v2891 = (_QWORD *)((char *)v2891 + 1);
                    }
                    *(_DWORD *)v2890 = v2880;
                    *(_QWORD *)(v2890 + 8) = v2878;
                    if ( v2879 == 7 )
                      sub_1403ED6CC(v2883, v2878, 512i64, v2890 + 24);
                    *(_DWORD *)(v2890 + 16) = 512;
                    *((_DWORD *)v2883 + 522) += 512;
                    v2894 = v2878;
                    v2895 = *((_DWORD *)v2883 + 517);
                    v2896 = v2878;
                    for ( i70 = *((_QWORD *)v2883 + 259); v2896 < v2878 + 512; v2896 += 64 )
                      _mm_prefetchnta(v2896);
                    v2898 = 4;
                    v2899 = *((_QWORD *)v2883 + 259);
                    do
                    {
                      v2900 = 8i64;
                      do
                      {
                        v2901 = *((_QWORD *)v2894 + 1) ^ __ROL8__(*(_QWORD *)v2894 ^ v2899, v2895);
                        v2894 += 16;
                        v2899 = __ROL8__(v2901, v2895);
                        --v2900;
                      }
                      while ( v2900 );
                      v2902 = (__ROL8__(i70 ^ (v2894 - v2878), 17) ^ i70 ^ (unsigned __int64)(v2894 - v2878))
                            * (unsigned __int128)0x7010008004002001ui64;
                      v4044 = *((_QWORD *)&v2902 + 1);
                      v2895 = ((unsigned __int8)v2902 ^ (unsigned __int8)(BYTE8(v2902) ^ v2895)) & 0x3F;
                      if ( !v2895 )
                        LOBYTE(v2895) = 1;
                      --v2898;
                    }
                    while ( v2898 );
                    for ( i71 = v2899 >> 31; i71; i71 >>= 31 )
                      LODWORD(v2899) = i71 ^ v2899;
                    v2904 = 32;
                    *(_DWORD *)(v3787 + 20) = v2899 & 0x7FFFFFFF;
                    *((_DWORD *)v2883 + 522) += 512;
                    v2905 = *((unsigned int *)v2883 + 505);
                    v2906 = (char *)qword_140D81080 + 512;
                    v2907 = *((_DWORD *)v2883 + 526);
                    if ( v2907 != 7 )
                      v2904 = 0;
                    v2908 = v2905 + 48;
                    if ( (unsigned int)(v2905 + 48) <= *((_DWORD *)v2883 + 647) )
                    {
                      v2513 = v2883;
                      *((_DWORD *)v2883 + 505) = v2908;
                    }
                    else
                    {
                      v2513 = (_BYTE *)sub_140B0F020(v2883, v2908, *((_DWORD *)v2883 + 585));
                      if ( !v2513 )
                        goto LABEL_3638;
                      v2909 = *((_DWORD *)v2883 + 612);
                      if ( (v2909 & 4) == 0 )
                      {
                        v2910 = *((_DWORD *)v2883 + 505);
                        v2911 = *((_QWORD *)v2883 + 249);
                        v2912 = (v2909 & 0x20000000) != 0 ? *((_DWORD *)v2883 + 585) : 0;
                        if ( v2910 >= 8 )
                        {
                          v2913 = (unsigned __int64)v2910 >> 3;
                          do
                          {
                            *(_QWORD *)v2883 = 0i64;
                            v2910 -= 8;
                            v2883 += 8;
                            --v2913;
                          }
                          while ( v2913 );
                        }
                        for ( ; v2910; --v2910 )
                          *v2883++ = 0;
                        v2914 = *((_DWORD *)v2513 + 585);
                        *((_DWORD *)v2513 + 585) = v2912;
                        if ( v2912 == 3 )
                        {
                          (*((void (__fastcall **)(__int64))v2513 + 109))(v2911);
                        }
                        else if ( (*((_DWORD *)v2513 + 612) & 0x10000000) != 0 || !v2912 )
                        {
                          (*((void (__fastcall **)(__int64))v2513 + 31))(v2911);
                        }
                        else
                        {
                          (*((void (__fastcall **)(__int64, _QWORD))v2513 + 69))(v2911 - 8, *(_QWORD *)(v2911 - 8));
                        }
                        *((_DWORD *)v2513 + 585) = v2914;
                      }
                      *((_DWORD *)v2513 + 612) &= ~4u;
                    }
                    ++*((_DWORD *)v2513 + 515);
                    v2915 = (ULONG_PTR)&v2513[v2905];
                    v3787 = v2915;
                    v2916 = (_QWORD *)v2915;
                    v2917 = 48;
                    v2918 = 6i64;
                    do
                    {
                      *v2916 = 0i64;
                      v2917 -= 8;
                      ++v2916;
                      --v2918;
                    }
                    while ( v2918 );
                    for ( ; v2917; --v2917 )
                    {
                      *(_BYTE *)v2916 = 0;
                      v2916 = (_QWORD *)((char *)v2916 + 1);
                    }
                    *(_DWORD *)v2915 = v2904;
                    *(_QWORD *)(v2915 + 8) = v2906;
                    if ( v2907 == 7 )
                      sub_1403ED6CC(v2513, v2906, 512i64, v2915 + 24);
                    *(_DWORD *)(v2915 + 16) = 512;
                    *((_DWORD *)v2513 + 522) += 512;
                    v2919 = v2906;
                    v2920 = *((_DWORD *)v2513 + 517);
                    v2921 = v2906;
                    for ( i72 = *((_QWORD *)v2513 + 259); v2921 < v2906 + 512; v2921 += 64 )
                      _mm_prefetchnta(v2921);
                    v2923 = 4;
                    v2924 = *((_QWORD *)v2513 + 259);
                    do
                    {
                      v2925 = 8i64;
                      do
                      {
                        v2926 = *((_QWORD *)v2919 + 1) ^ __ROL8__(*(_QWORD *)v2919 ^ v2924, v2920);
                        v2919 += 16;
                        v2924 = __ROL8__(v2926, v2920);
                        --v2925;
                      }
                      while ( v2925 );
                      v2927 = (__ROL8__(i72 ^ (v2919 - v2906), 17) ^ i72 ^ (unsigned __int64)(v2919 - v2906))
                            * (unsigned __int128)0x7010008004002001ui64;
                      v4045 = *((_QWORD *)&v2927 + 1);
                      v2920 = ((unsigned __int8)v2927 ^ (unsigned __int8)(BYTE8(v2927) ^ v2920)) & 0x3F;
                      if ( !v2920 )
                        LOBYTE(v2920) = 1;
                      --v2923;
                    }
                    while ( v2923 );
                    for ( i73 = v2924; ; LODWORD(v2924) = i73 ^ v2924 )
                    {
                      i73 >>= 31;
                      if ( !i73 )
                        break;
                    }
                    *(_DWORD *)(v3787 + 20) = v2924 & 0x7FFFFFFF;
                    *((_DWORD *)v2513 + 522) += 512;
                  }
                  v2545 = v3784 + 1;
                  LODWORD(v3784) = v2545;
                }
                while ( v2545 < (unsigned int)KeNumberProcessors_0 );
              }
              
            }
LABEL_4241:
            v3981 = v2513;
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            if ( !v2513 )
              return 0;
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            v2929 = *((unsigned int *)v2513 + 505);
            v2930 = v2929 + 48;
            if ( (unsigned int)(v2929 + 48) <= *((_DWORD *)v2513 + 647) )
            {
              v2931 = v2513;
              *((_DWORD *)v2513 + 505) = v2930;
            }
            else
            {
              v2931 = (_BYTE *)sub_140B0F020(v2513, v2930, *((_DWORD *)v2513 + 585));
              if ( !v2931 )
                return 0;
              v2932 = *((_DWORD *)v2513 + 612);
              if ( (v2932 & 4) == 0 )
              {
                v2933 = *((_DWORD *)v2513 + 505);
                v2934 = *((_QWORD *)v2513 + 249);
                v2935 = (v2932 & 0x20000000) != 0 ? *((_DWORD *)v2513 + 585) : 0;
                if ( v2933 >= 8 )
                {
                  v2936 = (unsigned __int64)v2933 >> 3;
                  do
                  {
                    *(_QWORD *)v2513 = 0i64;
                    v2933 -= 8;
                    v2513 += 8;
                    --v2936;
                  }
                  while ( v2936 );
                }
                for ( ; v2933; --v2933 )
                  *v2513++ = 0;
                v2937 = *((_DWORD *)v2931 + 585);
                *((_DWORD *)v2931 + 585) = v2935;
                if ( v2935 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v2931 + 109))(v2934);
                }
                else if ( (*((_DWORD *)v2931 + 612) & 0x10000000) != 0 || !v2935 )
                {
                  (*((void (__fastcall **)(__int64))v2931 + 31))(v2934);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v2931 + 69))(v2934 - 8, *(_QWORD *)(v2934 - 8));
                }
                *((_DWORD *)v2931 + 585) = v2937;
              }
              *((_DWORD *)v2931 + 612) &= ~4u;
            }
            ++*((_DWORD *)v2931 + 515);
            v2938 = &v2931[v2929];
            v2939 = 48;
            v2940 = &v2931[v2929];
            v2941 = 6i64;
            do
            {
              *v2940 = 0i64;
              v2939 -= 8;
              ++v2940;
              --v2941;
            }
            while ( v2941 );
            for ( ; v2939; --v2939 )
            {
              *(_BYTE *)v2940 = 0;
              v2940 = (_QWORD *)((char *)v2940 + 1);
            }
            *(_DWORD *)v2938 = 26;
            *((_QWORD *)v2938 + 1) = 0i64;
            *((_DWORD *)v2938 + 4) = 0;
            v2942 = *((_QWORD *)v2931 + 259);
            for ( i74 = v2942; ; LODWORD(v2942) = i74 ^ v2942 )
            {
              i74 >>= 31;
              if ( !i74 )
                break;
            }
            v3981 = v2931;
            *((_DWORD *)v2938 + 5) = v2942 & 0x7FFFFFFF;
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            v2944 = *((unsigned int *)v2931 + 505);
            v2945 = v2944 + 48;
            if ( (unsigned int)(v2944 + 48) <= *((_DWORD *)v2931 + 647) )
            {
              v2946 = v2931;
              *((_DWORD *)v2931 + 505) = v2945;
            }
            else
            {
              v2946 = (_BYTE *)sub_140B0F020(v2931, v2945, *((_DWORD *)v2931 + 585));
              if ( !v2946 )
                return 0;
              v2947 = *((_DWORD *)v2931 + 612);
              if ( (v2947 & 4) == 0 )
              {
                v2948 = *((_DWORD *)v2931 + 505);
                v2949 = *((_QWORD *)v2931 + 249);
                v2950 = (v2947 & 0x20000000) != 0 ? *((_DWORD *)v2931 + 585) : 0;
                if ( v2948 >= 8 )
                {
                  v2951 = (unsigned __int64)v2948 >> 3;
                  do
                  {
                    *(_QWORD *)v2931 = 0i64;
                    v2948 -= 8;
                    v2931 += 8;
                    --v2951;
                  }
                  while ( v2951 );
                }
                for ( ; v2948; --v2948 )
                  *v2931++ = 0;
                v2952 = *((_DWORD *)v2946 + 585);
                *((_DWORD *)v2946 + 585) = v2950;
                if ( v2950 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v2946 + 109))(v2949);
                }
                else if ( (*((_DWORD *)v2946 + 612) & 0x10000000) != 0 || !v2950 )
                {
                  (*((void (__fastcall **)(__int64))v2946 + 31))(v2949);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v2946 + 69))(v2949 - 8, *(_QWORD *)(v2949 - 8));
                }
                *((_DWORD *)v2946 + 585) = v2952;
              }
              *((_DWORD *)v2946 + 612) &= ~4u;
            }
            ++*((_DWORD *)v2946 + 515);
            v2953 = &v2946[v2944];
            v2954 = &v2946[v2944];
            v2955 = 48;
            v2956 = 6i64;
            do
            {
              *v2954 = 0i64;
              v2955 -= 8;
              ++v2954;
              --v2956;
            }
            while ( v2956 );
            for ( ; v2955; --v2955 )
            {
              *(_BYTE *)v2954 = 0;
              v2954 = (_QWORD *)((char *)v2954 + 1);
            }
            *(_DWORD *)v2953 = 27;
            *((_QWORD *)v2953 + 1) = 0i64;
            *((_DWORD *)v2953 + 4) = 0;
            v2957 = *((_QWORD *)v2946 + 259);
            for ( i75 = v2957; ; LODWORD(v2957) = i75 ^ v2957 )
            {
              i75 >>= 31;
              if ( !i75 )
                break;
            }
            v3981 = v2946;
            *((_DWORD *)v2953 + 5) = v2957 & 0x7FFFFFFF;
            v2959 = 32;
            v2960 = *((unsigned int *)v2946 + 505);
            v2961 = *((_DWORD *)v2946 + 526);
            if ( v2961 != 7 )
              v2959 = 0;
            v2962 = v2960 + 48;
            if ( (unsigned int)(v2960 + 48) <= *((_DWORD *)v2946 + 647) )
            {
              v2963 = v2946;
              *((_DWORD *)v2946 + 505) = v2962;
            }
            else
            {
              v2963 = (_BYTE *)sub_140B0F020(v2946, v2962, *((_DWORD *)v2946 + 585));
              if ( !v2963 )
                return 0;
              v2964 = *((_DWORD *)v2946 + 612);
              if ( (v2964 & 4) == 0 )
              {
                v2965 = *((_DWORD *)v2946 + 505);
                v2966 = *((_QWORD *)v2946 + 249);
                v2967 = (v2964 & 0x20000000) != 0 ? *((_DWORD *)v2946 + 585) : 0;
                if ( v2965 >= 8 )
                {
                  v2968 = (unsigned __int64)v2965 >> 3;
                  do
                  {
                    *(_QWORD *)v2946 = 0i64;
                    v2965 -= 8;
                    v2946 += 8;
                    --v2968;
                  }
                  while ( v2968 );
                }
                for ( ; v2965; --v2965 )
                  *v2946++ = 0;
                v2969 = *((_DWORD *)v2963 + 585);
                *((_DWORD *)v2963 + 585) = v2967;
                if ( v2967 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v2963 + 109))(v2966);
                }
                else if ( (*((_DWORD *)v2963 + 612) & 0x10000000) != 0 || !v2967 )
                {
                  (*((void (__fastcall **)(__int64))v2963 + 31))(v2966);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v2963 + 69))(v2966 - 8, *(_QWORD *)(v2966 - 8));
                }
                *((_DWORD *)v2963 + 585) = v2969;
              }
              *((_DWORD *)v2963 + 612) &= ~4u;
            }
            ++*((_DWORD *)v2963 + 515);
            v2970 = &v2963[v2960];
            v2971 = 48;
            v2972 = &v2963[v2960];
            v2973 = 6i64;
            do
            {
              *v2972 = 0i64;
              v2971 -= 8;
              ++v2972;
              --v2973;
            }
            while ( v2973 );
            for ( ; v2971; --v2971 )
            {
              *(_BYTE *)v2972 = 0;
              v2972 = (_QWORD *)((char *)v2972 + 1);
            }
            *(_DWORD *)v2970 = v2959;
            *((_QWORD *)v2970 + 1) = &KiKvaShadow;
            if ( v2961 == 7 )
              sub_1403ED6CC(v2963, &KiKvaShadow, 1i64, v2970 + 24);
            *((_DWORD *)v2970 + 4) = 1;
            ++*((_DWORD *)v2963 + 522);
            _mm_prefetchnta(&KiKvaShadow);
            v2974 = __ROL8__(*((_QWORD *)v2963 + 259) ^ (unsigned __int8)KiKvaShadow, *((_DWORD *)v2963 + 517));
            for ( i76 = v2974; ; LODWORD(v2974) = i76 ^ v2974 )
            {
              i76 >>= 31;
              if ( !i76 )
                break;
            }
            v3981 = v2963;
            *((_DWORD *)v2970 + 5) = v2974 & 0x7FFFFFFF;
            ++*((_DWORD *)v2963 + 522);
            if ( (v2963[2171] & 8) != 0 )
            {
              _disable();
              if ( !(_BYTE)KdDebuggerNotPresent )
              {
                while ( 1 )
                  ;
              }
              _enable();
              v2976 = *((unsigned int *)v2963 + 505);
              v2977 = v2976 + 48;
              if ( (unsigned int)(v2976 + 48) <= *((_DWORD *)v2963 + 647) )
              {
                v2978 = (__int64)v2963;
                *((_DWORD *)v2963 + 505) = v2977;
              }
              else
              {
                v2978 = sub_140B0F020(v2963, v2977, *((_DWORD *)v2963 + 585));
                if ( !v2978 )
                  return 0;
                v2979 = *((_DWORD *)v2963 + 612);
                if ( (v2979 & 4) == 0 )
                {
                  v2980 = *((_DWORD *)v2963 + 505);
                  v2981 = *((_QWORD *)v2963 + 249);
                  v2982 = (v2979 & 0x20000000) != 0 ? *((_DWORD *)v2963 + 585) : 0;
                  if ( v2980 >= 8 )
                  {
                    v2983 = (unsigned __int64)v2980 >> 3;
                    do
                    {
                      *(_QWORD *)v2963 = 0i64;
                      v2980 -= 8;
                      v2963 += 8;
                      --v2983;
                    }
                    while ( v2983 );
                  }
                  for ( ; v2980; --v2980 )
                    *v2963++ = 0;
                  v2984 = *(_DWORD *)(v2978 + 2340);
                  *(_DWORD *)(v2978 + 2340) = v2982;
                  if ( v2982 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v2978 + 872))(v2981);
                  }
                  else if ( (*(_DWORD *)(v2978 + 2448) & 0x10000000) != 0 || !v2982 )
                  {
                    (*(void (__fastcall **)(__int64))(v2978 + 248))(v2981);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v2978 + 552))(v2981 - 8, *(_QWORD *)(v2981 - 8));
                  }
                  *(_DWORD *)(v2978 + 2340) = v2984;
                }
                *(_DWORD *)(v2978 + 2448) &= ~4u;
              }
              ++*(_DWORD *)(v2978 + 2060);
              v2985 = v2978 + v2976;
              v2986 = (_QWORD *)(v2978 + v2976);
              v2987 = 48;
              v2988 = 6i64;
              do
              {
                *v2986 = 0i64;
                v2987 -= 8;
                ++v2986;
                --v2988;
              }
              while ( v2988 );
              for ( ; v2987; --v2987 )
              {
                *(_BYTE *)v2986 = 0;
                v2986 = (_QWORD *)((char *)v2986 + 1);
              }
              *(_DWORD *)v2985 = 47;
              *(_QWORD *)(v2985 + 8) = 0i64;
              *(_DWORD *)(v2985 + 16) = 0;
              v2989 = *(_QWORD *)(v2978 + 2072);
              for ( i77 = v2989; ; LODWORD(v2989) = i77 ^ v2989 )
              {
                i77 >>= 31;
                if ( !i77 )
                  break;
              }
              v2963 = (_BYTE *)v2978;
              *(_DWORD *)(v2985 + 20) = v2989 & 0x7FFFFFFF;
              v3981 = (_BYTE *)v2978;
            }
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            v2991 = *((unsigned int *)v2963 + 505);
            v2992 = v2991 + 48;
            if ( (unsigned int)(v2991 + 48) <= *((_DWORD *)v2963 + 647) )
            {
              v2993 = v2963;
              *((_DWORD *)v2963 + 505) = v2992;
            }
            else
            {
              v2993 = (_BYTE *)sub_140B0F020(v2963, v2992, *((_DWORD *)v2963 + 585));
              if ( !v2993 )
                return 0;
              v2994 = *((_DWORD *)v2963 + 612);
              if ( (v2994 & 4) == 0 )
              {
                v2995 = *((_DWORD *)v2963 + 505);
                v2996 = *((_QWORD *)v2963 + 249);
                v2997 = (v2994 & 0x20000000) != 0 ? *((_DWORD *)v2963 + 585) : 0;
                if ( v2995 >= 8 )
                {
                  v2998 = (unsigned __int64)v2995 >> 3;
                  do
                  {
                    *(_QWORD *)v2963 = 0i64;
                    v2995 -= 8;
                    v2963 += 8;
                    --v2998;
                  }
                  while ( v2998 );
                }
                for ( ; v2995; --v2995 )
                  *v2963++ = 0;
                v2999 = *((_DWORD *)v2993 + 585);
                *((_DWORD *)v2993 + 585) = v2997;
                if ( v2997 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v2993 + 109))(v2996);
                }
                else if ( (*((_DWORD *)v2993 + 612) & 0x10000000) != 0 || !v2997 )
                {
                  (*((void (__fastcall **)(__int64))v2993 + 31))(v2996);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v2993 + 69))(v2996 - 8, *(_QWORD *)(v2996 - 8));
                }
                *((_DWORD *)v2993 + 585) = v2999;
              }
              *((_DWORD *)v2993 + 612) &= ~4u;
            }
            ++*((_DWORD *)v2993 + 515);
            v3000 = &v2993[v2991];
            v3001 = &v2993[v2991];
            v3002 = 48;
            v3003 = 6i64;
            do
            {
              *v3001 = 0i64;
              v3002 -= 8;
              ++v3001;
              --v3003;
            }
            while ( v3003 );
            for ( ; v3002; --v3002 )
            {
              *(_BYTE *)v3001 = 0;
              v3001 = (_QWORD *)((char *)v3001 + 1);
            }
            *(_DWORD *)v3000 = 46;
            *((_QWORD *)v3000 + 1) = 0i64;
            *((_DWORD *)v3000 + 4) = 0;
            v3004 = *((_QWORD *)v2993 + 259);
            for ( i78 = v3004; ; LODWORD(v3004) = i78 ^ v3004 )
            {
              i78 >>= 31;
              if ( !i78 )
                break;
            }
            v3981 = v2993;
            *((_DWORD *)v3000 + 5) = v3004 & 0x7FFFFFFF;
            if ( (__29 & 2) != 0 )
            {
              v3006 = 32;
              *(_QWORD *)(*((_QWORD *)v2993 + 248) + *((_QWORD *)v2993 + 199)) = 0i64;
              v3007 = (char *)(*((_QWORD *)v2993 + 199) + *((_QWORD *)v2993 + 248));
              v3008 = *((unsigned int *)v2993 + 505);
              v3009 = *((_DWORD *)v2993 + 526);
              if ( v3009 != 7 )
                v3006 = 0;
              v3010 = v3008 + 48;
              if ( (unsigned int)(v3008 + 48) <= *((_DWORD *)v2993 + 647) )
              {
                v3011 = (__int64)v2993;
                *((_DWORD *)v2993 + 505) = v3010;
              }
              else
              {
                v3011 = sub_140B0F020(v2993, v3010, *((_DWORD *)v2993 + 585));
                if ( !v3011 )
                  return 0;
                v3012 = *((_DWORD *)v2993 + 612);
                if ( (v3012 & 4) == 0 )
                {
                  v3013 = *((_DWORD *)v2993 + 505);
                  v3014 = *((_QWORD *)v2993 + 249);
                  v3015 = (v3012 & 0x20000000) != 0 ? *((_DWORD *)v2993 + 585) : 0;
                  if ( v3013 >= 8 )
                  {
                    v3016 = (unsigned __int64)v3013 >> 3;
                    do
                    {
                      *(_QWORD *)v2993 = 0i64;
                      v3013 -= 8;
                      v2993 += 8;
                      --v3016;
                    }
                    while ( v3016 );
                  }
                  for ( ; v3013; --v3013 )
                    *v2993++ = 0;
                  v3017 = *(_DWORD *)(v3011 + 2340);
                  *(_DWORD *)(v3011 + 2340) = v3015;
                  if ( v3015 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v3011 + 872))(v3014);
                  }
                  else if ( (*(_DWORD *)(v3011 + 2448) & 0x10000000) != 0 || !v3015 )
                  {
                    (*(void (__fastcall **)(__int64))(v3011 + 248))(v3014);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v3011 + 552))(v3014 - 8, *(_QWORD *)(v3014 - 8));
                  }
                  *(_DWORD *)(v3011 + 2340) = v3017;
                }
                *(_DWORD *)(v3011 + 2448) &= ~4u;
              }
              ++*(_DWORD *)(v3011 + 2060);
              v3018 = v3011 + v3008;
              v3019 = 48;
              v3020 = (_QWORD *)(v3011 + v3008);
              v3021 = 6i64;
              do
              {
                *v3020 = 0i64;
                v3019 -= 8;
                ++v3020;
                --v3021;
              }
              while ( v3021 );
              for ( ; v3019; --v3019 )
              {
                *(_BYTE *)v3020 = 0;
                v3020 = (_QWORD *)((char *)v3020 + 1);
              }
              *(_DWORD *)v3018 = v3006;
              *(_QWORD *)(v3018 + 8) = v3007;
              if ( v3009 == 7 )
                sub_1403ED6CC(v3011, v3007, 8i64, v3018 + 24);
              *(_DWORD *)(v3018 + 16) = 8;
              *(_DWORD *)(v3011 + 2088) += 8;
              for ( i79 = v3007; i79 < v3007 + 8; i79 += 64 )
                _mm_prefetchnta(i79);
              v3023 = __ROL8__(*(_QWORD *)v3007 ^ *(_QWORD *)(v3011 + 2072), *(_DWORD *)(v3011 + 2068));
              for ( i80 = v3023; ; LODWORD(v3023) = i80 ^ v3023 )
              {
                i80 >>= 31;
                if ( !i80 )
                  break;
              }
              v3981 = (_BYTE *)v3011;
              *(_DWORD *)(v3018 + 20) = v3023 & 0x7FFFFFFF;
              v2993 = (_BYTE *)v3011;
              *(_DWORD *)(v3011 + 2088) += 8;
            }
            if ( (__29 & 4) != 0 )
            {
              v3025 = 32;
              *(_QWORD *)(*((_QWORD *)v2993 + 248) + 128i64) = 0i64;
              v3026 = *((unsigned int *)v2993 + 505);
              v3027 = (char *)(*((_QWORD *)v2993 + 248) + 128i64);
              v3028 = *((_DWORD *)v2993 + 526);
              if ( v3028 != 7 )
                v3025 = 0;
              v3029 = v3026 + 48;
              if ( (unsigned int)(v3026 + 48) <= *((_DWORD *)v2993 + 647) )
              {
                v3030 = (__int64)v2993;
                *((_DWORD *)v2993 + 505) = v3029;
              }
              else
              {
                v3030 = sub_140B0F020(v2993, v3029, *((_DWORD *)v2993 + 585));
                if ( !v3030 )
                  return 0;
                v3031 = *((_DWORD *)v2993 + 612);
                if ( (v3031 & 4) == 0 )
                {
                  v3032 = *((_DWORD *)v2993 + 505);
                  v3033 = *((_QWORD *)v2993 + 249);
                  v3034 = (v3031 & 0x20000000) != 0 ? *((_DWORD *)v2993 + 585) : 0;
                  if ( v3032 >= 8 )
                  {
                    v3035 = (unsigned __int64)v3032 >> 3;
                    do
                    {
                      *(_QWORD *)v2993 = 0i64;
                      v3032 -= 8;
                      v2993 += 8;
                      --v3035;
                    }
                    while ( v3035 );
                  }
                  for ( ; v3032; --v3032 )
                    *v2993++ = 0;
                  v3036 = *(_DWORD *)(v3030 + 2340);
                  *(_DWORD *)(v3030 + 2340) = v3034;
                  if ( v3034 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v3030 + 872))(v3033);
                  }
                  else if ( (*(_DWORD *)(v3030 + 2448) & 0x10000000) != 0 || !v3034 )
                  {
                    (*(void (__fastcall **)(__int64))(v3030 + 248))(v3033);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v3030 + 552))(v3033 - 8, *(_QWORD *)(v3033 - 8));
                  }
                  *(_DWORD *)(v3030 + 2340) = v3036;
                }
                *(_DWORD *)(v3030 + 2448) &= ~4u;
              }
              ++*(_DWORD *)(v3030 + 2060);
              v3037 = v3030 + v3026;
              v3038 = 48;
              v3039 = (_QWORD *)(v3030 + v3026);
              v3040 = 6i64;
              do
              {
                *v3039 = 0i64;
                v3038 -= 8;
                ++v3039;
                --v3040;
              }
              while ( v3040 );
              for ( ; v3038; --v3038 )
              {
                *(_BYTE *)v3039 = 0;
                v3039 = (_QWORD *)((char *)v3039 + 1);
              }
              *(_DWORD *)v3037 = v3025;
              *(_QWORD *)(v3037 + 8) = v3027;
              if ( v3028 == 7 )
                sub_1403ED6CC(v3030, v3027, 8i64, v3037 + 24);
              *(_DWORD *)(v3037 + 16) = 8;
              *(_DWORD *)(v3030 + 2088) += 8;
              for ( i81 = v3027; i81 < v3027 + 8; i81 += 64 )
                _mm_prefetchnta(i81);
              v3042 = __ROL8__(*(_QWORD *)v3027 ^ *(_QWORD *)(v3030 + 2072), *(_DWORD *)(v3030 + 2068));
              for ( i82 = v3042; ; LODWORD(v3042) = i82 ^ v3042 )
              {
                i82 >>= 31;
                if ( !i82 )
                  break;
              }
              v3981 = (_BYTE *)v3030;
              *(_DWORD *)(v3037 + 20) = v3042 & 0x7FFFFFFF;
              v2993 = (_BYTE *)v3030;
              *(_DWORD *)(v3030 + 2088) += 8;
            }
            v3044 = *((unsigned int *)v2993 + 505);
            v3045 = 32;
            v3046 = *((_DWORD *)v2993 + 526);
            if ( v3046 != 7 )
              v3045 = 0;
            v3047 = v3044 + 48;
            if ( (unsigned int)(v3044 + 48) <= *((_DWORD *)v2993 + 647) )
            {
              v3048 = v2993;
              *((_DWORD *)v2993 + 505) = v3047;
            }
            else
            {
              v3048 = (_BYTE *)sub_140B0F020(v2993, v3047, *((_DWORD *)v2993 + 585));
              if ( !v3048 )
                return 0;
              v3049 = *((_DWORD *)v2993 + 612);
              if ( (v3049 & 4) == 0 )
              {
                v3050 = *((_DWORD *)v2993 + 505);
                v3051 = *((_QWORD *)v2993 + 249);
                v3052 = (v3049 & 0x20000000) != 0 ? *((_DWORD *)v2993 + 585) : 0;
                if ( v3050 >= 8 )
                {
                  v3053 = (unsigned __int64)v3050 >> 3;
                  do
                  {
                    *(_QWORD *)v2993 = 0i64;
                    v3050 -= 8;
                    v2993 += 8;
                    --v3053;
                  }
                  while ( v3053 );
                }
                for ( ; v3050; --v3050 )
                  *v2993++ = 0;
                v3054 = *((_DWORD *)v3048 + 585);
                *((_DWORD *)v3048 + 585) = v3052;
                if ( v3052 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v3048 + 109))(v3051);
                }
                else if ( (*((_DWORD *)v3048 + 612) & 0x10000000) != 0 || !v3052 )
                {
                  (*((void (__fastcall **)(__int64))v3048 + 31))(v3051);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v3048 + 69))(v3051 - 8, *(_QWORD *)(v3051 - 8));
                }
                *((_DWORD *)v3048 + 585) = v3054;
              }
              *((_DWORD *)v3048 + 612) &= ~4u;
            }
            ++*((_DWORD *)v3048 + 515);
            v3055 = 48;
            v3056 = (ULONG_PTR)&v3048[v3044];
            HalExtensionList = v3056;
            v3057 = (_QWORD *)v3056;
            v3058 = 6i64;
            do
            {
              *v3057 = 0i64;
              v3055 -= 8;
              ++v3057;
              --v3058;
            }
            while ( v3058 );
            for ( ; v3055; --v3055 )
            {
              *(_BYTE *)v3057 = 0;
              v3057 = (_QWORD *)((char *)v3057 + 1);
            }
            *(_DWORD *)v3056 = v3045;
            *(_QWORD *)(v3056 + 8) = &_ti_a;
            if ( v3046 == 7 )
              sub_1403ED6CC(v3048, &_ti_a, 328i64, v3056 + 24);
            *(_DWORD *)(v3056 + 16) = 328;
            v3059 = (unsigned __int64)&_ti_a;
            *((_DWORD *)v3048 + 522) += 328;
            v3060 = &_ti_a;
            v3061 = *((_DWORD *)v3048 + 517);
            v3062 = *((_QWORD *)v3048 + 259);
            do
            {
              _mm_prefetchnta(v3060);
              v3060 += 8;
            }
            while ( v3060 < &qword_14003F868 );
            v3063 = *((_QWORD *)v3048 + 259);
            v3064 = 2;
            do
            {
              v3065 = 8i64;
              do
              {
                v3066 = *(_QWORD *)(v3059 + 8) ^ __ROL8__(*(_QWORD *)v3059 ^ v3063, v3061);
                v3059 += 16i64;
                v3063 = __ROL8__(v3066, v3061);
                --v3065;
              }
              while ( v3065 );
              v3067 = (__ROL8__(v3062 ^ (v3059 - (_QWORD)&_ti_a), 17) ^ v3062 ^ (v3059 - (unsigned __int64)&_ti_a))
                    * (unsigned __int128)0x7010008004002001ui64;
              v4046 = *((_QWORD *)&v3067 + 1);
              v3061 = ((unsigned __int8)v3067 ^ (unsigned __int8)(BYTE8(v3067) ^ v3061)) & 0x3F;
              if ( !v3061 )
                LOBYTE(v3061) = 1;
              --v3064;
            }
            while ( v3064 );
            *(_QWORD *)&v3068 = 9i64;
            DWORD2(v3068) = 72;
            do
            {
              v3063 = __ROL8__(*(_QWORD *)v3059 ^ v3063, v3061);
              v3059 += 8i64;
              *((_QWORD *)&v3068 + 1) = (unsigned int)(DWORD2(v3068) - 8);
              *(_QWORD *)&v3068 = v3068 - 1;
            }
            while ( (_QWORD)v3068 );
            if ( DWORD2(v3068) )
            {
              do
              {
                *(_QWORD *)&v3068 = *(unsigned __int8 *)v3059++;
                v3063 = __ROL8__(v3068 ^ v3063, v3061);
                v875 = DWORD2(v3068) == 1;
                *((_QWORD *)&v3068 + 1) = (unsigned int)(DWORD2(v3068) - 1);
              }
              while ( !v875 );
            }
            for ( i83 = v3063; ; LODWORD(v3063) = i83 ^ v3063 )
            {
              i83 >>= 31;
              if ( !i83 )
                break;
            }
            v3981 = v3048;
            *(_DWORD *)(HalExtensionList + 20) = v3063 & 0x7FFFFFFF;
            *((_DWORD *)v3048 + 522) += 328;
            v875 = (*((_DWORD *)v3048 + 612) & 0x40000000) == 0;
            LODWORD(Src) = 0;
            LODWORD(v3784) = 0;
            if ( v875 )
            {
              v3070 = *((unsigned int *)v3048 + 505);
              v3071 = v3801;
              v3072 = *((unsigned int *)v3048 + 585);
              v3073 = *((_DWORD *)v3048 + 505) - v3801;
              LODWORD(Src) = v3070;
              v3074 = v3070 + 48;
              if ( (unsigned int)(v3070 + 48) <= *((_DWORD *)v3048 + 647) )
              {
                v3075 = (__int64)v3048;
                *((_DWORD *)v3048 + 505) = v3074;
              }
              else
              {
                v3075 = sub_140B0F020(v3048, v3074, v3072);
                if ( !v3075 )
                  return 0;
                v3076 = *((_DWORD *)v3048 + 612);
                if ( (v3076 & 4) == 0 )
                {
                  v3077 = *((_DWORD *)v3048 + 505);
                  v3078 = *((_QWORD *)v3048 + 249);
                  v3079 = (v3076 & 0x20000000) != 0 ? *((_DWORD *)v3048 + 585) : 0;
                  if ( v3077 >= 8 )
                  {
                    v3080 = (unsigned __int64)v3077 >> 3;
                    do
                    {
                      *(_QWORD *)v3048 = 0i64;
                      v3077 -= 8;
                      v3048 += 8;
                      --v3080;
                    }
                    while ( v3080 );
                  }
                  for ( ; v3077; --v3077 )
                    *v3048++ = 0;
                  v3081 = *(_DWORD *)(v3075 + 2340);
                  *(_DWORD *)(v3075 + 2340) = v3079;
                  if ( v3079 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v3075 + 872))(v3078);
                  }
                  else if ( (*(_DWORD *)(v3075 + 2448) & 0x10000000) != 0 || !v3079 )
                  {
                    (*(void (__fastcall **)(__int64))(v3075 + 248))(v3078);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v3075 + 552))(v3078 - 8, *(_QWORD *)(v3078 - 8));
                  }
                  *(_DWORD *)(v3075 + 2340) = v3081;
                }
                *(_DWORD *)(v3075 + 2448) &= ~4u;
                v3071 = v3801;
              }
              ++*(_DWORD *)(v3075 + 2060);
              v3082 = v3075 + v3070;
              v3083 = 48;
              HalExtensionList = v3075 + v3070;
              *(_QWORD *)&v3068 = v3075 + v3070;
              *((_QWORD *)&v3068 + 1) = 6i64;
              do
              {
                *(_QWORD *)v3068 = 0i64;
                v3083 -= 8;
                *(_QWORD *)&v3068 = v3068 + 8;
                --*((_QWORD *)&v3068 + 1);
              }
              while ( *((_QWORD *)&v3068 + 1) );
              for ( ; v3083; --v3083 )
              {
                *(_BYTE *)v3068 = 0;
                *(_QWORD *)&v3068 = v3068 + 1;
              }
              *(_DWORD *)v3082 = 42;
              *(_QWORD *)(v3082 + 8) = 0i64;
              *(_DWORD *)(v3082 + 16) = 0;
              v3084 = *(_QWORD *)(v3075 + 2072);
              for ( i84 = v3084; ; LODWORD(v3084) = i84 ^ v3084 )
              {
                i84 >>= 31;
                if ( !i84 )
                  break;
              }
              *(_DWORD *)(v3082 + 20) = v3084 & 0x7FFFFFFF;
              v3086 = (char *)(v3075 + v3071);
              *(_DWORD *)(v3082 + 32) = v3071;
              v3059 = (unsigned __int64)v3086;
              *(_DWORD *)(v3082 + 36) = v3073;
              v3087 = v3086;
              *(_DWORD *)(v3075 + 2088) += v3073;
              v3088 = *(_DWORD *)(v3075 + 2068);
              v3089 = *(_QWORD *)(v3075 + 2072);
              v3090 = (unsigned __int64)&v3086[v3073];
              if ( (unsigned __int64)v3086 < v3090 )
              {
                do
                {
                  _mm_prefetchnta(v3087);
                  v3087 += 64;
                }
                while ( (unsigned __int64)v3087 < v3090 );
              }
              v3091 = *(_QWORD *)(v3075 + 2072);
              v3092 = v3073 >> 7;
              if ( v3073 >> 7 )
              {
                do
                {
                  v3093 = 8i64;
                  do
                  {
                    v3094 = *(_QWORD *)(v3059 + 8) ^ __ROL8__(*(_QWORD *)v3059 ^ v3091, v3088);
                    v3059 += 16i64;
                    v3091 = __ROL8__(v3094, v3088);
                    --v3093;
                  }
                  while ( v3093 );
                  v3068 = (__ROL8__(v3089 ^ (v3059 - (_QWORD)v3086), 17) ^ v3089 ^ (v3059 - (unsigned __int64)v3086))
                        * (unsigned __int128)0x7010008004002001ui64;
                  v4047 = *((_QWORD *)&v3068 + 1);
                  v3088 = ((unsigned __int8)v3068 ^ (unsigned __int8)(BYTE8(v3068) ^ v3088)) & 0x3F;
                  if ( !v3088 )
                    LOBYTE(v3088) = 1;
                  --v3092;
                }
                while ( v3092 );
                v3082 = HalExtensionList;
              }
              v3095 = v3073 & 0x7F;
              if ( v3095 >= 8 )
              {
                v3096 = (unsigned __int64)v3095 >> 3;
                do
                {
                  v3091 = __ROL8__(*(_QWORD *)v3059 ^ v3091, v3088);
                  v3059 += 8i64;
                  v3095 -= 8;
                  --v3096;
                }
                while ( v3096 );
              }
              for ( ; v3095; --v3095 )
              {
                v3097 = *(unsigned __int8 *)v3059++;
                v3091 = __ROL8__(v3097 ^ v3091, v3088);
              }
              *(_QWORD *)(v3082 + 24) = v3091;
              v3048 = (_BYTE *)v3075;
              v3098 = *(_DWORD *)(v3075 + 2020);
              v3981 = (_BYTE *)v3075;
              LODWORD(v3784) = v3098;
            }
            for ( i85 = 0; i85 < 2; ++i85 )
            {
              v3100 = 0i64;
              _disable();
              v3101 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + *((_QWORD *)v3048 + 202));
              _enable();
              (*((void (__fastcall **)(__int64, _QWORD, unsigned __int64))v3048 + 45))(
                v3101,
                *((_QWORD *)&v3068 + 1),
                v3059);
              LOBYTE(v3102) = 1;
              (*((void (__fastcall **)(_QWORD, __int64))v3048 + 28))(*((_QWORD *)v3048 + 166), v3102);
              v3103 = (PVOID *)PsLoadedModuleList;
              if ( PsLoadedModuleList != &PsLoadedModuleList )
              {
                while ( 1 )
                {
                  v3104 = (char *)v3103 - *((_QWORD *)v3048 + 234);
                  if ( RtlEqualUnicodeString(
                         (PCUNICODE_STRING)&unk_140C00208 + i85,
                         (PCUNICODE_STRING)&v3104[*((_QWORD *)v3048 + 237)],
                         1u) )
                  {
                    break;
                  }
                  v3103 = (PVOID *)*v3103;
                  if ( v3103 == &PsLoadedModuleList )
                    goto LABEL_4529;
                }
                v3100 = *(_QWORD *)&v3104[*((_QWORD *)v3048 + 235)];
              }
LABEL_4529:
              (*((void (__fastcall **)(_QWORD))v3048 + 35))(*((_QWORD *)v3048 + 166));
              (*((void (**)(void))v3048 + 46))();
              if ( v3100 )
              {
                v3105 = *((unsigned int *)v3048 + 505);
                v3059 = *((unsigned int *)v3048 + 585);
                v3106 = &asc_140C00228[8 * i85];
                v3107 = v3105 + ((*v3106 + 7) & 0xFFFFFFF8) + 48;
                if ( v3107 <= *((_DWORD *)v3048 + 647) )
                {
                  v3108 = (__int64)v3048;
                  *((_DWORD *)v3048 + 505) = v3107;
                }
                else
                {
                  v3108 = sub_140B0F020(v3048, v3107, v3059);
                  if ( !v3108 )
                    return 0;
                  v3109 = *((_DWORD *)v3048 + 612);
                  if ( (v3109 & 4) == 0 )
                  {
                    v3110 = *((_DWORD *)v3048 + 505);
                    v3111 = *((_QWORD *)v3048 + 249);
                    v3112 = (v3109 & 0x20000000) != 0 ? *((_DWORD *)v3048 + 585) : 0;
                    if ( v3110 >= 8 )
                    {
                      v3113 = (unsigned __int64)v3110 >> 3;
                      do
                      {
                        *(_QWORD *)v3048 = 0i64;
                        v3110 -= 8;
                        v3048 += 8;
                        --v3113;
                      }
                      while ( v3113 );
                    }
                    for ( ; v3110; --v3110 )
                      *v3048++ = 0;
                    v3114 = *(_DWORD *)(v3108 + 2340);
                    *(_DWORD *)(v3108 + 2340) = v3112;
                    if ( v3112 == 3 )
                    {
                      (*(void (__fastcall **)(__int64))(v3108 + 872))(v3111);
                    }
                    else if ( (*(_DWORD *)(v3108 + 2448) & 0x10000000) != 0 || !v3112 )
                    {
                      (*(void (__fastcall **)(__int64))(v3108 + 248))(v3111);
                    }
                    else
                    {
                      (*(void (__fastcall **)(__int64, _QWORD))(v3108 + 552))(v3111 - 8, *(_QWORD *)(v3111 - 8));
                    }
                    *(_DWORD *)(v3108 + 2340) = v3114;
                  }
                  *(_DWORD *)(v3108 + 2448) &= ~4u;
                }
                v3115 = v3108 + v3105;
                ++*(_DWORD *)(v3108 + 2060);
                v3116 = (_QWORD *)(v3108 + v3105);
                v3117 = 48;
                v3118 = 6i64;
                do
                {
                  *v3116 = 0i64;
                  v3117 -= 8;
                  ++v3116;
                  --v3118;
                }
                while ( v3118 );
                for ( ; v3117; --v3117 )
                {
                  *(_BYTE *)v3116 = 0;
                  v3116 = (_QWORD *)((char *)v3116 + 1);
                }
                *(_DWORD *)v3115 = 28;
                *(_QWORD *)(v3115 + 8) = 0i64;
                *(_DWORD *)(v3115 + 16) = 0;
                v3119 = *(_QWORD *)(v3108 + 2072);
                for ( i86 = v3119; ; LODWORD(v3119) = i86 ^ v3119 )
                {
                  i86 >>= 31;
                  if ( !i86 )
                    break;
                }
                v3121 = (char *)(v3115 + 48);
                *(_DWORD *)(v3115 + 20) = v3119 & 0x7FFFFFFF;
                *(_QWORD *)(v3115 + 24) = v3100;
                *(_WORD *)(v3115 + 40) = *v3106;
                *((_QWORD *)&v3068 + 1) = *v3106;
                v3122 = (_QWORD *)*((_QWORD *)v3106 + 1);
                if ( DWORD2(v3068) >= 8 )
                {
                  v3059 = (unsigned __int64)*v3106 >> 3;
                  do
                  {
                    *((_QWORD *)&v3068 + 1) = (unsigned int)(DWORD2(v3068) - 8);
                    *(_QWORD *)v3121 = *v3122++;
                    v3121 += 8;
                    --v3059;
                  }
                  while ( v3059 );
                }
                if ( DWORD2(v3068) )
                {
                  v3123 = v3121 - (char *)v3122;
                  do
                  {
                    *((_BYTE *)v3122 + v3123) = *(_BYTE *)v3122;
                    v3122 = (_QWORD *)((char *)v3122 + 1);
                    v875 = DWORD2(v3068) == 1;
                    *((_QWORD *)&v3068 + 1) = (unsigned int)(DWORD2(v3068) - 1);
                  }
                  while ( !v875 );
                }
                v3048 = (_BYTE *)v3108;
              }
            }
            v3981 = v3048;
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            v3124 = *((unsigned int *)v3048 + 505);
            v3125 = v3124 + 48;
            if ( (unsigned int)(v3124 + 48) <= *((_DWORD *)v3048 + 647) )
            {
              v3126 = v3048;
              *((_DWORD *)v3048 + 505) = v3125;
            }
            else
            {
              v3126 = (_BYTE *)sub_140B0F020(v3048, v3125, *((_DWORD *)v3048 + 585));
              if ( !v3126 )
                return 0;
              v3127 = *((_DWORD *)v3048 + 612);
              if ( (v3127 & 4) == 0 )
              {
                v3128 = *((_DWORD *)v3048 + 505);
                v3129 = *((_QWORD *)v3048 + 249);
                v3130 = (v3127 & 0x20000000) != 0 ? *((_DWORD *)v3048 + 585) : 0;
                if ( v3128 >= 8 )
                {
                  v3131 = (unsigned __int64)v3128 >> 3;
                  do
                  {
                    *(_QWORD *)v3048 = 0i64;
                    v3128 -= 8;
                    v3048 += 8;
                    --v3131;
                  }
                  while ( v3131 );
                }
                for ( ; v3128; --v3128 )
                  *v3048++ = 0;
                v3132 = *((_DWORD *)v3126 + 585);
                *((_DWORD *)v3126 + 585) = v3130;
                if ( v3130 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v3126 + 109))(v3129);
                }
                else if ( (*((_DWORD *)v3126 + 612) & 0x10000000) != 0 || !v3130 )
                {
                  (*((void (__fastcall **)(__int64))v3126 + 31))(v3129);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v3126 + 69))(v3129 - 8, *(_QWORD *)(v3129 - 8));
                }
                *((_DWORD *)v3126 + 585) = v3132;
              }
              *((_DWORD *)v3126 + 612) &= ~4u;
            }
            ++*((_DWORD *)v3126 + 515);
            v3133 = &v3126[v3124];
            v3134 = 48;
            v3135 = &v3126[v3124];
            v3136 = 6i64;
            do
            {
              *v3135 = 0i64;
              v3134 -= 8;
              ++v3135;
              --v3136;
            }
            while ( v3136 );
            for ( ; v3134; --v3134 )
            {
              *(_BYTE *)v3135 = 0;
              v3135 = (_QWORD *)((char *)v3135 + 1);
            }
            *(_DWORD *)v3133 = 24;
            *((_QWORD *)v3133 + 1) = 0i64;
            *((_DWORD *)v3133 + 4) = 0;
            v3137 = *((_QWORD *)v3126 + 259);
            for ( i87 = v3137; ; LODWORD(v3137) = i87 ^ v3137 )
            {
              i87 >>= 31;
              if ( !i87 )
                break;
            }
            v3981 = v3126;
            *((_DWORD *)v3133 + 5) = v3137 & 0x7FFFFFFF;
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            v3139 = *((unsigned int *)v3126 + 505);
            v3140 = v3139 + 48;
            if ( (unsigned int)(v3139 + 48) <= *((_DWORD *)v3126 + 647) )
            {
              v3141 = v3126;
              *((_DWORD *)v3126 + 505) = v3140;
            }
            else
            {
              v3141 = (_BYTE *)sub_140B0F020(v3126, v3140, *((_DWORD *)v3126 + 585));
              if ( !v3141 )
                return 0;
              v3142 = *((_DWORD *)v3126 + 612);
              if ( (v3142 & 4) == 0 )
              {
                v3143 = *((_DWORD *)v3126 + 505);
                v3144 = *((_QWORD *)v3126 + 249);
                v3145 = (v3142 & 0x20000000) != 0 ? *((_DWORD *)v3126 + 585) : 0;
                if ( v3143 >= 8 )
                {
                  v3146 = (unsigned __int64)v3143 >> 3;
                  do
                  {
                    *(_QWORD *)v3126 = 0i64;
                    v3143 -= 8;
                    v3126 += 8;
                    --v3146;
                  }
                  while ( v3146 );
                }
                for ( ; v3143; --v3143 )
                  *v3126++ = 0;
                v3147 = *((_DWORD *)v3141 + 585);
                *((_DWORD *)v3141 + 585) = v3145;
                if ( v3145 == 3 )
                {
                  (*((void (__fastcall **)(__int64))v3141 + 109))(v3144);
                }
                else if ( (*((_DWORD *)v3141 + 612) & 0x10000000) != 0 || !v3145 )
                {
                  (*((void (__fastcall **)(__int64))v3141 + 31))(v3144);
                }
                else
                {
                  (*((void (__fastcall **)(__int64, _QWORD))v3141 + 69))(v3144 - 8, *(_QWORD *)(v3144 - 8));
                }
                *((_DWORD *)v3141 + 585) = v3147;
              }
              *((_DWORD *)v3141 + 612) &= ~4u;
            }
            ++*((_DWORD *)v3141 + 515);
            v3148 = &v3141[v3139];
            v3149 = 48;
            v3150 = &v3141[v3139];
            v3151 = 6i64;
            do
            {
              *v3150 = 0i64;
              v3149 -= 8;
              ++v3150;
              --v3151;
            }
            while ( v3151 );
            for ( ; v3149; --v3149 )
            {
              *(_BYTE *)v3150 = 0;
              v3150 = (_QWORD *)((char *)v3150 + 1);
            }
            *(_DWORD *)v3148 = 15;
            *((_QWORD *)v3148 + 1) = 0i64;
            *((_DWORD *)v3148 + 4) = 0;
            v3152 = *((_QWORD *)v3141 + 259);
            for ( i88 = v3152; ; LODWORD(v3152) = i88 ^ v3152 )
            {
              i88 >>= 31;
              if ( !i88 )
                break;
            }
            v3981 = v3141;
            *((_DWORD *)v3148 + 5) = v3152 & 0x7FFFFFFF;
            if ( (*((_DWORD *)v3141 + 612) & 0x40000000) == 0 && (*((_DWORD *)v3141 + 613) & 0x80u) != 0 )
            {
              v3154 = *((unsigned int *)v3141 + 505);
              v3155 = (unsigned int)Src;
              v3156 = v3784 - (_DWORD)Src;
              v3157 = v3154 + 48;
              if ( (unsigned int)(v3154 + 48) <= *((_DWORD *)v3141 + 647) )
              {
                v3158 = (__int64)v3141;
                *((_DWORD *)v3141 + 505) = v3157;
              }
              else
              {
                v3158 = sub_140B0F020(v3141, v3157, *((_DWORD *)v3141 + 585));
                if ( !v3158 )
                  return 0;
                v3159 = *((_DWORD *)v3141 + 612);
                if ( (v3159 & 4) == 0 )
                {
                  v3160 = *((_DWORD *)v3141 + 505);
                  v3161 = *((_QWORD *)v3141 + 249);
                  v3162 = (v3159 & 0x20000000) != 0 ? *((_DWORD *)v3141 + 585) : 0;
                  if ( v3160 >= 8 )
                  {
                    v3163 = (unsigned __int64)v3160 >> 3;
                    do
                    {
                      *(_QWORD *)v3141 = 0i64;
                      v3160 -= 8;
                      v3141 += 8;
                      --v3163;
                    }
                    while ( v3163 );
                  }
                  for ( ; v3160; --v3160 )
                    *v3141++ = 0;
                  v3164 = *(_DWORD *)(v3158 + 2340);
                  *(_DWORD *)(v3158 + 2340) = v3162;
                  if ( v3162 == 3 )
                  {
                    (*(void (__fastcall **)(__int64))(v3158 + 872))(v3161);
                  }
                  else if ( (*(_DWORD *)(v3158 + 2448) & 0x10000000) != 0 || !v3162 )
                  {
                    (*(void (__fastcall **)(__int64))(v3158 + 248))(v3161);
                  }
                  else
                  {
                    (*(void (__fastcall **)(__int64, _QWORD))(v3158 + 552))(v3161 - 8, *(_QWORD *)(v3161 - 8));
                  }
                  v3155 = (unsigned int)Src;
                  *(_DWORD *)(v3158 + 2340) = v3164;
                }
                *(_DWORD *)(v3158 + 2448) &= ~4u;
              }
              ++*(_DWORD *)(v3158 + 2060);
              v3165 = v3158 + v3154;
              v3166 = 48;
              HalExtensionList = v3158 + v3154;
              v3167 = (_QWORD *)(v3158 + v3154);
              v3168 = 6i64;
              do
              {
                *v3167 = 0i64;
                v3166 -= 8;
                ++v3167;
                --v3168;
              }
              while ( v3168 );
              for ( ; v3166; --v3166 )
              {
                *(_BYTE *)v3167 = 0;
                v3167 = (_QWORD *)((char *)v3167 + 1);
              }
              *(_DWORD *)v3165 = 42;
              *(_QWORD *)(v3165 + 8) = 0i64;
              *(_DWORD *)(v3165 + 16) = 0;
              v3169 = *(_QWORD *)(v3158 + 2072);
              for ( i89 = v3169; ; LODWORD(v3169) = i89 ^ v3169 )
              {
                i89 >>= 31;
                if ( !i89 )
                  break;
              }
              *(_DWORD *)(v3165 + 20) = v3169 & 0x7FFFFFFF;
              v3171 = (_QWORD *)(v3158 + v3155);
              *(_DWORD *)(v3165 + 32) = v3155;
              v3172 = v3171;
              *(_DWORD *)(v3165 + 36) = v3156;
              v3173 = (char *)v3171;
              *(_DWORD *)(v3158 + 2088) += v3156;
              v3174 = *(_DWORD *)(v3158 + 2068);
              v3175 = *(_QWORD *)(v3158 + 2072);
              v3176 = (unsigned __int64)v3171 + v3156;
              if ( (unsigned __int64)v3171 < v3176 )
              {
                do
                {
                  _mm_prefetchnta(v3173);
                  v3173 += 64;
                }
                while ( (unsigned __int64)v3173 < v3176 );
              }
              v3177 = *(_QWORD *)(v3158 + 2072);
              v3178 = v3156 >> 7;
              if ( v3156 >> 7 )
              {
                do
                {
                  v3179 = 8i64;
                  do
                  {
                    v3180 = v3172[1] ^ __ROL8__(*v3172 ^ v3177, v3174);
                    v3172 += 2;
                    v3177 = __ROL8__(v3180, v3174);
                    --v3179;
                  }
                  while ( v3179 );
                  v3181 = (__ROL8__(v3175 ^ ((char *)v3172 - (char *)v3171), 17) ^ v3175 ^ (unsigned __int64)((char *)v3172 - (char *)v3171))
                        * (unsigned __int128)0x7010008004002001ui64;
                  v4048 = *((_QWORD *)&v3181 + 1);
                  v3174 = ((unsigned __int8)v3181 ^ (unsigned __int8)(BYTE8(v3181) ^ v3174)) & 0x3F;
                  if ( !v3174 )
                    LOBYTE(v3174) = 1;
                  --v3178;
                }
                while ( v3178 );
                v3165 = HalExtensionList;
              }
              v3182 = v3156 & 0x7F;
              if ( v3182 >= 8 )
              {
                v3183 = (unsigned __int64)v3182 >> 3;
                do
                {
                  v3177 = __ROL8__(*v3172++ ^ v3177, v3174);
                  v3182 -= 8;
                  --v3183;
                }
                while ( v3183 );
              }
              for ( ; v3182; --v3182 )
              {
                v3184 = *(unsigned __int8 *)v3172;
                v3172 = (_QWORD *)((char *)v3172 + 1);
                v3177 = __ROL8__(v3184 ^ v3177, v3174);
              }
              *(_QWORD *)(v3165 + 24) = v3177;
              v3141 = (_BYTE *)v3158;
              v3981 = (_BYTE *)v3158;
            }
            if ( a3 > 1 )
            {
              v3185 = __rdtsc();
              v3186 = *((unsigned int *)v3141 + 515);
              v3187 = (__ROR8__(v3185, 3) ^ v3185) * (unsigned __int128)0x7010008004002001ui64;
              v4049 = *((_QWORD *)&v3187 + 1);
              *((_DWORD *)v3141 + 520) = (*((_QWORD *)&v3187 + 1) ^ (unsigned __int64)v3187) % v3186;
            }
            if ( (*((_DWORD *)v3141 + 612) & 0x10000000) != 0 )
            {
              v3188 = __rdtsc();
              v3189 = (__ROR8__(v3188, 3) ^ v3188) * (unsigned __int128)0x7010008004002001ui64;
              v4050 = *((_QWORD *)&v3189 + 1);
              *((_QWORD *)v3141 + 251) = *((_QWORD *)v3141 + 185)
                                       + 16i64 * (((unsigned __int8)v3189 ^ BYTE8(v3189)) & 0xF);
              goto LABEL_4792;
            }
            v3190 = a1;
            v3191 = a1 == 6;
            if ( a1 <= 6 )
              goto LABEL_4734;
            do
            {
              v3192 = v3190 - 7;
              if ( !v3192 )
              {
                v3254 = IopIrpStackProfilerDpcRoutine;
                v3297 = -1073711747;
                goto LABEL_4789;
              }
              v3193 = v3192 - 1;
              if ( !v3193 )
              {
                v3254 = (__int64 (__fastcall *)())&KiBalanceSetManagerDeferredRoutine;
                v3297 = 2080402375;
                goto LABEL_4789;
              }
              if ( v3193 == 1 )
              {
                v3254 = PopThermalZoneDpc;
                v3297 = -2147454541;
                goto LABEL_4789;
              }
              v3194 = __rdtsc();
              v3195 = (__ROR8__(v3194, 3) ^ v3194) * (unsigned __int128)0x7010008004002001ui64;
              v4051 = *((_QWORD *)&v3195 + 1);
              v1153 = ((unsigned __int64)v3195 ^ *((_QWORD *)&v3195 + 1)) % 0xA < 8;
              v3196 = *((_DWORD *)v3141 + 526);
              v3197 = v3196 - 3;
              if ( !v1153 )
              {
                if ( (v3197 & 0xFFFFFFFA) == 0 && v3196 != 8 )
                  goto LABEL_4732;
                v3260 = 0;
                v3261 = *((_DWORD *)v3141 + 612) & 0x10000000;
                if ( !v3261 )
                  v3260 = *((_DWORD *)v3141 + 585);
                v3262 = *((_DWORD *)v3141 + 516);
                v3263 = __rdtsc();
                v3264 = __ROR8__(v3263, 3);
                v4060 = ((v3264 ^ v3263) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                v3265 = ((unsigned __int16)(8193 * (v3264 ^ v3263)) ^ (unsigned __int16)v4060) & 0x7FF;
                v3266 = __rdtsc();
                v3267 = __ROR8__(v3266, 3) ^ v3266;
                v4061 = (v3267 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                v3268 = (v4061 ^ (0x7010008004002001i64 * v3267)) % (unsigned int)(v3265 + 1);
                if ( v3260 )
                {
                  v3269 = __rdtsc();
                  v3270 = __ROR8__(v3269, 3);
                  v4062 = ((v3270 ^ v3269) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                  v3265 += ((((67117057 * ((unsigned int)v3270 ^ (unsigned int)v3269)) ^ (unsigned int)v4062) & 1) << 12)
                         + 4096;
                  v3271 = (unsigned int)(v3265 + 272);
                  v3272 = (*((__int64 (__fastcall **)(__int64, __int64))v3141 + 68))(v3271 + 8, 0xFFFFFFFFi64);
                  v3273 = (_QWORD *)v3272;
                  if ( !v3272 )
                    goto LABEL_4718;
                  if ( !(*((unsigned __int8 (__fastcall **)(__int64, unsigned __int64, __int64))v3141 + 70))(
                          v3272,
                          (v3271 + 4095) & 0xFFFFFFFFFFFFF000ui64,
                          64i64) )
                  {
                    v3234 = (unsigned int)v3271;
                    v3235 = v3273;
LABEL_4707:
                    (*((void (__fastcall **)(_QWORD *, __int64))v3141 + 69))(v3235, v3234);
                    goto LABEL_4718;
                  }
                  *v3273 = (unsigned int)(v3265 + 272) + 8i64;
                  v3274 = (__int64)(v3273 + 1);
                }
                else
                {
                  v3274 = (*((__int64 (__fastcall **)(unsigned __int64, _QWORD, _QWORD, _QWORD))v3141 + 30))(
                            (-(__int64)(v3261 != 0) & 0xFFFFFFFFFFFFFFC0ui64) + 130,
                            (unsigned int)(v3265 + 272),
                            v3262,
                            (unsigned int)-v3261);
                }
                if ( !v3274 )
                  goto LABEL_4718;
                v3275 = v3268;
                v3276 = (_QWORD *)v3274;
                if ( (unsigned int)v3268 >= 8 )
                {
                  v3277 = (unsigned __int64)(unsigned int)v3268 >> 3;
                  do
                  {
                    v3278 = __rdtsc();
                    v3275 -= 8;
                    v3279 = (__ROR8__(v3278, 3) ^ v3278) * (unsigned __int128)0x7010008004002001ui64;
                    v4063 = *((_QWORD *)&v3279 + 1);
                    *v3276++ = v3279 ^ *((_QWORD *)&v3279 + 1);
                    --v3277;
                  }
                  while ( v3277 );
                }
                if ( v3275 )
                {
                  v3280 = __rdtsc();
                  v3281 = (__ROR8__(v3280, 3) ^ v3280) * (unsigned __int128)0x7010008004002001ui64;
                  v4064 = *((_QWORD *)&v3281 + 1);
                  v3282 = v3281 ^ *((_QWORD *)&v3281 + 1);
                  do
                  {
                    *(_BYTE *)v3276 = v3282;
                    v3276 = (_QWORD *)((char *)v3276 + 1);
                    v3282 >>= 8;
                    --v3275;
                  }
                  while ( v3275 );
                }
                v3283 = v3265 - v3268;
                v3284 = (unsigned int)v3268 + v3274;
                v3285 = (_QWORD *)(v3284 + 272);
                if ( v3283 >= 8 )
                {
                  v3286 = (unsigned __int64)v3283 >> 3;
                  do
                  {
                    v3287 = __rdtsc();
                    v3283 -= 8;
                    v3288 = (__ROR8__(v3287, 3) ^ v3287) * (unsigned __int128)0x7010008004002001ui64;
                    v4065 = *((_QWORD *)&v3288 + 1);
                    *v3285++ = v3288 ^ *((_QWORD *)&v3288 + 1);
                    --v3286;
                  }
                  while ( v3286 );
                }
                if ( v3283 )
                {
                  v3289 = __rdtsc();
                  v3290 = (__ROR8__(v3289, 3) ^ v3289) * (unsigned __int128)0x7010008004002001ui64;
                  v4066 = *((_QWORD *)&v3290 + 1);
                  v3291 = v3290 ^ *((_QWORD *)&v3290 + 1);
                  do
                  {
                    *(_BYTE *)v3285 = v3291;
                    v3285 = (_QWORD *)((char *)v3285 + 1);
                    v3291 >>= 8;
                    --v3283;
                  }
                  while ( v3283 );
                }
                if ( !v3284 )
                  goto LABEL_4732;
                v3254 = (__int64 (__fastcall *)())(v3284 + 72);
                v3292 = 200;
                v3293 = (_QWORD *)(v3284 + 72);
                v3294 = KiDpcDispatch;
                v3295 = 25i64;
                do
                {
                  v3292 -= 8;
                  *v3293 = *(_QWORD *)v3294;
                  v3294 = (__int64 (__fastcall *)())((char *)v3294 + 8);
                  ++v3293;
                  --v3295;
                }
                while ( v3295 );
                for ( ; v3292; --v3292 )
                {
                  v3296 = *(_BYTE *)v3294;
                  v3294 = (__int64 (__fastcall *)())((char *)v3294 + 1);
                  *(_BYTE *)v3293 = v3296;
                  v3293 = (_QWORD *)((char *)v3293 + 1);
                }
                *(_BYTE *)v3284 = 19;
                *(_BYTE *)(v3284 + 1) = 1;
                *(_WORD *)(v3284 + 2) = 0;
                *(_QWORD *)(v3284 + 24) = v3254;
                *(_QWORD *)(v3284 + 32) = 0i64;
                *(_QWORD *)(v3284 + 56) = 0i64;
                *(_QWORD *)(v3284 + 16) = 0i64;
                if ( v3284 == -72 )
                  goto LABEL_4732;
                *((_DWORD *)v3141 + 612) |= 0x100u;
                goto LABEL_4771;
              }
              if ( (v3197 & 0xFFFFFFFA) == 0 && v3196 != 8 )
                goto LABEL_4732;
              v3198 = -1i64;
              v3199 = 0i64;
              v4237 = RtlLookupFunctionTable(KiTimerDispatch, &v4239, v3851);
              v3200 = v4237;
              if ( v4237 )
              {
                v4242 = 0i64;
                if ( v4147 != v4239 )
                  goto LABEL_4681;
                v3201 = (_DWORD *)v4148;
                v4242 = v4148;
                v4243 = 0i64;
                v4244 = v4149;
                v4245 = 0;
                v3202 = RtlLookupFunctionEntry(KiTimerDispatch, &v4239, 0i64);
                v4238 = v3202;
                if ( !v3202 )
                  goto LABEL_4680;
                v3203 = v3202 - v4239;
                v3204 = 0;
                v3205 = *v3201 - 1;
                if ( v3205 < 0 )
                  goto LABEL_4680;
                while ( 1 )
                {
                  v3206 = (v3205 + v3204) >> 1;
                  v3207 = v3203 - v3201[2 * v3206 + 2];
                  if ( v3207 >= 0 )
                  {
                    if ( v3207 <= 0 )
                    {
                      v3208 = v4243;
                      if ( v3205 >= v3204 )
                        v3208 = (__int64)&v3201[2 * ((v3205 + v3204) >> 1) + 2];
                      v4243 = v3208;
LABEL_4680:
                      v3200 = v4237;
LABEL_4681:
                      v3209 = (__int64 *)&v4052;
                      v3210 = v4239;
                      v4241 = (__int64 *)&v4052;
                      v3851[0] /= 0xCu;
                      HalExtensionList = v4239;
                      v4240 = v3200 + 12i64 * (unsigned int)v3851[0];
                      v4236 = KiTimerDispatch;
                      goto LABEL_4684;
                    }
                    v3204 = v3206 + 1;
                  }
                  else
                  {
                    if ( !v3206 )
                      goto LABEL_4680;
                    v3205 = v3206 - 1;
                  }
                  if ( v3205 < v3204 )
                    goto LABEL_4680;
                }
              }
              v3210 = HalExtensionList;
              while ( 1 )
              {
                v3209 = v4241;
LABEL_4684:
                if ( !v3200 || v3200 == v4240 )
                  break;
                if ( v4242 )
                {
                  if ( !v4238 )
                    break;
                  if ( !v4243 )
                  {
                    *v3209 = v4238;
                    v4238 = 0i64;
                    goto LABEL_4710;
                  }
                  v3211 = *(_DWORD *)(v4243 + 4);
                  if ( (v3211 & 1) != 0 )
                  {
                    *v3209 = v4239 + (v3211 & 0xFFFFFFFE);
                    v4243 = 0i64;
                    goto LABEL_4710;
                  }
                  v3212 = (unsigned int)(v4245 + v3211);
                  v3213 = (unsigned int)v3212;
                  v3214 = v3212 + 4;
                  if ( v3214 < v3213 || v3214 > v4244 )
                  {
                    v3851[1] = 317;
                    KeBugCheckEx(__ROR4__(317, 160), 0x12ui64, v4242, v4239, v3213);
                  }
                  v3215 = *(_DWORD *)(v3213 + v4242);
                  v4245 += 4;
                  v4243 &= -(__int64)((v3215 & 1) != 0);
                  if ( (v3215 & 1) != 0 )
                    v3215 &= ~1u;
                  *v3209 = v4239 + v3215;
                }
                else
                {
                  while ( 1 )
                  {
                    v3216 = v3200;
                    v3217 = RtlpConvertFunctionEntry(v3200, v4239, v3209);
                    v3218 = RtlpSameFunction(v3217, v4239, v4236);
                    v3200 = v4237 + 12;
                    v4237 += 12i64;
                    if ( v3218 )
                      break;
                    if ( v3200 == v4240 )
                      goto LABEL_4699;
                  }
                  *v4241 = v3216;
                }
                v3210 = HalExtensionList;
LABEL_4710:
                if ( v3198 > v3210 + *v4052 )
                  v3198 = v3210 + *v4052;
                if ( v3199 < v3210 + v4052[1] )
                  v3199 = v3210 + v4052[1];
                v3200 = v4237;
              }
LABEL_4699:
              if ( v3199 )
              {
                v3219 = v3199 - v3198;
                v3788 = v3219;
                if ( v3219 <= 0x1000 )
                {
                  v3220 = 0;
                  v3221 = *((_DWORD *)v3141 + 612) & 0x10000000;
                  if ( !v3221 )
                    v3220 = *((_DWORD *)v3141 + 585);
                  v3222 = *((_DWORD *)v3141 + 516);
                  v3223 = __rdtsc();
                  v3224 = __ROR8__(v3223, 3);
                  v4053 = ((v3224 ^ v3223) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                  v3225 = ((unsigned __int16)(8193 * (v3224 ^ v3223)) ^ (unsigned __int16)v4053) & 0x7FF;
                  v3226 = __rdtsc();
                  v3227 = __ROR8__(v3226, 3) ^ v3226;
                  v4054 = (v3227 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                  v3228 = (v4054 ^ (0x7010008004002001i64 * v3227)) % (unsigned int)(v3225 + 1);
                  if ( !v3220 )
                  {
                    v3236 = (*((__int64 (__fastcall **)(unsigned __int64, _QWORD, _QWORD, _QWORD))v3141 + 30))(
                              (-(__int64)(v3221 != 0) & 0xFFFFFFFFFFFFFFC0ui64) + 130,
                              (unsigned int)(v3225 + v3219),
                              v3222,
                              (unsigned int)-v3221);
                    goto LABEL_4717;
                  }
                  v3229 = __rdtsc();
                  v3230 = __ROR8__(v3229, 3);
                  v4055 = ((v3230 ^ v3229) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                  v3225 += ((((unsigned __int8)(v3230 ^ v3229) ^ (unsigned __int8)v4055) & 1) << 12) + 4096;
                  v3231 = (unsigned int)(v3225 + v3219);
                  v3232 = (*((__int64 (__fastcall **)(__int64, __int64))v3141 + 68))(v3231 + 8, 0xFFFFFFFFi64);
                  v3233 = (_QWORD *)v3232;
                  if ( !v3232 )
                    goto LABEL_4718;
                  if ( !(*((unsigned __int8 (__fastcall **)(__int64, _QWORD, __int64))v3141 + 70))(
                          v3232,
                          ((_DWORD)v3231 + 4095) & 0xFFFFF000,
                          64i64) )
                  {
                    v3234 = (unsigned int)v3231;
                    v3235 = v3233;
                    goto LABEL_4707;
                  }
                  *v3233 = v3231 + 8;
                  v3236 = (__int64)(v3233 + 1);
LABEL_4717:
                  if ( !v3236 )
                  {
LABEL_4718:
                    ++*((_DWORD *)v3141 + 646);
                    goto LABEL_4732;
                  }
                  v3237 = v3228;
                  v3238 = (_QWORD *)v3236;
                  if ( (unsigned int)v3228 >= 8 )
                  {
                    v3239 = (unsigned __int64)(unsigned int)v3228 >> 3;
                    do
                    {
                      v3240 = __rdtsc();
                      v3237 -= 8;
                      v3241 = (__ROR8__(v3240, 3) ^ v3240) * (unsigned __int128)0x7010008004002001ui64;
                      v4056 = *((_QWORD *)&v3241 + 1);
                      *v3238++ = v3241 ^ *((_QWORD *)&v3241 + 1);
                      --v3239;
                    }
                    while ( v3239 );
                  }
                  if ( v3237 )
                  {
                    v3242 = __rdtsc();
                    v3243 = (__ROR8__(v3242, 3) ^ v3242) * (unsigned __int128)0x7010008004002001ui64;
                    v4057 = *((_QWORD *)&v3243 + 1);
                    v3244 = v3243 ^ *((_QWORD *)&v3243 + 1);
                    do
                    {
                      *(_BYTE *)v3238 = v3244;
                      v3238 = (_QWORD *)((char *)v3238 + 1);
                      v3244 >>= 8;
                      --v3237;
                    }
                    while ( v3237 );
                  }
                  v3245 = (unsigned int)v3788;
                  v3246 = v3225 - v3228;
                  v3247 = (_QWORD *)((unsigned int)v3228 + v3236 + (unsigned int)v3788);
                  if ( v3246 >= 8 )
                  {
                    v3248 = (unsigned __int64)v3246 >> 3;
                    do
                    {
                      v3249 = __rdtsc();
                      v3246 -= 8;
                      v3250 = (__ROR8__(v3249, 3) ^ v3249) * (unsigned __int128)0x7010008004002001ui64;
                      v4058 = *((_QWORD *)&v3250 + 1);
                      *v3247++ = v3250 ^ *((_QWORD *)&v3250 + 1);
                      --v3248;
                    }
                    while ( v3248 );
                  }
                  if ( v3246 )
                  {
                    v3251 = __rdtsc();
                    v3252 = (__ROR8__(v3251, 3) ^ v3251) * (unsigned __int128)0x7010008004002001ui64;
                    v4059 = *((_QWORD *)&v3252 + 1);
                    v3253 = v3252 ^ *((_QWORD *)&v3252 + 1);
                    do
                    {
                      *(_BYTE *)v3247 = v3253;
                      v3247 = (_QWORD *)((char *)v3247 + 1);
                      v3253 >>= 8;
                      --v3246;
                    }
                    while ( v3246 );
                  }
                  v3254 = (__int64 (__fastcall *)())(v3236 + (unsigned int)v3228);
                  if ( v3254 )
                  {
                    v3298 = (_QWORD *)(v3236 + (unsigned int)v3228);
                    if ( (unsigned int)v3245 >= 8 )
                    {
                      v3299 = v3245 >> 3;
                      do
                      {
                        LODWORD(v3245) = v3245 - 8;
                        *v3298 = *(_QWORD *)v3198;
                        v3198 += 8i64;
                        ++v3298;
                        --v3299;
                      }
                      while ( v3299 );
                    }
                    if ( (_DWORD)v3245 )
                    {
                      v3300 = (char *)v3298 - v3198;
                      do
                      {
                        v3300[v3198] = *(_BYTE *)v3198;
                        ++v3198;
                        LODWORD(v3245) = v3245 - 1;
                      }
                      while ( (_DWORD)v3245 );
                    }
                    *((_DWORD *)v3141 + 612) |= 0x200u;
LABEL_4771:
                    v3297 = 0;
                    goto LABEL_4789;
                  }
                }
              }
LABEL_4732:
              v3255 = __rdtsc();
              v3256 = (__ROR8__(v3255, 3) ^ v3255) * (unsigned __int128)0x7010008004002001ui64;
              v4067 = *((_QWORD *)&v3256 + 1);
              v3190 = ((unsigned __int64)v3256 ^ *((_QWORD *)&v3256 + 1)) % 0xA;
            }
            while ( v3190 > 6 );
            v3191 = v3190 == 6;
LABEL_4734:
            if ( v3191 )
            {
              v3254 = IopTimerDispatch;
LABEL_4788:
              v3297 = 31048;
            }
            else if ( v3190 )
            {
              v3257 = v3190 - 1;
              if ( v3257 )
              {
                v3258 = v3257 - 1;
                if ( v3258 )
                {
                  v3259 = v3258 - 1;
                  if ( v3259 )
                  {
                    if ( v3259 != 1 )
                    {
                      v3254 = (__int64 (__fastcall *)())ExpTimerDpcRoutine;
                      goto LABEL_4788;
                    }
                    v3254 = (__int64 (__fastcall *)())ExpCenturyDpcRoutine;
                    v3297 = -855610774;
                  }
                  else
                  {
                    v3254 = (__int64 (__fastcall *)())ExpTimeZoneDpcRoutine;
                    v3297 = 1895852711;
                  }
                }
                else
                {
                  v3254 = ExpTimeRefreshDpcRoutine;
                  v3297 = -1879020783;
                }
              }
              else
              {
                v3254 = (__int64 (__fastcall *)())CmpLazyFlushDpcRoutine;
                v3297 = -1342149386;
              }
            }
            else
            {
              v3254 = (__int64 (__fastcall *)())CmpEnableLazyFlushDpcRoutine;
              v3297 = -805277989;
            }
LABEL_4789:
            if ( !*((_DWORD *)v3141 + 597) )
              *((_DWORD *)v3141 + 597) = v3297;
            *((_QWORD *)v3141 + 251) = v3254;
LABEL_4792:
            *((_QWORD *)v3141 + 301) = **((_QWORD **)v3141 + 300);
            *((_DWORD *)v3141 + 604) = -1;
            *((_DWORD *)v3141 + 605) = 0;
            *((_QWORD *)v3141 + 303) = 0i64;
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            v3301 = __rdtsc();
            v3302 = (__ROR8__(v3301, 3) ^ v3301) * (unsigned __int128)0x7010008004002001ui64;
            v4068 = *((_QWORD *)&v3302 + 1);
            *((_DWORD *)v3141 + 599) = v3302 ^ DWORD2(v3302);
            if ( v4344 == 3 )
            {
              HalExtensionList = sub_140B320C4(v3141, a4);
              if ( !HalExtensionList )
              {
                v3851[2] = 317;
                KeBugCheckEx(__ROR4__(317, 160), 0x1Eui64, (ULONG_PTR)v3141, 0i64, 0i64);
              }
            }
            else
            {
              HalExtensionList = 0i64;
            }
            v3303 = *((unsigned int *)v3141 + 585);
            *((_DWORD *)v3141 + 647) = 0;
            v3304 = *((_DWORD *)v3141 + 505);
            v3305 = v3304 + 4095;
            if ( *((_DWORD *)v3141 + 526) != 7 )
              v3305 = v3304;
            v3306 = sub_140B0F020(v3141, v3305, v3303);
            v3307 = 0i64;
            v3788 = v3306;
            v3308 = v3306;
            if ( !v3306 )
              return 0;
            v3309 = *((_DWORD *)v3141 + 612);
            if ( (v3309 & 4) == 0 )
            {
              v3310 = *((_DWORD *)v3141 + 505);
              v3311 = *((_QWORD *)v3141 + 249);
              v3312 = (v3309 & 0x20000000) != 0 ? *((_DWORD *)v3141 + 585) : 0;
              if ( v3310 >= 8 )
              {
                v3307 = (unsigned __int64)v3310 >> 3;
                do
                {
                  *(_QWORD *)v3141 = 0i64;
                  v3310 -= 8;
                  v3141 += 8;
                  --v3307;
                }
                while ( v3307 );
              }
              for ( ; v3310; --v3310 )
                *v3141++ = v3307;
              v3313 = *(_DWORD *)(v3308 + 2340);
              *(_DWORD *)(v3308 + 2340) = v3312;
              if ( v3312 == 3 )
              {
                (*(void (__fastcall **)(__int64, unsigned __int64))(v3308 + 872))(v3311, v3307);
              }
              else if ( (*(_DWORD *)(v3308 + 2448) & 0x10000000) != 0 || !v3312 )
              {
                (*(void (__fastcall **)(__int64, unsigned __int64))(v3308 + 248))(v3311, v3307);
              }
              else
              {
                (*(void (__fastcall **)(__int64, _QWORD))(v3308 + 552))(v3311 - 8, *(_QWORD *)(v3311 - 8));
              }
              *(_DWORD *)(v3308 + 2340) = v3313;
              v3307 = 0i64;
            }
            *(_DWORD *)(v3308 + 2448) &= ~4u;
            v3787 = *(_QWORD *)(v3308 + 2696);
            *(_QWORD *)(v3308 + 2696) = 0i64;
            v3314 = *(unsigned int *)(v3308 + 2600);
            if ( (_DWORD)v3314 )
            {
              v3315 = (int *)(v3308 + v3314);
              v3316 = *(_QWORD **)(v3308 + v3314 + 8);
              v3786 = v3308 + v3314;
              if ( v3316 )
              {
                v3317 = (unsigned int)v3315[4];
                v3318 = v3316;
                *(_DWORD *)(v3308 + 2088) += v3317;
                v3319 = (char *)v3316;
                v3320 = *(unsigned int *)(v3308 + 2068);
                v3321 = *(_QWORD *)(v3308 + 2072);
                if ( v3316 < (_QWORD *)((char *)v3316 + v3317) )
                {
                  do
                  {
                    _mm_prefetchnta(v3319);
                    v3319 += 64;
                  }
                  while ( v3319 < (char *)v3316 + v3317 );
                }
                v3322 = *(_QWORD *)(v3308 + 2072);
                v3323 = (unsigned int)v3317 >> 7;
                if ( (unsigned int)v3317 >> 7 )
                {
                  do
                  {
                    v3324 = 8i64;
                    do
                    {
                      v3325 = v3318[1] ^ __ROL8__(*v3318 ^ v3322, v3320);
                      v3318 += 2;
                      v3322 = __ROL8__(v3325, v3320);
                      --v3324;
                    }
                    while ( v3324 );
                    v3326 = (__ROL8__(v3321 ^ ((char *)v3318 - (char *)v3316), 17) ^ v3321 ^ (unsigned __int64)((char *)v3318 - (char *)v3316))
                          * (unsigned __int128)0x7010008004002001ui64;
                    v4069 = *((_QWORD *)&v3326 + 1);
                    v3320 = ((unsigned __int8)v3326 ^ (unsigned __int8)(BYTE8(v3326) ^ v3320)) & 0x3F;
                    if ( !(_DWORD)v3320 )
                      v3320 = 1i64;
                    --v3323;
                  }
                  while ( v3323 );
                  v3308 = v3788;
                  v3307 = 0i64;
                  v3315 = (int *)v3786;
                }
                v3327 = v3317 & 0x7F;
                if ( (unsigned int)v3327 >= 8 )
                {
                  v3328 = (unsigned __int64)(unsigned int)v3327 >> 3;
                  do
                  {
                    v3322 = __ROL8__(*v3318++ ^ v3322, v3320);
                    v3327 = (unsigned int)(v3327 - 8);
                    --v3328;
                  }
                  while ( v3328 );
                }
                if ( (_DWORD)v3327 )
                {
                  do
                  {
                    v3329 = *(unsigned __int8 *)v3318;
                    v3318 = (_QWORD *)((char *)v3318 + 1);
                    v3322 = __ROL8__(v3329 ^ v3322, v3320);
                    v875 = (_DWORD)v3327 == 1;
                    v3327 = (unsigned int)(v3327 - 1);
                  }
                  while ( !v875 );
                }
                for ( i90 = v3322; ; LODWORD(v3322) = i90 ^ v3322 )
                {
                  i90 >>= 31;
                  if ( !i90 )
                    break;
                }
                v3331 = v3322 & 0x7FFFFFFF;
                v3332 = 0;
                if ( v3331 != v3315[5] )
                {
                  if ( !*v3315 && v3315[6] )
                    v3332 = 1;
                  v3333 = (unsigned int)v3315[4];
                  v3307 = *((_QWORD *)v3315 + 1);
                  if ( v3315[4] && (*(_DWORD *)(v3308 + 2452) & 0x40) != 0 )
                  {
                    v3334 = KeGetCurrentIrql();
                    v4348 = v3334;
                    __writecr8(2ui64);
                    v3335 = v3307 & 0xFFFFFFFFFFFFF000ui64;
                    v3790 = (v3307 + v3333 - 1) | 0xFFF;
                    v3794 = (v3307 & 0xFFFFFFFFFFFFF000ui64) - 1;
                    while ( 2 )
                    {
                      v3336 = v3334;
                      while ( 1 )
                      {
                        v3337 = (*(__int64 (__fastcall **)(unsigned __int64, _QWORD, __int64, __int64))(v3308 + 1128))(
                                  v3335,
                                  0i64,
                                  v3327,
                                  v3320);
                        if ( v3337 != -1073741267 )
                          break;
                        if ( v3332 )
                          goto LABEL_4849;
                        v3334 = v4348;
                        if ( v4348 > 1u )
                          goto LABEL_4847;
                        v3336 = v4348;
                        __writecr8(v4348);
                        KeGetCurrentIrql();
                        __writecr8(2ui64);
                      }
                      if ( v3337 < 0 )
                      {
LABEL_4849:
                        __writecr8(v3336);
                        goto LABEL_4850;
                      }
                      v3334 = v4348;
LABEL_4847:
                      v3307 = 4096i64;
                      v3335 += 4096i64;
                      v3794 += 4096i64;
                      if ( v3794 != v3790 )
                        continue;
                      break;
                    }
                    __writecr8(v3336);
                  }
                  else
                  {
LABEL_4850:
                    if ( !*(_DWORD *)(v3308 + 2296) )
                    {
                      *(_QWORD *)(*(_QWORD *)(v3308 + 1416) + 24i64) = (unsigned int)v3315[5] ^ (unsigned __int64)v3331;
                      v3338 = *((_QWORD *)v3315 + 1);
                      if ( !*(_DWORD *)(v3308 + 2296) )
                      {
                        *(_QWORD *)(v3308 + 2304) = v3308 - 0x5C5FC0A76E374B18i64;
                        *(_QWORD *)(v3308 + 2312) = (char *)v3315 - 0x4C48B4211BBACBEBi64;
                        *(_QWORD *)(v3308 + 2320) = *v3315;
                        *(_QWORD *)(v3308 + 2328) = v3338;
                        *(_DWORD *)(v3308 + 2296) = 1;
                        __ba(v3308, 0i64);
                      }
                    }
                  }
                }
                (*(void (__fastcall **)(_QWORD, unsigned __int64, __int64, __int64))(v3308 + 248))(
                  *((_QWORD *)v3315 + 3),
                  v3307,
                  v3327,
                  v3320);
                *((_QWORD *)v3315 + 1) = 0i64;
                v3315[4] = 0;
                v3339 = *(_QWORD *)(v3308 + 2072);
                for ( i91 = v3339; ; LODWORD(v3339) = i91 ^ v3339 )
                {
                  i91 >>= 31;
                  if ( !i91 )
                    break;
                }
                v3315[5] = v3339 & 0x7FFFFFFF;
              }
              v3341 = __rdtsc();
              v3342 = (__ROR8__(v3341, 3) ^ v3341) * (unsigned __int128)0x7010008004002001ui64;
              v4070 = *((_QWORD *)&v3342 + 1);
              if ( ((unsigned __int64)v3342 ^ *((_QWORD *)&v3342 + 1)) == 3
                                                                        * (((unsigned __int64)v3342 ^ *((_QWORD *)&v3342 + 1))
                                                                         / 3) )
              {
                v3343 = *(unsigned int *)(v3308 + 2064);
                v3344 = __rdtsc();
                v3345 = __ROR8__(v3344, 3);
                v4071 = ((v3345 ^ v3344) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                v3346 = ((unsigned __int16)(8193 * (v3345 ^ v3344)) ^ (unsigned __int16)v4071) & 0x7FF;
                v3347 = __rdtsc();
                v3348 = __ROR8__(v3347, 3) ^ v3347;
                v4072 = (v3348 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                v3349 = (v4072 ^ (0x7010008004002001i64 * v3348)) % (unsigned int)(v3346 + 1);
                v3350 = (*(__int64 (__fastcall **)(unsigned __int64, _QWORD, __int64))(v3308 + 240))(
                          (-(__int64)((*(_DWORD *)(v3308 + 2448) & 0x10000000) != 0) & 0xFFFFFFFFFFFFFFC0ui64) + 130,
                          (unsigned int)(v3346 + 2720),
                          v3343);
                v3351 = v3350;
                if ( v3350 )
                {
                  v3352 = v3349;
                  v3353 = (_QWORD *)v3350;
                  if ( (unsigned int)v3349 >= 8 )
                  {
                    v3354 = (unsigned __int64)(unsigned int)v3349 >> 3;
                    do
                    {
                      v3355 = __rdtsc();
                      v3352 -= 8;
                      v3356 = (__ROR8__(v3355, 3) ^ v3355) * (unsigned __int128)0x7010008004002001ui64;
                      v4073 = *((_QWORD *)&v3356 + 1);
                      *v3353++ = v3356 ^ *((_QWORD *)&v3356 + 1);
                      --v3354;
                    }
                    while ( v3354 );
                  }
                  if ( v3352 )
                  {
                    v3357 = __rdtsc();
                    v3358 = (__ROR8__(v3357, 3) ^ v3357) * (unsigned __int128)0x7010008004002001ui64;
                    v4074 = *((_QWORD *)&v3358 + 1);
                    v3359 = v3358 ^ *((_QWORD *)&v3358 + 1);
                    do
                    {
                      *(_BYTE *)v3353 = v3359;
                      v3353 = (_QWORD *)((char *)v3353 + 1);
                      v3359 >>= 8;
                      --v3352;
                    }
                    while ( v3352 );
                  }
                  v3360 = v3346 - v3349;
                  v3361 = (char *)(v3351 + (unsigned int)v3349);
                  v3362 = v3361 + 2720;
                  if ( v3360 >= 8 )
                  {
                    v3363 = (unsigned __int64)v3360 >> 3;
                    do
                    {
                      v3364 = __rdtsc();
                      v3360 -= 8;
                      v3365 = (__ROR8__(v3364, 3) ^ v3364) * (unsigned __int128)0x7010008004002001ui64;
                      v4075 = *((_QWORD *)&v3365 + 1);
                      *v3362++ = v3365 ^ *((_QWORD *)&v3365 + 1);
                      --v3363;
                    }
                    while ( v3363 );
                    v3308 = v3788;
                  }
                  if ( v3360 )
                  {
                    v3366 = __rdtsc();
                    v3367 = (__ROR8__(v3366, 3) ^ v3366) * (unsigned __int128)0x7010008004002001ui64;
                    v4076 = *((_QWORD *)&v3367 + 1);
                    v3368 = v3367 ^ *((_QWORD *)&v3367 + 1);
                    do
                    {
                      *(_BYTE *)v3362 = v3368;
                      v3362 = (_QWORD *)((char *)v3362 + 1);
                      v3368 >>= 8;
                      --v3360;
                    }
                    while ( v3360 );
                  }
                  if ( v3315 != (int *)-24i64 )
                    *((_QWORD *)v3315 + 3) = v3351;
                  if ( v3361 )
                  {
                    *((_QWORD *)v3315 + 1) = v3361;
                    v3315[4] = 2720;
                    v3369 = 2720;
                    v3370 = (char *)v3308;
                    v3371 = (_QWORD *)(v3351 + (unsigned int)v3349);
                    v3372 = 340i64;
                    do
                    {
                      v3369 -= 8;
                      *v3371 = *(_QWORD *)v3370;
                      v3370 += 8;
                      ++v3371;
                      --v3372;
                    }
                    while ( v3372 );
                    for ( ; v3369; --v3369 )
                    {
                      v3373 = *v3370++;
                      *(_BYTE *)v3371 = v3373;
                      v3371 = (_QWORD *)((char *)v3371 + 1);
                    }
                    v3374 = *((_DWORD *)v3361 + 612);
                    *((_DWORD *)v3361 + 505) = 2720;
                    *((_DWORD *)v3361 + 514) = 2720;
                    v3375 = v3374 & 0xFFF7FFFD | 0x80000;
                    *((_DWORD *)v3361 + 612) = v3375;
                    *((_DWORD *)v3361 + 651) = 2720;
                    v4349 = v3375;
                    LODWORD(Src) = *((_DWORD *)v3361 + 597);
                    v3790 = *((_QWORD *)v3361 + 156);
                    v3794 = *((_QWORD *)v3361 + 183);
                    *((_DWORD *)v3361 + 49) = 315;
                    do
                    {
                      v3376 = __rdtsc();
                      v3377 = (__ROR8__(v3376, 3) ^ v3376) * (unsigned __int128)0x7010008004002001ui64;
                      v4077 = *((_QWORD *)&v3377 + 1);
                      v3378 = v3377 ^ *((_QWORD *)&v3377 + 1);
                    }
                    while ( (unsigned __int64)v3377 == *((_QWORD *)&v3377 + 1) );
                    v3379 = v3361 + 1944;
                    v3380 = v3786;
                    v3381 = v4177;
                    v3382 = 32;
                    v3792 = *((_QWORD *)v3361 + 247);
                    v3383 = v3361 + 1944;
                    LODWORD(v3784) = *((_DWORD *)v3361 + 522);
                    v3384 = 4i64;
                    do
                    {
                      v3382 -= 8;
                      *(_QWORD *)v3381 = *(_QWORD *)v3383;
                      v3383 += 8;
                      v3381 += 8;
                      --v3384;
                    }
                    while ( v3384 );
                    for ( ; v3382; --v3382 )
                    {
                      v3385 = *v3383++;
                      *v3381++ = v3385;
                    }
                    *((_QWORD *)v3361 + 247) = 0i64;
                    v3386 = 32;
                    *((_DWORD *)v3361 + 522) = 0;
                    v3387 = v3361 + 1944;
                    v3388 = 4i64;
                    do
                    {
                      *v3387 = 0i64;
                      v3386 -= 8;
                      ++v3387;
                      --v3388;
                    }
                    while ( v3388 );
                    for ( ; v3386; --v3386 )
                    {
                      *(_BYTE *)v3387 = 0;
                      v3387 = (_QWORD *)((char *)v3387 + 1);
                    }
                    v3389 = *((unsigned int *)v3361 + 505);
                    v3390 = v3361;
                    *((_DWORD *)v3361 + 522) += v3389;
                    v3391 = v3361;
                    v3392 = *((_DWORD *)v3361 + 517);
                    for ( i92 = *((_QWORD *)v3361 + 259); v3391 < &v3361[v3389]; v3391 += 64 )
                      _mm_prefetchnta(v3391);
                    v3394 = (unsigned int)v3389 >> 7;
                    if ( (unsigned int)v3389 >> 7 )
                    {
                      v3395 = *((_QWORD *)v3361 + 259);
                      do
                      {
                        v3396 = 8i64;
                        do
                        {
                          v3397 = v3390[1] ^ __ROL8__(*v3390 ^ i92, v3392);
                          v3390 += 2;
                          i92 = __ROL8__(v3397, v3392);
                          --v3396;
                        }
                        while ( v3396 );
                        v3398 = (__ROL8__(v3395 ^ ((char *)v3390 - v3361), 17) ^ v3395 ^ (unsigned __int64)((char *)v3390 - v3361))
                              * (unsigned __int128)0x7010008004002001ui64;
                        v4078 = *((_QWORD *)&v3398 + 1);
                        v3392 = ((unsigned __int8)v3398 ^ (unsigned __int8)(BYTE8(v3398) ^ v3392)) & 0x3F;
                        if ( !v3392 )
                          LOBYTE(v3392) = 1;
                        --v3394;
                      }
                      while ( v3394 );
                      v3308 = v3788;
                      v3379 = v3361 + 1944;
                    }
                    v3399 = v3389 & 0x7F;
                    if ( v3399 >= 8 )
                    {
                      v3400 = (unsigned __int64)v3399 >> 3;
                      do
                      {
                        i92 = __ROL8__(*v3390++ ^ i92, v3392);
                        v3399 -= 8;
                        --v3400;
                      }
                      while ( v3400 );
                    }
                    for ( ; v3399; --v3399 )
                    {
                      v3401 = *(unsigned __int8 *)v3390;
                      v3390 = (_QWORD *)((char *)v3390 + 1);
                      i92 = __ROL8__(v3401 ^ i92, v3392);
                    }
                    v3402 = v4177;
                    *((_QWORD *)v3361 + 247) = v3792;
                    v3403 = 32;
                    *((_DWORD *)v3361 + 522) += v3784;
                    v3404 = 4i64;
                    do
                    {
                      v3403 -= 8;
                      *v3379 = *(_QWORD *)v3402;
                      v3402 += 8;
                      ++v3379;
                      --v3404;
                    }
                    while ( v3404 );
                    for ( i93 = 0; v3403; --v3403 )
                    {
                      v3406 = *v3402++;
                      *(_BYTE *)v3379 = v3406;
                      v3379 = (_QWORD *)((char *)v3379 + 1);
                    }
                    *((_QWORD *)v3361 + 247) = i92;
                    if ( (*((_DWORD *)v3361 + 612) & 0x40000000) == 0 )
                    {
                      v3407 = v3361;
                      for ( i94 = 0; i94 < 0x19; ++i94 )
                        *v3407++ ^= v3378;
                      v3409 = v3407 + 314;
                      v3410 = 315;
                      while ( 1 )
                      {
                        *v3409-- ^= v3378;
                        v4079[0] = __ROR8__(v3378, v3410);
                        _bittestandcomplement64(v4079, v4079[0] & 0x3F);
                        if ( !--v3410 )
                          break;
                        v3378 = v4079[0];
                      }
                      v3411 = __rdtsc();
                      v3412 = (__ROR8__(v3411, 3) ^ v3411) * (unsigned __int128)0x7010008004002001ui64;
                      v4079[1] = *((_QWORD *)&v3412 + 1);
                      if ( ((unsigned __int64)v3412 ^ *((_QWORD *)&v3412 + 1)) == 3
                                                                                * (((unsigned __int64)v3412 ^ *((_QWORD *)&v3412 + 1))
                                                                                 / 3) )
                      {
                        v3413 = (unsigned int)Src;
                        v3414 = v3794;
                        v3415 = (ULONG_PTR *)v3361;
                        v3416 = v3790;
                        v3417 = __ROR8__(v3361, (char)v3361);
                        do
                        {
                          v3418 = *v3415 - i93 - (_QWORD)v3361;
                          if ( (v4349 & 0x200) != 0 )
                            v3419 = v3418 ^ v3417;
                          else
                            v3419 = v3414 ^ __ROR8__(v3417 ^ _byteswap_uint64(v3418 ^ v3416), v3414);
                          *v3415++ = v3419;
                          v3417 = v3413 ^ (unsigned __int64)&v3361[__ROL8__(
                                                                     __ROR8__(
                                                                       i93 ^ (unsigned __int64)(200 - i93),
                                                                       ~(_BYTE)v3419) ^ v3417,
                                                                     (unsigned __int8)v3419 ^ 0x29u)];
                          ++i93;
                        }
                        while ( i93 < 0x19 );
                        v3308 = v3788;
                        v3380 = v3786;
                      }
                    }
                    v3420 = *(_QWORD **)(v3380 + 8);
                    v3421 = *(unsigned int *)(v3380 + 16);
                    v3422 = v3420;
                    *(_DWORD *)(v3308 + 2088) += v3421;
                    v3423 = (char *)v3420;
                    v3424 = *(_DWORD *)(v3308 + 2068);
                    v3425 = *(_QWORD *)(v3308 + 2072);
                    if ( v3420 < (_QWORD *)((char *)v3420 + v3421) )
                    {
                      do
                      {
                        _mm_prefetchnta(v3423);
                        v3423 += 64;
                      }
                      while ( v3423 < (char *)v3420 + v3421 );
                    }
                    v3426 = (unsigned int)v3421 >> 7;
                    v3427 = *(_QWORD *)(v3308 + 2072);
                    if ( (unsigned int)v3421 >> 7 )
                    {
                      do
                      {
                        v3428 = 8i64;
                        do
                        {
                          v3429 = v3422[1] ^ __ROL8__(*v3422 ^ v3427, v3424);
                          v3422 += 2;
                          v3427 = __ROL8__(v3429, v3424);
                          --v3428;
                        }
                        while ( v3428 );
                        v3430 = (__ROL8__(v3425 ^ ((char *)v3422 - (char *)v3420), 17) ^ v3425 ^ (unsigned __int64)((char *)v3422 - (char *)v3420))
                              * (unsigned __int128)0x7010008004002001ui64;
                        v4079[2] = *((_QWORD *)&v3430 + 1);
                        v3424 = ((unsigned __int8)v3430 ^ (unsigned __int8)(BYTE8(v3430) ^ v3424)) & 0x3F;
                        if ( !v3424 )
                          LOBYTE(v3424) = 1;
                        --v3426;
                      }
                      while ( v3426 );
                      v3308 = v3788;
                      v3380 = v3786;
                    }
                    v3431 = v3421 & 0x7F;
                    if ( v3431 >= 8 )
                    {
                      v3432 = (unsigned __int64)v3431 >> 3;
                      do
                      {
                        v3427 = __ROL8__(*v3422++ ^ v3427, v3424);
                        v3431 -= 8;
                        --v3432;
                      }
                      while ( v3432 );
                    }
                    for ( ; v3431; --v3431 )
                    {
                      v3433 = *(unsigned __int8 *)v3422;
                      v3422 = (_QWORD *)((char *)v3422 + 1);
                      v3427 = __ROL8__(v3433 ^ v3427, v3424);
                    }
                    for ( i95 = v3427; ; LODWORD(v3427) = i95 ^ v3427 )
                    {
                      i95 >>= 31;
                      if ( !i95 )
                        break;
                    }
                    *(_DWORD *)(v3380 + 20) = v3427 & 0x7FFFFFFF;
                  }
                }
                else
                {
                  ++*(_DWORD *)(v3308 + 2584);
                }
              }
            }
            *(_DWORD *)(v3308 + 2448) |= 0x200000u;
            v3435 = *(_DWORD *)(v3308 + 196);
            v3436 = (_QWORD *)v3308;
            *(_DWORD *)(v3308 + 196) = 0;
            v3437 = (char *)v3308;
            *(_DWORD *)(v3308 + 2088) += 1576;
            v3438 = *(_DWORD *)(v3308 + 2068);
            v3439 = *(_QWORD *)(v3308 + 2072);
            if ( v3308 < v3308 + 1576 )
            {
              do
              {
                _mm_prefetchnta(v3437);
                v3437 += 64;
              }
              while ( (unsigned __int64)v3437 < v3308 + 1576 );
            }
            v3440 = *(_QWORD *)(v3308 + 2072);
            v3441 = 12;
            do
            {
              v3442 = 8i64;
              do
              {
                v3443 = v3436[1] ^ __ROL8__(*v3436 ^ v3440, v3438);
                v3436 += 2;
                v3440 = __ROL8__(v3443, v3438);
                --v3442;
              }
              while ( v3442 );
              v3444 = (__ROL8__(v3439 ^ ((unsigned __int64)v3436 - v3308), 17) ^ v3439 ^ ((unsigned __int64)v3436 - v3308))
                    * (unsigned __int128)0x7010008004002001ui64;
              v4079[3] = *((_QWORD *)&v3444 + 1);
              v3438 = ((unsigned __int8)(v3444 ^ BYTE8(v3444)) ^ (unsigned __int8)v3438) & 0x3F;
              if ( !v3438 )
                LOBYTE(v3438) = 1;
              --v3441;
            }
            while ( v3441 );
            v3445 = 40;
            v3446 = 5i64;
            do
            {
              v3440 = __ROL8__(*v3436++ ^ v3440, v3438);
              v3445 -= 8;
              --v3446;
            }
            while ( v3446 );
            for ( ; v3445; --v3445 )
            {
              v3447 = *(unsigned __int8 *)v3436;
              v3436 = (_QWORD *)((char *)v3436 + 1);
              v3440 = __ROL8__(v3447 ^ v3440, v3438);
            }
            *(_DWORD *)(v3308 + 196) = v3435;
            *(_QWORD *)(v3308 + 2592) = v3440;
            *(_DWORD *)(v3308 + 2088) = 0;
            *(_DWORD *)(v3308 + 2584) = 0;
            v3786 = *(_QWORD *)(v3308 + 1992);
            memmove(v4297, (const void *)v3308, 0xAA0ui64);
            __ba(v3308, 1i64);
            v4350 = *(_DWORD *)(v3308 + 2388);
            v3448 = *(_DWORD *)(v3308 + 2604) - 200;
            LODWORD(Src) = *(_DWORD *)(v3308 + 2448);
            v3790 = *(_QWORD *)(v3308 + 1248);
            v3449 = v3448 >> 3;
            v3794 = *(_QWORD *)(v3308 + 1464);
            *(_DWORD *)(v3308 + 196) = v3449;
            do
            {
              v3450 = __rdtsc();
              v3451 = (__ROR8__(v3450, 3) ^ v3450) * (unsigned __int128)0x7010008004002001ui64;
              v4079[4] = *((_QWORD *)&v3451 + 1);
              v3452 = v3451 ^ *((_QWORD *)&v3451 + 1);
            }
            while ( (unsigned __int64)v3451 == *((_QWORD *)&v3451 + 1) );
            v3453 = (_QWORD *)(v3308 + 1944);
            v3454 = 32;
            v3792 = *(_QWORD *)(v3308 + 1976);
            v3455 = v4178;
            LODWORD(v3783) = *(_DWORD *)(v3308 + 2088);
            v3456 = (char *)(v3308 + 1944);
            v3457 = 4i64;
            do
            {
              v3454 -= 8;
              *(_QWORD *)v3455 = *(_QWORD *)v3456;
              v3456 += 8;
              v3455 += 8;
              --v3457;
            }
            while ( v3457 );
            for ( ; v3454; --v3454 )
            {
              v3458 = *v3456++;
              *v3455++ = v3458;
            }
            *(_QWORD *)(v3308 + 1976) = 0i64;
            v3459 = 32;
            *(_DWORD *)(v3308 + 2088) = 0;
            v3460 = (_QWORD *)(v3308 + 1944);
            v3461 = 4i64;
            do
            {
              *v3460 = 0i64;
              v3459 -= 8;
              ++v3460;
              --v3461;
            }
            while ( v3461 );
            for ( ; v3459; --v3459 )
            {
              *(_BYTE *)v3460 = 0;
              v3460 = (_QWORD *)((char *)v3460 + 1);
            }
            v3462 = *(unsigned int *)(v3308 + 2020);
            v3463 = (_QWORD *)v3308;
            *(_DWORD *)(v3308 + 2088) += v3462;
            v3464 = (char *)v3308;
            v3465 = *(_DWORD *)(v3308 + 2068);
            v3466 = *(_QWORD *)(v3308 + 2072);
            if ( v3308 < v3308 + v3462 )
            {
              do
              {
                _mm_prefetchnta(v3464);
                v3464 += 64;
              }
              while ( (unsigned __int64)v3464 < v3308 + v3462 );
            }
            v3467 = *(_QWORD *)(v3308 + 2072);
            v3468 = (unsigned int)v3462 >> 7;
            if ( (unsigned int)v3462 >> 7 )
            {
              do
              {
                v3469 = 8i64;
                do
                {
                  v3470 = v3463[1] ^ __ROL8__(*v3463 ^ v3467, v3465);
                  v3463 += 2;
                  v3467 = __ROL8__(v3470, v3465);
                  --v3469;
                }
                while ( v3469 );
                v3471 = (__ROL8__(v3466 ^ ((unsigned __int64)v3463 - v3308), 17) ^ v3466 ^ ((unsigned __int64)v3463
                                                                                          - v3308))
                      * (unsigned __int128)0x7010008004002001ui64;
                v4079[5] = *((_QWORD *)&v3471 + 1);
                v3465 = ((unsigned __int8)(v3471 ^ BYTE8(v3471)) ^ (unsigned __int8)v3465) & 0x3F;
                if ( !v3465 )
                  LOBYTE(v3465) = 1;
                --v3468;
              }
              while ( v3468 );
              v3453 = (_QWORD *)(v3308 + 1944);
            }
            v3472 = v3462 & 0x7F;
            if ( v3472 >= 8 )
            {
              v3473 = (unsigned __int64)v3472 >> 3;
              do
              {
                v3467 = __ROL8__(*v3463++ ^ v3467, v3465);
                v3472 -= 8;
                --v3473;
              }
              while ( v3473 );
            }
            for ( ; v3472; --v3472 )
            {
              v3474 = *(unsigned __int8 *)v3463;
              v3463 = (_QWORD *)((char *)v3463 + 1);
              v3467 = __ROL8__(v3474 ^ v3467, v3465);
            }
            v3475 = v4178;
            *(_QWORD *)(v3308 + 1976) = v3792;
            v3476 = 32;
            *(_DWORD *)(v3308 + 2088) += v3783;
            v3477 = 4i64;
            do
            {
              v3476 -= 8;
              *v3453 = *(_QWORD *)v3475;
              v3475 += 8;
              ++v3453;
              --v3477;
            }
            while ( v3477 );
            for ( ; v3476; --v3476 )
            {
              v3478 = *v3475++;
              *(_BYTE *)v3453 = v3478;
              v3453 = (_QWORD *)((char *)v3453 + 1);
            }
            *(_QWORD *)(v3308 + 1976) = v3467;
            if ( (*(_DWORD *)(v3308 + 2448) & 0x40000000) == 0 )
            {
              v3479 = (_QWORD *)v3308;
              for ( i96 = 0; i96 < 0x19; ++i96 )
                *v3479++ ^= v3452;
              v4080[0] = v3452;
              v3481 = v3449;
              if ( v3449 )
              {
                v3482 = &v3479[v3449 - 1];
                while ( 1 )
                {
                  *v3482-- ^= v3452;
                  v4080[0] = __ROR8__(v3452, v3481);
                  _bittestandcomplement64(v4080, v4080[0] & 0x3F);
                  if ( !--v3481 )
                    break;
                  v3452 = v4080[0];
                }
              }
              v3483 = (int)Src;
              if ( ((unsigned int)Src & 0x80000) != 0 )
              {
                v3484 = __rdtsc();
                v3485 = (__ROR8__(v3484, 3) ^ v3484) * (unsigned __int128)0x7010008004002001ui64;
                v4080[1] = *((_QWORD *)&v3485 + 1);
                if ( ((unsigned __int64)v3485 ^ *((_QWORD *)&v3485 + 1)) != 3
                                                                          * (((unsigned __int64)v3485 ^ *((_QWORD *)&v3485 + 1))
                                                                           / 3) )
                  goto LABEL_5000;
              }
              else if ( ((unsigned __int16)Src & 0x100) != 0 )
              {
                goto LABEL_5000;
              }
              v3486 = v3794;
              v3487 = 25;
              v3488 = __ROR8__(v3308, v3308);
              v3489 = 0;
              v3490 = (ULONG_PTR *)v3308;
              v3491 = v3790;
              do
              {
                v3492 = *v3490 - v3489 - v3308;
                if ( (v3483 & 0x200) != 0 )
                  v3493 = v3488 ^ v3492;
                else
                  v3493 = v3486 ^ __ROR8__(v3488 ^ _byteswap_uint64(v3491 ^ v3492), v3486);
                *v3490++ = v3493;
                v3488 = v4350 ^ (v3308
                               + __ROL8__(
                                   __ROR8__(v3489 ^ (unsigned __int64)(200 - v3489), ~(_BYTE)v3493) ^ v3488,
                                   (unsigned __int8)v3493 ^ 0x29u));
                if ( ++v3489 == 25 )
                {
                  v3494 = 0;
                  if ( (v3483 & 0x80000) == 0 )
                    v3494 = v3449;
                  v3487 += v3494;
                }
              }
              while ( v3489 < v3487 );
            }
LABEL_5000:
            KeInitializeTimer(Timer);
            _disable();
            if ( !(_BYTE)KdDebuggerNotPresent )
            {
              while ( 1 )
                ;
            }
            _enable();
            if ( v4344 != 7 )
              goto LABEL_5256;
            v3495 = 32;
            if ( (*(_DWORD *)(v3308 + 2448) & 0x10000000) != 0 )
              v3495 = 2;
            if ( *(_DWORD *)(v3308 + 2340) )
            {
              MmSetPageProtection(*(_QWORD *)(v3308 + 1992) - 8i64, **(_QWORD **)(v3308 + 1992), v3495);
            }
            else
            {
              v3496 = *(void **)(v3308 + 1992);
              PoolBlockSize = ExQueryPoolBlockSize(v3496, QuotaCharged);
              ExProtectPool(v3496, PoolBlockSize, v3495);
            }
            for ( i97 = 0; i97 < 0x10; ++i97 )
            {
              v3499 = __rdtsc();
              v3500 = (__ROR8__(v3499, 3) ^ v3499) * (unsigned __int128)0x7010008004002001ui64;
              v4080[2] = *((_QWORD *)&v3500 + 1);
              v3501 = ((unsigned __int64)v3500 ^ *((_QWORD *)&v3500 + 1)) % 0xB;
              if ( (unsigned int)v3501 > 5 )
              {
                v3505 = v3501 - 6;
                if ( v3505 )
                {
                  v3506 = v3505 - 1;
                  if ( v3506 )
                  {
                    v3507 = v3506 - 1;
                    if ( v3507 )
                    {
                      if ( v3507 == 1 )
                      {
                        v3851[9] = -1333354875;
                        v3504 = __ROR4__(-1333354868, 33);
                      }
                      else
                      {
                        v3508 = __rdtsc();
                        v3509 = __ROR8__(v3508, 3);
                        v4081 = ((v3509 ^ v3508) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                        v3510 = (67117057 * (v3509 ^ v3508)) ^ v4081;
                        v3504 = ((((((v3510 % 0x1A + 97) << 8) | ((v3510 >> 5)
                                                                - 26
                                                                * ((unsigned int)((1321528399
                                                                                 * (unsigned __int64)(v3510 >> 5)) >> 32) >> 3)
                                                                + 65)) << 8) | ((v3510 >> 10) % 0x1A + 97)) << 8) | ((v3510 >> 15) % 0x1A + 65);
                      }
                    }
                    else
                    {
                      v3851[10] = 1684422978;
                      v3504 = __ROR4__(1684422978, 8);
                    }
                  }
                  else
                  {
                    v3851[11] = -2100910376;
                    v3504 = __ROL4__(-2100910376, 7);
                  }
                }
                else
                {
                  v3851[12] = 1314342514;
                  v3504 = __ROR4__(1314342516, 24);
                }
              }
              else if ( (_DWORD)v3501 == 5 )
              {
                v3851[8] = 680282605;
                v3504 = __ROR4__(680282605, 5);
              }
              else if ( (_DWORD)v3501 )
              {
                v3502 = v3501 - 1;
                if ( v3502 )
                {
                  v3503 = v3502 - 1;
                  if ( v3503 )
                  {
                    if ( v3503 == 1 )
                    {
                      v3851[4] = -1474152136;
                      v3504 = __ROR4__(-1474152133, 15);
                    }
                    else
                    {
                      v3851[3] = 1728537748;
                      v3504 = __ROL4__(1728537748, 4);
                    }
                  }
                  else
                  {
                    v3851[5] = -2051698419;
                    v3504 = __ROR4__(-2051698419, 2);
                  }
                }
                else
                {
                  v3851[6] = -1297272415;
                  v3504 = __ROL4__(-1297272415, 1);
                }
              }
              else
              {
                v3851[7] = -795291432;
                v3504 = __ROR4__(-795291432, 6);
              }
              v3511 = i97;
              dword_140C0DF60[v3511] = v3504;
            }
            v3308 = v3788;
            v3512 = (_QWORD *)v3788;
            v3513 = (char *)v3788;
            v3514 = *(unsigned int *)(v3788 + 2020);
            v3515 = *(_DWORD *)(v3788 + 2068);
            v3516 = *(_QWORD *)(v3788 + 2072);
            if ( v3788 < v3788 + v3514 )
            {
              do
              {
                _mm_prefetchnta(v3513);
                v3513 += 64;
              }
              while ( (unsigned __int64)v3513 < v3788 + v3514 );
            }
            v3517 = (unsigned int)v3514 >> 7;
            for ( i98 = *(_QWORD *)(v3788 + 2072); v3517; --v3517 )
            {
              v3519 = 8i64;
              do
              {
                v3520 = v3512[1] ^ __ROL8__(*v3512 ^ i98, v3515);
                v3512 += 2;
                i98 = __ROL8__(v3520, v3515);
                --v3519;
              }
              while ( v3519 );
              v3521 = (__ROL8__(v3516 ^ ((unsigned __int64)v3512 - v3788), 17) ^ v3516 ^ ((unsigned __int64)v3512 - v3788))
                    * (unsigned __int128)0x7010008004002001ui64;
              v4082 = *((_QWORD *)&v3521 + 1);
              v3515 = ((unsigned __int8)v3521 ^ (unsigned __int8)(BYTE8(v3521) ^ v3515)) & 0x3F;
              if ( !v3515 )
                LOBYTE(v3515) = 1;
            }
            v3522 = v3514 & 0x7F;
            if ( v3522 >= 8 )
            {
              v3523 = (unsigned __int64)v3522 >> 3;
              do
              {
                i98 = __ROL8__(*v3512++ ^ i98, v3515);
                v3522 -= 8;
                --v3523;
              }
              while ( v3523 );
            }
            for ( ; v3522; --v3522 )
            {
              v3524 = *(unsigned __int8 *)v3512;
              v3512 = (_QWORD *)((char *)v3512 + 1);
              i98 = __ROL8__(v3524 ^ i98, v3515);
            }
            v3525 = 4;
            qword_140D1E9D0 = i98;
            v3526 = 4;
            v4351 = 4;
            v4112 = 0i64;
            v3527 = (int *)&v4113;
            do
            {
              *(_BYTE *)v3527 = 0;
              v3527 = (int *)((char *)v3527 + 1);
              --v3525;
            }
            while ( v3525 );
            v3528 = 0i64;
            if ( *(_DWORD *)(v3308 + 2060) )
            {
              v3529 = v4113;
              v3530 = HIDWORD(v4112);
              v3531 = v4112;
              while ( 1 )
              {
                v3532 = v3308;
                v3533 = 0;
                if ( *(_QWORD *)(v3308 + 2680) )
                  v3532 = *(_QWORD *)(v3308 + 2680);
                v3534 = (int *)(v3532 + *(unsigned int *)(v3532 + 2056));
                if ( v3531 && v3530 <= (unsigned int)v3528 )
                {
                  v3533 = v3530;
                  v3534 = (int *)(v3532 + v3529);
                }
                if ( v3533 != (_DWORD)v3528 )
                {
                  v3535 = (unsigned int)v3528 - v3533;
                  v3533 = v3528;
                  while ( 1 )
                  {
                    v3536 = *v3534;
                    if ( *v3534 > 28 )
                    {
                      v3544 = v3536 - 30;
                      if ( !v3544 )
                      {
                        v3542 = (((v3534[9] != 0 ? v3534[9] - 1 : 0) / 0xCu + 7) & 0xFFFFFFF8)
                              + 24 * (*((unsigned __int16 *)v3534 + 20) + 2);
                        goto LABEL_5076;
                      }
                      v3545 = v3544 - 3;
                      if ( !v3545 || (v3546 = v3545 - 1) == 0 )
                      {
                        v3542 = 20
                              * (unsigned int)(((v3534[8] & 0xFFF) + (unsigned __int64)(unsigned int)v3534[10] + 4095) >> 12)
                              + 48;
                        goto LABEL_5076;
                      }
                      v3541 = v3546 == 9;
                    }
                    else
                    {
                      if ( v3536 == 28 )
                      {
                        v3543 = *((unsigned __int16 *)v3534 + 20);
                        goto LABEL_5064;
                      }
                      v3537 = v3536 - 1;
                      if ( !v3537 )
                        goto LABEL_5073;
                      v3538 = v3537 - 6;
                      if ( !v3538 )
                      {
                        v3542 = (unsigned int)(24 * (v3534[6] + 2));
                        goto LABEL_5076;
                      }
                      v3539 = v3538 - 1;
                      if ( !v3539 )
                      {
                        v3543 = *((unsigned __int16 *)v3534 + 16);
LABEL_5064:
                        v3542 = (v3543 + 55) & 0xFFFFFFF8;
                        goto LABEL_5076;
                      }
                      v3540 = v3539 - 2;
                      if ( !v3540 )
                      {
                        v3542 = (unsigned int)(16 * (v3534[7] + 3));
                        goto LABEL_5076;
                      }
                      v3541 = v3540 == 2;
                    }
                    if ( v3541 )
                    {
LABEL_5073:
                      v3542 = 4 * (v3534[4] / 0xCu) + 48;
                      goto LABEL_5076;
                    }
                    v3542 = 48i64;
LABEL_5076:
                    v3534 = (int *)((char *)v3534 + v3542);
                    if ( !--v3535 )
                    {
                      v3308 = v3788;
                      break;
                    }
                  }
                }
                LODWORD(v4112) = 1;
                v3529 = (_DWORD)v3534 - v3532;
                HIDWORD(v4112) = v3533;
                v4113 = (_DWORD)v3534 - v3532;
                v3531 = 1;
                v3547 = *v3534;
                v3530 = v3533;
                if ( (unsigned int)v3547 <= 0x26 && (v3548 = 0x400020020Ci64, _bittest64(&v3548, v3547)) )
                {
                  ++v3526;
                  if ( (_DWORD)v3547 == 2 )
                    goto LABEL_5085;
                }
                else
                {
                  if ( (_DWORD)v3547 != 32 )
                  {
                    if ( (_DWORD)v3547 == 7 )
                    {
                      v3526 += v3534[6];
                    }
                    else if ( (_DWORD)v3547 == 33 )
                    {
                      v3550 = v3534 + 12;
                      v3551 = (unsigned __int64)&v3534[5
                                                     * (((unsigned int)v3534[10]
                                                       + 4095i64
                                                       + (*((_QWORD *)v3534 + 4) & 0xFFFui64)) >> 12)
                                                     + 12];
                      while ( v3550 != (int *)v3551 )
                      {
                        v3552 = v3526++;
                        if ( *((char *)v3550 + 15) < 0 )
                          v3526 = v3552;
                        v3550 += 5;
                      }
                    }
                    goto LABEL_5094;
                  }
                  v3549 = v3534[10];
                  if ( (v3549 & 2) == 0 && (v3549 & 1) != 0 )
LABEL_5085:
                    ++v3526;
                }
LABEL_5094:
                v3528 = (unsigned int)(v3528 + 1);
                if ( (unsigned int)v3528 >= *(_DWORD *)(v3308 + 2060) )
                {
                  v4351 = v3526;
                  break;
                }
              }
            }
            v3553 = __rdtsc();
            v3554 = (__ROR8__(v3553, 3) ^ v3553) * (unsigned __int128)0x7010008004002001ui64;
            v4083 = *((_QWORD *)&v3554 + 1);
            v3555 = ((unsigned __int64)v3554 ^ *((_QWORD *)&v3554 + 1)) % 0xB;
            if ( (unsigned int)v3555 > 5 )
            {
              v3559 = v3555 - 6;
              if ( v3559 )
              {
                v3560 = v3559 - 1;
                if ( v3560 )
                {
                  v3561 = v3560 - 1;
                  if ( v3561 )
                  {
                    if ( v3561 == 1 )
                    {
                      v3851[19] = -1333354875;
                      v3558 = (unsigned int)__ROR4__(-1333354868, 33);
                    }
                    else
                    {
                      v3562 = __rdtsc();
                      v3528 = 1321528399i64;
                      v3563 = __ROR8__(v3562, 3);
                      v4084 = ((v3563 ^ v3562) * (unsigned __int128)0x7010008004002001ui64) >> 64;
                      v3564 = (67117057 * (v3563 ^ v3562)) ^ v4084;
                      v3558 = ((((((v3564 % 0x1A + 97) << 8) | ((v3564 >> 5)
                                                              - 26
                                                              * ((unsigned int)((1321528399
                                                                               * (unsigned __int64)(v3564 >> 5)) >> 32) >> 3)
                                                              + 65)) << 8) | ((v3564 >> 10)
                                                                            - 26
                                                                            * ((unsigned int)((1321528399
                                                                                             * (unsigned __int64)(v3564 >> 10)) >> 32) >> 3)
                                                                            + 97)) << 8) | ((v3564 >> 15) % 0x1A + 65);
                    }
                  }
                  else
                  {
                    v3851[20] = 1684422978;
                    v3558 = (unsigned int)__ROR4__(1684422978, 8);
                  }
                }
                else
                {
                  v3851[21] = -2100910376;
                  v3558 = (unsigned int)__ROL4__(-2100910376, 7);
                }
              }
              else
              {
                v3851[22] = 1314342514;
                v3558 = (unsigned int)__ROR4__(1314342516, 24);
              }
            }
            else if ( (_DWORD)v3555 == 5 )
            {
              v3851[18] = 680282605;
              v3558 = (unsigned int)__ROR4__(680282605, 5);
            }
            else if ( (_DWORD)v3555 )
            {
              v3556 = v3555 - 1;
              if ( v3556 )
              {
                v3557 = v3556 - 1;
                if ( v3557 )
                {
                  if ( v3557 == 1 )
                  {
                    v3851[14] = -1474152136;
                    v3558 = (unsigned int)__ROR4__(-1474152133, 15);
                  }
                  else
                  {
                    v3851[13] = 1728537748;
                    v3558 = (unsigned int)__ROL4__(1728537748, 4);
                  }
                }
                else
                {
                  v3851[15] = -2051698419;
                  v3558 = (unsigned int)__ROR4__(-2051698419, 2);
                }
              }
              else
              {
                v3851[16] = -1297272415;
                v3558 = (unsigned int)__ROL4__(-1297272415, 1);
              }
            }
            else
            {
              v3851[17] = -795291432;
              v3558 = (unsigned int)__ROR4__(-795291432, 6);
            }
            v3565 = *(__int64 (__fastcall **)(__int64, __int64, __int64, __int64))(v3308 + 240);
            v3790 = (unsigned __int64)v3526 << 6;
            v3566 = v3565(64i64, v3790, v3558, v3528);
            if ( v3566 )
            {
              v3567 = __rdtsc();
              v3568 = (__ROR8__(v3567, 3) ^ v3567) * (unsigned __int128)0x7010008004002001ui64;
              v4085 = *((_QWORD *)&v3568 + 1);
              v4086[0] = v3568 ^ *((_QWORD *)&v3568 + 1) ^ (unsigned int)ExGenRandom(0i64);
              v3569 = __rdtsc();
              v3570 = (__ROR8__(v3569, 3) ^ v3569) * (unsigned __int128)0x7010008004002001ui64;
              v4086[1] = *((_QWORD *)&v3570 + 1);
              v3571 = v3566 + 8;
              v3794 = v3566 + 8;
              v3851[23] = ((unsigned __int64)v3570 ^ *((_QWORD *)&v3570 + 1) ^ (unsigned int)ExGenRandom(0i64)) % 0x3F
                        + 1;
              *(_QWORD *)(v3566 + 8) = 0i64;
              *(_QWORD *)(v3566 + 16) = 0i64;
              *(_WORD *)(v3566 + 24) = 4096;
              *(_QWORD *)(v3566 + 32) = v4086[0];
              *(_DWORD *)(v3566 + 40) = v3851[23];
              *(_DWORD *)(v3566 + 44) = 0;
              v3572 = MmStrongCodeGuaranteesEnforced();
              v3576 = 0;
              if ( v3572 )
              {
                v3577 = sub_140B32784(v3574, v3573, v3575, 0i64);
                v3576 = 0;
                if ( v3577 )
                  *(_DWORD *)(v3566 + 44) |= 1u;
              }
              if ( (v3836 & 0x10) != 0 )
                *(_DWORD *)(v3566 + 44) |= 4u;
              v3578 = 1;
              v4112 = 0i64;
              v3579 = (int *)&v4113;
              v3580 = 4;
              do
              {
                *(_BYTE *)v3579 = 0;
                v3579 = (int *)((char *)v3579 + 1);
                --v3580;
              }
              while ( v3580 );
              v3852 = 0;
              v3581 = 0;
              v3582 = 0i64;
              LODWORD(v3784) = 0;
              v3583 = 0i64;
              Timer = 0i64;
              v3792 = 0i64;
              LODWORD(Src) = 0;
              if ( *(_DWORD *)(v3308 + 2060) )
              {
                while ( 1 )
                {
                  v3584 = v3308;
                  if ( *(_QWORD *)(v3308 + 2680) )
                    v3584 = *(_QWORD *)(v3308 + 2680);
                  v3585 = v3584 + *(unsigned int *)(v3584 + 2056);
                  if ( (_DWORD)v4112 && HIDWORD(v4112) <= v3581 )
                  {
                    v3576 = HIDWORD(v4112);
                    v3585 = v3584 + v4113;
                  }
                  if ( v3576 != v3581 )
                  {
                    v3586 = v3581 - v3576;
                    v3576 = v3581;
                    while ( 1 )
                    {
                      v3587 = *(_DWORD *)v3585;
                      if ( *(int *)v3585 > 28 )
                      {
                        v3595 = v3587 - 30;
                        if ( !v3595 )
                        {
                          v3593 = (((*(_DWORD *)(v3585 + 36) != 0 ? *(_DWORD *)(v3585 + 36) - 1 : 0) / 0xCu + 7) & 0xFFFFFFF8)
                                + 24 * (*(unsigned __int16 *)(v3585 + 40) + 2);
                          goto LABEL_5154;
                        }
                        v3596 = v3595 - 3;
                        if ( !v3596 || (v3597 = v3596 - 1) == 0 )
                        {
                          v3593 = 20
                                * (unsigned int)(((*(_DWORD *)(v3585 + 32) & 0xFFF)
                                                + (unsigned __int64)*(unsigned int *)(v3585 + 40)
                                                + 4095) >> 12)
                                + 48;
                          goto LABEL_5154;
                        }
                        v3592 = v3597 == 9;
                      }
                      else
                      {
                        if ( v3587 == 28 )
                        {
                          v3594 = *(unsigned __int16 *)(v3585 + 40);
                          goto LABEL_5142;
                        }
                        v3588 = v3587 - 1;
                        if ( !v3588 )
                          goto LABEL_5151;
                        v3589 = v3588 - 6;
                        if ( !v3589 )
                        {
                          v3593 = (unsigned int)(24 * (*(_DWORD *)(v3585 + 24) + 2));
                          goto LABEL_5154;
                        }
                        v3590 = v3589 - 1;
                        if ( !v3590 )
                        {
                          v3594 = *(unsigned __int16 *)(v3585 + 32);
LABEL_5142:
                          v3593 = (v3594 + 55) & 0xFFFFFFF8;
                          goto LABEL_5154;
                        }
                        v3591 = v3590 - 2;
                        if ( !v3591 )
                        {
                          v3593 = (unsigned int)(16 * (*(_DWORD *)(v3585 + 28) + 3));
                          goto LABEL_5154;
                        }
                        v3592 = v3591 == 2;
                      }
                      if ( v3592 )
                      {
LABEL_5151:
                        v3593 = 4 * (*(_DWORD *)(v3585 + 16) / 0xCu) + 48;
                        goto LABEL_5154;
                      }
                      v3593 = 48i64;
LABEL_5154:
                      v3585 += v3593;
                      if ( !--v3586 )
                      {
                        v3308 = v3788;
                        v3582 = Timer;
                        v3583 = v3792;
                        break;
                      }
                    }
                  }
                  LODWORD(v4112) = 1;
                  HIDWORD(v4112) = v3576;
                  v4113 = v3585 - v3584;
                  v3598 = *(_DWORD *)v3585;
                  if ( (unsigned int)(*(_DWORD *)v3585 - 2) <= 1 )
                  {
                    v3658 = *(_QWORD *)(v3585 + 8);
                    v3659 = (unsigned __int64)v3578 << 6;
                    *(_QWORD *)(v3659 + v3566 + 8) = v3658;
                    *(_QWORD *)(v3659 + v3566 + 16) = *(unsigned int *)(v3585 + 16);
                    *(_WORD *)(v3659 + v3566 + 24) = 4101 - (*(_DWORD *)v3585 != 3);
                    *(_DWORD *)(v3659 + v3566 + 48) = *(_DWORD *)(v3585 + 40);
                    *(_WORD *)(v3659 + v3566 + 52) = *(_WORD *)(v3585 + 44);
                    sub_1403ED6CC(v3308, v3658, *(unsigned int *)(v3659 + v3566 + 16), v3659 + v3566 + 32);
                    v3582 = Timer;
                    v3576 = 0;
                    ++v3578;
                    if ( *(_DWORD *)v3585 == 2 )
                    {
                      v3660 = (unsigned __int64)v3578 << 6;
                      *(_QWORD *)(v3660 + v3566 + 8) = 0i64;
                      *(_QWORD *)(v3660 + v3566 + 16) = 0i64;
                      *(_WORD *)(v3660 + v3566 + 24) = 4107;
                      *(_DWORD *)(v3660 + v3566 + 32) = *(_DWORD *)(v3585 + 40);
LABEL_5234:
                      ++v3578;
                    }
                  }
                  else
                  {
                    switch ( v3598 )
                    {
                      case 9:
                        v3599 = *(_QWORD *)(v3585 + 8);
                        v3600 = (unsigned __int64)v3578 << 6;
                        *(_QWORD *)(v3600 + v3566 + 8) = v3599;
                        *(_QWORD *)(v3600 + v3566 + 16) = *(unsigned int *)(v3585 + 16);
                        *(_WORD *)(v3600 + v3566 + 24) = 4097;
                        sub_1403ED6CC(v3308, v3599, *(unsigned int *)(v3600 + v3566 + 16), v3600 + v3566 + 32);
                        v3582 = Timer;
                        ++v3578;
LABEL_5159:
                        v3576 = 0;
                        break;
                      case 32:
                        v3601 = *(_DWORD *)(v3585 + 40);
                        v3602 = 2i64;
                        if ( (v3601 & 2) == 0 && (v3601 & 1) != 0 )
                        {
                          LODWORD(v3603) = 16;
                          v3604 = (char *)(v3585 + 24);
                          v3605 = (unsigned __int64)v3578 << 6;
                          *(_QWORD *)(v3605 + v3566 + 8) = *(_QWORD *)(v3585 + 8);
                          *(_QWORD *)(v3605 + v3566 + 16) = *(unsigned int *)(v3585 + 16);
                          *(_WORD *)(v3605 + v3566 + 24) = 4097;
                          v3606 = (_QWORD *)(v3605 + v3566 + 32);
                          do
                          {
                            v3603 = (unsigned int)(v3603 - 8);
                            *v3606 = *(_QWORD *)v3604;
                            v3604 += 8;
                            ++v3606;
                            --v3602;
                          }
                          while ( v3602 );
                          if ( (_DWORD)v3603 )
                          {
                            do
                            {
                              v3607 = *v3604++;
                              *(_BYTE *)v3606 = v3607;
                              v3606 = (_QWORD *)((char *)v3606 + 1);
                              v875 = (_DWORD)v3603 == 1;
                              v3603 = (unsigned int)(v3603 - 1);
                            }
                            while ( !v875 );
                          }
                          v3608 = *(_QWORD *)(v3585 + 8);
                          v3609 = 0i64;
                          if ( v3608 )
                          {
                            if ( v3608 < (unsigned __int64)v3582 || v3608 >= v3583 )
                            {
                              v3611 = (*(__int64 (__fastcall **)(ULONG_PTR, char *, __int64))(v3308 + 520))(
                                        v3608,
                                        v4087,
                                        v3603);
                              v3582 = Timer;
                              v3610 = (struct _KTIMER *)v3611;
                            }
                            else
                            {
                              v3610 = v3582;
                            }
                          }
                          else
                          {
                            v3610 = 0i64;
                          }
                          if ( (*(_DWORD *)(v3585 + 40) & 4) != 0 )
                          {
                            *(_WORD *)(v3605 + v3566 + 24) = 4106;
                            v3612 = MmGetPhysicalAddress(*(PVOID *)(v3585 + 8));
                            v3582 = Timer;
                            *(_QWORD *)(v3605 + v3566 + 48) = (unsigned __int64)v3612.QuadPart >> 12;
                          }
                          else if ( v3610 )
                          {
                            v3613 = (*(__int64 (__fastcall **)(struct _KTIMER *, __int64, __int64))(v3308 + 504))(
                                      v3610,
                                      v3609,
                                      v3603);
                            v3614 = (unsigned int)(*(_DWORD *)(v3585 + 8) - (_DWORD)v3610);
                            v3792 = v3613;
                            v3615 = RtlSectionTableFromVirtualAddress(v3613, v3610, v3614);
                            if ( v3615 && (*(_DWORD *)(v3615 + 36) & 0x20000000) != 0 )
                              *(_BYTE *)(v3605 + v3566 + 47) |= 0x80u;
                            v3582 = v3610;
                            Timer = v3610;
                            v3792 = (ULONG_PTR)v3610 + *(unsigned int *)(v3792 + 80);
                          }
                          else
                          {
                            v3616 = *(_QWORD *)(v3585 + 8);
                            if ( v3616 + 0x88000000000i64 > 0xFFF )
                            {
                              v3617 = *(unsigned int *)(v3585 + 16);
                              if ( (_DWORD)v3617 )
                              {
                                if ( (unsigned int)v3617 > 0x1000 )
                                {
                                  v3854 = 317;
                                  KeBugCheckEx(__ROR4__(317, 160), 0xDui64, v3308, v3616, v3617);
                                }
                                *(_WORD *)(v3605 + v3566 + 24) = 4105;
                                *(_QWORD *)(v3605 + v3566 + 48) = (unsigned __int64)MmGetPhysicalAddress(*(PVOID *)(v3585 + 8)).QuadPart >> 12;
                                v3618 = MmGetPhysicalAddress((PVOID)(*(_QWORD *)(v3585 + 8)
                                                                   + (unsigned int)(*(_DWORD *)(v3585 + 16) - 1)));
                                v3582 = Timer;
                                *(_QWORD *)(v3605 + v3566 + 56) = (unsigned __int64)v3618.QuadPart >> 12;
                              }
                            }
                          }
                          ++v3578;
                        }
                        goto LABEL_5159;
                      case 7:
                        v3576 = 0;
                        v3619 = (_QWORD *)(v3585 + 48);
                        for ( i99 = 0;
                              i99 < *(_DWORD *)(v3585 + 24);
                              *(_DWORD *)(v3621 + v3566 + 48) = *((_DWORD *)v3619 - 2) )
                        {
                          v3621 = (unsigned __int64)v3578++ << 6;
                          ++i99;
                          *(_QWORD *)(v3621 + v3566 + 8) = 0i64;
                          *(_QWORD *)(v3621 + v3566 + 16) = 0i64;
                          *(_WORD *)(v3621 + v3566 + 24) = 4099;
                          *(_DWORD *)(v3621 + v3566 + 52) = *(_DWORD *)(v3585 + 28);
                          v3622 = *v3619;
                          v3619 += 3;
                          *(_QWORD *)(v3621 + v3566 + 32) = v3622;
                          *(_QWORD *)(v3621 + v3566 + 40) = *(v3619 - 2);
                        }
                        break;
                      case 21:
                      case 38:
                        v3656 = 4108;
                        v3657 = (unsigned __int64)v3578 << 6;
                        v3576 = 0;
                        *(_QWORD *)(v3657 + v3566 + 8) = 0i64;
                        *(_QWORD *)(v3657 + v3566 + 16) = 0i64;
                        if ( *(_DWORD *)v3585 != 38 )
                          v3656 = 4102;
                        *(_WORD *)(v3657 + v3566 + 24) = v3656;
                        *(_DWORD *)(v3657 + v3566 + 52) = *(_DWORD *)(v3585 + 44);
                        *(_QWORD *)(v3657 + v3566 + 32) = *(_QWORD *)(v3585 + 24);
                        *(_QWORD *)(v3657 + v3566 + 40) = *(_QWORD *)(v3585 + 32);
                        *(_DWORD *)(v3657 + v3566 + 48) = *(_DWORD *)(v3585 + 40);
                        goto LABEL_5234;
                      case 33:
                        v3623 = *(struct _KTIMER **)(v3585 + 32);
                        v3624 = *(unsigned int *)(v3585 + 40);
                        Timer = v3623;
                        v3783 = ((unsigned __int64)((unsigned __int16)v3623 & 0xFFF) + 4095 + v3624) >> 12;
                        v3785 = (*(__int64 (__fastcall **)(struct _KTIMER *, __int64))(v3308 + 504))(v3623, 4097i64);
                        v3625 = 0i64;
                        v4345 = 0;
                        v3792 = (ULONG_PTR)v3623 + *(unsigned int *)(v3585 + 40);
                        _disable();
                        v3626 = *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + *(_QWORD *)(v3308 + 1616));
                        _enable();
                        (*(void (__fastcall **)(__int64))(v3308 + 360))(v3626);
                        LOBYTE(v3627) = 1;
                        (*(void (__fastcall **)(_QWORD, __int64))(v3308 + 224))(*(_QWORD *)(v3308 + 1328), v3627);
                        v3629 = (PVOID *)PsLoadedModuleList;
                        if ( PsLoadedModuleList != &PsLoadedModuleList )
                        {
                          v3630 = *(_QWORD *)(v3308 + 1872);
                          while ( 1 )
                          {
                            v3631 = (char *)v3629 - v3630;
                            v3632 = *(unsigned __int64 *)((char *)v3629 + *(_QWORD *)(v3308 + 1880) - v3630);
                            v3628 = v3632 + *(unsigned int *)((char *)v3629 + *(_QWORD *)(v3308 + 1888) - v3630);
                            if ( (unsigned __int64)v3623 >= v3632 && (unsigned __int64)v3623 < v3628 )
                              break;
                            v3629 = (PVOID *)*v3629;
                            if ( v3629 == &PsLoadedModuleList )
                              goto LABEL_5207;
                          }
                          v3633 = v3853;
                          v4345 = 1;
                          v3634 = 4;
                          do
                          {
                            *v3633++ = 0;
                            --v3634;
                          }
                          while ( v3634 );
                          v3635 = *(_QWORD *)(v3308 + 1896);
                          v3636 = 0;
                          do
                          {
                            if ( v3636 >= *(unsigned __int16 *)&v3631[v3635] >> 1 )
                              break;
                            v3637 = v3636++;
                            v3853[v3637] = *(_BYTE *)(*(_QWORD *)&v3631[v3635 + 8] + 2 * v3637);
                          }
                          while ( v3636 < 4 );
                          LODWORD(v3628) = 4;
                          v3638 = 0i64;
                          do
                          {
                            v3853[v3638 - 4] = v3853[v3638];
                            ++v3638;
                            v875 = (_DWORD)v3628 == 1;
                            v3628 = (unsigned int)(v3628 - 1);
                          }
                          while ( !v875 );
                        }
LABEL_5207:
                        (*(void (__fastcall **)(_QWORD, unsigned __int64))(v3308 + 280))(
                          *(_QWORD *)(v3308 + 1328),
                          v3628);
                        (*(void (**)(void))(v3308 + 368))();
                        v3639 = v3585 + 48;
                        v3576 = 0;
                        v3852 = v4345 != 0 ? v3852 : 0;
                        i100 = v3585 + 48 + 20 * v3783;
                        v3783 = i100;
                        if ( v3585 + 48 != i100 )
                        {
                          v3641 = Timer;
                          v3642 = Timer;
                          do
                          {
                            if ( *(char *)(v3639 + 15) >= 0 )
                            {
                              if ( *(int *)(v3639 + 16) < 0 )
                                *(_WORD *)(((unsigned __int64)v3578 << 6) + v3566 + 26) |= 1u;
                              v3643 = (unsigned __int64)v3578 << 6;
                              v3644 = 16;
                              v3645 = v3643 + v3566;
                              *(_QWORD *)(v3645 + 8) = v3642;
                              v3646 = (_QWORD *)(v3643 + v3566 + 32);
                              *(_QWORD *)(v3645 + 16) = 4096i64;
                              v3647 = 2i64;
                              *(_WORD *)(v3645 + 24) = 4098;
                              *(_QWORD *)(v3645 + 48) = v3641;
                              v3648 = (char *)v3639;
                              *(_DWORD *)(v3645 + 56) = ((char *)v3642 - (char *)v3641) / 4096;
                              do
                              {
                                v3644 -= 8;
                                *v3646 = *(_QWORD *)v3648;
                                v3648 += 8;
                                ++v3646;
                                --v3647;
                              }
                              while ( v3647 );
                              for ( i100 = v3783; v3644; --v3644 )
                              {
                                v3649 = *v3648++;
                                *(_BYTE *)v3646 = v3649;
                                v3646 = (_QWORD *)((char *)v3646 + 1);
                              }
                              v3650 = 4;
                              v3651 = v3643 - (_QWORD)&v3852;
                              v3652 = &v3852;
                              do
                              {
                                *((_BYTE *)v3652 + v3651 + v3566 + 60) = *(_BYTE *)v3652;
                                v3652 = (int *)((char *)v3652 + 1);
                                --v3650;
                              }
                              while ( v3650 );
                              v3576 = 0;
                              v3653 = (unsigned int)(*(_DWORD *)(v3645 + 56) << 12);
                              if ( !v3625 || (unsigned int)v3653 >= (unsigned int)Src )
                              {
                                v3654 = RtlSectionTableFromVirtualAddress(v3785, v3641, v3653);
                                i100 = v3783;
                                v3576 = 0;
                                v3625 = v3654;
                                if ( v3654 )
                                  v3655 = *(_DWORD *)(v3654 + 8) + *(_DWORD *)(v3654 + 12);
                                else
                                  v3655 = *(_DWORD *)(*(unsigned __int16 *)(v3785 + 20) + v3785 + 36);
                                LODWORD(Src) = v3655;
                              }
                              *(_BYTE *)(v3645 + 47) &= ~0x80u;
                              if ( v3625 && (*(_DWORD *)(v3625 + 36) & 0x20000000) != 0 )
                                *(_BYTE *)(v3645 + 47) |= 0x80u;
                              ++v3578;
                            }
                            v3639 += 20i64;
                            v3642 += 64;
                          }
                          while ( v3639 != i100 );
                          v3308 = v3788;
                        }
                        v3582 = Timer;
                        break;
                      default:
                        goto LABEL_5159;
                    }
                  }
                  v3581 = v3784 + 1;
                  LODWORD(v3784) = v3581;
                  if ( v3581 >= *(_DWORD *)(v3308 + 2060) )
                  {
                    v3526 = v4351;
                    v3571 = v3566 + 8;
                    break;
                  }
                  v3583 = v3792;
                }
              }
              _InterlockedOr(v3779, 0);
              *(_QWORD *)&MaxDataSize = v3308;
              v3661 = (unsigned __int64)v3578 << 6;
              *(_QWORD *)(v3661 + v3566 + 8) = &MaxDataSize;
              *(_QWORD *)(v3661 + v3566 + 16) = 8i64;
              *(_WORD *)(v3661 + v3566 + 24) = 4097;
              sub_1403ED6CC(v3308, &MaxDataSize, 8i64, v3566 + v3661 + 32);
              v3662 = v3578 + 1;
              v3663 = (unsigned __int64)v3662 << 6;
              *(_QWORD *)(v3663 + v3566 + 8) = *(_QWORD *)&MaxDataSize;
              *(_QWORD *)(v3663 + v3566 + 16) = *(_DWORD *)(v3308 + 2020) & 0xFFFFF000;
              *(_WORD *)(v3663 + v3566 + 24) = 4097;
              sub_1403ED6CC(
                v3308,
                *(_QWORD *)(v3663 + v3566 + 8),
                *(unsigned int *)(v3663 + v3566 + 16),
                v3663 + v3566 + 32);
              v3664 = (unsigned __int64)(v3662 + 1) << 6;
              *(_QWORD *)(v3664 + v3566 + 8) = &qword_140D1E9D0;
              *(_QWORD *)(v3664 + v3566 + 16) = 8i64;
              *(_WORD *)(v3664 + v3566 + 24) = 4097;
              sub_1403ED6CC(v3308, &qword_140D1E9D0, 8i64, v3566 + v3664 + 32);
              if ( v3526 )
              {
                v3665 = v3526;
                do
                {
                  v3666 = *(_QWORD **)v3571;
                  v3667 = *(unsigned int *)(v3571 + 8);
                  v3668 = *(_QWORD **)v3571;
                  v3669 = *(_QWORD *)v3571 + v3667;
                  if ( *(_QWORD *)v3571 < v3669 )
                  {
                    do
                    {
                      _mm_prefetchnta(v3668);
                      v3668 += 8;
                    }
                    while ( (unsigned __int64)v3668 < v3669 );
                  }
                  v3670 = v4086[0];
                  do
                  {
                    v3671 = ((unsigned int)v3666 & 0xFFFFF000) + 4096 - (_DWORD)v3666;
                    if ( (unsigned int)v3667 < v3671 )
                      v3671 = v3667;
                    LODWORD(v3667) = v3667 - v3671;
                    if ( v3671 >= 8 )
                    {
                      v3672 = (unsigned __int64)v3671 >> 3;
                      do
                      {
                        v3671 -= 8;
                        v3670 = __ROR8__(*v3666++ ^ v3670, v3851[23]);
                        --v3672;
                      }
                      while ( v3672 );
                    }
                    for ( ; v3671; --v3671 )
                    {
                      v3673 = *(unsigned __int8 *)v3666;
                      v3666 = (_QWORD *)((char *)v3666 + 1);
                      v3670 = __ROR8__(v3673 ^ v3670, v3851[23]);
                    }
                  }
                  while ( (_DWORD)v3667 );
                  v3674 = v3794;
                  *(_QWORD *)(v3794 - 8) = v3670;
                  v3571 = v3674 + 64;
                  v3794 = v3674 + 64;
                  --v3665;
                }
                while ( v3665 );
                v3308 = v3788;
              }
              if ( (v3836 & 8) != 0 )
              {
                ExFreePool((PVOID)v3566);
                goto LABEL_5256;
              }
              v3675 = KiConnectSwInterrupt(v3566, v3526);
              memset((void *)v3566, 0, v3790);
              memset(v4086, 0, 8ui64);
              memset(&v3851[23], 0, sizeof(int));
              ExFreePool((PVOID)v3566);
              if ( v3675 >= 0 )
              {
LABEL_5256:
                if ( v3787 )
                  v4298(v3787);
                v3676 = __rdtsc();
                v3677 = v4324;
                v3678 = (__ROR8__(v3676, 3) ^ v3676) * (unsigned __int128)0x7010008004002001ui64;
                v3836 = *((_QWORD *)&v3678 + 1);
                v3679 = *((_QWORD *)&v3678 + 1) ^ v3678;
                if ( (v4334 & 0x10000000) != 0 )
                {
                  v3680 = __rdtsc();
                  v3681 = (__ROR8__(v3680, 3) ^ v3680) * (unsigned __int128)0x7010008004002001ui64;
                  v4088 = *((_QWORD *)&v3681 + 1);
                  v3677 = (_DWORD *)(v4310 + 16 * ((v3681 ^ *((_QWORD *)&v3681 + 1)) & 0xF));
                }
                v3682 = 40;
                v3683 = &v4326;
                v3684 = &v4179;
                v3685 = 5i64;
                do
                {
                  v3682 -= 8;
                  *(_QWORD *)v3684 = *(_QWORD *)v3683;
                  v3683 += 2;
                  v3684 += 2;
                  --v3685;
                }
                while ( v3685 );
                for ( ; v3682; --v3682 )
                {
                  v3686 = *(_BYTE *)v3683;
                  v3683 = (int *)((char *)v3683 + 1);
                  *(_BYTE *)v3684 = v3686;
                  v3684 = (int *)((char *)v3684 + 1);
                }
                if ( (v4334 & 0x8000) != 0 || !v4326 )
                {
                  if ( (v4334 & 0x40000000) != 0 )
                    goto LABEL_5341;
                  v3687 = v3308 ^ v3679;
                  v3688 = (unsigned __int8)(v4331 - 1);
                  v3689 = __rdtsc();
                  v3690 = (__ROR8__(v3689, 3) ^ v3689) * (unsigned __int128)0x7010008004002001ui64;
                  v4089 = *((_QWORD *)&v3690 + 1);
                  v3691 = v3688 + (*((_QWORD *)&v3690 + 1) ^ (unsigned __int64)v3690) % (unsigned int)(63 - v3688);
                  do
                  {
                    v3692 = __rdtsc();
                    v3693 = __ROR8__(v3692, 3) ^ v3692;
                    v4090 = (v3693 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                    v3694 = v3688 + (v4090 ^ (0x7010008004002001i64 * v3693)) % (unsigned int)(63 - v3688);
                  }
                  while ( v3694 == v3691 );
                  v3695 = v4321;
                  v3696 = v3691;
                  i101 = v4322;
                  v3698 = (v3687 | (1i64 << v3696)) & ~(1i64 << v3694);
                  v4352 = v4322;
                  if ( v4332 == 3 && (v3699 = v3786) != 0 )
                  {
                    v3700 = v4304;
                    *v4322 = 19;
                    i101[1] = 1;
                    *((_WORD *)i101 + 1) = 0;
                    *((_QWORD *)i101 + 3) = v3700;
                    *((_QWORD *)i101 + 4) = v3699;
                    *((_QWORD *)i101 + 7) = 0i64;
                    *((_QWORD *)i101 + 2) = 0i64;
                    *((_QWORD *)i101 + 5) = v3698;
                    v4303(*(_QWORD *)(v3699 + 8), *(unsigned int *)(v3699 + 16), *(_QWORD *)v3699);
                    v3701 = *(_QWORD *)v3699;
                    v3702 = v3699 ^ __ROL8__(v3699, 17);
                    v3703 = 4;
                    v4091 = (v3702 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                    v3704 = v3702 ^ v4091;
                    v3705 = (0x7010008004002001i64 * v3702) ^ v4091;
                    v3706 = (_QWORD *)(v3786 + 24);
                    do
                    {
                      *v3706 ^= v3705;
                      v3705 = __ROL8__(v3705, v3703);
                      --v3706;
                      --v3703;
                    }
                    while ( v3703 );
                    if ( (v3704 & 0xFu) < 7 )
                    {
                      v3707 = 6;
                      v3708 = v3701 ^ __ROL8__(v3701, 17);
                      v4092 = ((unsigned __int64)v3708 * (unsigned __int128)0x7010008004002001ui64) >> 64;
                      v3709 = ((0x7010008004002001i64 * v3708) ^ v4092) + v3705;
                      v3710 = (_QWORD *)(v3701 + 40);
                      v3711 = (unsigned int)*(__int16 *)(v3701 + 8);
                      do
                      {
                        *v3710 ^= v3709;
                        v3709 = __ROL8__(v3709, v3707);
                        --v3710;
                        --v3707;
                      }
                      while ( v3707 );
                      v3712 = (unsigned __int64)(v3711 - 48) >> 3;
                      if ( (_DWORD)v3712 )
                      {
                        v3713 = (_QWORD *)(v3701 + 8 * ((int)v3712 + 5i64));
                        do
                        {
                          *v3713 ^= v3709;
                          v3709 = __ROL8__(v3709, v3712);
                          --v3713;
                          LODWORD(v3712) = v3712 - 1;
                        }
                        while ( (_DWORD)v3712 );
                      }
                    }
                  }
                  else
                  {
                    *v4322 = 19;
                    i101[1] = 1;
                    *((_WORD *)i101 + 1) = 0;
                    *((_QWORD *)i101 + 3) = v3677;
                    *((_QWORD *)i101 + 4) = v3698;
                    *((_QWORD *)i101 + 7) = 0i64;
                    *((_QWORD *)i101 + 2) = 0i64;
                  }
                  *((_QWORD *)i101 + 8) = v3679;
                  if ( (v4334 & 0x100) != 0 )
                  {
                    v3714 = (__int64)(v3677 - 18);
                    *((_QWORD *)v3677 - 1) = i101;
                    v3715 = __rdtsc();
                    v3716 = 25i64;
                    v3717 = (__ROR8__(v3715, 3) ^ v3715) * (unsigned __int128)0x7010008004002001ui64;
                    v4093 = *((_QWORD *)&v3717 + 1);
                    v3718 = v3717 ^ *((_QWORD *)&v3717 + 1);
                    v3719 = v3677;
                    do
                    {
                      *v3719++ ^= v3718;
                      --v3716;
                    }
                    while ( v3716 );
                    *v3677 = 1213280584;
                    *(_QWORD *)(v3714 + 32) = v3718;
                  }
                  else
                  {
                    v3714 = (__int64)i101;
                  }
                  if ( v4339 )
                  {
                    v3720 = *(_QWORD *)(v4339 + 32);
                    v3721 = v4308 ^ ((v3720 ^ ((v3720 ^ 0xE5D49100ui64) >> 4)) >> 4);
                    v3722 = v3721;
                    v3723 = (v4308 ^ ((v3720 ^ ((v3720 ^ 0xE5D49100ui64) >> 4)) >> 4)) & 0xF;
                    if ( !v3723 )
                      v3723 = 1;
                    do
                    {
                      v3724 = (__int64 *)(v3720 + (v3721 & 0xF));
                      v3720 = *v3724;
                      v3721 ^= (*v3724 ^ ((*v3724 ^ 0x1E5200ui64) >> 4)) >> 4;
                      --v3723;
                    }
                    while ( v3723 );
                    if ( (v3722 & 0x1000) != 0 )
                      v3714 ^= v3722;
                    *v3724 = v3714;
                    v3714 = v4339;
                  }
                  _InterlockedOr(v3779, 0);
                  if ( v4325 )
                  {
                    switch ( v4325 )
                    {
                      case 1:
                        *(_QWORD *)(v4323 + v4311) = v3714;
                        break;
                      case 2:
                        *(_QWORD *)(v4323 + 128) = v3714;
                        break;
                      case 3:
                        v3736 = v4335;
                        if ( *(_QWORD *)(v4335 + v4318) )
                        {
                          if ( !v4326 )
                          {
                            v4330 = *(_QWORD *)(v4335 + v4318);
                            v4328 = 0i64;
                            v4329 = 260i64;
                            v4327 = &v3779[0xE8E80FD62472332Aui64];
                            v4326 = 1;
                            __ba(v4297, 0i64);
                          }
                          v3737 = 5i64;
                          v3738 = &v4326;
                          v3739 = &v4179;
                          v3740 = 40;
                          do
                          {
                            v3740 -= 8;
                            *(_QWORD *)v3739 = *(_QWORD *)v3738;
                            v3738 += 2;
                            v3739 += 2;
                            --v3737;
                          }
                          while ( v3737 );
                          for ( i101 = v4352; v3740; --v3740 )
                          {
                            v3741 = *(_BYTE *)v3738;
                            v3738 = (int *)((char *)v3738 + 1);
                            *(_BYTE *)v3739 = v3741;
                            v3739 = (int *)((char *)v3739 + 1);
                          }
                        }
                        _InterlockedOr(v3779, 0);
                        *(_QWORD *)(v3736 + v4318) = i101;
                        break;
                      case 4:
                        v3728 = v4338;
                        v3729 = v4337;
                        v3730 = v4336;
                        v3731 = v4335;
                        *v4336 = 18;
                        v3730[2] = 88;
                        v3730[80] = 0;
                        *((_QWORD *)v3730 + 1) = v3731;
                        *((_QWORD *)v3730 + 4) = v3729;
                        *((_QWORD *)v3730 + 5) = 0i64;
                        *((_QWORD *)v3730 + 6) = v3728;
                        v3730[81] = 0;
                        *((_QWORD *)v3730 + 7) = 0i64;
                        v3730[82] = 0;
                        if ( !v4302(v4336, i101, 0i64, 0i64) )
                        {
                          if ( !v4326 )
                          {
                            v4328 = 0i64;
                            v4329 = 260i64;
                            v4330 = v3731;
                            v4327 = &v3779[0xE8E80FD62472332Aui64];
                            v4326 = 1;
                            __ba(v4297, 0i64);
                          }
                          v3732 = &v4326;
                          v3733 = 40;
                          v3734 = &v4179;
                          do
                          {
                            v3733 -= 8;
                            *(_QWORD *)v3734 = *(_QWORD *)v3732;
                            v3732 += 2;
                            v3734 += 2;
                            --v3881;
                          }
                          while ( v3881 );
                          for ( ; v3733; --v3733 )
                          {
                            v3735 = *(_BYTE *)v3732;
                            v3732 = (int *)((char *)v3732 + 1);
                            *(_BYTE *)v3734 = v3735;
                            v3734 = (int *)((char *)v3734 + 1);
                          }
                        }
                        break;
                      default:
                        v3725 = (_DWORD *)v4335;
                        *(_QWORD *)(v4335 + 72) = v3714;
                        _InterlockedOr(v3779, 0);
                        v3726 = __rdtsc();
                        v3727 = (__ROR8__(v3726, 3) ^ v3726) * (unsigned __int128)0x7010008004002001ui64;
                        v4094 = *((_QWORD *)&v3727 + 1);
                        *v3725 = (__int64)(((unsigned __int64)v3727 ^ *((_QWORD *)&v3727 + 1)) % 0x5F5E100 + 1200000000)
                               / 10000000;
                        break;
                    }
                  }
                  else
                  {
                    v3742 = __rdtsc();
                    v3743 = (__ROR8__(v3742, 3) ^ v3742) * (unsigned __int128)0x7010008004002001ui64;
                    v4095 = *((_QWORD *)&v3743 + 1);
                    v3744 = -1200000000i64 - ((unsigned __int64)v3743 ^ *((_QWORD *)&v3743 + 1)) % 0x5F5E100;
                    *(_QWORD *)&v3743 = __rdtsc();
                    v3745 = (__ROR8__(v3743, 3) ^ (unsigned __int64)v3743) * (unsigned __int128)0x7010008004002001ui64;
                    v4096 = *((_QWORD *)&v3745 + 1);
                    v4300(v3695, v3744, 0i64, ((unsigned __int64)v3745 ^ *((_QWORD *)&v3745 + 1)) % 0x2710, v3714);
                  }
                }
                if ( v4179 && (v4334 & 0x8000) == 0 )
                {
                  v3746 = v4182;
                  v3747 = v4183;
                  v3748 = v4181;
                  v3749 = v4180;
                  v4353 = v4182;
                  HalExtensionList = v4183;
                  v3788 = v4181;
                  v3787 = v4180;
                  if ( KeGetCurrentIrql() < 2u )
                  {
                    KeGetCurrentIrql();
                    __writecr8(2ui64);
                  }
                  CurrentPrcb = KeGetCurrentPrcb();
                  v3751 = *(_QWORD *)((char *)&CurrentPrcb->MxCsr + v4312);
                  v3752 = *(_QWORD *)((char *)&CurrentPrcb->MxCsr + v4314);
                  if ( !*((_BYTE *)&CurrentPrcb->MxCsr + v4313)
                    || (unsigned __int64)&v4097 > v3751
                    || (unsigned __int64)&v4097 < v3751 - 24576 )
                  {
                    v3751 = *(_QWORD *)(v3752 + v4315);
                  }
                  if ( (v4334 & 0x8000000) == 0 )
                  {
                    v3753 = __readcr0();
                    __writecr0(v3753 & 0xFFFFFFFFFFFEFFFFui64);
                    v3754 = v4342;
                    v3755 = &v4342[v4340];
                    v3756 = 0;
                    for ( i102 = v3755; v3756 < v4341; ++v3756 )
                    {
                      *(_QWORD *)*i102 = i102[1];
                      v3758 = __readcr4();
                      if ( (v3758 & 0x20080) != 0 )
                      {
                        __writecr4(v3758 ^ 0x80);
                        __writecr4(v3758);
                      }
                      else
                      {
                        v3759 = __readcr3();
                        __writecr3(v3759);
                      }
                      i102 += 2;
                    }
                    if ( v4342 < v3755 )
                    {
                      do
                      {
                        v3760 = *((unsigned int *)v3754 + 2);
                        v3761 = i102;
                        v3762 = *(char **)v3754;
                        v3763 = v3760;
                        if ( (unsigned int)v3760 >= 8 )
                        {
                          v3764 = (unsigned __int64)(unsigned int)v3760 >> 3;
                          do
                          {
                            v3763 -= 8;
                            *(_QWORD *)v3762 = *v3761++;
                            v3762 += 8;
                            --v3764;
                          }
                          while ( v3764 );
                        }
                        if ( v3763 )
                        {
                          v3765 = v3762 - (char *)v3761;
                          do
                          {
                            *((_BYTE *)v3761 + v3765) = *(_BYTE *)v3761;
                            v3761 = (_QWORD *)((char *)v3761 + 1);
                            --v3763;
                          }
                          while ( v3763 );
                        }
                        i102 = (_QWORD *)((char *)i102 + v3760);
                        ++v3754;
                      }
                      while ( v3754 < v3755 );
                      v3746 = v4353;
                      v3747 = HalExtensionList;
                    }
                    *v4301 = -61;
                    __writecr0(v3753);
                    v3748 = v3788;
                    v3749 = v3787;
                  }
                  v3773 = v4333;
                  if ( v4333 )
                  {
                    if ( KeGetCurrentIrql() < 2u )
                    {
                      KeGetCurrentIrql();
                      __writecr8(2ui64);
                      v3773 = v4333;
                    }
                    if ( v3773 )
                    {
                      v3774 = v3773 - 1;
                      if ( v3774 )
                      {
                        v3775 = v3774 - 1;
                        if ( v3775 )
                        {
                          v3776 = v3775 - 1;
                          if ( v3776 )
                          {
                            v3777 = v3776 - 1;
                            if ( v3777 )
                            {
                              if ( v3777 == 1 )
                                _interlockedbittestandset(
                                  *(volatile signed __int32 **)((char *)&KeGetCurrentPrcb()->MxCsr + v4314),
                                  (v4334 >> 10) & 0x1F);
                              else
                                _InterlockedOr64((volatile signed __int64 *)(v4309 + 832), 1ui64);
                            }
                            else
                            {
                              _interlockedbittestandset(
                                *(volatile signed __int32 **)(v4316
                                                            + *(_QWORD *)((char *)&KeGetCurrentPrcb()->MxCsr + v4314)
                                                            + v4320),
                                (v4334 >> 10) & 0x1F);
                            }
                            goto LABEL_5427;
                          }
                          v3778 = v4307;
                        }
                        else
                        {
                          v3778 = v4306;
                        }
                      }
                      else
                      {
                        v3778 = v4305;
                      }
                      _interlockedbittestandset64(v3778, 0i64);
                    }
                  }
LABEL_5427:
                  *(_QWORD *)(v3752 + v4317) = 0i64;
                  *(_QWORD *)(v3752 + v4319) = 0i64;
                  SdbpCheckDll(265, v3749, v3748, v3747, v3746, Target, v3751);
                  __debugbreak();
                }
LABEL_5341:
                _disable();
                if ( !(_BYTE)KdDebuggerNotPresent )
                {
                  while ( 1 )
                    ;
                }
                _enable();
                v3766 = (struct _KEVENT *)HalExtensionList;
                if ( HalExtensionList )
                {
                  *(_QWORD *)(HalExtensionList + 16) = v3859;
                  _InterlockedOr(v3779, 0);
                  KeSetEvent(v3766 + 1, 1, 0);
                }
                v3767 = v4297;
                v3768 = 2720;
                v3769 = 340i64;
                do
                {
                  *(_QWORD *)v3767 = 0i64;
                  v3768 -= 8;
                  v3767 += 8;
                  --v3769;
                }
                while ( v3769 );
                for ( ; v3768; --v3768 )
                  *v3767++ = 0;
                _disable();
                if ( !(_BYTE)KdDebuggerNotPresent )
                {
                  while ( 1 )
                    ;
                }
                _enable();
                return 1;
              }
            }
            v3855 = 317;
            KeBugCheckEx(__ROR4__(317, 160), 0x15ui64, v3308, (unsigned int)v3836, v3787);
          }
          v2438 = *((_DWORD *)v2367 + 612);
          if ( (v2438 & 4) == 0 )
          {
            v2439 = *((_DWORD *)v2367 + 505);
            v2440 = *((_QWORD *)v2367 + 249);
            v2441 = (v2438 & 0x20000000) != 0 ? *((_DWORD *)v2367 + 585) : 0;
            if ( v2439 >= 8 )
            {
              v2442 = (unsigned __int64)v2439 >> 3;
              do
              {
                *(_QWORD *)v2367 = 0i64;
                v2439 -= 8;
                v2367 += 8;
                --v2442;
              }
              while ( v2442 );
            }
            for ( ; v2439; --v2439 )
              *v2367++ = 0;
            v2443 = *(_DWORD *)(v2437 + 2340);
            *(_DWORD *)(v2437 + 2340) = v2441;
            if ( v2441 == 3 )
            {
              (*(void (__fastcall **)(__int64))(v2437 + 872))(v2440);
            }
            else if ( (*(_DWORD *)(v2437 + 2448) & 0x10000000) != 0 || !v2441 )
            {
              (*(void (__fastcall **)(__int64))(v2437 + 248))(v2440);
            }
            else
            {
              (*(void (__fastcall **)(__int64, _QWORD))(v2437 + 552))(v2440 - 8, *(_QWORD *)(v2440 - 8));
            }
            v2434 = v3785;
            *(_DWORD *)(v2437 + 2340) = v2443;
          }
          *(_DWORD *)(v2437 + 2448) &= ~4u;
          v2433 = v3783;
          v2432 = v3784;
        }
        *(_DWORD *)(v2437 + 2060) += v2428;
        v2444 = v2437 + v2434;
        if ( v2428 )
        {
          v2445 = v2413;
          v3790 = v2428;
          v3786 = (unsigned __int64)v2427;
          do
          {
            v2446 = (unsigned int)*v2427;
            v2447 = 48;
            v2448 = (_QWORD *)*v2445;
            v2449 = (_QWORD *)v2444;
            LODWORD(v3785) = *v2427;
            v2450 = 6i64;
            do
            {
              *v2449 = 0i64;
              v2447 -= 8;
              ++v2449;
              --v2450;
            }
            while ( v2450 );
            for ( ; v2447; --v2447 )
            {
              *(_BYTE *)v2449 = 0;
              v2449 = (_QWORD *)((char *)v2449 + 1);
            }
            *(_DWORD *)v2444 = v2433;
            *(_QWORD *)(v2444 + 8) = v2448;
            if ( v2432 == 7 && (_DWORD)v2446 )
              sub_1403ED6CC(v2437, v2448, (unsigned int)v2446, v2444 + 24);
            *(_DWORD *)(v2444 + 16) = v2446;
            *(_DWORD *)(v2437 + 2088) += v2446;
            v2451 = v2448;
            v2452 = *(_DWORD *)(v2437 + 2068);
            v2453 = (char *)v2448;
            v2454 = *(_QWORD *)(v2437 + 2072);
            if ( v2448 < (_QWORD *)((char *)v2448 + v2446) )
            {
              do
              {
                _mm_prefetchnta(v2453);
                v2453 += 64;
              }
              while ( v2453 < (char *)v2448 + v2446 );
            }
            v2455 = *(_QWORD *)(v2437 + 2072);
            v2456 = (unsigned int)v2446 >> 7;
            if ( (unsigned int)v2446 >> 7 )
            {
              do
              {
                v2457 = 8i64;
                do
                {
                  v2458 = v2451[1] ^ __ROL8__(*v2451 ^ v2455, v2452);
                  v2451 += 2;
                  v2455 = __ROL8__(v2458, v2452);
                  --v2457;
                }
                while ( v2457 );
                v2459 = (__ROL8__(v2454 ^ ((char *)v2451 - (char *)v2448), 17) ^ v2454 ^ (unsigned __int64)((char *)v2451 - (char *)v2448))
                      * (unsigned __int128)0x7010008004002001ui64;
                v4039 = *((_QWORD *)&v2459 + 1);
                v2452 = ((unsigned __int8)v2459 ^ (unsigned __int8)(BYTE8(v2459) ^ v2452)) & 0x3F;
                if ( !v2452 )
                  LOBYTE(v2452) = 1;
                --v2456;
              }
              while ( v2456 );
              v2437 = v3787;
              LODWORD(v2446) = v3785;
              v2427 = (_DWORD *)v3786;
            }
            v2460 = v2446 & 0x7F;
            if ( v2460 >= 8 )
            {
              v2461 = (unsigned __int64)(v2446 & 0x7F) >> 3;
              do
              {
                v2455 = __ROL8__(*v2451++ ^ v2455, v2452);
                v2460 -= 8;
                --v2461;
              }
              while ( v2461 );
            }
            for ( ; v2460; --v2460 )
            {
              v2462 = *(unsigned __int8 *)v2451;
              v2451 = (_QWORD *)((char *)v2451 + 1);
              v2455 = __ROL8__(v2462 ^ v2455, v2452);
            }
            for ( i103 = v2455 >> 31; i103; i103 >>= 31 )
              LODWORD(v2455) = i103 ^ v2455;
            v2433 = v3783;
            v2432 = v3784;
            ++v2427;
            *(_DWORD *)(v2444 + 20) = v2455 & 0x7FFFFFFF;
            ++v2445;
            *(_DWORD *)(v2437 + 2088) += v2446;
            v2444 += 48i64;
            v875 = v3790-- == 1;
            v3786 = (unsigned __int64)v2427;
          }
          while ( !v875 );
          v2427 = (_DWORD *)v3788;
          v2413 = (_QWORD *)HalExtensionList;
        }
        v2367 = (_BYTE *)v2437;
        goto LABEL_3543;
      }
      v4176 = (__int64 (__fastcall **)())HvlpHypercallCodeVa;
      v2355 = __cpuid(0x40000000, 0);
      v2353 = EAX(v2355);
      v2354 = EDX(v2355);
      v4127 = __PAIR64__(ECX(v2355), EBX(v2355));
      v4126 = v2353;
      v4128 = v2354;
      if ( v4127 != 0x666F736F7263694Di64 )
        goto LABEL_3386;
      if ( v2354 != 1984438388 )
        goto LABEL_3386;
      if ( v2353 < 0x40000002 )
        goto LABEL_3386;
      v2356 = __cpuid(1073741825, 0);
      v4126 = EAX(v2356);
      v4127 = __PAIR64__(ECX(v2356), EBX(v2356));
      v4128 = EDX(v2356);
      if ( v4126 != 824407624 )
        goto LABEL_3386;
      v2358 = __cpuid(1073741826, 0);
      v2357 = EBX(v2358);
      v4126 = EAX(v2358);
      v4127 = __PAIR64__(ECX(v2358), v2357);
      v4128 = EDX(v2358);
      if ( (v2357 & 0xFFFF0000) == 393216 && (unsigned __int16)v2357 == 1 )
        v2359 = 4;
      else
LABEL_3386:
        v2359 = 4096;
      LODWORD(v3783) = 1;
    }
    else
    {
      v4176 = HvlpInterruptCallback;
      v2359 = dword_140D815F8;
    }
    v2352 = 2;
    v4125[1] = v2359;
    goto LABEL_3390;
  }
  v1877 = *((unsigned int *)v1845 + 505);
  v1878 = v1877 + 16 * v1875 + 48;
  if ( v1878 <= *((_DWORD *)v1845 + 647) )
  {
    v1879 = (__int64)v1845;
    *((_DWORD *)v1845 + 505) = v1878;
  }
  else
  {
    v1879 = sub_140B0F020(v1845, v1878, *((_DWORD *)v1845 + 585));
    if ( !v1879 )
      return 0;
    v1880 = *((_DWORD *)v1845 + 612);
    if ( (v1880 & 4) == 0 )
    {
      v1881 = *((_DWORD *)v1845 + 505);
      v1882 = *((_QWORD *)v1845 + 249);
      v1883 = (v1880 & 0x20000000) != 0 ? *((_DWORD *)v1845 + 585) : 0;
      if ( v1881 >= 8 )
      {
        v1884 = (unsigned __int64)v1881 >> 3;
        do
        {
          *(_QWORD *)v1845 = 0i64;
          v1881 -= 8;
          v1845 += 8;
          --v1884;
        }
        while ( v1884 );
      }
      for ( ; v1881; --v1881 )
        *v1845++ = 0;
      v1885 = *(_DWORD *)(v1879 + 2340);
      *(_DWORD *)(v1879 + 2340) = v1883;
      if ( v1883 == 3 )
      {
        (*(void (__fastcall **)(__int64))(v1879 + 872))(v1882);
      }
      else if ( (*(_DWORD *)(v1879 + 2448) & 0x10000000) != 0 || !v1883 )
      {
        (*(void (__fastcall **)(__int64))(v1879 + 248))(v1882);
      }
      else
      {
        (*(void (__fastcall **)(__int64, _QWORD))(v1879 + 552))(v1882 - 8, *(_QWORD *)(v1882 - 8));
      }
      *(_DWORD *)(v1879 + 2340) = v1885;
    }
    *(_DWORD *)(v1879 + 2448) &= ~4u;
  }
  ++*(_DWORD *)(v1879 + 2060);
  v1886 = v1879 + v1877;
  v1887 = 48;
  v1888 = (_QWORD *)(v1879 + v1877);
  v1889 = 6i64;
  do
  {
    *v1888 = 0i64;
    v1887 -= 8;
    ++v1888;
    --v1889;
  }
  while ( v1889 );
  for ( ; v1887; --v1887 )
  {
    *(_BYTE *)v1888 = 0;
    v1888 = (_QWORD *)((char *)v1888 + 1);
  }
  *(_DWORD *)v1886 = 10;
  *(_QWORD *)(v1886 + 8) = 0i64;
  *(_DWORD *)(v1886 + 16) = 0;
  v1890 = *(_QWORD *)(v1879 + 2072);
  for ( i104 = v1890; ; LODWORD(v1890) = i104 ^ v1890 )
  {
    i104 >>= 31;
    if ( !i104 )
      break;
  }
  v1892 = v1886 + 48;
  *(_DWORD *)(v1886 + 20) = v1890 & 0x7FFFFFFF;
  v1845 = (_BYTE *)v1879;
  *(_DWORD *)(v1886 + 24) = 0;
  *(_DWORD *)(v1886 + 28) = v1875;
  v1893 = 0;
  if ( *(_DWORD *)(HalExtensionList + 16) )
  {
    while ( 1 )
    {
      v1894 = v3788 + ((__int64)*(int *)(v3788 + 4i64 * v1893) >> 4);
      if ( !(*(__int64 (__fastcall **)(ULONG_PTR, char *, _QWORD))(v1879 + 608))(v1894, v4018, 0i64) )
      {
        v1895 = (unsigned __int8 *)v1894;
        *(_DWORD *)(v1879 + 2088) += 4;
        v1896 = (char *)v1894;
        v1897 = *(_QWORD *)(v1879 + 2072);
        if ( v1894 < v1894 + 4 )
        {
          do
          {
            _mm_prefetchnta(v1896);
            v1896 += 64;
          }
          while ( (unsigned __int64)v1896 < v1894 + 4 );
        }
        v1898 = 4;
        do
        {
          v1899 = *v1895++;
          v1897 = __ROL8__(v1899 ^ v1897, *(_DWORD *)(v1879 + 2068));
          --v1898;
        }
        while ( v1898 );
        for ( i105 = v1897; ; LODWORD(v1897) = i105 ^ v1897 )
        {
          i105 >>= 31;
          if ( !i105 )
            break;
        }
        *(_DWORD *)v1892 ^= (*(_DWORD *)v1892 ^ v1897) & 0x7FFFFFFF;
        *(_DWORD *)(v1892 + 4) = 4;
        *(_QWORD *)(v1892 + 8) = v1894;
        v1892 += 16i64;
        if ( !--v1875 )
          break;
      }
      if ( ++v1893 >= *(_DWORD *)(HalExtensionList + 16) )
        return 0;
    }
    goto LABEL_2728;
  }
  return 0;
}