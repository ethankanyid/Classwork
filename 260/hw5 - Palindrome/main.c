#include "stdio.h"
#include "stdlib.h"
#include "time.h"

extern int set_number(int number);
extern int guess(int upperbound, int lowerbound);
extern int palindrome(char *str);

void test_guess(int upperbound) {
    int number = rand() % upperbound;
    set_number(number);
    int your_guess = guess(upperbound, 0);
    if (your_guess == number) {
        printf("[SUCCESS] Correct the number is %d\n", number);
    } else {
        printf("[FAILURE] Incorrect the number is %d but you guessed %d\n", number, your_guess);
    }
}

void test_palindrome(char *str, int expected) {
    int result = palindrome(str);
    if (result == expected) {
        printf("[SUCCESS] %s is %s\n", str, expected ? "palindrome" : "not palindrome");
    } else {
        printf("[FAILURE] %s is %s but you returned %s\n", str, expected ? "palindrome" : "not palindrome", result ? "palindrome" : "not palindrome");
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    test_guess(10);
    test_guess(100);
    test_guess(1000);
    test_guess(10000);
    test_guess(100000);
    test_guess(1000000);
    test_guess(10000000);

    test_palindrome("racecar", 1);
    test_palindrome("hello", 0);
    test_palindrome("world", 0);
    test_palindrome("madam", 1);
    test_palindrome("hello world", 0);
    test_palindrome("a", 1);
    test_palindrome("", 1);
    return 0;
}
