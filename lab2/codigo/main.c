#include<stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void)
{
    Vector *v = vector_construct();

    vector_push_back(v, -81);
    vector_push_back(v, 27);
    vector_push_back(v, 57);
    vector_push_back(v, 63);

    int b = vector_binary_search(v, 63);
    printf("%d\n", b);

    return 0;
}

