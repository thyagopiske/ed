#include "priority_queue_vector.h"
#include "vector.h"
#include "stdlib.h"

struct PriorityQueue {
  Vector *v;
  int (*cmp_fn)(const void *, const void *);
};

PriorityQueue *pq_constructor(int cmp_fn(const void *, const void *)) {
  PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
  pq->v = vector_construct();
  pq->cmp_fn = cmp_fn;

  return pq;
}

void pq_push(PriorityQueue *pq, void *data) {
  vector_push_back(pq->v, data);
}

void *pq_pop(PriorityQueue *pq) {
  int i = vector_argmax(pq->v, pq->cmp_fn);
  void *v = (void *)vector_remove(pq->v, i);

  return v;
}

int pq_size(PriorityQueue *pq) {
  return pq->v->size;
}

void pq_destroy(PriorityQueue *pq) {
  vector_destroy(pq->v);
  free(pq);
}
