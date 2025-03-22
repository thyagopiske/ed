#include "stdlib.h"
#include "stdbool.h"
#include "binary_tree.h"
#include "stdio.h"
#include "string.h"
#include "queue.h"

struct BinaryTree 
{
  struct BTNode *root;
  CmpFn cmp_fn;
  KeyDestroyFn key_destroy_fn;
  ValDestroyFn val_destroy_fn;
};

typedef struct BTNode
{
  KeyValPair *key_val_pair;
  struct BTNode *left;
  struct BTNode *right;
} BTNode;


BTNode *binary_tree_add_recursive_2(BTNode *node, void *key, void *value, CmpFn cmp_fn);
void binary_tree_destroy_recursive(BTNode *node);
BTNode *binary_tree_get_recursive(BTNode *node, void *key, CmpFn cmp_fn);
BTNode *node_construct(void *key, void *value, void *left, void *right);
void binary_tree_print_recursive(BTNode *node);
void inorder(BTNode *node, Vector *v);
void pre_order(BTNode *node, Vector *v);
void post_order(BTNode *node, Vector *v);
KeyValPair *copy_kvp(KeyValPair *kvp);


KeyValPair *key_val_pair_construct(void *key, void *val)
{
  KeyValPair *kvp = malloc(sizeof(KeyValPair));
  kvp->key = key;
  kvp->value = val;

  return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp)
{
  free(kvp->value);
  free(kvp->key);
  free(kvp);
}

BinaryTree *binary_tree_construct(
  CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
  ValDestroyFn val_destroy_fn)
{
  BinaryTree  *bt = malloc(sizeof(BinaryTree));
  bt->cmp_fn = cmp_fn;
  bt->key_destroy_fn = key_destroy_fn;
  bt->val_destroy_fn = val_destroy_fn;
  bt->root = NULL;

  return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value)
{
  bt->root = binary_tree_add_recursive_2(bt->root, key, value, bt->cmp_fn);
}

BTNode *binary_tree_add_recursive_2(BTNode *node, void *key, void *value, CmpFn cmp_fn)
{
  if (node == NULL)
    return node_construct(key, value, NULL, NULL);

  if(cmp_fn(node->key_val_pair->key, key) > 0)
    node->left = binary_tree_add_recursive_2(node->left, key, value, cmp_fn);    
  else if(cmp_fn(node->key_val_pair->key, key) < 0)
    node->right = binary_tree_add_recursive_2(node->right, key, value, cmp_fn);
  else
  {
    free(key);
    free(value);
  }

  return node;
};

BTNode *node_construct(void *key, void *value, void *left, void *right)
{
  BTNode *node = malloc(sizeof(BTNode));
  node->key_val_pair = key_val_pair_construct(key, value);
  node->left = left;
  node->right = right;
  
  return node;
}

void node_destroy(BTNode *node)
{
  key_val_pair_destroy(node->key_val_pair);
  free(node);
}

void *binary_tree_get(BinaryTree *bt, void *key)
{
  BTNode *node = binary_tree_get_recursive(bt->root, key, bt->cmp_fn);

  if (node == NULL)
    return NULL;

  return node->key_val_pair->value;
}

BTNode *binary_tree_get_recursive(BTNode *node, void *key, CmpFn cmp_fn)
{
  if (node == NULL || cmp_fn(node->key_val_pair->key, key) == 0)
    return node;
  
  if(cmp_fn(node->key_val_pair->key, key) > 0)
    return binary_tree_get_recursive(node->left, key, cmp_fn);
  else
    return binary_tree_get_recursive(node->right, key, cmp_fn);
}

void binary_tree_destroy(BinaryTree *bt)
{
  binary_tree_destroy_recursive(bt->root);
  free(bt);
}

void binary_tree_destroy_recursive(BTNode *node)
{
  if(node == NULL)
    return;

  binary_tree_destroy_recursive(node->left);
  binary_tree_destroy_recursive(node->right);
  key_val_pair_destroy(node->key_val_pair);
  free(node);
}

void binary_tree_remove(BinaryTree *bt, void *key)
{
  BTNode *node_atual = bt->root;
  BTNode *node_pai = NULL;

  while (node_atual != NULL && bt->cmp_fn(node_atual->key_val_pair->key, key) != 0)
  {
    node_pai = node_atual;
    if (bt->cmp_fn(key, node_atual->key_val_pair->key) < 0)
    {
      node_atual = node_atual->left;
    }
    else 
    {
      node_atual = node_atual->right;
    }
  }

  if (node_atual == NULL)
  {
    return;
  }
  
  //caso 1: node não tem filhos:
  if (node_atual->left == NULL && node_atual->right == NULL)
  {
    if (node_pai == NULL)
    {
      bt->root = NULL;
    }
    else if(node_atual == node_pai->left)
    {
      node_pai->left = NULL;
    }
    else 
    {
      node_pai->right = NULL;
    }

    node_destroy(node_atual);
  }
  //caso 2: node a ser removido tem apenas 1 filho
  else if(node_atual->left == NULL)
  {
    if (node_pai == NULL)
    {
      bt->root = node_atual->right;
    } 
    else if(node_atual == node_pai->left)
    {
      node_pai->left = node_atual->right;
    }
    else
    {
      node_pai->right = node_atual->right;
    }
    
    node_destroy(node_atual);
  }
  else if(node_atual->right == NULL)
  {
    if (node_pai == NULL)
    {
      bt->root = node_atual->left;
    }
    else if(node_atual == node_pai->left)
    {
      node_pai->left = node_atual->left;
    }
    else
    {
      node_pai->right = node_atual->left;
    }

    
    node_destroy(node_atual);
  }
  //caso 3: node a ser removido tem 2 filhos
  else
  {
    //sucessor = encontrar_sucessor
    BTNode *node_sucessor = node_atual->right;
    while (node_sucessor->left != NULL)
    {
      node_sucessor = node_sucessor->left;
    }

    KeyValPair* valor_sucessor = copy_kvp(node_sucessor->key_val_pair);

    binary_tree_remove(bt, node_sucessor->key_val_pair->key);
    key_val_pair_destroy(node_atual->key_val_pair);
    node_atual->key_val_pair = valor_sucessor;
  }
}

void binary_tree_print_recursive(BTNode *node) {
  if (node == NULL) {
      printf("NULL");
      return;
  }
  
  printf("(");
  printf("%d, ", *((int*)(node->key_val_pair->key)));
  
  binary_tree_print_recursive(node->left);
  printf(", ");
  
  binary_tree_print_recursive(node->right);
  printf(")");
}

void binary_tree_print(BinaryTree *bt) {
  binary_tree_print_recursive(bt->root);
  printf("\n");
}

KeyValPair *binary_tree_min(BinaryTree *bt)
{
  BTNode *node = bt->root;
  while (node->left != NULL)
  {
    node = node->left;
  }
  
  return node->key_val_pair;
}

KeyValPair *binary_tree_max(BinaryTree *bt)
{
  BTNode *node = bt->root;
  while (node->right != NULL)
  {
    node = node->right;
  }
  
  return node->key_val_pair;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt)
{
  KeyValPair *kvp = binary_tree_min(bt);

  KeyValPair *cp = copy_kvp(kvp);

  binary_tree_remove(bt, kvp->key);

  return cp;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt)
{
  KeyValPair *kvp = binary_tree_max(bt);

  KeyValPair *cp = copy_kvp(kvp);

  binary_tree_remove(bt, kvp->key);

  return cp;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt)
{
  Queue *q = queue_constructor(100);
  Vector *v = vector_construct();
  
  queue_add(q, bt->root);

  while(!queue_is_empty(q))
  {
    BTNode *node = queue_remove(q);
    if (node != NULL)
    {
      vector_push_back(v, node->key_val_pair);
      queue_add(q, node->left);
      queue_add(q, node->right);
    }
  }
  
  queue_destroy(q);

  return v;
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt)
{
  Vector *v = vector_construct();

  inorder(bt->root, v);

  return v;
}

void inorder(BTNode *node, Vector *v)
{
  if (node == NULL)
  {
    return;
  }

  inorder(node->left, v);
  vector_push_back(v, copy_kvp(node->key_val_pair));
  inorder(node->right, v);
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt)
{
  Vector *v = vector_construct();

  pre_order(bt->root, v);

  return v;
}

void pre_order(BTNode *node, Vector *v)
{
  if (node == NULL)
  {
    return;
  }
  
  vector_push_back(v, copy_kvp(node->key_val_pair));
  pre_order(node->left, v);
  pre_order(node->right, v);
}


Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt)
{
  Vector *v = vector_construct();

  post_order(bt->root, v);

  return v;
}

void post_order(BTNode *node, Vector *v)
{
  if (node == NULL)
  {
    return;
  }
  
  post_order(node->left, v);
  post_order(node->right, v);
  vector_push_back(v, copy_kvp(node->key_val_pair));
}

KeyValPair *copy_kvp(KeyValPair *kvp)
{
  KeyValPair *cp = malloc(sizeof(KeyValPair));
  cp->key = malloc(sizeof(void *));
  cp->value = malloc(sizeof(void *));
  memcpy(cp->key, kvp->key, sizeof(void *));
  memcpy(cp->value, kvp->value, sizeof(void *));

  return cp;
}