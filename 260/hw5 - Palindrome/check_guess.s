.data
number: .word 0

.text
.globl set_number
.ent set_number
.type set_number, @function
# set_number - function to set the number to guess
# $a0 the number to guess
set_number:
    # save the return address

    sw $a0, number

    jr $ra
.end set_number

.globl check_guess
.ent check_guess
.type check_guess, @function
# check_guess - function check the guess in $a0 against the number
# $a0 the guess
check_guess:
    .frame $fp, 16, $ra
    # save the return address
    addi $sp, $sp, -16
    sw $ra, 4($sp)
    sw $fp, 8($sp)
    move $fp, $sp
    .cprestore 12

    lw $t0, number

    beq $a0, $t0, equal
    blt $a0, $t0, less

    #defaults to greater
    li $v0, 1
    j exit
    
equal:
    li $v0, 0
    j exit

less:
    li $v0, -1

exit:
    # exit the function
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 8($sp)
    addi $sp, $sp, 16
    # return the address of the ciphertext string
    jr $ra
.end check_guess
