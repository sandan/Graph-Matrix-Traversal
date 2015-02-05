# Graph-Matrix-Traversal
sparse/

Results L1 data cache misses:
Adjacency Matrix 4096x4096 sparse matrix of zero and ones
Ring:253
Half-connected:1919
The results were taken for flush size of 32 KB before performing the level labeling.
Results L1 data cache misses:
Compressed Row Storage Matrix 4096x4096 sparse matrix of zero and ones
Ring:108
Half-connected:116

The results show that using the compressed row storage representation gave less L1
cache data misses. The results were almost a 20 fold savings for larger matrices with sparse
entries. The compressed row storage works by only keeping one array of non-zero elements
in the matrix. Since the matrix is sparse, the savings can be significant since most non-zero
entries will be contiguous in memory. The data structure uses a row array to locate the
elements in the data array that are the start of the row of that matrix. using a column array
that stores the column index of that element in the data array, we can index using the row
array (that holds the offset into the data array to start iterating over) each non-zero element
in the data array. The major assumption was that there were no zero rows (rows with no
non-zero entries). There would have to be additional safeguards and or data structures to
recognize which rows were non-zero.

dense/

Implements Djikstra SSSP BFS level labeling over sparse matrices with CRS representation and dense matrices with a priority queue data structure

A Breadth First single source shortest path (SSSP) algorithm was implemented
to investigate the performance of different graphs having varying edge density.
The algorithm ws implemented with a Piority Queue that had an ExtractMin operation
that effciently extracts the minimum node with the smallest label value (O(log(|V |)) prioroty
queue operations). This improves the performance of the algorithm asymptotically to
O(|E|log(|V|)), especially for graphs with less vertices. Using a simple queue, we the running
time is O(|V||E|) since there are |V | − 1 iterations at most in the loop and choosing the
next node label that has the smallest label in the nodes not considered (and thus decrease
the labels of the other nodes), is O(|E|) since you have to check all the edges for each node
in the queue so far.
The experiments were done similarly for the previous assignment using different edge
density edges. Both use a matrix data representation for the graph and only differ in the
kind of queue used, The number of nodes in each matrix is N = 4096. The matrices are
sparse 0-1 matrices. These results were chosen experimentally to see the overall algorithmic
behavior between the two implementations

The results were obtained using the PAPI L1 data cache miss counter. The results show
that using a priority does help when graphs are more dense rather than sparsely connected.
For sparsely connected graphs, the overhead of inserting into a priority queue and extracting
the data it stores leads to more cache misses which decreases performance when the graphs
become large but very sparse.
