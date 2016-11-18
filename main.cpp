    /*//CURRENT STATUS AND PATCH NOTES////
FIXED OBJECT SLICING WITH shared_ptr.  Consider unique_ptr if you can figure out the syntax.

Current Status:

// TODO (Backbox#5#): Set relevant functions/parameters as const

 */


#include "MachineInitialisation.hpp"

#include <iostream>
#include <fstream> //DEBUG




using namespace std;

int findMachine(std::string requestedName, std::vector<std::shared_ptr<VendingMachine>>& machineSet);
std::shared_ptr<VendingMachine> selectMachine(std::istream& uiIn, std::ostream& uiOut, std::vector<std::shared_ptr<VendingMachine>>& machineSet);

int main()
{
    std::ifstream testInputFromFile;
    testInputFromFile.open("testInputs.txt");
    istream* inStream = &std::cin; //Select input method here

    std::string initSentinel = "";
    vector<std::shared_ptr<VendingMachine>> myMachines;

    while (initSentinel != INITSTRING){*inStream >> initSentinel;}

    MachineInitialisation("machines.txt", "products.txt", myMachines);

    std::shared_ptr<VendingMachine> activeMachine = selectMachine(*inStream, std::cout, myMachines);

    while(activeMachine)
    {
        activeMachine->purchaseWrapper(*inStream, std::cout);
        activeMachine = selectMachine(*inStream, std::cout, myMachines);
    }

    for (unsigned int i = 0; i < myMachines.size(); i++)
    {
        myMachines[i]->reportShutdown(std::cout);
    }

    return 0;
}

std::shared_ptr<VendingMachine> selectMachine(std::istream& uiIn, std::ostream& uiOut, std::vector<std::shared_ptr<VendingMachine>>& machineSet)
{
    std::string machineSelection;
    std::shared_ptr<VendingMachine> machine = nullptr;
    int ID = -1;

    uiOut << "\nSelect a machine --> ";
    uiIn >> machineSelection;
    ID = findMachine(machineSelection, machineSet);
    if (ID == SHUTDOWNINTFLAG)
    {
        return machine;
    }
    return (ID >= 0) ? machineSet[ID] : selectMachine(uiIn, uiOut, machineSet); // Recursive call for valid selection
}

int findMachine(std::string requestedName, std::vector<std::shared_ptr<VendingMachine>>& machineSet)
{
    for (unsigned int i = 0; i < machineSet.size(); i++)
    {
        if(machineSet[i]->getMachineName() == requestedName)
        {
            return i;
        }
        else if (requestedName == SHUTDOWNSTRING)
        {
            return SHUTDOWNINTFLAG;
        }
    }

    return -1;
}
