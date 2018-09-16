#include <iostream>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

const std::shared_ptr<N> intersection_point(const SLL& sll1, const SLL& sll2)
{
  auto last1 = sll1._head->_next;
  auto last2 = sll2._head->_next;

  if(!last1 || !last2)
    return nullptr;

  int c1 = 1;
  for(; last1->_next != nullptr; ++c1, last1 = last1->_next);
  int c2 = 1;
  for(; last2->_next != nullptr; ++c2, last2 = last2->_next);

  if (last1 != last2)
    return nullptr;

  auto n1 = sll1._head->_next;
  auto n2 = sll2._head->_next;
  int chopLen = 0;
  if (c1 > c2)
  {
    chopLen = c1 - c2;
  }
  else if(c1 < c2)
  {
    chopLen = c2 - c1;
    n1 = sll2._head->_next;
    n2 = sll1._head->_next;
  }

  while(chopLen--)
    n1 = n1->_next;

  for(; n1 != nullptr && n2 != nullptr; n1 = n1->_next, n2 = n2->_next)
    if(n1 == n2)
      return n1;

  // should never happen
  return nullptr;
}

TEST_CASE("intersection point", "[ch2.7]")
{
  SLL l1 {};
  SLL l2 {};
  REQUIRE(intersection_point(l1, l2) == nullptr);

  l1 = { 1 };
  l2 = { };
  REQUIRE(intersection_point(l1, l2) == nullptr);
  REQUIRE(intersection_point(l2, l1) == nullptr);

  l1 = { 1 };
  l2 = { 1 };
  auto i = l1.nthNode(0);
  l2._head->_next = i;
  REQUIRE(intersection_point(l1, l2) == i);
  REQUIRE(intersection_point(l2, l1) == i);

  l1 = { 1, 2, 3 };
  l2 = { 1 };
  i = l1.nthNode(0);
  l2._head->_next = i;
  REQUIRE(intersection_point(l1, l2) == i);
  REQUIRE(intersection_point(l2, l1) == i);

  l1 = { 1, 2, 3 };
  l2 = { 1 };
  i = l1.nthNode(1);
  l2._head->_next = i;
  REQUIRE(intersection_point(l1, l2) == i);
  REQUIRE(intersection_point(l2, l1) == i);

  l1 = { 1, 2, 3 };
  l2 = { 1, 2, 3, 4 };
  i = l1.nthNode(2);
  i->_next = l2.nthNode(1);
  REQUIRE(intersection_point(l1, l2) == i->_next);
  REQUIRE(intersection_point(l2, l1) == i->_next);

  l1 = { 1, 2, 3 };
  l2 = { 1, 2, 3, 4 };
  i = l1.nthNode(2);
  i->_next = l2.nthNode(2);

  REQUIRE(intersection_point(l1, l2) == i->_next);
  REQUIRE(intersection_point(l2, l1) == i->_next);

  l1 = { 1, 2, 3 };
  l2 = { 1, 2, 3, 4 };
  REQUIRE(intersection_point(l1, l2) == nullptr);
  REQUIRE(intersection_point(l2, l1) == nullptr);
}
