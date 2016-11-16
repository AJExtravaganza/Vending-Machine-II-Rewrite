#pragma once

#include "CashSet.hpp"
#include "Product.hpp"

struct Transaction
{
    Transaction();
    Transaction(int ID);

    int transactionID;
    int productRow;
    int productColumn;
    CashSet tendered;
    CashSet change;

    Product product;
};
