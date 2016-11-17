#pragma once

#include "VendingMachine.hpp"

#include <iostream>
#include <string>
#include <vector>

class VM100C : public VendingMachine
{
public:
    VM100C();
    VM100C(std::istream& machineDefsInput, std::vector<Product>& productDefsDB, int machineID);
    bool performTransaction(Product * currentProduct, std::ostream& uiOut, Transaction& currentTransaction);
    void refund(std::ostream& uiOut);
    bool requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction);
    bool sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod);
private:
    void reportCurrentBalance(std::ostream &technianOut);
    void reportInitialBalance(std::ostream &technianOut);
    CardManager cardManagement;
};
