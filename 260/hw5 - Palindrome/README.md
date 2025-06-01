# Homework 5 - Guessing and Checking

## Guessing Numbers (40 Points)

The number guessing game is implemented in functions 
`int guess(int, int)` in `guess.s` and two other functions
`void set_number(int)` and `int check_guess(int)` in `check_guess.s`.

1. Implement `void set_number(int)` by setting the global variable 
`number` to the passed value.
1. Implement `int check_guess(int)` by checking if the first argument is
equal to the global variable `number`. If the first argument is equal
return 0. If the first argument is less than return -1. If the first
argument is greater than return 1.
1. Implement `int guess(int, int)` by iterating over the upper and lower
bounds checking the guess by calling `int check_guess(int)`.

Extra Credit (5 Points): Implement `int guess(int, int)` by using a
binary search algorithm.

## Palindrome Check (30 Points)

In `palindrome.s` implement the function `int palindrome(char *)` that 
checks if the input string is a palindrome. If the string is a 
palindrome the function will return 1 otherwise return 0.

- https://en.wikipedia.org/wiki/Palindrome