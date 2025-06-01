.text
.global subtract_integer
.ent subtract_integer
.type subtract_integer, @function
# subtract_integer - pops two integers off the stack, subtracts them, and pushes the result onto the stack
# $v0 is the number of values pushed onto the stack
subtract_integer:
    .frame $fp, 24, $ra
    # Save the return address
    addi $sp, $sp, -24
    sw $ra, 20($sp)
    sw $fp, 16($sp)
    move $fp, $sp
    .cprestore 4

# This code takes two values off the stack and subtracts them 
    # before storing a single value back on the stack.
# checks every function call to make sure it was a succesful call

    addi $v0, $zero, 0

    sw $a0, 8($sp)
    addi $a0, $sp, 12 #a0 stores into 12 for this functions stack frame

    jal pop
        lw $s0, 12($sp)
    beq $v0, $zero, done_sub #
    
    jal pop
        lw $s1, 12($sp)
    beq $v0, $zero, done_sub #

    sub $a0, $s1, $s0

    jal push
    beq $v0, $zero, done_sub #

    addi $v0, $zero, 1

done_sub:
    lw $a0, 8($sp)

# it pushes a value onto the stack, but returns an address in a0 when exiting.
# returns 0 if subtraction was unsuccesful, 1 if it was.

subtract_integer_exit:
    # exit the function restoring the stack frame
    move $sp, $fp
    lw $ra, 20($sp)
    lw $fp, 16($sp)
    addi $sp, $sp, 24
    j $ra
.end subtract_integer
