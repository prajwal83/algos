#include <vector>
#include "../../test_framework/catch.hpp"

using Array = std::vector<int>;

struct MArray
{
  MArray(Array&& a) : _a(a) {}

  int at(int i) const
  {
    if(i > _a.size() || i < 0)
      return -1;
    return _a[i];
  }

  Array _a;
};

int bSearch(const MArray& a, int x, int l, int r)
{
  if(l > r)
    return -1;

  int m = (l + r) / 2;
  
  if(a.at(m) == x)
    return m;

  if(a.at(m) == -1 || x < a.at(m))
    return bSearch(a, x, l, m - 1);

  return bSearch(a, x, m + 1, r);
}

int noSizeSearch(const MArray& a, int x)
{
  int index = 1;
  while(a.at(index) != -1 && a.at(index) < x)
    index *= 2;

  //1. if index = -1 then index/2 != -1 and at(index/2) < x
  //2. if index != -1 then at(index) >= x and at(index/2) < x
  return bSearch(a, x, index / 2, index);
}

TEST_CASE("unbounded binary search", "[ch10.4]")
{
  MArray a1(Array({1, 2, 3, 4, 5, 6}));
  for(int i = 1; i <= 6; ++i)
    REQUIRE(noSizeSearch(a1, i) == (i - 1));

  MArray a2(Array({1, 2, 3, 4, 5, 6, 7, 8}));
  for(int i = 1; i <= 8; ++i)
    REQUIRE(noSizeSearch(a2, i) == (i - 1));
  REQUIRE(noSizeSearch(a2, 9) == -1);
  REQUIRE(noSizeSearch(a2, 0) == -1);

  MArray a3(Array({1}));
  REQUIRE(noSizeSearch(a3, 1) == 0);
  REQUIRE(noSizeSearch(a3, 9) == -1);
  REQUIRE(noSizeSearch(a3, 0) == -1);
}
