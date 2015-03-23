#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <assert.h>
#include <papi.h>

typedef struct node{
 int label;
 int visited;
 int id;
 struct node* next;
}node;

struct Queue {
    int size;
    node *head;
    node *tail;
};

struct Queue nodeQueue;

//append the next node to the end of the line
void Enqueue(struct Queue *q, struct node *vertex) {
    q->size+=1;
    struct node *oldTail = q->tail;
    vertex->next = 0;
    q->tail = vertex;
    if (oldTail == 0) {
        q->head = vertex;
    } else {
        oldTail->next = vertex;
    }
}
//dequeue the head node of the line
struct node* Dequeue(struct Queue *q) {
    struct node* vertex = q->head;
    if (vertex != 0) {
        q->size-=1;
        q->head = vertex->next;
        if (q->head == 0) {
            q->tail = 0;
        }
    }
    return vertex;
}

/* allocate space for RING,HALF, and nodes array for the queue */
struct node nodes[N]; //N is set at compile time
int RING[N][N]; //adjacency matrix representation of ring graph
int HALF[N][N]; //adj matrix rep of half-connected graph

void adj_lvl_labeling(struct node source, int G[N][N]){
 source.label=0;
 Enqueue(&nodeQueue,&source);
 while(nodeQueue.size!=0){
   struct node* vertex=Dequeue(&nodeQueue);
   if (!(vertex->visited)){
   int row=vertex->id,neighbor;
   for (neighbor=0;neighbor<N;neighbor++){
     if (G[row][neighbor]!=0){
       nodes[neighbor].visited=1;
       if (nodes[neighbor].label>vertex->label+1){
         nodes[neighbor].label=vertex->label+1;
         Enqueue(&nodeQueue,&nodes[neighbor]);
       }
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
 /*initialize the nodes array to access nodes*/
 for (i=0; i<N; ++i){
   struct node v;
   v.id=i;
   nodes[i]=v;
 }
 /*create the RING graph*/
 int row;
 for (i=0; i<N-1; i++){
  row=nodes[i].id;
  RING[row][row+1]=1;
 }
 row=nodes[i+1].id;
 RING[row][0]=1; 

  /*create the HALF graph*/
 int j;
 for (i=0; i<N; i++){
  row=nodes[i].id;
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

void doRING(){

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
adj_lvl_labeling(nodes[0],RING);

/* stop counting in the Event Set */
if (PAPI_stop(EventSet, values) != PAPI_OK)
        handle_error(1);

/*report the result*/
printf("%lld\n",values[0]);

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
adj_lvl_labeling(nodes[0],HALF);

/* stop counting in the Event Set */
if (PAPI_stop(EventSet, values) != PAPI_OK)
        handle_error(1);

/*report the result*/
printf("%lld\n",values[0]);

}

int main(){
 //doRING();
 doHALF();
return 0;
}



