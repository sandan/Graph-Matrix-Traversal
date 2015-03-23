#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <assert.h>
#include <papi.h>
#include "../../include/priority_q.h"

struct pq priorty_queue;

/* allocate space for RING,HALF, and vertices array for the queue */
vertex vertices[N]; //N is set at compile time
int HALF[N][N];       //adj matrix rep of half-connected graph

void adj_lvl_labeling(struct vertex source, int G[N][N]){
 source.label=0;
 insert(&vertexQueue,source.label);
 while(vertexQueue.size!=0){
   struct vertex* vertex=Dequeue(&nodeQueue);
   int label=extractmin(&vertexQueue);
   int row=vertex->id,neighbor;
   for (neighbor=0;neighbor<N;neighbor++){
     if (G[row][neighbor]!=0){
       vertices[neighbor].visited=1;
       if (vertices[neighbor].label>vertex->label+label){
         vertices[neighbor].label=vertex->label+label;
         Enqueue(&vertexQueue,&vertices[neighbor]);
         insert(&vertexQueue,vertices[neighbor].label);
       }
     }
   }
 }
}

/* zero out FLUSH_SIZE bytes in memory*/
int flush(){
char* mem=(char*)malloc(FLUSH_SIZE);
  assert(mem!=NULL);
  int i;
  for(i=0; i<(FLUSH_SIZE); i++){
   *(mem+i)=0;
  }
return 0;
}

void setup(){
 srand(time(NULL));
 int i;
 /*initialize the vertices array to access vertexs*/
 for (i=0; i<N; ++i){
   struct vertex v;
   v.id=i;
   vertices[i]=v;
 }
  /*create the HALF graph*/
 int j,row;
 for (i=0; i<N; i++){
  row=vertices[i].id;
  for(j=0; j<N;j++){
   if(rand()%2==1){
    HALF[row][j]=1;
   }
  }
 }
}

void handle_error(int retval){
  printf("PAPI error %d: %s\n",retval,PAPI_strerror(retval));
  exit(1);
}
void doHALF(){

/*event measued: PAPI_L1_DCM*/
int retval, EventSet=PAPI_NULL;
long_long values[1];

/* initialize the PAPI library */
retval = PAPI_library_init(PAPI_VER_CURRENT);
if (retval != PAPI_VER_CURRENT) {
  fprintf(stderr, "PAPI library init error!\n");
  exit(1);
}

/* create Event Set */
if (PAPI_create_eventset(&EventSet) != PAPI_OK)
        handle_error(1);

/* add Total Instructions Executed to our Event Set */
if (PAPI_add_event(EventSet, PAPI_L1_DCM) != PAPI_OK)
        handle_error(1);

/* initialize the Graphs*/
setup();

/*flush the cache 32Kb*/
flush();

/* start counting events in the Event Set */
if (PAPI_start(EventSet) != PAPI_OK)
        handle_error(1);

/* BFS level labeling */
adj_lvl_labeling(vertices[0],HALF);

/* stop counting in the Event Set */
if (PAPI_stop(EventSet, values) != PAPI_OK)
        handle_error(1);

/*report the result*/
printf("%lld\n",values[0]);

}

int main(){
 doHALF();
return 0;
}



