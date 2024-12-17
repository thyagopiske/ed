typedef struct heap Heap;

Heap *heap_construct(int capacity, int (*cmp_fn)(void *, void *));
void heap_destroy(Heap *h);
int heap_size(Heap *h);
void *heap_get(Heap *h, int i);
void heap_push(Heap *h, void *val);
void heapify_up(Heap *h, int i);