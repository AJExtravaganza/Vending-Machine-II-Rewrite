
#include "VM100D.hpp"

#include <iomanip>

VM100D::VM100D(): cardManagement(CardManager()), cashManagement(CashManager()), selectedMethod(NOPAYMENT)
{
    machineType = 'D';
}

VM100D::VM100D(std::istream& machineDefsInput, std::vector<Product>& productDefsDB, int machineID): cardManagement(CardManager()), cashManagement(true, true), selectedMethod(NOPAYMENT)
{
    machineName = "100D";
    machineName += ('0' + machineID);
    machineType = 'D';
    int stockedSKUs(0), initQuarters(0), initDimes(0), initNickels(0);
    machineDefsInput >> initQuarters >> initDimes >> initNickels >> stockedSKUs;
    cashManagement = CashManager(0, initQuarters, initDimes, initNickels, true, true);
    fillInventory(stockedSKUs, machineDefsInput, productDefsDB);

}

bool VM100D::performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction)
{
    if (selectedMethod == CASH)
    {
        return (cashManagement.performTransaction(currentProduct, uiOut, currentTransaction));
    }
    else if (selectedMethod == CARD)
    {
        return (cardManagement.performTransaction(currentProduct, uiOut, currentTransaction));
    }
    else
    {
        return false;
    }
}

void VM100D::refund(std::ostream& uiOut)
{
    cashManagement.refund(uiOut);
}

void VM100D::reportCurrentBalance(std::ostream& technicianOut)
{
    int cumulativeRevenue = 0;
    cumulativeRevenue -= cashManagement.reportInitialBalance();
    cumulativeRevenue += cashManagement.reportCurrentBalance(technicianOut);
    technicianOut << "\b";
    cumulativeRevenue += cardManagement.reportCurrentBalance(technicianOut);
// TODO (Backbox#1#): Is balance useful, or should the total provide revenue instead?
    technicianOut << "Total Revenue: $"
                  << (cumulativeRevenue / 100) << "."
                  << std::setw(2) << std::setfill('0') << (cumulativeRevenue % 100) << "\n";
}

void VM100D::reportInitialBalance(std::ostream& technicianOut)
{
    cashManagement.reportInitialBalance(technicianOut);
}

bool VM100D::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction)
{
    uiOut << "Pay with cash[1], or card[2]? ";
    int selection = static_cast<int>(getValidInt(uiIn, 1, 2));
    switch (selection)
    {
    case 1:
        selectedMethod = CASH;
        return cashManagement.requestTender(uiIn, uiOut, paymentMethod, currentTransaction);
        break;
    case 2:
        selectedMethod = CARD;
        return cardManagement.requestTender(uiIn, uiOut, paymentMethod, currentTransaction);
        break;
    default:
        return false;
        break;
    }
    return cardManagement.requestTender(uiIn, uiOut, paymentMethod, currentTransaction);
}

bool VM100D::sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod)
{
    if (currentPaymentMethod == CASH)
    {
        return (cashManagement.getCurrentTenderCents() >= requestedProduct.price);
    }
    else if (currentPaymentMethod == VALIDCARD)
    {
        return true;
    }
    else
    {
        return false;
    }
}
