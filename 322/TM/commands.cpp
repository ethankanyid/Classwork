#include "TM.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

//fix use hex colors?

/*  Function to trim leading and trailing whitespaces*/
static string trim(string str);


char TuringMachine::getCommand()
{
    string input ="";
    char ch = 0;

    cout << "Command: ";
    getline(cin, input);

    if (input.empty())
    {
        return 0;
    }

    input = trim(input);

    if(input.size() != 1)
    {
        cout << "Invalid input" << endl;
        return 0;
    }


    char command = input.at(0);

    return tolower(command);
}

bool TuringMachine::runCommand(char command)
{
    switch (command)
    {
        case 0:
            break;
        case 'd':
        {
            commandD();
            break;
        }
        case 'x':
        {
            return 0;
        }
        case 'h':
        {
            commandH();
            break;
        }
        case 'i':
        {
            commandI();
            break;
        }
        case 'l':
        {
            commandL();
            break;
        }
        case 'q':
        {
            commandQ();
            break;
        }
        case 'r':
        {
            commandR();
            break;
        }
        case 'e':
        {
            commandE();
            break;
        }
        case 'w':
        {
            commandW();
            break;
        }
        case 't':
        {
            commandT();
            break;
        }
        case 'v':
        {
            commandV();
            break;
        }
        default:
        {
            cout << "Invalid Command" << endl;
            break;
        }
    }
    return 1;
}

void TuringMachine::commandD()
{
    if(inputList.empty())
    {
        cout << endl << "Input list is already empty" << endl << endl;
        return;
    }

    string input = "";
    int index = 0;

    cout << endl << "Enter the index you'd like to delete: ";
    getline(cin,input);
    if (input.empty())
    {
        return;
    }

    input = trim(input);
    if (input.empty())
    {
        cout << "Input must be exactly one number" << endl << endl;
        return;
    }

    try
    {
    index = std::stoi(input) - 1;
    }
    catch (std::invalid_argument)
    {
        cout << "Invalid argument" << endl << endl;
        return;
    }

    if (index > inputList.size() - 1 || index < 0)
    {
        cout << "Invalid index to delete" << endl << endl;
        return;
    }

    input = inputList.at(index);

    inputList.erase(inputList.begin() + index);     //erases the index

    cout << "Deleted index " << index + 1 << " containing string: \"" << input << "\""<< endl << endl;
    changedInput = true;

    return;
}

void TuringMachine::commandH()
{
    cout << endl
        << "D   Delete      Delete input string from list" << endl
        << "X   Exit        Exit application" << endl
        << "H   Help        Help user" << endl
        << "I   Insert      Insert input string into list" << endl
        << "L   List        List input string" << endl
        << "Q   Quit        Quit operation of Turing machine on input string" << endl
        << "R   Run         Run Turing machine on input string" << endl
        << "E   Set         Set maximum number of transitions to perform" << endl
        << "W   Show        Show status of application" << endl
        << "T   Truncate    Truncate instantaneous descriptions" << endl
        << "V   View        View Turing machine" << endl << endl;
    return;
}

void TuringMachine::commandI()
{
    string input = "";

    cout << endl << "Enter string to insert in input list: ";
    getline(cin, input);
    if (input.empty())
    {
        return;
    }

    input = trim(input);
    if (input.empty())
    {
        cout << "Input must be exactly one string" << endl << endl;
        return;
    }

    string error = validInput(input);
    if (!error.empty())
    {
        cout << error << endl << endl;
        return;
    }

    inputList.push_back(input);
    cout << "Inserted string \"" << input << "\"" << endl << endl;
    changedInput = true;

    return;
}

void TuringMachine::commandL()
{
    if (inputList.empty())
    {
        cout << endl << "Input list is empty" << endl << endl;
        return;
    }

    cout << endl;
    for (int i = 0; i < inputList.size(); i++)
    {
        cout << i + 1 << ".\t" << inputList.at(i) << endl;
    }
    cout << endl;
}

void TuringMachine::commandQ()
{

    if (TMstatus != running)
    {
        cout << endl << "TM is not currently running" << endl << endl;
        return;
    }

    cout << endl << "Quit Turing Machine on input \"" << tape.input << "\"" << endl;
    cout << "Turing Machine did not accpet or reject input string \"" << tape.input;
    cout << "\" in " << tape.transitions <<" transition" << endl << endl;


    TMstatus = run;
    tape.status = tape.quit;

    tape.reset();

    return;
}
//question is the current cell to the right or left
void TuringMachine::commandR()
{
    //qeustion, if string is deleted while Tm is running, currently it allows itself to finish
    if(inputList.empty() && TMstatus != running)
    {
        cout << endl << "Input list is empty" << endl << endl;

        tape.reset();

        return;
    }
    if (TMstatus == run || TMstatus == unrun)
    {
        string input = "";
        int inputIndex = 0;

        cout << endl << "Enter the index of the string to run: ";
        getline(cin,input);
        if (input.empty())
            return;

        input = trim(input);
        if (input.empty())
        {
            cout << "Input must be exactly one number" << endl << endl;
            return;
        }

        try
        {
        inputIndex = std::stoi(input) - 1;
        }
        catch (std::invalid_argument)
        {
            cout << "Invalid argument" << endl << endl;
            return;
        }

        if (inputIndex < 0 || inputIndex > inputList.size() - 1)
        {
            cout << "Invalid input" << endl << endl;
            return;
        }

        cout << "Running TM on input: \"" << inputList.at(inputIndex) << "\"" << endl << endl;
        TMstatus = running;

        //set class variables
        tape.reset();
        tape.transitions = 0;
        tape.status = tape.nil;
        tape.input = inputList.at(inputIndex);


        //load current state
        for (int i = 0; i < states.size(); i++)
        {
            if (states.at(i)->state == startState)
            {
                tape.stateIndex = i;
                break;
            }
        }


        //load string into Tape
        for (int i = 0; i < inputList.at(inputIndex).size(); i++)
        {
            if (inputList.at(inputIndex).at(i) == '\\')
                continue;
            tape.tape.push_back(inputList.at(inputIndex).at(i));
        }

        //empty string
        if(tape.tape.empty())
        {
            tape.tape.push_back('-');
        }

        //print ID (calculates i from the max id where current state is in the middle)
        int i = ((tape.index - maxID) < 0) ? 0 : (tape.index - maxID);
        int maxI = (tape.tape.size() > (tape.index + maxID)) ? (tape.index + maxID) : tape.tape.size();
        cout << tape.transitions << ".\t";
        // ID is truncated
        if (i != 0)
            cout << "<";
        //prints Tape
        bool printedState = false;
        for (; !printedState || (i < maxI); i++)
        {
            if (i == tape.index)
            {
                cout << "[" << states.at(tape.stateIndex)->state << "]";
                printedState = true;
            }
            cout << tape.tape.at(i);
        }
        //ID is truncated
        if (i != tape.tape.size())
            cout << ">";
    }

    bool accept = false;
    bool reject = false;

    // actually do the transitions
    for (int i = 0; i < maxTransitions; i++)
    {
        if (states.at(tape.stateIndex)->isFinalState)
        {
            accept = true;
            break;
        }
        //check valid state of TM
        if (tape.index < 0 || reject)
        {
            reject = true;
            break;
        }

        tape.transitions++;

        for (int i2 = 0; i2 < states.at(tape.stateIndex)->transitions.size(); i2++)
        {
            reject = true;
            if (states.at(tape.stateIndex)->transitions.at(i2)->read == tape.tape.at(tape.index))
            {
                reject = false;

                //write char
                tape.tape.at(tape.index) = states.at(tape.stateIndex)->transitions.at(i2)->write;

                //move tapehead
                if (states.at(tape.stateIndex)->transitions.at(i2)->move == 'r')
                    tape.index ++;
                else if (states.at(tape.stateIndex)->transitions.at(i2)->move == 'l')
                    tape.index --;

                //change state
                for (int i3 = 0; i3 < states.size(); i3++)
                {
                    if (states.at(i3)->state == states.at(tape.stateIndex)->transitions.at(i2)->nextState)
                    {
                        tape.stateIndex = i3;
                        break;
                    }
                }

                break;
            }
        }
        if (tape.index >= tape.tape.size())
        {
            tape.tape.push_back(blankCharacter);
        }
        if (states.at(tape.stateIndex)->isFinalState)
        {
            accept = true;
            break;
        }
        //check valid state of TM
        if (tape.index < 0 || reject)
        {
            reject = true;
            break;
        }
    }

    cout << endl;
    //print ID (calculates i from the max id where current state is in the middle)
    int i = ((tape.index - maxID) < 0) ? 0 : (tape.index - maxID);
    int maxI = (tape.tape.size() > (tape.index + maxID)) ? (tape.index + maxID) : tape.tape.size();
    cout << tape.transitions << ".\t";
    // ID is truncated
    if (i != 0)
        cout << "<";
    //prints Tape
    bool printedState = false;
    for (; !printedState || (i < maxI); i++)
    {
        if (i == tape.index)
        {
            cout << "[" << states.at(tape.stateIndex)->state << "]";
            printedState = true;
        }
        cout << tape.tape.at(i);
    }
    //ID is truncated
    if (i != tape.tape.size())
        cout << ">";
    cout << endl;

    //print final state
    if (accept)
    {
        cout << endl << "Turing Machine accepted input \"" << tape.input << "\"";
        cout << " in " << tape.transitions <<" transitions" << endl;

        TMstatus = run;
        tape.status = tape.accepted;

        tape.reset();
    }
    //print final state
    if (reject)
    {
        //rejected
        cout << endl << "Turing Machine rejected input \"" << tape.input << "\"";
        cout << " in " << tape.transitions <<" transitions" << endl;

        TMstatus = run;
        tape.status = tape.rejected;

        tape.reset();
    }

    cout << endl;

    return;
}

void TuringMachine::commandE()
{
    string input = "";
    int size = 0;

    cout << endl << "Enter the maximum transitions to perform [current = " << maxTransitions << "]: ";
    getline(cin,input);
    if (input.empty())
    {
        return;
    }

    input = trim(input);
    if (input.empty())
    {
        cout << "Input must be exactly one number" << endl << endl;
        return;
    }

    try
    {
    size = std::stoi(input);
    }
    catch (std::invalid_argument)
    {
        cout << "Invalid argument" << endl << endl;
        return;
    }

    if (size < 1)
    {
        cout << "Invalid input" << endl << endl;
        return;
    }

    maxTransitions = size;

    cout << "Maximum transitions = " << maxTransitions << endl << endl;

    return;
}

void TuringMachine::commandW()
{
    cout << endl
            << "Course: CPTS 322" << endl
            << "Semester: Spring" << endl
            << "Year: 2025" << endl
            << "Instructor: Neil Corrigan" << endl
            << "Author: Ethan Kanyid" << endl
            << "Version: 1.0" << endl << endl;

    cout << "TM information: " << endl
            << "Name of TM: " << filename << endl
            << "Definition: " << definition << endl << endl;

    cout << "Status: " << endl;
    if (TMstatus == unrun)
        cout << "TM has not been run" << endl << endl;
    else if (TMstatus == running)
    {
        cout << "TM is running on \"" << tape.input << "\" and has not been accepted or rejected in ";
        cout << tape.transitions << " transitions" << endl << endl;
    }
    else if (TMstatus == run)
    {
        cout << "TM was run on \"" << tape.input << "\" ";
        if (tape.status == tape.nil)
            cout << "but was not accepted or rejected in ";
        else if (tape.status == tape.accepted)
            cout << "and was accepted in ";
        else if (tape.status == tape.rejected)
            cout << "and was rejected in ";
        else if (tape.status == tape.quit)
            cout << "and was quit after ";
        cout << tape.transitions << " transitions" << endl << endl;
    }

    cout << "Configuration settings: " << endl
            << "Status of input list: ";
    if (!changedInput)
        cout << "un";
    cout << "changed" << endl << endl;

    cout << "Instantaneous description: " << maxID << endl
            << "Number of transitions: " << maxTransitions << endl << endl;

    return;
}

void TuringMachine::commandT()
{
    string input = "";
    int size = 0;

    cout << endl << "Enter the maximum instantaneous description [current = " << maxID << "]: ";
    getline(cin,input);
    if (input.empty())
    {
        return;
    }

    input = trim(input);
    if (input.empty())
    {
        cout << "Input must be exactly one number" << endl << endl;
        return;
    }

    try
    {
    size = std::stoi(input);
    }
    catch (std::invalid_argument)
    {
        cout << "Invalid argument" << endl << endl;
        return;
    }

    if (size < 1)
    {
        cout << "Invalid input" << endl << endl;
        return;
    }

    maxID = size;

    cout << "Instantaneous description = " << maxID << endl << endl;

    return;
}

void TuringMachine::commandV()
{
    cout << endl << filename << endl;
    cout << definition << endl << endl;

    cout << "Q = {";
    for (int i = 0; i < states.size() - 1; i++)
    {
        cout << states.at(i)->state << ", ";
    }
    cout << states.back()->state << "} " << endl << endl;

    cout << "\u03A3 = {";
    for (int i = 0; i < inputAlphabet.size() - 1; i++)
    {
        cout << inputAlphabet.at(i) << " ";
    }
    cout << inputAlphabet.back() << "} " << endl << endl;

    cout << "\u0393 = {";
    for (int i = 0; i < tapeAlphabet.size() - 1; i++)
    {
        cout << tapeAlphabet.at(i) << " ";
    }
    cout << tapeAlphabet.back() << "} " << endl << endl;

    for (int i = 0; i < states.size(); i++)
    {
        for (int i2 = 0; i2 < states.at(i)->transitions.size(); i2++)
        {
            cout << "\u03b4("<<states.at(i)->state << ", " << states.at(i)->transitions.at(i2)->read;
            cout << ") = (" << states.at(i)->transitions.at(i2)->nextState;
            cout << ", " << states.at(i)->transitions.at(i2)->write;
            cout << ", " << states.at(i)->transitions.at(i2)->move << ")" << endl;
        }
    }

    cout << endl << "q0 = " << startState << endl << endl;

    cout << "B = " << blankCharacter << endl << endl;

    bool prevState = false;
    cout << "F = {";
    for (int i = 0; i < states.size() - 1; i++)
    {
        if (states.at(i)->isFinalState)
        {
            if (prevState)
                cout << ", ";
            cout << states.at(i)->state;
            prevState = true;
        }

    }
    if (prevState)
        cout << ", ";
    if (states.back()->isFinalState)
        cout <<states.back()->state;
    cout << "}" << endl;

    cout << endl;

    return;
}

static string trim(string str)
{

    stringstream ss(str);
    string temp = "";

    ss >> str;
    while (ss >> temp);
    if (!temp.empty())
        return "";

    return str;
}
