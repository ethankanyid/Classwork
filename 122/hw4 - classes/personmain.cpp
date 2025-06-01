#include "person.h"
#include "student.h"
#include "employee.h"
#include <iostream>

using std::cout;
using std::endl;

void displayPerson(Person* person)
{
    cout << "=================================" << endl;
    cout << person->toString() << endl;;
    cout << "=================================" << endl;
}

int main(int argc, char* argv[])
{
    Person person(
            "John", 
            "Public", 
            "Quentin", 
            "12345 The Street",
            "Anytown",
            "CA",
            "12345");

    displayPerson(&person);

    Student student(
            "John",
            "Public", 
            "Quentin", 
            "12345 The Street",
            "Anytown",
            "CA",
            "12345",
            1186054,
            2026,
            4.0);
    displayPerson(&student);

    Employee employee(
        "John",
        "Public", 
        "Quentin", 
        "12345 The Street",
        "Anytown",
        "CA",
        "12345",
        1186054,
        5,
        "He is a Nice Guy");
    displayPerson(&employee);

    return 0;
}
