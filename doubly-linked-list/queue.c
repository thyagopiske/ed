#include "queue.h"
#include "list.h"
#include "stdlib.h"

struct Queue 
{
  List *list;
};

Queue *queue_construct()
{
  Queue *q = malloc(sizeof(Queue));
  q->list = list_construct();

  return q;
}

void queue_push(Queue *q, data_type item)
{
  list_push_back(q->list, item);
}

data_type queue_pop(Queue *q)
{
  return list_pop_front(q->list);
}

void queue_destroy(Queue *q)
{
  list_destroy(q->list);
  free(q);
}