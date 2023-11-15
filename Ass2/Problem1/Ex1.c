# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
The memory structure of a Panbox is as follows:
- Panbox@1
    |- (int) size 
    |- (pointer) pointer of 1st length  ---------- Heap: A memory of (size) of Int type @2
    |- (pointer) pointer of data storage ---------- Heap: A memory of (size) of char type @3
*/


typedef struct PandoraBox
{
    int item_count; // Number of items stored in the PandoraBox.
    int *item_size; // Array of item sizes in bytes.
    void *data;     // A type-agnostic pointer to store data.
} Panbox;

int isValidBox(Panbox * panbox){
    // case 0: invalid box
    // case 1: valid non-empty box
    // case 2: empty box
    if (panbox == NULL)
    {
        return 0;
    }
    if (panbox->item_count < 0)
    {
        return 0;
    }
    if (panbox->item_count == 0)
    {
        return 2;
    }
    return 1;
}

void delete_box(Panbox * Panbox)
{
    if (Panbox == NULL)
    {
        return;
    }
    if (Panbox->item_size != NULL)
    {
        free(Panbox->item_size);
    }
    if (Panbox->data != NULL)
    {
        free(Panbox->data);
    }
    free(Panbox);
    return;
}

void delete_ptr(void * ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    free(ptr);
    return;
}

size_t get_dataSize(Panbox * panbox)
{
    if (isValidBox(panbox) == 0)
    {
        return 0;
    }
    size_t total_size = 0;
    // empty box
    if (panbox->item_size == NULL || panbox->data == NULL)
    {
        return 0;
    }
    // non-empty box
    for (int i = 0; i < panbox->item_count; i++)
    {
        total_size += panbox->item_size[i];
    }
    return total_size;
}

void *mycpy(void *dst, const void *src, size_t size)
{
    // Lifan: copy (size) bytes from (src) to (dst)
    // ! NOT assign memory to dst, just copy the value
    // dst = (char *)malloc(size * sizeof(char));
    while (size > 0)
    {
        size -= 1;
        *((char *)dst + size ) = *((char *)src + size);
    }
    return NULL;
}
/*
Function: See memcpy in <string.h>

Notes:
- It is not a must to implement this function, but with it you can implement the following functions more easily.@
*/

void *myset(void *dst, int n, size_t size)
{
    // Lifan: to set (size) bytes in (dst) to (n), n is an int, but interpreted as a char
    // ! NOT assign memory to dst, just set the value
    if ((unsigned) n > 0xff)
    {
        return NULL;
    }
    else if (size == 0)
    {
        // printf("Warning: size is 0, nothing to set.\n");
        return NULL;
    }
    
    else
    {
        // dst = (void *)malloc(size * sizeof(char));
        while (size > 0)
        {
            size -= 1;
            *((char *)dst + size ) = (char) n;
        }
    }
    
    return NULL;
}
/*
Function: See memset in <string.h>

Notes:
- It is not a must to implement this function, but with it you can implement the following functions more easily.@
*/

Panbox *create(int item_count, int item_size[])
{
    // exception handling
    int total_size = 0;
    if (item_count < 0 || (item_count > 0 && item_size == NULL))
    {
        return NULL;
    }else if (item_count == 0)
    {
        // create a empty Panbox
        Panbox *emptybox = (Panbox *)malloc(sizeof(Panbox)); // @1:Y
        if (emptybox == NULL)
        {
            return NULL;
        }
        emptybox->item_count = 0;
        // emptybox->item_size = NULL; // @2:N
        // emptybox->data = NULL; // @3:N
        return emptybox;
    }
    else
    {
        for (int i = 0; i < item_count; i++)
        {
            if (item_size[i] <= 0)
            {
                return NULL;
            }
            total_size += item_size[i];
        }
    }    

    // When comes here, every argument is valid

    // create a Panbox
    Panbox *panbox = (Panbox *)malloc(sizeof(Panbox)); // @1:creat
    if (panbox == NULL)
    {
        return NULL;
    }
    panbox->item_count = item_count;
    // panbox->item_size = (int *)malloc(item_count * sizeof(int)); // @2:creat
    // panbox->data = (void*)calloc(total_size, sizeof(char)); // @3:creat and initialize with 0s
    int * item_size_ptr = (int *)malloc(item_count * sizeof(int));
    void * data_ptr = (void*)calloc(total_size, sizeof(char));
    if (item_size_ptr == NULL || data_ptr == NULL)
    {
        free(panbox);
        if (item_size_ptr != NULL)
        {
            free(item_size_ptr);
        }
        if (data_ptr != NULL)
        {
            free(data_ptr);
        }
        return NULL;
    }else
    {
        panbox->item_size = item_size_ptr;
        panbox->data = data_ptr;
    }

    // create items
    // int pos = 0;
    // int stored_size = 0;
    for (int i = 0; i < item_count; i++)
    {
        // stored_size = item_size[i];
        // myset((char *)panbox->data + pos, 0, stored_size); // @3:initialize
        panbox->item_size[i] = item_size[i];
        // pos += item_size[i];
    }
    return panbox;

}
/*
Function: Create an empty PandoraBox with specified item counts and their respective sizes.

Parameters:
- item_count: The number of items to be stored in the PandoraBox.
- item_size: An array specifying the size (in bytes) of each item.

Returns:
A pointer to the created PandoraBox.

Note:
- You CAN create a Panbox with no initial items, i.e., item_count=0 and item_size=NULL.@!
- However, (1)negative item_count is not supported, and (2)item_size should not be NULL when item_count is non-zero.@!
- The size of any item should be positive.@!
- Make sure that the memory newly allocated is filled with 0s.@!
- You should return NULL immediately if any failure happens.@!
- Good news: GuTao guarantees that [item_size, item_size+item_count-1] is allocated in advance, unless item_size is NULL.@!
*/

void append(Panbox *panbox, void *value, int width)
{
    // exception handling
    if (width <= 0 || value == NULL ||  isValidBox(panbox) == 0)
    {
        return;
    }
    // if is empty box
    if (isValidBox(panbox) == 2)
    {
        int * item_size_ptr = (int *)malloc(sizeof(int));
        void * data_ptr = (void *)malloc(width * sizeof(char));
        if (item_size_ptr == NULL || data_ptr == NULL)
        {
            
            if (item_size_ptr != NULL)
            {
                free(item_size_ptr);
            }
            if (data_ptr != NULL)
            {
                free(data_ptr);
            }
            return;
        }else
        {
            panbox->item_count = 1;
            panbox->item_size = item_size_ptr;
            panbox->data = data_ptr;
        }
        panbox->item_size[0] = width;
        mycpy(panbox->data, value, width);
        return;
    }
    
    // if not empty box, append to the end of the data
    size_t total_size = get_dataSize(panbox);
    // panbox->item_size = (int *)realloc(panbox->item_size, (panbox->item_count + 1) * sizeof(int));
    // panbox->data = (void *)realloc(panbox->data, (total_size + width) * sizeof(char));
    int * item_size_ptr = (int *)realloc(panbox->item_size, (panbox->item_count + 1) * sizeof(int));
    void * data_ptr = (void *)realloc(panbox->data, (total_size + width) * sizeof(char));
    if (item_size_ptr == NULL || data_ptr == NULL)
    {
        if (item_size_ptr != NULL)
        {
            // invert the change
            panbox->item_size = (int *)realloc(panbox->item_size, panbox->item_count * sizeof(int));
        }
        if (data_ptr != NULL)
        {
            // invert the change
            panbox->data = (void *)realloc(panbox->data, total_size * sizeof(char));
        }
        return;
    }else
    {
        panbox->item_size = item_size_ptr;
        panbox->data = data_ptr;
    }
    mycpy(panbox->data + total_size, value, width);
    panbox->item_count += 1;
    panbox->item_size[panbox->item_count - 1] = width;
    return;
}
/*
Function: Extend the memory of the PandoraBox to append an item.

Parameters:
- panbox: A pointer to the PandoraBox.
- value: A pointer to the data to be added to the PandoraBox.
- width: The size of the data in value (in bytes).

Note:
- You should not append this item if any failure happens.@
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
*/

void write(Panbox *panbox, int item_id, void *value, int width)
{
    // exception handling
    if (isValidBox(panbox) != 1)
    {
        return;
    }
    if (item_id>= panbox->item_count || item_id < 0 || width <= 0 || value == NULL)
    {
        return;
    }
    if (width > panbox->item_size[item_id])
    {
        return;
    }
    
    int pos = 0;
    int idx = 0;
    while (idx < item_id)
    {
        pos += panbox->item_size[idx++];
    }
    int pad_len = panbox->item_size[item_id] - width;
    int pad_byte = 0;
    int highest_bit;
    if (pad_len > 0)
    {
        highest_bit = *((char *)value + width - 1);
        pad_byte = (highest_bit & 0x80) ? 0xff : 0x00;
        // myset(panbox->data + pos, pad_byte, pad_len);
        myset(panbox->data + pos + width, pad_byte, pad_len);
    }
    // mycpy(panbox->data + pos + pad_len, value, width);
    mycpy(panbox->data + pos, value, width); 
    return;
}
/*
Function: COPY the data stored in 'value' into the segment of the item with index item_id in the PandoraBox.

Parameters:
- panbox: A pointer to the PandoraBox.
- item_id: The index of the item in the PandoraBox where data will be written.
- value: A pointer to the data that needs to be written to the PandoraBox.
- width: The size of the data in value (in bytes).

Notes:
- If 'item_id' is out of valid bounds, the data won't be written.@!
- If the item size cannot hold all data in value, the data won't be written.@!
- If the width of value is smaller than the item size, the data will be placed in the lower address and padded with the highest bit.@
- Example: inserting a 1-byte value into a 2-byte item: (0x7f -> 0x007f), (0xf7 -> 0xfff7).
- The item_size should not change in this function.@
- You should not write the item if any failure happens.@!
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.@!
*/

void *read(Panbox *panbox, int item_id)
{
    // exception handling
    if (isValidBox(panbox) != 1)
    {
        return NULL;
    }
    if (item_id>= panbox->item_count || item_id < 0)
    {
        return NULL;
    }
    // this should never happen
    if (panbox->item_size == NULL || panbox->data == NULL)
    {
        return NULL;
    }
    int size = panbox->item_size[item_id];
    int pos = 0;
    int idx = 0;
    while(idx < item_id)
    {
        pos += panbox->item_size[idx];
        idx += 1;
    
    }
    void *new_data = (void *)malloc(size * sizeof(char));
    if (new_data == NULL)
    {
        return NULL;
    }
    mycpy(new_data, panbox->data + pos, size);
    return new_data;
}
/*
Function: COPY@ the item with index item_id from the PandoraBox into a newly allocated memory, and return a pointer to
this memory.

Parameters:
- panbox: A pointer to the PandoraBox.
- item_id: The index of the item in the PandoraBox that should be read.

Returns:
A pointer to the newly allocated memory containing a copy of the specified item.

Notes:
- You should return NULL immediately if any failure happens.
*/

void destroy(Panbox *panbox)
{
    if (panbox == NULL)
    {
        return;
    }
    if (panbox->item_size != NULL)
    {
        free(panbox->item_size);
    }
    if (panbox->data != NULL)
    {
        free(panbox->data);
    }
    free(panbox);
    
    return;
}
/*
Function: Deallocate the memory associated with the PandoraBox and its data.

Parameters:
- panbox: A pointer to the PandoraBox that should be destroyed.

Notes:
- This function should be used when the PandoraBox is no longer needed to prevent memory leak.
- You should check before freeing a pointer.@
*/

void printc(void *value, int width)
{
    // exception handling
    if (width <= 0 || value == NULL)
    {
        return;
    }
    int print_anything = 0;
    int idx = 0;
    while (idx < width)
    {
        if (*((char *)value + idx) > 32 && *((char *)value + idx) != 127)
        {
            print_anything = 1;
            {
                printf("%c ",*((char *)value + idx));
            }         
        }else if (*((char *)value + idx) < 0)
        {
            print_anything = 1;
            printf("- ");
        }
        idx++;
    }
    if (print_anything == 1)
    {
        printf("\n");
    }
    
    
    return;
}
/*
Function: Print every 1 byte (char) in [value, value+width-1] as a character, split by a space.

Notes:
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
- If the value of the byte is in [0, 32] or equals to 127(Del), do not print anything(they are special characters).@!
- e.g., for an empty box with all 0, the destroy of this box will invoke printc(), but should not print anything.@
- If the value of the byte is negative, print '-' instead.@?!
- You should return immediately if any failure happens.@!!
- Please print a `\n` before returning, unless you print nothing in this function.!
*/

void printx(void *value, int width)
{
    // exception handling
    if ((value == NULL) || (width <= 0))
    {
        return;
    }
    printf("0x");
    while (width > 0)
    {
        unsigned char * temp = (unsigned char *)value + width - 1;
        printf("%02x", *temp);
        width -= 1;
    }
    printf("\n");
    
    
}
/*
Function: Print the value in [value, value+width-1] as a single hexadecimal, in format of 0x12345678.

Notes:
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
- You should return immediately if any failure happens.@
- If the highest byte is less than 0x10, please output a leading 0, e.g., 0x0514.@
- Leading zeros are OK, if *(value) = 0x000f, width = 2, then print 0x000f. (print even number of characters)@
- If the item is full of 0s, please still print it. E.g., 0x0000.
- Please print a `\n` before returning.@
*/

void hex2byte(void *dst, char *hex)
{
    // exception handling
    if (dst == NULL || hex == NULL)
    {
        return;
    }
    int hex_len = strlen(hex) - 2;
    // char hex_str[hex_len+1];
    char * hex_str = (char *)malloc((hex_len) * sizeof(char));
    if (hex_str == NULL)
    {
        return;
    }
    int byte_len = (hex_len + 1) / 2;
    void *byte_ptr = (void *)realloc(dst, byte_len * sizeof(char));
    if (byte_ptr == NULL)
    {
        free(hex_str);
        return;
    }else
    {
        dst = byte_ptr;
    }

    mycpy(hex_str, hex+2, hex_len); // remove the "0x" at the beginning, prepare a position for potential padding 0
    

    int ary_pointer = hex_len - 1 - 1; // *(hex_str + ary_pointer) is the -2th char in hex
    int byte_pointer = 0;
    while (ary_pointer >= 0 )
    {
        if (ary_pointer >= 0) // at least 2 hex left
        {
            sscanf(hex_str + ary_pointer, "%2hhx", (char *)dst + byte_pointer); // read 2 hex at a time
            ary_pointer -= 2;
            byte_pointer += 1;
        }else if (ary_pointer == 1) // only 1 hex left
        {
            sscanf(hex_str + ary_pointer, "%1hhx", (char *)dst + byte_pointer); // pad 0 at the beginning
            ary_pointer -= 2;
            byte_pointer += 1;
        }
    }
    free(hex_str);
    return;
    
}
/*
Function: For the given hex string "0x12345678", write 0x12345678 into dst.

Notes:
- The length of hex might be ODD, make sure to put all data into dst.@ For example, "0xfff"(12 bits) should be stored
using 2 bytes as 0x0fff(different from write(), just add a padding 0 here).
- You should return immediately if any failure happens.@
*/

/*=+=+=+=+=+=+=+=+=+=+=Your code ends here=+=+=+=+=+=+=+=+=+=+=*/

void show_info(Panbox *p)
{
    if (p != NULL)
    {
        printf("%d\n", p->item_count);
        for (int i = 0; i < p->item_count; i++)
        {
            printf("%d ", p->item_size[i]);
        }
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }
}
/*
Function: Display the basic information of given PandoraBox

Implemented by GuTao.
*/

Panbox *p = NULL;

int test1()
{
    int T;
    int command_idx = 0;
    scanf("%d", &T);
    while (T--)
    {
        char op;
        command_idx++;
        scanf(" %c", &op);
        // printf("Command %d: %c\n", ++command_idx, op);
        switch (op)
        {
        case 'C': {
            int item_count;
            scanf("%d", &item_count);
            int *item_size = (int *)malloc(item_count * sizeof(int));
            for (int i = 0; i < item_count; i++)
            {
                scanf("%d", &item_size[i]);
            }
            p = create(item_count, item_size);
            free(item_size);
            break;
        }
        case 'D': {
            if (p != NULL)
            {
                for (int i = p->item_count - 1; i >= 0; i--)
                {
                    void *data = read(p, i);
                    if (data != NULL)
                    {
                        printc(data, p->item_size[i]);
                        free(data);
                    }
                }
            }
            destroy(p);
            break;
        }
        case 'A': {
            int len;
            scanf("%d", &len);
            char *hex_str = (char *)malloc(len + 1);
            scanf("%s", hex_str);
            int num_of_byte = (strlen(hex_str) - 1) / 2;
            void *data = (void *)malloc(num_of_byte);
            hex2byte(data, hex_str);
            append(p, data, num_of_byte);
            free(hex_str);
            free(data);
            break;
        }
        case 'W': {
            int item_id;
            scanf("%d", &item_id);
            int len;
            scanf("%d", &len);
            char *hex_str = (char *)malloc(len + 1);
            scanf("%s", hex_str);
            int num_of_byte = (strlen(hex_str) - 1) / 2;
            void *data = (void *)malloc(num_of_byte);
            hex2byte(data, hex_str);
            write(p, item_id, data, num_of_byte);
            free(hex_str);
            free(data);
            break;
        }
        case 'R': {
            int item_id;
            scanf("%d", &item_id);
            int is_printc;
            scanf("%d", &is_printc);
            void *data = read(p, item_id);
            if (data != NULL)
            {
                if (is_printc)
                {
                    printc(data, p->item_size[item_id]);
                }
                else
                {
                    printx(data, p->item_size[item_id]);
                }
                free(data);
            }
            break;
        }
        case 'Q': {
            show_info(p);
            break;
        }
        default: {
            break;
        }
        }
    }
    return 0;
}

/*
Main function implemented by GuTao, you cannot rewrite one for yourself.

- Just for you to understand how the functions you implement would be invoked.
- Not exact the main function to test on OJ, this one does not check your error handling.
- You can test your functions on your PC with your own main().
- You may want to hack with your own main function, but this won't help you AC :)
*/
void testP(Panbox *p)
{
    char * inhex = "0x12345678f1add930ad90";
    int hex_len = strlen(inhex);
    int item_id;
    int num_of_byte = (hex_len - 1) / 2;
    void *data = (void *)malloc(num_of_byte);
    hex2byte(data, inhex);
    append(p, data, num_of_byte);
    append(p, NULL, num_of_byte);
    append(p, data, 0);
    append(p, data, -1);

    write(p, 0, data, num_of_byte);
    write(p, 100, data, num_of_byte);
    write(p, 2, data, 0);
    write(p, 2, NULL, 0);
    write(p, 2, data, -1);

    void * readin = read(p, 0);
    printc(readin, num_of_byte);
    printx(readin, num_of_byte);
    readin = read(p, 100);
    printc(readin, num_of_byte);
    printx(readin, num_of_byte);
    readin = read(p, 2);
    printc(readin, 0);
    printx(readin, 0);
    readin = read(p, -1);
    printc(readin, 0);
    printx(readin, 1);
    printc(readin, -1);

    destroy(p);
}


int test2()
{
    Panbox *p = NULL;
    testP(p);
    Panbox *p2 = create(0, NULL);
    testP(p2);
    int item_size[3] = {1, 2, 3};
    Panbox *p3 = create(3, item_size);
    testP(p3);
    int item_size2[3] = {1, 2, -3};
    Panbox *p4 = create(3, item_size2);
    testP(p4);
    return 0;
}

int main()
{
    // test1();
    test2();
    return 0;
}