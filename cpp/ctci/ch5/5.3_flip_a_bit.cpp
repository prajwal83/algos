#include "../../test_framework/catch.hpp"

int longestFlipBitLength(uint32_t n)
{
  bool aFlipDone = false;
  int counter = 0;
  int maxLen = 0;
  for(int i = 0; i < 32; ++i)
  {
    if(n & 0x1)
    {
      ++counter;
    }
    else
    {
      if(aFlipDone)
      {
        maxLen = std::max(maxLen, counter);
        counter = 1;
      }
      else
      {
        aFlipDone = true;
        ++counter;
      }
    }
    n >>= 1;
  }
  return std::max(maxLen, counter);
}

TEST_CASE("flip a bit length", "[ch5.3]")
{
  REQUIRE(longestFlipBitLength(0b11011101111) == 8);
  REQUIRE(longestFlipBitLength(0b0) == 1);
  REQUIRE(longestFlipBitLength(0b11011001111) == 5);
  REQUIRE(longestFlipBitLength(0b11011111111) == 11);
  REQUIRE(longestFlipBitLength(0b10011111111) == 9);
  REQUIRE(longestFlipBitLength(0b10011111100) == 7);
}
