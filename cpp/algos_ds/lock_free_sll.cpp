#include <iostream>
#include <thread>
#include <experimental/random>
#include <chrono>
#include <memory>
#include <atomic>
#include "../test_framework/catch.hpp"

template <typename T>
class slist
{
public:
  struct node
  {
    node(const T& value) : _value(value), _next(nullptr) {}
    T     _value;
    std::shared_ptr<node> _next;
  };

  slist() : _head(nullptr) {}
  ~slist() {}

  bool empty() const { return _head == nullptr; }

  void push_front(const T& value) 
  {
    auto n = std::make_shared<node>(value);
    n->_next = std::atomic_load(&_head);
    while(!std::atomic_compare_exchange_weak(&_head, &(n->_next), n)) {}
  }

  void pop_front()
  {
    auto p = std::atomic_load(&_head);
    while(p && !std::atomic_compare_exchange_weak(&_head, &p, p->_next)) {}
  }

  node* find(const T& value) const
  {
    auto p = std::atomic_load(&_head);
    while(p && p->_value != value)
      p = p->_next;
    return p.get();
  }

  std::shared_ptr<node> _head;
};

using islist = slist<int>;

void push_thread(islist& sll, const int start, const int end)
{
  for(int i = start; i < end; ++i)
    sll.push_front(i);
}

void pop_thread(islist& sll, const int count)
{
  for(int i = 0; i < count; ++i)
    sll.pop_front();
}

void find_thread(const islist& sll, const int start, const int end)
{
  for(int i = start; i < end; ++i)
    REQUIRE(sll.find(i) != nullptr);
}

TEST_CASE("lock free - singly linked list", "[sll]")
{
  islist sll;

  auto sizer = [](const int x) { return x * 1; };

  for(int i = sizer(2000); i < sizer(4000); ++i)
    sll.push_front(i);

  std::vector<std::thread> threads;

  threads.push_back(std::thread(push_thread, std::ref(sll), sizer(0), sizer(800)));
  threads.push_back(std::thread(push_thread, std::ref(sll), sizer(800), sizer(1500)));
  threads.push_back(std::thread(push_thread, std::ref(sll), sizer(1500), sizer(2000)));

  threads.push_back(std::thread(pop_thread, std::ref(sll), sizer(300)));
  threads.push_back(std::thread(pop_thread, std::ref(sll), sizer(300)));
  threads.push_back(std::thread(pop_thread, std::ref(sll), sizer(400)));

//  threads.push_back(std::thread(find_thread, std::ref(sll), sizer(3000), sizer(3500)));
  //threads.push_back(std::thread(find_thread, std::ref(sll), sizer(3500), sizer(4000)));

  for(int i = 0; i < threads.size(); ++i)
    threads[i].join();

  int count = 0;
  auto p = std::atomic_load(&sll._head);
  while(p)
  {
    ++count;
    p = p->_next;
  }

  REQUIRE(count == 3000);
}
