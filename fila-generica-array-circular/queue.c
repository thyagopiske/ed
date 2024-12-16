#include "queue.h"
#include "stdlib.h"

struct Queue{
  int max_capacity;
  void **data;
  int size;

  //fila implementada como array circular
  int i_begin;
  int i_end;
};

Queue *queue_constructor(int max_capacity) {
  Queue *q = (Queue *) malloc(sizeof(Queue));
  q->data = (void **) calloc(max_capacity, sizeof(void *));
  q->max_capacity = max_capacity;
  q->size=0;
  q->i_begin=0;
  q->i_end=0;

  return q;
}

void queue_add(Queue *queue, void *data) {
  queue->data[queue->i_end] = data;
  queue->i_end = (queue->i_end+1)%queue->max_capacity;
  queue->size = queue->size+1;
}

void* queue_remove(Queue *queue) {
  void *item = queue->data[queue->i_begin];
  queue->i_begin = (queue->i_begin+1)%queue->max_capacity;
  queue->size = queue->size-1;

  return item;
}

int queue_size(Queue *queue) {
  return queue->size;
}

int queue_is_full(Queue *queue) {
  return queue->size == queue->max_capacity;
}

int queue_is_empty(Queue *queue) {
  return queue->size == 0;
}

void queue_destroy(Queue *queue) {
  for(int i=0; i<queue->size; i++) {
    int indice_array_circular = (queue->i_begin+i)%queue->max_capacity;
    free(queue->data[indice_array_circular]);
  }

  free(queue->data);
  free(queue);
}
