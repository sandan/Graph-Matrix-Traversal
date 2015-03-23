
To run the executable for the number of L1 data cache misses.
Requires the Performance API

To Compile:
./compile


####Results L1 data cache misses:
* The results were taken for flush size of 32 KB before performing the level labeling.

* Adjacency Matrix 4096x4096 sparse matrix of zero and ones
 * Ring:253 misses
 * Half-connected:1919 misses

* Compressed Row Storage Matrix 4096x4096 sparse matrix of zero and ones
 * Ring:108 misses
 * Half-connected:116 misses

These results show that using the compressed row storage representation gave less L1
cache data misses. The results were almost a 20 fold savings for larger matrices with sparse
entries. 
