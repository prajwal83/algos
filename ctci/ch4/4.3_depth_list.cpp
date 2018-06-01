#include <vector>
#include <list>
#include "../../test_framework/catch.hpp"
#include "common.h"

using NodeList = std::list<TreeNodePtr>;
using DepthValues = std::list<int>;
using DepthList = std::vector<DepthValues>;

void depthList(NodeList bq, DepthList& v)
{
  if(bq.empty())
    return;

  v.push_back(DepthValues());
  NodeList cbq;
  for(auto i : bq)
  {
    v.rbegin()->push_back(i->value);
    if(i->left != nullptr) cbq.push_back(i->left);
    if(i->right != nullptr) cbq.push_back(i->right);
  }
  depthList(cbq, v);
}

TEST_CASE("tree depth linked list 1", "[ch4.3]")
{
  TreeNodePtr r(new TreeNode(10));
  NodeList q { r };
  DepthList v;
  depthList(q, v);
  REQUIRE(v.size() == 1);
  REQUIRE(v[0] == DepthValues({ 10 }));

  r->left.reset(new TreeNode(20));
  v.clear();
  depthList(q, v);
  REQUIRE(v.size() == 2);
  REQUIRE(v[0] == DepthValues({ 10 }));
  REQUIRE(v[1] == DepthValues({ 20 }));

  r->right.reset(new TreeNode(30));
  v.clear();
  depthList(q, v);
  REQUIRE(v.size() == 2);
  REQUIRE(v[0] == DepthValues({ 10 }));
  REQUIRE(v[1] == DepthValues({ 20, 30 }));

  r->left->right.reset(new TreeNode(40));
  r->right->left.reset(new TreeNode(50));
  r->right->left->left.reset(new TreeNode(60));
  r->right->left->right.reset(new TreeNode(70));
  v.clear();
  depthList(q, v);
  REQUIRE(v.size() == 4);
  REQUIRE(v[0] == DepthValues({ 10 }));
  REQUIRE(v[1] == DepthValues({ 20, 30 }));
  REQUIRE(v[2] == DepthValues({ 40, 50 }));
  REQUIRE(v[3] == DepthValues({ 60, 70 }));
}
