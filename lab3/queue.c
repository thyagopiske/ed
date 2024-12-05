#include "vector.h"
#include "queue.h"
#include "stdlib.h"
#include "string.h"

struct queue {
  Vector *v;  
};

Queue *queue_construct() {
  Queue *q = (Queue *) malloc(sizeof(Queue));
  q->v = vector_construct();

  return q;
}

void queue_destroy(Queue *q) {
  for(int i = 0; i < queue_size(q); i++) {
    free(q->v->data[i]);
  }

  vector_destroy(q->v);
  free(q);
}

void enqueue(Queue *q, void *val) {
  vector_push_back(q->v, val);
}

const void *dequeue(Queue *q) {
  return vector_pop_front(q->v);
}

int queue_size(Queue *q) {
  return vector_size(q->v);
}