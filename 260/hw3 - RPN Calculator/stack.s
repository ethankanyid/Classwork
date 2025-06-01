.data
# Define the size of the stack
STACK_SIZE: .word 1024
# Allocate space for the stack
stack: .space 1024

# Global stack pointer
.global stack_pointer
stack_pointer: .word stack
# Global stack root
.global stack_root
stack_root: .word stack


.text
.global push
.ent push
.type push, @function
# push - pushes a value onto the stack
# $a0 is the value to push
# $v0 the number of values pushed onto the stack
push:
    .frame $fp, 20, $ra
    # Save the return address
    addi $sp, $sp, -20
    sw $ra, 16($sp)
    sw $fp, 12($sp)
    move $fp, $sp
    .cprestore 4

# This function takes a value from a0 and pushes it onto the stack

    addi $v0, $zero, 0

    lw $t1, stack_pointer
    addi $t1, $t1, 4 # increment before storing
    sw $a0, 0($t1)
    sw $t1, stack_pointer

    addi $v0, $zero, 1

# This function returns 1 upon success, and 0 upon failure

exit_push:
    # exit the function restoring the stack frame
    move $sp, $fp
    lw $ra, 16($sp)
    lw $fp, 12($sp)
    addi $sp, $sp, 20
    j $ra
.end push

.global pop
.ent pop
.type pop, @function
# pop - pops a value from the stack
# $a0 is the value popped off the stack
pop:
    .frame $fp, 20, $ra
    # Save the return address
    addi $sp, $sp, -20
    sw $ra, 16($sp)
    sw $fp, 12($sp)
    move $fp, $sp
    .cprestore 4

# This function takes a value off the stack and stores it in address pointed to by a0

    addi $v0, $zero, 0

    lw $t0, stack_pointer
    lw $t1, stack_root
    beq $t0, $t1, exit_pop  # check for bottom of stack

    lw $t2, 0($t0)
    addi $t0, $t0, -4 # decrement after loading
    sw $t0, stack_pointer
    sw $t2, 0($a0) 

    addi $v0, $zero, 1

# This function returns 1 upon success, and 0 upon failure
    
exit_pop:
    # exit the function restoring the stack frame
    move $sp, $fp
    lw $ra, 16($sp)
    lw $fp, 12($sp)
    addi $sp, $sp, 20
    j $ra
.end pop
