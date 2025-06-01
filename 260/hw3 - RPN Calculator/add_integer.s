.text
.global add_integer
.ent add_integer
.type add_integer, @function
# add_integer - pops two integers off the stack, adds them, and pushes the result onto the stack
# $v0 is the number of values pushed onto the stack
add_integer:
    .frame $fp, 24, $ra
    # Save the return address
    addi $sp, $sp, -24
    sw $ra, 20($sp)
    sw $fp, 16($sp)
    move $fp, $sp
    .cprestore 4

# This code takes two values off the stack and adds them 
    # before storing a single value back on the stack.
# checks every function call to make sure it was a succesful call

    addi $v0, $zero, 0

    sw $a0, 8($sp)
    addi $a0, $sp, 12 #a0 stores into 12 for this functions stack frame

    jal pop
        lw $s0, 12($sp)
    beq $v0, $zero, done_add #
    
    jal pop
        lw $s1, 12($sp)
    beq $v0, $zero, done_add #

    add $a0, $s1, $s0

    jal push
    beq $v0, $zero, done_add #

    addi $v0, $zero, 1

done_add:
    lw $a0, 8($sp)

# it pushes a value onto the stack, but returns an address in a0 when exiting.
# returns 0 if addition was unsuccesful, 1 if it was.

add_integer_exit:
    # exit the function restoring the stack frame
    move $sp, $fp
    lw $fp, 16($sp)
    lw $ra, 20($sp)
    addi $sp, $sp, 24
    j $ra
.end add_integer
