#include <iostream>
#include <random>
#include <vector>
#include "../../test_framework/catch.hpp"

void zero_matrix(int* matrix, int m, int n)
{
  std::vector<bool> zeroRow(m, false);
  std::vector<bool> zeroColumn(n, false);

  for(int i = 0; i < m; ++i)
    for(int j = 0; j < n; ++j)
      if(matrix[i * n + j] == 0)
        zeroRow[i] = zeroColumn[j] = true;
  
  for(int i = 0; i < m; ++i)
    for(int j = 0; j < n; ++j)
      if(zeroRow[i] || zeroColumn[j])
        matrix[i * n + j] = 0;
}

bool zcompare_matrix(int* m1, int* m2, int len)
{
  for(int i = 0; i < len; ++i)
    if(m1[i] != m2[i])
      return false;
  return true;
}

void zinit_matrix(int* m, std::vector<int> v)
{
  for(int i = 0; i < v.size(); ++i)
    m[i] = v[i];
}

TEST_CASE("empty zero matrix", "[ch1.8]")
{
  int inMatrix[10][3] = { 1, 2 };
  int outMatrix[10][3] = { 1, 2 };

  zero_matrix((int*)inMatrix, 0, 0);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 30) == true );
}

TEST_CASE("1x1 zero matrix", "[ch1.8]")
{
  int inMatrix[1][1] = { 1 };
  int outMatrix[1][1] = { 1 };

  zero_matrix((int*)inMatrix, 1, 1);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 1) == true );

  zinit_matrix((int*)inMatrix, { 0 });
  zinit_matrix((int*)outMatrix, { 0 });

  zero_matrix((int*)inMatrix, 1, 1);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 1) == true );
}

TEST_CASE("2x2 zero matrix", "[ch1.8]")
{
  int inMatrix[2][2] = { 1, 2, 3, 4 };
  int outMatrix[2][2] = { 1, 2, 3, 4 };

  zero_matrix((int*)inMatrix, 2, 2);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 4) == true );

  zinit_matrix((int*)inMatrix, { 
    0, 1,
    1, 1
  });
  zinit_matrix((int*)outMatrix, {
    0, 0,
    0, 1
  });

  zero_matrix((int*)inMatrix, 2, 2);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 4) == true );

  zinit_matrix((int*)inMatrix, { 
    0, 1,
    1, 0
  });
  zinit_matrix((int*)outMatrix, {
    0, 0,
    0, 0
  });

  zero_matrix((int*)inMatrix, 2, 2);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 4) == true );

  zinit_matrix((int*)inMatrix, { 
    0, 1,
    0, 1
  });
  zinit_matrix((int*)outMatrix, {
    0, 0,
    0, 0
  });

  zero_matrix((int*)inMatrix, 2, 2);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 4) == true );
}

TEST_CASE("4x3 zero matrix", "[ch1.8]")
{
  int inMatrix[4][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
  int outMatrix[4][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

  zero_matrix((int*)inMatrix, 4, 3);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 12) == true );

  zinit_matrix((int*)inMatrix, { 
    0, 1, 2,
    1, 1, 3,
    3, 4, 0,
    1, 1, 1
  });
  zinit_matrix((int*)outMatrix, {
    0, 0, 0,
    0, 1, 0,
    0, 0, 0,
    0, 1, 0
  });

  zero_matrix((int*)inMatrix, 4, 3);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 12) == true );

  zinit_matrix((int*)inMatrix, { 
    0, 1, 2,
    1, 1, 3,
    3, 4, 1,
    1, 0, 1
  });
  zinit_matrix((int*)outMatrix, {
    0, 0, 0,
    0, 0, 3,
    0, 0, 1,
    0, 0, 0
  });

  zero_matrix((int*)inMatrix, 4, 3);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 12) == true );

  zinit_matrix((int*)inMatrix, { 
    0, 1, 0,
    1, 1, 1,
    3, 4, 1,
    1, 0, 1
  });
  zinit_matrix((int*)outMatrix, {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  });

  zero_matrix((int*)inMatrix, 4, 3);
  REQUIRE( zcompare_matrix((int*)inMatrix, (int*)outMatrix, 12) == true );
}
