#include "text-edit.h"

int main (int argc, char *argv[])
{
    vector<string> *buffer = new vector<string>;

    int line = 1;
    int begin = 0;
    int end = 0;
    char command = '\0';
    char temp = '\0';
    bool change = false;
    bool staychanged = false;
    string feed = "";
    string filename = "";

    if (argc > 2)
    {
        cout << "Exception: Too many arguments." << endl;
        return -1;
    }
    else if (argc == 2)
    {
        filename = (string)argv[1];

        read_file(filename, buffer);
    }

    cout << "Welcome to Notepad--!" << endl << "Enter 'H' for help and 'Q' to quit." << endl;
    for (int i = 0; i < 80; i++)
        cout << "-";
    cout << endl;

    while(command != 'Q')
    {
        if (staychanged)
            cout << line << "!> ";
        else
            cout << line << "> ";
        cin >> command;

        temp = getchar();

        if (!isspace(temp))
            command = '\0';

        switch (command)
        {
            case 'q':
                command = 'Q';
            case 'Q':
                if (staychanged)
                { 
                    cout << "Would you like to save the file? (Y/n) ";
                    cin >> temp;
                }

                if (temp != 'Y')
                    break;
                cin.ignore();

            case 'w':
            case 'W':
                if (temp != '\n')
                    getline(cin, filename);
                if (filename == "")
                {
                    cout << "Enter filename: ";
                    getline(cin, filename);
                }

                write(filename, buffer);
                staychanged = false;
                break;

            case 'j':
            case 'J':
                cin >> line;
                line = jump(line, buffer);
                break;

            case 'i':
            case 'I':
                if (temp != '\n')
                    getline(cin, feed);
                else
                    feed = "";

                change = insert_at(line, feed, buffer);
                if (!staychanged && change)
                    staychanged = change;
                break;

            case 'a':
            case 'A':
                if (temp != '\n')
                    getline(cin, feed);
                else
                    feed = "";

                change = insert_after(line, feed, buffer);
                if (!staychanged && change)
                    staychanged = change;
                break;

            case 'l':
            case 'L':
                if (temp == '\n')
                {
                    list_buffer(buffer);
                    break;
                }
                
                cin >> begin;
                temp = getchar();

                if (temp == '\n')
                {
                    list_buffer(buffer, begin, begin);
                }
                else
                {
                    cin >> end;  
                    list_buffer(buffer, begin, end);
                }
                break;

            case 'd':
            case 'D':
                if (temp == '\n')
                {
                    change = remove(buffer, line, line);
                    if (!staychanged && change)
                        staychanged = change; 
                    break;
                }
                
                cin >> begin;
                temp = getchar();

                if (temp == '\n')
                {
                    change = remove(buffer, begin, begin);
                }
                else
                {
                    cin >> end;  
                    change = remove(buffer, begin, end);
                }
                if (!staychanged && change)
                    staychanged = change;
                break;

            case 'h':
            case 'H':
                help();
                break;

            default:
                cout << "Invalid Input" << endl;
                cout << "Enter H for Help" << endl << endl;

        }
        if (buffer->empty() || buffer->size() < line)
        {
            line = 1;
        }
    
    }

    delete buffer;


    return 0;
}