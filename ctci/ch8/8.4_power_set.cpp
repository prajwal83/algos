#include <iostream>
#include <vector>
#include "../../test_framework/catch.hpp"

using Set = std::vector<int>;
using Sets = std::vector<Set>;

void powerSet(const Set& s, int i, Sets& result)
{
  if(s.size() == i)
  {
    result.push_back(Set());
    return;
  }

  powerSet(s, i + 1, result);
  auto rSize = result.size();
  for(int x = 0; x < rSize; ++x)
  {
    auto nr = result[x];
    nr.push_back(s[i]);
    result.push_back(nr);
  }
}

void powerSet(const Set& s, Sets& result)
{
  powerSet(s, 0, result);
}

TEST_CASE("power set by recursion", "[ch8.4]")
{
  Sets result;
  powerSet(Set({ }), result);
  REQUIRE(result == Sets({ 
    Set({ }) 
  }));

  result.clear();
  powerSet(Set({ 1 }), result);
  REQUIRE(result == Sets({ 
    Set({ }),
    Set({ 1 }),
  }));

  result.clear();
  powerSet(Set({ 1, 2 }), result);
  REQUIRE(result == Sets({ 
    Set({ }),
    Set({ 2 }),
    Set({ 1 }),
    Set({ 2, 1 }),
  }));

  result.clear();
  powerSet(Set({ 1, 2, 3 }), result);
  REQUIRE(result == Sets({ 
    Set({ }),
    Set({ 3 }),
    Set({ 2 }),
    Set({ 3, 2 }),
    Set({ 1 }),
    Set({ 3, 1 }),
    Set({ 2, 1 }),
    Set({ 3, 2, 1 }),
  }));

  result.clear();
  powerSet(Set({ 1, 1, 1, 1 }), result);
  REQUIRE(result == Sets({ 
    Set({ }),
    Set({ 1 }),
    Set({ 1 }),
    Set({ 1, 1 }),
    Set({ 1 }),
    Set({ 1, 1 }),
    Set({ 1, 1 }),
    Set({ 1, 1, 1 }),
    Set({ 1 }),
    Set({ 1, 1 }),
    Set({ 1, 1 }),
    Set({ 1, 1, 1 }),
    Set({ 1, 1 }),
    Set({ 1, 1, 1 }),
    Set({ 1, 1, 1 }),
    Set({ 1, 1, 1, 1 })
  }));
}
