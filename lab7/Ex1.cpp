#include <iostream>
#include <cstring>

struct stringy
{
    char *str;
    int ct;
};

void set(stringy &r, const char t[])
{
    r.ct = strlen(t);
    char *newstr = new char[r.ct+1];
    for (int i = 0; i < r.ct; i++)
    {
        newstr[i]=t[i];
    };
    newstr[r.ct] = '\0';
    r.str = newstr;
}

void show(stringy &r, int times = 1)
{
    for (int i = 0; i < times; i++)
    {
        std::cout << r.str << "\n";
    }
}
void show(char *str, int times = 1)
{
    for (int i = 0; i < times; i++)
    {
        std::cout << str << "\n";
    }
}


int main()
{
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";
    set(beany, testing);

    show(beany);
    show(beany, 2);

    testing[0] = 'D';
    testing[1] = 'u';

    show(testing);
    show(testing, 3);
    show("Done!");

    // free memory
    delete [] beany.str;
    return 0;
}