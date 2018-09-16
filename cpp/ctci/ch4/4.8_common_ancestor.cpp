#include "../../test_framework/catch.hpp"
#include "common.h"

using Result = std::pair<TreeNodePtr, bool>;

Result findCommonAncestor(TreeNodePtr root, TreeNodePtr p, TreeNodePtr q)
{
  if(root == nullptr)
    return Result(nullptr, false);

  if(root == p && root == q)
    return Result(root, true);

  auto x = findCommonAncestor(root->left, p, q);
  if(x.second)
    return x;

  auto y = findCommonAncestor(root->right, p, q);
  if(y.second)
    return y;

  if(x.first != nullptr && y.first != nullptr)
    return Result(root, true);

  if(root == p || root == q)
    return Result(root, x.first != nullptr || y.first != nullptr);

  return x.first != nullptr ? x : y;
}

TEST_CASE("common ancestor", "[ch4.8]")
{
  TreeNodePtr root(new TreeNode(10));
  TreeNodePtr l1(new TreeNode(10));
  TreeNodePtr r1(new TreeNode(10));
  TreeNodePtr ll2(new TreeNode(10));
  TreeNodePtr lr2(new TreeNode(10));
  TreeNodePtr rl2(new TreeNode(10));
  TreeNodePtr rr2(new TreeNode(10));

  root->left = l1;
  root->right = r1;

  l1->left = ll2;
  l1->right = lr2;

  r1->left = rl2;
  r1->right = rr2;

  TreeNodePtr odd(new TreeNode(10));

  REQUIRE(findCommonAncestor(root, root, root) == Result(root, true));
  REQUIRE(findCommonAncestor(root, root, odd) == Result(root, false));

  REQUIRE(findCommonAncestor(root, l1, r1) == Result(root, true));
  REQUIRE(findCommonAncestor(root, ll2, rl2) == Result(root, true));
  REQUIRE(findCommonAncestor(root, ll2, rr2) == Result(root, true));
  REQUIRE(findCommonAncestor(root, lr2, rl2) == Result(root, true));
  REQUIRE(findCommonAncestor(root, lr2, rr2) == Result(root, true));

  REQUIRE(findCommonAncestor(root, l1, rr2) == Result(root, true));
  REQUIRE(findCommonAncestor(root, l1, ll2) == Result(l1, true));
  REQUIRE(findCommonAncestor(root, l1, lr2) == Result(l1, true));
  REQUIRE(findCommonAncestor(root, ll2, lr2) == Result(l1, true));
  REQUIRE(findCommonAncestor(root, root, lr2) == Result(root, true));

  REQUIRE(findCommonAncestor(root, r1, lr2) == Result(root, true));
  REQUIRE(findCommonAncestor(root, r1, rl2) == Result(r1, true));
  REQUIRE(findCommonAncestor(root, r1, rr2) == Result(r1, true));
  REQUIRE(findCommonAncestor(root, rl2, rr2) == Result(r1, true));
  REQUIRE(findCommonAncestor(root, root, rr2) == Result(root, true));
}
