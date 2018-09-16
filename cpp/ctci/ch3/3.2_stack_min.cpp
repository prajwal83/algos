#include "common.h"
#include "../../test_framework/catch.hpp"

class StackMin
{
private:
  struct Item
  {
    Item() : value(0), min(0) {}
    Item(int v, int m) : value(v), min(m) {}
    int value;
    int min;
  };

public:
  explicit StackMin(const int size) : _v(new Item[size]), _size(size), _top(-1) {}

  int pop()
  {
    if(_top == -1)
      throw std::string("stack empty");
    return _v[_top--].value;
  }

  void push(int i)
  {
    if(_top == _size - 1)
      throw std::string("stack overflow");
    const int min = _top == -1 ? i : (i < _v[_top].min ? i : _v[_top].min);
    _v[++_top] = Item(i, min);
  }

  int min()
  {
    if(_top == -1)
      throw std::string("stack empty");
    return _v[_top].min;
  }

private:
  std::unique_ptr<Item[]> _v;
  int _size;
  int _top;
};

class StackMin2
{
public:
  explicit StackMin2(const int size) : _main(size), _mins(size) {}

  int pop()
  {
    if(_main.peek() == _mins.peek())
      _mins.pop();
    return _main.pop();
  }

  void push(int i)
  {
    _main.push(i);
    if(_mins.empty() || _mins.peek() > i)
      _mins.push(i);
  }

  int min()
  {
    return _mins.peek();
  }
  
private:
  Stack<int> _main;
  Stack<int> _mins;
};

TEST_CASE("min stack", "[ch3.2]")
{
  StackMin s(5);
  REQUIRE_THROWS_AS(s.pop(), std::string);
  REQUIRE_THROWS_AS(s.min(), std::string);

  s.push(1);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 1);
  REQUIRE_THROWS_AS(s.pop(), std::string);
  REQUIRE_THROWS_AS(s.min(), std::string);

  s.push(3);
  s.push(2);
  s.push(1);
  s.push(5);
  s.push(2);

  REQUIRE_THROWS_AS(s.push(0), std::string);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 5);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 1);
  REQUIRE(s.min() == 2);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 3);
  REQUIRE(s.pop() == 3);
  REQUIRE_THROWS_AS(s.min(), std::string);
  REQUIRE_THROWS_AS(s.pop(), std::string);

  s.push(3);
  s.push(2);
  s.push(1);
  s.push(5);
  s.push(2);

  REQUIRE_THROWS_AS(s.push(0), std::string);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 5);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 1);
  REQUIRE(s.min() == 2);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 3);
  REQUIRE(s.pop() == 3);
  REQUIRE_THROWS_AS(s.min(), std::string);
  REQUIRE_THROWS_AS(s.pop(), std::string);
}

TEST_CASE("min stack with 2 separate stacks", "[ch3.2]")
{
  StackMin2 s(5);
  REQUIRE_THROWS_AS(s.pop(), std::string);
  REQUIRE_THROWS_AS(s.min(), std::string);

  s.push(1);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 1);
  REQUIRE_THROWS_AS(s.pop(), std::string);
  REQUIRE_THROWS_AS(s.min(), std::string);

  s.push(3);
  s.push(2);
  s.push(1);
  s.push(5);
  s.push(2);

  REQUIRE_THROWS_AS(s.push(0), std::string);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 5);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 1);
  REQUIRE(s.min() == 2);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 3);
  REQUIRE(s.pop() == 3);
  REQUIRE_THROWS_AS(s.min(), std::string);
  REQUIRE_THROWS_AS(s.pop(), std::string);

  s.push(3);
  s.push(2);
  s.push(1);
  s.push(5);
  s.push(2);

  REQUIRE_THROWS_AS(s.push(0), std::string);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 5);
  REQUIRE(s.min() == 1);
  REQUIRE(s.pop() == 1);
  REQUIRE(s.min() == 2);
  REQUIRE(s.pop() == 2);
  REQUIRE(s.min() == 3);
  REQUIRE(s.pop() == 3);
  REQUIRE_THROWS_AS(s.min(), std::string);
  REQUIRE_THROWS_AS(s.pop(), std::string);
}
