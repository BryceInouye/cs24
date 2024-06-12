# VoxHop Write-Up

## World Map Representation

The world map is stored as a 3D `std::vector` of booleans, where each boolean value represents if a voxel is full (`1`) or empty (`0`). Initially, the dimensions of the map are extracted from the input stream, allowing for the initialization of the 3D vector to the correct size.

The process of populating the grid involves converting hexadecimal data from the `.vox` file into binary representation. This conversion is facilitated by a switch statement that iterates through each character in the input stream, converting it to its corresponding hexadecimal value. Each hex value is then translated into a binary representation and used to populate the respective voxel in the 3D vector.

Once the grid population is complete, the adjacency matrix is constructed to represent the connectivity between voxels. This adjacency matrix is implemented as an `std::unordered_map`, where key represents a voxel, mapping to a set of walkable neighboring voxels. This step ensures efficient storage and retrieval of neighbor information, facilitating subsequent pathfinding operations.
