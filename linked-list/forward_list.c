#include "forward_list.h"
#include "stdlib.h"
#include "stdio.h"

ForwardList *forward_list_construct() 
{
  ForwardList *l = (ForwardList *) malloc(sizeof(ForwardList));
  l->size = 0;
  l->head = NULL;
  // l->last = NULL;

  return l;
} 

int forward_list_size(ForwardList *l)
{
  return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data) 
{
  Node *n = node_construct(data, l->head);
  l->head = n;
  l->size++;

  // if (l->size == 1)
  //   l->last = n;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)) 
{
  // printf("[");
  Node *n = l->head; 
  while(n != NULL)
  {
    print_fn(n->value);
    n = n->next;
    // if(n != NULL) 
    // {
    //   printf(", ");
    // }
  }
  // printf("]");
  
}

data_type forward_list_get(ForwardList *l, int i)
{
  if (i < 0 || i >= l->size)
  {
    printf("Índice inválidod\n");
    exit(1);
  }
  
  Node *node = l->head;
  for (int j = 0; j < i; j++)
  {
    if (j != i)
    {
      node = node->next;
    }
  }
  
  return node->value;
}

data_type forward_list_pop_front(ForwardList *l) 
{
  if (l->head == NULL)
  {
    printf("Lista vazia, não é possível remover elementos\n");
    exit(1);
  }

  
  Node *head = l->head;
  l->head = l->head->next;
  
  data_type head_value = head->value;
  node_destroy(head);

  l->size--;

  // if(l->size <= 1)
  //   l->last = l->head;

  return head_value;

}

ForwardList *forward_list_reverse(ForwardList *l)
{
  ForwardList *m = forward_list_construct();
  Node *node = l->head;
  while(node != NULL)
  {
    forward_list_push_front(m, node->value);
    node = node->next;
  }
  
  return m;
}

void forward_list_clear(ForwardList *l)
{
  int n_itens = l->size;

  //não usar l->size aqui pq ela muda de acordo com a remoção dos elementos
  for (int i = 0; i < n_itens; i++)
  {
    forward_list_pop_front(l);
  }
  
}

void forward_list_remove(ForwardList *l, data_type val)
{
  Node *node = l->head;
  Node *prev = NULL;
  while(node != NULL) 
  {
    if (node->value == val)
    {
      if (prev == NULL)
      {
        l->head = node->next;
        free(node);
        node = l->head;
      }
      else
      {
        prev->next = node->next;
        free(node);  
        node = prev->next;
      }
    } 
    else
    {
      prev = node;
      node = node->next;
    }
  }
}

// void forward_list_unique(ForwardList *l)
// {

// }

void forward_list_cat(ForwardList *l, ForwardList *m)
{
  Node *node = m->head;
  while(node != NULL)
  {
    forward_list_push_front(l, node->value);
    node = node->next;
  }
}

// void forward_list_sort(ForwardList *l)
// {

// }

void forward_list_destroy(ForwardList *l)
{
  Node *n = l->head;
  while(n != NULL)
  {
    Node *next = n->next;
    node_destroy(n);
    n = next; 
  }

  free(l);
}

// void forward_list_push_back(ForwardList *l, data_type data)
// {
  // Node *node = node_construct(data, NULL);
  // if(l->size == 0)
  // {
  //   l->head = node;
  //   l->last = node;
  // } 
  // else
  // {
  //   l->last->next = node;
  //   l->last = node;
  // }

//   l->size++;
// }

data_type forward_list_pop_index(ForwardList *l, int index)
{
  if(index < 0 || index >= l->size || l->size == 0)
  {
    printf("INVALID INDEX\n");
    return NULL;
  }

  Node *node = l->head;
  Node *prev = NULL;
  for (int i = 0;  i < index; i++)
  {
    prev = node;
    node = node->next;
  }

  if(prev == NULL)
  {
    l->head = node->next;
  } 
  else 
  {
    prev->next = node->next;
  }

  data_type val = node->value;
  node_destroy(node);
  l->size--;
  
  return val;
}

// ListIterator *list_iterator_construct(ForwardList *l)
// {
//   ListIterator *it = (ListIterator *) malloc(sizeof(ListIterator));
//   it->current = l->head;

//   return it;
// }

// void list_iterator_destroy(ListIterator *it)
// {
//   free(it);
// }

// data_type* list_iterator_next(ListIterator *it)
// {
//   data_type * val= &(it->current->value);
//   it->current = it->current->next;

//   return val;
// }

// bool list_iterator_is_over(ListIterator *it)
// {
//   return it->current == NULL;
// }

