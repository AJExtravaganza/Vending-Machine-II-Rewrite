#include "CashManager.hpp"

#include <iomanip>

CashManager::CashManager():initialCash(0,0,0,0), currentCash(0,0,0,0), currentTenderCents(0), tendersBills(false), tendersCoins(false)
{

}

CashManager::CashManager(bool tenderBills, bool tenderCoins):initialCash(0,0,0,0), currentCash(0,0,0,0), currentTenderCents(0), tendersBills(tenderBills), tendersCoins(tenderCoins)
{

}

CashManager::CashManager(int initDollars_, int initQuarters_, int initDimes_, int initNickels_, bool tenderBills, bool tenderCoins): initialCash(CashSet(initDollars_, initQuarters_, initDimes_, initNickels_)), currentCash(initialCash), currentTenderCents(0), tendersBills(tenderBills), tendersCoins(tenderCoins)
{

}

void CashManager::dispenseChange(CashSet change, std::ostream& uiOut)
{
    currentCash -= change;

    uiOut << "Your change of " << change.balance << " cents is given as:\n"
          << "    dollar(s):  " << change.dollars << "\n"
          << "    quarter(s): " << change.quarters << "\n"
          << "    dime(s):    " << change.dimes << "\n"
          << "    nickel(s):  " << change.nickels << "\n\n";
}

bool CashManager::generateChange(CashSet& change, Product product, std::ostream& uiOut)
{
    change = CashSet(0,0,0,0);
    int changeRemaining = (currentTenderCents - product.price);

    while (changeRemaining >= 100 && currentCash.dollars > change.dollars)
    {
        change.add(1,0,0,0);
        changeRemaining = (currentTenderCents - product.price - change.balance);
    }

    while (changeRemaining >= 25 && currentCash.quarters > change.quarters)
    {
        change.add(0,1,0,0);
        changeRemaining = (currentTenderCents - product.price - change.balance);
    }

    while (changeRemaining >= 10 && currentCash.dimes > change.dimes)
    {
        change.add(0,0,1,0);
        changeRemaining = (currentTenderCents - product.price - change.balance);
    }

    while (changeRemaining >= 5 && currentCash.nickels > change.nickels)
    {
        change.add(0,0,0,1);
        changeRemaining = (currentTenderCents - product.price - change.balance);
    }

    while (changeRemaining != 0 && change.quarters > 0) // If special case exists
    {
        change.remove(0,1,0,0); // Give a quarter back
        changeRemaining = (currentTenderCents - product.price - change.balance);

        while (changeRemaining >= 10 && currentCash.dimes > change.dimes) // Try to complete transaction (nickels are already gone, so use dimes only)
        {
            change.add(0,0,1,0);
            changeRemaining = (currentTenderCents - product.price - change.balance);
        }

    }

    if (changeRemaining == 0)
    {
        return true;
    }
    else
    {   change = CashSet(0,0,0,0);
        return false;
    }

}

int CashManager::getCurrentTenderCents()
{
    return currentTenderCents;
}

bool CashManager::performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction)
{
    CashSet changeCash;
    if (generateChange(changeCash, *currentProduct, uiOut))
    {
        currentTransaction.change = changeCash;
        dispenseChange(changeCash, uiOut);
        return true;
    }
    else
    {
        uiOut << "ERROR: INSUFFICIENT CHANGE.\n";
        return false;
    }
}

void CashManager::refund(std::ostream& uiOut)
{
    CashSet change;
    Product refund("0000", 0, 0, "Refund");
    uiOut << "Issuing refund...\n ";
    generateChange(change, refund, uiOut);
    dispenseChange(change, uiOut);
}

int CashManager::reportCurrentBalance(std::ostream& technicianOut)
{
    technicianOut << "Current Balance: $"
                  << (currentCash.balance / 100) << "."
                  << std::setw(2) << std::setfill('0') << (currentCash.balance % 100)
                  << std::setw(0) << " ("
                  << currentCash.dollars << " $, "
                  << currentCash.quarters << " Q, "
                  << currentCash.dimes << " D, "
                  << currentCash.nickels << " N)\n";
    return currentCash.balance;
}

int CashManager::reportInitialBalance(std::ostream& technicianOut)
{
    technicianOut << "Initial Balance: $"
                  << (initialCash.balance / 100) << "."
                  << std::setw(2) << std::setfill('0') << (initialCash.balance % 100)
                  << std::setw(0) << " ("
                  << initialCash.dollars << " $, "
                  << initialCash.quarters << " Q, "
                  << initialCash.dimes << " D, "
                  << initialCash.nickels << " N)\n\n";
    return initialCash.balance;
}

bool CashManager::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod& paymentMethod, Transaction& currentTransaction)
{
    int dollars(0), quarters(0), dimes(0), nickels(0);

    uiOut << "Insert your money [";
    uiOut << (tendersBills ? "$" : "");
    uiOut << ((tendersBills && tendersCoins) ? " " : "");
    uiOut << (tendersCoins ? "Q D N" : "");
    uiOut << "] --> ";

    if (tendersBills)
    {
        uiIn >> dollars;
    }

    if (tendersCoins)
    {
        uiIn >> quarters >> dimes >> nickels;
    }

    if(!uiIn.fail())
    {
        CashSet tender(dollars, quarters, dimes, nickels);
        currentTransaction.tendered = tender;
        currentCash += tender;
        currentTenderCents = tender.getBalance();
        paymentMethod = CASH;
        return true;
    }
    else
    {
        uiOut << "\nInvalid entry\n";
        requestTender(uiIn, uiOut, paymentMethod, currentTransaction); //Recursive call for valid entry.
    }

    return false;

}
