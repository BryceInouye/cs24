#include "Point.h"

  bool Point::operator<(const Point& other) const {  // logic works for a min heap
    // ties broken in the following order: f, g, h
    if (f != other.f) {
      return f < other.f;
    }
    if (g != other.g) {
      return g < other.g;
    }
    return h < other.h;
  }
  bool Point::operator>(const Point& other) const {
    if (f != other.f) {
      return f > other.f;
    }
    if (g != other.g) {
      return g > other.g;
    }
    return h > other.h;
  }
  bool Point::operator==(const Point& other) const {
    if (x != other.x) {
       return false;
    }
    if (y != other.y)  {
      return false;
    }
    return z == other.z;
  }
  bool Point::operator!=(const Point& other) const {
    if (x != other.x) {
       return true;
    }
    if (y != other.y)  {
      return true;
    }
    return z != other.z;
  
  }

std::istream& operator >> (std::istream& stream, Point& point) {
  return stream >> point.x >> point.y >> point.z;
}

std::ostream& operator << (std::ostream& stream, const Point& point) {
  return stream << '(' << point.x << ", " << point.y << ", " << point.z << ')';
}