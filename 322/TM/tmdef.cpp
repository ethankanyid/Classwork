#include "TM.h"
#include "errorlog.h"

using std::ifstream;
using std::string;
using std::isalnum; //to check for alphanumeric values
using std::isprint; // to check if something is printable

//fix - the only necessary aspects are the initial state and the blank char

/*  lowers a string to lowercase */
static string stolower(string input);

bool TuringMachine::initDef()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;
    char ch = 0;

    //find states label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        else
            nextLabel = file.tellg();
        if (input == "states:")
            break;
    }
    file.seekg(pos);

    //read the first lines of the TM def.
    while(file.get(ch) && file.tellg() <= nextLabel)
        definition += ch;

    file.close();

    error |= readStates();

    error |= readFinStates();

    error |= readInitState();

    error |= readTAlph();

    error |= readInAlph();

    error |= readBlankChar();

    error |= readTransFun();

    return error;
}

bool TuringMachine::readStates()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "states:")
            break;
        else
            pos = file.tellg();
    }
    //find next label
    nextLabel = file.tellg();
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            break;
        else
            nextLabel = file.tellg();
    }

    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "states:")
    {
        errorLog("'States:' tag missing or misordered");
        return 1;
    }

    while((file >> input) && file.tellg() <= nextLabel)
    {
        bool invalidChar = false;
        if (input.empty())
            return 1;
        for (int i = 0; i < input.size(); i++)
        {
            if (!(isalnum(input.at(i)) || input.at(i) == '_' || input.at(i) == '-'))
            {
                invalidChar = true;
                break;
            }
        }
        if (!invalidChar)
        {
            bool validState = true;
            for (int i = 0; i < states.size(); i++)
            {
                if (input == states.at(i)->state)
                {
                    validState = false;
                    break;
                }
            }
            if (validState)
                states.push_back(new States(input));
            else
            {
                error = true;
                errorLog(input + " is a duplicate state");
            }
        }
        else
        {
            error = true;
            errorLog(input + " contains invalid characters for a State");
        }
    }

    file.close();

    if (states.empty())
    {
        error = true;
        errorLog("Invalid number of states for State: there must be at least 1");
    }

    return error;
}

bool TuringMachine::readInAlph()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "input_alphabet:")
            break;
        else
            pos = file.tellg();
    }
    //find next label
    nextLabel = file.tellg();
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            break;
        else
            nextLabel = file.tellg();
    }

    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "input_alphabet:")
    {
        errorLog("'Input_Alphabet:' tag missing or misordered");
        return 1;
    }

    /* read in input alphabet */
    while((file >> input) && file.tellg() <= nextLabel)
    {
        bool validChar = false;

        //check for non char
        if (input.size() != 1)
        {
            errorLog("Invalid Input Char: " + input);
            error = true;
            continue;
        }

        //check valid char
        for (int i = 0; i < tapeAlphabet.size(); i++)
        {
            if (tapeAlphabet.at(i) == input.at(0))
            {
                validChar = true;
                break;
            }
        }
        for (int i = 0; i < inputAlphabet.size(); i++)
        {
            if (inputAlphabet.at(i) == input.at(0))
            {
                validChar = false;
                break;
            }
        }
        if (!validChar)
        {
            errorLog(input + " is not a valid char for Input_Alphabet");
            error = true;
        }
        else
            inputAlphabet.push_back(input.at(0));
    }

    file.close();

    return error;
}

bool TuringMachine::readTAlph()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "tape_alphabet:")
            break;
        else
            pos = file.tellg();
    }
    //find next label
    nextLabel = file.tellg();
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            break;
        else
            nextLabel = file.tellg();
    }

    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "tape_alphabet:")
    {
        errorLog("'Tape_Alphabet:' tag missing or misordered");
        return 1;
    }

    /* read in tape alphabet */
    while((file >> input) && file.tellg() <= nextLabel)
    {
        //check for non char
        if (input.size() != 1)
        {
            errorLog("Invalid Tape Char: " + input);
            error = true;
            continue;
        }

        char c = input.at(0);
        if (isprint(c) && c != '\\' && c != '[' && c != ']' && c != '<' && c != '>')
        {
            bool validChar = true;
            //check duplicate char
            for (int i = 0; i < tapeAlphabet.size(); i++)
            {
                if (tapeAlphabet.at(i) == input.at(0))
                {
                    validChar = false;
                    break;
                }
            }
            if (!validChar)
            {
                errorLog(input + " is not a valid char for Tape_Alphabet");
                error = true;
            }
            else
                tapeAlphabet.push_back(c);
        }
        else
        {
            errorLog(input + " is not a valid char for Tape_Alphabet");
            error = true;
        }
    }

    if (tapeAlphabet.empty())
    {
        error = true;
        errorLog("Invalid number of characters for Tape_Alphabet: there must be at least 1 (the blank)");
    }

    file.close();

    return error;
}

bool TuringMachine::readTransFun()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";

    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "transition_function:")
            break;
        else
            pos = file.tellg();
    }
    //find next label
    nextLabel = file.tellg();
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            break;
        else
            nextLabel = file.tellg();
    }

    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "transition_function:")
    {
        errorLog("'Transition_Function:' tag missing or misordered");
        return 1;
    }

    /* read in transition functions */
    while((file >> input) && file.tellg() <= nextLabel)
    {
        States* tempState = nullptr;
        //check state in state list
        for (int i = 0; i < states.size(); i++)
        {
            if (states.at(i)->state == input)
            {
                tempState = states.at(i);
                break;
            }
        }
        if (tempState == nullptr)
        {
            errorLog(input + " is not a valid state for Transition_Function");
            error = true;
        }

        //read input char
        file >> input;
        //check for non char
        if (input.size() != 1)
        {
            errorLog(input + " is not a valid input char for Transition_Function");
            error = true;
        }
        else
        {
            bool foundChar = false;
            //check valid char
            for (int i = 0; i < tapeAlphabet.size(); i++)
            {
                if (tapeAlphabet.at(i) == input.at(0))
                {
                    foundChar = true;
                    break;
                }
            }
            if (!foundChar)
            {
                errorLog(input + " is not a valid char for Transition_Function");
                error = true;
            }
        }

        //make sure state and char do not have transition already
        if (tempState != nullptr)
        {
            bool validChar = true;
            //check for duplicate transition
            for (int i = 0; i < tempState->transitions.size(); i++)
            {
                if (tempState->transitions.at(i)->read == input.at(0))
                {
                    validChar = false;
                    break;
                }
            }
            if (validChar)
            {
                tempState->transitions.push_back(new States::Transitions());
                tempState->transitions.back()->read = input.at(0);
            }
            else
            {
                errorLog(input + " is a duplicate transition for state " + tempState->state);
                error = true;
            }
        }

        //read next state
        file >> input;
        bool foundState = false;
        //check valid state
        for (int i = 0; i < states.size(); i++)
        {
            if (states.at(i)->state == input)
            {
                foundState = true;
                break;
            }
        }
        if (foundState && tempState != nullptr)
            tempState->transitions.back()->nextState = input;
        else if (!foundState)
        {
            errorLog(input + " is not a valid state for Transition_Function");
            error = true;
        }

        //read output char
        file >> input;
        //check for non char
        if (input.size() != 1)
        {
            errorLog(input + " is not a valid output char for Transition_Function");
            error = true;
        }
        else
        {
            bool foundChar = false;
            //check valid char
            for (int i = 0; i < tapeAlphabet.size(); i++)
            {
                if (tapeAlphabet.at(i) == input.at(0))
                {
                    foundChar = true;
                    break;
                }
            }
            if (foundChar && tempState != nullptr)
                tempState->transitions.back()->write = input.at(0);
            else if (!foundChar)
            {
                errorLog(input + " is not a valid char for Transition_Function");
                error = true;
            }
        }

        //read movement char
        file >> input;
        //check for non char
        if (input.size() != 1)
        {
            errorLog(input + " is not a valid movement char for Transition_Function");
            error = true;
        }
        else
        {
            input.at(0) = tolower(input.at(0));
            if ((input.at(0) == 'r' || input.at(0) == 'l') && tempState != nullptr)
                tempState->transitions.back()->move = input.at(0);
            else if (input.at(0) != 'r' && input.at(0) != 'l')
            {
                errorLog(input + " is not a valid movement char for Transition_Function");
                error = true;
            }
        }
    }

    file.close();

    /*  ensure final states have no transitions out of it */
    for (int i = 0; i < states.size(); i++)
    {
        if (states.at(i)->isFinalState && !states.at(i)->transitions.empty())
        {
            errorLog(states.at(i)->state + " is a final state and not allowed to have transitions out of it");
            error = true;
        }
    }

    return error;
}

bool TuringMachine::readInitState()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "initial_state:")
            break;
        else
            pos = file.tellg();
    }
    //find next label
    nextLabel = file.tellg();
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            break;
        else
            nextLabel = file.tellg();
    }

    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "initial_state:")
    {
        errorLog("'Initial_State:' tag missing or misordered");
        return 1;
    }

    /* read in initial state */
    bool oneState = false;
    while((file >> input) && file.tellg() <= nextLabel)
    {
        bool foundState = false;
        for (int i = 0; i < states.size(); i++)
        {
            if (states.at(i)->state == input)
            {
                foundState = true;
                break;
            }
        }
        //could not find state
        if (!foundState)
        {
            errorLog(input + " is not a valid state for Initial_State");
            error = true;
        }
        if (!oneState)
        {
            startState = input;
            oneState = true;
        }
        else
        {
            errorLog(input + " cannot be an additional Initial_State");
            error = true;
        }
    }

    file.close();

    if (!oneState)
    {
        errorLog("Invalid number of states for Initial_State: there must be exactly 1");
        return 1;
    }

    return error;
}

bool TuringMachine::readBlankChar()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos nextLabel = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "blank_character:")
            break;
        else
            pos = file.tellg();
    }
    //find next label
    nextLabel = file.tellg();
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            break;
        else
            nextLabel = file.tellg();
    }

    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "blank_character:")
    {
        errorLog("'Blank_Character:' tag missing or misordered");
        return 1;
    }

    /* read in blank character */
    bool oneBlank = false;
    while((file >> input) && file.tellg() <= nextLabel)
    {
        //check for non char
        if (input.size() != 1)
        {
            errorLog(input + " is not a valid char for Blank_Character");
            error = true;
        }
        else
        {
            bool foundBlank = false;
            for (int i = 0; i < tapeAlphabet.size(); i++)
            {
                if (tapeAlphabet.at(i) == input.at(0))
                {
                    foundBlank = true;
                    break;
                }
            }
            //could not find blank
            if (!foundBlank)
            {
                errorLog("Blank Character must be in Tape Alphabet");
                error = true;
            }
            if (!oneBlank)
            {
                blankCharacter = input[0];
                oneBlank = true;
            }
            else
            {
                errorLog(input + " cannot be an additional Blank_Character");
                error = true;
            }
        }
    }

    //ensure blank is not in input alphabet
    for (int i = 0; i < inputAlphabet.size(); i++)
    {
        if (inputAlphabet.at(i) == blankCharacter)
        {
            errorLog("Blank Character must not be in Input Alphabet");
            error = true;
            break;
        }
    }

    file.close();

    if (!oneBlank)
    {
        errorLog("Invalid number of characters for Blank_Character: there must be exactly 1");
        return 1;
    }

    return error;
}

bool TuringMachine::readFinStates()
{
    ifstream file(filename + ".def");
    if(!file.is_open())
    {
        errorLog("Failed to open " + filename + ".def");
        return 1;
    }

    //label
    std::streampos endOfFile = file.tellg();
    std::streampos pos = file.tellg();

    string input = "";
    bool error = false;

    //find label
    while(file >> input)
    {
        if (input.find(':') != string::npos)
            input = stolower(input);
        if (input == "final_states:")
            break;
        else
            pos = file.tellg();
    }
    file.seekg(pos);
    if (!(file >> input) && stolower(input) != "final_states:")
    {
        errorLog("'Final_States:' tag missing or misordered");
        return 1;
    }

    /* read in final states */
    while(file >> input)
    {
        bool foundState = false;
        for (int i = 0; i < states.size(); i++)
        {
            if (states.at(i)->state == input)
            {
                if (states.at(i)->isFinalState == true)
                {
                    errorLog(input + " is a duplicate final state for Final_States");
                    error = true;
                }
                states.at(i)->isFinalState = true;
                foundState = true;
                break;
            }
        }
        //could not find final state
        if (!foundState)
        {
            errorLog(input + " is not a valid final state for Final_States");
            error = true;
        }
    }

    return error;
}

static string stolower(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        input.at(i) = tolower(input.at(i));
    }
    return input;
}
