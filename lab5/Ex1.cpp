#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    int word_count = 0;
    string word;
    printf("Enter words (to stop, type the word done):\n");
    while (true)
    {
        cin >> word;
        if (word == "done")
        {
            break;
        }
        word_count++;
    }

    if (word_count <=1)
    {
        printf("You entered %d word\n", word_count);
    }
    else
    {
        printf("You entered %d words\n", word_count);
    }
    
    return 0;
}

