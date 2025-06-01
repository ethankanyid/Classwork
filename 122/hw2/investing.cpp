/* 
Programmer: Ethan Kanyid
Class: cpts 122
Date: 2-5-2024
Program: to show compound vs simple interest.
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double simple = 100.0, compound = 100.0;
    int years = 0;

    double const SIMPLE_RATE = .1*simple; //10% of simple.
    double const COMPOUND_RATE =.05; // 5% of compound, needs to be re-calculated every year.
    

    while (1)
    // calculates interest until the accounts are equal.
    {
        simple += SIMPLE_RATE;
        compound = compound + compound*COMPOUND_RATE;
        years++;
        
        if (compound > simple)
        {
            break;
        }
    } 

    cout << "After " << years << " years, the compound account exceeded the simple account at ";
    cout << compound << " and " << simple << " respectively." << endl;

}