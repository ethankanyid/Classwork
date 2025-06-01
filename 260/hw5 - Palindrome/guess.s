.globl guess
.ent guess
.type guess, @function
# guess - function to guess a number between 1 and $a0
# call the function check_guess to check the guess
# $a0 the upper bound of the number to guess
# $a1 the lower bound of the number to guess
guess:
    .frame $fp, 24, $ra
    # save the return address
    addi $sp, $sp, -24
    sw $ra, 4($sp)
    sw $fp, 8($sp)
    sw $a0, 16($sp)
    sw $a1, 20($sp)
    move $fp, $sp
    .cprestore 12    

start:
    lw $a0, 20($sp)     # lower
    lw $t0, 16($sp)     # upper

    bgt $a0, $t0, error
    jal check_guess
    beq $0, $v0, found

    addi $a0, $a0, 1
    sw $a0, 20($sp)
    j start

found:
    lw $a0, 20($sp)
    sw $a0, 16($sp)
    lw $a1, 16($sp)
    j exit
    
error:
    li $a1, 0

exit:
    move $v0, $a1
    # exit the function
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 8($sp)
    lw $a0, 16($sp)
    lw $a1, 20($sp)
    addi $sp, $sp, 24
    # return the address of the ciphertext string
    jr $ra
.end guess
