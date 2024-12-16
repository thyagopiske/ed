#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct atendimento {
    char nome[100];
    char cpf[100];
} Atendimento;

const int MAX_SIZE = 10;

int main() {
    Atendimento fila[MAX_SIZE];
    int N;
    scanf("%d", &N);
    char str[100];
    char comando[100];
    char nome[100];
    char cpf[100];
    int i_inicio = 0;
    int i_final = 0;
    int tamanho = 0;

    for(int i=0; i<N; i++) {
        scanf("\n%[^\n]s\n", str);
        sscanf(str,"%s %s %s", comando, nome, cpf);
        if (strcmp(comando, "ADICIONAR") == 0) {
            if(tamanho == MAX_SIZE) {
                printf("FILA CHEIA\n");
                continue;
            }

            Atendimento a;
            strcpy(a.nome, nome);
            strcpy(a.cpf, cpf);
            fila[i_final] = a;
            i_final = (i_final + 1) % MAX_SIZE;
            tamanho++;
        }

        if (strcmp(comando, "CHAMAR") == 0) {
            if(!tamanho) {
                printf("FILA VAZIA\n");
                continue;
            }

            Atendimento a = fila[i_inicio];
            i_inicio = (i_inicio + 1) % MAX_SIZE;
            tamanho--;
            printf("%s\n", a.nome);
        }
    }

    return 0;
}