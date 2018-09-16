#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../test_framework/catch.hpp"

bool CheckPalindromePermutationWithSort(std::string s)
{
  std::sort(s.begin(), s.end());
  bool oddCheck = false;
  int i;
  for (i = 0; i < s.length() - 1;)
  {
    if (s[i] != s[i + 1])
    {
      if (oddCheck)
        return false;
      oddCheck = true;
      ++i;
    }
    else
      i += 2;
  }

  return i == s.length() ? true : !oddCheck;
}

bool CheckPalindromePermutationWithCharCount(const std::string& s)
{
  std::vector<int> counter(128, 0);
  for(auto c : s)
    ++counter[c];
  bool oddCheck = false;
  for(auto v : counter)
  {
    if (v % 2 != 0)
    {
      if (oddCheck)
        return false;
      oddCheck = true;
    }
  }
  return true;
}

bool CheckPalindromePermutationWithBitIndex(const std::string& s)
{
  unsigned bitmap = 0;
  for(auto c : s)
  {
    unsigned bitindex = 1 << c;
    if(bitmap & bitindex)
      bitmap &= ~bitindex;
    else
      bitmap |= bitindex;
  }

  return bitmap == 0 || (bitmap & (bitmap - 1)) == 0;
}

TEST_CASE("CheckPalindromePermutationWithSort", "[ch1.4]")
{
  REQUIRE( CheckPalindromePermutationWithSort("tactcoa") == true );
  REQUIRE( CheckPalindromePermutationWithSort("abccba") == true );
  REQUIRE( CheckPalindromePermutationWithSort("a") == true );
  REQUIRE( CheckPalindromePermutationWithSort("ab") == false );
  REQUIRE( CheckPalindromePermutationWithSort("abbaaaa") == true );
  REQUIRE( CheckPalindromePermutationWithSort("aabbcefczef") == true );
  REQUIRE( CheckPalindromePermutationWithSort("aabbcefcef") == true );
  REQUIRE( CheckPalindromePermutationWithSort("aabbcefczf") == false );
}

TEST_CASE("CheckPalindromePermutationWithCharCount", "[ch1.4]")
{
  REQUIRE( CheckPalindromePermutationWithCharCount("tactcoa") == true );
  REQUIRE( CheckPalindromePermutationWithCharCount("abccba") == true );
  REQUIRE( CheckPalindromePermutationWithCharCount("a") == true );
  REQUIRE( CheckPalindromePermutationWithCharCount("ab") == false );
  REQUIRE( CheckPalindromePermutationWithCharCount("abbaaaa") == true );
  REQUIRE( CheckPalindromePermutationWithCharCount("aabbcefczef") == true );
  REQUIRE( CheckPalindromePermutationWithCharCount("aabbcefcef") == true );
  REQUIRE( CheckPalindromePermutationWithCharCount("aabbcefczf") == false );
}

TEST_CASE("CheckPalindromePermutationWithBitIndex", "[ch1.4]")
{
  REQUIRE( CheckPalindromePermutationWithBitIndex("tactcoa") == true );
  REQUIRE( CheckPalindromePermutationWithBitIndex("abccba") == true );
  REQUIRE( CheckPalindromePermutationWithBitIndex("a") == true );
  REQUIRE( CheckPalindromePermutationWithBitIndex("ab") == false );
  REQUIRE( CheckPalindromePermutationWithBitIndex("abbaaaa") == true );
  REQUIRE( CheckPalindromePermutationWithBitIndex("aabbcefczef") == true );
  REQUIRE( CheckPalindromePermutationWithBitIndex("aabbcefcef") == true );
  REQUIRE( CheckPalindromePermutationWithBitIndex("aabbcefczf") == false );
}
