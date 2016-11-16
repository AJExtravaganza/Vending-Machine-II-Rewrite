#include "Transaction.hpp"

Transaction::Transaction(): transactionID(0), productRow(0), productColumn(0), tendered(CashSet()), change(CashSet()), product(Product())
 {

 }

Transaction::Transaction(int ID): transactionID(ID), productRow(0), productColumn(0), tendered(CashSet()), change(CashSet()), product(Product())
 {

 }
