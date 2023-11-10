#include<stdio.h>

int main() {
    printf("Hello World!\n");
    short n1 = 120;
    short p1 = &n1; //should initialize with a pointer
    short *p2 = &n1;
    short *p3 = n1;
    printf("n1 = %d\n", n1);
    printf("p1 = %d\n", p1);
    printf("p2 = %d\n", p2);
    printf("*p2 = %d\n", *p2);
    printf("p3 = %d\n", p3);
    // printf("*p3 = %d\n", *p3); //Exception thrown: read access violation. p3 was a pointer initialized with a short value, not a pointer to a short value. Memory address 120 is not readable.

    printf("--------------------\n");

    short n2[5] = {1, 2, 3, 4, 5};
    short *p4 = n2;//n2 is a *pointer* to the first element of the array, not the first element of the array
    short *p5 = &n2[0];
    short *p6 = &n2;
    printf("n2 = %d\n", n2);
    printf("p4 = %d\n", p4);
    printf("p5 = %d\n", p5);
    printf("p6 = %d\n", p6);
    printf("*n2 = %d\n", *(n2));
    printf("*p4 = %d\n", *p4);
    printf("*p5 = %d\n", *p5);
    printf("*p6 = %d\n", *p6);
    printf("*(p4 + 1) = %d\n", *(p4 + 1));


    return 0;
}