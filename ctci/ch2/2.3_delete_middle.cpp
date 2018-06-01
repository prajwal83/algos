#include <iostream>
#include <cmath>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

//Notes: it can't work if the element to delete is last node
//one possible option is to mark the last node as dummy node
void delete_middle(std::shared_ptr<N> midNode)
{
  std::shared_ptr<N> prev(nullptr);
  auto n = midNode;
  for(; n->_next != nullptr; prev = n, n = n->_next)
    n->_elem = n->_next->_elem;
  if(prev)
    prev->_next = nullptr;
}

TEST_CASE("delete middle node", "[ch2.3]")
{
  SLL inList { 1 };
  SLL outList { 1 };

  delete_middle(inList._head->_next);
  REQUIRE(inList == outList);
  
  inList = { 1, 2 };
  outList = { 1, 2 };
  delete_middle(inList._head->_next->_next);
  REQUIRE(inList == outList);
  outList = { 2 };
  delete_middle(inList._head->_next);
  REQUIRE(inList == outList);

  inList = { 1, 2, 3, 4};
  outList = { 1, 3, 4 };
  delete_middle(inList._head->_next->_next);
  REQUIRE(inList == outList);
}

