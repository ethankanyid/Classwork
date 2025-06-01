.text
.global rpncalculate
.ent rpncalculate
.type rpncalculate, @function
# rpncalculate - reads a string of numbers and operators in reverse polish notation and returns the result
# $a0 is the address of the rpn string
# $v0 is the result of the calculation
rpncalculate:
    .frame $fp, 24, $ra
    # save the return address
    addi $sp, $sp, -24
    sw $ra, 20($sp) 
    sw $fp, 16($sp)
    move $fp, $sp
    .cprestore 4

# This function acts as a main for the rest of the functions. 
    # it utilizes switch type logic to parse a string and evaluate the strings operations

    addi $v0, $zero, 0

# we store the address of the string, which as we iterate is our position in the string
    sw $a0, 8($sp)  

# these statements make sure that we have an int as our first character
    lb $t0, 0($a0)
    beq $t0, $zero, catch
    beq $t0, 32, catch
    beq $t0, '+', catch
    beq $t0, '-', catch
    beq $t0, '*', catch
    beq $t0, '/', catch
    
push_int:
    jal scanpush
handle_int:             # this label iterates past a whole integer byte by byte.
    lw $a0, 8($sp)
    add $a0, $a0, 1
    sw $a0, 8($sp)
    lb $t0, 0($a0)
    bgt $t0, 47, handle_int
whats_next:             # this label finds whatever the next char is in the string and jumps to the neccessary action
    beq $t0, $zero, done_scan
    beq $t0, 32, handle_single
    beq $t0, '+', add_op
    beq $t0, '-', sub_op
    beq $t0, '*', mul_op
    beq $t0, '/', div_op
    j push_int
handle_single:           # this label iterates past a singular char
    lw $a0, 8($sp)
    add $a0, $a0, 1
    sw $a0, 8($sp)
    lb $t0, 0($a0)
    j whats_next

# These statements are where a operator is evaluated. 
   # they call the specified operator function and then iterate past the operator char in the string

mul_op:
    jal multiply_integer
    beq $v0, $zero, catch
    j handle_single
div_op:
    jal divide_integer
    beq $v0, $zero, catch
    j handle_single
add_op:
    jal add_integer
    beq $v0, $zero, catch
    j handle_single
sub_op:
    jal subtract_integer
    beq $v0, $zero, catch
    j handle_single


# This label handles the end of the string. it pops the top* value off the stack and returns that value out of the function
    # *(assuming the operations were done correctly and it is in fact the last item too) 
done_scan:
    addi $a0, $sp, 12       # the value popped off is stored at a offset 12 for this functions stack frame
    jal pop
    beq $v0, $zero, catch
    lw $t0, 12($sp)
    add $v0, $zero, $t0


    # a statement like this could check if the top item was the last item
        # jal pop
        # bne $v0, $zero, catch
    # or could alternately iterate until the stack is empty and then jump to catch
        # jal pop
        # bne $v0, $zero, done_scan
        # j catch


catch:      # this label catches errors and exits with 0.
rpncalculate_exit:
    # exit the function
    move $sp, $fp
    lw $fp, 16($sp)
    lw $ra, 20($sp)
    addi $sp, $sp, 24
    # return the address of the ciphertext string
    jr $ra
.end rpncalculate
