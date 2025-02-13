#include "deque.h"
#include "list.h"
#include "stdlib.h"

struct Deque
{
  List *list;
};

Deque *deque_construct()
{
  Deque *f = malloc(sizeof(Deque));
  f->list = list_construct();

  return f;
}

void deque_push_back(Deque *f, int item)
{
  list_push_back(f->list, item);
}

void deque_push_front(Deque *f, int item)
{
  list_push_front(f->list, item);
}

int deque_pop_back(Deque *f)
{
  return list_pop_back(f->list);
}

int deque_pop_front(Deque *f)
{
  return list_pop_front(f->list);
}

void deque_destroy(Deque *f)
{
  list_destroy(f->list);
  free(f);
}