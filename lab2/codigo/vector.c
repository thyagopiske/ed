#include<stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <stdbool.h>

Vector *vector_construct() {
	Vector *v;
	v = (Vector *)calloc(1, sizeof(Vector));

	int allocated = 10;
	data_type *d;
	d = (data_type *)calloc(allocated, sizeof(data_type));

	v->data = d;
	v->size = 0;
	v->allocated = allocated;

	return v;
}


void vector_destroy(Vector *v) {
	free(v->data);
	free(v);
}

void vector_push_back(Vector *v, data_type val) {
	if (v->allocated == v->size) {
		int new_allocated = 2 * v->allocated;
		v->data = (data_type *)realloc(v->data, new_allocated * sizeof(data_type));
		v->allocated = new_allocated;

    v->data[v->size] = val;
		v->size++;
	} 
	else {
		v->data[v->size] = val;
		v->size++;
	}
}



int vector_size(Vector *v) {
	return v->size;
}

data_type vector_get(Vector *v, int i) {
	if (i < 0 || i > v->size) {
		printf("Índice inválido");
		exit(1);
	}

	return v->data[i];
}

void vector_set(Vector *v, int i, data_type val) {
		if (i < 0 || i > v->size) {
		printf("Índice inválido");
		exit(1);
	}

	v->data[i] = val;
}

int vector_find(Vector *v, data_type val) {
	for(int i = 0; i < v->size; i++) {
		if(vector_get(v, i) == val) return i;
	}

	return -1;
}

int vector_argmax(Vector *v) {
	int i_max = 0;

	for(int i = 0; i < v->size; i++) {
		if(v->data[i] > v->data[i_max]) {
			i_max = i;
		}
	}

	return i_max;
}

int vector_argmin(Vector *v) {
	int i_min = 0;

	for(int i = 0; i < v->size; i++) {
		if(v->data[i] < v->data[i_min]) {
			i_min = i;
		}
	}

	return i_min;
}

data_type vector_max(Vector *v) {
	int i_max = vector_argmax(v);
	return v->data[i_max];
}

data_type vector_min(Vector *v) {
	int i_min = vector_argmin(v);
	return v->data[i_min];
}

data_type vector_remove(Vector *v, int i) {
	data_type val = vector_get(v, i);

	for(int j = i + 1; j < vector_size(v); j++) {
		vector_set(v, j - 1, vector_get(v, j));
	}

	v->size = vector_size(v) - 1;

	return val;
}

data_type vector_pop_front(Vector *v) {
	return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v) {
	return vector_remove(v, vector_size(v) - 1);
}

void vector_insert(Vector *v, int i, data_type val) {
	if (v->allocated == v->size) {
		int new_allocated = 2 * v->allocated;
		v->data = (data_type *)realloc(v->data, new_allocated * sizeof(data_type));
		v->allocated = new_allocated;

		for (int j = vector_size(v); j > i; j--) {
			vector_set(v, j, vector_get(v, j - 1));
		}
  } 
	else {
		for (int j = vector_size(v); j > i; j--) {
			vector_set(v, j, vector_get(v, j - 1));
		}
	}

	vector_set(v, i, val);
	v->size = v->size + 1;
}

void vector_swap(Vector *v, int i, int j) {
	data_type aux = vector_get(v, i);
	vector_set(v, i, vector_get(v, j));
	vector_set(v, j, aux);
}

void vector_sort(Vector *v) {
	bool houveTrocas = true;
	int i = 0;
	while(houveTrocas) {
		houveTrocas = false;

		for(int j = 0; j < vector_size(v) - 1 - i; j++) {
			if(vector_get(v, j) > vector_get(v, j+1)) {
				vector_swap(v, j, j+1);
				houveTrocas = true;
			}
		}
	}
}

int vector_binary_search(Vector *v, data_type val) {
	int i_search_min = 0;
	int i_search_max = vector_size(v) - 1;

	while(i_search_min <= i_search_max) {
		int i_central = (i_search_min + i_search_max) / 2;

		if(vector_get(v, i_central) == val) {
			return i_central;
		}

		if(vector_get(v, i_central) > val) {
			i_search_max = i_central - 1;
			continue;
		}

		if(vector_get(v, i_central) < val) {
			i_search_min = i_central + 1;
			continue;
		}
	}

	return -1;
}

void vector_reverse(Vector *v) {
	int num_iteracoes = vector_size(v)/2;
	for(int i = 0; i < num_iteracoes; i++){
		vector_swap(v, i, vector_size(v)-1-i);
	}
}

// CUSTOM

// void realocar(Vector *v) {
//   int new_allocated = 2 * v->allocated;
//   v->data = (data_type *)realloc(v->data, new_allocated * sizeof(data_type));
//   v->allocated = new_allocated;
// }

// void deslocarParaDireita(Vector *v, int i) {
//   for (int j = vector_size(v); j > i; j--)
//   {
//     vector_set(v, j, vector_get(v, j - 1));
//   }
// }