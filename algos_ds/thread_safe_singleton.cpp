#include <iostream>
#include <thread>
#include <mutex>
#include <experimental/random>
#include <atomic>
#include <chrono>
#include "../test_framework/catch.hpp"

class Singleton
{
  private:
  static std::mutex _mutex;
  static std::once_flag create_once_flag;

  static std::atomic<Singleton*> _instance;
  static Singleton* _onceOnlyInstance;

  explicit Singleton(const int value) : _value(value) {}

  public:
  static Singleton* Instance() {
    auto p = _instance.load();
    if(p == nullptr) {
      std::lock_guard<std::mutex> g(_mutex);
      if((p = _instance.load()) == nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        volatile const auto rint = std::experimental::randint(0, 1000'000);
        _instance = p = new Singleton(rint);
      }
    }
    return p;
  }

  static Singleton* OnceOnlyInstance() {
    std::call_once(create_once_flag, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        volatile const auto rint = std::experimental::randint(0, 1000'000);
      _onceOnlyInstance = new Singleton(rint);
    });
    return _onceOnlyInstance;
  }

  int GetValue() const { return _value; }
  
  private:
  int _value;
};

std::atomic<Singleton*> Singleton::_instance { nullptr };
Singleton* Singleton::_onceOnlyInstance { nullptr };
std::mutex Singleton::_mutex;
std::once_flag Singleton::create_once_flag;

void dcl_create(std::vector<Singleton*>& singletons, const int index) {
  singletons[index] = Singleton::Instance();
}

TEST_CASE("thread safe DCL - Singleton", "[dcl]")
{
  const int SAMPLE_SIZE = 100;
  const int COUNT = 100;

  for(int i = 0; i < COUNT; ++i) {
    std::vector<Singleton*> singletons(SAMPLE_SIZE);
    std::vector<std::thread> threads;
    for(int i = 0; i < COUNT; ++i) 
      threads.push_back(std::thread(dcl_create, std::ref(singletons), i));

    for(int i = 0; i < threads.size(); ++i)
      threads[i].join();

    auto value = singletons[0]->GetValue();
    for(int i = 1; i < singletons.size(); ++i)
      REQUIRE(singletons[i]->GetValue() == value);
  }
}

void once_create(std::vector<Singleton*>& singletons, const int index) {
  singletons[index] = Singleton::OnceOnlyInstance();
}

TEST_CASE("thread safe once only - Singleton", "[once]")
{
  const int SAMPLE_SIZE = 100;
  const int COUNT = 100;

  for(int i = 0; i < COUNT; ++i) {
    std::vector<Singleton*> singletons(SAMPLE_SIZE);
    std::vector<std::thread> threads;
    for(int i = 0; i < COUNT; ++i) 
      threads.push_back(std::thread(once_create, std::ref(singletons), i));

    for(int i = 0; i < threads.size(); ++i)
      threads[i].join();

    auto value = singletons[0]->GetValue();
    for(int i = 1; i < singletons.size(); ++i)
      REQUIRE(singletons[i]->GetValue() == value);
  }
}
