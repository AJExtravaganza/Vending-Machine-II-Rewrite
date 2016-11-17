#pragma once

#include "VendingMachine.hpp"

#include <iostream>
#include <string>
#include <vector>

class VM100D : public VendingMachine
{
public:
    VM100D();
    VM100D(std::istream& machineDefsInput, std::vector<Product>& productDefsDB, int machineID);
    bool performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction);
    void refund(std::ostream& uiOut);
    bool requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction);
    bool sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod);
private:
    void reportCurrentBalance(std::ostream& technicianOut);
    void reportInitialBalance(std::ostream& technicianOut);
    CardManager cardManagement;
    CashManager cashManagement;
    PaymentMethod selectedMethod;

};
