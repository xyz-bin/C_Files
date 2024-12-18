#include <stdio.h>

int main() {
    // Initialize variables for Fibonacci sequence
    int first = 0, second = 1, next;

    printf("Fibonacci numbers between 0 and 50:\n");

    // Print the first Fibonacci number
    printf("%d\n", first);

    // Continue generating Fibonacci numbers
    while (second <= 50) {
        printf("%d\n", second);
        next = first + second; // Calculate the next number in the sequence
        first = second;        // Update 'first' to the current 'second'
        second = next;         // Update 'second' to the newly calculated 'next'
    }

    return 0;
}
