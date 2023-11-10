#include <stdio.h>
#include <math.h>

#define PI acos(-1)

int main()
{
    int n_commands;
    scanf("%d", &n_commands);
    
    double angles[n_commands];
    for (int i = 0; i < n_commands; i++)
    {
        scanf("%lf", &angles[i]);
        // to radians
        angles[i] = angles[i] * PI / 180;
    }

    // using brute force to iterate all possible combinations
    double max_sin = -1;
    double temp;
    double combs[(long long)pow(2, n_commands)];

    // there are 2^n combinations
    for (long long i = 0; i < pow(2, n_commands); i++)
    {
        temp = 0;
        for (int j = 0; j < n_commands; j++)
        {
            // if in binary representation of i, the j-th bit is 1
            if ((i >> j) & 1)
            {
                temp += angles[j];
            }
        }
        // restrict temp to [0, 2 * M_PI)
        while (temp > 2 * PI)
        {
            temp -= 2 * PI;
        }
        while (temp < 0)
        {
            temp += 2 * PI;
        }
        if (sin(temp) > max_sin)
        {
            max_sin = sin(temp);
        }
        
    }
    printf("%.2lf\n", max_sin);
    
    
}