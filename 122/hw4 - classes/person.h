#pragma once
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Person {
protected:
    string firstName;
    string lastName;
    string middleName;
    string streetAddress;
    string city;
    char state[4];
    char zip[6];
public:
    Person(string fName, string lName, string mName, string street, string city, const char *state, const char* zip);

    string getFirstName() const;
    void setFirstName(string fName);

    string getLastName() const;
    void setLastName(string lName);

    string getMiddleName() const;
    void setMiddleName(string mName);

    string getStreetAddress() const;
    void setStreetAddress(string address);

    string getCity() const;
    void setCity(string city);

    char* getState() const;
    void setState(const char* state);

    char* getZip() const;
    void setZip(const char* zip);


    virtual string toString();
};
