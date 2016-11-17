#include "VendingMachine.hpp"
#include <cstddef> // LINUX


VendingMachine::VendingMachine(): machineName("Uninitialised"), machineType(0), transactionRecord(TransactionManager()), inventory({})
{

}

VendingMachine::VendingMachine(std::string machineName_, char machineType_):
    machineName(machineName_), machineType(machineType_), transactionRecord(TransactionManager()), inventory({})
{

}

VendingMachine::~VendingMachine()
{

}


// TODO (Backbox#1#): ////VIRTUAL FUNCTIONS.  DETERMINE NEED TO INCLUDE HERE ONCE OTHER STUFF IS COMPLETE////
bool VendingMachine::performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction){return false;}
void VendingMachine::refund(std::ostream& uiOut){}
bool VendingMachine::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction){return false;}
bool VendingMachine::sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod){return false;}
void VendingMachine::reportCurrentBalance(std::ostream& technicianOut){}
void VendingMachine::reportInitialBalance(std::ostream& technicianOut){}


void VendingMachine::dispenseProduct(Product* product, std::ostream& uiOut)
{
    product->currentQty--;
    uiOut << "One " << product->description << " dispensed.\n\n";
}


void VendingMachine::fillInventory(int stockedSKUs, std::istream& machineDefsInput, std::vector<Product>& productDefsDB)
{
    for (int i = 0; i < stockedSKUs; i++)
    {
        int requestedQty(0), initialQty(0), locationRow(0), locationColumn(0);
        std::string locationStr, SKU;
        Product* DBProduct = nullptr;

        machineDefsInput >> locationStr >> SKU >> requestedQty;

        locationRow = locationStr[0] - '1'; //SHOULD PERFORM VALIDATION.  CONSIDER ADDING LATER.
        locationColumn = locationStr[1] - 'A';

        for (unsigned int DBIndex = 0; DBIndex < productDefsDB.size() && DBProduct == nullptr; DBIndex++)
        {
            if (SKU == productDefsDB[DBIndex].SKU)
            {
                DBProduct = &productDefsDB[DBIndex];
            }
        }

        inventory[locationRow][locationColumn] = Product(DBProduct, requestedQty);
    }
}

std::string VendingMachine::getMachineName()
{
    return machineName;
}

Product * VendingMachine::getPurchaseRequest(std::istream& uiIn, std::ostream& uiOut)
{
    Product * requestedProduct;

    uiReportInventory(uiOut);

    do
    {
        uiOut << "Select an item --> ";
        std::string requestedProductLocation = getValidProductLocation(uiIn, uiOut);
        requestedProduct = retrieveProduct(requestedProductLocation);
    }while(requestedProduct->currentQty < 1);

    return requestedProduct;
}

std::string VendingMachine::getValidProductLocation(std::istream& uiIn, std::ostream& uiOut)
{
    std::string rawProductLocation;

    uiIn >> rawProductLocation;

    if ((rawProductLocation.length() == 2)
    && (rawProductLocation[0] >= '1')
    && (rawProductLocation[0] < ('1' + MACHINE_ROWS))
    && (rawProductLocation[1] >= 'A')
    && (rawProductLocation[1] < ('A' + MACHINE_COLUMNS)))
    {
        uiOut << std::endl;
        return rawProductLocation;
    }
    else
    {
        uiOut << "Invalid Entry.  Please enter in the form [1-" << MACHINE_ROWS << "][A-" << static_cast<char>('A' + MACHINE_COLUMNS-1) << "]\n";
        return getValidProductLocation(uiIn, uiOut); // Recursive call for valid entry
    }

    return "00";
}

void VendingMachine::purchaseWrapper(std::istream& uiIn, std::ostream& uiOut)
{
    Transaction currentTransaction(transactionRecord.nextLogID());

    PaymentMethod currentPaymentMethod = NOPAYMENT;

    if (requestTender(uiIn, uiOut, currentPaymentMethod, currentTransaction))
    {
        Product * selectedProduct = getPurchaseRequest(uiIn, uiOut);

        currentTransaction.product = *selectedProduct;

        Product * firstProduct = &inventory[0][0];
        std::ptrdiff_t location = selectedProduct - firstProduct;
        currentTransaction.productRow = location % MACHINE_COLUMNS;
        currentTransaction.productColumn = location / MACHINE_COLUMNS;

        uiOut << "The cost of this item is " << selectedProduct->price << " cents.\n";


        if (sufficientTenderFor(*selectedProduct, currentPaymentMethod))
        {
            if (performTransaction(selectedProduct, uiOut, currentTransaction))
            {
                dispenseProduct(selectedProduct, uiOut);
                transactionRecord.logSuccessfulTransaction(currentTransaction);
            }
            else
            {
                uiOut << "ERROR: TRANSACTION FAILED.\n";
                refund(uiOut);
            }
        }
        else if (currentPaymentMethod == CASH)
        {
            uiOut << "ERROR: INSUFFICIENT TENDER FOR REQUESTED ITEM.\n";
            refund(uiOut);
        }
        else
        {
            uiOut << "ERROR: SHOULD NOT BE HERE (VendingMachine::PurchaseWrapper)\n";
        }
    }
    else
    {
        uiOut << "ERROR: NO VALID CARD PROVIDED.\n";
    }

}

Product * VendingMachine::retrieveProduct(std::string validatedLocation)
{
    int row = (validatedLocation[0] - '1');
    int column = (validatedLocation[1] - 'A');
    return &inventory[row][column];
}

void VendingMachine::reportShutdown(std::ostream& technicianOut)
{
    technicianOut << "Machine: " << machineName << "\n";
    reportInitialBalance(technicianOut);
    transactionRecord.transactionReport(technicianOut);
    reportCurrentBalance(technicianOut);
    technicianOut << "\n\n";
}

void VendingMachine::uiReportInventory(std::ostream& uiOut)
{
    uiOut << "Available items:\n";
    for (int row = 0; row < MACHINE_ROWS; row++)
    {
        for (int column = 0; column < MACHINE_COLUMNS; column++)
        {
            if (inventory[row][column].currentQty > 0)
            {
                uiOut << "    " << static_cast<char>('1' + row) << static_cast<char>('A' + column) << " " << inventory[row][column].price << " " << inventory[row][column].description << "\n";
            }
        }
    }
}



