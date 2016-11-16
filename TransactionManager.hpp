
#include "CardManager.hpp"
#include "CashManager.hpp"

#include <iostream>
#include <vector>

class TransactionManager
{
public:
    TransactionManager();
    int nextLogID();
    void transactionReport(std::ostream& technicianOut);
    void logSuccessfulTransaction(Transaction newTransaction);

private:
    void reset();
    std::vector<Transaction> transactionLog = {};

};
