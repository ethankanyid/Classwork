/*
Programmer: Ethan Kanyid
Class: cpts 122
Date: 3-6-2024

Program: To calculate the harmonic mean of two numbers.
*/


#include <iostream>
#include <iomanip>

// im not using namespace std to test my capabilities

double mean (double x, double y)
// calculates the harmonic mean of two doubles. doubles are used beacause a mean is not a determined int.
{
  return (2.0 * x * y )/ (x + y);
}

int main ()
{
    double pair1, pair2;
for(;;)
// operates until pair (0 0 ) is entered.
{
    std::cout << std::endl << "Enter a pair of numbers (x y), ";
    std::cout << "(Enter \"0 0\" to break): ";
    std::cin >> pair1 >> pair2;

    if(pair1 == 0 && pair2 == 0)
    // breaks the loop.
    {
        std::cout << "Pair (0 0) was entered. Function Complete." << std::endl << std::endl;
        break;
    }

    printf("Harmonic Mean: %.3f \n",mean(pair1, pair2));
    
    
    //std::cout << "Harmonic Mean: " << std::setprecision(10) << mean(pair1, pair2) << std::endl; 
    /*sets significant digits and not decimal places*/
}

    return 0;
}