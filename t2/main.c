#include "stdlib.h"
#include<stdio.h>
#include<string.h>
#include "binary_tree.h"
#include "hash.h"

typedef struct 
{
  char *nome;
  char *sigla;
  float *valor_unitario_acao;
  int n_total_acoes;
  int n_acoes_vendidas;
} Empresa;


int cmp_empresas(void *e1, void *e2)
{
  Empresa *emp1 = (Empresa *)e1;
  Empresa *emp2 = (Empresa *)e2;

  if (*(emp1->valor_unitario_acao) == *(emp2->valor_unitario_acao))
  {
    return strcmp(emp1->sigla, emp2->sigla);
  }

  if (*(emp1->valor_unitario_acao) > *(emp2->valor_unitario_acao))
    return 1;
  else
    return -1;
}

int cmp_strings(void *k1, void *k2)
{
  return strcmp((char *)k1, (char *)k2);
}

float *new_float(float value)
{
  float *ptr = malloc(sizeof(float));
  *ptr = value;
  return ptr;
}

void ht_key_destroy_fn(void *key)
{
  free(key);
}

Empresa *duplicar_empresa(Empresa *empresa)
{
  Empresa *cp = malloc(sizeof(Empresa));
  cp->nome = malloc(101*sizeof(char));
  cp->sigla = malloc(33*sizeof(char));
  cp->valor_unitario_acao = new_float(*(empresa->valor_unitario_acao));
  strcpy(cp->nome, empresa->nome);
  strcpy(cp->sigla, empresa->sigla);
  cp->n_total_acoes = empresa->n_total_acoes;
  cp->n_acoes_vendidas = empresa->n_acoes_vendidas;

  return cp;
}


KeyValPair *cp_kvp(KeyValPair *kvp)
{
  Empresa *e = (Empresa *) kvp->value;
  KeyValPair *cp = malloc(sizeof(KeyValPair));
  
  cp->value = duplicar_empresa(e);
  cp->key = ((Empresa *)cp->value)->valor_unitario_acao;
  
  return cp;
}

void ht_val_destroy_fn(void *val)
{
  Empresa *e = (Empresa *)val;
  free(e->nome);
  free(e->sigla);
  free(e->valor_unitario_acao);
  free(e);
}

void bt_key_destroy_fn(void *key)
{
  free(key);
}

void bt_val_destroy_fn(void *val)
{
  Empresa *e = (Empresa *)val;
  free(e->nome);
  free(e->sigla);
  free(e);
}

void print_interval(void *val)
{
  Empresa *e = (Empresa *)val;
  printf("%s\n", e->sigla);
}


int *new_int(int value)
{
    int *ptr = malloc(sizeof(int));
    *ptr = value;
    return ptr;
}

Empresa *new_empresa(char *nome, char *sigla, float *valor_unitario_acao, int n_total_acoes, int n_acoes_vendidas)
{
  Empresa *e = malloc(sizeof(Empresa));
  e->nome = nome;
  e->sigla = sigla;
  e->valor_unitario_acao = valor_unitario_acao;
  e->n_total_acoes = n_total_acoes;
  e->n_acoes_vendidas = n_acoes_vendidas;

  return e;
}

int hash_str(HashTable *h, void *data)
{
    char *str = (char *)data;

    long hash_val = 0;
    int base = 31;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

void print_sorted_fn(void *val)
{
  Empresa *e = (Empresa *) val;
  printf("%s %.2f\n", e->sigla, *(e->valor_unitario_acao));
}

int main()
{
  char nome_arquivo[10];
  FILE *arquivo;
  char linha[200];
  int n;
  BinaryTree *bt = binary_tree_construct(cmp_empresas, bt_key_destroy_fn, bt_val_destroy_fn, cp_kvp);
  HashTable *ht = hash_table_construct(23, hash_str, cmp_strings, ht_key_destroy_fn, ht_val_destroy_fn);

  scanf("%s", nome_arquivo);
  arquivo = fopen(nome_arquivo, "r");
  fscanf(arquivo, "%d\n", &n);

  for (size_t i = 0; i < n; i++)
  {
    fgets(linha, 100, arquivo);
    Empresa *empresa = malloc(sizeof(Empresa));
    // empresa->nome = malloc(101*sizeof(char));
    // empresa->nome = malloc(101*sizeof(char));
    char *nome =  malloc(101*sizeof(char));
    char *sigla =  malloc(33*sizeof(char));
    float *valor_unitario_acao = malloc(sizeof(float));
    int n_total_acoes;
    int n_acoes_vendidas;
    sscanf(linha,"%s %s %f %d %d\n", nome, sigla, valor_unitario_acao, &n_total_acoes, &n_acoes_vendidas);
    empresa->nome = nome;
    empresa->sigla = sigla;
    empresa->valor_unitario_acao = valor_unitario_acao;
    empresa->n_total_acoes = n_total_acoes;
    empresa->n_acoes_vendidas = n_acoes_vendidas;

    hash_table_set(ht, sigla, empresa);

    Empresa *empresa_dup = duplicar_empresa(empresa);

    binary_tree_add(bt, empresa_dup->valor_unitario_acao, empresa_dup);
  }
  

  fclose(arquivo);

  int m;
  scanf("%d", &m);

  for (size_t i = 0; i < m; i++)
  {
    char *comando = malloc(15*sizeof(char));
    scanf("\n%s", comando);
    if (strcmp(comando, "UPDATE") == 0)
    {
      char *sigla = malloc(33*sizeof(char));
      float *valor = malloc(sizeof(float));
      scanf("%s", sigla);
      scanf("%f", valor);

      Empresa *e = hash_table_get(ht, sigla);

      Empresa *new_e_ht = duplicar_empresa(e);
      free(new_e_ht->valor_unitario_acao);
      new_e_ht->valor_unitario_acao = new_float(*(valor));
      Empresa *val = (Empresa *) hash_table_set(ht, sigla, new_e_ht);

      binary_tree_remove(bt, e);
      Empresa *new_e_bt = duplicar_empresa(new_e_ht);
      binary_tree_add(bt, new_e_bt->valor_unitario_acao, new_e_bt);

      ht_val_destroy_fn(val);
      
      free(sigla);
      free(valor);
    }

    if (strcmp(comando, "GET") == 0)
    {
      char *sigla = malloc(33*sizeof(char));
      scanf("%s", sigla);

      Empresa *e = hash_table_get(ht, sigla);
      printf("%s %s %.2f %d %d\n", e->nome, e->sigla, *(e->valor_unitario_acao), e->n_total_acoes, e->n_acoes_vendidas);

      free(sigla);
    }

    if (strcmp(comando, "RM") == 0)
    {
      char *sigla = malloc(33*sizeof(char));
      scanf("%s", sigla);

      Empresa *e = hash_table_pop(ht, sigla);
      binary_tree_remove(bt, e);

      free(sigla);
      ht_val_destroy_fn(e);
    }
    
    if (strcmp(comando, "MIN") == 0)
    {
      KeyValPair* kvp = binary_tree_min(bt);
      Empresa *e = kvp->value;
      printf("%s\n", e->sigla);
    }
    
    if (strcmp(comando, "MAX") == 0)
    {
      KeyValPair* kvp = binary_tree_max(bt);
      Empresa *e = kvp->value;
      printf("%s\n", e->sigla);
    }

    if(strcmp(comando, "INTERVAL") == 0)
    {
      float *min = malloc(sizeof(float)); 
      float *max = malloc(sizeof(float));
      scanf("%f", min); 
      scanf("%f", max);
      binary_tree_print_interval(bt, print_interval, *(min), *(max)); 

      free(min);
      free(max);
    }

    if(strcmp(comando, "SORTED") == 0)
    {
      binary_tree_print_sorted(bt, print_sorted_fn); 
    }
    
    free(comando);
  }
  

  hash_table_destroy(ht);
  binary_tree_destroy(bt);

  return 0;
}