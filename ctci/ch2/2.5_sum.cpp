#include <iostream>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

std::shared_ptr<N> add_to_end(std::shared_ptr<N> n, int v)
{
  n->_next.reset(new N());
  n->_next->_elem = v;
  return n->_next;
};

SLL lsum(const SLL& sll1, const SLL& sll2)
{
  SLL sum;
  auto prev = sum._head;
  typename N::value_type carry = 0;

  for(auto n1 = sll1._head->_next, n2 = sll2._head->_next; n1 != nullptr || n2 != nullptr;)
  {
    auto s = carry + (n1 ? n1->_elem : 0) + (n2 ? n2->_elem : 0);
    carry = s > 9 ? 1 : 0;
    s %= 10;
    prev = add_to_end(prev, s);

    if(n1) n1 = n1->_next;
    if(n2) n2 = n2->_next;
  }
  if(carry)
    prev = add_to_end(prev, carry);

  return std::move(sum);
}

typename N::value_type add_digit(std::shared_ptr<N> n1, std::shared_ptr<N> n2, std::shared_ptr<N> s)
{
  if(n1 == nullptr && n2 == nullptr)
    return 0;
  
  s = add_to_end(s, 0);

  int carry = add_digit(n1 ? n1->_next : nullptr, n2 ? n2->_next : nullptr, s);
  int sum = carry + (n1 ? n1->_elem : 0) + (n2 ? n2->_elem : 0);
  s->_elem = sum % 10;
  return sum > 9 ? 1 : 0;
}

SLL bsum(SLL sll1, SLL sll2)
{
  auto padZero = [](SLL& sll, int len)
  {
    for(int i = 0; i < len; ++i)
    {
      std::shared_ptr<N> n(new N());
      n->_elem = 0;
      n->_next = sll._head->_next;
      sll._head->_next = n;
    }
  };

  SLL sum;
  auto l1 = sll1.length();
  auto l2 = sll2.length();
  if(l1 < l2)
    padZero(sll1, l2 - l1);
  else if(l2 < l1)
    padZero(sll2, l1 - l2);

  int carry = add_digit(sll1._head->_next, sll2._head->_next, sum._head);
  if(carry)
  {
    std::shared_ptr<N> n(new N());
    n->_elem = carry;
    n->_next = sum._head->_next;
    sum._head->_next = n;
  }
  return std::move(sum);
}

TEST_CASE("little-endian linked list sum", "[ch2.5]")
{
  SLL n1 {};
  SLL n2 {};
  REQUIRE(lsum(n1, n2) == SLL {});

  n1 = { 1 };
  n2 = { 0 };
  REQUIRE(lsum(n1, n2) == SLL { 1 });
  REQUIRE(lsum(n2, n1) == SLL { 1 });
  
  n1 = { 9 };
  n2 = { 8 };
  REQUIRE(lsum(n1, n2) == SLL({ 7, 1 }));

  n1 = { 9, 1 };
  n2 = { 8 };
  REQUIRE(lsum(n1, n2) == SLL({ 7, 2 }));
  REQUIRE(lsum(n2, n1) == SLL({ 7, 2 }));
  REQUIRE(lsum(n1, n1) == SLL({ 8, 3 }));

  n1 = { 9, 1 };
  n2 = { 1, 8 };
  REQUIRE(lsum(n1, n2) == SLL({ 0, 0, 1 }));

  n1 = { 7, 1, 6 };
  n2 = { 5, 9, 2 };
  REQUIRE(lsum(n1, n2) == SLL({ 2, 1, 9 }));

  n1 = { 1, 0, 0, 7, 1, 6 };
  n2 = { 5, 9, 2 };
  REQUIRE(lsum(n1, n2) == SLL({ 6, 9, 2, 7, 1, 6 }));
}

TEST_CASE("big-endian linked list sum", "[ch2.5]")
{
  SLL n1 {};
  SLL n2 {};
  REQUIRE(bsum(n1, n2) == SLL {});

//  n1 = { 1 };
//  n2 = { 0 };
//  REQUIRE(bsum(n1, n2) == SLL { 1 });
//  REQUIRE(bsum(n2, n1) == SLL { 1 });
//  
//  n1 = { 9 };
//  n2 = { 8 };
//  REQUIRE(bsum(n1, n2) == SLL({ 1, 7 }));
//
//  n1 = { 1, 9 };
//  n2 = { 8 };
//  REQUIRE(bsum(n1, n2) == SLL({ 2, 7 }));
//  REQUIRE(bsum(n2, n1) == SLL({ 2, 7 }));
//  REQUIRE(bsum(n1, n1) == SLL({ 3, 8 }));
//
//  n1 = { 1, 9 };
//  n2 = { 8, 1 };
//  REQUIRE(bsum(n1, n2) == SLL({ 1, 0, 0 }));
//
//  n1 = { 6, 1, 7 };
//  n2 = { 2, 9, 5 };
//  REQUIRE(bsum(n1, n2) == SLL({ 9, 1, 2 }));
//
//  n1 = { 6, 1, 7, 0, 0, 1 };
//  n2 = { 2, 9, 5 };
//  REQUIRE(bsum(n1, n2) == SLL({ 6, 1, 7, 2, 9, 6 }));
}
