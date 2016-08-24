#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <string>

void Usage()
{
  std::cout << "Usage: ./a.out <filename> <uid1> <uid2> [x threshold] [y threshold]" << std::endl;
}

class Position
{
  public:
    Position(double x, double y) : _x(x), _y(y)
    {
    }

    double X() const { return _x; }
    double Y() const { return _y; }

    bool Match(const Position& other, const Position& threshold) const
    {
      return std::fabs(_x - other.X()) < threshold.X() && std::fabs(_y - other.Y()) < threshold.Y();
    }

  private:
    const double _x;
    const double _y;
};

typedef std::pair<std::string, std::string> Key;
typedef std::map<Key, Position> TimeLocationMap;

void Tokenize(const std::string& s, std::vector<std::string>& v, const std::string& delim)
{
  int start = 0;
  auto pos = s.find_first_of(delim, start);
  while(pos != std::string::npos)
  {
    v.push_back(s.substr(start, (pos - start)));
    start = pos + 1;
    pos = s.find_first_of(delim, start);
  }
  if(start < s.length())
    v.push_back(s.substr(start));
}

int main(int argc, char** argv)
{
  if(argc < 4)
  {
    Usage();
    return -1;
  }

  auto fileName = argv[1];
  const std::string uid1(argv[2]);
  const std::string uid2(argv[3]);
  const Position threshold(argc > 4 ? atof(argv[4]) : 10, argc > 5 ? atof(argv[5]) : 10);

  TimeLocationMap uid1Locs, uid2Locs;

  std::string line;
  std::ifstream ifs(fileName);
  if(!ifs.good())
  {
    std::cout << "Failed to open file: " << fileName << std::endl;
    return -1;
  }

  while(std::getline(ifs, line))
  {
    auto lastToken = line.find_last_of(",");
    if(line.find(uid1, lastToken) == std::string::npos && line.find(uid2, lastToken) == std::string::npos)
      continue;

    std::vector<std::string> v;
    Tokenize(line, v, ",");
    if(v.size() != 5)
    {
      std::cout << "Invalid line: " << line << std::endl;
      continue;
    }
    const std::string& uid = v[4];
    const std::string& timestamp = v[0];
    const std::string& floor = v[3];
    if(uid == uid1)
    {
      uid1Locs.insert(std::make_pair(Key(timestamp, floor), Position(atof(v[1].c_str()), atof(v[2].c_str()))));
    }
    else if(uid == uid2)
    {
      uid2Locs.insert(std::make_pair(Key(timestamp, floor), Position(atof(v[1].c_str()), atof(v[2].c_str()))));
    }
  }

  const TimeLocationMap& smaller = uid1Locs.size() < uid2Locs.size() ? uid1Locs : uid2Locs;
  const TimeLocationMap& larger = uid1Locs.size() < uid2Locs.size() ? uid2Locs : uid1Locs;

  for(const auto& s : smaller)
  {
    auto it = larger.find(s.first);
    if(it == larger.end())
      continue;

    if(s.second.Match(it->second, threshold))
    {
      std::cout << "Match found @ " << s.first.first << " - " << s.first.second << std::endl;
    }
  }
  return 0;
}
