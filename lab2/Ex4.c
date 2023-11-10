#include <stdio.h>

int main()
{
    printf("Please input a character :\n");
    char a;
    scanf("%c", &a);

    printf("Please inpt an integer:\n");
    int b;
    scanf("%d", &b);

    printf("Please input a float:\n");
    float c;
    scanf("%f", &c);

    printf("The variables you entered were:\n");
    printf("The charactr is:%c\n",a);
    printf("The integer is:%d\n",b);
    printf("The float is %f\n",c);

    return 0;
}