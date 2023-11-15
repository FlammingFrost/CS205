#include <stdio.h>
#include <stdlib.h>
typedef struct PandoraBox
{
    int item_count; // Number of items stored in the PandoraBox.
    int *item_size; // Array of item sizes in bytes.
    void *data;     // A type-agnostic pointer to store data.
} Panbox;
int main()
{
    char * value = (char *)malloc(4);
    int width = 2;
    value[0] = 0x00;
    value[1] = 0x70;
    value[2] = 0x00;
    value[3] = 0x00;
    char interm = *((char *)value + width - 1);
    int pad_byte = (interm & 0x80) ? 0xff : 0x00;
    printf("%hhx\n", interm);
    printf("%hhx\n", pad_byte);

    char * temp;
    sscanf("a6", "%2hhx", &temp);
    printf("%d\n", temp);
    int * A = (int *)malloc(0);
    printf("%p\n", A);
    printf("%d\n", sizeof(Panbox));
    Panbox * box = (Panbox *)malloc(0);
    printf("%d\n", sizeof(box));
    printf("%d\n", sizeof(*box));
    printf("%d\n", box->item_size == NULL);
    Panbox * box2 = (Panbox *)malloc(sizeof(Panbox));
    printf("%d\n", sizeof(box2));
    printf("%d\n", sizeof(*box2));
    Panbox * box3 = (Panbox *)malloc(sizeof(Panbox));
    box3->item_count = 1;
    box3->item_size = NULL;
    box3->data = NULL;
    printf("%d\n", sizeof(box3));
    printf("%d\n", sizeof(*box3));
}