#pragma once
#include <iostream>
#include <chrono>
#include <functional>

namespace ch8 {
  static void TimeMetrics(const std::string& fname, const std::function<void()>& f)
  {
    auto start = std::chrono::system_clock::now();
    f();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time taken to run " << fname << " = " << diff.count() << "s" << std::endl;
  }
};
