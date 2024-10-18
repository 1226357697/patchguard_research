#include "InlineHook.h"
#include "./third/zydis/Zydis.h"
#include <intrin.h>

#pragma warning(disable : 4996)

#define ExAllocateMemeory(size)  ExAllocatePoolWithTag(NonPagedPool, size, 'HOOK')
#define ExFreeMemeory(p) ExFreePoolWithTag(p, 'HOOK')

#pragma pack(push)
#pragma pack(1)
typedef struct _JMP64_NEAR_STUB {
  UINT8  opcode0;     // FF25 00000000: JMP [+6]
  UINT8  opcode1;
  UINT32 dummy;
  UINT64 address;     // Absolute destination address
} JMP64_NEAR_STUB;
#pragma pack(pop)

// 最多会覆盖掉 sizeof(JMP64_NEAR_STUB) + one instruct(15)
#define MAX_OVERWRITE_INSTRUCT (sizeof(JMP64_NEAR_STUB) + 15)
typedef struct _TRAMPOLINE_CHUNK {
  SIZE_T originInstSize;
  UCHAR originInst[MAX_OVERWRITE_INSTRUCT];
  UCHAR trampolineInst[MAX_OVERWRITE_INSTRUCT + sizeof(JMP64_NEAR_STUB) + 0x10];
  PVOID targetAddress;
}TRAMPOLINE_CHUNK;

static NTSTATUS SimulateMemLeaInst(ZydisDisassembledInstruction* leaInst, PVOID buffer, ZyanUSize* size)
{
  NTSTATUS status = STATUS_UNSUCCESSFUL;

  if(leaInst->info.mnemonic != ZYDIS_MNEMONIC_LEA)
    return STATUS_INVALID_PARAMETER;
  
  ZydisEncoderRequest req;
  memset(&req, 0, sizeof(req));

  ULONGLONG target = (LONGLONG)(leaInst->runtime_address + leaInst->info.length + leaInst->info.raw.disp.value);

  req.mnemonic = ZYDIS_MNEMONIC_MOV;
  req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
  req.operand_count = 2;

  req.operands[0].type = leaInst->operands[0].type;
  req.operands[0].reg.value = leaInst->operands[0].reg.value;
  req.operands[1].type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
  req.operands[1].imm.u = target;

  if (ZYAN_SUCCESS(ZydisEncoderEncodeInstruction(&req, buffer, size)))
    status = STATUS_SUCCESS;

  return status;
}

static TRAMPOLINE_CHUNK* CreateTrampoline(PVOID targetAddress)
{
  NTSTATUS status = STATUS_UNSUCCESSFUL;
  ULONG placeSize = 0;
  ULONG instIndex = 0;
  ZydisDisassembledInstruction zydisInst;
  TRAMPOLINE_CHUNK* trampolineChunk = NULL;

  trampolineChunk = (TRAMPOLINE_CHUNK*)ExAllocateMemeory(sizeof(TRAMPOLINE_CHUNK));
  if(trampolineChunk == NULL)
    return NULL;

  // 一条一条把originInstBlock 的指令拷贝的trampolineBlock， 需要修复相对偏移指令的机器码
  // TODO: in case, analyze ret 
  while (placeSize < sizeof(JMP64_NEAR_STUB))
  {
    if (!ZYAN_SUCCESS(ZydisDisassembleIntel(
      ZYDIS_MACHINE_MODE_LONG_64,
      (ZyanU64)targetAddress + placeSize,
      (PUCHAR)targetAddress + placeSize,
      0x100 - placeSize,
      &zydisInst)))
    {
      // 可能是混淆导致失败
      RtlCopyMemory(trampolineChunk->trampolineInst + instIndex, (PUCHAR)targetAddress + placeSize, sizeof(JMP64_NEAR_STUB) - placeSize);
      placeSize = sizeof(JMP64_NEAR_STUB);
      break;
    }
      
    
    if (zydisInst.info.raw.modrm.mod == 0 && zydisInst.info.raw.modrm.rm == 5)
    {
      // rip relative addressing
      ULONGLONG target =(LONGLONG)(zydisInst.runtime_address + zydisInst.info.length + zydisInst.info.raw.disp.value );
      ULONGLONG relativeOffet = (ULONGLONG)(target - (ULONGLONG)trampolineChunk->trampolineInst + instIndex + zydisInst.info.length);
      if (relativeOffet <= ULONG_MAX)
      {
        RtlCopyMemory(trampolineChunk->trampolineInst + instIndex, (PUCHAR)targetAddress + placeSize, zydisInst.info.length);
        *(PULONG)(trampolineChunk->trampolineInst + instIndex + zydisInst.info.raw.disp.offset) = (ULONG)relativeOffet;
        instIndex += zydisInst.info.length;
      }
      else
      {
        // division two addring
        if (zydisInst.info.mnemonic == ZYDIS_MNEMONIC_LEA)
        {
          // lea reg, [0xXXXXXXX]
          ZyanUSize len = sizeof(trampolineChunk->trampolineInst) - instIndex;
          SimulateMemLeaInst(&zydisInst, trampolineChunk->trampolineInst + instIndex, &len);
          instIndex += (ULONG)len;
        }
        else if (zydisInst.info.mnemonic == ZYDIS_MNEMONIC_MOV)
        {
          // mov reg, [0xXXXXXXX]
          ASSERT(0);
        }
        else if (zydisInst.info.mnemonic == ZYDIS_MNEMONIC_JMP)
        {
          // jmp reg, [0xXXXXXXX]
          ASSERT(0);
        }
        else if (zydisInst.info.mnemonic == ZYDIS_MNEMONIC_CALL)
        {
          // call reg, [0xXXXXXXX]
          ASSERT(0);
        }
      }
    }
    else if (zydisInst.info.meta.branch_type != ZYDIS_BRANCH_TYPE_NONE && zydisInst.info.raw.imm[0].is_relative)
    {
      LONGLONG target = (ULONGLONG)(zydisInst.runtime_address + zydisInst.info.length + zydisInst.info.raw.imm[0].value.s);
      ULONGLONG imm = target - (ULONGLONG)trampolineChunk->trampolineInst + instIndex + zydisInst.info.length;
      if (imm > MAXULONG)
      {
        if (zydisInst.info.mnemonic == ZYDIS_MNEMONIC_CALL)
        {
          // 破逼 zydis ，编码不了 call [mem]
          //转化成 
          // call [target_address] 
          // jmp jmp_lab 
          // target_address 
          // jmp_lab:
          // xxx
          UCHAR* patch_insts = trampolineChunk->trampolineInst + instIndex;
          UCHAR repalce_bytes[] = {
            0xFF, 0x15, 0x02, 0x00, 0x00, 0x00, 0xEB, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
          };
          PLONGLONG replace_address = (PLONGLONG)(repalce_bytes + 8);
          *replace_address = target;

          memcpy(patch_insts, repalce_bytes, sizeof(repalce_bytes));
          instIndex += sizeof(repalce_bytes);
        }
        else 
        {
          
          ASSERT(0);
        }
      }
      else
      {
        RtlCopyMemory(trampolineChunk->trampolineInst + instIndex, (PUCHAR)targetAddress + placeSize, zydisInst.info.length);
        *(PLONG)(trampolineChunk->trampolineInst + instIndex + zydisInst.info.raw.imm[0].offset) = (LONG)imm;
        instIndex += zydisInst.info.length;
      }
    }
    else
    {
      RtlCopyMemory(trampolineChunk->trampolineInst + instIndex, (PUCHAR)targetAddress + placeSize, zydisInst.info.length);
      instIndex += zydisInst.info.length;
    }

    placeSize += zydisInst.info.length;
  }

  ASSERT(placeSize <= MAX_OVERWRITE_INSTRUCT);
  trampolineChunk->targetAddress = targetAddress;
  trampolineChunk->originInstSize = placeSize;

  // 直接拷贝将要被覆盖的指令
  RtlCopyMemory(trampolineChunk->originInst, trampolineChunk->targetAddress, trampolineChunk->originInstSize);

  JMP64_NEAR_STUB* jmpStub = (JMP64_NEAR_STUB*)(trampolineChunk->trampolineInst + instIndex);
  jmpStub->opcode0 = 0xff;
  jmpStub->opcode1 = 0x25;
  jmpStub->dummy = 0;
  jmpStub->address = ((UINT64)trampolineChunk->targetAddress) + trampolineChunk->originInstSize;

  return trampolineChunk;
}

typedef struct _MdlMapping {
  PMDL mdl;
  PVOID mapping;
}MdlMapping;

static VOID FreeMdlMapping(MdlMapping* mdlmap)
{
  if (mdlmap->mapping)
    MmUnmapLockedPages(mdlmap->mapping, mdlmap->mdl);

  MmUnlockPages(mdlmap->mdl);

  if (mdlmap->mdl)
    IoFreeMdl(mdlmap->mdl);
}

static NTSTATUS MdlMappingMemory(PVOID target, ULONG size, MdlMapping* mdlmap)
{
  NTSTATUS status = STATUS_UNSUCCESSFUL;
 
  do
  {
    mdlmap->mdl = IoAllocateMdl(target, size, FALSE, FALSE, NULL);
    if (mdlmap->mdl == NULL)
    {
      status = STATUS_INSUFFICIENT_RESOURCES;
      break;
    }
    __try
    {
      MmProbeAndLockPages(mdlmap->mdl, KernelMode, IoReadAccess);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
      status = STATUS_INSUFFICIENT_RESOURCES;
      break;
    }

    mdlmap->mapping = MmMapLockedPagesSpecifyCache(mdlmap->mdl, KernelMode, MmNonCached, NULL, FALSE, NormalPagePriority);
    if (mdlmap->mapping == NULL)
      break;

    status = MmProtectMdlSystemAddress(mdlmap->mdl, PAGE_READWRITE);
    if (!NT_SUCCESS(status))
      break;

    return STATUS_SUCCESS;

  } while (false);

  FreeMdlMapping(mdlmap);

  return status;
}

NTSTATUS SetInlineHook(PVOID targetFunction, PVOID detourFucntion, PVOID* originalFucntion)
{
  NTSTATUS status = STATUS_UNSUCCESSFUL;
  
  /*
  *  check param is valid
  */
  if(!MmIsAddressValid(targetFunction) || !MmIsAddressValid(detourFucntion) || !MmIsAddressValid(originalFucntion))
    return STATUS_INVALID_PARAMETER;

  TRAMPOLINE_CHUNK* trampoline = CreateTrampoline(targetFunction);
  if (trampoline)
  {
    *originalFucntion = trampoline->trampolineInst;

    // replace the target fucntion to jmp stub detour function
    MdlMapping mdlmap;
    status = MdlMappingMemory(targetFunction, MAX_OVERWRITE_INSTRUCT, &mdlmap);
    if (NT_SUCCESS(status))
    {
      // CPU不可以发生中断，也别被系统切换了
      _disable();
      KIRQL OldIrql = KeRaiseIrqlToDpcLevel();

      JMP64_NEAR_STUB* jmpStub = (JMP64_NEAR_STUB*)mdlmap.mapping;
      jmpStub->opcode0 = 0xff;
      jmpStub->opcode1 = 0x25;
      jmpStub->dummy = 0;
      jmpStub->address = (UINT64)detourFucntion;

      KeLowerIrql(OldIrql);
      _enable();

      FreeMdlMapping(&mdlmap);
      return STATUS_SUCCESS;
    }
  }
        
  return status;
}

static VOID Sleep(LONGLONG msec)
{
  LARGE_INTEGER interval;
  interval.QuadPart = -10 * 1000 * msec;
  KeDelayExecutionThread(KernelMode, FALSE, &interval);
}

NTSTATUS RemoveInlineHook(PVOID targetFunction, PVOID originalFucntion)
{
  if (!MmIsAddressValid(targetFunction) || !MmIsAddressValid(originalFucntion))
    return STATUS_INVALID_PARAMETER;

  NTSTATUS status = STATUS_UNSUCCESSFUL;
  TRAMPOLINE_CHUNK* trampoline = CONTAINING_RECORD(originalFucntion, TRAMPOLINE_CHUNK, trampolineInst);

  // replace the target fucntion to jmp stub detour function
  MdlMapping mdlmap;
  status = MdlMappingMemory(targetFunction, MAX_OVERWRITE_INSTRUCT, &mdlmap);
  if (NT_SUCCESS(status))
  {
    // CPU不可以发生中断，也别被系统切换了
    _disable();
    KIRQL OldIrql = KeRaiseIrqlToDpcLevel();

    RtlCopyMemory(mdlmap.mapping, trampoline->originInst, trampoline->originInstSize);
    
    KeLowerIrql(OldIrql);
    _enable();

    FreeMdlMapping(&mdlmap);

    // wait some time
    Sleep(100);
    ExFreeMemeory(trampoline);
    return STATUS_SUCCESS;
  }

  return status;
}

