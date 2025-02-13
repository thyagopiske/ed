
#include "node.h"

#ifndef _STACK_H_
#define _STACK_H_

typedef struct Stack Stack;

Stack *stack_construct();
void stack_push(Stack *s, data_type item);
data_type stack_pop(Stack *s);
void stack_destroy(Stack *s);

#endif