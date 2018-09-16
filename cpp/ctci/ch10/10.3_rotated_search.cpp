#include <vector>
#include "../../test_framework/catch.hpp"

using Array = std::vector<int>;

int search(const Array& a, int e, int left, int right)
{
  if(left > right)
    return -1;

  int mid = (left + right) / 2;
  if(a[mid] == e) return mid;
  if(a[left] == e) return left;
  if(a[right] == e) return right;
  
  if(a[left] < a[mid])
  {
    if(e > a[left] && e < a[mid])
      return search(a, e, left, mid - 1);
    return search(a, e, mid + 1, right);
  }
  else if(a[mid] < a[right])
  {
    if(e > a[mid] && e < a[right])
      return search(a, e, mid + 1, right);
    return search(a, e, left, mid - 1);
  }
  else
  {
    int r = search(a, e, left, mid - 1);
    return r == -1 ? search(a, e, mid + 1, right) : r;
  }
}

int search(const Array& a, int e)
{
  return search(a, e, 0, a.size() - 1);
}

TEST_CASE("rotated search", "[ch10.3]")
{
  Array a1 = { 1, 2, 3, 4, 5, 6, 7, 8 };
  for(auto i : a1)
    REQUIRE(search(a1, i) == (i - 1));

  Array a2 = { 40, 0, 1, 20, 30, 35, 38 };
  REQUIRE(search(a2, 40) == 0);
  REQUIRE(search(a2, 0) == 1);
  REQUIRE(search(a2, 1) == 2);
  REQUIRE(search(a2, 20) == 3);
  REQUIRE(search(a2, 30) == 4);
  REQUIRE(search(a2, 35) == 5);
  REQUIRE(search(a2, 38) == 6);

  Array a3 = { 15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14 };
  REQUIRE(search(a3, 5) == 8);

  Array a4 = { 20, 0, 1, 20, 20, 20, 20 };
  REQUIRE(search(a4, 40) == -1);
  REQUIRE(search(a4, 0) == 1);
  REQUIRE(search(a4, 1) == 2);
  REQUIRE(search(a4, 20) == 3);
  REQUIRE(search(a4, 30) == -1);
  REQUIRE(search(a4, 35) == -1);
  REQUIRE(search(a4, 38) == -1);
}
