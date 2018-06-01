#include <map>
#include <vector>
#include <list>
#include <set>
#include "../../test_framework/catch.hpp"

using Graph = std::map<int, std::vector<int>>;
bool route_exists(const Graph& graph, const int n1, const int n2)
{
  std::set<int> visited;
  std::list<int> q;
  q.push_back(n1);
  while(!q.empty())
  {
    auto n = *q.begin();
    q.pop_front();

    auto v = visited.insert(n);
    if(!v.second)
      continue;

    auto it = graph.find(n);
    if(it != graph.end())
    {
      if(n == n2)
        return true;
      for(auto i : it->second)
        q.push_back(i);
    }
  }
  return false;
}

TEST_CASE("route between nodes", "[ch4.1]")
{
  std::map<int, std::vector<int>> graph;
  graph[0] = { 1, 2, 3 };
  graph[1] = { 2, 4, 5, 9 };
  graph[2] = { 1, 0, 5, 6,};
  graph[3] = { };
  graph[4] = { 5, 6 };
  graph[5] = { 6 };
  graph[6] = { 1, 2, 3 };
  graph[8] = { 1 };
  graph[9] = { 3 };
  graph[11] = { 9 };

  REQUIRE(route_exists(graph, 3, 3) == true);
  REQUIRE(route_exists(graph, 3, 4) == false);
  REQUIRE(route_exists(graph, 7, 7) == false);
  REQUIRE(route_exists(graph, 0, 6) == true);
  REQUIRE(route_exists(graph, 5, 0) == true);
  REQUIRE(route_exists(graph, 6, 0) == true);
  REQUIRE(route_exists(graph, 4, 0) == true);
  REQUIRE(route_exists(graph, 4, 2) == true);
  REQUIRE(route_exists(graph, 4, 3) == true);
  REQUIRE(route_exists(graph, 1, 0) == true);
  REQUIRE(route_exists(graph, 6, 4) == true);
  REQUIRE(route_exists(graph, 8, 0) == true);
  REQUIRE(route_exists(graph, 9, 3) == true);
  REQUIRE(route_exists(graph, 9, 0) == false);
  REQUIRE(route_exists(graph, 9, 11) == false);
  REQUIRE(route_exists(graph, 11, 9) == true);
  REQUIRE(route_exists(graph, 11, 0) == false);
  REQUIRE(route_exists(graph, 6, 11) == false);
}
