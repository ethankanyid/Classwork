#include "text-edit-support.cpp"

void read_file(string filename, vector<string> *buffer);

void write(string filename, vector<string> *buffer);

void help();

int jump(int line, vector<string> *buffer);

bool insert_at(int line, string feed, vector<string> *buffer);

bool insert_after(int line, string feed, vector<string> *buffer);

bool remove(vector<string> *buffer, int begin, int end);

void list_buffer(vector<string> *buffer, int begin,int end);
