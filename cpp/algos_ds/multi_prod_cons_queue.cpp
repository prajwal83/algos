#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include "../test_framework/catch.hpp"

class Semaphore {
public:
  Semaphore() : _done(false) {}

  void signal() {
    std::lock_guard<std::mutex> g(_m);
    _done = true;
    cv.notify_one();
  }

  void wait() {
    std::unique_lock<std::mutex> g(_m);
    cv.wait(g, [this]() { return _done; });
    _done = false;
  }

private:
  std::mutex _m;
  std::condition_variable cv;
  bool _done;
};

template <typename T>
class ThreadSafeSlotBuffer {
public:
  explicit ThreadSafeSlotBuffer(int size) : _size(size), _slots(size), _sems(size) {
    for(auto& a : _slots) a.store(T());
  }

  void Produce(const int slot, const T& e) {
    while(_slots[slot] != 0);
    _slots[slot] = e;
    _sems[slot].signal();
  }

  T Consume(int slot) {
    while(_slots[slot] == 0)
      _sems[slot].wait();
    T v = _slots[slot];
    _slots[slot] = 0;
    return v;
  }

private:
  const int _size;
  std::vector<std::atomic<T>> _slots;
  std::vector<Semaphore> _sems;
};

void producer(ThreadSafeSlotBuffer<int>& mtq, const int slot) {
  const auto SIZE = 1'000;
  const auto start = slot * SIZE;
  for(int i = start; i < start + SIZE; ++i)
    mtq.Produce(slot, i + 1);
  mtq.Produce(slot, -1);
}

void consumer(ThreadSafeSlotBuffer<int>& mtq, const int slot, std::vector<int>& output) {
  int v;
  while((v = mtq.Consume(slot)) != -1)
    output.push_back(v);
}

TEST_CASE("thread safe multiple producer/consumer", "[mpc]")
{
  const int COUNT = 100;
  const int POOL_SIZE = 8;

  for(int i = 0; i < COUNT; ++i) {
    ThreadSafeSlotBuffer<int> mtq(POOL_SIZE);
    
    std::vector<std::vector<int>> outputs(POOL_SIZE);
    std::vector<std::thread> threads;
    for(int i = 0; i < POOL_SIZE; ++i) {
      threads.push_back(std::thread(producer, std::ref(mtq), i));
      threads.push_back(std::thread(consumer, std::ref(mtq), i, std::ref(outputs[i])));
    }

    for(int i = 0; i < threads.size(); ++i)
      threads[i].join();

    std::vector<int> expectedOutput;
    for(int i = 1; i <= 8'000; ++i)
      expectedOutput.push_back(i);

    std::vector<int> output;
    for(int i = 0; i < outputs.size(); ++i)
      output.insert(output.end(), outputs[i].begin(), outputs[i].end());

    REQUIRE(output.size() == expectedOutput.size());
    std::sort(output.begin(), output.end());
    for(int i = 0; i < expectedOutput.size(); ++i)
      REQUIRE(output[i] == expectedOutput[i]);
  }
}
