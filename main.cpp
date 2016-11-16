    /*//CURRENT STATUS AND PATCH NOTES////
FIXED OBJECT SLICING WITH shared_ptr.  Consider unique_ptr if you can figure out the syntax.

Current Status:

// TODO (Backbox#3#): Implement VM100B
// FEATURE (Backbox#7#): Implement VM100D

// TODO (Backbox#5#): Set relevant functions/parameters as const

 */


#include "machineInitialisation.hpp"

#include <iostream>




using namespace std;

int findMachine(std::string requestedName, std::vector<std::shared_ptr<VendingMachine>> &machineSet);
VendingMachine &selectMachine(std::istream& uiIn, std::ostream& uiOut, std::vector<std::shared_ptr<VendingMachine>> &machineSet);

int main()
{
// TODO (Backbox#1#): Introduction and startup
    std::cout << "STUB: STARTUP INTRODUCTION TEXT\n\n";

    vector<std::shared_ptr<VendingMachine>> myMachines;

// TODO (Backbox#1#): Sentinel loop for initialisation
    std::cout << "STUB: GETTING SECRET INIT CODE\n\n";

    MachineInitialisation("machines.txt", "products.txt", myMachines);

    while(true)
    {
        VendingMachine * activeMachine = &(selectMachine(std::cin, std::cout, myMachines));
        activeMachine->purchaseWrapper(std::cin, std::cout);
        activeMachine->reportShutdown(std::cout);
    }
// TODO (Backbox#1#): Implement transaction loop with exit sentinel.
    std::cout << "STUB: TRANSACTION LOOP\n\n";

    for (unsigned int i = 0; i < myMachines.size(); i++)
    {
        myMachines[i]->reportShutdown(std::cout);
    }

    return 0;
}

VendingMachine &selectMachine(std::istream& uiIn, std::ostream& uiOut, std::vector<std::shared_ptr<VendingMachine>> &machineSet) // Is the & necessary?  Check.
{
    std::string machineSelection;
    int ID(-1);
    uiOut << "\nSelect a machine --> ";
    uiIn >> machineSelection;
    ID = findMachine(machineSelection, machineSet);
    return (ID >= 0) ? *machineSet[ID] : selectMachine(uiIn, uiOut, machineSet); // Recursive call for valid selection
}

int findMachine(std::string requestedName, std::vector<std::shared_ptr<VendingMachine>> &machineSet) //Does this really need & for size to work?
{
    for (unsigned int i = 0; i < machineSet.size(); i++)
    {
        if(machineSet[i]->getMachineName() == requestedName)
        {
            return i;
        }
    }

    return -1;
}
