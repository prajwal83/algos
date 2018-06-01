#include <map>
#include "common.h"
#include "../../test_framework/catch.hpp"

int totalSumPaths(TreeNodePtr root, const int targetSum, int runningSum, std::map<int, int>& sumPathCounter)
{
  if(root == nullptr)
    return 0;

  runningSum += root->value;
  int total = 0;
  auto it = sumPathCounter.find(runningSum - targetSum);
  if(it != sumPathCounter.end())
    total += it->second;

  if(runningSum == targetSum)
    ++total;

  auto r = sumPathCounter.insert(std::make_pair(runningSum, 1));
  if(!r.second)
    ++r.first->second;

  total += totalSumPaths(root->left, targetSum, runningSum, sumPathCounter);
  total += totalSumPaths(root->right, targetSum, runningSum, sumPathCounter);

  auto x = sumPathCounter.find(runningSum);
  --x->second;
  if(!x->second)
    sumPathCounter.erase(x);

  return total;
}

int totalSumPaths(TreeNodePtr root, const int targetSum)
{
  std::map<int, int> sumPathCounter;
  return totalSumPaths(root, targetSum, 0, sumPathCounter);
}

TEST_CASE("paths with sum", "[ch4.12]")
{
  TreeNodePtr root(new TreeNode(10));

  root->left.reset(new TreeNode(5));
  root->right.reset(new TreeNode(-3));

  root->left->left.reset(new TreeNode(3));
  root->left->right.reset(new TreeNode(1));

  root->right->right.reset(new TreeNode(11));

  root->left->left->left.reset(new TreeNode(3));
  root->left->left->right.reset(new TreeNode(-2));

  root->left->right->right.reset(new TreeNode(2));

  REQUIRE(totalSumPaths(root, 8) == 3);
  REQUIRE(totalSumPaths(root, 18) == 3);
  REQUIRE(totalSumPaths(root, 1) == 2);
  REQUIRE(totalSumPaths(root, 3) == 3);
}
