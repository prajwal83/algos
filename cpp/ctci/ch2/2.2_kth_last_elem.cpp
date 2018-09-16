#include <iostream>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

const std::shared_ptr<N> kth_last_node(const SLL& l, int k)
{
  auto kthNode = l._head;
  auto n = l._head->_next;
  for(int i = 0; i < k; ++i)
  {
    if(n == nullptr)
      break;
    n = n->_next;
  }

  while(n)
  {
    n = n->_next;
    kthNode = kthNode->_next;
  }

  if(kthNode.get() == l._head.get())
    return nullptr;
  return kthNode;
}

TEST_CASE("kth last element", "[ch2.2]")
{
  SLL l{};

  REQUIRE(kth_last_node(l, 0) == nullptr);

  l = { 1 };
  REQUIRE(kth_last_node(l, 0)->_elem == 1);
  REQUIRE(kth_last_node(l, 1) == nullptr);

  l = { 1, 2, 3 };
  REQUIRE(kth_last_node(l, 0)->_elem == 3);
  REQUIRE(kth_last_node(l, 1)->_elem == 2);
  REQUIRE(kth_last_node(l, 2)->_elem == 1);
  REQUIRE(kth_last_node(l, 3) == nullptr);
}

