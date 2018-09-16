#include <limits>
#include <vector>
#include "../../test_framework/catch.hpp"

using Array = std::vector<int>;

Array peaksAndValleySort(const Array& a)
{
  Array result = a;
  if(a.size() <= 1)
    return a;

  auto swap = [&](int x, int y)
  {
    auto t = result[x];
    result[x] = result[y];
    result[y] = t;
  };

  bool peak = false;
  for(int i = 1; i < result.size(); ++i)
  {
    const bool doSwap = peak ? result[i] > result[i - 1] : result[i] < result[i - 1];
    if(doSwap) swap(i, i - 1);
    peak = !peak;
  }

  return result;
}

//copy pasting text book solution to understand how that works -- my solution is shorter
int maxindex(const Array& array, int a, int b, int c) 
{
  int len = array.size();
  int aValue = a >= 0 && a < len ? array[a] : std::numeric_limits<int>::min();
  int bValue = b >= 0 && b < len ? array[b] : std::numeric_limits<int>::min();
  int cValue = c >= 0 && c < len ? array[c] : std::numeric_limits<int>::min();

  int max = std::max(aValue, std::max(bValue, cValue));
  if (aValue == max) return a;
  else if (bValue == max) return b;
  else return c;
}

Array sortValleyPeak(const Array& a)
{
  Array array = a;	
  auto swap = [&](int x, int y)
  {
    auto t = array[x];
    array[x] = array[y];
    array[y] = t;
  };
  for (int i = 1; i < array.size(); i += 2) 
  {
    int biggestindex = maxindex(array, i - 1, i, i + 1);
    if (i != biggestindex) 
      swap(i, biggestindex);
  }
  return array;
}

TEST_CASE("peaks and valleys", "[ch10.11]")
{
  REQUIRE(peaksAndValleySort(Array({1, 2, 3, 4, 5, 6})) == Array({1, 3, 2, 5, 4, 6}));
  REQUIRE(peaksAndValleySort(Array({1})) == Array({1}));
  REQUIRE(peaksAndValleySort(Array({1, 2})) == Array({1, 2}));
  REQUIRE(peaksAndValleySort(Array({2, 1})) == Array({1, 2}));
  REQUIRE(peaksAndValleySort(Array({0, 1, 4, 7, 8, 9})) == Array({0, 4, 1, 8, 7, 9}));
  REQUIRE(peaksAndValleySort(Array({9, 1, 0, 4, 8, 7})) == Array({1, 9, 0, 8, 4, 7}));
  REQUIRE(peaksAndValleySort(Array({6, 5, 4, 3, 2, 1})) == Array({5, 6, 3, 4, 1, 2}));
}

TEST_CASE("(text book) peaks and valleys", "[ch10.11]")
{
  REQUIRE(sortValleyPeak(Array({1, 2, 3, 4, 5, 6})) == Array({1, 3, 2, 5, 4, 6}));
  REQUIRE(sortValleyPeak(Array({1})) == Array({1}));
  REQUIRE(sortValleyPeak(Array({1, 2})) == Array({1, 2}));
  REQUIRE(sortValleyPeak(Array({2, 1})) == Array({1, 2}));
  REQUIRE(sortValleyPeak(Array({0, 1, 4, 7, 8, 9})) == Array({0, 4, 1, 8, 7, 9}));
  REQUIRE(sortValleyPeak(Array({9, 1, 0, 4, 8, 7})) == Array({1, 9, 0, 8, 4, 7}));
  REQUIRE(sortValleyPeak(Array({6, 5, 4, 3, 2, 1})) == Array({5, 6, 3, 4, 1, 2}));
}
