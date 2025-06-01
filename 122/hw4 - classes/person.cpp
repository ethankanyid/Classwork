#include "person.h"
#include <cstring>
#include <iostream>

using std::endl;

Person::Person(string fName, string lName, string mName, string street, string city, const char *state, const char* zip)
{
    firstName = fName;
    middleName = mName;
    lastName = lName;
    streetAddress = street;
    this->city = city;
    strncpy_s(this->state, 4, state, 4);
    strncpy_s(this->zip, 6, zip, 6);
}

string Person::getFirstName() const
{
    return firstName;
}

void Person::setFirstName(string fName)
{
    firstName = fName;
}

string Person::getLastName() const
{
    return lastName;
}

void Person::setLastName(string lName)
{
    lastName = lName;
}

string Person::getMiddleName() const
{
    return middleName;
}

void Person::setMiddleName(string mName)
{
    middleName = mName;
}

string Person::getStreetAddress() const
{
    return streetAddress;
}

void Person::setStreetAddress(string address)
{
    this->streetAddress = address;
}

string Person::getCity() const
{
    return city;
}

void Person::setCity(string city)
{
    this->city = city;
}

char* Person::getState() const
{
    char* tmpState = new char[4];

    strncpy_s(tmpState, 4, state, 4);
    
    return tmpState;
}

void Person::setState(const char* state)
{
    strncpy_s(this->state, 4, state, 4);
    this->state[3] = '\0';
}

char* Person::getZip() const
{
    char* tempZip = new char[6];

    strncpy_s(tempZip, 6, zip, 6);

    return tempZip;
}
void Person::setZip(const char *zip)
{
    strncpy_s(this->zip, 6, zip, 6);
    this->zip[5] = '\0'; // Ensure that the last character is a null
}

string Person::toString()
{
    stringstream sstream;
    sstream << "First Name: " << getFirstName() << endl;
    sstream << "Middle Initial: " << getMiddleName()[0] << "." << endl;
    sstream << "Last Name: " << getLastName() << endl;
    sstream << "Address:" << endl;
    sstream << getStreetAddress() << endl;
    sstream << getCity() << ", " << getState() << " ";
    sstream << getZip();

    return sstream.str();
}
