#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "priority_queue_vector.h"

typedef struct {
  char nome[32];
  char categoria[32];
  int identificador;
  int prioridade;
} Process;

int cmp_fn(const void* v1, const void* v2) {
  Process *p1 = (Process *) v1;
  Process *p2 = (Process *) v2;

  if(p1->prioridade < p2->prioridade) return -1;
  if(p1->prioridade > p2->prioridade) return 1;
  
  return 0;
}

int main() {
  int N;
  scanf("%d", &N);

  PriorityQueue *pq = pq_constructor(cmp_fn);

  for(int i=0; i<N; i++) {
    char nome[32];
    char categoria[32];
    int identificador;
    int prioridade;
    scanf("%s %s %d %d", nome, categoria, &identificador, &prioridade);
    Process *p = (Process *) malloc(sizeof(Process));
    strcpy(p->nome, nome);
    strcpy(p->categoria, categoria);
    p->identificador = identificador;
    p->prioridade = prioridade;

    pq_push(pq, p);  
  }


  while(pq_size(pq)!=0) {
    Process *p = (Process *) pq_pop(pq);
    printf("%s %s %d %d\n", p->nome, p->categoria, p->identificador, p->prioridade);
    free(p);
  }

  pq_destroy(pq);

  return 0;
}