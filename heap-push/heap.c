#include "heap.h"
#include "stdlib.h"

struct heap {
  void **arr;
  int size;
  int capacity;
  int (*cmp_fn)(void *, void *);
};

Heap *heap_construct(int capacity, int (*cmp_fn)(void *, void *)) {
  Heap *h = (Heap *) malloc(sizeof(Heap));
  h->arr = (void **) calloc(capacity, sizeof(void *));
  h->size = 0;
  h->capacity = capacity;
  h->cmp_fn = cmp_fn;

  return h;
}

int heap_size(Heap *h) {
  return h->size;
}

void heap_push(Heap *h, void *val) {
  h->arr[h->size] = val;
  heapify_up(h, h->size);
  h->size = h->size + 1;
}

void heapify_up(Heap *h, int i) {
  int i_parent = (i-1)/2;

  if(i_parent >= 0 && h->cmp_fn(h->arr[i_parent], h->arr[i]) == -1) {
    void *tmp = h->arr[i_parent];
    h->arr[i_parent] = h->arr[i];
    h->arr[i] = tmp;

    heapify_up(h, i_parent);
  } 
}

void *heap_get(Heap *h, int i) {
  return h->arr[i];
}

void heap_destroy(Heap *h) {
  free(h->arr);
  free(h);
}