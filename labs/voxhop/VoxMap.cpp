#include "VoxMap.h"
#include "Errors.h"

VoxMap::VoxMap(std::istream& stream) {
  if (!(stream >> width >> depth >> height)) {
    std::cerr << "ERROR: invalid map dimensions\n";
    return;
  }
  for (int i = 0; i < height; i++) {
    std::string line;
    std::getline(stream, line); //ignore the blank line
    std::getline(stream, line);

    for (int j = 0; j < depth; j++) {
      for (int k = 0; k < width; k++) {
        world[k][j][i] = true;
      } 
    }
  }
}

VoxMap::~VoxMap() {

}

Route VoxMap::route(Point src, Point dst) {
  throw NoRoute(src, dst);
}
