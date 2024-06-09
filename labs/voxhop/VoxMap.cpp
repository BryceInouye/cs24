#include "VoxMap.h"
#include "Errors.h"
#include <iostream>

std::string hexCharToBinary(char hexChar) {
    switch (hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a': return "1010";
        case 'b': return "1011";
        case 'c': return "1100";
        case 'd': return "1101";
        case 'e': return "1110";
        case 'f': return "1111";
        default: throw std::invalid_argument("Invalid hexadecimal character");
    }
}

VoxMap::VoxMap(std::istream& stream) {
    stream >> width >> depth >> height; // Assume the map dimensions are valid
    world.resize(width, std::vector<std::vector<bool>>(depth, std::vector<bool>(height, false)));

    std::string line;
    std::getline(stream, line); // Ignore the blank line after reading map dimensions

    for (int i = 0; i < height; i++) {
        std::getline(stream, line);
        for (int j = 0; j < depth; ++j) {
            std::getline(stream, line);
            // Remove carriage return if it exists
            if (!line.empty() && line[line.length()-1] == '\r') {
                line.erase(line.length() - 1);
            }
            // std::cout << "LINE ROW:" << j << std::endl;
            // std::cout << line << "\n";
            // std::cout << "line length: " << line.length() << "\n\n";
            for (size_t k = 0; k < line.length(); k++) {
                // std::cout << "hex at line[" << k <<"]: " << line[k] << '\n';
                std::string hex_string = hexCharToBinary(line[k]);
                for (int m = 0; m < 4; m++) {
                    world[4*k + m][j][i] = hex_string[m] - '0';
                }
            }
        }
    }
    
// loop to print the grid for reference

//     std::cout << "GRID HERE:";
//   for (int i = 0; i < height; i++) {
//     std::cout << "height: " << i << "\n";
//     for (int j = 0; j < depth; j++) {
//       std::cout << "depth: " << j << ":";
//       for (int k = 0; k < width; k++) {
//         std::cout << world[k][j][i];
//       }
//       std::cout << "\n";
//     }
//   }
       
  
  for (int i = 1; i < height; i++) { // (i,j,k) = (z,y,x)
    for (int j = 0; j < depth; j++) {
      for (int k = 0; k < width; k++) {
        Point parent = Point(k, j, i); // Parent->(Child)
        // std::cout << "parent being tested: " << parent << " VALUE:" << world[parent.x][parent.y][parent.z] << "\n";
        if (can_stand(parent)) {
          Point north_neighbor = parent;
          std::unordered_set<Point> valid_neighbors;
          north_neighbor.y--;
          north_neighbor.z = 1; // set to 1 since neighbor can be on the groun
          if (north_neighbor.y >= 0) {
            while ((parent.z + 1) >= north_neighbor.z) {
              if (neighbor_valid(parent, north_neighbor)) {
                valid_neighbors.insert(north_neighbor);
                break;
              }
              north_neighbor.z++;
            }
          }
          Point south_neighbor = parent;
          south_neighbor.y++;
          south_neighbor.z = 1;
          if (south_neighbor.y < depth) {
            while ((parent.z + 1) >= south_neighbor.z) { // fix loop later to avoid doing same computation twice
                if (neighbor_valid(parent, south_neighbor)) {
                  valid_neighbors.insert(south_neighbor);
                  break;
                }
              south_neighbor.z++;
            }
          }

          Point east_neighbor = parent;
          east_neighbor.x++;
          east_neighbor.z = 1;
          if (east_neighbor.x < width) {
            while ((parent.z + 1) >= east_neighbor.z) {
            if (neighbor_valid(parent, east_neighbor)) {
              valid_neighbors.insert(east_neighbor);
              break;
            }
            east_neighbor.z++;
            }
          }

          Point west_neighbor = parent;
          west_neighbor.x--;
          west_neighbor.z = 1;
          if (west_neighbor.x >= 0) {
            while ((parent.z + 1) >= west_neighbor.z) {
            if (neighbor_valid(parent, west_neighbor)) {
              valid_neighbors.insert(west_neighbor);
              break;
            }
            west_neighbor.z++;
            }
          }
            // std::cout << "parent: " << parent << std::endl;
            // std::cout << "children: ";
            // for (Point n : valid_neighbors) {
            //     std::cout << n;
            // }
            // std::cout << "\n";
          vgraph[parent] = valid_neighbors;
        }
      }
    }
  }
}

VoxMap::~VoxMap() {
    // everything gets allocated and deallocated automatically. maybe change later
}

bool VoxMap::is_valid(Point& point) { // voxel exists in the grid
  if (point.x < 0 || point.x >= width || point.y < 0 || point.y >= depth || point.z < 1 || point.z >= height) { // The voxel must be within the map bounds.
    return false;
  }

  return true;
}

bool VoxMap::can_stand(Point& point) {
  if (!is_valid(point)) {
    return false;
  }

  if (world[point.x][point.y][point.z]) { // The voxel must be empty.
//   std::cout << "     FAIL AT:" << point << std::endl;
    return false;
  }

  if (point.z < 1) {
// std::cout << "     FAIL AT:" << point << std::endl;
    return false;
  }

  if (world[point.x][point.y][point.z-1]) {
    return true; // The voxel must have a full voxel directly below it.
  }
  Point temp = point;
  temp.z--;
  //std::cout << "     FAIL AT:" << point << ", VALUE:" << world[point.x][point.y][point.z] << ". BELOW:"<< temp << "VALUE:" << world[temp.x][temp.y][temp.z] << std::endl;
  return false;
}
bool VoxMap::neighbor_valid(Point& point, Point& neighbor) {
  if (!can_stand(point) || !can_stand(neighbor)) {
    return false;
  }

  if (fabs(point.x - neighbor.x) > 1 || fabs(point.y - neighbor.y) > 1) {
    return false;
  }

  // point.z = neighbor.z (Flat Move)
  if (point.z == neighbor.z) {
    return true;
  }
  Point temp;
  // point.z < neighbor.z (Jump Up)
  if (neighbor.z - point.z == 1) {
    temp = point;
    temp.z++;
    if (world[temp.x][temp.y][temp.z]) {
      return false;
    }
    return true;
  }
  // point.z > neighbor.z (Fall Down)
  if (point.z > neighbor.z) {
    temp = neighbor;
    temp.z = point.z;
    while (temp.z > neighbor.z) {
      if (world[temp.x][temp.y][temp.z]) {
        return false;
      }
      temp.z--;
    }
    return true;
  }

  return false;
}

Move VoxMap::get_move(Point& parent, Point& child) {
  int horizontal_vector = child.x - parent.x;
  int vertical_vector = child.y - parent.y;

  if (horizontal_vector == 0 && vertical_vector == 1) {
    return Move::SOUTH;
  } else if (horizontal_vector == 0 && vertical_vector == -1) {
    return Move::NORTH;
  } else if (horizontal_vector == 1 && vertical_vector == 0) {
    return Move::EAST;
  } else if (horizontal_vector == -1 && vertical_vector == 0) {
    return Move::WEST;
  } else {
    throw std::invalid_argument("get_move error");
  }
}
// 1. Dequeue a point from the queue, call it 'current'
// 2. Mark 'current' as visited
// 3. If 'current' is the destination point 'dst', then:
//    3.1. Initialize an empty list for the path
//    3.2. While 'current' is not the source point 'src':
//          3.2.1. Add 'current' to the beginning of the path
//          3.2.2. Move to the parent of 'current' by looking it up in the 'path' map
//    3.3. Add 'src' to the beginning of the path
//    3.4. Return the path as the route from 'src' to 'dst'
// 4. For each point 'neighbor' that is a neighbor of 'current':
//    4.1. If 'neighbor' has not been visited and can be stood on:
//          4.1.1. Add 'neighbor' to the queue
//          4.1.2. Add a mapping from 'neighbor' to 'current' in the 'path' map
// 5. If the queue is empty, throw NoRoute(src, dst) to indicate that no route was found

Route VoxMap::route(Point src, Point dst) {
  if (!can_stand(src)) {
    throw InvalidPoint(src);
  } else if (!can_stand(dst)) {
    throw InvalidPoint(dst);
  }

  std::unordered_map<Point, Point> path; // to reconstruct the path, 
                                         // where child maps to parent
                                         // and every child has only 1 parent
  std::unordered_set<Point> visited; // set of visited nodes to prevent infinite loops
  std::queue<Point> q; // set of nodes to visit, no heuristics yet
  std::unordered_set<Point> waiting; // set of nodes added to the queue
  q.push(src);
  while (!q.empty()) {
    // std::cout << "Outer loop, queue size: " << q.size() << std::endl;
    Point current = q.front(); // 1.
    visited.insert(current); // 2.
    q.pop();

    if (current == dst) { // 3. found the destination 
      Route route;
      while (current != src) {
        //   std::cout << "current: " << current << "; src: " << src << "\n";
        route.insert(route.begin(), get_move(path[current], current));
        current = path[current]; // if A->B, then path[B] = A
        // std::cout << "new current: " << current << "\n";
      }
      // std::cout << "Route from " << src << " to " << dst << ": "; // show route coordinates for reference
      return route; 
    }

    for (Point neighbor : vgraph[current]) { // 4.
    //   std::cout << "  Inner loop, neighbor: " << neighbor << std::endl;
      if (visited.find(neighbor) == visited.end() && can_stand(neighbor) 
          && waiting.find(neighbor) == waiting.end()) {
        q.push(neighbor);
        waiting.insert(neighbor);
        path[neighbor] = current; // child -> parent : path[current] = current parent
      }
    }
  }
  throw NoRoute(src, dst); // 5.
}

