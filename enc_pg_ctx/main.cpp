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

uint64_t KiWaitNever = 0x6ab044059fdd7af6;
uint64_t KiWaitAlways = 0x00b3fbf32de56818;

uint8_t move_table[16] { 0x09, 0x0A, 0x0C, 0x01, 0x0F, 0x00, 0x05, 0x0E, 0x04, 0x03, 0x07, 0x0D, 0x08, 0x06, 0x02, 0x0B };
 
unsigned int btc(unsigned int n, unsigned int pos) {
  // 测试并翻转 pos 位
  // pos 是从 0 开始计算的
  unsigned int bit = (n >> pos) & 1;  // 取出 pos 位的值
  printf("原来的第 %u 位是: %u\n", pos, bit);  // 打印测试位的值
  n ^= (1U << pos);  // 翻转 pos 位
  return n;
}
unsigned long long btc64(unsigned long long n, unsigned long long  pos) {
  // 测试并翻转 pos 位
  // pos 是从 0 开始计算的
  unsigned long bit_pos = n % 64;  // 计算位位置，模 64 是因为寄存器是 64 位
  unsigned int bit = (n >> pos) & 1;  // 取出 pos 位的值
  //printf("原来的第 %u 位是: %u\n", pos, bit);  // 打印测试位的值
  n ^= (1ULL << pos);  // 翻转 pos 位
  return n;
}

buffer_t get_enc_context_data()
{
  buffer_t data;
  fs::path enc_data_path("../note/解密算法测试/pg_undec.bin");
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
  fs::path enc_data_path("../note/解密算法测试/test_pg_undec.bin");
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
  uint32_t end_loop = 25;
  uint32_t end2_loop = 16;
  uint32_t i = 0;
  while (i < end_loop)
  {
    uint64_t item = pg_ctx_ptr[i];
    pg_ctx_ptr[i] = _byteswap_uint64(_rotl64(pg_ctx_ptr[i] ^ KiWaitNever, (char)KiWaitNever) ^ PGDecodeKey) ^ KiWaitAlways;
    pg_ctx_ptr[i] = pg_ctx_ptr[i] + i + PGContextPtr;

    char tmp_shift_key = (char)(~item & 0x3f);
    PGDecodeKey = PGDecodeKey ^ _rotr64(((200 - i) ^ i), tmp_shift_key);
    PGDecodeKey = _rotl64(PGDecodeKey, tmp_shift_key);
    PGDecodeKey = PGDecodeKey + PGContextPtr;
    PGDecodeKey = PGDecodeKey ^ 0xFB006943;

    for (uint32_t j = 0; j < end2_loop; ++j)
    {
      pg_ctx_ptr[i] = _rotl64(pg_ctx_ptr[i], 4);
      int mi = (pg_ctx_ptr[i] & 0xf);
      int move = move_table[mi];
      pg_ctx_ptr[i] = pg_ctx_ptr[i] & 0xFFFFFFFFFFFFFFF0;

      pg_ctx_ptr[i] = pg_ctx_ptr[i] | move;
    }
    i ++;

    if (i == 25)
    {
      #define CONST_XOR_VALUE 0x17042898A40898A4ULL
      uint64_t value = CONST_XOR_VALUE >> 55 | CONST_XOR_VALUE << 9;
      if ((value ^ pg_ctx_ptr[0]) != 0)
      {
        uint64_t tmp_dec = value;
        tmp_dec ^= pg_ctx_ptr[i - 1];
        tmp_dec ^= pg_ctx_ptr[0];
        pg_ctx_ptr[i - 1] = tmp_dec;

        end_loop += ((uint32_t*)&pg_ctx_ptr[i])[-1];

        tmp_dec = value;
        tmp_dec ^= pg_ctx_ptr[i - 1];
        tmp_dec ^= pg_ctx_ptr[0];
        pg_ctx_ptr[i - 1] = tmp_dec;

      }
      end2_loop = 1;
    }
  }
  //write_dec_conetxt_data(enc_ctx);
  printf("解密context第一次完毕\n");
  // 可以简化成 85131481131482E
  PGDecodeKey = 0x6244935FAD1B6FF5 ^ 0x6A15A217BC2A27DB ^ pg_ctx_ptr[0] ;
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
    int count = *(int*)(tmp_data + 0xc4);
    for (int i = count ; i >= 0xc8 / 8; --i)
    {
      pg_ctx_ptr[i] ^= PGDecodeKey;
      PGDecodeKey = _rotr64(PGDecodeKey, i);
      PGDecodeKey = btc64(PGDecodeKey, PGDecodeKey);
    }
  }


  printf("解密context第二次完毕\n");

  return 0;
}