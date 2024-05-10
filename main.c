#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *dig; // array for storing a number
    int n;     // the number of digits of the number in base 100
    char sign; // the sign of the number
} LongN;

void convertToLongN(char *s, LongN *num) {
    int flag = 0;
    int n = strlen(s);
    num->n = 0;
    num->sign = '+';

    // Determine sign and update n
    if (s[0] == '-' || s[0] == '+') {
        num->sign = s[0];
        flag = 1;
        n--;
    }

    // Calculate number of digits
    num->n = (n + 1) / 2;

    // Allocate memory for the digit array
    num->dig = malloc(num->n * sizeof(char));

    // Convert string to long number in reverse order
    int i = strlen(s) - 1, j = 0;
    while (i >= flag) {
        if (i - 1 >= flag && isdigit(s[i - 1])) {
            num->dig[j] = (s[i - 1] - '0') * 10 + (s[i] - '0');
            i -= 2;
        } else {
            num->dig[j] = (s[i] - '0');
            i--;
        }
        j++;
    }
}

LongN getLongN(char *s) {
    LongN num;
    convertToLongN(s, &num);
    return num;
}

void printLongN(LongN num) {
    printf("%c ", num.sign);
    for (int i = num.n - 1; i >= 0; i--) {
        printf("%d ", num.dig[i]);
    }
    printf("\n");
}

void releaseLongN(LongN num) {
    free(num.dig);
}

int main() {
    char input[201];
    printf("Enter a string of numbers: ");
    fgets(input, 200, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character from input

    LongN longNumber = getLongN(input);
    printLongN(longNumber);
    releaseLongN(longNumber);

    return 0;
}