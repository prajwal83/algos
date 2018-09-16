#include <iostream>
#include <string>
#include "../../test_framework/catch.hpp"

bool CheckUniqueWithoutExtraDS(const std::string& s)
{
  if (s.length() > 256)
    return false;
  for(int i = 0; i < s.length() - 1; ++i)
  {
    for(int j = i + 1; j < s.length(); ++j)
    {
      if (s[i] == s[j])
        return false;
    }
  }
  return true;
}

bool CheckUniqueWithExtraDS(const std::string& s)
{
  const unsigned BIT_SIZE = sizeof(unsigned) * 8;
  unsigned flag[4] = { 0, 0, 0, 0 };
  for(int i = 0; i < s.length(); ++i)
  {
    const unsigned code = (unsigned)s[i];
    const unsigned flagIndex = code / BIT_SIZE;
    const unsigned bitIndex = 1 << (code % BIT_SIZE);
    if (flag[flagIndex] & bitIndex)
      return false;
    flag[flagIndex] |= bitIndex;
  }
  return true;
}

void PrintResult(const bool result)
{
  if (result)
    std::cout << "all characters are unique" << std::endl;
  else
    std::cout << "has duplicate characters" << std::endl;
}

TEST_CASE("CheckUniqueWithoutExtraDS", "[ch1.1]")
{
  REQUIRE( CheckUniqueWithoutExtraDS("aabc") == false );
  REQUIRE( CheckUniqueWithoutExtraDS("abc") == true );
  REQUIRE( CheckUniqueWithoutExtraDS("") == true );
  REQUIRE( CheckUniqueWithoutExtraDS("a") == true );
  REQUIRE( CheckUniqueWithoutExtraDS("abcda") == false );
  REQUIRE( CheckUniqueWithoutExtraDS("abcbd") == false );
  REQUIRE( CheckUniqueWithoutExtraDS("abcdcz") == false );
  REQUIRE( CheckUniqueWithoutExtraDS("abcdez") == true );
}

TEST_CASE("CheckUniqueWithExtraDS", "[ch1.1]")
{
  REQUIRE( CheckUniqueWithExtraDS("aabc") == false );
  REQUIRE( CheckUniqueWithExtraDS("abc") == true );
  REQUIRE( CheckUniqueWithExtraDS("") == true );
  REQUIRE( CheckUniqueWithExtraDS("a") == true );
  REQUIRE( CheckUniqueWithExtraDS("abcda") == false );
  REQUIRE( CheckUniqueWithExtraDS("abcbd") == false );
  REQUIRE( CheckUniqueWithExtraDS("abcdcz") == false );
  REQUIRE( CheckUniqueWithExtraDS("abcdez") == true );
}
