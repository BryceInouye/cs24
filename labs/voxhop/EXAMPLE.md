# VoxHop Write-Up
***Table of Contents***

[World Map Representation](#World-Map-Representation)

[Pathfinding Algorithm (A* Search)](#Pathfinding-Algorithm-(A*-Search))

[Data Structures Used](#Data-Structures-Used)

[Big-O Runtime and Big-O Space](#Big-O-Runtime-and-Big-O-Space)

## World Map Representation

The world map is stored as a 3D `std::vector`, which is covered in more detail in the [Data Structures Used](#Data-Structures-Used) section. Initially, the dimensions of the map are extracted from the input stream, allowing for the initialization of the 3D vector to the correct size.

The process of populating the grid involves converting hexadecimal data from the `.vox` file into binary representation. This conversion is executed using a switch statement that iterates through each character in the input stream, converting it to its corresponding hexadecimal value. Each hex value is then translated into a binary representation and used to populate the respective voxel in the 3D vector.

Once the grid population is complete, the adjacency matrix is constructed to represent the connectivity between voxels. This adjacency matrix is implemented as an `std::unordered_map`, where key represents a voxel, mapping to a set of walkable neighboring voxels. This step ensures efficient storage and retrieval of neighbor information, facilitating subsequent pathfinding operations.

## Pathfinding Algorithm (A* Search)

### Overview

The route queries employ the **A search algorithm**, a pathfinding technique that incorporates heuristics to find the shortest path from a source (src) to a destination (dst). Initially, I implemented **Breadth-First Search (BFS)**, which systematically explores neighboring points until it reaches the destination. To upgrade this to A*, I introduced heuristics, particularly the Manhattan distance, calculated as:

$$|x-x_{0}| + |y-y_{0}| + |z-z_{0}|$$

In the A* implementation, each point retains additional data: the Manhattan distance to both the source and the destination. This allows the algorithm to prioritize exploration based on proximity to both points rather than simply the order of discovery.

### Example

For instance, let's imagine navigating from Theater and Dance West to the San Diego Zoo. In this analogy, pathfinding with BFS is like using a balloon, while A* is akin to employing a metal detector. With BFS (the balloon), you inflate it at Theater and Dance West, and it expands outward, marking every path it encounters until it reaches the San Diego Zoo. While it finds a short path, it also records routes to irrelevant places to the search like the Fresno Zoo, which are remote from both the start and target.

In contrast, A* (the metal detector) explores the surrounding area but with a twist: it prioritizes areas where the metal detector beeps louder. So, you move in the direction where the beeps get stronger, eventually reaching the zoo, while not going on unnecessary detours. This approach minimizes unnecessary detours by focusing on paths that lead more directly to the destination. Additionally, the Manhattan values for a point's neighboring points are updated if the path leading to it is shorter, resulting in more optimal paths. The visual representations below demonstrate the regions explored by each pathfinding algorithm. These illustrations serve to underscore the significant improvement achieved through the incorporation of a basic distance heuristic.

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

1. **3D Vector (`std::vector<std::vector<std::vector<bool>>> world;`)**: A vector is used to represent the world map.
Because each point has an (x,y,z) value, a 3D vector is the most straightforward way to represent the 3D space as a matrix of booleans, where each boolean value represents if a voxel is full (`1`) or empty (`0`). Alternatively, a 3D
array could have been used since it can perform operations slightly faster, but the safety and flexibility of the vector
outweighs the benefits of an array in my opinion. 
2. **Unordered Map (`std::unordered_map<Point, std::unordered_set<Point>> vgraph`)**:  Unordered maps were chosen to represent the adjacency list and facilitate path construction due to their efficiency in storing key-value pairs. In our scenario, the order of data insertion is irrelevant, making unordered maps provide faster performance compared to ordered maps. This speed advantage is crucial for the route queries, as it ensures quick retrieval of neighboring points during pathfinding.
     * ***Adjacency List(`std::unordered_map<Point, std::unordered_set<Point>> vgraph`)*** - This maps a Point to a set of valid neighboring nodes. A neighbor is valid if the entity can access it from the key point. An alternate data structure could be an adjacency matrix, which could be more space-efficient for dense graphs but would take up a lot of extra data to show how one point can map to every other point in the map.
     * ***Path Reconstruction(`std::unordered_map<Point, Point> path`)*** - The unordered map is also used to reconstruct
     the path from the target to the destination. Its key-value pair is child-parent, since each child point can only have
     at most one parent, whereas each parent can have at most 4 children. The child-parent not only makes implementation simpler, but can be a little confusing since you then need to backtrack in order to get to the start, which involves adding a step, then adding the previous step before so the path reverses from finish-to-start to start-to-finish.
3. **Priority Queue (`std::priority_queue<Point, std::vector<Point>, std::greater<Point>> q`)**: This data structure is used to implement a min-heap, which sorts elements from the least value to the greatest value. Points are compared using their `f` value, which is the sum of the Manhattan distances between the point and the target and the point and the source. A priority queue ensures that the point with the lowest `f` value is explored first, enhancing efficiency compared to a queue's first-in-first-out approach used in a BFS, which is less optimized for pathfinding. An alternate data structure could be a sorted vector, but it would require manual insertion and sorting operations, leading to higher time complexity for insertion and removal of elements.
4. **Unordered Set(`std::unordered_set<Point> visited`)**: Unordered sets were useful for several aspects of the code. They are chosen because they allow constant-time insertion and lookup operations, which are crucial for this program's pathfinding performance. An alternate data structure could be a binary search tree, but it would have higher time complexity for insertion and deletion operations, particularly in scenarios with frequent modifications to the set. Here is a brief overview of the ways unordered sets were used.
     * ***Neighbors (`std::unordered_set<Point> valid_neighbors`)*** - This set holds all of a point's valid neighbors. When performing a search, the target point could be any direction from the starting point, making the order of the points irrelevant. However, if all points started from a constant area and destinations were in the opposite direction, an ordered structure might improve performance.
     * ***Visited (`std::unordered_set<Point> visited`)*** - This set is crucial when adding nodes during a search. The quick lookup allows a point to efficiently check to see if a point should be added to the priority queue based on whether or not it has been visited, preventing the pathfinder to run in endless circles.
     * ***Waiting (`std::unordered_set<Point> waiting`)*** - Waiting might seem redundant, but is crucial for the program to work. It essentially holds the same values as `std::priority_queue<Point, std::vector<Point>, std::greater<Point>> q`, but allows for constant time point checks. They work together to form this relationship, where the queue sorts the points, and the set checks that the point is not waiting. The waiting set prevents duplicates from entering the waiting queue since a point can have multiple paths leading to it. 

## Big-O Runtime and Big-O Space

1. VoxMap Constructor
     * ***Initializing the 3D Vector*** - Resizing the vector requires iterating through each element in the 3D grid. Since there are no restrictions to what grid points are added, the Big-O runtime here is simply the product of the Width, Depth, and Height of the map.
        * Time Complexity - O(Width * Depth * Height)
        * Space Complexity - O(Width * Depth * Height) 
     * ***Converting stream to Populate Grid***
        * Time Complexity: O(Width * Depth * Height) - Converting the stream to binary is done in constant time and involves iterating through every element in the 3D matrix to represent a filled or empty voxel.
        * Space Complexity: O(Width * Depth * Height) - No new memory is allocated.
     * ***Building Adjacency List***
        * Time Complexity: O(Width * Depth * Height * Height * 4) - For each voxel, every cardinal direction could be a potential neighbor. So `neighbors` is a value from 0-4, so we can get rid of it from the big-O notation. For a standable voxel, a point is mapped to a set of walkable neighbors. Since neighbor checking checks all of the spaces below the current height, in the worst case, the time complexity is multiplied by height again. 
        * Space Complexity: O(Width * Depth * Height * 4) - Vgraph maps each voxel to a set of valid neighbors. This means in the worst case, this can result in storing multiple neighbors for each voxel. 
     * ***Constructor Big-O Runtime and Big-O Space***: 
        * _Time Complexity_: The dominant term is from the adjacency list construction so the time complexity for the constructor: $$O(Width * Depth * Height^{2})$$
        * _Space Complexity_: Resizing, grid initialization, and adjacency list construction each have a space complexity of `O(Width * Depth * Height)`. Adding them, we get `O(3(Width * Depth * Height))`. Dropping the coefficient gives the space complexity for the constructor: $$O(Width * Depth * Height)$$

2. Pathfinding Algorithm (A*)
     
     * ***Time Complexity***: O(Width * Depth * Height * log(Width * Depth * Height) + (Width * Depth * Height * Height)) - The priority queue operations (enqueueing and dequeueing) each take `O(log n)`, and in the worst case, all nodes (voxels) could be processed. This results in a combined complexity of `O(n log n)`, where n is the total number of nodes (voxels). Here, the algorithm is responsible for dequeuing the current point, marking it as visited, checking if it's the destination, processing neighbors, updating distances, and managing the priority queue.
        * Dissecting each piece:
           * `can_stand(Point& point)` -  Series of vector index access operations, so `O(1)`
           * `neighbor_valid(Point& point, Point& neighbor)` - Like `can_stand()`, but with a while loop in the case where neighbor elevation is lower than a point's elevation. Thus in the worst case, the time complexity is `O(Height)`. In the worst case where every point is checked, this results in time complextiy `O(Width * Depth * Height * Height)
           * `get_move(Point& parent, Point& child)` - In the worst, case where the input throws an `invalid_argument` error, 4 checks need to fail. This simplifies to `O(1)` time complexity.
           * `manhattan_distance(const Point A, const Point B) const` - One arithmetic calculation so `O(1)`.
     * ***Pathfinder Algorithm Big-O Time Compelxity***: Big-(O) time complexity drops the lowest terms and coefficients, yielding the following: $$O(Width * Depth * Height^{2})$$ 
     * ***Space Complexity***: O(W * D * H) - The priority queue, visited set, waiting set, and path map collectively can hold all nodes in the worst case. This results in a space complexity of `O(4n)`, where `n` is the total number of voxels.
        * The `route()` helper functions do not affect the memory to lead to a substantial increase in space complexity.
     * ***Pathfinder ALgorithm Big-O Space Complexity***: Dropping the coefficients, this gives us the following: $$O(n)$$

     * ***Overall Big-O Runtime and Big-O Space***:
        * _Time Complexity_: First we take the dominant term between the pathfinding algorithm and the map parser. Since they are equal: $$(2 * Width * Depth * Height^{2})$$ This is not the final answer. Because the main program takes `n` queries, this is the overall time complexity: $$O(n * Width * Depth * Height^{2})$$
        * _Space Complexity_: Note that the number of queries does not affect the amount of memory used. Taking the dominant term gives us the following space complexity: $$O(Width * Depth * Height)$$