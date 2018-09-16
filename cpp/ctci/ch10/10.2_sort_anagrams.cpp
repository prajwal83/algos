#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include "../../test_framework/catch.hpp"

using Array = std::vector<std::string>;

void sortedAnagrams(const Array& input, Array& result)
{
  std::map<std::string, std::list<std::string>> h;
  for(auto s : input)
  {
    auto k = s;
    std::sort(k.begin(), k.end());
    h[k].push_back(s);
  }

  for(const auto& e : h)
    for(const auto& s : e.second)
      result.push_back(s);
}

TEST_CASE("sort anagrams", "[ch10.2]")
{
  Array s = { "a", "b", "aba", "baa", "bac", "pmpe", "leta", "mepp", "cab", "alet", "a" };
  Array result;
  sortedAnagrams(s, result);
  REQUIRE(result == Array({ "a", "a", "aba", "baa", "bac", "cab", "leta", "alet", "b", "pmpe", "mepp" }));
}
