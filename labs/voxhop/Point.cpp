#include "Point.h"

  bool Point::operator<(const Point& other) const {
    if (x != other.x) {
       return x > other.x;
    }
    if (y != other.y)  {
      return y > other.y;
    }
    return z > other.z;
  }
  bool Point::operator>(const Point& other) const {
    if (x != other.x) {
       return x < other.x;
    }
    if (y != other.y)  {
      return y < other.y;
    }
    return z < other.z;   
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