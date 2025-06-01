#include "mainfunct.h"

void write_bool(string& message)
{
    int val = 0;
    int buffer = 0;
    char ch = '\0';
    string temp = "";

    while(!message.empty())
    {
        for (int i = 0; i < 7; i++) // chars dont use the lm bit
        {
            if (!message.empty())
            {
                val += (message.back() - '0')*(pow(2,i));
                message.pop_back();
            }
            else
            {
                buffer++;
            }
        }
        ch = val;
        temp.insert(temp.begin(), ch);
        val = 0;
    }
    ch = buffer;
    temp.insert(temp.begin(), ch);

    message = temp;
}

void read_bool(string& message)
{
    stringstream yikes;
    int val = 0;

    int buffer = message[0];
    message.erase(0,1);

    while(!message.empty())
    {
        char ch = message[0];

        for (int i = 6; i >= 0; i--)
        {
            val = ch/(pow(2,i));
            if (val)
                ch = ch - (pow(2,i));
            if (buffer > 0)
            {
                buffer--;
            }
            else
            {
                yikes << val;
            }
        }

        message.erase(0,1);
    }

    //yikes << endl;
    message = yikes.str();
}

bool get_message(string filename, string& message)
{
    stringstream temp;

    //open message file
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Could not open file: " << filename << endl;
        return 0;
    }

    while (getline(file, message))
        temp << message << "\n";
        
    file.close();

    message = temp.str();
    message.pop_back();

    return 1;
}

bool valid_extension(string& filename)
{
    int x = filename.find('.');

    string name = filename.substr(0,++x);

    string ext = filename.substr(x);

    if (ext != "txt" && ext != "encoded" && ext != "decoded" && ext != "cpp" && ext != "h")
    {
        cout << "Invalid extension: " << ext << endl;
        return 0;
    }

    filename = name;

    return 1;
}

bool read_alphabet(string& alphabet)
{
    string result = "";

    //open alphabet file
    ifstream bet(alphabet);
    if (!bet.is_open())
    {
        cout << "Could not open file: " << alphabet << endl;
        return 0;
    }

    getline(bet, result);
    bet.close();

    alphabet = result;

    return 1;
}
