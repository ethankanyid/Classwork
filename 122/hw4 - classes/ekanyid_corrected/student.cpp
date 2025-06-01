#include "student.h"

// constructors

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