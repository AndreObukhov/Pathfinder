<h1> Pathfinder </h1>

Search of path between two points on a 2-dimensional map.

<h3> 1. Default algorithm v1 </h3>

(Made by Andrew Obukhov)

Just a breadth-first search on a map. To build a reverse route,
during the search previous point is stored in each point.
By doing this, once the algorithm reaches finish point,
the route (if there is one) can be built 
by reversing to the start point.

<h3> 2. Default algorithm v1.1 </h3>

(Made by Andrew Obukhov)

Just a breadth-first search on a map. To build a reverse route,
during the search distance from start is stored in each point.
By doing this, once the algorithm reaches finish point,
the route (if there is one) can be built
by reversing - always going to the point with less distance.

This fix was inspired by the next algorithm...:

<h3> 3. Default algorithm v2 </h3>

(made by Ilya Kochetygov)

Breadth-first search on a map as well. 
But instead of storing info about point, 
the distance to the start point is written on each step.
This also allows to build route by reversing, 
but apparently requires less memory and read-write operations.

<h3> 4. Fancy algorithms </h3>

(made by Yauhenii Sharamed)

A-star algorithm on the map of points. 
There is a priority queue of points that algorithm 
has to visit. By adding priority, algorithm tends to
visit points that are more likely to be the shortest path
first.
Reverse map is built just like in default algorithm v1 - 
by saving coordinates of points from previous step.

<h3> Results </h3>

![alt text](https://github.com/AndreObukhov/Pathfinder/blob/main/reports/performance_graph.png?raw=true)
