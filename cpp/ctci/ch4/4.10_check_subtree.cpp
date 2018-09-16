#include <list>
#include "../../test_framework/catch.hpp"
#include "common.h"

bool matchTree(TreeNodePtr parentRoot, TreeNodePtr childRoot)
{
  if(childRoot == nullptr)
    return true;

  if(parentRoot == nullptr)
    return false;

  if(parentRoot->value != childRoot->value)
    return false;

  return matchTree(parentRoot->left, childRoot->left) && matchTree(parentRoot->right, childRoot->right);
}

bool checkSubtree(TreeNodePtr parentRoot, TreeNodePtr childRoot)
{
  std::list<TreeNodePtr> bfsQ;

  bfsQ.push_back(parentRoot);
  while(!bfsQ.empty())
  {
    auto node = *bfsQ.begin();
    bfsQ.pop_front();
    if(node->left) bfsQ.push_back(node->left);
    if(node->right) bfsQ.push_back(node->right);
    if(matchTree(node, childRoot))
      return true;
  }
  return false;
}

TEST_CASE("check subtree", "[ch4.10]")
{
  TreeNodePtr root(new TreeNode(100));
  TreeNodePtr child(new TreeNode(100));
  REQUIRE(checkSubtree(root, child) == true);

  root->left.reset(new TreeNode(50));
  root->right.reset(new TreeNode(150));
  REQUIRE(checkSubtree(root, child) == true);

  child->left.reset(new TreeNode(50));
  child->right.reset(new TreeNode(150));
  REQUIRE(checkSubtree(root, child) == true);

  child->left->left.reset(new TreeNode(25));
  REQUIRE(checkSubtree(root, child) == false);
  REQUIRE(checkSubtree(child, root) == true);

  root->left->left.reset(new TreeNode(20));
  root->left->left->right.reset(new TreeNode(25));
  REQUIRE(checkSubtree(root, child->left->left) == true);

  child->left->left->right.reset(new TreeNode(30));
  child->left->left->left.reset(new TreeNode(20));

  root->left->left->right->right.reset(new TreeNode(30));
  REQUIRE(checkSubtree(root, child->left->left) == false);

  root->left->left->left.reset(new TreeNode(25));
  root->left->left->left->left.reset(new TreeNode(20));
  root->left->left->left->right.reset(new TreeNode(30));
  REQUIRE(checkSubtree(root, child->left->left) == true);
}
