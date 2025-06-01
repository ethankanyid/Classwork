#include "tree.h"
#include "mainfunct.h"

int main(int const argc, char const *argv[])
{
    string action = "";
    string alphabet = "";
    string filename = ""; 
    string message = "";

    if (argc == 4)
    {
        action = argv[1];
        alphabet = argv[2];
        filename = argv[3];
    }
    else
    {
        cout << "Please pass in 3 arguments. ('decode/encode' 'alphabet file' 'filename')" << endl;

        return -1;
    }

    //string for alphabet
    if (!read_alphabet(alphabet))
    {
        cout << "Invalid alphabet." << endl;
        return -1;
    }

    if (!get_message(filename, message))
    {
        cout << "Invalid message." << endl;
        return -1;
    }

    //checks valid filename adjusts filename to exclude extension
    if (!valid_extension(filename))
    {
        cout << "Invalid filename." << endl;
        return -1;
    }

    try
    {
        Tree tree(alphabet);

        if (action == "encode")
        {
            cout << "size unencoded: " << message.size() << endl;
            tree.encode(message);
            cout << "size encoded: " << message.size() << endl;
            write_bool(message);
            cout << "size bool: " << message.size() << endl;
        }
        else if (action == "decode")
        {
            cout << "size bool: " << message.size() << endl;
            read_bool(message);
            cout << "size encoded: " << message.size() << endl;
            tree.decode(message);
            cout << "size decoded: " << message.size() << endl;
        }
        else 
        {
            cout << "Invalid action" << endl;
            return -1;
        }

        ofstream file(filename + action + "d");
        file << message;
        file.close();

    }
    catch(string error)
    {
        cout << error << endl;
    }

    return 0;
}
