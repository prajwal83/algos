#include "common.h"
#include "../../test_framework/catch.hpp"

class MyQueue
{
public:
  explicit MyQueue(const int size) : _addStack(size), _removeStack(size), _size(size) {}

  void add(int i)
  {
    if(full())
      throw std::string("queue full");
    _addStack.push(i);
  }

  int remove()
  {
    if(empty())
      throw std::string("queue empty");
    if(_removeStack.empty())
      while(!_addStack.empty())
        _removeStack.push(_addStack.pop());
    return _removeStack.pop();
  }
  
  bool empty() const { return _addStack.empty() && _removeStack.empty(); }
  bool full() const { return _addStack.size() + _removeStack.size() == _size; }

private:
  Stack<int> _addStack;
  Stack<int> _removeStack;
  int _size;
};

TEST_CASE("MyQueue with size 1", "[ch3.4]")
{
  MyQueue q(1);
  REQUIRE_THROWS_AS(q.remove(), std::string);
  q.add(10);
  REQUIRE(q.remove() == 10);
  REQUIRE_THROWS_AS(q.remove(), std::string);
  q.add(20);
  REQUIRE_THROWS_AS(q.add(1), std::string);
  REQUIRE(q.remove() == 20);
  REQUIRE_THROWS_AS(q.remove(), std::string);
}

TEST_CASE("MyQueue with size > 1", "[ch3.4]")
{
  MyQueue q(5);

  REQUIRE_THROWS_AS(q.remove(), std::string);
  q.add(10);
  q.add(20);
  q.add(30);
  REQUIRE(q.remove() == 10);
  REQUIRE(q.remove() == 20);
  REQUIRE(q.remove() == 30);
  REQUIRE_THROWS_AS(q.remove(), std::string);

  q.add(10);
  q.add(20);
  q.add(30);
  REQUIRE(q.remove() == 10);
  q.add(40);
  REQUIRE(q.remove() == 20);
  q.add(50);
  REQUIRE(q.remove() == 30);
  q.add(60);
  REQUIRE(q.remove() == 40);
  q.add(70);
  q.add(80);
  q.add(90);
  REQUIRE_THROWS_AS(q.add(100), std::string);
  REQUIRE(q.remove() == 50);
  q.add(100);
  REQUIRE(q.remove() == 60);
  REQUIRE(q.remove() == 70);
  q.add(110);
  q.add(120);
  REQUIRE_THROWS_AS(q.add(130), std::string);
  REQUIRE(q.remove() == 80);
  REQUIRE(q.remove() == 90);
  REQUIRE(q.remove() == 100);
  REQUIRE(q.remove() == 110);
  REQUIRE(q.remove() == 120);
  REQUIRE_THROWS_AS(q.remove(), std::string);
  
  //repeat
  q.add(10);
  q.add(20);
  q.add(30);
  REQUIRE(q.remove() == 10);
  q.add(40);
  REQUIRE(q.remove() == 20);
  q.add(50);
  REQUIRE(q.remove() == 30);
  q.add(60);
  REQUIRE(q.remove() == 40);
  q.add(70);
  q.add(80);
  q.add(90);
  REQUIRE_THROWS_AS(q.add(100), std::string);
  REQUIRE(q.remove() == 50);
  q.add(100);
  REQUIRE(q.remove() == 60);
  REQUIRE(q.remove() == 70);
  q.add(110);
  q.add(120);
  REQUIRE_THROWS_AS(q.add(130), std::string);
  REQUIRE(q.remove() == 80);
  REQUIRE(q.remove() == 90);
  REQUIRE(q.remove() == 100);
  REQUIRE(q.remove() == 110);
  REQUIRE(q.remove() == 120);
  REQUIRE_THROWS_AS(q.remove(), std::string);
}
