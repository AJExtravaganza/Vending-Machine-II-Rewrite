#pragma once

class CashSet
{
    friend class CashManager;
    friend class TransactionManager;

public:
    CashSet();
    CashSet(int dollars_, int quarters_, int dimes_, int nickels_);

    CashSet add(int _dollars, int quarters_, int dimes_, int nickels_);
    CashSet forceBalance(int balanceCents);
    CashSet remove(int _dollars, int quarters_, int dimes_, int nickels_);
    int getBalance();

    CashSet &operator+=(const CashSet other);
    CashSet &operator-=(const CashSet other);

private:
    void refreshBalance();

    int dollars = 0;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;

    int balance = 0;

};
