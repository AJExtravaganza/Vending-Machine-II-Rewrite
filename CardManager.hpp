#pragma once

#include "enums.h"
#include "Transaction.hpp"

#include <string>

class CardManager
{
public:
    CardManager();
    bool isValidCard(std::string cardNumber);
    bool performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction);
    int reportCurrentBalance(std::ostream& technicianOut);
    bool requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction);

private:
    std::string activeCard;
    int revenueBalance;

};
