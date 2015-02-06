Graph-Matrix-Traversal
=======================
* sparse/ contains code for optimizing graoh traversal over sparse graphs with CRS representation
* dense/ contains code for optimzing graph traversal over dense graphs using a priority queue

Both implement a graph traversal algorithm (Dijkstra SSSP BFS) over a matrix representation of the graph. The Performance API [(PAPI)] (http://icl.cs.utk.edu/papi/) is used to record data from hardware counters.
