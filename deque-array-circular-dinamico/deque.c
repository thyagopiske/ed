#include "deque.h"
#include "stdlib.h"

typedef int data_type;
struct Deque {
  data_type *arr;
  int size;
  int allocated;
  int i_start;
  int i_end;
};

Deque *deque_construct() {
  Deque *d = (Deque *) malloc(sizeof(Deque));
  int allocated = 10;
  d->arr = (data_type *) calloc(allocated, sizeof(data_type));
  d->size = 0;
  d->allocated = allocated;
  d->i_start = 0;
  d->i_end = 0;

  return d;
}

void deque_push_back(Deque *f, int item) {
  if(f->size == f->allocated) {
    int new_allocated = 2*f->allocated;
    f->arr = (data_type *) realloc(f->arr, new_allocated*sizeof(data_type));
    int num_items_to_be_shifted = f->size - f->i_start;
    int new_start_index = f->i_start + f->allocated;
    for(int i=0; i<num_items_to_be_shifted; i++) {
      f->arr[new_start_index + i] = f->arr[f->i_start + i];
    }
    f->i_start = new_start_index;
    f->allocated = 2*f->allocated;
  }

  f->arr[f->i_end] = item;
  f->i_end = (f->i_end+1)%f->allocated;
  f->size = f->size+1;
}

void deque_push_front(Deque *f, int item) {
  if(f->size == f->allocated) {
    int new_allocated = 2*f->allocated;
    f->arr = (data_type *) realloc(f->arr, new_allocated*sizeof(data_type));
    int num_items_to_be_shifted = f->size - f->i_start;
    int new_start_index = f->i_start + f->allocated;
    for(int i=0; i<num_items_to_be_shifted; i++) {
      f->arr[new_start_index + i] = f->arr[f->i_start + i];
    }
    f->i_start = new_start_index;
    f->allocated = 2*f->allocated;
  }

  f->i_start = (f->i_start-1+f->allocated)%f->allocated;
  f->arr[f->i_start] = item;
  f->size = f->size+1;
}

int deque_pop_back(Deque *f) {
  int i_last_item = (f->i_end-1+f->allocated)%f->allocated;
  data_type item = (data_type) f->arr[i_last_item];
  f->i_end = i_last_item;
  f->size = f->size-1;

  return item;
}

int deque_pop_front(Deque *f) {
  data_type item = (data_type) f->arr[f->i_start];
  f->i_start = (f->i_start+1)%f->allocated;
  f->size = f->size-1;

  return item;
}

int deque_get(Deque *f, int idx) {
  return f->arr[(f->i_start + idx)%f->allocated];
}

void deque_destroy(Deque *f) {
  free(f->arr);
  free(f);
}