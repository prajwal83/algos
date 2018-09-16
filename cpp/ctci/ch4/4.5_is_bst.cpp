#include "common.h"
#include "../../test_framework/catch.hpp"

std::pair<bool, TreeNodePtr> isBST(const TreeNodePtr n)
{
  if(n == nullptr)
    return std::make_pair(true, nullptr);

  auto l = isBST(n->left);
  if(!l.first)
    return l;

  if(l.second && l.second->value > n->value)
    return std::make_pair(false, nullptr);

  auto r = isBST(n->right);
  if(!r.first)
    return r;

  if(r.second)
  {
    if(r.second->value <= n->value)
      return std::make_pair(false, nullptr);
    return std::make_pair(true, r.second);
  }
  else
    return std::make_pair(true, n);
}

TEST_CASE("is tree a BST", "[ch4.5]")
{
  TreeNodePtr r(new TreeNode(10));
  REQUIRE(isBST(r).first == true);

  r->left.reset(new TreeNode(20));
  REQUIRE(isBST(r).first == false);

  r->left->value = 5;
  REQUIRE(isBST(r).first == true);

  r->left->right.reset(new TreeNode(40));
  REQUIRE(isBST(r).first == false);

  r->left->right->value = 7;
  REQUIRE(isBST(r).first == true);

  r->right.reset(new TreeNode(30));
  REQUIRE(isBST(r).first == true);

  r->right->left.reset(new TreeNode(50));
  REQUIRE(isBST(r).first == false);

  r->right->left->value = 20;
  REQUIRE(isBST(r).first == true);

  r->right->left->left.reset(new TreeNode(60));
  REQUIRE(isBST(r).first == false);

  r->right->left->left->value = 13;
  REQUIRE(isBST(r).first == true);

  r->right->left->right.reset(new TreeNode(70));
  REQUIRE(isBST(r).first == false);

  r->right->left->right->value = 25;
  REQUIRE(isBST(r).first == true);

  r->right->right.reset(new TreeNode(80));
  REQUIRE(isBST(r).first == true);
}
