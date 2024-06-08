#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "Point.h"
#include "Route.h"
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return p.x * 73856093 ^ p.y * 19349663 ^ p.z * 83492791;
        }
    };
}
class VoxMap {
  // Member Variables
  public:
    int width; // (x) west to east, increasing x means going east
    int depth; // (y) north to south, increasing y means going south
    int height; // (z) up and down
    std::vector<std::vector<std::vector<bool>>> world;
    std::unordered_map<Point, std::unordered_set<Point>> vgraph;

  // Helper Functions


public:
  VoxMap(std::istream& stream);
  ~VoxMap();

  //helper functions
  bool is_valid(Point& point);
  bool can_stand(Point& point);
  bool neighbor_valid(Point& point, Point& neighbor);
  Move get_move(Point& parent, Point& child);
  // int getDistance(Point p1, Point p2) const; // use later for heuristics. main idea is to get program working

  Route route(Point src, Point dst);
};

#endif
