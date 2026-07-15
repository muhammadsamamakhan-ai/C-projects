#include "Validation.h"
#include <iostream>
#include <string>

using namespace std;

int getValidatedInteger(string prompt, int minVal, int maxVal)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val)
        {
            if (val >= minVal && val <= maxVal)
                return val;
            else
                cout << "Error: Out of bounds! Please enter an integer between "
                     << minVal << " and " << maxVal << ".\n";
        }
        else
        {
            cout << "Error: Invalid numeric input type! Please try again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

double getValidatedDouble(string prompt, double minVal, double maxVal)
{
    double val;
    while (true)
    {
        cout << prompt;
        if (cin >> val)
        {
            if (val >= minVal && val <= maxVal)
                return val;
            else
                cout << "Error: Out of range! Please enter a value between "
                     << minVal << " and " << maxVal << ".\n";
        }
        else
        {
            cout << "Error: Invalid numeric type! Please enter a valid number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

string getValidatedString(string prompt, bool allowComma)
{
    string val;
    while (true)
    {
        cout << prompt;
        getline(cin >> ws, val);

        if (val.empty())
        {
            cout << "Error: Input cannot be empty. Please enter something!\n";
            continue;
        }
        if (!allowComma && val.find(',') != string::npos)
        {
            cout << "Error: Special character ',' is forbidden to preserve storage integrity!\n";
            continue;
        }
        return val;
    }
}

string getValidatedName(string prompt)
{
    string val;
    while (true)
    {
        cout << prompt;
        getline(cin >> ws, val);

        if (val.empty())
        {
            cout << "Error: Input cannot be empty!\n";
            continue;
        }
        if (val.find(',') != string::npos)
        {
            cout << "Error: Special character ',' is not allowed!\n";
            continue;
        }

        bool hasLetter = false;
        for (size_t i = 0; i < val.length(); i++)
        {
            if (isalpha(val[i])) { hasLetter = true; break; }
        }
        if (!hasLetter)
        {
            cout << "Error: Name/Username must contain at least one letter!\n";
            continue;
        }

        return val;
    }
}

char getValidatedChar(string prompt, string validChars)
{
    char val;
    while (true)
    {
        cout << prompt;
        if (cin >> val)
            if (validChars.find(val) != string::npos)
                return val;
        cout << "Error: Invalid input! Choose from: (" << validChars << ")\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}