#include "list.h"
#include "stdlib.h"
#include "stdio.h"

List *list_construct()
{
  List *l = (List *) malloc(sizeof(List));
  l->size = 0;
  l->head = NULL;
  l->last = NULL;

  return l;
}

int list_size(List *l)
{
  return l->size;
}

void list_print(List *l, void (*print_fn)(data_type))
{
  printf("[");
  Node *n = l->head; 
  while(n != NULL)
  {
    print_fn(n->value);
    n = n->next;
    if(n != NULL) 
    {
      printf(", ");
    }
  }
  printf("]");
}

void list_print_reverse(List *l, void (*print_fn)(data_type))
{
  printf("[");
  Node *n = l->last; 
  while(n != NULL)
  {
    print_fn(n->value);
    n = n->prev;
    if(n != NULL) 
    {
      printf(", ");
    }
  }
  printf("]");
}

void list_destroy(List *l)
{
  // Node *n = l->head;
  // while(n != NULL)
  // {
  //   Node *next = n->next;
  //   node_destroy(n);
  //   n = next; 
  // }

  free(l);
}

void list_push_front(List *l, data_type data)
{
  Node *n = node_construct(data, NULL, l->head);
  if (l->head != NULL)
  {
    l->head->prev = n;
  }
  
  l->head = n;
  
  l->size++;

  if (l->size == 1)
    l->last = n;
}

data_type list_pop_front(List *l)
{
  Node *node = l->head;
  data_type val = node->value;
  l->head = node->next;
  l->head->prev = NULL;
  
  free(node);

  l->size--;

  if(l->size <= 1)
    l->last = l->head;

  return val;
}

void list_push_back(List *l, data_type data)
{
  Node *node = node_construct(data, l->last, NULL);
  if (l->last != NULL)
  {
    l->last->next = node;
  }
  
  l->last = node;

  l->size++;

  if(l->size == 1)
    l->head = l->last;
}

data_type list_pop_back(List *l)
{
  if (l->head == NULL)
  {
    printf("Lista vazia\n");
    exit(1);
  }

  Node *node = l->last;
  data_type val = node->value;

  node->prev->next = NULL;
  l->last = node->prev;

  l->size--;

  if(l->size <= 1)
    l->head = l->last;

  return val;
}

ListIterator *list_front_iterator(List *l)
{
  ListIterator *it = malloc(sizeof(ListIterator));
  it->current = l->head;
  
  return it;
}

ListIterator *list_back_iterator(List *l)
{
  ListIterator *it = malloc(sizeof(ListIterator));
  it->current = l->last;
  
  return it;
}

data_type *list_iterator_next(ListIterator *it)
{
  data_type *val = &(it->current->value);
  it->current = it->current->next;

  return val;
}

data_type *list_iterator_previous(ListIterator *it)
{
  data_type *val = &(it->current->value);
  it->current = it->current->prev;

  return val;
}

bool list_iterator_is_over(ListIterator *it)
{
  return it->current == NULL;
}

void list_iterator_destroy(ListIterator *it)
{
  free(it);
}