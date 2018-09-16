#include <vector>
#include "../../test_framework/catch.hpp"
#include "common.h"

int tripleStepCount(int stairs)
{
  int count = 0;
  if(stairs == 1)
    count += 1;

  if(stairs > 1)
    count += tripleStepCount(stairs - 1);

  if(stairs == 2)
    count += 1;

  if(stairs > 2)
    count += tripleStepCount(stairs - 2);

  if(stairs == 3)
    count += 1;

  if(stairs > 3)
    count += tripleStepCount(stairs - 3);

  return count;
}

int countWays(int stairs)
{
  if(stairs < 0)
    return 0;
  if(stairs == 0)
    return 1;
  return countWays(stairs - 1) + countWays(stairs - 2) + countWays(stairs - 3);
}

int memoizationCountWays(int stairs, std::vector<int>& cache)
{
  if(stairs < 0)
    return 0;

  if(stairs == 0)
    return 1;

  if(cache[stairs] == -1)
    cache[stairs] = memoizationCountWays(stairs - 1, cache) + memoizationCountWays(stairs - 2, cache) + memoizationCountWays(stairs - 3, cache);

  return cache[stairs];
}

int memoizationCountWays(int stairs)
{
  std::vector<int> cache(stairs + 1, -1);
  return memoizationCountWays(stairs, cache);
}

TEST_CASE("triple step my brute force approach", "[ch8.1]")
{
  REQUIRE(tripleStepCount(0) == 0);
  REQUIRE(tripleStepCount(1) == 1);
  REQUIRE(tripleStepCount(2) == 2);
  REQUIRE(tripleStepCount(3) == 4);
  REQUIRE(tripleStepCount(4) == 7);
  REQUIRE(tripleStepCount(5) == 13);
}

TEST_CASE("triple step book brute force approach", "[ch8.1]")
{
  REQUIRE(countWays(0) == 1);
  REQUIRE(countWays(1) == 1);
  REQUIRE(countWays(2) == 2);
  REQUIRE(countWays(3) == 4);
  REQUIRE(countWays(4) == 7);
  REQUIRE(countWays(5) == 13);
}

TEST_CASE("triple step with memoization", "[ch8.1]")
{
  REQUIRE(memoizationCountWays(0) == 1);
  REQUIRE(memoizationCountWays(1) == 1);
  REQUIRE(memoizationCountWays(2) == 2);
  REQUIRE(memoizationCountWays(3) == 4);
  REQUIRE(memoizationCountWays(4) == 7);
  REQUIRE(memoizationCountWays(5) == 13);
}

TEST_CASE("triple step - performance", "[ch8.1_performance]")
{
  ch8::TimeMetrics("brute force 1", [] { tripleStepCount(35); });
  ch8::TimeMetrics("brute force 2", [] { countWays(35); });
  ch8::TimeMetrics("memoization sol", [] { memoizationCountWays(35); });
}
