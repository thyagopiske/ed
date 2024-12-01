#include "product.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
  int N;

  scanf("%d", &N);

  Product **products = (Product**) calloc(N, sizeof(Product *));

  for(int i=0; i<N; i++) {
    char nome[64];
    float price;
    int qtd;
    int sales;

    scanf(" %[^\n]s", nome);
    scanf("%f", &price);
    scanf("%d", &qtd);
    scanf("%d", &sales);

    products[i] = product_constructor(nome, price, qtd);
    product_sell(products[i], sales);
  }

  char c;
  scanf(" %c", &c);

  if(c == 'N') {
    qsort(products, N, sizeof(Product *), product_compare_name);
  }

  if(c == 'P') {
    qsort(products, N, sizeof(Product *), product_compare_price);
  }

  if(c == 'S') {
    qsort(products, N, sizeof(Product *), product_compare_sales);
  }

  for(int i=0; i<N; i++) {
    product_print(products[i]);
  }

  for(int i=0; i<N; i++) {
    product_destructor(products[i]);
  }
  free(products);

  return 0;
}