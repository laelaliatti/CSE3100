#include <stdio.h>

int main() {
    int number, first_digit;

    printf("Enter an integer: ");
    // Use %d for decimal input
    scanf("%d", &number); 

    // Handle negative numbers by using the absolute value
    if (number < 0) {
        number = -number;
    }
    
    // Check for the special case of 0
    if (number == 0) {
        first_digit = 0;
    } else {
        first_digit = number; // Start with the original number
        // Repeatedly divide by 10 until only the first digit remains
        while (first_digit >= 10) {
            first_digit /= 10;
        }
    }

    printf("The first digit is: %d\n", first_digit);

    return 0;
}