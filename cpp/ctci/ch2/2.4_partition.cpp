#include <iostream>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

void partition(SLL& l, typename N::value_type pe)
{
  //unstable partition
  bool swap = false;
  auto prev = l._head;
  for(auto n = l._head->_next; n != nullptr; prev = n, n = n->_next)
  {
    if(n->_elem >= pe)
      swap = true;
    else if(swap)
    {
      prev->_next = n->_next;
      n->_next = l._head->_next;
      l._head->_next = n;
      n = prev;
    }
  }
}

TEST_CASE("partition", "[ch2.4]")
{
  SLL inList {};
  SLL outList {};

  partition(inList, 1);
  REQUIRE(inList == outList);

  inList = { 1, 3, 1, 2, 5 };
  outList = { 1, 3, 1, 2, 5 };
  partition(inList, 1);
  REQUIRE(inList == outList);

  inList = { 1, 3, 1, 2, 5 };
  outList = { 2, 1, 1, 3, 5 };
  partition(inList, 3);
  REQUIRE(inList == outList);

  inList = { 1, 3, 1, 2, 5 };
  outList = { 1, 3, 1, 2, 5 };
  partition(inList, 5);
  REQUIRE(inList == outList);
  
  inList = { 6, 5, 4, 3, 2, 1 };
  outList = { 1, 2, 3, 4, 5, 6 };
  partition(inList, 6);
  REQUIRE(inList == outList);
}
