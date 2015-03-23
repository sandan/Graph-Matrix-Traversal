#include <limits.h>
#include "../include/priority_q.h"

void adj_lvl_labeling(vertex V[N], priority_queue* pq, vertex source, int Graph[N][N]){

 source.unvisited = false;
 source.label = 0;
 pq_insert(pq,source);

 while(pq->heap.size!=0){
   vertex* v=extract_min(pq);

   if (v->unvisited){
     int row=v->id;
     for (int neighbor=0; neighbor<N; neighbor++){
       //assumes a matrix of nonnegative weights
       if (Graph[row][neighbor]!=0){
         V[neighbor].unvisited=false;
         if (nodes[neighbor].label>vertex->label+Graph[row][neighbor]){
           V[neighbor].label=vertex->label+Graph[row][neighbor];
           pq_insert(pq,V[neighbor]);
      }
     }
    }
   }
 }
}

void dijkstra(priority_queue* pq, vertex V[N], Graph[N][N]){
 //initialize vertices
 for (int i = 1; i < N; i++){
  V[i].unvisited = true;
  V[i].label = INT_MAX;
 }
 //the vertex to start the algorithm with
 adj_lvl_labeling(V,pq,V[0],Graph);

 //make sure we visit all connected graphs
 for (int i = 0; i < N; i++){
   if (V[i].unvisited){
    adj_lvl_labeling(V,pq,V[i],G);
   }
 }
}
