#pragma once
#include <iostream> //for input and output
#include <string> // for strings
#include <fstream> // for the help file

/*  writes out to error.log with newlines. truncates file on first error */
void errorLog(std::string error);
