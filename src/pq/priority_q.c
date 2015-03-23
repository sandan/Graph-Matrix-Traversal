#include <stdlib.h>
#include "../../headers/priority_q.h"
#include <limits.h>

//int based priority queue based on min heap
void pq_insert(pq *priority_q, int x){
  priority_q->H->size+=1;
  priority_q->H->heap[priority_q->H->size]=INT_MAX;
  decrease_key(priority_q->H,priority_q->H->size,x);
}

int get_min(pq* priority_q){
 return priority_q->H->heap[1]; //1 idxed array
}

int extract_min(pq* priority_q){
 if (priority_q->H->size < 1) abort(); //no elements to return

 int result = get_min(priority_q);

 //replace top with a leaf
 priority_q->H->heap[1] = priority_q->H->heap[priority_q->H->size];
 priority_q->H->size-=1;
 min_heapify(priority_q->H, 1);
 return result;
}
