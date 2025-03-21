#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct HashTableIterator
{
    HashTable *hash_tbl;
    int bucket_idx;
    int current_element;
    ListIterator *list_it;
};

HashTableItem *hash_pair_construct(void *key, void *val)
{
    HashTableItem *p = calloc(1, sizeof(HashTableItem));

    p->key = key;
    p->val = val;

    return p;
}

void hash_pair_destroy(HashTableItem *p)
{
    free(p);
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;

    return hash_tbl;
}

int hash_table_size(HashTable *h)
{
    return h->table_size;
}

int hash_table_n_elems(HashTable *h)
{
    return h->n_elements;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
        if (h->buckets[i] != NULL)
            forward_list_destroy(h->buckets[i]);

    free(h->buckets);
    free(h);
}

void *hash_table_set(HashTable *h, void *key, void *val)
{
    int hash = h->hash_fn(h, key);
    ForwardList *l = h->buckets[hash];

    if (l == NULL)
    {
        l = forward_list_construct();
        h->buckets[hash] = l;
    }

    FlNode *n = l->head;
    while(n != NULL) 
    {
        HashTableItem *item = n->value;
        if (h->cmp_fn(item->key, key) == 0)
        {
            void *old_val = item->val;
            item->val = val;

            return old_val;
        }

        n = n->next;
    }

    HashTableItem *item = malloc(sizeof(HashTableItem));
    item->key = key;
    item->val = val;

    forward_list_push_front(l, item);

    h->n_elements++;

    return NULL;
}

Vector *hash_table_items(HashTable *hash_table)
{
    Vector *items = vector_construct();

    for (size_t i = 0; i < hash_table->table_size; i++)
    {
        ForwardList *l = hash_table->buckets[i];
        if (l != NULL)
        {
            FlNode *n = l->head;
            while (n != NULL)   
            {
                vector_push_back(items, n->value);
                n = n->next;
            }
        }
    }
    

    return items;
}

int *hash_table_count_collisions(HashTable * hash_table)
{
    int *counts = (int *) calloc (hash_table_size(hash_table), sizeof(int));

    for (size_t i = 0; i < hash_table->table_size; i++)
    {
        ForwardList *l = hash_table->buckets[i];
        if (l != NULL)
        {
            if (l->size >= 1)
            {
                int collisions = l->size;
                counts[i] = collisions;
            } 
            else
            {
                counts[i] = 0;
            }
        }
    }

    return counts;
}
