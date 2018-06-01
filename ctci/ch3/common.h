#pragma once
#include <memory>

template <typename T>
class Stack
{
public:
  explicit Stack(const int size) : _v(new T[size]), _size(size), _top(-1) {}

  Stack(std::initializer_list<T> l) : _v(nullptr)
  {
    init(l);
  }

  void operator=(std::initializer_list<T> l)
  {
    init(l);
  }

  Stack(Stack&& r)
  {
    _v.reset(r._v.release());
    _size = r._size;
    _top = r._top;
  }

  bool operator==(const Stack& r)
  {
    if(_top != r._top)
      return false;
    for(int i = 0; i <= _top; ++i)
      if(_v[i] != r._v[i])
        return false;
    return true;
  }

  T pop()
  {
    if(empty())
      throw std::string("stack empty");
    return _v[_top--];
  }

  void push(T i)
  {
    if(full())
      throw std::string("stack overflow");
    _v[++_top] = i;
  }

  T peek()
  {
    if(empty())
      throw std::string("stack empty");
    return _v[_top];
  }

  bool empty() const { return _top == -1; }

  bool full() const { return _top == _size - 1; }

  int size() const { return _top + 1; }

private:
  void init(std::initializer_list<T> l)
  {
    _v.reset(new T[l.size()]);
    _size = l.size();
    _top = -1;
    for(auto i : l)
      push(i);
  }

  std::unique_ptr<T[]> _v;
  int _size;
  int _top;
};
