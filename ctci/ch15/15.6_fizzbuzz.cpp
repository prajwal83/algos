#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
#include <string>
#include "../../test_framework/catch.hpp"

namespace {
std::atomic_int count;
//int count;
std::stringstream ss;
};

void runner(std::function<bool(int)> validate, std::function<std::string(int)> str, int max)
{
  while (true)
  {
    auto x = count.load();
    if(x > max)
      return;
    if(validate(x))
    {
      ss << str(x) << " ";
      ++count;
    }
  }
}

std::string expectedOutput(int max)
{
  std::stringstream s;
  for(int i = 1; i <= max; ++i)
  {
    if(i % 3 == 0 && i % 5 == 0)
      s << "FB" << " ";
    else if(i % 3 == 0 && i % 5 != 0)
      s << "F" << " ";
    else if(i % 3 != 0 && i % 5 == 0)
      s << "B" << " ";
    else
      s << i << " ";
  }
  return s.str();
}

TEST_CASE("multithreaded fizz buzz", "[ch15.6]")
{
  auto runJob = [](const int max) {
    std::thread fizz(runner, [](int i){ return i % 3 == 0 && i % 5 != 0; }, [](int i) { return std::string("F"); }, max);
    std::thread buzz(runner, [](int i){ return i % 3 != 0 && i % 5 == 0; }, [](int i) { return std::string("B"); }, max);
    std::thread fizzbuzz(runner, [](int i){ return i %  3 == 0 && i % 5 == 0; }, [](int i) { return std::string("FB"); }, max);
    std::thread number(runner, [](int i){ return i % 3 != 0 && i % 5 != 0; }, [](int i) { return std::to_string(i); }, max);

    fizz.join();
    buzz.join();
    fizzbuzz.join();
    number.join();
  };

  for(int i = 0; i < 50; ++i)
  {
    count = 1;
    ss.str("");
    runJob(10);
    REQUIRE(ss.str() == expectedOutput(10));
  }
}
