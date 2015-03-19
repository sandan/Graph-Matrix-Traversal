To compile:
./compile

Graph Traversal was implemented with a piority queue that had an ExtractMin operation
that effciently extracts the minimum node with the smallest label value (O(log(|V|))). 

This improves the performance of the algorithm asymptotically to
O(|E| + |V|log(|V|)).

 * SSSP using PQ Cycle Graph:
  *27363 L1 Data cache Misses

* SSSP using PQ Half Connected Graph :
  *1766 L1 Data cache Misses

* SSSP using Q Cycle Graph:
  *302 L1 Data Cache Misses

* SSSP using Q Half Connected Graph:
  *1892 L1 Data Cache Misses



The results were obtained using the PAPI L1 data cache miss counter. The results show
that using a priority does help when graphs are more dense rather than sparsely connected.
For sparsely connected graphs, the overhead of inserting into a priority queue and extracting
the data it stores leads to more cache misses which decreases performance when the graphs
become large but very sparse.
