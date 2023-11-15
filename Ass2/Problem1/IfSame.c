#include <stdio.h>  
#include <stdlib.h>

// for given 2 text files, compare if they are the same
// if not the same, output the number of lines that are different
// ignore the any blank in lines

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char ch1, ch2;
    int line = 1, col = 1, diff = 0;
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        exit(1);
    }
    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        printf("Cannot open %s\n", argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        printf("Cannot open %s\n", argv[2]);
        exit(1);
    }
    while (1) {
        ch1 = fgetc(fp1);
        ch2 = fgetc(fp2);
        if (ch1 == EOF || ch2 == EOF) {
            break;
        }
        if (ch1 == '\n') {
            line++;
            col = 1;
        }
        if (ch1 == ' ') {
            col++;
            continue;
        }
        if (ch1 != ch2) {
            diff++;
            printf("Line %d, col %d: %c - %c\n", line, col, ch1, ch2);
        }
        col++;
    }
    if (ch1 != EOF || ch2 != EOF) {
        printf("The two files have different length\n");
    } else if (diff == 0) {
        printf("The two files are the same\n");
    } else {
        printf("The two files have %d different characters\n", diff);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
