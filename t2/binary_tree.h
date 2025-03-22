
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "vector.h"

typedef struct
{
    void *key;
    void *value;
} KeyValPair;

typedef int (*CmpFn)(void *, void *);
typedef void (*BT_KeyDestroyFn)(void *);
typedef void (*BT_ValDestroyFn)(void *);
typedef void (*PrintIntervalFn)(void *);
typedef void (*PrintSortedFn)(void *);
typedef KeyValPair *(*KvpCp)(KeyValPair *);



KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp, BT_KeyDestroyFn key_destroy_fn, BT_ValDestroyFn val_destroy_fn);

typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_construct(CmpFn cmp_fn, BT_KeyDestroyFn key_destroy_fn, BT_ValDestroyFn val_destroy_fn, KvpCp key_value_pair_copy_fn);
void binary_tree_add(BinaryTree *bt, void *key, void *value);
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *val);
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *val);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt, PrintSortedFn print_fn);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);

void binary_tree_print_interval(BinaryTree *bt, PrintIntervalFn print_interval_fn, float min, float max);
void binary_tree_print_sorted(BinaryTree *bt, PrintSortedFn print_sorted_fn);


#endif