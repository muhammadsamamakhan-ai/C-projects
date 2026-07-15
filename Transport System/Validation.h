#pragma once
#include <string>

int getValidatedInteger(std::string prompt, int minVal, int maxVal);
double getValidatedDouble(std::string prompt, double minVal, double maxVal);
std::string getValidatedString(std::string prompt, bool allowComma = false);
std::string getValidatedName(std::string prompt);
char getValidatedChar(std::string prompt, std::string validChars);