#include <set>
#include <list>
#include <vector>
#include <memory>
#include <functional>
#include "../../test_framework/catch.hpp"

class Project;
using ProjectPtr = std::shared_ptr<Project>;

class Project
{
public:
  Project(const std::string name) : _name(name) {}
  void addDependency(ProjectPtr parent)
  {
    _dependsOn.insert(parent);
  }

  void removeDependency(ProjectPtr parent)
  {
    _dependsOn.erase(parent);
  }

  void addChild(ProjectPtr child)
  {
    _children.insert(child);
  }

  int dependencyCount()
  {
    return _dependsOn.size();
  }

  const std::string& Name() const { return _name; }
  const std::set<ProjectPtr> getChildren() const { return _children; }

  void reset()
  {
    _dependsOn.clear();
    _children.clear();
  }

private:
  std::string _name;
  std::set<ProjectPtr> _dependsOn;
  std::set<ProjectPtr> _children;
};

class Graph
{
public:
  Graph(const std::list<ProjectPtr>& projects,  const std::list<std::pair<ProjectPtr, ProjectPtr>>& dependencies)
    : _projects(projects)
  {
    for(auto dependency : dependencies)
    {
      dependency.first->addChild(dependency.second);
      dependency.second->addDependency(dependency.first);
    }
  }

  std::vector<std::string> buildOrder()
  {
    std::vector<std::string> order;
    std::list<ProjectPtr> projs = _projects;
  
    bool completedProjects = false;
    do
    {
      completedProjects = false;
      for(auto it = projs.begin(); it != projs.end();)
      {
        if((*it)->dependencyCount() == 0)
        {
          order.push_back((*it)->Name());
          for(auto c : (*it)->getChildren())
            c->removeDependency(*it);
          projs.erase(it++);
          completedProjects = true;
        }
        else
          ++it;
      }
    } while(completedProjects);

    if(projs.empty())
      return order;
    return std::vector<std::string>();
  }

private:
  std::list<ProjectPtr> _projects;
};

using DEP = std::pair<ProjectPtr, ProjectPtr>;
TEST_CASE("build order", "[ch4.7]")
{
  ProjectPtr a(new Project("a"));
  ProjectPtr b(new Project("b"));
  ProjectPtr c(new Project("c"));
  ProjectPtr d(new Project("d"));
  ProjectPtr e(new Project("e"));
  ProjectPtr f(new Project("f"));
  auto reset = std::mem_fn(&Project::reset);

  std::vector<ProjectPtr> origProjects = { a, b, c, d, e, f };

  Graph g1({ a, b, c, d, e, f }, { DEP(a, d), DEP(f, b), DEP(b, d), DEP(f, a), DEP(d, c) });
  REQUIRE(g1.buildOrder() == std::vector<std::string>({ "e", "f", "a", "b", "d", "c" }));
  std::for_each(origProjects.begin(), origProjects.end(), reset);
  
  Graph g2({ a, b, c, d, e, f }, { DEP(a, d), DEP(f, b), DEP(b, d), DEP(f, a), DEP(d, c), DEP(c, f) });
  REQUIRE(g2.buildOrder() == std::vector<std::string>());
  std::for_each(origProjects.begin(), origProjects.end(), reset);

  Graph g3({ a, b, c, d, e, f }, { DEP(a, d), DEP(f, b), DEP(b, d), DEP(f, a), DEP(d, c), DEP(c, e) });
  REQUIRE(g3.buildOrder() == std::vector<std::string>({ "f", "a", "b", "d", "c", "e" }));
  std::for_each(origProjects.begin(), origProjects.end(), reset);

  Graph g4({ a, b, c, d, e, f }, { });
  REQUIRE(g4.buildOrder() == std::vector<std::string>({ "a", "b", "c", "d", "e", "f" }));
  std::for_each(origProjects.begin(), origProjects.end(), reset);
}
