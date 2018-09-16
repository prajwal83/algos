#include <vector>
#include <algorithm>
#include "../../test_framework/catch.hpp"

using Array = std::vector<int>;

void sortedMerge(Array& a, Array& b, const int aSize)
{
  const int bSize = b.size();
  const int tSize = aSize + bSize;
  for(int i = aSize - 1, j = (tSize - 1); i >= 0 && j >= 0; --i, --j)
    a[j] = a[i];

  int i = bSize, j = 0, k = 0;
  
  while(i < tSize && j < bSize)
  {
    if(a[i] < b[j])
      a[k++] = a[i++];
    else
      a[k++] = b[j++];
  }

  while(j < bSize)
    a[k++] = b[j++];
}

void sortedMergeBackward(Array& a, Array& b, const int aSize)
{
  const int bSize = b.size();
  const int tSize = aSize + bSize;

  int i = aSize - 1, j = bSize - 1, k = tSize - 1;
  
  while(j >= 0)
  {
    if(i >= 0 && a[i] > b[j])
      a[k--] = a[i--];
    else
      a[k--] = b[j--];
  }
}

TEST_CASE("sorted merge", "[ch10.1]")
{
  Array a;
  Array b;

  sortedMerge(a, b, 0);
  REQUIRE(a == Array { });

  a = { 1, -1 };
  b = { 2 };
  sortedMerge(a, b, 1);
  REQUIRE(a == Array({ 1, 2 }));

  a = { 1, -1, -1 };
  b = { 2, 3 };
  sortedMerge(a, b, 1);
  REQUIRE(a == Array({ 1, 2, 3 }));

  a = { 10, 11, -1, -1 };
  b = { 1, 2 };
  sortedMerge(a, b, 2);
  REQUIRE(a == Array({ 1, 2, 10, 11 }));

  a = { 3, 5, 10, 11, -1, -1, -1, -1 };
  b = { 1, 2, 5, 7 };
  sortedMerge(a, b, 4);
  REQUIRE(a == Array({ 1, 2, 3, 5, 5, 7, 10, 11 }));
}

TEST_CASE("sorted merge - backward", "[ch10.1]")
{
  Array a;
  Array b;

  sortedMergeBackward(a, b, 0);
  REQUIRE(a == Array { });

  a = { 1, -1 };
  b = { 2 };
  sortedMergeBackward(a, b, 1);
  REQUIRE(a == Array({ 1, 2 }));

  a = { 1, -1, -1 };
  b = { 2, 3 };
  sortedMergeBackward(a, b, 1);
  REQUIRE(a == Array({ 1, 2, 3 }));

  a = { 10, 11, -1, -1 };
  b = { 1, 2 };
  sortedMergeBackward(a, b, 2);
  REQUIRE(a == Array({ 1, 2, 10, 11 }));

  a = { 3, 5, 10, 11, -1, -1, -1, -1 };
  b = { 1, 2, 5, 7 };
  sortedMergeBackward(a, b, 4);
  REQUIRE(a == Array({ 1, 2, 3, 5, 5, 7, 10, 11 }));
}
