#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void read_file(string filename, vector<string> *buffer)
{
    ifstream file;
    file.open(filename);

    string temp;
    while(getline(file,temp))
    buffer->push_back(temp);

    return;
}

void write(string filename, vector<string> *buffer)
{
    ofstream file;
    stringstream temp;
    file.open(filename);

    for(int i = 0; i < buffer->size(); i++)
    {
        file << buffer->at(i) << endl;
    }

    file.close();

    cout << " Buffer written to " << filename << "." << endl;

    return;
}

int jump(int line, vector<string> *buffer)
{
    if (line == -1)
        line = buffer->size();

    if (buffer->size() < line || line < 1)
    {
        cout << "Exception: Invalid line number; size is "<< buffer->size() << endl;
        return line;
    }
    return line;
}

bool insert_at(int line, string feed, vector<string> *buffer)
{
    buffer->insert(buffer->begin() + line - 1, feed);

    return true;
}

bool insert_after(int line, string feed, vector<string> *buffer)
{   
    if (buffer->empty())
        buffer->insert(buffer->begin(), feed);
    else
        buffer->insert(buffer->begin() + line, feed);

    return true;
}

bool remove(vector<string> *buffer, int begin, int end)
{
    if ((begin < 1 && end != -1) || (begin > end && end != -1))
    {
        cout << "Exception: Invalid range" << endl;
        return false;
    }
    if (begin == -1)
    {
        begin = buffer->size();
    }
    if (end == -1)
    {
        end = buffer->size();
    }
    if (end > buffer->size())
    {
        cout << begin << " " << end << " " << buffer->size() <<  "Exception: Invalid range" << endl;
        return false;    
    }

    for(int i = begin - 1; i < end; i++)
    {
        buffer->erase(buffer->begin() + begin - 1);
    }

    return true;
}

void list_buffer(vector<string> *buffer, int begin = 1, int end = -1)
{
    if ((begin < 1 && end != -1) || (begin > end && end != -1) || (begin == end && end > buffer->size()))
    {
        cout << "Exception: Invalid range" << endl;
        return;
    }
    if (end > buffer->size() || end == -1)
    {   
        end = buffer->size();
    }
    if (begin == -1)
    {
        begin = end;
    }

    for (int i = 0; i < 80; i++)
        cout << "-";
    cout << endl;

    for(begin -= 1;begin < end; begin++)
    {
        cout << begin +1 << " " << buffer->at(begin) << endl;
    }
    for (int i = 0; i < 80; i++)
        cout << "-";
    cout << endl;
    
    return;
}

void help()
{
    cout << "W [<filename>] - Writes the contents of the current \"buffer\" to a file. If no filename is given,";
    cout << " then it uses the file name of the file that has been opened. If no file has been opened,"; 
    cout << " then the editor will prompt the user for a file name, which will be used going forward. " << endl << endl;

    cout << "J <line number> - Jump to a line in the file. -1 will jump to the end of the file, 1 will jump to the beginning of the file.";
    cout << " The numeric argument should be checked that it is a valid location in the file." << endl << endl;

    cout << "I [<some text>] - Insert the text at the \"current\" line. If no text is given, will insert a blank line" << endl << endl;

    cout << "A [<some text>] - Insert the text after the \"current\" line. If no text is given, will insert a blank line" << endl << endl;

    cout << "L [<line number>] [<line number>] - Lists the contents of the buffer. If no line numbers are given, lists the contents of the entire buffer."; 
    cout << " If one line number is given, shows only that line. If 2 line numbers are given, lists all the lines between the numbers,";
    cout << " including the lines at the start and end number. In the list output, the line numbers requested should be displayed in some fashion.";
    cout << " If -1 is given as a single number, display the last line. If -1 is given as start, then that is invalid. If 2 numbers are given,";
    cout << "and the second one is -1, then display from the first line number to the end of the file. If the second number is larger";
    cout << " than the maximum number of lines in the file, display the lines from the start number to the end of the file." << endl << endl;

    cout << "D [<line number>] [<line number>] - Deletes one or more lines. If no line numbers are given, deletes the current line.";
    cout << " If a single line number is given, deletes that line. If 2 line numbers are given, deletes the range of lines,";
    cout << " inclusive of the start and end line numbers. The first line number given is the start, and the second is the end.";
    cout << " The program should check to see if the line numbers are in the appropriate order, and if the range is valid" << endl << endl;

    cout << "Q - Quits the editor. If the buffer has been modified and not written,";
    cout << " the close command should prompt the user and ask if they want to save changes before quitting." << endl << endl;

    cout << "H - Shows a help message that prints out the command listed here, and what they do.";
    cout << " Should also be shown in the case of an \"Invalid Command\"." << endl << endl;

    return;
}