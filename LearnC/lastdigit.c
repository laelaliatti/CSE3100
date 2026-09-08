#include <stdio.h>

int main() {
    int number, lastDigit;

    printf("Please Enter any Number: ");
    scanf("%d", &number);

    // Use the modulo operator to get the remainder when divided by 10
    lastDigit = number % 10;

    printf("The Last Digit of a Given Number %d = %d\n", number, lastDigit);

    return 0;
}