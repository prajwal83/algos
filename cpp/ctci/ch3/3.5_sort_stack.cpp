#include "common.h"
#include "../../test_framework/catch.hpp"

Stack<int> sort_stack(Stack<int>& in)
{
  Stack<int> out(in.size());

  while(!in.empty())
  {
    const auto elem = in.pop();
    while(!out.empty() && elem > out.peek())
      in.push(out.pop());
    out.push(elem);
  }
  return out;
}

TEST_CASE("sort stack", "[ch3.5]")
{
  Stack<int> in { };
  Stack<int> out { };

  REQUIRE(sort_stack(in) == out);

  in = { 3, 4, 5, 1, 2, 6 };
  out = { 6, 5, 4, 3, 2, 1 };
  REQUIRE(sort_stack(in) == out);

  in = { 6, 5, 4, 3, 2, 1 };
  out = { 6, 5, 4, 3, 2, 1 };
  REQUIRE(sort_stack(in) == out);

  in = { 1, 2, 3, 4, 5, 6 };
  out = { 6, 5, 4, 3, 2, 1 };
  REQUIRE(sort_stack(in) == out);

  in = { 1 };
  out = { 1 };
  REQUIRE(sort_stack(in) == out);

  in = { 1, 1 };
  out = { 1, 1 };
  REQUIRE(sort_stack(in) == out);

  in = { 2, 1, 1, 2 };
  out = { 2, 2, 1, 1 };
  REQUIRE(sort_stack(in) == out);
}
