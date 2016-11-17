#include "VM100C.hpp"

VM100C::VM100C(): cardManagement(CardManager())
{
    machineType = 'C';
}

VM100C::VM100C(std::istream& machineDefsInput, std::vector<Product>& productDefsDB, int machineID): cardManagement(CardManager())
{
    machineName = "100C";
    machineName += ('0' + machineID);
    machineType = 'C';
    int stockedSKUs(0), initQuarters(0), initDimes(0), initNickels(0);
    machineDefsInput >> initQuarters >> initDimes >> initNickels >> stockedSKUs;
    fillInventory(stockedSKUs, machineDefsInput, productDefsDB);

}

bool VM100C::performTransaction(Product * currentProduct, std::ostream& uiOut, Transaction& currentTransaction)
{
    return cardManagement.performTransaction(currentProduct, uiOut, currentTransaction);
}

void VM100C::refund(std::ostream& uiOut)
{

}

void VM100C::reportCurrentBalance(std::ostream& technicianOut)
{
    cardManagement.reportCurrentBalance(technicianOut);
}

void VM100C::reportInitialBalance(std::ostream& technicianOut)
{
    technicianOut << "Initial Balance: $0.00\n";
}

bool VM100C::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction)
{
    return cardManagement.requestTender(uiIn, uiOut, paymentMethod, currentTransaction);
}

bool VM100C::sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod)
{
    return currentPaymentMethod == VALIDCARD;
}
