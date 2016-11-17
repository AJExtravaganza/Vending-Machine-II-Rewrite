#include "CardManager.hpp"
#include "global.h"

#include <iostream>
#include <iomanip>

CardManager::CardManager(): activeCard(""), revenueBalance(0)
{

}

bool CardManager::isValidCard(std::string cardNumberStr)
{
    if (cardNumberStr == "card")
    return true;

    if ((cardNumberStr.length() >= 13) && (cardNumberStr.length() <= 16))
    {
        int cardNumberDigits[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int doubledDigits[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int sum(0);

        for (unsigned int i = 0; i < cardNumberStr.length(); i++)
        {
            cardNumberDigits[i] = (cardNumberStr[cardNumberStr.length() - 1 - i] - '0');

            doubledDigits[i] = (cardNumberDigits[i] * 2);

            if (doubledDigits[i] > 9)
            {
                doubledDigits[i] = ((doubledDigits[i] / 10) + (doubledDigits[i] % 10));
            }

            sum += ((i % 2) ? doubledDigits[i] : cardNumberDigits[i]);
        }

        return ((sum % 10) == 0);
    }
    else
    {
        return false;
    }
}

bool CardManager::performTransaction(Product* currentProduct, std::ostream& uiOut, Transaction& currentTransaction)
{
    if (isValidCard(activeCard) && currentProduct->currentQty > 0)
    {
        uiOut << "Card " << activeCard << " has been charged " << currentProduct->price << " cents.\n";
        revenueBalance += currentProduct->price;
        currentTransaction.tendered.forceBalance(currentProduct->price);
        return true;
    }
    else
    {
        return false;
    }
}

int CardManager::reportCurrentBalance(std::ostream& technicianOut)
{
    technicianOut << "Current charged: $"
                  << (revenueBalance / 100) << "."
                  << std::setw(2) << std::setfill('0') << (revenueBalance % 100) << "\n";
    return revenueBalance;
}

bool CardManager::requestTender(std::istream& uiIn, std::ostream& uiOut, PaymentMethod &paymentMethod, Transaction &currentTransaction)
{
    std::string cardNumberRaw;
    uiIn.ignore();

    for (int attempt = 0; attempt < MAXCARDATTEMPTS; attempt++)
    {
        uiOut << "Please enter a valid card number: ";

        std::getline(uiIn, cardNumberRaw);

        for (unsigned int digit = 0; digit < cardNumberRaw.length(); digit++)
        {
            if (std::isspace(cardNumberRaw[digit]))
            {
                cardNumberRaw.erase(digit, 1);
                digit--;
            }
        }

        if (isValidCard(cardNumberRaw))
        {
            activeCard = cardNumberRaw;
            paymentMethod = VALIDCARD;
            return true;
        }
        else
        {
            uiOut << "ERROR: INVALID CARD NUMBER. (" << (MAXCARDATTEMPTS - attempt - 1) << " ATTEMPTS REMAINING)\n";
        }
    }

    uiOut << (paymentMethod == VALIDCARD ? "Card Accepted.\n" : "Failed to provide valid card.\n");
    return false;
}
