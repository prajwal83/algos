#pragma once
#include <vector>
#include <memory>

template <typename T>
struct Node
{
  Node() : _next(nullptr) {}
  T _elem;
  std::shared_ptr<Node> _next;
  using value_type = T;
};

using N = Node<int>;

struct SLL
{
  SLL() : _head(new N())
  {
  }

  SLL(std::initializer_list<typename N::value_type> v) { init(v); }

  SLL& operator=(std::initializer_list<typename N::value_type> v) { init(v); }
  SLL& operator=(const SLL& r) = delete;
  
  SLL(const SLL& r) : _head(new N())
  {
    r.copy(*this);
  }

  SLL(SLL&& r) : _head(new N())
  {
    _head->_next = r._head->_next;
    r._head->_next = nullptr;
  }

  ~SLL() { }

  void print()
  {
    for(auto n = _head->_next; n != nullptr; n = n->_next)
      std::cout << n->_elem << " ";
    std::cout << std::endl;
  }

  void copy(SLL& dest) const
  {
    auto prev = dest._head;
    for(auto n = _head->_next; n != nullptr; n = n->_next)
    {
      std::shared_ptr<N> x(new N());
      x->_elem = n->_elem;
      prev->_next = x;
      prev = prev->_next;
    }
  }

  bool operator==(const SLL& other)
  {
    auto l = _head->_next;
    auto r = other._head->_next;
    for(; l != nullptr && r != nullptr; l = l->_next, r = r->_next)
    {
      if (l->_elem != r->_elem)
        return false;
    }
    return l == nullptr && r == nullptr;
  }

  int length()
  {
    int len = 0;
    for(auto n = _head->_next; n != nullptr; n = n->_next) ++len;
    return len;
  }

  std::shared_ptr<N> nthNode(int n)
  {
    int i = 0;
    auto nthNode = _head->_next;
    for(; nthNode != nullptr && i < n; nthNode = nthNode->_next, ++i);
    return nthNode;
  }

  std::shared_ptr<N> _head;

private:
  void init(std::initializer_list<typename N::value_type> v)
  {
    _head.reset(new N());
    auto prev = _head;
    for(auto i : v)
    {
      auto* x = new N();
      x->_elem = i;
      prev->_next.reset(x);
      prev = prev->_next;
    }
  }
};

