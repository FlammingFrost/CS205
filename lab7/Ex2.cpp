#include <iostream>
#include <cstring>  

template <typename T>
T maxn(T arr[], int n)
{
    T max_element = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_element)
        {
            max_element = arr[i];
        }  
    }
    return max_element;
}
template<>
const char * maxn(const char *arr[], int n)
{
    const char *max_element = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (strlen(arr[i]) > strlen(max_element))
        {
            max_element = arr[i];
        }  
    }
    return max_element;
}

int main()
{
    int arr1[] = {1,2,3,4,5};
    double arr2[] = {9.21, 23.3, 1123.323};
    const char *arr3[] = {"this","no body","morning","bird","sky"};
    std::cout << "size of arr3: " << sizeof(arr3) << "\n";
    std::cout << "Max int is: " << maxn(arr1, 5) << "\n";
    std::cout << "Max double is: " << maxn(arr2, 3) << "\n";
    std::cout << "Max char is: " << maxn(arr3, 5) << "\n";
}