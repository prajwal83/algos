#include <iostream>
#include <random>
#include "../../test_framework/catch.hpp"

void swap(int& x, int& y)
{
  int tmp = x;
  x = y;
  y = tmp;
}

void rotate_swap(int* matrix, int dim, int row, int col, int distance)
{
  if(distance == 0)
    return;

  auto ind = [dim](int row, int col) { return row * dim + col; };

//  std::cout << "(" << row << "," << col << ")" << distance << std::endl;
//  std::cout << ind(col, row + distance) << " <-> " << ind(row, col) << std::endl;
//  std::cout << ind(row + distance, dim - col - 1) << " <-> " << ind(row, col) << std::endl;
//  std::cout << ind(dim - col - 1, row) << " <-> " << ind(row, col) << std::endl;
  swap(matrix[ind(col, row + distance)], matrix[ind(row, col)]);
  swap(matrix[ind(row + distance, dim - col - 1)], matrix[ind(row, col)]);
  swap(matrix[ind(dim - col - 1, row)], matrix[ind(row, col)]);
}

void rotate_plane(int* matrix, int dim, int row, int col, int len)
{
  for(int i = 0; i < len - 1; ++i)
    rotate_swap(matrix, dim, row, col + i, len - 1);
}

void rotate_matrix(int dim, int* matrix)
{
  int it = dim / 2;
  for(int row = 0; row < it; ++row)
    rotate_plane(matrix, dim, row, row, dim - 2 * row);
}

bool compare_matrix(int* m1, int* m2, int len)
{
  for(int i = 0; i < len; ++i)
    if(m1[i] != m2[i])
      return false;
  return true;
}

void init_matrix(int* m, std::vector<int> v)
{
  for(int i = 0; i < v.size(); ++i)
    m[i] = v[i];
}

TEST_CASE("matrix rotation clockwise 90'", "[ch1.7]")
{
  const int dim = 10;
  const int len = dim * dim;
  int inMatrix[dim][dim] = { 1, 2 };
  int outMatrix[dim][dim] = { 1, 2 };

  rotate_matrix(0, (int*)inMatrix);
  REQUIRE( compare_matrix((int*)inMatrix, (int*)outMatrix, len) == true );

  rotate_matrix(1, (int*)inMatrix);
  REQUIRE( compare_matrix((int*)inMatrix, (int*)outMatrix, 1) == true );

  init_matrix((int*)inMatrix, { 
    1, 2, 
    3, 4 
  });
  init_matrix((int*)outMatrix, {
    3, 1,
    4, 2
  });
  rotate_matrix(2, (int*)inMatrix);
  REQUIRE( compare_matrix((int*)inMatrix, (int*)outMatrix, 4) == true );

  init_matrix((int*)inMatrix, {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  });
  init_matrix((int*)outMatrix, {
    7, 4, 1,
    8, 5, 2,
    9, 6, 3
  });
  rotate_matrix(3, (int*)inMatrix);
  REQUIRE( compare_matrix((int*)inMatrix, (int*)outMatrix, 9) == true );

  init_matrix((int*)inMatrix, {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  });
  init_matrix((int*)outMatrix, {
    13, 9, 5, 1,
    14, 10, 6, 2,
    15, 11, 7, 3,
    16,12, 8, 4
  });
  rotate_matrix(4, (int*)inMatrix);
  REQUIRE( compare_matrix((int*)inMatrix, (int*)outMatrix, 16) == true );
}

TEST_CASE("random generated matrix rotation by 90'", "[ch1.7]")
{
  const int dim = 100;
  const int len = dim * dim;
  int inMatrix[dim][dim];
  int outMatrix[dim][dim];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 1000);

  //random init
  for(int i = 0; i < dim; ++i)
    for(int j = 0; j < dim; ++j)
      inMatrix[i][j] = dis(gen);

  //copy rotate
  for(int i = 0, c = dim -1; i < dim; ++i, --c)
    for(int j = 0, r = 0; j < dim; ++j, ++r)
      outMatrix[r][c] = inMatrix[i][j];

  rotate_matrix(dim, (int*)inMatrix);
  REQUIRE( compare_matrix((int*)inMatrix, (int*)outMatrix, len) == true );
}
