#include <stdio.h>
#include <stdlib.h>

// for given list of input (integer split by space), count the total

int main()
{
    int temp,total;
    total = 0;
    int num_of_input = 0;
    scanf("%d", &num_of_input);
    while (num_of_input--)
    {
        scanf("%d", &temp);
        total += temp;
    }
    printf("%d\n", total);
}