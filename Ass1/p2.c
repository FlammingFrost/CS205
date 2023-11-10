#include <stdio.h>
#include <math.h>

#define PI acos(-1)

double factorial(int n)
{
    double result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

int main()
{
    double input;
    int degree;
    char option;
    double radius;
    scanf("%lf %d %c", &input, &degree, &option);

    if (option == 'd')
    {
        radius = input * PI / 180;
    }
    else if (option == 'r')
    {
        radius = input;
    }
    else
    {
        // should not happen, no output.
    }

    
    //convert radius to nearest 2*pi
    int n_period = (int)radius/(2*PI);
    radius -= n_period*2*PI; // both negative and positive should work

    //test
    // printf("%.2f\n", radius);

    // now calculate the sin, cos
    // with taylor series of degree [degree]
    double sinx=0, cosx=0;
    for (int i = 0; i <= degree; i++)
    {
        if (i%2==1)
        {
            sinx += pow(radius, i)/factorial(i)*pow(-1, (i - 1)/2);
        }
        else if (i%2==0)
        {
            cosx += pow(radius, i)/factorial(i)*pow(-1, i/2);
        }
        
    }
    printf("%.2f\n%.2f", sinx, cosx);
    return 0;
}