#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <assert.h>
#include <papi.h>

vertex vertices[N]; //N is set at compile time
int HALF[N][N]; //adj matrix rep of half-connected graph

void crs_lvl_labeling(struct node source, int* data, int* col, int* row, int size){
 source.label=0;
 Enqueue(&nodeQueue,&source);
 while(nodeQueue.size!=0){
   struct node* vertex=Dequeue(&nodeQueue);
   if (!(vertex->visited)){
   int offset=row[vertex->id];//start of first row
   int previous=-1;
   for (;offset<size;offset++){
       nodes[offset].visited=1;
       if (col[offset]<=previous){
        break; //finished with this row
       }
       
       if (nodes[offset].label>vertex->label+1){
         nodes[offset].label=vertex->label+1;
         Enqueue(&nodeQueue,&nodes[offset]);

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
   v.label = INT_MAX;
   v.unvisited = true; 
   v.id=i;
   nodes[i]=v;
 }
  /*create the HALF graph*/
 int j;
 for (i=0; i<N; i++){
  row=nodes[i].id;
  for(j=0; j<N;j++){
   if(rand()%2==1){
    HALF[row][j]=1; //complicate
   }
  }
 }
 
}

void handle_error(int retval){
  printf("PAPI error %d: %s\n",retval,PAPI_strerror(retval));
  exit(1);
}

int main(){
  int valcol,nzfirstrow,i,j,k;
  
    for (i=0; i<N; i++){
     for(j=0; j<N; j++){
      if (HALF[i][j]!=0){
        valcol++;
      }
     }
    }
   int* val=malloc(sizeof(int)*valcol);
   int* col=malloc(sizeof(int)*valcol);
   int tmp=0;
  
    for (i=0; i<N; i++){
     for(j=0; j<N; j++){
      if (HALF[i][j]!=0){
        val[tmp]=HALF[i][j];
        col[tmp]=j;tmp++;
      }
     }
    }
  
    for (i=0; i<N; i++){
     for(j=0; j<N; j++){
      if(HALF[i][j]!=0){
         nzfirstrow++;
      }
     }
    }
    
    int* row=malloc(sizeof(int)*nzfirstrow);
  
    for (i=0; i<N; i++){
     for(j=0; j<N; j++){
      if(HALF[i][j]!=0){
        if (val[k]==HALF[i][j] && col[j]==j){
          row[k]=k;k++;
          break;
        }
       }
      }
     }
  
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
  crs_lvl_labeling(nodes[0],val,col,row,valcol);
  
  /* stop counting in the Event Set */
  if (PAPI_stop(EventSet, values) != PAPI_OK)
          handle_error(1);
  
  /*report the result*/
  printf("%lld\n",values[0]);
  return 0;
  
}
