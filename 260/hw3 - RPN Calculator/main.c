#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "regex.h"

extern int *stack_root;
extern int *stack_pointer;
extern int pop(int *value);
extern int push(int value);
extern int scanpush(const char *input);
extern int add_integer();
extern int subtract_integer();
extern int multiply_integer();
extern int divide_integer();
extern int rpncalculate(const char *input);

void print_stack() {
    printf("Stack pointer: %p\n", stack_pointer);
    printf("Stack: %p\n", stack_root);
    printf("Stack: ");
    for (int i = 0; i < stack_pointer - stack_root; i++) {
        printf("%d ", stack_root[i]);
    }
    printf("\n");
}

void test_scanpush() {
    const char *input = "12 3";
    int ret = scanpush(input);
    if (ret != 1) {
        printf("[FAILED]: scanpush(\"%s\") = %d, expected 1\n", input, ret);
    } else {
        printf("[SUCCESS]: scanpush(\"%s\") = 1\n", input);
    }
    int pop_ret = 0;
    if (pop(&pop_ret) != 1 || pop_ret != 12) {
        printf("[FAILED]: pop() = 12, expected 12\n");
    } else {
        printf("[SUCCESS]: pop() = 12\n");
    }

    const char *input2 = input + 3;
    ret = scanpush(input2);
    if (ret != 1) {
        printf("[FAILED]: scanpush(\"%s\") = %d, expected 1\n", input2, ret);
    } else {
        printf("[SUCCESS]: scanpush(\"%s\") = 1\n", input2);
    }
    if (pop(&pop_ret) != 1 || pop_ret != 3) {
        printf("[FAILED]: pop() = 3, expected 3\n");
    } else {
        printf("[SUCCESS]: pop() = 3\n");
    }
}

void test_stack() {
    int pop_ret = 0;
    if (pop(&pop_ret) != 0) {
        printf("[FAILED]: pop() != 0, expected 0\n");
    } else {
        printf("[SUCCESS]: pop() = 0\n");
    }

    int ret = push(1);
    if (ret != 1) {
        printf("[FAILED]: push(1) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(1)\n");
    }

    ret = push(2);
    if (ret != 1) {
        printf("[FAILED]: push(2) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(2)\n");
    }

    ret = push(3);
    if (ret != 1) {
        printf("[FAILED]: push(3) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(3)\n");
    }

    if (pop(&pop_ret) != 1 || pop_ret != 3) {
        printf("[FAILED]: pop() != 3, expected 3\n");
    } else {
        printf("[SUCCESS]: pop() = 3\n");
    }
    if (pop(&pop_ret) != 1 || pop_ret != 2) {
        printf("[FAILED]: pop() != 2, expected 2\n");
    } else {
        printf("[SUCCESS]: pop() = 2\n");
    }
    if (pop(&pop_ret) != 1 || pop_ret != 1) {
        printf("[FAILED]: pop() != 1, expected 1\n");
    } else {
        printf("[SUCCESS]: pop() = 1\n");
    }
}

void test_print_stack(){
    print_stack();

    int ret = push(1);
    if (ret != 1) {
        printf("[FAILED]: push(1) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(1)\n");
    }

    print_stack();

    ret = push(2);
    if (ret != 1) {
        printf("[FAILED]: push(2) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(2)\n");
    }

    print_stack();

    ret = push(3);
    if (ret != 1) {
        printf("[FAILED]: push(3) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(3)\n");
    }

    print_stack();
}

void test_add_integer() {
    int ret = push(1);
    if (ret != 1) {
        printf("[FAILED]: push(1) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(1)\n");
    }

    ret = push(2);
    if (ret != 1) {
        printf("[FAILED]: push(2) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(2)\n");
    }

    ret = add_integer();
    if (ret != 1) {
        printf("[FAILED]: add_integer() = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: add_integer()\n");
    }

    int pop_ret = 0;
    if (pop(&pop_ret) != 1 || pop_ret != 3) {
        printf("[FAILED]: pop() = 3, expected 3\n");
    } else {
        printf("[SUCCESS]: pop() = 3\n");
    }
}

void test_subtract_integer() {
    int ret = push(1);
    if (ret != 1) {
        printf("[FAILED]: push(1) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(1)\n");
    }

    ret = push(2);
    if (ret != 1) {
        printf("[FAILED]: push(2) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(2)\n");
    }

    ret = subtract_integer();
    if (ret != 1) {
        printf("[FAILED]: subtract_integer() = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: subtract_integer()\n");
    }

    int pop_ret = 0;
    if (pop(&pop_ret) != 1 || pop_ret != -1) {
        printf("[FAILED]: pop() = -1, expected -1\n");
    } else {
        printf("[SUCCESS]: pop() = -1\n");
    }
}

void test_multiply_integer() {
    int ret = push(1);
    if (ret != 1) {
        printf("[FAILED]: push(1) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(1)\n");
    }

    ret = push(2);
    if (ret != 1) {
        printf("[FAILED]: push(2) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(2)\n");
    }

    ret = multiply_integer();
    if (ret != 1) {
        printf("[FAILED]: multiply_integer() = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: multiply_integer()\n");
    }

    int pop_ret = 0;
    if (pop(&pop_ret) != 1 || pop_ret != 2) {
        printf("[FAILED]: pop() != 2, expected 2\n");
    } else {
        printf("[SUCCESS]: pop() = 2\n");
    }
}

void test_divide_integer() {
    int ret = push(1);
    if (ret != 1) {
        printf("[FAILED]: push(1) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(1)\n");
    }

    ret = push(2);
    if (ret != 1) {
        printf("[FAILED]: push(2) = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: push(2)\n");
    }

    ret = divide_integer();
    if (ret != 1) {
        printf("[FAILED]: divide_integer() = %d, expected 0\n", ret);
    } else {
        printf("[SUCCESS]: divide_integer()\n");
    }

    int pop_ret = 0;
    if (pop(&pop_ret) != 1 || pop_ret != 0) {
        printf("[FAILED]: pop() != 0, expected 0\n");
    } else {
        printf("[SUCCESS]: pop() = 0\n");
    }
}

void test_rpncalculate(const char *input, int expected_ret) {
    int ret = rpncalculate(input);
    if (ret != expected_ret) {
        printf("[FAILED]: rpncalculate(\"%s\") = %d, expected %d\n", input, ret, expected_ret);
    } else {
        printf("[SUCCESS]: rpncalculate(\"%s\") = %d\n", input, ret);
    }
}

int main(int argc, char *argv[]) {
    int pop_ret = 0;
    test_stack();
    test_print_stack();
    test_add_integer();
    test_subtract_integer();
    test_multiply_integer();
    test_divide_integer();
    test_scanpush();
    // clean up the stack from testing it.
    pop(&pop_ret);
    pop(&pop_ret);
    pop(&pop_ret);

    test_rpncalculate("1\0", 1);
    test_rpncalculate("2\0", 2);
    //test_rpncalculate("11 2", 2);
    test_rpncalculate("1 2\0", 2);
    // clean up the stack from testing it.
    pop(&pop_ret);
    test_rpncalculate("\0", 0);
    test_rpncalculate("1 2 +\0", 3);
    test_rpncalculate("1 2 -\0", -1);
    test_rpncalculate("1 2 *\0", 2);
    test_rpncalculate("1 2 /\0", 0);

    // do some more complex tests
    test_rpncalculate("1 2 3 + +\0", 6);
    test_rpncalculate("1 2 3 + -\0", -4);
    test_rpncalculate("1 2 3 + *\0", 5);
    test_rpncalculate("1 2 3 + /\0", 0);
    test_rpncalculate("1 2 3 - +\0", 0);

    // do some more complex tests
    test_rpncalculate("3 4 - 5 +\0", 4);
    test_rpncalculate("3 4 + 5 6 + *\0", 77);
    test_rpncalculate("3 4 - 5 6 - *\0", 1);
    test_rpncalculate("1024 2 /\0", 512);

    return 0;
}
