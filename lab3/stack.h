#ifndef STACK
#define STACK

typedef struct stack Stack;

Stack *stack_construct();
void stack_destroy(Stack *s);
int stack_size(Stack *s);
void push(Stack *s, void *val);
void *pop(Stack *s);

#endif