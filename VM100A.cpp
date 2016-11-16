#include "VM100A.hpp"

#include <iomanip>

VM100A::VM100A(): cashManagement()
{
    machineType = 'A';
}

VM100A::VM100A(std::istream& machineDefsInput, std::vector<Product> productDefsDB, int machineID): cashManagement(true, false)
{
    machineName = "100A";
    machineName += ('0' + machineID);
    machineType = 'A';
    int stockedSKUs(0), initQuarters(0), initDimes(0), initNickels(0);
    machineDefsInput >> initQuarters >> initDimes >> initNickels >> stockedSKUs;
    cashManagement = CashManager(0, initQuarters, initDimes, initNickels, true, false);
    fillInventory(stockedSKUs, machineDefsInput, productDefsDB);

}

bool VM100A::performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction)
{
    return cashManagement.performTransaction(currentProduct, uiOut, currentTransaction);
}

void VM100A::refund(std::ostream& uiOut)
{
    cashManagement.refund(uiOut);
}

void VM100A::reportCurrentBalance(std::ostream& technicianOut)
{
    cashManagement.reportCurrentBalance(technicianOut);
}

void VM100A::reportInitialBalance(std::ostream& technicianOut)
{
    cashManagement.reportInitialBalance(technicianOut);
}

bool VM100A::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction)
{
    return cashManagement.requestTender(uiIn, uiOut, paymentMethod, currentTransaction);
}

bool VM100A::sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod)
{
    if (currentPaymentMethod == CASH)
    {
        return (cashManagement.getCurrentTenderCents() >= requestedProduct.price);
    }
    else
    {
        return false;
    }
}
