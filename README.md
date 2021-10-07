<h1> Pathfinder </h1>

Search of path between two points on a 2-dimensional map.

<h3> 1. Default algorithm v1 </h3>

(Made by Andrew Obukhov)

Just a breadth-first search on a map. To build a reverse route,
during the search previous point is stored in each point.
By doing this, once the algorithm reaches finish point,
the route (if there is one) can be built 
by reversing to the start point.

###2. Default algorithm v2

(made by Ilya Kochetygov)

Breadth-first search on a map as well. 
But instead of storing info about point, 
the distance to the start point is written on each step.
This also allows to build route by reversing, 
but apparently requires less memory and read-write operations.

###3. Fancy algorithms

(made by Yauhenii Sharamed)
