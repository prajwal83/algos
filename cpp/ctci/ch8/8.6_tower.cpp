#include <iostream>
#include "../../test_framework/catch.hpp"

using Tower = std::vector<int>;

void moveDisks(int count, Tower& source, Tower& temp, Tower& destination)
{
  if(count <= 0)
    return;

  moveDisks(count - 1, source, destination, temp);

  if(!destination.empty() && *destination.rbegin() < *source.rbegin())
    throw "disk movement failed";

  destination.push_back(*source.rbegin());
  source.pop_back();

  moveDisks(count - 1, temp, source, destination);
}

void startMoveDisks(Tower& source, Tower& temp, Tower& destination)
{
  moveDisks(source.size(), source, temp, destination);
}

TEST_CASE("tower of hanoi", "[ch8.6]")
{
  Tower source = { };
  Tower temp;
  Tower destination;

  startMoveDisks(source, temp, destination);
  REQUIRE(source.empty() == true);
  REQUIRE(temp.empty() == true);
  REQUIRE(destination == Tower());

  source.clear(); temp.clear(); destination.clear();
  source = { 1 };
  startMoveDisks(source, temp, destination);
  REQUIRE(source.empty() == true);
  REQUIRE(temp.empty() == true);
  REQUIRE(destination == Tower({ 1 }));

  source.clear(); temp.clear(); destination.clear();
  source = { 2, 1 };
  startMoveDisks(source, temp, destination);
  REQUIRE(source.empty() == true);
  REQUIRE(temp.empty() == true);
  REQUIRE(destination == Tower({ 2, 1 }));

  source.clear(); temp.clear(); destination.clear();
  source = { 3, 2, 1 };
  startMoveDisks(source, temp, destination);
  REQUIRE(source.empty() == true);
  REQUIRE(temp.empty() == true);
  REQUIRE(destination == Tower({ 3, 2, 1 }));
  
  source.clear(); temp.clear(); destination.clear();
  source = { 4, 3, 2, 1 };
  startMoveDisks(source, temp, destination);
  REQUIRE(source.empty() == true);
  REQUIRE(temp.empty() == true);
  REQUIRE(destination == Tower({ 4, 3, 2, 1 }));

  source.clear(); temp.clear(); destination.clear();
  source = { 5, 4, 3, 2, 1 };
  startMoveDisks(source, temp, destination);
  REQUIRE(source.empty() == true);
  REQUIRE(temp.empty() == true);
  REQUIRE(destination == Tower({ 5, 4, 3, 2, 1 }));
}
