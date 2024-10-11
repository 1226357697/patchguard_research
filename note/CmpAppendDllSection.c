__int64 __fastcall CmpAppendDllSection(struct_Context_Function *a1, __int64 a2)
{
  struct_Context_Function *v2; // rcx
  __int64 v3; // rax
  struct_Context_Function *v4; // rdx
  __int64 v5; // rcx
  __int64 v6; // rax
  struct_Context_Function *v7; // rax

  *(_QWORD *)&a1->unsigned_int0 ^= a2;
  *((_QWORD *)&a1->unsigned_int0 + 1) ^= a2;
  *(_QWORD *)a1->CmpAppendDllSection ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[8] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[16] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[24] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[32] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[40] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[48] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[56] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[64] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[72] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[80] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[88] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[96] ^= a2;
  *(_QWORD *)&a1->CmpAppendDllSection[104] ^= a2;
  v2 = (struct_Context_Function *)&a1->CmpAppendDllSection[104];
  *((_QWORD *)&v2->unsigned_int0 + 1) ^= a2;
  *(_QWORD *)v2->CmpAppendDllSection ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[8] ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[16] ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[24] ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[32] ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[40] ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[48] ^= a2;
  *(_QWORD *)&v2->CmpAppendDllSection[56] ^= a2;
  v2 = (struct_Context_Function *)((char *)v2 - 120);
  v2->unsigned_int0 ^= a2;
  v3 = a2;
  v4 = v2;
  v5 = *(unsigned int *)&v2->CmpAppendDllSection[180];
  if ( v3 )
  {
    do
    {
      *(_QWORD *)&v4->CmpAppendDllSection[8 * v5 + 176] ^= v3;
      v6 = __ROR8__(v3, v5);
      v3 = v6 ^ (1i64 << v6);
      --v5;
    }
    while ( v5 );
  }
  v7 = (struct_Context_Function *)((__int64 (__fastcall *)(__int64))((char *)v4 + (unsigned int)v4->dword7E8))(v5);
  return ((__int64 (__fastcall *)(_BYTE *, __int64))v7->ExQueueWorkItem)(v7->pg_WorkItem_gap798, 1i64);
}