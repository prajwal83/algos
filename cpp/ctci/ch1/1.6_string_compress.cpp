#include <iostream>
#include <string>
#include "../../test_framework/catch.hpp"

std::string str_compress(const std::string& s)
{
  std::string r("");
  int counter = 0;
  char lastChar = '\0';
  for(int i = 0; i < s.length() && r.length() < s.length(); ++i)
  {
    if (i == 0 || lastChar != s[i])
    {
      if(counter)
        r += std::to_string(counter);
      r += s[i];
      lastChar = s[i];
      counter = 1;
    }
    else
      ++counter;
  }

  r += std::to_string(counter);
  if(r.length() >= s.length())
    return s;
  else
    return r;
}

TEST_CASE("string compress", "[ch1.6]")
{
  REQUIRE( str_compress("abc") == "abc" );
  REQUIRE( str_compress("aabbcc") == "aabbcc" );
  REQUIRE( str_compress("aaabbbcc") == "a3b3c2" );
  REQUIRE( str_compress("a") == "a" );
  REQUIRE( str_compress("aa") == "aa" );
  REQUIRE( str_compress("aaa") == "a3" );
  REQUIRE( str_compress("aaaabbbc") == "a4b3c1" );
  REQUIRE( str_compress("abbccccc") == "a1b2c5" );
  REQUIRE( str_compress("abbcccccaaaabbbc") == "a1b2c5a4b3c1" );
}
