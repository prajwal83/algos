#include <iostream>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

bool isPalindromeByReversing(const SLL& sll)
{
  if(sll._head->_next == nullptr || sll._head->_next->_next == nullptr)
    return true;

  std::vector<typename N::value_type> stack;

  auto slow = sll._head;
  auto fast = sll._head;

  do
  {
    stack.push_back(slow->_next->_elem);
    slow = slow->_next;
    fast = fast->_next->_next;
  } while(fast != nullptr && fast->_next != nullptr);

  int si = stack.size() - (fast ? 1 : 2);
  for(auto n = slow->_next; n != nullptr; n = n->_next)
    if(stack[si--] != n->_elem)
      return false;

  return true;
}

TEST_CASE("is palindrome by reversing", "[ch2.6]")
{
  SLL sll {};
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2 };
  REQUIRE(isPalindromeByReversing(sll) == false);

  sll = { 1, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 2 };
  REQUIRE(isPalindromeByReversing(sll) == false);

  sll = { 1, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 1, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 1, 1, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 3, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 3, 3, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 3, 4, 3, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 3, 4, 5, 3, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == false);

  sll = { 1, 2, 3, 5, 4, 5, 3, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);

  sll = { 1, 2, 3, 5, 5, 3, 2, 1 };
  REQUIRE(isPalindromeByReversing(sll) == true);
}
