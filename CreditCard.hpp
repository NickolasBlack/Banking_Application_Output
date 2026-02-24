#pragma once

#include "Stdafx.hpp"

/*
    Card Level Enum
    Determines the card limit on a credit car
*/
enum class CardLevel : int {
    BASIC = 500, // 500.00 
    GOLD = 2000, // 2000.00
    PLATINUM = 5000 // 5000.00
};
/*
    Credit Card class
    Used to perform credit transactions on credit accounts.
    contains an account number, date of expiration, and card limit.
*/
class CreditCard{
    public:
        /* Credit Card constructor series */
        CreditCard(); // no args constructor
        CreditCard(
            // Credit card keyword args constructor
            int cardNumber, // account number
            Calendar expirationDate, // expiration date
            CardLevel limit, // card limit
            double creditCharge // credit charge amount
        );

        /* Credit card getter series */
        int getCardNumber(); // returns account number
        Calendar getExpirationDate(); // return expiration date
        double getCardLimit(); // returns card limit
        std::string getCardLevel(); // get card level
        double getCreditCharge(); // get credit charge

        /* Credit Card Formatter Series */
        std::string printCreditChargeAmount();

    private:
        int cardNumber; // account number
        Calendar expirationDate; // expiration date
        CardLevel limit; // card limit
        double creditCharge; // credit charge
};

// Unit test for dredit card class
void testCreditCard();