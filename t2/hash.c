#include "stdlib.h"
#include "hash.h"
#include "forward_list.h"
#include<stdio.h>
#include<string.h>

struct HashTable 
{
  int table_size;
  int n_elements;
  ForwardList **table;
  HashFunction hash_fn;
  CmpFunction cmp_fn;
  HT_KeyDestroyFn key_destroy_fn;
  HT_ValDestroyFn val_destroy_fn;
};

struct HashTableIterator
{
  HashTable *hash_tbl;
  int bucket_idx;
  int current_element;
  ListIterator *list_it;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn, HT_KeyDestroyFn key_destroy_fn, HT_ValDestroyFn val_destroy_fn)
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->table_size = table_size;
  ht->table = calloc(table_size, sizeof(ForwardList *));
  ht->hash_fn = hash_fn;
  ht->cmp_fn = cmp_fn;
  ht->key_destroy_fn = key_destroy_fn;
  ht->val_destroy_fn = val_destroy_fn;
  ht->n_elements = 0;

  return ht;
}

void *hash_table_set(HashTable *h, void *key, void *val)
{
  int hash = h->hash_fn(h, key);
  ForwardList *l = h->table[hash];

  if (l == NULL)
  {
      l = forward_list_construct();
      h->table[hash] = l;
  }

  Node *n = l->head;
  while(n != NULL) 
  {
    HashTableItem *item = n->value;
    if (h->cmp_fn(key, item->key) == 0)
    {
      void *val_antigo = item->val;
      item->val = val;
      return val_antigo;
    }

    n = n->next;
  }
  
  HashTableItem *new_item = malloc(sizeof(HashTableItem));
  new_item->key = strdup(key);
  new_item->val = val;

  forward_list_push_front(l, new_item);

  h->n_elements++;

  return NULL;
}

void *hash_table_get(HashTable *h, void *key)
{
  int hash = h->hash_fn(h, key);
  ForwardList *l = h->table[hash];

  if (l != NULL)
  {
    Node *n = l->head;
    while(n != NULL) 
    {
      HashTableItem *item =  n->value;
      if (h->cmp_fn(key, item->key) == 0)
      {
        return item->val;
      }
  
      n = n->next;
    }
  }

  return NULL;
}

void hash_table_destroy(HashTable *h)
{
  for (int i = 0; i < h->table_size; i++)
  {
    ForwardList *l = h->table[i];
    if (l != NULL)
    {
      Node *n = l->head;
      while(n != NULL)
      {
        Node *next = n->next;
        
        HashTableItem *item = n->value;

        h->key_destroy_fn(item->key);
        h->val_destroy_fn(item->val);
        free(item);

        n = next; 
      }
  
      forward_list_destroy(h->table[i]);
    }
  }
  
  free(h->table);
  free(h);
}

int hash_table_size(HashTable *h)
{
  return h->table_size;
}

void *hash_table_pop(HashTable *h, void *key)
{
  int hash = h->hash_fn(h, key);
  ForwardList *l = h->table[hash];

  Node *curr = l->head;
  Node *prev = NULL;
  while (curr != NULL)
  {
    HashTableItem *item =  curr->value;
    if (h->cmp_fn(item->key, key) == 0)
    {
      if (prev == NULL)
      {
        l->head = curr->next;
      }
      else 
      {
        prev->next = curr->next;
      }
      
      void *val = item->val;
      h->key_destroy_fn(item->key);
      free(item);
      free(curr);
      l->size--;

      return val;
    }
    
    prev = curr;
    curr = curr->next;
  }
  
  return NULL;
}

HashTableIterator *hash_table_iterator(HashTable *h)
{
  HashTableIterator *it = malloc(sizeof(HashTableIterator));
  // it->bucket_idx = 0;
  // it->current_element = 0;
  it->hash_tbl = h;
  ListIterator *list_it = malloc(sizeof(ListIterator));
  // list_it->current = NULL;
  // it->list_it = list_it;
  
  for (size_t i = 0; i < h->table_size; i++)
  {
    ForwardList *l = h->table[i];
    if (l != NULL)
    {
      list_it->current = l->head;
      it->list_it = list_it;
      it->bucket_idx = i;
      it->current_element = 0;

      break;
    }
  }

  return it;
}

int hash_table_iterator_is_over(HashTableIterator *it)
{
  return it->current_element >= it->hash_tbl->n_elements;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it)
{
  if (it->list_it->current == NULL)
  {
    for (size_t i = it->bucket_idx + 1; i < it->hash_tbl->table_size; i++)
    {
      ForwardList *l = it->hash_tbl->table[i];
      if (l != NULL)
      {
        HashTableItem *item = l->head->value;
        it->list_it->current = l->head->next;
        it->bucket_idx = i;
        it->current_element++;
        
        return item;
      }
    }

    return NULL;
  } 

  HashTableItem *item = it->list_it->current->value;
  it->list_it->current =  it->list_it->current->next;
  it->current_element++;
  
  return item;
}

void hash_table_iterator_destroy(HashTableIterator *it)
{
  free(it->list_it);
  free(it);
}

Vector *hash_to_vector(HashTable *h)
{
  Vector *items = vector_construct();

  for (size_t i = 0; i < h->table_size; i++)
  {
    ForwardList *l = h->table[i];
    if (l != NULL)
    {
      Node *n = l->head;
      while (n != NULL)   
      {
        vector_push_back(items, n->value);
        n = n->next;
      }
    }
  }

  return items;
}