#include "errorlog.h"
#include "TM.h"

using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

static int errored = false;

/* is set when a fatal error is encountered so program knows to exit */
static bool fatalerror = false;

TuringMachine::TuringMachine(string arg1)
{
    filename = arg1;
    maxTransitions = 1;
    maxID = 32;
    changedInput = false;
    blankCharacter = 0;
    startState = "";
    definition = "";

    TMstatus = unrun;

    inputList.resize(0);
    states.resize(0);
    tapeAlphabet.resize(0);
    inputAlphabet.resize(0);

    // '\' specified as empty string
    inputAlphabet.push_back('\\');
    tapeAlphabet.push_back('\\');

    if (initDef())
    {
        errorLog("Invalid Turing Machine Definition File");
        fatalerror = true;
        errored = true;
    }

    if (fatalerror)
    {
        destroy();
        exit(1);
    }

    if (initStr())
    {
        errorLog("Invalid Input String Definition File");
        errored = true;
    }

    if (!fatalerror)
        cout << "Turing machine successfully loaded" << endl;
    else
    {
        destroy();
        exit(1);
    }

    return;
}

TuringMachine::~TuringMachine()
{
    destroy();
}
//question write empty set to file? if not provided?
void TuringMachine::destroy()
{
    //delete dynamically allocated vector for states
    for (int i = 0; i < states.size(); i++)
    {
        delete states.at(i);
    }

    //write input strings to file
    if (fatalerror)
    {
        cout << "Input list was not written to file due to a fatal error reading "<< filename <<".def" << endl;
    }
    else if (changedInput)
    {
        ofstream str_file(filename + ".str", std::ios::trunc);
        if(!str_file.is_open())
        {
            cout << "Failed to open " + filename + ".str";
        }
        else
        {
            for (int i = 0; i < inputList.size(); i++)
            {
                str_file << inputList.at(i) << endl;
            }

            cout << "Wrote input list to " << filename + ".str" << endl;
        }
    }
    else
    {
        cout << "Input list was not changed - file unchanged" << endl;
    }

    if(!errored)
    {
        errorLog("No Errors Caught");
    }
    else
    {
        ifstream error_log("error.log");
        if (!error_log.is_open())
        {
            cout << endl << "Failed to open error.log" << endl;
            return;
        }

        cout << endl;

        string output = "";
        while(getline(error_log,output))
        {
            cout << output << endl;
        }

        error_log.close();
    }

    return;
}
