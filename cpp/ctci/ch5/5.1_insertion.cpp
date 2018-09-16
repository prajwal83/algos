#include "../../test_framework/catch.hpp"

uint32_t insert(const uint32_t n, const uint32_t m, const int i, const int j)
{
  const uint32_t mask = ~(((1 << (j - i + 1)) - 1) << i);
  return (n & mask) | (m << i);
}

TEST_CASE("insertion", "[ch5.1]")
{
  REQUIRE(insert(0b10000000000, 0b10011, 2, 6) == 0b10001001100);
  REQUIRE(insert(0b10000110000, 0b10011, 2, 6) == 0b10001001100);
  REQUIRE(insert(0b10000110000, 0b10011, 0, 4) == 0b10000110011);
}
