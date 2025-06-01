# Homework 1 - Reverse Polish Notation Calculator
 
In this project, we will implement a Reverse Polish Notation (RPN) calculator using MIPS
assembly language. RPN is a mathematical notation in which operators follow their operands,
eliminating the need for parentheses to define operator precedence, which simplifies
calculations on stack-based architectures. This notation was popularized by calculators
such as the HP-35 due to its efficient handling of mathematical expressions (Wikipedia, 2023).
The goal of this project is to implement an RPN calculator in MIPS, leveraging a dynamic stack
to process operations and operands efficiently, adhering to the core principles of MIPS
architecture. This project will not only deepen our understanding of assembly programming
but also demonstrate the practicality of RPN in low-level computation.

- Wikipedia contributors. "Reverse Polish Notation." Wikipedia, The Free Encyclopedia.
  September 1, 2023. https://en.wikipedia.org/wiki/Reverse_Polish_notation

## Reverse Polish Notation Specification

- Input Handling:
    - Accept input string of space-separated operands and operators in RPN format
      (e.g., "3 4 + 2 *" and see tests in `main.c`).
    - Parse the input string to identify operands (numbers) and operators (+, -, *, /).
    - Do not parse floats, this calculator only works on integers.

- Stack Management:
    - Use a stack to store operands during evaluation.
    - Push each operand onto the stack when encountered.
    - When an operator is encountered, pop the necessary operands from the stack.

- Operations:
    - Implement basic arithmetic operations: addition (+), subtraction (-), multiplication
      (*), and division (/).
    - For each operator, pop the required number of operands, perform the operation, and
      push the result back onto the stack.
    - Perform integer division and drop remainders.

## Program Design

Each function is put into separate assembly files to help separate responsibilities and
simplify the implementation and testing.

1. `main.c` primary entrypoint and contains all the testing for the following functions.
1. `stack.s` contains the interface for a stack of integers and operations for pushing
   and popping values off the stack.
1. `scan_push.s` contains a function to scan (sscanf) an integer from the string and push
   the integer on the stack.
1. `add_integer.s` contains a function to pop two values off the stack, add them and push
   the result back on the stack.
1. `subtract_integer.s` contains a function to pop two values off the stack, subtract them
   and push the result back on the stack. (make sure you get the right order for subtract)
1. `multiply_integer.s` contains a function to pop two values off the stack, multiply them
   and push the result back on the stack.
1. `divide_integer.s` contains a function to pop two values off the stack, divide them and
   push the result back on the stack. (make sure you get the right order for divide)
1. `calculate.s` contains the primary function that pulls all the other functions together
   to calculate a Reverse Polish Notation expression.

## Grading

Remember that an additional 5 points will be added for students that document their code.
The comments should be describing the high level of what you are doing, not reiterating the
instructions that were just read. The comment should address why you are performing the
instruction not the instruction itself.
