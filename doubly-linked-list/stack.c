#include "stack.h"
#include "list.h"
#include "stdlib.h"

struct Stack
{
  List *list;
};

Stack *stack_construct()
{
  Stack *s = malloc(sizeof(Stack));
  s->list = list_construct();

  return s;
}

void stack_push(Stack *s, data_type item)
{
  list_push_back(s->list, item);
}

data_type stack_pop(Stack *s)
{
  return list_pop_back(s->list);
}

void stack_destroy(Stack *s)
{
  list_destroy(s->list);
  free(s);
}