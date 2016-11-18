#pragma once

#include <iostream>
#include <string>



int getValidInt(std::istream& input, int lowerBound, int upperBound);
char getValidMachineType(std::istream& input);
bool isValidSKU(std::string SKU);
