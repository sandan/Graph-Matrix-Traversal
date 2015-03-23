#include <limits.h>

struct priority_queue pq;


void adj_lvl_labeling(vertex source, int Graph[N][N]){
 source.label=0;
 insert(&pq, source);
 while(pq->heap.size!=0){
   vertex* v=extract_min(&pq);

   if (v->unvisited){

     int row=vertex->id;
     for (int neighbor=0; neighbor<N; neighbor++){
       if (Graph[row][neighbor]!=0){
         nodes[neighbor].unvisited=1;
         if (nodes[neighbor].label>vertex->label+1){
           nodes[neighbor].label=vertex->label+1;
           Enqueue(&pq,&nodes[neighbor]);
       }
     }
   }
   }
 }
}

void initialize(vertex V[N]){

 for (int i =0; i < N; i++){
  V[i].unvisited = true;
  V[i].label = INT_MAX;
  pq_insert(&pq, V[i]);
 }
}
