#include "../../test_framework/catch.hpp"

int bitDifferenceWithBitShiftCounter(uint32_t n1, uint32_t n2)
{
  auto n = n1 ^ n2;
  int count = 0;
  for(int i = 0; i < 32; ++i, n >>= 1)
    count += (n & 0x1);
  return count;
}

int bitDifferenceWithBitReduction(uint32_t n1, uint32_t n2)
{
  int count = 0;
  for(int c = n1 ^ n2; c != 0; c &= (c - 1))
    ++count;
  return count;
}

TEST_CASE("conversion - bit difference by bit counting", "[ch5.6]")
{
  REQUIRE(bitDifferenceWithBitShiftCounter(0b1, 0b1) == 0);
  REQUIRE(bitDifferenceWithBitShiftCounter(0b0, 0b0) == 0);
  REQUIRE(bitDifferenceWithBitShiftCounter(0b10, 0b11) == 1);
  REQUIRE(bitDifferenceWithBitShiftCounter(0x80000000, 0xF0000010) == 4);
  REQUIRE(bitDifferenceWithBitShiftCounter(0b11101, 0b1111) == 2);
}

TEST_CASE("conversion - bit difference by bit reduction", "[ch5.6]")
{
  REQUIRE(bitDifferenceWithBitReduction(0b1, 0b1) == 0);
  REQUIRE(bitDifferenceWithBitReduction(0b0, 0b0) == 0);
  REQUIRE(bitDifferenceWithBitReduction(0b10, 0b11) == 1);
  REQUIRE(bitDifferenceWithBitReduction(0x80000000, 0xF0000010) == 4);
  REQUIRE(bitDifferenceWithBitReduction(0b11101, 0b1111) == 2);
}
