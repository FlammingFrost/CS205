#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    printf("Enter words(q to quit):\n");
    int vowel_count = 0;
    int consonant_count = 0;
    int other_count = 0;
    string word;
    while (true)
    {
        cin >> word;
        if (word == "q")
        {
            break;
        }
        else
        {
            if (isalpha(word[0]))
            {
                char firest_lower = tolower(word[0]);
                if (firest_lower == 'a' || firest_lower == 'e' || firest_lower == 'i' || firest_lower == 'o' || firest_lower == 'u')
                {
                    vowel_count++;
                }
                else
                {
                    consonant_count++;
                }
            }
            else
            {
                other_count++;
            }
            
        }
    }

    printf("%d words beginning with vowels\n", vowel_count);
    printf("%d words beginning with consonants\n", consonant_count);
    printf("%d others\n", other_count);

    
}