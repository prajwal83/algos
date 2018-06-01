#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../test_framework/catch.hpp"

bool CheckPermutationBySorting(std::string s1, std::string s2)
{
  if(s1.length() != s2.length())
    return false;
  std::sort(s1.begin(), s1.end());
  std::sort(s2.begin(), s2.end());
  return s1 == s2;
}

bool CheckPermutationByCharCount(const std::string& s1, const std::string& s2)
{
  if(s1.length() != s2.length())
    return false;

  std::vector<int> counter(128, 0);

  for(const char c : s1)
    ++counter[c];
  for(const char c : s2)
    --counter[c];
  for(auto i : counter)
    if (i != 0)
      return false;
  return true;
}

TEST_CASE("CheckPermutationBySorting", "[ch1.2]")
{
  REQUIRE( CheckPermutationBySorting("abc", "bca") == true );
  REQUIRE( CheckPermutationBySorting("abc", "baca") == false );
  REQUIRE( CheckPermutationBySorting("abccba", "bcaabc") == true );
  REQUIRE( CheckPermutationBySorting("a", "a") == true );
  REQUIRE( CheckPermutationBySorting("ab", "ab") == true );
  REQUIRE( CheckPermutationBySorting("ab", "ba") == true );
  REQUIRE( CheckPermutationBySorting("abcdefrgrg", "abcdrgfrge") == true );
  REQUIRE( CheckPermutationBySorting("abcdefrgrg", "zbcdrgfrge") == false );
  REQUIRE( CheckPermutationBySorting("ab", "aa") == false );
}

TEST_CASE("CheckPermutationByCharCount", "[ch1.2]")
{
  REQUIRE( CheckPermutationBySorting("abc", "bca") == true );
  REQUIRE( CheckPermutationBySorting("abc", "baca") == false );
  REQUIRE( CheckPermutationBySorting("abccba", "bcaabc") == true );
  REQUIRE( CheckPermutationBySorting("a", "a") == true );
  REQUIRE( CheckPermutationBySorting("ab", "ab") == true );
  REQUIRE( CheckPermutationBySorting("ab", "ba") == true );
  REQUIRE( CheckPermutationBySorting("abcdefrgrg", "abcdrgfrge") == true );
  REQUIRE( CheckPermutationBySorting("abcdefrgrg", "zbcdrgfrge") == false );
  REQUIRE( CheckPermutationBySorting("ab", "aa") == false );
}
