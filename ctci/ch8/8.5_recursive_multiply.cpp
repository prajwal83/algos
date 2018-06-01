#include <iostream>
#include <functional>
#include "../../test_framework/catch.hpp"

int nonRecursiveMultiply(int n1, int n2)
{
  int product = 0;

  if(n1 < n2)
  {
    auto t = n1;
    n1 = n2;
    n2 = t;
  }

  for(int i = 0; n2 != 0; n2 >>= 1, ++i)
  {
    if(n2 & 0x1)
      product += (n1 << i);
  }
  return product;
}

int recursiveMultiply(int n1, int n2)
{
  std::function<int(int, int)> calc;
  calc = [&](int s, int b)
  {
    if(s == 0) return 0;
    if(s == 1) return b;
    auto halfP = calc(s >> 1, b);
    if(s % 2 == 0)
      return halfP + halfP;
    else
      return halfP + halfP + b;
  };

  return n1 < n2 ? calc(n1, n2) : calc(n2, n1);
}

TEST_CASE("nonRecursive multiply", "[ch8.5]")
{
  REQUIRE(nonRecursiveMultiply(3, 1) == 3);
  REQUIRE(nonRecursiveMultiply(3, 2) == 6);
  REQUIRE(nonRecursiveMultiply(2, 2) == 4);
  REQUIRE(nonRecursiveMultiply(5, 7) == 35);
  REQUIRE(nonRecursiveMultiply(100, 1000) == 100000);
  REQUIRE(nonRecursiveMultiply(25, 25) == 625);
  REQUIRE(nonRecursiveMultiply(4, 11) == 44);
  REQUIRE(nonRecursiveMultiply(64, 64) == 4096);
  REQUIRE(nonRecursiveMultiply(9, 0) == 0);
  REQUIRE(nonRecursiveMultiply(1, 3) == 3);
  REQUIRE(nonRecursiveMultiply(0, 33) == 0);
}

TEST_CASE("recursive multiply", "[ch8.5]")
{
  REQUIRE(recursiveMultiply(3, 1) == 3);
  REQUIRE(recursiveMultiply(3, 2) == 6);
  REQUIRE(recursiveMultiply(2, 2) == 4);
  REQUIRE(recursiveMultiply(5, 7) == 35);
  REQUIRE(recursiveMultiply(100, 1000) == 100000);
  REQUIRE(recursiveMultiply(25, 25) == 625);
  REQUIRE(recursiveMultiply(4, 11) == 44);
  REQUIRE(recursiveMultiply(64, 64) == 4096);
  REQUIRE(recursiveMultiply(9, 0) == 0);
  REQUIRE(recursiveMultiply(1, 3) == 3);
  REQUIRE(recursiveMultiply(0, 33) == 0);
}
