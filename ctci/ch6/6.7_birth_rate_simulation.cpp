#include <iostream>
#include <random>
#include <functional>
#include <cmath>
#include "../../test_framework/catch.hpp"

double genderRatio(int totalFamilies)
{
  int boyCount = 0;
  int girlCount = 0;
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);

  std::function<void(int)> simulateBirth;

  simulateBirth = [&](int n) {
    if(n == 0)
      return;
    int b = 0;
    for(int i = 0; i < n; ++i)
    {
      if(dis(gen))
        ++girlCount;
      else
        ++b;
    }

    boyCount += b;
    simulateBirth(b);
  };

  simulateBirth(totalFamilies);

  return std::floor( ((double)boyCount / (boyCount + girlCount)) * 100 + 0.5 ) / 100;
}

TEST_CASE("birth rate - apocalyptic decision", "[ch6.7]")
{
  const int totalFamilies = 2000;
  std::cout << "Run birth simulation on total families = " << totalFamilies << std::endl;
  std::cout << "Gender ratio (for boys) = " << genderRatio(totalFamilies) << std::endl;
}
