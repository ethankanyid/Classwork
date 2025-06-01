#include <iostream>
#include <string>

using namespace std;

/* shifts a text by the key passed in.
has capacity for lower case and upper case.
keeps the character given otherwise. */
string shift(string text, int key)
{
    string shifttext = text;
    int character = 0;

    for (int i = 0; i < text.size(); i++)
    {
        if(text[i] >= 'A' && text[i] <= 'Z')
        {
            character = (text[i] - key + 26 - 'A') % 26;
            shifttext[i] = character + 'A';
        }
        else if(text[i] >= 'a' && text[i] <= 'z')
        {
            character = (text[i] - key + 26 - 'a') % 26;
            shifttext[i] = character + 'a';
        }
        else if (text[i] >= 32 && text[i] <= 127)
        {
            shifttext[i] = text[i];
        }
        else
        {
            return "Shift broke.\n";
        }
    }

    return shifttext;
}

int main(int argc, char* argv[])
{
    string text = "Olssv Dvysk!";

    if (argc > 1)
    {
        text = argv[1];
    }

    cout << "Text is \"" << text << "\".\n";

    for (int i = 0; i <= 25; i++)
    {
        cout << i << "\t" << shift(text, i) << endl;
    }

    return 0;
}
