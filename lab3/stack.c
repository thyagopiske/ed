#include "vector.h"
#include "stack.h"
#include "stdlib.h"

struct stack {
  Vector *v;
};

Stack *stack_construct() {
  Stack *s = (Stack *) malloc(sizeof(Stack));
  s->v = vector_construct();

  return s;
}

void stack_destroy(Stack *s) {
  for(int i = 0; i < stack_size(s); i++) {
    free(s->v->data[i]);
  }

  vector_destroy(s->v);
  free(s);
}

int stack_size(Stack *s) {
  return vector_size(s->v);
}

void push(Stack *s, void *val) {
  vector_push_back(s->v, val);
}

void *pop(Stack *s) {
  return vector_pop_back(s->v);
}