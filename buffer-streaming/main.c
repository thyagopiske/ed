#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
  char identificador_video[50];
  int identificador_unico;
  float timestamp;
} Frame;

const int MAX_SIZE=20;

int main() {
  Frame buffer[MAX_SIZE];
  int i_inicio=0;
  int i_final=0;
  int tamanho=0;
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
      if(tamanho == MAX_SIZE) {
        printf("FILA CHEIA\n");
        continue;
      }

      Frame f;
      strcpy(f.identificador_video, identificador_video);
      f.identificador_unico = identificador_unico;
      f.timestamp = timestamp;
      buffer[i_final] = f;
      i_final = (i_final+1)%MAX_SIZE;
      tamanho++;
    }

    if(strcmp(comando, "PLAY") == 0) {
      if(tamanho < 5) {
        printf("AGUARDE\n");
        continue;
      }

      for(int j=0; j<5; j++) {
        Frame f = buffer[i_inicio];
        i_inicio = (i_inicio+1)%MAX_SIZE;
        tamanho--;
        printf("ID: %d, Timestamp: %.2f\n", f.identificador_unico, f.timestamp);
      }
    }
  }

  return 0;
}