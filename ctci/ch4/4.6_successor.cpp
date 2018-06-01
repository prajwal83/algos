#include "common.h"
#include "../../test_framework/catch.hpp"

TreeNodePtr inOrderSuccessor(TreeNodePtr n)
{
  if(n->right == nullptr)
  {
    if(n->parent == nullptr)
      return nullptr;

    if(n->parent->right == n)
    {
      auto p = n->parent;
      while(p->parent != nullptr)
      {
        if(p->parent->left == p)
          return p->parent;
        p = p->parent;
      }
      return nullptr;
    }

    return n->parent;
  }

  auto next = n->right;
  while(next->left != nullptr)
    next = next->left;
  return next;
}

TEST_CASE("in order successor", "[ch4.6]")
{
  TreeNodePtr n(new TreeNode(10));
  REQUIRE(inOrderSuccessor(n) == nullptr);

  n->left.reset(new TreeNode(1));
  n->left->parent = n;
  REQUIRE(inOrderSuccessor(n) == nullptr);
  REQUIRE(inOrderSuccessor(n->left) == n);

  n->right.reset(new TreeNode(1));
  n->right->parent = n;
  REQUIRE(inOrderSuccessor(n) == n->right);
  REQUIRE(inOrderSuccessor(n->left) == n);
  REQUIRE(inOrderSuccessor(n->right) == nullptr);

  n->left->left.reset(new TreeNode(1));
  n->left->left->parent = n->left;
  REQUIRE(inOrderSuccessor(n) == n->right);
  REQUIRE(inOrderSuccessor(n->left) == n);
  REQUIRE(inOrderSuccessor(n->right) == nullptr);

  n->left->right.reset(new TreeNode(1));
  n->left->right->parent = n->left;
  REQUIRE(inOrderSuccessor(n) == n->right);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right);
  REQUIRE(inOrderSuccessor(n->right) == nullptr);

  n->right->left.reset(new TreeNode(1));
  n->right->left->parent = n->right;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right);
  REQUIRE(inOrderSuccessor(n->right) == nullptr);

  n->left->right->right.reset(new TreeNode(1));
  n->left->right->right->parent = n->left->right;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right);
  REQUIRE(inOrderSuccessor(n->right) == nullptr);
  REQUIRE(inOrderSuccessor(n->left->right->right) == n);

  n->left->right->left.reset(new TreeNode(1));
  n->left->right->left->parent = n->left->right;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right->left);
  REQUIRE(inOrderSuccessor(n->right) == nullptr);

  n->left->right->left->right.reset(new TreeNode(1));
  n->left->right->left->right->parent = n->left->right->left;
  REQUIRE(inOrderSuccessor(n->left->right->left->right) == n->left->right);

  n->right->right.reset(new TreeNode(1));
  n->right->right->parent = n->right;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right->left);
  REQUIRE(inOrderSuccessor(n->right) == n->right->right);

  n->right->right->right.reset(new TreeNode(1));
  n->right->right->right->parent = n->right->right;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right->left);
  REQUIRE(inOrderSuccessor(n->right) == n->right->right);

  n->right->right->left.reset(new TreeNode(1));
  n->right->right->left->parent = n->right->right;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right->left);
  REQUIRE(inOrderSuccessor(n->right) == n->right->right->left);

  n->right->right->left->left.reset(new TreeNode(1));
  n->right->right->left->left->parent = n->right->right->left;
  REQUIRE(inOrderSuccessor(n) == n->right->left);
  REQUIRE(inOrderSuccessor(n->left) == n->left->right->left);
  REQUIRE(inOrderSuccessor(n->right) == n->right->right->left->left);
  REQUIRE(inOrderSuccessor(n->right->right->left->left) == n->right->right->left);
  REQUIRE(inOrderSuccessor(n->right->right->left) == n->right->right);
  REQUIRE(inOrderSuccessor(n->right->right) == n->right->right->right);
  REQUIRE(inOrderSuccessor(n->right->right->right) == nullptr);
}
