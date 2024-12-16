#include "stdio.h"
#include "stdlib.h"

void heapify_up(float *arr, int i) {
  int i_parent = (i-1)/2;
  int i_child = i;

  if(i_parent >= 0 && arr[i_parent] < arr[i_child]) {
    float tmp = arr[i_parent];
    arr[i_parent] = arr[i_child];
    arr[i_child] = tmp;

    i_child = i_parent;
    heapify_up(arr, i_child);
  }
}

void heapify_down(float *arr, int i_end, int i_start) {
  int i_max = i_start;
  int i_left_child = 2*i_start + 1;
  int i_right_child = 2*i_start + 2;

  if(i_left_child < i_end  && arr[i_left_child] > arr[i_max]) {
    i_max = i_left_child;
  } 

  if(i_right_child < i_end && arr[i_right_child] > arr[i_max]) {
    i_max = i_right_child;
  }
  
  if(i_start < (i_end+1)/2 && i_max != i_start) {
    float tmp = arr[i_start];
    arr[i_start] = arr[i_max];
    arr[i_max] = tmp;

    i_start = i_max;
    heapify_down(arr, i_end, i_start);
  } 

}

int main() {
  int n;
  scanf("%d", &n);

  float *arr = (float *)malloc(n * sizeof(float));

  // le o array
  for (int i = 0; i < n; i++)
    scanf("%f", &arr[i]);

  // organiza o array como um heap
  for (int i = 0; i < n; i++)
    heapify_up(arr, i);

  // ordena o array
  for (int i = 0; i < n; i++) {
    // troca ultimo com a raiz
    float temp = arr[0];
    arr[0] = arr[n - i - 1];
    arr[n - i - 1] = temp;

    // heapify a partir da raiz
    heapify_down(arr, n - i - 1, 0);
  }

  // mostra o array ordenado na tela
  for (int i = 0; i < n; i++)
    printf("%.2f\n", arr[i]);

  free(arr);

  return 0;
}