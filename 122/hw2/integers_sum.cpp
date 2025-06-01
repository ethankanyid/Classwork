/* 
Programmer: Ethan Kanyid
Class: cpts 122
Date: 2-5-2024
Program: to read in two integers and calculate the sum of all integers between them inclusive.
*/

#include <iostream>

using namespace std;

int main()
{
    int upper, lower, x, y, sum = 0;
    
    do
    // takes in two different integers.
    {
        cout << "Please enter two different integers: ";
        cin >> x >> y;
    } while (x == y);

    upper = x > y ? x : y; // sets upper = x if x is greater than y - or y if not.
    lower = y < x ? y : x; // sets lower = y if y is greater than x - or x if not.

    for (; lower <= upper; lower++)
    // adds the variable lower into sum as lower approaches upper.
    {
        sum += lower;
    }

    cout << sum << endl;
}