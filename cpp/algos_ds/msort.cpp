#include "../test_framework/catch.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

namespace alds {

void merge(std::vector<int>& a, int low, int mid, int high)
{
  std::vector<int> temp(high - low + 1);

  int i = low;
  int j = mid + 1;
  int k = 0;

  while(i <= mid && j <= high)
  {
    if(a[i] <= a[j])
      temp[k++] = a[i++];
    else
      temp[k++] = a[j++];
  }

  while(i <= mid)
    temp[k++] = a[i++];

  while(j <= high)
    temp[k++] = a[j++];

  std::copy(temp.begin(), temp.end(), a.begin() + low);
}

void msort(std::vector<int>& a, int low, int high)
{
  if(low < high)
  {
    int mid = (low + high) / 2;
    msort(a, low, mid);
    msort(a, mid + 1, high);
    merge(a, low, mid, high);
  }
}

void msort(std::vector<int>& a)
{
  msort(a, 0, a.size() - 1);
}
}

TEST_CASE("merge sort an integer array", "[msort]")
{
  using alds::msort;
  std::vector<int> a = {};
  std::vector<int> r = {};
  msort(a);
  REQUIRE( a == r );

  a = { 1 };
  r = { 1 };
  msort(a);
  REQUIRE( a == r );

  a = { 1, 2 };
  r = { 1, 2 };
  msort(a);
  REQUIRE( a == r );

  a = { 2, 1 };
  r = { 1, 2 };
  msort(a);
  REQUIRE( a == r );

  a = { 2, 1, 3, 4, 10, 11, 8, 6 };
  r = { 1, 2, 3, 4, 6, 8, 10, 11 };
  msort(a);
  REQUIRE( a == r );

  a = {};
  r = {};
  for(int i = 0; i < 1000; ++i)
  {
    a.push_back(1000 - i - 1);
    r.push_back(i);
  }
  msort(a);
  REQUIRE( a == r );

  a = {};
  r = {};
  for(int i = 0; i < 1000000; ++i)
  {
    a.push_back(1000000 - i - 1);
    r.push_back(i);
  }
  std::shuffle(a.begin(), a.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
  msort(a);
  REQUIRE( a == r );
}
