# include<stdio.h>

int fill_array(double arr[], int size);
void show_array(double *arr, int size);
void reverse_array(double *arr, int size);

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    double arr[size];
    int actl_size = fill_array(arr, size);
    show_array(arr, actl_size);
    reverse_array(arr, actl_size);
    show_array(arr, actl_size);
}

int fill_array(double arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("Enter number #%d: ", i + 1);
        if (scanf("%lf", &arr[i]))
            continue;
        else
            break;

    }
    return i;
}

void show_array(double *arr, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}

void reverse_array(double *arr, int size)
{
    int i;
    double temp;
    for(i = 0; i < size / 2; i++)
    {
        //swap two elements
        temp = arr[i];
        arr[i] = *(arr + size - i - 1);
        arr[size - i - 1] = temp;
    }
}
