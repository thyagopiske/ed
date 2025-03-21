#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hash_str(HashTable *h, void *data)
{
    char *str = (char *)data;

    long hash_val = 0;
    int base = 127;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int main()
{
    HashTable *h = hash_table_construct(11, hash_str, cmp_str);

    int n;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        char *name = malloc(sizeof(char) * 100);
        int *age = malloc(sizeof(int));
        scanf("%s %d", name, age);
        void *prev = hash_table_set(h, name, age);
        if(prev != NULL) {
            free(prev);
            free(name);
        }
    }

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        char *name = malloc(sizeof(char) * 100);
        scanf("%s", name);
        printf("%d\n", *(int *)hash_table_get(h, name));
        free(name);
    }

    hash_table_destroy(h);

    return 0;
}
