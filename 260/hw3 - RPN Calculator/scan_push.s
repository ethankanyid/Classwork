.data
# define the scanf format string
SCANF_FORMAT: .asciiz "%i"

.text
.global scanpush
.ent scanpush
.type scanpush, @function
# scanpush - reads an integer from the string and pushes it onto the stack
# $a0 is the address of the rpn string
# $v0 is the result of pushing the integer onto the stack
scanpush:
    .frame $fp, 24, $ra
    # save the return address
    addi $sp, $sp, -24
    sw $ra, 20($sp)
    sw $fp, 16($sp)
    move $fp, $sp
    .cprestore 4

# This function utilizes glibc sscanf. it calls the function with a string, format, and place to store arguments
    #a0 is already pointing to the string

    addi $v0, $zero, 0

    sw $a0, 12($sp)             # save address for later

    la $a1, SCANF_FORMAT        # format
    addi $a2, $sp, 8            # address to store
    jal sscanf
    beq $v0, $zero, scanpush_done


    lw $a0, 8($sp)              # calls function with the value as the argument
    jal push
    beq $v0, $zero, scanpush_done

    addi $v0, $zero, 1
    
scanpush_done:
    lw $a0, 12($sp)             # restore address for exiting

# This function returns 0 upon failure and 1 upon success

scanpush_exit:
    # return
    move $sp, $fp
    lw $ra, 20($sp)
    lw $fp, 16($sp)
    addi $sp, $sp, 24
    j $ra
.end scanpush
