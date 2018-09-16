#include <string.h>
#include <iostream>
#include <algorithm>
#include "../../test_framework/catch.hpp"

void drawLine(uint8_t screen[], const int width, const int x1, const int x2, const int y)
{
  auto rowIndex = width * y;

  auto startFullByte = x1 / 8;
  if(x1 % 8 != 0)
    ++startFullByte;

  auto endFullByte = x2 / 8;
  if(x2 % 8 < 7)
    --endFullByte;

  for(auto i = startFullByte; i <= endFullByte; ++i)
    screen[rowIndex + i] = 0xFF;

  if(x1 / 8 == x2 / 8)
  {
    auto i = rowIndex + x1 / 8;
    screen[i] |= (uint8_t)((~0 << (x1 % 8)) & ((1 << ((x2 % 8) + 1)) - 1));
  }
  else
  {
    auto s = rowIndex + x1 / 8;
    screen[s] = 0xFF << (x1 % 8);
    auto e = rowIndex + x2 / 8;
    screen[e] = 0xFF >> (7 - (x2 % 8));
  }
}

TEST_CASE("monochrome - draw line", "[ch5.8]")
{
  const int SIZE = 20;
  uint8_t screen[SIZE] = { 0 };

  drawLine(screen, 4, 8, 31, 3);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0xFF, 0xFF, 0xFF,
    0, 0, 0, 0
  })));

  memset(screen, 0, SIZE);
  drawLine(screen, 5, 8, 31, 3);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 
    0, 0xFF, 0xFF, 0xFF, 0,
  })));

  drawLine(screen, 5, 6, 22, 2);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 
    0xC0, 0xFF, 0x7F, 0, 0, 
    0, 0xFF, 0xFF, 0xFF, 0,
  })));

  drawLine(screen, 5, 1, 3, 2);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 
    0xCE, 0xFF, 0x7F, 0, 0, 
    0, 0xFF, 0xFF, 0xFF, 0,
  })));

  drawLine(screen, 5, 8, 15, 1);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0, 0, 0, 0, 0, 
    0, 0xFF, 0, 0, 0, 
    0xCE, 0xFF, 0x7F, 0, 0, 
    0, 0xFF, 0xFF, 0xFF, 0,
  })));

  drawLine(screen, 5, 0, 6, 1);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0, 0, 0, 0, 0, 
    0x7F, 0xFF, 0, 0, 0, 
    0xCE, 0xFF, 0x7F, 0, 0, 
    0, 0xFF, 0xFF, 0xFF, 0,
  })));

  drawLine(screen, 5, 1, 7, 0);
  REQUIRE(std::equal(std::begin(screen), std::end(screen), std::begin({
    0xFE, 0, 0, 0, 0, 
    0x7F, 0xFF, 0, 0, 0, 
    0xCE, 0xFF, 0x7F, 0, 0, 
    0, 0xFF, 0xFF, 0xFF, 0,
  })));
}
