/* 
Programmer: Ethan Kanyid
Class: cpts 122
Date: 2-5-2024
Program: to use arrays.
*/

#include <iostream>
#include <cctype>
#include <string>
#include <sstream>


using namespace std;

int main()
{

    double currency[10], sum = 0, average = 0;
    int total = 0, count = 0;
    string input;
    stringstream X;    
    
    cout << "Please enter up to 10 currency values to be computed in the array, typing done when finished (x x x... done): ";
 
    getline(cin, input);

    X << input;
 
    string temp;
    double found;
    while (!X.eof()) 
    // finds doubles within a string and terminates at a non-double
    {
        X >> temp;

        if (stringstream(temp) >> found)
        {
            currency[count] = found;
            total++;
        }
        else 
        {
            break;
        }

        temp = "";
    }


    for(int x = 0; x < total; x++)
    // calculates sum.
    {
        sum += currency[x];
    }
    
    average = sum/total;

    for (int i = 0; i < total;  i++)
    // counts how many values are above average.
    {   
        if(currency[i] > average)
        {
            count++;
        }
    }

    cout << "The average is " << average << endl;

    if(count != 1)
    {
        cout << count << " Values are larger than average." << endl;
    }
    else 
    {
        cout << count << " Value is larger than average." << endl;
    }
}