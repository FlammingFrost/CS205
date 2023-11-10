#include <stdio.h>
#include <math.h>
#define PI acos(-1)

int main()
{
    double input;
    char option;
    scanf("%lf %c", &input, &option);
    if (option == 'd')
    {
        printf("%.2f", input * PI / 180);
    }
    else if (option == 'r')
    {
        printf("%.2f", input * 180 / PI);
    }
    else
    {
        // should not happen, no output.
    }
}