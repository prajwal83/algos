#pragma once
#include <memory>
#include <vector>

struct TreeNode;
using TreeNodePtr = std::shared_ptr<TreeNode>;

struct TreeNode
{
  TreeNode(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr), size(1) {}

  int value;
  TreeNodePtr left;
  TreeNodePtr right;
  TreeNodePtr parent;
  int size;

  void inOrderInsert(int v)
  {
    if(v <= value)
    {
      if(left == nullptr)
        left.reset(new TreeNode(v));
      else
        left->inOrderInsert(v);
    }
    else
    {
      if(right == nullptr)
        right.reset(new TreeNode(v));
      else
        right->inOrderInsert(v);
    }
    ++size;
  }
};

static int height(const TreeNodePtr n)
{
  if(n == nullptr)
    return 0;
  return std::max(height(n->left), height(n->right)) + 1;
}

static std::vector<int> inOrder(const TreeNodePtr n)
{
  std::vector<int> data;
  std::function<void (const TreeNodePtr)> traverse;

  traverse = [&](const TreeNodePtr i) {
    if(i == nullptr)
      return;
    traverse(i->left);
    data.push_back(i->value);
    traverse(i->right);
  };

  traverse(n);
  return data;
}
