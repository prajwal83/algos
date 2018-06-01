#include <iostream>
#include <vector>
#include <list>
#include "../../test_framework/catch.hpp"
#include "common.h"

using NodeSequence = std::list<int>;
using BSTSequence = std::vector<NodeSequence>;

void permutated_combine(NodeSequence left, NodeSequence right, NodeSequence prefix, BSTSequence& result)
{
  if(left.empty())
  {
    prefix.insert(prefix.end(), right.begin(), right.end());
    result.push_back(prefix);
    return;
  }

  if(right.empty())
  {
    prefix.insert(prefix.end(), left.begin(), left.end());
    result.push_back(prefix);
    return;
  }

  prefix.push_back(*left.begin());
  left.pop_front();
  permutated_combine(left, right, prefix, result);

  left.push_front(*prefix.rbegin());
  prefix.pop_back();

  prefix.push_back(*right.begin());
  right.pop_front();
  permutated_combine(left, right, prefix, result);
}

BSTSequence getBSTSequence(TreeNodePtr root)
{
  if(root == nullptr)
    return BSTSequence({ {} });

  auto leftBSTSequence = getBSTSequence(root->left);
  auto rightBSTSequence = getBSTSequence(root->right);

  BSTSequence result;
  for(const auto& l : leftBSTSequence)
    for(const auto& r : rightBSTSequence)
    {
      NodeSequence prefix;
      permutated_combine(l, r, prefix, result);
    }
 
  for(auto& s : result)
    s.push_front(root->value);

  return result;
}

void print_result(const BSTSequence& r)
{
  std::cout << "r.size = " << r.size() << std::endl;
  std::for_each(r.begin(), r.end(), [](const NodeSequence& x) 
  { 
    std::for_each(x.begin(), x.end(), [](const int v) { std::cout << v << " "; });
    std::cout << std::endl;
  });
  std::cout << std::endl;
}

TEST_CASE("bst sequence", "[ch4.9]")
{
  TreeNodePtr root(new TreeNode(10));
  REQUIRE(getBSTSequence(root) == BSTSequence({ 
    { 10 }
  }));

  root->left.reset(new TreeNode(5));
  REQUIRE(getBSTSequence(root) == BSTSequence({ 
    { 10, 5 }
  }));

  root->left->left.reset(new TreeNode(2));
  REQUIRE(getBSTSequence(root) == BSTSequence({ 
    { 10, 5, 2 }
  }));

  root->right.reset(new TreeNode(15));
  REQUIRE(getBSTSequence(root) == BSTSequence({ 
    { 10, 5, 2, 15 },
    { 10, 5, 15, 2 },
    { 10, 15, 5, 2 }
  }));

  root->left->right.reset(new TreeNode(8));
  REQUIRE(getBSTSequence(root) == BSTSequence({ 
    { 10, 5, 2, 8, 15 },
    { 10, 5, 2, 15, 8 },
    { 10, 5, 15, 2, 8 },
    { 10, 15, 5, 2, 8 },
    { 10, 5, 8, 2, 15 },
    { 10, 5, 8, 15, 2 },
    { 10, 5, 15, 8, 2 },
    { 10, 15, 5, 8, 2 },
  }));

  root->right->left.reset(new TreeNode(12));
  REQUIRE(getBSTSequence(root) == BSTSequence({ 
    { 10, 5, 2, 8, 15, 12 },
    { 10, 5, 2, 15, 8, 12 },
    { 10, 5, 2, 15, 12, 8 },
    { 10, 5, 15, 2, 8, 12 },
    { 10, 5, 15, 2, 12, 8 },
    { 10, 5, 15, 12, 2, 8 },
    { 10, 15, 5, 2, 8, 12 },
    { 10, 15, 5, 2, 12, 8 },
    { 10, 15, 5, 12, 2, 8 },
    { 10, 15, 12, 5, 2, 8 },

    { 10, 5, 8, 2, 15, 12 },
    { 10, 5, 8, 15, 2, 12 },
    { 10, 5, 8, 15, 12, 2 },
    { 10, 5, 15, 8, 2, 12 },
    { 10, 5, 15, 8, 12, 2 },
    { 10, 5, 15, 12, 8, 2 },
    { 10, 15, 5, 8, 2, 12 },
    { 10, 15, 5, 8, 12, 2 },
    { 10, 15, 5, 12, 8, 2 },
    { 10, 15, 12, 5, 8, 2 }
  }));
}
