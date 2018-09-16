#include "../test_framework/catch.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

namespace alds {

int partition(std::vector<int>& a, int low, int high)
{
  auto swap = [&a](int i, int j) {
    if(i != j)
    {
      auto t = a[i];
      a[i] = a[j];
      a[j] = t;
    }
  };

  const int pivot = a[high];
  int i = low - 1;
  for(int j = low; j <= high - 1; ++j)
  {
    if(a[j] <= pivot)
      swap(++i, j);
  }
  swap(++i, high);
  return i; 
}

void qsort(std::vector<int>& a, int low, int high)
{
  if(low < high)
  {
    int m = partition(a, low, high);
    qsort(a, low, m - 1);
    qsort(a, m + 1, high);
  }
}

void qsort(std::vector<int>& a)
{
  qsort(a, 0, a.size() - 1);
}

}

TEST_CASE("quick sort an integer array", "[qsort]")
{
  using alds::qsort;
  std::vector<int> a = {};
  std::vector<int> r = {};
  qsort(a);
  REQUIRE( a == r );

  a = { 1 };
  r = { 1 };
  qsort(a);
  REQUIRE( a == r );

  a = { 1, 2 };
  r = { 1, 2 };
  qsort(a);
  REQUIRE( a == r );

  a = { 2, 1 };
  r = { 1, 2 };
  qsort(a);
  REQUIRE( a == r );

  a = { 2, 1, 3, 4, 10, 11, 8, 6 };
  r = { 1, 2, 3, 4, 6, 8, 10, 11 };
  qsort(a);
  REQUIRE( a == r );

  a = {};
  r = {};
  for(int i = 0; i < 1000; ++i)
  {
    a.push_back(1000 - i - 1);
    r.push_back(i);
  }
  qsort(a);
  REQUIRE( a == r );

  a = {};
  r = {};
  for(int i = 0; i < 1000000; ++i)
  {
    a.push_back(1000000 - i - 1);
    r.push_back(i);
  }
  std::shuffle(a.begin(), a.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
  qsort(a);
  REQUIRE( a == r );
}
