#ifndef _PQHEAP_H_
#define _PQHEAP_H_

#include <stdint.h>
#include <stdio.h>

#define N 100

typedef struct {
 int size;
 int heap[N+1]; //a 1-indexed array of ints
}heap;


/** Index to elements in heap **/
int parent(int i);
int rchild(int i);
int lchild(int i);

/** Maintains min heap invariant **/
void min_heapify(heap *H, int i);
void pq_swap(int *a, int *b);
void build_min_heap(heap *H);
void heapsort(heap *H, int result[]);
void decrease_key(heap* H, int i, int new);
#endif
