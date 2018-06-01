#include <string>
#include <vector>
#include "../../test_framework/catch.hpp"

using Result = std::vector<std::string>;

void permutate(const std::string& str, Result& result)
{
  if(str.length() == 1)
    result.push_back(str);

  for(int i = 0; i < str.length(); ++i)
  {
    auto c = str[i];
    auto temp = str;
    Result tr;
    permutate(temp.erase(i, 1), tr);
    for(const auto& x : tr)
      result.push_back(c + x);
  }
}

TEST_CASE("permutation without dups", "[ch8.7]")
{
  Result result;

  permutate("", result);
  REQUIRE(result.size() == 0);
  result.clear();

  permutate("1", result);
  REQUIRE(result == Result({ "1" }));
  result.clear();

  permutate("12", result);
  REQUIRE(result == Result({ 
    "12",
    "21"
  }));
  result.clear();

  permutate("123", result);
  REQUIRE(result == Result({ 
    "123",
    "132",
    "213",
    "231",
    "312",
    "321"
  }));
  result.clear();

  permutate("1234", result);
  REQUIRE(result == Result({ 
    "1234", "1243", "1324", "1342",
    "1423", "1432", "2134", "2143",
    "2314", "2341", "2413", "2431",
    "3124", "3142", "3214", "3241",
    "3412", "3421", "4123", "4132",
    "4213", "4231", "4312", "4321",
  }));
  result.clear();
}
