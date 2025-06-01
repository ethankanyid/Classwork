#include "person.h"


using std::endl;

class Employee : public Person
{
    private:
    // new members
    int employeeID;
    int seniorityLevel;
    string rating;

    public:
    // constructors
    Employee(string fName, string lName, string mName, string street, string city, const char *state, const char* zip, int eID, int sLvl, string rtg);
    Employee(string fName, string lName, string mName, string street, string city, const char *state, const char* zip, int eID, int sLvl, string rtg) : 
            Person(fName, lName, mName, street, city, state, zip)
    {}

    //getters and setters
    int getID();
    int getLevel();
    string getRating();

    void setID(int eID);
    void setLevel(int sLvl);
    void setRating(string rtg);


    // overriding parent function
    string toString(){
        stringstream sstream;

        sstream << "Employee ID: " << getID() << endl;
        sstream << "Seniority Level: " << getLevel() << endl;
        sstream << "Rating: " << getRating() << endl;
    }

};


