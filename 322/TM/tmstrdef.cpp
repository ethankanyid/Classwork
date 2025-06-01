#include "TM.h"
#include "errorlog.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

bool TuringMachine::initStr()
{
    ifstream str_file(filename + ".str");
    if(!str_file.is_open())
    {
        errorLog("Failed to open " + filename + ".str");
        cout << "Failed to open " + filename + ".str" << endl;
        return 1;
    }

    string input = "";
    bool errored = false;

    while (getline(str_file,input))
    {
        string error = validInput(input);
        if (!error.empty())
        {
            errorLog(error);
            cout << error << endl;
            changedInput = true;
            errored = true;
        }
        else
            inputList.push_back(input);
    }

    str_file.close();

    return errored;
}

string TuringMachine::validInput(string input)
{
    if (input.size() == 1 && input.at(0) == '\\')
    {
        for (int i = 0; i < inputList.size(); i++)
        {
            if (inputList.at(i) == input)
                return (input + " is a duplicate input string" );
        }
        return "";
    }

    //check for valid chars
    for(int i = 0; i < input.size(); i++)
    {
        bool validChar = false;
        //starts at 1 because '\' is not allowed in string
        for (int i2 = 1; i2 < inputAlphabet.size(); i2++)
        {
            if (input.at(i) == inputAlphabet.at(i2))
            {
                validChar = true;
                break;
            }
        }
        if (!validChar)
            return ("Invalid character in string \"" + input + "\"");
    }
    for (int i = 0; i < inputList.size(); i++)
    {
        if (inputList.at(i) == input)
            return (input + " is a duplicate input string" );
    }

    return "";
}
