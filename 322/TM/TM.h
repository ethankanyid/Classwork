#pragma once
#include <cctype> // for tolower
#include <iostream> //for input and output
#include <string> // for strings
#include <fstream> // for the help file
#include <vector>
#include <sstream>

using std::string;
using std::vector;

/*  is intitialized with constructor argument which holds the filename for xxx.def and xxx.str. */
class TuringMachine
{
    private:
    /****** PRIVATE CLASSES ******/

        /*  contains states and transition function per state
            contains bool for final state status
            must be dynamically allocated. */
        class States
        {
            public:
            /*  holds the valid transitions for this state
                must be dynamically allocated*/
            class Transitions
            {
                public:

                char read;
                string nextState;
                char write;
                char move;

                Transitions()
                {
                    read = 0;
                    nextState = "";
                    write = 0;
                    move = 0;
                }
            };

            string state;
            bool isFinalState;

            //dynamically allocated vector holding transition functions for this state
            vector<Transitions*> transitions;

            States(string stateName)
            {
                state = stateName;
                isFinalState = false;
            }
            ~States()
            {
                //delete dynamically allocated vector for states
                for (int i = 0; i < transitions.size(); i++)
                {
                    delete transitions.at(i);
                }
            }
        };

        /*  holds the tape and any relevant information to the tape */
        class Tape
        {
            public:
            /*  tape for TM to run on */
            vector<char> tape;

            /*  current state index for tape */
            int stateIndex;

            /*  current cell of Tape */
            int index;

            /*  last input run */
            string input;

            /*  how many transitions were performed on the last input*/
            int transitions;

            /*  status of the last input */
            enum {
                nil,
                accepted,
                rejected,
                quit
            } status;

            Tape()
            {
                tape.clear();
                tape.resize(0);

                stateIndex = -1;

                index = 0;

                input = "";

                transitions = 0;

                status = nil;
            }

            /*  resets tape besides input, transitions, and status */
            void reset()
            {
                tape.clear();
                tape.resize(0);

                stateIndex = -1;

                index = 0;

                //needed for previous information
                //tapeInput = "";

                //needed for previous information
                //int tapeTransitions = 0;

                //needed for previous information
                //tapeStatus = nil;
            }
        };

        /*  command methods executable on the TM*/
        /*  commands should not throw errors but instead inform user of error and return to getCommand*/
            /*  deletes input string specified by index. must use delete()
                checks for valid index*/
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

    /********* PRIVATE METHODS *************/

        /*  reads the definition file and stores errors in error log.
            returns 0 on success. calls functions necessary to reading the file*/
        bool initDef();

        /*  helper functions for reading the definition file */
            /*  reads in the states from definition file. checks valid chars of state, duplicates,
                and if no states were defined*/
            bool readStates();

            /*  reads in the alphabet checking for valid chars.
                compares itself to tape.*/
            bool readInAlph();

            /*  reads in tape alphabet checking for valid chars */
            bool readTAlph();

            /*  reads in transfunction checking for valid states, valid characters, and
                valid movement characters*/
            bool readTransFun();

            /*  reads initial state checking for valid state and only one. */
            bool readInitState();

            /*  reads blank character checking for valid char and only one.
                must be found in tape alphabet */
            bool readBlankChar();

            /*  reads final states checking for valid states. */
            bool readFinStates();

        /*  reads the string file. throws out invalid strings. if file does not exist list is empty.
            returns 0 on success although no error is fatal*/
        bool initStr();

        /*  checks for valid strings returns message. checks duplicates and valid chars.
            returns empty string on success although no error is fatal*/
        string validInput(string input);

        /*  private deconstructor and exit for program */
        void destroy();

    /*********** PRIVATE MEMBERS ***********/

        /*  vector holding the input string*/
        vector<string> inputList;

        /*  dynamically allocated vector of valid states and final states*/
        vector<States*> states;

        /*  command line argument and name of TM*/
        string filename;

        /*  single char to hold blank char. only in tape alphabet */
        char blankCharacter;

        /*  single state to hold start state */
        string startState;

        /*  holds blank char, input alph, empty set, and whatever others chars TM uses */
        vector<char> tapeAlphabet;

        /*  only holds chars to be found in input list. and empty set. */
        vector<char> inputAlphabet;

        /*  holds first lines of TM def */
        string definition;

        /*  maxTransitions is defaulted to 1 and is set by the set function */
        int maxTransitions;

        /*  maxID is the instantaneous description length and is set by the truncate function. default is 32.
            value is applied to both side of ID not total*/
        int maxID;

        /*  indicates whether the TM has been run */
        enum {
            unrun,
            running,
            run
        } TMstatus;

        /*  indicates whether the input list has been changed */
        bool changedInput;

        Tape tape;

    public:

    /********* PUBLIC METHODS ***************/

        /* initializes the TM with the name */
        TuringMachine(string arg1);

        /* must deallocate dynamic memory from inputList and states */
        ~TuringMachine();

        /*runs the command passed in on the TM */
        bool runCommand(char command);

        /*prompts the user for a command and returns only a single char in lower case*/
        char getCommand();

    /********* PUBLIC MEMBERS ***************/
    //none
};
