#include "stdio.h"
#include "string.h"
#include "deque.h"
#include "stdlib.h"

int main() {
  int N;
  scanf("%d", &N);
  Deque *d = deque_construct();

  for(int i=0; i<N; i++) {
    char str[64];
    char command[64];
    int number;
    scanf("\n%[^\n]s\n", str);
    sscanf(str, "%s %d", command, &number);
    if(strcmp(command, "PUSH_BACK")==0) {
      deque_push_back(d, number);
    }

    if(strcmp(command, "PUSH_FRONT")==0) {
      deque_push_front(d, number);
    }

    if(strcmp(command, "POP_BACK")==0) {
      int item = deque_pop_back(d);
      printf("%d\n", item);
    }

    if(strcmp(command, "POP_FRONT")==0) {
      int item = deque_pop_front(d);
      printf("%d\n", item);
    }

    if(strcmp(command, "GET")==0) {
      int item = deque_get(d, number);
      printf("%d\n", item);
    }
  }

  deque_destroy(d);

  return 0;
}