#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "heap.h"

typedef struct {
  char nome[32];
  char categoria[32];
  int identificador;
  int prioridade;
} Process;

int cmp_fn_prioridade_processo(void *p1, void *p2) {
  Process *proc1 = (Process *) p1;
  Process *proc2 = (Process *) p2;

  if(proc1->prioridade < proc2->prioridade) return -1;
  if(proc1->prioridade > proc2->prioridade) return 1;

  return 0;
}

int main() {
  int N;
  scanf("%d", &N);

  Heap *h = heap_construct(N, cmp_fn_prioridade_processo);

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

    heap_push(h, p);
  }

  for(int i=0; i<heap_size(h); i++) {
    Process *p = (Process *) heap_get(h, i);
    printf("%s %s %d %d\n", p->nome, p->categoria, p->identificador, p->prioridade);
  }

  for(int i=0; i<heap_size(h); i++) {
    free(heap_get(h, i));
  }

  heap_destroy(h);

  return 0;
}