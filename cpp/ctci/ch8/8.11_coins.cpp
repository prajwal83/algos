#include <vector>
#include <map>
#include "../../test_framework/catch.hpp"
#include "common.h"

using Memo = std::map<std::pair<int, int>, int>;

//this is my sol.
int coinWays(int n, int max, Memo& m)
{
  if(n < 0)
    return 0;

  if(n == 0)
    return 1;
  
  auto i = m.find(std::make_pair(max, n));
  if(i != m.end())
    return i->second;

  int count = 0;
  if(max >= 25)
    count += coinWays(n - 25, 25, m);

  if(max >= 10)
    count += coinWays(n - 10, 10, m);

  if(max >= 5)
    count += coinWays(n - 5, 5, m);

  if(max >= 1)
    count += coinWays(n - 1, 1, m);

  m.insert(std::make_pair(std::make_pair(max, n), count));
  return count;
}

int coinWays(int n)
{
  Memo m;
  return coinWays(n, 25, m);
}

//this is from book
int makeChange(int amount, const std::vector<int>& denoms, int index)
{
	if (index >= denoms.size() - 1) return 1; // last denom
	int denomAmount = denoms[index];
	int ways = 0;
	for (int i = 0; i * denomAmount <= amount; i++)
	{	
		int amountRemaining = amount - i * denomAmount;
		ways += makeChange(amountRemaining, denoms, index + 1);
	}
	return ways;
}

int makeChange(int n)
{
	std::vector<int> denoms = {25, 10, 5, 1};
	return makeChange(n, denoms, 0);
}

TEST_CASE("coin ways to change", "[ch8.10]")
{
  REQUIRE(coinWays(0) == 1);
  REQUIRE(coinWays(1) == 1);
  REQUIRE(coinWays(2) == 1);
  REQUIRE(coinWays(3) == 1);
  REQUIRE(coinWays(4) == 1);
  REQUIRE(coinWays(5) == 2);
  REQUIRE(coinWays(6) == 2);

  REQUIRE(coinWays(10) == 4);
  REQUIRE(coinWays(11) == 4);
  REQUIRE(coinWays(15) == 6);

  REQUIRE(coinWays(25) == 13);
	REQUIRE(makeChange(25) == 13);

	for(int i = 0; i < 100; ++i)
		REQUIRE(coinWays(i) == makeChange(i));
}

TEST_CASE("performance of coin ways to change", "[ch8.10]")
{
  REQUIRE(coinWays(10000) == makeChange(10000));
  ch8::TimeMetrics("coins [my impl]", []{ coinWays(10000); });
  ch8::TimeMetrics("coins [book impl]", []{ makeChange(10000); });
}
