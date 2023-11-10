#include <iostream>
int main()
{
    int n = 0;
    for (; n == 0; ++n)
        std::cout << n;
    while (n = 0)
        std::cout << n;
    for (; n < 3; n += 2)
        ;
    switch (n)
    {
    case 1:
        std::cout << n;
    case 2:
        std::cout << n;
    case 3:
        std::cout << n;
    case 4:
        std::cout << n;
    case 5:
        std::cout << n;
    }
    std::cout << (n = 100) << n << "\n";

    int arr[] = {1, 2, 3, 4, 5};
    int *const p1 = &arr[0];
    int const *p2 = &arr[0];
    int *p3 = &arr[0];

    std::cout << *p1 << *p2 << "\n";
    *p1 += 1;
    p2 += 1;
    std::cout << *p1 << *p2 << "\n";

    unsigned int num = 0x4142;
    char *p = (char *)(&num);
    std::cout << *p << " " << *(p + 1);

    


}