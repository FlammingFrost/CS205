# include <stdio.h>

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



void *mycpy(void *dst, const void *src, size_t size)
{
    // Lifan: copy (size) bytes from (src) to (dst)
    dst = (void *)realloc(dst, size * sizeof(char));
    while (--size >= 0)
    {
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
    }else
    {
        dst = (void *)realloc(dst, size * sizeof(char));
        while (--size >= 0)
        {
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
        emptybox->item_count = item_count;
        emptybox->item_size = NULL; // @2:N
        emptybox->data = NULL; // @3:N
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
            total_size += item_count;
        }
    }    

    // When comes here, every argument is valid

    // create a Panbox
    Panbox *panbox = (Panbox *)malloc(sizeof(Panbox)); // @1:creat
    panbox->item_count = item_count;
    panbox->item_size = (int *)malloc(item_count * sizeof(int)); // @2:creat
    panbox->data = (void*)malloc(total_size * sizeof(char)); // @3:creat

    // create items
    int pos = 0;
    int stored_size = 0;
    for (int i = 0; i < item_count; i++)
    {
        myset(panbox->data + pos, 0, stored_size); // @3:initialize
        *(panbox->item_size + i) = item_size[i]; // @2:assign
        pos += item_size[i];
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
    if (width <= 0 || value == NULL || panbox == NULL)
    {
        return;
    }
    // if is empty box
    if (panbox->item_size == NULL && panbox->data == NULL)
    {
        panbox->item_size = (int *)malloc(sizeof(int));
        panbox->data = (void *)malloc(width * sizeof(char));
        *(panbox->item_size) = width;
        mycpy(panbox->data, value, width);
        return;
    }
    
    // if not empty box, append to the end of the data
    int total_size = 0;
    for(int i = 0; i < panbox->item_count; i++)
    {
        total_size += panbox->item_size[i];
    }
    panbox->data = (void *)realloc(panbox->data, (total_size + width) * sizeof(char));
    mycpy(panbox->data + total_size, value, width);    
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
    if (item_id>= panbox->item_count || item_id < 0 || width <= 0 || value == NULL || panbox == NULL)
    {
        return;
    }
    if (width > panbox->item_size[item_id])
    {
        return;
    }
    
    int pos = 0;
    while (item_id-- > 0)
    {
        pos += panbox->item_size[item_id];
    }
    int pad_len = panbox->item_size[item_id] - width;
    int pad_byte = 0;
    if (pad_len > 0)
    {
        pad_byte = ((((char *)value + width - 1))[-1] & 0x80) ? 0xff : 0x00;
    }
    myset(panbox->data + pos, pad_byte, pad_len);
    mycpy(panbox->data + pos + pad_len, value, width);
    
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
    if (item_id>= panbox->item_count || item_id < 0 || panbox == NULL)
    {
        return NULL;
    }
    int size = panbox->item_size[item_id];
    int pos = 0;
    while(item_id-- > 0)
    {
        pos += panbox->item_size[item_id];
    }
    void *new_data = (void *)malloc(size * sizeof(char));
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
    free(panbox->item_size);
    free(panbox->data);
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
    while (width-- > 0)
    {
        if (*((char *)value + width) > 32 && *((char *)value + width) != 127)
        {
            if (print_anything==0)
            {
                print_anything = 1;
            }else
            {
                printf(" ");
            }
            
            if (*((char *)value + width) > 127)
            {
                printf("-");
            }else
            {
                printf("%c",*((char *)value + width));
            }         
        }
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
    while (width-- > 0)
    {
        printf("%02x", *((char *)value + width));
    }
    
    
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
    char hex_str[hex_len+1];
    char * beg_of_hex = hex_str+1;
    int char_len;
    mycpy(beg_of_hex, hex+2, hex_len); // remove the "0x" at the beginning, prepare a position for potential padding 0
    if (hex_len % 2 == 1)
    {
        hex_str[0] = '0';
        beg_of_hex = hex_str;
        char_len = (hex_len + 1) / 2;
    }else
    {
        char_len = hex_len / 2;
    }
    char * ptr = beg_of_hex;
    while (char_len-- > 0)
    {
        sscanf(ptr, "%2hhx", (char *)dst + char_len);
        ptr += 2;
    }
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

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        char op;
        scanf(" %c", &op);
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