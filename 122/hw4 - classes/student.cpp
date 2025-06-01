#include "student.h"

// constructors
Student::Student(string fName, string lName, string mName, string street, string city, const char *state, const char* zip, int sID, int gYear, double GPA)
{
    firstName = fName;
    middleName = mName;
    lastName = lName;
    streetAddress = street;
    this->city = city;
    strncpy_s(this->state, 4, state, 4);
    strncpy_s(this->zip, 6, zip, 6);
    studentID = sID;
    gradYear = gYear;
    this->GPA = GPA;
}

// getters and setters
int Student::getID()
{
    return studentID;
}
int Student::getYear()
{
    return gradYear;
}
double Student::getGPA()
{
    return GPA;
}

void Student::setID(int sID)
{
    studentID = sID;
}
void Student::setYear(int gYear)
{
    gradYear = gYear; 
}
void Student::setGPA(double GPA)
{
    this->GPA = GPA;
}