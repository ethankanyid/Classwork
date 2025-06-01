/*
Programmer: Ethan Kanyid
Class: cpts 122
Date: 3-6-2024

Program: 
*/

#include <iostream>
#include <iomanip>
#include <array>

// im not using namespace std to test my capabilities

template <typename kind> kind max5(kind array[5], int x)
// a templated function that finds the largest value and returns it.
{
    kind max = array[0];

    for (int i = 1; i < x; i++)
    {
        max = (array[i] > max) ? array[i] : max;
    }

    return max;
}



int main ()
{
    int x=0;

    std::cout << "How many numbers would you like to compare? " << std::endl;

    std::cin >> x;

    int arrayI[x];
    double arrayD[x];

    std::cout << "Enter "<< x << " integers in format (a b c...) " << std::endl;

    for(int i = 0; i < x; i++)
    //reads in the variables
    {
        std::cin >> arrayI[i];
    }

    std::cout << "Max Integer: " << max5(arrayI,x) << std::endl;

    std::cout << "Enter " << x << " doubles in format (a b c...) " << std::endl;

    for(int i = 0; i < x; i++)
    //reads in the variables
    {
        std::cin >> arrayD[i];
    }

    std::cout << "Max Double: " << max5(arrayD,x) << std::endl;

    return 0;
}