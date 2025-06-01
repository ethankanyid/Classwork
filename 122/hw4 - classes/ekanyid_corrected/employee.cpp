#include "employee.h"

// constructors

// getters and setters
int Employee::getID()
{
    return employeeID;
}
int Employee::getLevel()
{
    return seniorityLevel;
}
string Employee::getRating()
{
    return rating;
}

void Employee::setID(int eID)
{
    employeeID = eID;
}
void Employee::setLevel(int sLvl)
{
    seniorityLevel = sLvl; 
}
void Employee::setRating(string rtg)
{
    rating = rtg;
}