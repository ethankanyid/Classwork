#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "regex.h"

extern int piglatin(const char *input, char *output);

void test_piglatin(const char *input, const char *expected, int expected_ret) {
    char output[100];
    memset(output, 0, sizeof(output));
    int ret = piglatin(input, output);
    if (ret != expected_ret) {
        printf("[FAILED] piglatin(%s) = %s return value %d\n", input, output, ret);
    } else if (strcmp(output, expected) != 0) {
        printf("[FAILED] piglatin(%s) = %s return value %d\n", input, output, ret);
    } else {
        printf("[PASSED] piglatin(%s) = %s return value %d\n", input, output, ret);
    }
}

int main(int argc, char *argv[]) {
    test_piglatin("\0", "\0", -1);
    test_piglatin("hello", "ellohay", 0);
    test_piglatin("world", "orldway", 0);
    test_piglatin("apple", "appleway", 0);
    test_piglatin("banana", "ananabay", 0);
    test_piglatin("cherry", "errychay", 0);
    test_piglatin("eat", "eatway", 0);
    test_piglatin("omelet", "omeletway", 0);
    test_piglatin("under", "underway", 0);
    test_piglatin("the", "ethay", 0);
    return 0;
}
