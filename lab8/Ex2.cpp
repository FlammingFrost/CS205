#include <iostream>
#include "match.h"

using namespace std;

int main()
{
    printf("Enter a string: ");
    char str[100];
    cin.getline(str, 100);
    printf("Enter a character: ");
    char ch;
    cin >> ch;

    const char * ptr = match(str, ch);

    if (ptr == NULL)
    {
        printf("Not Found.\n");
    }
    else
    {
        cout<< ptr << endl;
    }

}