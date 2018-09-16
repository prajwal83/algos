#include <iostream>
#include <string>
#include <cmath>
#include "../../test_framework/catch.hpp"

bool one_away(std::string main, std::string mod)
{
  const int len_diff = std::labs(main.length() - mod.length());
  bool result = true;
  if (len_diff > 1)
    result = false;
  else if(len_diff == 1)
  {
    if (main.length() < mod.length())
    {
      std::string tmp = main;
      main = mod;
      mod = tmp;
    }
    bool modFound = false;
    for(int i = 0, k = 0; i < main.length();)
    {
      if(main[i] != mod[k])
      {
        if(modFound)
        {
          result = false;
          break;
        }
        modFound = true;
        ++i;
      }
      else
      {
        ++i;
        ++k;
      }
    }
  }
  else
  {
    bool modFound = false;
    for(int i = 0; i < main.length(); ++i)
    {
      if(main[i] != mod[i])
      {
        if(modFound)
        {
          result = false;
          break;
        }
        modFound = true;
      }
    }
  }
  return result;
}

TEST_CASE("one away edit", "[ch1.5]")
{
  REQUIRE( one_away("abc", "abc") == true );
  REQUIRE( one_away("abc", "ab") == true );
  REQUIRE( one_away("a", "") == true );
  REQUIRE( one_away("a", "b") == true );
  REQUIRE( one_away("abcde", "abcd") == true );
  REQUIRE( one_away("abc", "abz") == true );
  REQUIRE( one_away("abczz", "abce") == false );
  REQUIRE( one_away("abczz", "abzz") == true );
  REQUIRE( one_away("abczz", "abcez") == true );
  REQUIRE( one_away("ab", "") == false );
}
