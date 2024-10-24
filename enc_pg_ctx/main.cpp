#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
using buffer_t = std::vector<char>;
using string = std::string;

uint64_t DeferredContext = 0x0378c3bcbe1ed466;
uint64_t SystemArgument1 = 0x1d;
uint64_t SystemArgument2 = 0xbbf0a934;
uint64_t PGContextPtr = 0xfca74a37ac1fd4e3;
uint64_t PGDecodeKey = 0;

//uint64_t DeferredContext = 0x8e6f30fcae2830d0;
//uint64_t SystemArgument1 = 0x00000001;
//uint64_t SystemArgument2 = 0x10c274d;
//uint64_t PGContextPtr = 0x7310b977bc2932f3;
//uint64_t PGDecodeKey = 0;

uint64_t KiWaitNever = 0x6ab044059fdd7af6;
uint64_t KiWaitAlways = 0x00b3fbf32de56818;

uint8_t move_table[16] { 0x09, 0x0A, 0x0C, 0x01, 0x0F, 0x00, 0x05, 0x0E, 0x04, 0x03, 0x07, 0x0D, 0x08, 0x06, 0x02, 0x0B };
 

unsigned long long btc64(unsigned long long n, unsigned long long  pos) 
{
  unsigned long bit_pos = pos % 64;  
  n ^= (1ULL << bit_pos);
  return n;
}

buffer_t get_enc_context_data()
{
  buffer_t data;
  fs::path enc_data_path("../note/解密算法测试/pg_undec.bin");
  //fs::path enc_data_path("D:\\pg_ctx930.bin");
  std::ifstream ifs(enc_data_path, std::ios::binary);
  if (ifs.is_open())
  {
    ifs.seekg(0, std::ios::end);
    data.resize(ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    ifs.read(data.data(), data.size());
  }
  return data;
}

void write_dec_conetxt_data(buffer_t data)
{
  //fs::path enc_data_path("D:\\test_pg_undec.bin");
  
  fs::path enc_data_path("../note/解密算法测试/test_pg_undec.bin");
  std::ofstream ifs(enc_data_path, std::ios::binary);
  if (ifs.is_open())
  {
    ifs.write(data.data(), data.size());
  }
}

void write_denc_conetxt_data(buffer_t data)
{
  //fs::path enc_data_path("D:\\test_pg_unenc.bin");

  fs::path enc_data_path("../note/解密算法测试/test_pg_unenc.bin");
  std::ofstream ifs(enc_data_path, std::ios::binary);
  if (ifs.is_open())
  {
    ifs.write(data.data(), data.size());
  }
}

void dec_pg_context_ptr()
{
  // PGContextPtr ^ DeferredContext | FFFF800000000000
  //
  PGContextPtr = PGContextPtr ^ DeferredContext | 0xFFFF800000000000;
}

int main()
{
  buffer_t enc_ctx = get_enc_context_data();
  dec_pg_context_ptr();
  printf("解密后PGContextPtr:%llX\n", PGContextPtr);

  char shift_key = PGContextPtr & 0x3f;
  PGDecodeKey = _rotr64( PGContextPtr, shift_key);

  // 解密move_table
  // 00 03 05 08 06 09 0c 07 0d 0a 0e 04 01 0f 0b 02
  for (int i = 0; i< sizeof(move_table); ++i)
  {
    move_table[i] ^= 9;
  }
  printf("开始第一次解密context\n");

  // 解密pg_context
  uint64_t* pg_ctx_ptr = (uint64_t*)enc_ctx.data();
  const uint32_t CmpAppendDllSection_Size = 0xc8;
  const uint32_t CmpAppendDllSection_Count = 0xc8 / 8;
  uint32_t count = CmpAppendDllSection_Count;
  uint32_t sub_count = sizeof(move_table);
  for (uint32_t i = 0; i < count; ++i)
  {
    uint64_t item = pg_ctx_ptr[i];
    pg_ctx_ptr[i] = _byteswap_uint64(_rotl64(pg_ctx_ptr[i] ^ KiWaitNever, (char)KiWaitNever) ^ PGDecodeKey) ^ KiWaitAlways;
    pg_ctx_ptr[i] = pg_ctx_ptr[i] + i + PGContextPtr;

    for (uint32_t j = 0; j < sub_count; ++j)
    {
      pg_ctx_ptr[i] = _rotl64(pg_ctx_ptr[i], 4);
      int byte = (pg_ctx_ptr[i] & 0xf);
      pg_ctx_ptr[i] = (pg_ctx_ptr[i] & (~0XF)) | move_table[byte];
    }

    // 更新滚动密钥
    char tmp_shift_key = (char)(~item & 0x3f);
    PGDecodeKey = PGDecodeKey ^ _rotr64(((CmpAppendDllSection_Size - i) ^ i), tmp_shift_key);
    PGDecodeKey = (_rotl64(PGDecodeKey, tmp_shift_key) + PGContextPtr) ^ 0xFB006943;


    //继续 解密context body
    if (i == CmpAppendDllSection_Count - 1)
    {
#define CONST_XOR_VALUE 0x17042898A40898A4ULL
      uint64_t value = CONST_XOR_VALUE >> 55 | CONST_XOR_VALUE << 9;
      if ((value ^ pg_ctx_ptr[0]) != 0)
      {
        uint64_t tmp_dec = value;
        tmp_dec ^= pg_ctx_ptr[CmpAppendDllSection_Count - 1] ^ pg_ctx_ptr[0];

        count += *(((uint32_t*)&tmp_dec) + 1);
      }

      sub_count = 1;
    }
  }

  write_dec_conetxt_data(enc_ctx);
  printf("解密context第一次完毕\n");
  // 可以简化成 85131481131482E
  //PGDecodeKey = 0x6244935FAD1B6FF5 ^ 0x6A15A217BC2A27DB ^ pg_ctx_ptr[0] ;
  PGDecodeKey = 0x85131481131482E ^ pg_ctx_ptr[0] ;
  printf("PGDecodeKey: %llX\n", PGDecodeKey);

  printf("开始第二次解密context\n");
  char* tmp_data =  enc_ctx.data();
  //tmp_data[0] = 0x2e;
  //tmp_data[1] = 0x48;
  //tmp_data[2] = 0x31;
  //tmp_data[3] = 0x11;

  // 解密 CmpAppendDllSection
  // 大小C0
  for (int i = 0; i < 0xc8/8;++i)
  {
    pg_ctx_ptr[i] ^= PGDecodeKey;
  }

  // 解密context体
  if (PGDecodeKey != 0)
  {
    uint64_t* ctx_body =(uint64_t*)( (char*)pg_ctx_ptr + 0xc0);
    int count = *(int*)(tmp_data + 0xc4);
    for (int i = count ; i > 0; --i)
    {
      ctx_body[i] ^= PGDecodeKey;
      PGDecodeKey = _rotr64(PGDecodeKey, i);
      PGDecodeKey = btc64(PGDecodeKey, PGDecodeKey);
    }
  }


  printf("解密context第二次完毕\n");
  write_denc_conetxt_data(enc_ctx);
  return 0;
}