#include "employee.h"

// constructors
Employee::Employee(string fName, string lName, string mName, string street, string city, const char *state, const char* zip, int eID, int sLvl, string rtg);
{
    firstName = fName;
    middleName = mName;
    lastName = lName;
    streetAddress = street;
    this->city = city;
    strncpy_s(this->state, 4, state, 4);
    strncpy_s(this->zip, 6, zip, 6);
    EmployeeID = eID;
    seniorityLevel = sLvl;
    rating = rtg;
}

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