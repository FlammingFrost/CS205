#include <stdio.h>

const char* match(const char* s, char ch)
{
    int pos = 0;
    while (s[pos] != '\0')
    {
        if (s[pos] == ch)
        {
            return &s[pos];
        }
        pos++;
    }
    return NULL;
}