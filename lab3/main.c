#include "stdio.h"
#include "stack.h"
#include "string.h"
#include "stdlib.h"

int main() {
  Stack *s = stack_construct();

  int n;
  scanf("%d", &n);

  for(int i=0; i<n; i++) {
    char str[64];
    char cmd[64];
    char name[64];

    scanf("\n%[^\n]s", str);
    sscanf(str, "%s %s", cmd, name);

    if(!strcmp(cmd, "PUSH")) {
      //strdup usa malloc, então o resultado tem q ser desalocado
      push(s, strdup(name));
    }

    if(!strcmp(cmd, "POP")) {
      char *val = pop(s);
      printf("%s\n", val);
      free(val);
    }
  }

  stack_destroy(s);

  return 0;
}