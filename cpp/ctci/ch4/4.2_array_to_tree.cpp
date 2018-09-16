#include "../../test_framework/catch.hpp"
#include "common.h"

TreeNodePtr createFromArray(const std::vector<int> data)
{
  std::function<TreeNodePtr (int, int)> create;
  create = [&](int start, int end) -> TreeNodePtr {
    if (end < start)
      return nullptr;

    auto mid = (start + end) / 2;
    TreeNodePtr r(new TreeNode(data[mid]));
    r->left = create(start, mid - 1);
    r->right = create(mid + 1, end);
    return r;
  };

  return create(0, data.size() - 1);
}

TEST_CASE("balanced tree from sorted array", "[ch4.2]")
{
  auto r = createFromArray({ 1 });
  REQUIRE(height(r) == 1);
  REQUIRE(inOrder(r) == std::vector<int>({ 1 }));

  r = createFromArray({ 1, 2 });
  REQUIRE(height(r) == 2);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2 }));

  r = createFromArray({ 1, 2, 3 });
  REQUIRE(height(r) == 2);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3 }));

  r = createFromArray({ 1, 2, 3, 4, 5 });
  REQUIRE(height(r) == 3);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5 }));

  r = createFromArray({ 1, 2, 3, 4, 5, 6 });
  REQUIRE(height(r) == 3);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5, 6 }));

  r = createFromArray({ 1, 2, 3, 4, 5, 6, 7 });
  REQUIRE(height(r) == 3);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5, 6, 7 }));

  r = createFromArray({ 1, 2, 3, 4, 5, 6, 7, 8 });
  REQUIRE(height(r) == 4);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8 }));

  r = createFromArray({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 });
  REQUIRE(height(r) == 4);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }));

  r = createFromArray({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
  REQUIRE(height(r) == 4);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }));

  r = createFromArray({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
  REQUIRE(height(r) == 5);
  REQUIRE(inOrder(r) == std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }));
}
