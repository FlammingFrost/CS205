#include<stdio.h>

int Add(int num1, int num2);
int Subtract(int num1, int num2);
int Multiply(int num1, int num2);
int Divide(int num1, int num2);
int Modulus(int num1, int num2);
void PrintMenu();

int main()
{
    int choice;
    int num1, num2;

    // GUI initialization
    PrintMenu();

    while (1)
    {
        printf("Enter your choice(1~5): ");
        scanf("%d", &choice);

        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Result: %d\n", Add(num1, num2));
            break;
        case 2:
            printf("Result: %d\n", Subtract(num1, num2));
            break;
        case 3:
            printf("Result: %d\n", Multiply(num1, num2));
            break;
        case 4:
            printf("Result: %d\n", Divide(num1, num2));
            break;
        case 5:
            printf("Result: %d\n", Modulus(num1, num2));
            break;
        }

        char c;
        printf("Press 'y' or 'Y' to continue:");
        scanf(" %c", &c);
        if(!(c == 'y' || c == 'Y'))
        {
            printf("Done!\n");
            break;
        }
    }
    return 0;
    
}


int Add(int num1, int num2) {
    return num1 + num2;
}

int Subtract(int num1, int num2) {
    return num1 - num2;
}

int Multiply(int num1, int num2) {
    return num1 * num2;
}

int Divide(int num1, int num2) {
    return num1 / num2;
}

int Modulus(int num1, int num2) {
    return num1 % num2;
}

void PrintMenu()
{
    printf("====================================\n");
    printf("               MENU                \n");
    printf("====================================\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("====================================\n");
}