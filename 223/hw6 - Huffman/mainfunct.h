#pragma once
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

void write_bool(string& message);

void read_bool(string& message);

bool get_message(string filename, string& message);

bool valid_extension(string& filename);

bool read_alphabet(string& alphabet);