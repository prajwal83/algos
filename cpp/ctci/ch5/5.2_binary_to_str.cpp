#include <string>
#include "../../test_framework/catch.hpp"

std::string decimalToBinaryString(double num)
{
  if(num >= 1 || num < 0)
    return "ERROR";

  std::stringstream ss;
  auto stream_size = [&ss]() {
    auto c = ss.tellp();
    ss.seekp(0, std::ios::end);
    auto r = ss.tellp();
    ss.seekp(c, std::ios::beg);
    return r;
  };

  ss << "0.";
  while(num > 0)
  {
    if(stream_size() >= 32)
      return "ERROR";

    num *= 2;
    if(num >= 1)
    {
      ss << "1";
      num -= 1;
    }
    else
    {
      ss << "0";
    }
  }

  return ss.str();
}

TEST_CASE("decimal to binary string", "[ch5.2]")
{
  REQUIRE(decimalToBinaryString(0.5) == "0.1");
  REQUIRE(decimalToBinaryString(0.625) == "0.101");
  REQUIRE(decimalToBinaryString(0.1) == "ERROR");
  REQUIRE(decimalToBinaryString(0.75) == "0.11");
  REQUIRE(decimalToBinaryString(0.875) == "0.111");
  REQUIRE(decimalToBinaryString(0.55) == "ERROR");
}
