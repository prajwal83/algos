#include <iostream>
#include "../../test_framework/catch.hpp"

std::pair<uint32_t, uint32_t> nextNumberWithSameBits(uint32_t n)
{
  int c = n;
  bool isPrevZero = false;
  bool isPrevOne = false;
  int c1 = -1;
  int c1OneCount = 0;
  int c0 = -1;
  int c0OneCount = 0;
  for(int i = 0; i < 32; ++i)
  {
    if(c & 0x1)
    {
      if(c1 == -1)
        ++c1OneCount;
      if(c0 == -1)
        ++c0OneCount;
      if(isPrevZero && c1 == -1)
        c1 = i;
      isPrevZero = false;
      isPrevOne = true;
    }
    else
    {
      if(isPrevOne && c0 == -1)
        c0 = i;
      isPrevOne = false;
      isPrevZero = true;
    }
    if(c0 != -1 && c1 != -1)
      break;
    c >>= 1;
  }

  uint32_t next = n;
  if(c0 > 0)
  {
    next &= ~((1 << c0) - 1);
    next |= (1 << c0);
    if(c0OneCount > 1)
      next |= ((1 << (c0OneCount - 1)) - 1);
  }

  uint32_t prev = n;
  if(c1 > 0)
  {
    prev &= ~((1 << c1) - 1) & ~(1 << c1);
    prev |= (((1 << c1) - 1) & (~0 << (c1 - c1OneCount)));
  }

  return std::make_pair(prev, next);
}

TEST_CASE("next number with same bits", "[ch5.4]")
{
  REQUIRE(nextNumberWithSameBits(0b110) == (std::pair<uint32_t, uint32_t>(0b101, 0b1001)));
  REQUIRE(nextNumberWithSameBits(0b0) == (std::pair<uint32_t, uint32_t>(0, 0)));
  REQUIRE(nextNumberWithSameBits(0b001) == (std::pair<uint32_t, uint32_t>(1, 2)));
  REQUIRE(nextNumberWithSameBits(0b1100) == (std::pair<uint32_t, uint32_t>(0b1010, 0x11)));
  REQUIRE(nextNumberWithSameBits(0b1000) == (std::pair<uint32_t, uint32_t>(4, 0x10)));
  REQUIRE(nextNumberWithSameBits(0b10000000000000000000000000000000) == (std::pair<uint32_t, uint32_t>(0b01000000000000000000000000000000, 0b10000000000000000000000000000000)));
  REQUIRE(nextNumberWithSameBits(0b01000000000000000000000000000000) == (std::pair<uint32_t, uint32_t>(0b00100000000000000000000000000000, 0b10000000000000000000000000000000)));
  REQUIRE(nextNumberWithSameBits(0b00100000000000000000000000000000) == (std::pair<uint32_t, uint32_t>(0b00010000000000000000000000000000, 0b01000000000000000000000000000000)));

  REQUIRE(nextNumberWithSameBits(0b010) == (std::pair<uint32_t, uint32_t>(1, 4)));
  REQUIRE(nextNumberWithSameBits(0b1010) == (std::pair<uint32_t, uint32_t>(0b1001, 0b1100)));

  REQUIRE(nextNumberWithSameBits(0b101110) == (std::pair<uint32_t, uint32_t>(0b101101, 0b110011)));
  REQUIRE(nextNumberWithSameBits(0b10011110000011) == (std::pair<uint32_t, uint32_t>(0b10011101110000, 0b10011110000101)));
  REQUIRE(nextNumberWithSameBits(0b11011011111100) == (std::pair<uint32_t, uint32_t>(0b11011011111010, 0b11011100011111)));
}
