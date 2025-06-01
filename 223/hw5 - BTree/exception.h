#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Exceptions
{
protected:
    string message;
    int errorNumber;

public:
    Exceptions(int eNo, string msg) : errorNumber(eNo), message(msg) {}
    virtual string toString()
    {
        stringstream sstream;
        sstream << "Exception: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};

class DuplicateItemException : public Exceptions
{
public:
    DuplicateItemException(int eNo, string msg) : Exceptions(eNo, msg) {}
    string toString()
    {
    stringstream sstream;
    sstream << "DuplicatItemException: " << errorNumber << " ERROR: " << message;
    return sstream.str();
    }
};

class TreeEmptyException : public Exceptions
{
public:
    TreeEmptyException(int eNo, string msg) : Exceptions(eNo, msg) {}
    string toString()
    {
    stringstream sstream;
    sstream << "TreeEmptyException: " << errorNumber << " ERROR: " << message;
    return sstream.str();
    }
};

class ItemNotFoundException : public Exceptions
{
public:
    ItemNotFoundException(int eNo, string msg) : Exceptions(eNo, msg) {}
    string toString()
    {
    stringstream sstream;

    sstream << "ItemNotFoundException: " << errorNumber << " ERROR: " << message;
    return sstream.str();
    }
};

class InvalidSize : public Exceptions
{
public:
    InvalidSize(int eNo, string msg) : Exceptions(eNo, msg) {}
    string toString()
    {
    stringstream sstream;
    sstream << "Invalid Size: " << errorNumber << " ERROR: " << message;
    return sstream.str();
    }
};
