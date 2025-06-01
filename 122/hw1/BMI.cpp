#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main ()
{
    double feet, inches, pounds;

    double meters, kilos;

    double const INCHES_TO_METERS = 0.0254;
    double const POUNDS_TO_KILOS = 2.2;

    cout << "Please enter your height in \"Feet Inches\": ";

    cin >> feet >> inches;

    cout << "Please enter your weight in pounds: ";

    cin >> pounds;

    meters = INCHES_TO_METERS * (inches + feet * 12); // converts the feet to inches and then converts it all to meters
    kilos = pounds / POUNDS_TO_KILOS;                 // converts pounds to kilos

    cout << "Your BMI is " << fixed << setprecision(2) << kilos / pow(meters,2) << "." << endl; // prints out the calculated BMI
}