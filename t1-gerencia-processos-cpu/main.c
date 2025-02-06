#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "heap.h"
#include "deque.h"
#include "vector.h"

typedef struct {
  char nome[64];
  // ProgramType tipo;
  char tipo[5];
  int prioridade;
  int carga;
  int ultimo_uso;
  int iteracao_inicio;
} Program;

// typedef enum {
//   RT,
//   SO,
//   USER
// } ProgramType;

void program_execute(Program *p, int i) {
  p->carga--;
  p->ultimo_uso = i;
}

void program_finish(Program *p) {
  printf("%s %d\n", p->nome, p->ultimo_uso);  
  free(p);
}

int so_program_cmp(const void *p1, const void *p2) {
  Program *prog1 = (Program *)p1;
  Program *prog2 = (Program *)p2;

  if(prog1->prioridade == prog2->prioridade) {
    if(prog1->carga == prog2->carga) {
      return strcmp(prog2->nome, prog1->nome);
    }

    return prog2->carga - prog1->carga;
  }

  return prog1->prioridade - prog2->prioridade;
}

int user_program_cmp(const void *p1, const void *p2) {
  Program *prog1 = (Program *)p1;
  Program *prog2 = (Program *)p2;

  if(prog1->prioridade == prog2->prioridade) {
    if(prog1->ultimo_uso == prog2->ultimo_uso) {
      return strcmp(prog2->nome, prog1->nome);
    }

    return prog2->ultimo_uso - prog1->ultimo_uso;
  }

  return prog1->prioridade - prog2->prioridade;
}

int main() {
  int N;
  scanf("%d", &N);

  Vector *programs = vector_construct();

  for(int i=0; i<N; i++) {
    char nome[64];
    char tipo[5];
    int prioridade;
    int carga;
    int iteracao_inicio;

    scanf("%s %s %d %d %d", nome, tipo, &prioridade, &carga, &iteracao_inicio);

    Program *p = (Program *) malloc(sizeof(Program));
    strcpy(p->nome, nome);
    strcpy(p->tipo, tipo);
    p->prioridade = prioridade;
    p->carga = carga;
    p->iteracao_inicio = iteracao_inicio;
    p->ultimo_uso = 0;

    vector_push_back(programs, p);
  }

  
  Deque *fila_rt = deque_construct();
  Heap *fila_so = heap_constructor(so_program_cmp);
  Heap *fila_user = heap_constructor(user_program_cmp);

  //0 = SO, 1 = USER
  int ultimo_programa = 1;
  for(int i=0; 1; i++) {
    for(int j=0; j<vector_size(programs); j++) {
      Program *p = (Program *) vector_get(programs, j);
      if(p->iteracao_inicio == i) {
        if(strcmp(p->tipo, "RT") == 0) {
          deque_push_back(fila_rt, vector_remove(programs, j));
          j--;
        } 
      
        if(strcmp(p->tipo, "SO") == 0) {
          heap_push(fila_so, vector_remove(programs, j));
          j--;
        }

        if(strcmp(p->tipo, "USER") == 0) {
          heap_push(fila_user, vector_remove(programs, j));
          j--;
        }
      }
    }

    if(deque_size(fila_rt) == 0 && heap_size(fila_so) == 0 && heap_size(fila_user) == 0)
      break;

    if(deque_size(fila_rt) > 0) {
      Program *p = (Program *) deque_pop_front(fila_rt);
      program_execute(p, i);

      if(p->carga == 0) {
        program_finish(p);
        continue;
      }

      deque_push_back(fila_rt, p);
      continue;
    }

    if((ultimo_programa == 1 && heap_size(fila_so) > 0) || (ultimo_programa == 0 && heap_size(fila_user) == 0)) {
      Program *p = (Program *) heap_pop(fila_so);
      program_execute(p, i);

      if(p->carga == 0) {
        program_finish(p);

        ultimo_programa = 0;
        continue;
      }

      heap_push(fila_so, p);

      ultimo_programa = 0;
      continue;
    }

    if((ultimo_programa == 0 && heap_size(fila_user) > 0) || (ultimo_programa == 1 && heap_size(fila_so) == 0)) {
      Program *p = (Program *) heap_pop(fila_user);
      program_execute(p, i);

      if(p->carga == 0) {
        program_finish(p);

        ultimo_programa = 1;
        continue;
      }

      heap_push(fila_user, p);
      
      ultimo_programa = 1;
      continue;
    }

  }

  vector_destroy(programs);
  deque_destroy(fila_rt);
  heap_destroy(fila_so);
  heap_destroy(fila_user);
}