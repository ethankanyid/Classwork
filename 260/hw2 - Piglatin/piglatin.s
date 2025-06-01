.globl piglatin
.ent piglatin
.type piglatin, @function

.text
.globl main

piglatin:
    .frame $sp, 20, $ra             # save the return address
    addi $sp, $sp, -20              # Make space on the stack
    sw $ra, 0($sp)                  # stores return address at 0 on the stack.
    .cprestore 4

    sw $s0, 8($sp)           # Save $s0 
    sw $s1, 12($sp)          # Save $s1 
    sw $s2, 16($sp)          # Save $s2

    # Initialize
    move $s0, $a0           # $s0 (index in string)
    move $s1, $a1           # $s1 (output pointer)
    li $s2, 0               # $s2 (first vowel)

    # Check if the input string is empty
    lb $t0, 0($s0)          # Load first byte of the input string
    beq $t0, $zero, catch    # If it's NULL, go to catch

find_first_vowel:
    lb $t2, 0($s0)          # Load byte from input string
    beq $t2, 'a', vowel_found
    beq $t2, 'e', vowel_found
    beq $t2, 'i', vowel_found
    beq $t2, 'o', vowel_found
    beq $t2, 'u', vowel_found

    addi $s0, $s0, 1        # Move to the next character
    j find_first_vowel

vowel_found:
    # Copy the vowel and following characters to output
    move $s2, $s0
    move $t0, $s0           # $t0 = start of vowel
    lb $t1, 0($s0)          # Load vowel character
    sb $t1, 0($s1)          # Store vowel character to output
    addi $s0, $s0, 1        # Move to next character
    addi $s1, $s1, 1        # Move output pointer
copy_letters:
    lb $t1, 0($s0)          # Load next character
    beq $t1, $zero, add_ending # If NULL, go to add_ending
    sb $t1, 0($s1)          # Store character
    addi $s0, $s0, 1        # Move to next character
    addi $s1, $s1, 1        # Move output pointer
    j copy_letters

add_ending:
    # evaluate if the word starts with vowel or consonant

    # does the word start with a vowel?
    beq $s2, $a0, add_way

    # it starts with a consonant
    move $s0, $a0
    j move_consonants

add_way:
    # Add "way" to the end of the string
    li $t1, 'w'
    sb $t1, 0($s1)
    addi $s1, $s1, 1
    li $t1, 'a'
    sb $t1, 0($s1)
    addi $s1, $s1, 1
    li $t1, 'y'
    sb $t1, 0($s1)
    addi $s1, $s1, 1
    sb $zero, 0($s1)        # Null-terminate the output string

    j success

move_consonants:

    beq $s0, $s2, add_ay

    lb $t1, 0($s0)          # Load character
    sb $t1, 0($s1)          # Store consonant

    addi $s1, $s1, 1        # Move output pointer
    addi $s0, $s0, 1        # Move to next character
    j move_consonants

add_ay:
    li $t1, 'a'
    sb $t1, 0($s1)
    addi $s1, $s1, 1
    li $t1, 'y'
    sb $t1, 0($s1)
    addi $s1, $s1, 1
    sb $zero, 0($s1)        # Null-terminate the output string

    j success

catch:

    # initialize return value to -1
    addi $v0, $zero, -1

    j done

success:
    # initialize return value to 0
    add $v0, $zero, $zero

done:
    # Restore saved registers and return
    lw $s0, 8($sp)          # Restore $s0
    lw $s1, 12($sp)          # Restore $s1
    lw $s2, 16($sp)          # Restore $s2
    lw $ra, 0($sp)
    addi $sp, $sp, 20       # Deallocate stack space
    jr $ra                  # return the address of the ciphertext string
.end piglatin
