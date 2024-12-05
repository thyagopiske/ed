// #include "queue.h"
// #include "stdio.h"
// #include "string.h"
// #include "stdlib.h"

// int main() {

//   Queue *q = queue_construct();

//   int n;
//   scanf("%d", &n);
//   for (int i = 0; i < n; i++) {
//     char str[64];
//     char cmd[64];
//     char name[64];

//     scanf("\n%[^\n]s", str);
//     sscanf(str, "%s %s", cmd, name);
    
//     if (!strcmp(cmd, "ENQUEUE")) {
//       enqueue(q, strdup(name));
//     }

//     if(!strcmp(cmd, "DEQUEUE")) {
//       char *val = (char *) dequeue(q);
//       printf("%s\n", val);
//       free(val);
//     }
//   }

//   queue_destroy(q);

//   return 0;
// }