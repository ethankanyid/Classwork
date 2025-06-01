# MIPS Assembly

Consider the following questions read the instructions carefully.

## Hexidecimal Basics. (5 Points)

Test your understanding of hexadecimal.

1. How many symbols are used in hexadecimal?

16

1. What are all the symbols used in hexadecimal?

0-9 and a,b,c,d,e,f 

1. Convert all the hexadecimal symbols to decimal. (Put your answers into a [table](https://docs.gitlab.com/ee/user/markdown.html#tables))

    | Hexadecimal Symbol | Decimal Value |
    | --- | --- |
    | 0 | 0 |
    |1   |1 |
    |2   |2|
    |3   |3|
    |4   |4|
    |5   |5|
    |6   |6|
    |7   |7|
    |8   |8|
    |9   |9|
    |a   |10|
    |b   |11|
    |c   |12 |
    |d   |13|
    |e   |14|
    |f   |15|


## Convert MIPS Assembly to C code. (20 Points)

1. Convert the following assembly to a single C statement.

    ```
    addi $t0, $s0, -3
    sll $t1, $t0, 3
    addi $t0, $s0, 4
    add $s1, $t0, $t1
    ```
    ```
    # answer:
    $s1 = ($s0 +4) + (($s0 + (-3)) * 8);
    ```

1. Consider the register value for `$s0` is 4. What's the value of `$s1` after the instructions?

16

1. Convert the following assembly to a single C statement.

    ```
    addi $t0, $s0, 0
    addi $t1, $zero, 1
    or   $t3, $t1, $t0
    slt  $s1, $t0, $t3
    ```
    ```
    # answer:
    $s1 = ($t0 < ($s0 + 0) | (0 + 1)) ? 1 : 0;
    ```
1. Consider the register value for `$s0` is 4. What's the value of `$s1` after the instructions?

1

## Convert the C code to MIPS Assembly. (20 Points)

1. Convert the C statement into a set of commented MIPS assembly code.

    ```
    b[i-2] = a[i+1] + a[4];
    ```

    Assume `$s0` contains the address of the array a, `$s1` contains the address
    of the array b, and `$s2` contains the integer variable i. Use the `$t*` 
    registers for temporary storage, if you need any. All variables and arrays are
    integers.

    ```
    # answer:
    
    subi $t0, $s2, 2     # t0 = i-2
    sll $t0, $t0, 2     # byte offset
    add $t0, $t0, $s1   # address of b[i-2]

    addi $t1, $s2, 1     # t1 = i+1
    sll $t1, $t1, 2     # byte offset
    add $t1, $t1, $s0   # address of a[i+1]

    lw $t1, 0($t1)      # t1 = a[1+1]
    sll $t2, $s0, 5     # address of a[4]
    lw $t2, 0($t2)      # t3 = a[4]

    add $t3, $t1, $t2   # t3 = a[i+1] + a[4]
    sw $t3, 0($t0)      # t3 is stored in b[i-2]
    ```


1. Convert the C statement into a set of commented MIPS assembly code.

    ```
    x = ((b << 2) - 1) < a ? 1 : 0
    ```

    Assume `$s0` is b, `$s1` is a and `$v0` is x.

    ```
    # answer:

    addi $t0, $0, 1     # creates temp for 1
    sll $s0, $s0, 2     # shifts b 2 to the left
    addi $s0, $s0, -1    # subs -1 from b
    slt $t1, $s0, $s1   # compares b and a and stores result in t1
    beq $t1, $0, else   # if t0 is 0 than b is greater than a; jumps to else
    addi $v0, $0, 1      # b is less than a, set x = 1
else:
    addi $v0, $0, 0      # b is greater than a, x = 0
    ```



## High-Level Code and MIPS Assembly. (30 Points)

1. Convert the following MIPS assembly into C code and describe what it does.

    ```
    addi $t0, 0, 5          # i
    addi $t1, 0, 1          # x
    loop:                   # for loop
    beq $t0, $zero, done    # expression
    mul $t1, $t1, $t0       # body
    addi $t0, $t0, -1       # decrement
    j loop                  # for loop
    done:
    addi $v0, $t1, 0        # stores value in function variable
    ```

    ```
    # answer:
    int x = 1;                      # decalares and intitalizes x to 1

    for (int i = 5; i != 0; i--)    # a for loop that declares and intializes i to 5  
    {
        x *= i;                     # x is multiplied with i and stored in x
    }                               # loops until i = 0 including subtracting 1 from i each time
    return x;                       # stores x in the function return variable; this would also return to the callee which was not declared in the assembly code
    ```

1. Convert the following MIPS assembly into C code and describe what it does.

    ```
    li $t0, $a0             # loads immediate $a0 into temp (array address)
    li $t1, 0               # sets t1 to 0
    li $t2, 5               # sets t2 to 5
    li $t3, 0               # sets t3 to 0
    loop:                   # for loop
    beq $t3, $t2, done      # expression
    lw $t4, 0($t0)          # loads address value of array into t4
    add $t1, $t1, $t4       # adds t1 with t4 and stores in t1
    addi $t0, $t0, 4        # adds 4 to base address t0
    addi $t3, $t3, 1        # increments t3 by 1
    j loop                  # jumps to loop
    done:                   # exit from loop
    li $v0, $t1             # loads t1 into function return variable
    ```

    ```
    # answer:
    int x[5];                             # delcares array size 5
    int y = 0;                            # decalres y and initializes to 0

    for (int i = 0; i < 5; i ++)          # loops until i = 5 including incrementing i by 1
    {
        y += x[i];                        # adds y and the ith position of x array and stores in y
    }
    return y;                             # returns y (and returns to the callee)
    ```


