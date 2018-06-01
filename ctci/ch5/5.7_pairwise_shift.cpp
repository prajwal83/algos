#include <iostream>
#include "../../test_framework/catch.hpp"

uint32_t pairwiseShift(uint32_t n)
{
  return ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
}

TEST_CASE("pairwise shift", "[ch5.7]")
{
  REQUIRE(pairwiseShift(0b0) == 0);
  REQUIRE(pairwiseShift(0b1) == 0b10);
  REQUIRE(pairwiseShift(0b10101010) == 0b01010101);
  REQUIRE(pairwiseShift(-1) == 0xFFFFFFFF);
  REQUIRE(pairwiseShift(0b11101110) == 0b11011101);
}
