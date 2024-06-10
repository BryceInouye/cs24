#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <climits>
struct Point {
  int x;
  int y;
  int z;
// A* heuristics: where...
  int g; // distance from start
  int h; // distance to goal
  int f; // f = g + h (total cost)

  Point() : g(INT_MAX), h(INT_MAX), f(INT_MAX) {}
  Point(int x, int y, int z): x(x), y(y), z(z), g(INT_MAX), h(INT_MAX), f(INT_MAX) {}
  bool operator<(const Point& other) const;
  bool operator>(const Point& other) const;
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const; 
};

std::istream& operator >> (std::istream& stream, Point& point);
std::ostream& operator << (std::ostream& stream, const Point& point);

#endif
