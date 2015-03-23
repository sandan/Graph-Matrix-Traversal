#include <stdlib.h>
#include "../../include/pq_heap.h"

int parent(int i){
 return i >> 1;
}

int rchild(int i){
 return i << 1; 
}

int lchild(int i){
 return rchild(i) + 1;
}

void pq_swap (int* a, int* b){
 int temp = *a;
 *a=*b;
 *b=temp;
}

heap *make_heap(int *elems, int n){
 heap* H=(heap*)(malloc(sizeof(heap)));
 H->size=n;
 for (int i =0 ; i <n; i++){
  H->heap[i]=*(elems+i);
 }
 return H;
}
//takes a heap pointer and an index into the heap array i
//swaps elements in the array so min heap property is preserved
void min_heapify(heap *H, int i){
 int l_index=lchild(i);
 int r_index=rchild(i);
 int smallest = i;

 if (H->heap[i] > H->heap[l_index] && l_index <= H->size){
  smallest = l_index;

 }else if (H->heap[smallest] > H->heap[r_index] && r_index <= H->size){
  smallest = r_index;

 }

 if (smallest != i){
  pq_swap((H->heap)+i, (H->heap)+smallest);
  min_heapify(H,smallest);
 }
}

//assumes the new value of key is at least as big as current key
void decrease_key(heap* H, int i, int new){

 if (new >= H->heap[i]) printf("error: new key is bigger than current key\n");

 H->heap[i]=new; //decrease the current value of heap[i]
 while (i > 1 && H->heap[parent(i)] > H->heap[i]){
  pq_swap((H->heap)+i, (H->heap)+parent(i));
  i=parent(i);
 }
}
void build_min_heap(heap* H){
//access the internal nodes stored in heap, just above the leaves
 for(int i=(H->size/2); i>=1; i--){
  min_heapify(H,i);
 }
}

//can also do with extract min with pq
void heapsort(heap *H, int result[]){
 //get a min heap
 build_min_heap(H);
 for (int i=H->size; i >=2; i--){
   pq_swap(H->heap+1, H->heap+i); //swap the top of heap with a leaf
   H->size-=1;

   result[i]=H->heap[1]; //save into result

   min_heapify(H,1);
 }
}
