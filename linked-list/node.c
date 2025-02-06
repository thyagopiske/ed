#include "node.h"
#include "stdlib.h"

Node *node_construct(data_type value, Node *next)
{
  Node *n = (Node *) malloc(sizeof(Node));
  n->value = value;
  n->next = next;

  return n;
}

data_type node_value(Node *node) 
{
  return node->value;
}

Node *node_next(Node *node) 
{
  return node->next;
}

void node_destroy(Node *n)
{
  free(n);
}
