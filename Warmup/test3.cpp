#include <iostream>
using namespace std;

void f(int a[], int* b){
        std::cout << sizeof(a) << " " << sizeof(b) << "\n";
}
void modifyv(int &v){
    cout << "modifyv\n" << v << "\n";
    v *=10;
}
void modifyv2(int *v){
    cout << "modifyv2\n" << *v << "\n";
    *v *=10;
}



int main(){
    int a[3] = {10, 20, 30};
    int * b = new int[4];
    cout << sizeof(a) << " " << sizeof(b) << "\n";
    f(a, b);
    int * p = &a[0];
    cout << *++p << " " << *p << "\n";

    int num = 10;
    int num2 = 10;
    modifyv(num);
    modifyv2(&num2);
    cout << num << "\n";
    cout << num2 << "\n";


    int ci = 100;
    const int &rci = ci;
    ci = 200;
    cout << rci << "\n";

    int i = 42;
    int &r1 = i;
    const int &r2 = i;
    const int r4 = r1 * 2;
    cout << r4 << "\n";
    r1 = 0;
    cout << r4 << "\n";

    int val = 10;
    int *p1 = &val;
    cout << p1  << " " <<  *p1++ << " " << p1 << "\n";
    cout << *p1 << " " << p1 << "\n";


}