#include "node.h"

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue Queue;

Queue *queue_construct();
void queue_push(Queue *q, data_type item);
data_type queue_pop(Queue *q);
void queue_destroy(Queue *q);

#endif