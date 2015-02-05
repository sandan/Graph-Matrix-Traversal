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

struct PQueue {
    int size;
    int keys[N*3];
    node *head;
    node *tail;
};

struct PQueue nodeQueue;

/*Priority Queue*/
void swap(struct PQueue* Q, int i, int j)
{
        int temp = Q->keys[i];
        Q->keys[i] = Q->keys[j];
        Q->keys[j] = temp;
}

int extractmin(struct PQueue* Q) {
        int i,c;
        int t = Q->keys[1];
        Q->keys[1]=Q->keys[Q->size--];
        for(i=1;(c=2*i)<=Q->size;i=c)
        {
                if( ( c + 1 <= Q->size ) && ( Q->keys[c+1] < Q->keys[c] ) ) {
                        c++;
                }
                if( Q->keys[i] <= Q->keys[c] ) {
                        break;
                }
                swap(Q,c,i);
        }
        return t;
}

void insert(struct PQueue* Q, int key) {
        int i,p;
        Q->size++;
        Q->keys[Q->size] = key;
        for(i = Q->size;( i > 1) && (Q->keys[p=i/2] > Q->keys[i]); i=p)
        {
                swap(Q,p,i);
        }
}
//append the next node to the end of the line
void Enqueue(struct PQueue *q, struct node *vertex) {
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
struct node* Dequeue(struct PQueue *q) {
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
 insert(&nodeQueue,source.label);
 while(nodeQueue.size!=0){
   struct node* vertex=Dequeue(&nodeQueue);
   int label=extractmin(&nodeQueue);
   int row=vertex->id,neighbor;
   for (neighbor=0;neighbor<N;neighbor++){
     if (G[row][neighbor]!=0){
       nodes[neighbor].visited=1;
       if (nodes[neighbor].label>vertex->label+label){
         nodes[neighbor].label=vertex->label+label;
         Enqueue(&nodeQueue,&nodes[neighbor]);
         insert(&nodeQueue,nodes[neighbor].label);
       }
     }
   }
 }
}


/* allocate space for RING,HALF, and nodes array for the queue */
struct node nodes[N]; //N is set at compile time
int RING[N][N]; //adjacency matrix representation of ring graph

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

int main(){
 doRING();
return 0;
}



