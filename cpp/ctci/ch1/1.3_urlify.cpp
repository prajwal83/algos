#include <iostream>
#include <string>
#include "../../test_framework/catch.hpp"

std::string urlify(std::string url)
{
  const int actualLen = url.length();
  int spaceCount = 0;
  for(int i = 0; i < actualLen; ++i)
    if (url[i] == ' ')
      ++spaceCount;
  
  int index = actualLen + spaceCount * 2;
  url[index] = '\0';
  --index;
  for (int i = actualLen - 1; i >= 0; --i)
  {
    if (url[i] == ' ')
    {
      url[index] = '0';
      url[index - 1] = '2';
      url[index - 2] = '%';
      index -= 3;
    }
    else
    {
      url[index] = url[i];
      --index;
    }
  }
  return url;
}

TEST_CASE("urlify", "[ch1.3]")
{
  REQUIRE( urlify("abc") == "abc" );
  REQUIRE( urlify("ab c  ") == "ab%20c" );
  REQUIRE( urlify("a b  c      ") == "a%20b%20%20c" );
  REQUIRE( urlify("abc   ") == "abc%20" );
  REQUIRE( urlify("   ") == "%20" );
  REQUIRE( urlify("a") == "a" );
  REQUIRE( urlify("a  b  c        ") == "a%20%20b%20%20c" );
}
