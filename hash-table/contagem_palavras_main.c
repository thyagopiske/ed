#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "hash.h"
#include "memory.h"

int cmp_strings(void *k1, void *k2)
{
  return strcmp((char *)k1, (char *)k2);
}

int cmp_items(void *i1, void* i2)
{
  return strcmp((char *) (((HashTableItem *) i1)->key), (char *) (((HashTableItem *) i2)->key));
};

int hash_str(HashTable *h, void *data)
{
    char *str = (char *)data;

    long hash_val = 0;
    int base = 127;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

int main() 
{
  int n;
  scanf("%d", &n);

  Vector *v = vector_construct();
  HashTable *h = hash_table_construct(n, hash_str, cmp_strings);

  for (size_t i = 0; i < n; i++)
  {
    char *name = malloc(sizeof(char) * 100);
    scanf("\n%s", name);

    void *val = hash_table_get(h, name);
    if (val == NULL)
    {
      int *count = malloc(sizeof(int));
      *count = 1;
      hash_table_set(h, name, count);
    }
    else 
    {
      int *count = (int *) val;
      *count = *count + 1;
      hash_table_set(h, name, count);
      free(name);
    }

  }

  HashTableIterator *it = hash_table_iterator(h);
  while(!hash_table_iterator_is_over(it))
  {
    HashTableItem *item = hash_table_iterator_next(it);
    vector_push_back(v, item);
  }

  vector_sort(v, cmp_items);

  for (size_t i = 0; i < vector_size(v); i++)
  {
    HashTableItem *item = vector_get(v, i);
    printf("%s %d\n", (char *)item->key, *((int *)item->val));
  }
  
  vector_destroy(v);
  hash_table_iterator_destroy(it);
  hash_table_destroy(h);
  
  return 0;
}