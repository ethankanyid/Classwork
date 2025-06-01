.globl palindrome
.ent palindrome
.type palindrome, @function

# MIPS Assembly  Language
#
# This file contains the palindrome function written in MIPS assembly language.
# $a0 is the address of the string
# $v0 is the return value
palindrome:
  .frame $fp, 24, $ra
  # save the return address
  addi $sp, $sp, -24
  sw $ra, 4($sp)
  sw $fp, 8($sp)
  sw $a0, 16($sp)
  move $fp, $sp
  .cprestore 12

  lw $t0, 16($sp)      # Load start address into $t0
  sw $t0, 20($sp)      # Initialize end address with start address

find_end:
  lw $t0, 20($sp)      # Load end address

  lb $t1, 0($t0)       # Load byte at end address
  beqz $t1, next       # If it's zero (null terminator), go to next

  addi $t0, $t0, 1     # Move to the next byte
  sw $t0, 20($sp)      # Update end address
  j find_end           # Repeat the loop

next:
  lw $t0, 20($sp)      # Load end address
  addi $t0, $t0, -1    # Adjust end address to point to the last character
  sw $t0, 20($sp)      # Store updated end address

  lw $t0, 16($sp)      # Load start address (string start)
  lw $t1, 20($sp)      # Load adjusted end address

  beq $t1, $t0, passes # If start and end are the same, handle single character
  lb $t2, 0($t0)
  beqz $t2, passes

continue:
  lw $t0, 16($sp)      # Load start address
  lw $t1, 20($sp)      # Load end address

  lb $t2, 0($t0)       # Load byte at start address
  lb $t3, 0($t1)       # Load byte at end address

  bne $t2, $t3, fails   # If characters are not equal, go to fails

  beq $t1, $t0, passes  # If both pointers are the same, we've passed
  addi $t0, $t0, 1      # Move start pointer to next character
  beq $t1, $t0, passes  # If next to each other, we've passed

  sw $t0, 16($sp)       # Update start address
  addi $t1, $t1, -1     # Move end pointer to previous character
  sw $t1, 20($sp)       # Update end address
  j continue             # Repeat the comparison

passes:
    li $v0, 1           # Load 1 into $v0 (indicates success)
    j exit               # Jump to exit

fails:
    li $v0, 0           # Load 0 into $v0 (indicates failure)

exit:
    # Exit routine here (not provided in original code)


exit:
  # exit the function
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 8($sp)
  lw $a0, 16($sp)
  addi $sp, $sp, 24
  # return the address of the ciphertext string
  jr $ra
