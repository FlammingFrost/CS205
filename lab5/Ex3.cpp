#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>

using namespace std;

int read_file(string filename);

int main(){
    char input[100];

    fstream fout1("f1.txt", ios::out); //store original content
    fstream fout2("f2.txt", ios::out); //store uppercase content

    printf("Enter a string: ");

    if (!fout1 || !fout2)
    {
        cout << "Error opening files" << endl;
        return -1;
    }
    else
    {
        cin.getline(input, 100);
        fout1 << input;
        for (char *p = input; *p != '\0'; p++)
        {
            fout2 << (char)toupper(*p);
        }


        fout1.clear();
        fout2.clear();
        fout1.seekg(0);
        fout2.seekg(0);

        fout1.close();
        fout2.close();

        
        //read f1.txt and f2.txt
        printf("The contents of f1.txt: ");
        read_file("f1.txt");
        printf("\n");
        printf("The contents of f2.txt: ");
        read_file("f2.txt");
        printf("\n");
        


    }

    
}
int read_file(string filename)
{
    fstream fin(filename, ios::in);
    if (!fin.good())
    {
        cout << "Error opening file" << endl;
        return -1;
    }
    else
    {
        string readline;
        getline(fin, readline);
        cout << readline;
    }
    return 0;
}