#include "stdio.h"
#include "stdlib.h"
#include "forward_list.h"
#include "string.h"

void print_data(data_type data)
{
    printf("%s\n", (char *)data);
}

int main()
{
    int num_instructions;
    scanf("%d", &num_instructions);

    ForwardList *list = forward_list_construct();

    for (int i = 0; i < num_instructions; i++)
    {
        char command[20];

        scanf("\n%s", command);

        if (strcmp(command, "PUSH_FRONT") == 0)
        {
            // O que aconteceria aqui se trocássemos a alocação dinâmica por alocação estática? Faça o teste!
            char *value = calloc(20, sizeof(char));
            scanf("%s\n", value);

            forward_list_push_front(list, value);
        }
        else if (strcmp(command, "POP") == 0)
        {
            int idx;
            scanf("%d", &idx);

            void *val = forward_list_pop_index(list, idx);

            // PARA FAZER: libere o elemento retornado pelo pop
            if(val != NULL)
            {
                free(val);
            }
        }
    }

    forward_list_print(list, print_data);

    // PARA FAZER: a lista ainda pode ter elementos aqui. Libere-os.
    Node *n = list->head;
    while(n != NULL)
    {
        free(n->value);
        n = n->next;
    }
    
    forward_list_destroy(list);

    return 0;
}