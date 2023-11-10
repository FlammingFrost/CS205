#include <iostream>
using namespace std;

struct CandyBar
{
    char name[20];
    float weight;
    int calories;
};

int main()
{
    CandyBar bars[3];
    printf("Please input three CandyBars' information:\n");

    float r[3];
    for (int i = 0; i < 3; i++)
    {
       printf("Enter brand name of a Candybar:   ");
       cin.getline(bars[i].name, 20);
       
       printf("Enter weight of the Candybar:   ");
       cin >> bars[i].weight;
       printf("Enter calories (an integer value) in the Candybar:   ");
       cin >> bars[i].calories;
       cin.get();
       r[i] = bars[i].calories/bars[i].weight;

    }
    printf("------------------------------");
    printf("Disyplay the CandyBar array contents:\n");
    for (int i = 0; i < 3; i++)
    {
       cout << "Brand name: " << bars[i].name << endl;
       cout << "Weight: " << bars[i].weight << endl;
       cout << "Calories: " << bars[i].calories << endl;

    }
    int idx;
    if (r[0]>r[1])
    {
        idx = 0;
    }
    else
    {
        idx = 1;
    }
    if (r[idx]<r[2]) 
    {
        idx = 2;
    }

    

    printf("max:\n");
    cout << bars[idx].name << endl;
    cout << r[idx] << endl;


    


    

}


