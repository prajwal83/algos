#include <map>
#include <vector>
#include <string>
#include "../../test_framework/catch.hpp"

using FreqMap = std::map<char, int>;
using Result = std::vector<std::string>;

void permWithDups(FreqMap& m, std::string prefix, int remaining, Result& result)
{
  if(remaining == 0)
    result.push_back(prefix);

  for(const auto& e : m)
  {
    if(e.second > 0)
    {
      m[e.first] -= 1;
      permWithDups(m, prefix + e.first, remaining - 1, result);
      m[e.first] += 1;
    }
  }
}

void permutation(const std::string& str, Result& result)
{
  FreqMap m;
  for(const auto c : str)
  {
    auto i = m.insert(std::make_pair(c, 1));
    if(!i.second)
      i.first->second += 1;
  }
  permWithDups(m, "", str.length(), result);
}

TEST_CASE("permutation with unique chars", "[ch8.8]")
{
  Result result;

  permutation("", result);
  REQUIRE(result.size() == 1);
  result.clear();

  permutation("1", result);
  REQUIRE(result == Result({ "1" }));
  result.clear();

  permutation("12", result);
  REQUIRE(result == Result({ 
    "12",
    "21"
  }));
  result.clear();

  permutation("123", result);
  REQUIRE(result == Result({ 
    "123",
    "132",
    "213",
    "231",
    "312",
    "321"
  }));
  result.clear();

  permutation("1234", result);
  REQUIRE(result == Result({ 
    "1234", "1243", "1324", "1342",
    "1423", "1432", "2134", "2143",
    "2314", "2341", "2413", "2431",
    "3124", "3142", "3214", "3241",
    "3412", "3421", "4123", "4132",
    "4213", "4231", "4312", "4321",
  }));
  result.clear();
}

TEST_CASE("permutation with dups", "[ch8.8]")
{
  Result result;

  permutation("11", result);
  REQUIRE(result == Result({ 
    "11",
  }));
  result.clear();

  permutation("113", result);
  REQUIRE(result == Result({ 
    "113",
    "131",
    "311",
  }));
  result.clear();

  permutation("1232", result);
  REQUIRE(result == Result({ 
    "1223", "1232", "1322", "2123",
    "2132", "2213", "2231", "2312", 
    "2321", "3122", "3212", "3221"
  }));
  result.clear();
}
