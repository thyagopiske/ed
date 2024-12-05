#ifndef QUEUE
#define QUEUE

typedef struct queue Queue;

Queue *queue_construct();
void queue_destroy(Queue *q);
void enqueue(Queue *q, void *val);
const void *dequeue(Queue *q);
int queue_size(Queue *q);

#endif