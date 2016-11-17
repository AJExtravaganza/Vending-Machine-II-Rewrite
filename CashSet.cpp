#include "CashSet.hpp"


CashSet::CashSet(): dollars(0), quarters(0), dimes(0), nickels(0), balance(0)
{

}

CashSet::CashSet(int dollars_, int quarters_, int dimes_, int nickels_): dollars(dollars_), quarters(quarters_), dimes(dimes_), nickels(nickels_), balance(0)
{
    refreshBalance();
}

CashSet CashSet::add(int dollars_, int quarters_, int dimes_, int nickels_)
 {
     dollars += dollars_;
     quarters += quarters_;
     dimes += dimes_;
     nickels += nickels_;

     refreshBalance();
     return *this;
 }

CashSet CashSet::forceBalance(int balanceCents)
{
    balance = balanceCents;
    return *this;
}

void CashSet::refreshBalance()
{
    balance = ((100*dollars) + (25*quarters) + (10*dimes) + (5*nickels));
}

CashSet CashSet::remove(int dollars_, int quarters_, int dimes_, int nickels_)
 {
     this->add(-dollars_, -quarters_, -dimes_, -nickels_);

     return *this;
 }

 int CashSet::getBalance()
 {
     return ((100*dollars)+(25*quarters)+(10*dimes)+(5*nickels));
 }

 CashSet &CashSet::operator+=(const CashSet other)
 {
     add(other.dollars, other.quarters, other.dimes, other.nickels);
     return *this;
 }

CashSet &CashSet::operator-=(const CashSet other)
{
    remove(other.dollars, other.quarters, other.dimes, other.nickels);
    return *this;
}

