.text
.global divide_integer
.ent divide_integer
.type divide_integer, @function
# divide_integer - pops two integers off the stack, divides them, and pushes the result onto the stack
# $v0 is the number of values pushed onto the stack
divide_integer:
    .frame $fp, 24, $ra
    # Save the return address
    addi $sp, $sp, -24
    sw $ra, 20($sp)
    sw $fp, 16($sp)
    move $fp, $sp
    .cprestore 4

# This code takes two values off the stack and divides them 
    # before storing a single value back on the stack.
# checks every function call to make sure it was a succesful call

    addi $v0, $zero, 0

    sw $a0, 8($sp)
    addi $a0, $sp, 12 #a0 stores into 12 for this functions stack frame

    jal pop
        lw $s0, 12($sp)
    beq $v0, $zero, done_div #
    jal pop
        lw $s1, 12($sp)
    beq $v0, $zero, done_div #

    beq $s0, $zero, done_div    # checks divide by zero

    div $s1, $s0 # quotient is stored in lo; remainder is stored in hi
    mflo $t0
    mfhi $t1
    add $a0, $t0, $zero

    jal push
beq $v0, $zero, done_div #

    addi $v0, $zero, 1

done_div:

    lw $a0, 8($sp)

# it pushes a value onto the stack, but returns an address in a0 when exiting.
# returns 0 if division was unsuccesful, 1 if it was.

divide_integer_exit:
    # exit the function restoring the stack frame
    move $sp, $fp
    lw $fp, 16($sp)
    lw $ra, 20($sp)
    addi $sp, $sp, 24
    j $ra
.end divide_integer
