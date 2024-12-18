
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

Deque *deque_construct();
void deque_push_back(Deque *f, int item);
void deque_push_front(Deque *f, int item);
int deque_get(Deque *f, int idx);
int deque_pop_back(Deque *f);
int deque_pop_front(Deque *f);
void deque_destroy(Deque *f);

#endif