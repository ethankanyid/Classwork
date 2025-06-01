#include <iostream>

using namespace std;

int main ()
{
    int height;

    int const INCHES_TO_FEET = 12;

    cout << "Please enter your height in inches as an integer: ";

    cin >> height;

    cout << "Your height is " << height / INCHES_TO_FEET << " feet " << height % INCHES_TO_FEET << " inches."; 
    // ^prints out the calculated feet and inches from the inputted height
}