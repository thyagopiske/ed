#include "stdio.h"
#include "string.h"
#include "queue.h"
#include "atendimento.h"
#include "frame.h"
#include "stdlib.h"

int main() {
  char programa[64];

  scanf("\n%[^\n]s\n", programa);

  if(strcmp(programa, "SENHAS")==0) {
    Queue *q = queue_constructor(10);
    int N;
    scanf("%d", &N);
    char str[100];
    char comando[100];
    char nome[50];
    char cpf[12];

    for(int i=0; i<N; i++) {
      scanf("\n%[^\n]s\n", str);
      sscanf(str,"%s %s %s", comando, nome, cpf);
      if (strcmp(comando, "ADICIONAR") == 0) {
          if(queue_is_full(q)) {
              printf("FILA CHEIA\n");
              continue;
          }

          Atendimento *a = atendimento_constructor(nome, cpf);
          queue_add(q, a);
      }

      if (strcmp(comando, "CHAMAR") == 0) {
        if(queue_is_empty(q)) {
            printf("FILA VAZIA\n");
            continue;
        }

        Atendimento *a = (Atendimento *) queue_remove(q);
        printf("%s\n", atendimento_get_nome(a));
        free(a);
      }
    }

    queue_destroy(q);
  }

  if(strcmp(programa, "STREAMING")==0) {
    Queue *q = queue_constructor(20);
    int N;
    scanf("%d", &N);

    char str[100];
    char comando[100];
    char identificador_video[50];
    int identificador_unico;
    float timestamp;

    for(int i=0; i<N; i++) {
      scanf("\n%[^\n]s\n", str);
      sscanf(str, "%s %s %d %f", comando, identificador_video, &identificador_unico, &timestamp);

      if(strcmp(comando, "ADICIONAR") == 0) {
        if(queue_is_full(q)) {
          printf("FILA CHEIA\n");
          continue;
        }

        Frame *f = frame_constructor(identificador_video, identificador_unico, timestamp);
        queue_add(q, f);
      }

      if(strcmp(comando, "PLAY") == 0) {
        if(queue_size(q) < 5) {
          printf("AGUARDE\n");
          continue;
        }

        for(int j=0; j<5; j++) {
          Frame *f = (Frame *) queue_remove(q);
          printf("ID: %d, Timestamp: %.2f\n", frame_get_frame_id(f), frame_get_timestamp(f));
          free(f);
        }
      }
    }

  }
  
  return 0;
}