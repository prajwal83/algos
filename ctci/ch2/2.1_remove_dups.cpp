#include <iostream>
#include <set>
#include "list_common.h"
#include "../../test_framework/catch.hpp"

// n + Sum(log x) --> O(n + nlogn) --> O(nlogn)
// ignoring set<> insert/lookup --> O(n)
void RemoveDupsWithTempBuffer(std::shared_ptr<N> head)
{
  std::set<typename N::value_type> s;
  auto prev = head;
  for(auto n = head->_next; n != nullptr;)
  {
    if(s.count(n->_elem))
    {
      prev->_next = n->_next;
      n = n->_next;
    }
    else
    {
      prev = n;
      s.insert(n->_elem);
      n = n->_next;
    }
  }
}

// O(n^2)
void RemoveDupsWithoutTempBuffer(std::shared_ptr<N> head)
{
  auto remove = [](std::shared_ptr<N> start)
  {
    auto prev = start;
    for(auto n = start->_next; n != nullptr;)
    {
      if(n->_elem == start->_elem)
      {
        prev->_next = n->_next;
        n = n->_next;
      }
      else
      {
        prev = n;
        n = n->_next;
      }
    }
  };

  for(auto n = head->_next; n != nullptr; n = n->_next)
    remove(n);
}

TEST_CASE("remove duplicates using temp buffer", "[ch2.1]")
{
  SLL inList {};
  SLL outList {};

  RemoveDupsWithTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1 };
  outList = { 1 };
  RemoveDupsWithTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1, 1 };
  outList = { 1 };
  RemoveDupsWithTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1, 2, 1, 2 };
  outList = { 1, 2 };
  RemoveDupsWithTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1, 3, 3, 2, 3, 3, 1, 2, 1, 1, 1 };
  outList = { 1, 3, 2 };
  RemoveDupsWithTempBuffer(inList._head);
  REQUIRE( inList == outList );
}

TEST_CASE("remove duplicates wihtout using temp buffer", "[ch2.1]")
{
  SLL inList {};
  SLL outList {};

  RemoveDupsWithoutTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1 };
  outList = { 1 };
  RemoveDupsWithoutTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1, 1 };
  outList = { 1 };
  RemoveDupsWithoutTempBuffer(inList._head);
  REQUIRE( inList == outList );
  
  inList = { 1, 2, 1, 2 };
  outList = { 1, 2 };
  RemoveDupsWithoutTempBuffer(inList._head);
  REQUIRE( inList == outList );

  inList = { 1, 3, 3, 2, 3, 3, 1, 2, 1, 1, 1 };
  outList = { 1, 3, 2 };
  RemoveDupsWithoutTempBuffer(inList._head);
  REQUIRE( inList == outList );
}
