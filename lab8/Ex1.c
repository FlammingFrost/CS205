#include "swap.h"
#include <stdio.h>

int main()
{
    int a, b;
    printf("Enter a and b: ");
    scanf("%d%d", &a, &b);
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);
    return 0;
}