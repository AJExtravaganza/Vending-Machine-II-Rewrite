#pragma once

#include "enums.h"
#include "Transaction.hpp"
//#include "VM100A.hpp"
//#include "VM100B.hpp"
//#include "VM100C.hpp"
//#include "VM100D.hpp"

#include <iostream>
#include <string>

class CashManager
{
    //friend void VM100A::reportCurrentBalance(std::ostream& technicianOut);
    // TODO (Backbox#1#): reduce friend scope to report function
    //friend class VM100A;
    //friend class VM100B;
    //friend class VM100C;
    //friend class VM100D;

public:
    CashManager();
    CashManager(bool tenderBills, bool tenderCoins);
    CashManager(int initDollars_, int initQuarters_, int initDimes_, int initNickels_, bool tenderBills, bool tenderCoins);

    void dispenseChange(CashSet change, std::ostream& uiOut);
    bool generateChange(CashSet &change, Product product, std::ostream& uiOut);
    int getCurrentTenderCents();
    bool performTransaction(Product * currentProduct, std::ostream& uiOut, Transaction& currentTransaction);
    void refreshStockBalance();
    void refund(std::ostream& uiOut);
    int reportCurrentBalance(std::ostream& technicianOut);
    int reportInitialBalance(std::ostream& technicianOut);
    bool requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction);


private:

    CashSet initialCash;
    CashSet currentCash;
    int currentTenderCents;
    bool tendersBills;
    bool tendersCoins;

};
