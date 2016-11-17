#include "VM100B.hpp"

#include <iomanip>

VM100B::VM100B(): cashManagement()
{
    machineType = 'B';
}

VM100B::VM100B(std::istream& machineDefsInput, std::vector<Product>& productDefsDB, int machineID): cashManagement(true, true)
{
    machineName = "100B";
    machineName += ('0' + machineID);
    machineType = 'B';
    int stockedSKUs(0), initQuarters(0), initDimes(0), initNickels(0);
    machineDefsInput >> initQuarters >> initDimes >> initNickels >> stockedSKUs;
    cashManagement = CashManager(0, initQuarters, initDimes, initNickels, true, true);
    fillInventory(stockedSKUs, machineDefsInput, productDefsDB);

}

bool VM100B::performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction)
{
    return cashManagement.performTransaction(currentProduct, uiOut, currentTransaction);
}

void VM100B::refund(std::ostream& uiOut)
{
    cashManagement.refund(uiOut);
}

void VM100B::reportCurrentBalance(std::ostream& technicianOut)
{
    cashManagement.reportCurrentBalance(technicianOut);
}

void VM100B::reportInitialBalance(std::ostream& technicianOut)
{
    cashManagement.reportInitialBalance(technicianOut);
}

bool VM100B::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction)
{
    return cashManagement.requestTender(uiIn, uiOut, paymentMethod, currentTransaction);
}

bool VM100B::sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod)
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
