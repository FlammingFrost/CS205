#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
    int *p = (int*)malloc(10 * sizeof(int));
    for (size_t i = 0; i < 10; i++)
    {
        p[i] = i;
    }
    int *half_p = p + 5;
    // free(half_p); // munmap_chunk(): invalid pointer
    // half_p = (int*)realloc(half_p, 10 * sizeof(int)); // realloc(): invalid pointer
    half_p = (int*)malloc(10);
    free(half_p);
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", p[i]);
    }
    // to show that the memory is not freed
    // printf("%d\n", _msize(p));
    // free(p);
    return 0;
}
