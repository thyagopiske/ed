#include "stdlib.h"
#include "heap.h"
#include "vector.h"

struct Heap {
  Vector *v;
  int (*cmp_fn)(const void *, const void *);
};

Heap *heap_constructor(int (*cmp_fn)(const void *, const void *)) {
  Heap *h = (Heap *) malloc(sizeof(Heap));
  h->v = vector_construct();
  h->cmp_fn = cmp_fn;

  return h;
}

void heap_push(Heap *heap, void *data) {
  vector_push_back(heap->v, data);

  int i = vector_size(heap->v) - 1;
  int i_parent = (i-1)/2; 
  while(i_parent >= 0 && heap->cmp_fn(vector_get(heap->v, i_parent), vector_get(heap->v, i)) < 0) {
    vector_swap(heap->v, i_parent, i);
    i = i_parent;
    i_parent = (i-1)/2; 
  }
}

int heap_size(Heap *heap) {
  return vector_size(heap->v);
}

void *heap_pop(Heap *heap) {
  vector_swap(heap->v, 0, vector_size(heap->v)-1);
  void *val = vector_pop_back(heap->v);

  int i_parent = 0;
  int i_max = i_parent;
  int i_left_child = 2*i_max+1;
  int i_right_child = 2*i_max +2;

  if(i_left_child < vector_size(heap->v) && heap->cmp_fn(vector_get(heap->v, i_left_child), vector_get(heap->v, i_max)) > 0)
    i_max = i_left_child;

  if(i_right_child < vector_size(heap->v) && heap->cmp_fn(vector_get(heap->v, i_right_child), vector_get(heap->v, i_max)) > 0)
    i_max = i_right_child;

  while(i_parent < vector_size(heap->v)/2 && i_max != i_parent) {
    vector_swap(heap->v, i_parent, i_max);

    i_parent = i_max;
    i_max = i_parent;
    i_left_child = 2*i_max+1;
    i_right_child = 2*i_max +2;

    if(i_left_child < vector_size(heap->v) && heap->cmp_fn(vector_get(heap->v, i_left_child), vector_get(heap->v, i_max)) > 0)
      i_max = i_left_child;

    if(i_right_child < vector_size(heap->v) && heap->cmp_fn(vector_get(heap->v, i_right_child), vector_get(heap->v, i_max)) > 0)
      i_max = i_right_child;
  }

  return val;
}

void heap_destroy(Heap *heap) {
  vector_destroy(heap->v);
  free(heap);
}