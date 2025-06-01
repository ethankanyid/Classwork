/************************************************************************

* Programmer: Ethan Kanyid

* Class: CptS 121, Fall 2022; Lab Section 02

* Programming Assignment: Lab2 Task1

* Date: September 1, 2022

* Description: This program prints out a simple small calculation.

*************************************************************************/


#include <stdio.h>
#include <math.h>
 
int main(void)
{
       
        /*int number1_int, number2_int,sum_1,div_1;
        double number1_float, number2_float, dif_1,mult_1,div_2,div_3;
    
    printf("Enter two integer values: ");
    scanf("%d %d", &number1_int, &number2_int);
    
    printf("Enter two floating-point values: ");
    scanf("%lf %lf", &number1_float, &number2_float);*/
    
        int number1_int=28, number2_int=14;
        double number1_float=28.0, number2_float=14.0;
    
    printf("Sum of two ints: %d\n",number1_int+number2_int);
    
    printf("Difference of two floats: %.1lf\n",number1_float - number2_float);
    
    printf("Multiplication of int and float: %d\n",number1_int*number1_float);
    
    printf("Division of two ints as an int: %d\n",number1_int/number2_int);
    printf("Division of two ints as a float %.1lf\n",number1_int/number2_int);
    
    printf("Division of an int and float as an int: %d\n",number1_int/number2_float);
    printf("Division of an int and float as a float: %.1lf\n",number1_int/number2_float);
    
    printf("Division of a floated int and a float as a float: %.1lf\n",(float)number1_int/number2_int);
    
    printf("Mod of a float and a float: %d\n",(int)number1_float%(int)number2_float);
    
    printf("0 if even, 1 if odd: %d\n",number1_int%2);
    printf("0 if even, 1 if odd: %d\n",number2_int%2);
    
       return 0;
}