#include <cmath>
#include "common.h"
#include "../../test_framework/catch.hpp"

bool isBalanced(const TreeNodePtr n)
{
  if(n == nullptr)
    return true;

  if(isBalanced(n->left) && isBalanced(n->right))
    return std::abs(height(n->left) - height(n->right)) < 2;
  else
    return false;
}

int isBalancedHeight(const TreeNodePtr n)
{
  if(n == nullptr)
    return 0;

  auto lh = isBalancedHeight(n->left);
  if(lh < 0) return lh;

  auto rh = isBalancedHeight(n->right);
  if(rh < 0) return rh;

  if(std::abs(lh - rh) > 1)
    return -1;
  return std::max(lh, rh) + 1;
}

bool isBalancedOptimized(const TreeNodePtr n)
{
  return isBalancedHeight(n) >= 0;
}

TEST_CASE("check is balanced", "[ch4.4]")
{
  TreeNodePtr r(new TreeNode(10));
  REQUIRE(isBalanced(r) == true);

  r->left.reset(new TreeNode(20));
  REQUIRE(isBalanced(r) == true);

  r->left->right.reset(new TreeNode(40));
  REQUIRE(isBalanced(r) == false);

  r->right.reset(new TreeNode(30));
  REQUIRE(isBalanced(r) == true);

  r->right->left.reset(new TreeNode(50));
  REQUIRE(isBalanced(r) == true);

  r->right->left->left.reset(new TreeNode(60));
  REQUIRE(isBalanced(r) == false);

  r->right->left->right.reset(new TreeNode(70));
  REQUIRE(isBalanced(r) == false);

  r->right->right.reset(new TreeNode(80));
  REQUIRE(isBalanced(r) == true);
}

TEST_CASE("check is balanced - optimized", "[ch4.4]")
{
  TreeNodePtr r(new TreeNode(10));
  REQUIRE(isBalancedOptimized(r) == true);

  r->left.reset(new TreeNode(20));
  REQUIRE(isBalancedOptimized(r) == true);

  r->left->right.reset(new TreeNode(40));
  REQUIRE(isBalancedOptimized(r) == false);

  r->right.reset(new TreeNode(30));
  REQUIRE(isBalancedOptimized(r) == true);

  r->right->left.reset(new TreeNode(50));
  REQUIRE(isBalancedOptimized(r) == true);

  r->right->left->left.reset(new TreeNode(60));
  REQUIRE(isBalancedOptimized(r) == false);

  r->right->left->right.reset(new TreeNode(70));
  REQUIRE(isBalancedOptimized(r) == false);

  r->right->right.reset(new TreeNode(80));
  REQUIRE(isBalancedOptimized(r) == true);
}
