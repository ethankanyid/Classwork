#include <iostream>
#include <fstream>

using namespace std;

char getCommand();

void commandD();

/*  help function uses help.txt */
void commandH();

/*  inserts at end of list, checks for string validity. */
void commandI();

/*  lists the input strings with their index */
void commandL();

/*  quits running TM */
void commandQ();

/*  runs TM at list index */
void commandR();

/*  Set maximum number of transitions to perform */
void commandE();

/*  shows meta data for application */
void commandW();

/*  truncates instantaneous description; default is 32 */
void commandT();

/*  views TM description */
void commandV();


int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        cout << "Too many command line arguments." << endl;
        return 0;
    }

    cout << "Turing Machine anbn succesfully loaded" << endl << endl;

    char command = 0;

    while((command = getCommand()))
    {
        switch (command)
        {
            case 'd':
            {
                commandD();
                break;
            }
            case 'x':
            {
                cout << "Wrote input list to file" << endl;
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
    }

    return 0;
}

char getCommand()
{
    string input ="";

    while (true)
    {
        cout << "Command: ";
        getline(cin, input);

        if(input.empty());
        else if(input.size() > 1)
        {
            cout << "Invalid inputs" << endl;
        }
        else
        {
            break;
        }
    }

    char command = input.at(0);

    return tolower(command);
}

void commandD()
{
    cout << endl << "Enter the index you'd like to delete: 1" << endl;
    cout << "Deleted line 1" << endl << endl;
}

void commandH()
{
    ifstream help_txt("help.txt");
    if(!help_txt.is_open())
    {
        cout << "Failed to open help.txt" << endl;
        return;
    }

    string output = "";

    cout << endl;
    while(getline(help_txt,output))
    {
        cout << output << endl;
    }
    cout << endl;

    help_txt.close();

    return;
}

void commandI()
{
    cout << endl << "Enter the string to insert: ab" << endl;
    cout << "Inserted ab" << endl << endl;

    return;
}

void commandL()
{
    cout << endl;
    cout << 1 << " ba" << endl;
    cout << 2 << " ab" << endl;
    cout << endl;
}

void commandQ()
{
    cout << endl << "Quit Turing Machine on input ba" << endl;
    cout << "Turing Machine did not accpet input string \"ba\" in 1 transition" << endl << endl;
}

void commandR()
{
    cout << endl << "Enter the index of the string to run: 2" << endl;
    cout << "running ab" << endl;
    cout << "[s0] a b - - - - - "<< endl << endl;
}

void commandE()
{
    cout << endl << "Enter the maximum number of transitions to perform: 10" << endl;
    cout << "Max Transitions = 10" << endl << endl;

    return;
}

void commandW()
{
    ifstream info_txt("info.txt");
    if(!info_txt.is_open())
    {
        cout << "Failed to open info.txt" << endl;
        return;
    }

    string output = "";

    cout << endl;
    while(getline(info_txt,output))
    {
        cout << output << endl;
    }
    cout << endl;

    info_txt.close();

    cout << endl << "tm information: " << endl;
    cout << "currently running: ab, 1 transition" << endl;
    // or completed: last input, status of acceptance/quit, number of transitions

    cout << "configuration settings:" << endl;
    cout << "Name: anbn" << endl;
    cout << "Instantaneous Description: 32" << endl;
    cout << "Number of Transitions: 10" << endl << endl;
    //status of tm
    //status of list of input strings


    return;
}

void commandT()
{
    cout << endl << "Enter the maximum instantaneous description: 32" << endl;
    cout << "Instantaneous Description = 32" << endl << endl;

    return;
}

void commandV()
{
    ifstream anbn_def("anbn.def");
    if(!anbn_def.is_open())
    {
        cout << "Failed to open anbn_def" << endl;
        return;
    }

    string output = "";

    cout << endl;
    while(getline(anbn_def,output))
    {
        cout << output << endl;
    }
    cout << endl;

    anbn_def.close();

    return;
}
