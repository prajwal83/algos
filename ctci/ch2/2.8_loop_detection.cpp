#include <iostream>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

std::shared_ptr<N> loop_start(const SLL& sll)
{
  auto slow = sll._head;
  auto fast = sll._head;
  while(true)
  {
    slow = slow->_next;

    if(fast->_next)
      fast = fast->_next->_next;
    else
      return nullptr;

    if(!slow || !fast)
      return nullptr;

    if(slow == fast)
      break;
  }

  
  slow = sll._head;
  for(; slow != fast; slow = slow->_next, fast = fast->_next);
  return slow;
}

TEST_CASE("loop detection", "[ch2.8]")
{
  SLL l1 {};
  REQUIRE(loop_start(l1) == nullptr);

  l1 = { 1 };
  REQUIRE(loop_start(l1) == nullptr);

  l1._head->_next->_next = l1._head->_next;
  REQUIRE(loop_start(l1) == l1._head->_next);

  l1 = { 1, 2 };
  REQUIRE(loop_start(l1) == nullptr);

  auto i = l1.nthNode(0);
  l1.nthNode(1)->_next = i;
  REQUIRE(loop_start(l1) == i); 

  i = l1.nthNode(1);
  i->_next = i;
  REQUIRE(loop_start(l1) == i); 

  l1 = { 1, 2, 3, 4, 5, 6 };
  i = l1.nthNode(3);
  l1.nthNode(5)->_next = i;
  REQUIRE(loop_start(l1) == i);
  REQUIRE(i->_elem == 4);

  l1 = { 1, 2, 3, 4, 5, 6, 7 };
  i = l1.nthNode(3);
  l1.nthNode(6)->_next = i;
  REQUIRE(loop_start(l1) == i);
  REQUIRE(i->_elem == 4);

  l1 = { 1, 2, 3, 4, 5, 6, 7 };
  i = l1.nthNode(1);
  l1.nthNode(6)->_next = i;
  REQUIRE(loop_start(l1) == i);
  REQUIRE(i->_elem == 2);

  l1 = { 1, 2, 3, 4, 5, 6, 7 };
  REQUIRE(loop_start(l1) == nullptr);
}
