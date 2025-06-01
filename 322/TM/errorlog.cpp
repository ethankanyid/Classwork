#include "errorlog.h"

using std::string;
using std::ofstream;
using std::endl;
using std::cout;

static int errored = false;

void errorLog(string error)
{
    ofstream error_log;

    if (errored == false)
    {
        errored = true;
        error_log.open("error.log", std::ios::trunc);  // truncates file if it exists
        error_log << "Errors Caught: " << endl << endl;
    }
    else
    {
        error_log.open("error.log", std::ios::app);  // appends to file
    }

    if (!error_log.is_open())
    {
        cout << "Failed to open error.log" << endl;
        return;
    }

    error_log << error << endl;

    error_log.close();

    return;
}
