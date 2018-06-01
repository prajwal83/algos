#include <iostream>
#include <string>
#include "../../test_framework/catch.hpp"

bool is_rotation(const std::string& s1, const std::string& s2)
{
  if (s1.length() != s2.length())
    return false;
  else if(s1.empty())
    return true;
  else
    return (s1 + s1).find(s2) != std::string::npos;
}

TEST_CASE("is rotation string", "[ch1.9]")
{
  REQUIRE( is_rotation("", "1") == false );
  REQUIRE( is_rotation("", "") == true );
  REQUIRE( is_rotation("1", "1") == true );
  REQUIRE( is_rotation("1234", "3412") == true );
  REQUIRE( is_rotation("1234", "4123") == true );
  REQUIRE( is_rotation("1234", "4213") == false );
  REQUIRE( is_rotation("12", "21") == true );
  REQUIRE( is_rotation("120", "012") == true );
}

