#include "MachineInitialisation.hpp"

void MachineInitialisation(std::string filenameMachineDefs, std::string filenameProductDefs, std::vector<std::shared_ptr<VendingMachine>> &machineSet)
{
    std::ifstream productDefs;
    productDefs.open(filenameProductDefs);
    std::vector<Product> productDefsDB;

    productDBInit(productDefs, productDefsDB);


    std::ifstream machineDefsFile;
    machineDefsFile.open(filenameMachineDefs);

    char machineType = 0;
    int machineTypeQty = 0;

    do
    {
        machineType = 0;
        machineType = getValidMachineType(machineDefsFile);
        machineTypeQty = getValidInt(machineDefsFile, 1, MACHINELIMIT);

        for (int i = 1; i <= machineTypeQty; i++)
        {
            switch (machineType)
            {
            case 'A':
                {
                    std::shared_ptr<VM100A> newMachine(new VM100A(machineDefsFile, productDefsDB, i));
                    machineSet.push_back(newMachine);
                }
                break;
            case 'B':
                {
                    std::shared_ptr<VM100B> newMachine(new VM100B(machineDefsFile, productDefsDB, i));
                    machineSet.push_back(newMachine);
                }
                break;
            case 'C':
                {
                    std::shared_ptr<VM100C> newMachine(new VM100C(machineDefsFile, productDefsDB, i));
                    machineSet.push_back(newMachine);
                }
                break;
            case 'D':
                {
                    std::shared_ptr<VM100D> newMachine(new VM100D(machineDefsFile, productDefsDB, i));
                    machineSet.push_back(newMachine);
                }
                break;
            default:
                break;
            }
        }

        machineTypeQty  =0;

    }while (machineType != 0);

}

void productDBInit(std::istream& productDefsInput, std::vector<Product> &database)
{
    int quantity(0), price(0);
    std::string SKU, description;

    while (productDefsInput >> SKU)
    {
        if (isValidSKU(SKU) && !(productDefsInput.fail()))
        {
            productDefsInput >> quantity >> price;
            productDefsInput.ignore(1);
            std::getline(productDefsInput, description);
            database.push_back(Product(SKU, quantity, price, description));
        }
    }
}

