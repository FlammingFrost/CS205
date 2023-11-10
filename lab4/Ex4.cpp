#include <iostream>
using namespace std;

int main()
{
    int *p;
    p = new int[5];
    for (int i = 0; i < 5; i++)
    {
        p[i] = i+10086;
    }
    for (int * i = p+5-1; i >= p; i--)
    {
        printf("%d\n", *i);
    }
    delete[] p;
    return 0;
}