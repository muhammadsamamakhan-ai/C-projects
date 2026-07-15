#define _CRT_SECURE_NO_WARNINGS
#include "Helpers.h"
#include <cctype>

int inputInteger()
{
    int value;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid! Enter a whole number: ";
    }
    cin.ignore(1000, '\n');
    return value;
}

double inputDouble()
{
    double value;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid! Enter a number: ";
    }
    cin.ignore(1000, '\n');
    return value;
}

string inputString()
{
    string value;
    bool valid;
    do
    {
        getline(cin >> ws, value);
        valid = !value.empty();
        for (int i = 0; i < (int)value.length(); i++)
            if (!isalpha(value[i]) && value[i] != ' ') { valid = false; break; }
        if (!valid) cout << "Letters only please: ";
    } while (!valid);
    return value;
}

void inputBrandName(char* brand, int maxSize)
{
    string value;
    bool valid;
    do
    {
        getline(cin >> ws, value);
        valid = !value.empty();
        for (int i = 0; i < (int)value.length(); i++)
            if (!isalpha(value[i]) && value[i] != ' ') { valid = false; break; }
        if (!valid) cout << "Letters only please: ";
    } while (!valid);
    strncpy(brand, value.c_str(), maxSize - 1);
    brand[maxSize - 1] = '\0';
}

string inputExpiryDate()
{
    string value;
    bool hasAlpha, hasDigit, hasSymbol, valid;
    do
    {
        getline(cin >> ws, value);
        hasAlpha = hasDigit = hasSymbol = false;
        for (int i = 0; i < (int)value.length(); i++)
        {
            if      (isalpha(value[i])) hasAlpha  = true;
            else if (isdigit(value[i])) hasDigit  = true;
            else                        hasSymbol = true;
        }
        valid = hasAlpha && hasDigit && hasSymbol;
        if (!valid) cout << "Use format 26-Jan-2026: ";
    } while (!valid);
    return value;
}
