#include "global.h"
#include "validation.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdlib.h>



// TODO (Backbox#1#): Change to int (including calls)
char getValidInt(std::istream& input, int lowerBound, int upperBound) //Fail to 0
{
    int integer = 0;
    input >> integer;
    if (input.fail() || integer < lowerBound || integer > upperBound)
    {
        std::cout << "EVENT IN getValidInt(istream, int, int): BAD INPUT OR END OF FILE.  CLEARING BUFFER.\n";
        input.clear();
        input.ignore(INT_MAX, '\n');
        integer = 0;
    }

    return integer;
}

char getValidMachineType(std::istream& input) //Fail to 0
{
    char machineType = 0;
    std::string rawInput;

    input >> rawInput;

    if ((rawInput.length() != 4) || (rawInput.substr(0,3) != "100") || (rawInput[3] < FIRSTVALIDTYPE) || (rawInput[3] > LASTVALIDTYPE))
    {
        std::cout << "EVENT IN getValidMachineType(istream): BAD INPUT OR END OF FILE.  CLEARING BUFFER.\n";
        input.clear();
        input.ignore(INT_MAX, '\n');
        machineType = 0;
    }
    else
    {
        machineType = rawInput[3];
    }
    return machineType;
}

bool isValidSKU(std::string SKU)
{
    return ((SKU.length() == 4) && isdigit(SKU[0]) && isdigit(SKU[1]) && isdigit(SKU[2]) && isdigit(SKU[3]));
}

