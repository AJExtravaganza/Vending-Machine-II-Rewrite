#include "TransactionManager.hpp"

#include <iomanip>

TransactionManager::TransactionManager()
{

}

int TransactionManager::nextLogID()
{
    return transactionLog.size() + 1;
}

void TransactionManager::logSuccessfulTransaction(Transaction newTransaction)
{
    transactionLog.push_back(newTransaction);
}

void TransactionManager::transactionReport(std::ostream& technicianOut)
{
    int totalSales = 0;

    technicianOut << std::right <<std::setfill(' ')
                  << std::setw(5) <<"Trans"
                  << std::setw(5) << "Item"
                  << std::setw(5) << "Cost"
                  << std::setw(5) << "Paid"
                  << " (  $, Q, D, N)   Change (  $, Q, D, N)\n";

    for (unsigned int i = 0; i < transactionLog.size(); i++)
    {
        totalSales += transactionLog[i].product.price;

        technicianOut << std::setw(5) << std::right <<std::setfill(' ')
                      << std::setw(5) << transactionLog[i].transactionID
                      << std::setw(4) << static_cast<char>('1' + transactionLog[i].productColumn)
                      << static_cast<char>('A' + transactionLog[i].productRow)
                      << std::setw(5) << transactionLog[i].product.price
                      << std::setw(5) << transactionLog[i].tendered.balance << " ("
                      << std::setw(3) << transactionLog[i].tendered.dollars
                      << std::setw(3) << transactionLog[i].tendered.quarters
                      << std::setw(3) << transactionLog[i].tendered.dimes
                      << std::setw(3) << transactionLog[i].tendered.nickels << ")   "
                      << std::setw(6) << transactionLog[i].change.balance << " ("
                      << std::setw(3) << transactionLog[i].change.dollars
                      << std::setw(3) << transactionLog[i].change.quarters
                      << std::setw(3) << transactionLog[i].change.dimes
                      << std::setw(3) << transactionLog[i].change.nickels << ")\n";

    }

    technicianOut << "Total Cost:" << std::setw(4) << totalSales << "\n\n";
}
