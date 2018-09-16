#include <vector>
#include <string>
#include "../../test_framework/catch.hpp"

using Parens = std::vector<std::string>;

Parens parensComb(int openCount, int pairCount)
{
  if(pairCount == 0)
  {
    if(openCount)
      throw "ERROR - failed to generate parens combinations";
    return Parens({""});
  }

  Parens tr;
  if(openCount == 0)
  {
    tr = parensComb(1, pairCount);
    for(auto& r : tr)
      r = "(" + r;
  }
  else
  {
    tr = parensComb(openCount - 1, pairCount - 1);
    for(auto& r : tr)
      r = ")" + r;

    if(openCount < pairCount)
    {
      auto&& t = parensComb(openCount + 1, pairCount);
      for(auto& r : t)
        r = "(" + r;

      tr.reserve(tr.size() + t.size());
      std::move(t.begin(), t.end(), std::back_inserter(tr));
      t.clear();
    }
  }
  return tr;
}

Parens parens(int pairCount)
{
  return parensComb(0, pairCount);
}

TEST_CASE("parens combination", "[ch8.9]")
{
  REQUIRE(parens(1) == Parens({"()"}));

  REQUIRE(parens(2) == Parens({
    "()()",
    "(())"
  }));

  REQUIRE(parens(3) == Parens({
    "()()()",
    "()(())",
    "(())()",
    "(()())",
    "((()))",
  }));
}
