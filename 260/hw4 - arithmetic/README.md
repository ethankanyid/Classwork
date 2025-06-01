# Assignment 2 - Arithmetic

Fill in the empty table cells. Showing your work or submitting code
snippets that helped you will give partial credit.

## Signed and Unsigned Conversion

(20 Points)

Convert the following hexadecimal numbers to their signed and unsigned
decimal equivalent. Fill in your answers in the table.

| Hexadecimal | Signed Decimal | Unsigned Decimal |
| ----------- | -------------- | ---------------- |
| 1. 0x91     |       -111       |      145       |
| 2. 0xA4     |       -92        |      164       |
| 3. 0x14     |        20        |      20        |
| 4. 0xF0     |       -16        |      240       |

signed: normal
unsigned (msb == 1): subtract 1 and unflip bits; add negative


1. 0x91 -> 1001 0001 (binary) -> 145 (decimal unsigned) 
                              -> 1001 0000 -> 0110 1111 -> 111 -> -111 (decimal signed)
2. 0xA4 -> 1010 0100 (binary) -> 164 (decimal unsigned) 
                              -> 1010 0011 -> 0101 1100 -> 92 -> -92 (decimal signed)
3. 0x14 -> 0001 0100 (binary) -> 20 (decimal unsigned & signed)
4. 0xF0 -> 1111 0000 (binary) -> 240 (decimal unsigned) 
                              -> 1110 1111 -> 0001 0000 -> 16 -> -16 (decimal signed)

## Two's Compliment

//it formatted this section weird, so it looks better in code.

(40 Points)

Perform Two's Compliment conversions where appropriate to answer the
following questions. Fill in your answers in the table.

| row |      X |      Y | 1. | 2. | 3. | 4. |
| --- | ------ | ------ | -- | -- | -- | -- |
|  A. | 0xEDDF | 0xE23C |1D01B|4361|60,895|-4,641|
|  B. | 0xAE0F | 0x6AAE |118BD|0BA3|44,559|-20,977|

Assuming that X and Y are 16-bit hexadecimal values, calculate the
following and insert the answers into the table above.

1. `X + Y`, in hexadecimal
   11111
A.  EDDF
    E23C
   1D01B

   11011
B.  AE0F
    6AAE
   118BD

2. `X - Y`, using 2's complement arithmetic, in hexadecimal
   
A.  EDDF
    E23C
    0BA3

      1
B.  AE0F
    6AAE
    4361
   
3. the decimal value of `X` assuming unsigned representation
A. EDDF -> 1110 1101 1101 1111 (binary) -> 60,895 (decimal unsigned) 
                                        -> 1110 1101 1101 1110 -> 0001 0010 0010 0001 -> 4,641 -> -4,641 (decimal signed)

B. AE0F -> 1010 1110 0000 1111 (binary) -> 44,559 (decimal unsigned)
                                        -> 1010 1110 0000 1110 -> 0101 0001 1111 0001 -> 20,977 -> -20,977 (decimal signed)

4. the decimal value of `X` assuming two's complement representation
A. EDDF -> 1110 1101 1101 1111 (binary) -> 60,895 (decimal unsigned) 
                                        -> 1110 1101 1101 1110 -> 0001 0010 0010 0001 -> 4,641 -> -4,641 (decimal signed)

B. AE0F -> 1010 1110 0000 1111 (binary) -> 44,559 (decimal unsigned)
                                        -> 1010 1110 0000 1110 -> 0101 0001 1111 0001 -> 20,977 -> -20,977 (decimal signed)

## Floating Point Conversion

//it formatted this section weird, so it looks better in code.

(40 Points)

Convert the hexadecimal numbers to floating point and answer the
following questions. Fill your answers in the table.

| row |       word | 1. | 2. | 3. | 4. |
| --- | ---------- | -- | -- | -- | -- |
|  A. | 0x41660000 |0 (pos)|3|1110.0110|14.375|
|  B. | 0xC1A38000 |1 (neg)|4|1 0100.0111|-20.4375|

Convert the hexadecimal numbers and answer the following questions
about those numbers.

1. the sign of the number.
A. 0100 0001 0110 0110 0000 0000 0000 0000 -> 0 (100 0001 0) (110 0110 0000 0000 0000 0000)
   ^ leading 0. positive

B. 1100 0001 1010 0011 1000 0000 0000 0000 -> 1 (100 0001 1) (010 0011 1000 0000 0000 0000)
   ^ leading 1. negative

2. the unbias decimal exponent.
bias = 127 (0111 1111)
A. 1000 0010 - 0111 1111 = 0000 0011 = 3
B. 1000 0011 - 0111 1111 = 0000 0100 = 4

3. the binary number.
A. Fraction = 110 0110 0000 0000 0000 0000
   Mantissa = 1.110 0110 0000 0000 0000 0000
   binary = 1110 . 0110


B. Fraction = 010 0011 1000 0000 0000 0000
   Mantissa = 1.010 0011 1000 0000 0000 0000
   binary = 1 0100.0111

4. the decimal number.
A. 8 + 4 + 2 . 2^-2 + 2^-3 = 14.375

B. 16 + 4 . 2^-2 + 2^-3 + 2^-4  = 20.4375 -> -20.4375

## Extra Credit

(10 Points)

Make a C program to verify your answers. The program does not have to
work on MIPS. Consider looking at `stdint.h` for appropriate types.
Commit the program as a separate file.
