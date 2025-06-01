#include "TM.h"

using namespace std;

//fix must be able to take path to file
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid number of command line arguments. (expected 2)" << endl;
        return 0;
    }

    TuringMachine TM(argv[1]);

    while (TM.runCommand(TM.getCommand()));

    return 0;
}
