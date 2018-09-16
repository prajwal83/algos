#include <iostream>
#include <thread>
#include <experimental/random>
#include <atomic>
#include <chrono>
#include "../test_framework/catch.hpp"

template <typename T>
class DualThreadQueue {
  public:
  explicit DualThreadQueue(int size) : _size(size), _queue(size), _count(0), _readPtr(0), _writePtr(0) {}

  void Produce(const T& e) {
    while(_count == _size) std::this_thread::yield();
    _queue[_writePtr] = e;
    _writePtr = (_writePtr + 1) % _size;
    ++_count;
  }

  T Consume() {
    while(_count == 0) std::this_thread::yield();
    auto temp = _queue[_readPtr];
    _readPtr = (_readPtr + 1) % _size;
    --_count;
    return temp;
  }

  private:
  const int _size;
  std::vector<T> _queue;
  std::atomic<int> _count;
  int _readPtr, _writePtr;
};

void producer(DualThreadQueue<int>& dtq, const std::vector<int>& input) {
  for(int i = 0; i < input.size(); ++i)
    dtq.Produce(input[i]);
}

void consumer(DualThreadQueue<int>& dtq, std::vector<int>& output, int size) {
  for(int i = 0; i < size; ++i)
    output.push_back(dtq.Consume());
}

TEST_CASE("thread safe single producer/consumer", "[spc]")
{
  const int SAMPLE_SIZE = 1000;
  const int COUNT = 100;

  for(int i = 0; i < COUNT; ++i) {
    DualThreadQueue<int> dtq(10);
    std::vector<std::thread> threads;
    
    std::vector<int> input;
    for(int i = 0; i < SAMPLE_SIZE; ++i)
      input.push_back(std::experimental::randint(0, 100'000));

    threads.push_back(std::thread(producer, std::ref(dtq), std::ref(input)));

    std::vector<int> output;
    threads.push_back(std::thread(consumer, std::ref(dtq), std::ref(output), input.size()));

    for(int i = 0; i < threads.size(); ++i)
      threads[i].join();

    REQUIRE(output.size() == input.size());
    for(int i = 0; i < input.size(); ++i)
      REQUIRE(output[i] == input[i]);
  }
}
