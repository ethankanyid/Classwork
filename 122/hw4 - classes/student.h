#include "person.h"

using std::endl;

class Student : public Person
{
    private:
    // new members
    int studentID;
    int gradYear;
    double GPA;

    public:
    // constructors
    Student(string fName, string lName, string mName, string street, string city, const char *state, const char* zip, int sID, int gYear, double GPA);
    Student(string fName, string lName, string mName, string street, string city, const char *state, const char* zip, int sID, int gYear, double GPA) : Person(fName, lName, mName, street, city, state, zip){}

    //getters and setters
    int getID();
    int getYear();
    double getGPA();

    void setID(int sID);
    void setYear(int gYear);
    void setGPA(double GPA);


    // overriding parent function
    string toString(){
        stringstream sstream;

        sstream << "Student ID: " << getID() << endl;
        sstream << "Graduation Year: " << getYear() << endl;
        sstream << "GPA: " << getGPA() << endl;
    }

};


