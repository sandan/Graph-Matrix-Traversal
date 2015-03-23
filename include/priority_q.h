#ifndef _PRIORITY_Q_H_
#define _PRIORITY_Q_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"
#include "pq_heap.h"

//the heap based priority queue 
typedef struct{
  heap* H; //heap H
} pq;

#endif
