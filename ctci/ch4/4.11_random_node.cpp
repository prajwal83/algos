#include <iostream>
#include <map>
#include <random>
#include "../../test_framework/catch.hpp"
#include "common.h"

TreeNodePtr getRandomNodeBySize(TreeNodePtr root, std::mt19937& gen)
{
  std::uniform_int_distribution<> dis(1, root->size);
  int n = dis(gen);
  const int leftSize = root->left ? root->left->size : 0;
  if(root->left && n <= leftSize)
    return getRandomNodeBySize(root->left, gen);
  else if(n == leftSize + 1 || !root->right)
    return root;
  else
    return getRandomNodeBySize(root->right, gen);
}

TreeNodePtr getRandomNodeByPosition(TreeNodePtr root, const int pos)
{
  const int leftSize = root->left ? root->left->size : 0;
  if(root->left && pos <= leftSize)
    return getRandomNodeByPosition(root->left, pos);
  else if(pos == leftSize + 1 || !root->right)
    return root;
  else
    return getRandomNodeByPosition(root->right, pos - leftSize - 1);
}

void printDistribution(std::map<int, int>& distCount)
{
  const int MARGIN(8);
  for(const auto& it : distCount)
    std::cout << std::setw(MARGIN) << it.first;
  std::cout << std::endl;

  for(const auto& it : distCount)
    std::cout << std::setw(MARGIN) << it.second;
  std::cout << std::endl;

  bool done = false;
  while(!done)
  {
    done = true;
    for(auto& it : distCount)
    {
      if(it.second)
      {
        std::cout << std::setw(MARGIN) << "+";
        --it.second;
        done = false;
      }
      else
        std::cout << std::setw(MARGIN) << ".";
    }
    std::cout << std::endl;
  }
}

TEST_CASE("random node from BST using size", "[ch4.11]")
{
  std::random_device rd;
  std::mt19937 gen(rd());

  TreeNodePtr root(new TreeNode(100));
  root->inOrderInsert(50);
  root->inOrderInsert(150);
  root->inOrderInsert(25);
  root->inOrderInsert(75);
  root->inOrderInsert(125);
  root->inOrderInsert(175);
  root->inOrderInsert(200);

  std::map<int, int> distCount;
  distCount[25] = 0;
  distCount[50] = 0;
  distCount[75] = 0;
  distCount[100] = 0;
  distCount[125] = 0;
  distCount[150] = 0;
  distCount[175] = 0;
  distCount[200] = 0;

  for(int i = 0; i < 10; ++i)
    for(int j = 0; j < 8; ++j)
      ++distCount[getRandomNodeBySize(root, gen)->value];

  printDistribution(distCount);
}

TEST_CASE("random node from BST using position", "[ch4.11]")
{
  std::random_device rd;
  std::mt19937 gen(rd());

  TreeNodePtr root(new TreeNode(100));
  root->inOrderInsert(50);
  root->inOrderInsert(150);
  root->inOrderInsert(25);
  root->inOrderInsert(75);
  root->inOrderInsert(125);
  root->inOrderInsert(175);
  root->inOrderInsert(200);

  std::map<int, int> distCount;
  distCount[25] = 0;
  distCount[50] = 0;
  distCount[75] = 0;
  distCount[100] = 0;
  distCount[125] = 0;
  distCount[150] = 0;
  distCount[175] = 0;
  distCount[200] = 0;

  std::uniform_int_distribution<> dis(1, root->size);

  for(int i = 0; i < 10; ++i)
    for(int j = 0; j < 8; ++j)
      ++distCount[getRandomNodeByPosition(root, dis(gen))->value];

  printDistribution(distCount);
}
