# VoxHop Write-Up

## World Map Representation

The world map is stored as a 3D `std::vector` of booleans, where each boolean value represents if a voxel is full (`1`) or empty (`0`). Initially, the dimensions of the map are extracted from the input stream, allowing for the initialization of the 3D vector to the correct size.

The process of populating the grid involves converting hexadecimal data from the `.vox` file into binary representation. This conversion is executed using a switch statement that iterates through each character in the input stream, converting it to its corresponding hexadecimal value. Each hex value is then translated into a binary representation and used to populate the respective voxel in the 3D vector.

Once the grid population is complete, the adjacency matrix is constructed to represent the connectivity between voxels. This adjacency matrix is implemented as an `std::unordered_map`, where key represents a voxel, mapping to a set of walkable neighboring voxels. This step ensures efficient storage and retrieval of neighbor information, facilitating subsequent pathfinding operations.

## Pathfinding Algorithm (A* Search)

### Overview

The route queries employ the **A search algorithm**, a pathfinding technique that incorporates heuristics to find the shortest path from a source (src) to a destination (dst). Initially, I implemented **Breadth-First Search (BFS)**, which systematically explores neighboring points until it reaches the destination. To upgrade this to A*, I introduced heuristics, particularly the Manhattan distance, calculated as:

$$|x-x_{0}| + |y-y_{0}| + |z-z_{0}|$$

In the A* implementation, each point retains additional data: the Manhattan distance to both the source and the destination. This allows the algorithm to prioritize exploration based on proximity to both points rather than simply the order of discovery.

### Example

For instance, let's imagine navigating from Theater and Dance West to the San Diego Zoo. In this analogy, pathfinding with BFS is like using a balloon, while A* is akin to employing a metal detector. With BFS (the balloon), you inflate it at Theater and Dance West, and it expands outward, marking every path it encounters until it reaches the San Diego Zoo. While it finds a short path, it also records routes to irrelevant cities to the search like the Fresno Zoo, which are further from the starting point.

In contrast, A* (the metal detector) explores the surrounding area but with a twist: it prioritizes areas where the metal detector beeps louder. So, you move in the direction where the beeps get stronger, eventually reaching the zoo, while not going on unnecessary detours. This approach minimizes unnecessary detours by focusing on paths that lead more directly to the destination. The visual representations below vividly demonstrate the regions explored by each pathfinding algorithm. These illustrations serve to underscore the significant improvement achieved through the incorporation of a basic distance heuristic.

<div style="display: flex; justify-content: center;">
    <div style="margin-right: 10px; text-align: center;">
        <img src="https://i.imgur.com/ZlRlGwa.png" alt="Alt text for Image A" width="300">
        <p>Breadth-first search</p>
    </div>
    <div style="margin-left: 10px; text-align: center;">
        <img src="https://i.imgur.com/XR5TY0G.png" alt="Alt text for Image B" width="300">
        <p>A* search</p>
    </div>
</div>

## Data Structures Used

VoxMap uses several data structures to efficiently represent and manipulate the data.

1. **3D Vector (`std::vector<std::vector<std::vector<bool>>> world;`)** 

2. **Unordered Map (`std::unordered_map<Point, std::unordered_set<Point>>`)**
3. **Priority Queue (`std::priority_queue<Point, std::vector<Point>, std::greater<Point>> q`)**
4. **Unordered Set(`std::unordered_set<Point> visited`)**