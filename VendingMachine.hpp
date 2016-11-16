#pragma once

#include "global.h"
#include "TransactionManager.hpp"
#include "validation.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>


class VendingMachine
{
public:
    void purchaseWrapper(std::istream& uiIn, std::ostream& uiOut);
// TODO (Backbox#1#): Consider making the following few functions private, so that public access is only given to purchaseWrapper

    VendingMachine();
    VendingMachine(std::string name, char type);
    virtual ~VendingMachine() = 0;

    virtual bool performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction);
    virtual void refund(std::ostream& uiOut);
    virtual bool requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction);
    virtual bool sufficientTenderFor(Product requestedProduct, PaymentMethod currentPaymentMethod) = 0;

    void dispenseProduct(Product* product, std::ostream& uiOut);
    Product * getPurchaseRequest(std::istream& uiIn, std::ostream& uiOut);
    Product * retrieveProduct(std::string validatedLocation);
    void reportShutdown(std::ostream& technicianOut);
    void uiReportInventory(std::ostream& uiOut);


    std::string getMachineName();

protected:
    void fillInventory(int stockedSKUs, std::istream& machineDefsInput, std::vector<Product> productDefsDB);
    std::string getValidProductLocation(std::istream& uiIn, std::ostream& uiOut);
    virtual void reportCurrentBalance(std::ostream& technicianOut);
    virtual void reportInitialBalance(std::ostream& technicianOut);
    std::string machineName;

    char machineType;
    TransactionManager transactionRecord;
    Product inventory[MACHINE_ROWS][MACHINE_COLUMNS];
};

