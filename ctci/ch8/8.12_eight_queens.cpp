#include <iostream>
#include <cmath>
#include "../../test_framework/catch.hpp"

static const int DIM = 8;
using Positions = std::vector<int>;
using Result = std::vector<Positions>;

bool checkValid(Positions& positions, int row, int col)
{
  for(int r = 0; r < row; ++r)
  {
    auto placedCol = positions[r];
    if(placedCol == col)
      return false;

    if(std::abs(placedCol - col) == (row - r))
      return false;
  }
  return true;
}

void solveEightQueens(int row, Positions positions, Result& results)
{
  if(row == DIM)
  {
    results.push_back(positions);
    return;
  }

  for(int c = 0; c < DIM; ++c)
  {
    if(!checkValid(positions, row, c))
      continue;
    positions[row] = c;
    solveEightQueens(row + 1, positions, results);
  }
}

void printSol(const Result& results)
{
  int i = 0;
  
  std::ios oldCoutFlags(nullptr);
  oldCoutFlags.copyfmt(std::cout);

  for(const auto& positions : results)
  {
    std::cout.copyfmt(oldCoutFlags);
    std::cout << ++i << ")" << std::endl;
    for(int r = 0; r < DIM; ++r)
      std::cout << std::setw(2 * positions[r]) << 'X' << std::endl;
    std::cout << std::setfill('-') << std::setw(2 * DIM) << " " << std::endl;
  }
}

TEST_CASE("eight queens", "[ch8.12]")
{
  Positions positions(DIM, -1);
  Result results;
  solveEightQueens(0, positions, results);
  REQUIRE(results.size() == 92);
  
//  printSol(results);
}
