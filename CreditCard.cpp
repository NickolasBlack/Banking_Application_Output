#include "CreditCard.hpp"

using namespace std;

/* Credit Card Constructor series */
CreditCard::CreditCard()
    // Credit card no args constructor
    : cardNumber(11111), // account number
      expirationDate(Calendar()), // expiration date
      limit(CardLevel::BASIC), // card limit 
      creditCharge(0.0) // credit charge
{}

CreditCard::CreditCard(
    int accountNumber, // account number
    Calendar expirationDate, // expiration date
    CardLevel limit, // limit
    double creditCharge // charge amount
) : // Set variables
    cardNumber(accountNumber), // account number
    expirationDate(expirationDate), // expiration date
    limit (limit), // card limit
    creditCharge (creditCharge) // credit charge
{}

/* Credit Card getter Series */
int CreditCard::getCardNumber() {
    // Credit card class get account number. returns account 
    // number
    return cardNumber; // return card number
}

Calendar CreditCard::getExpirationDate() {
    // credit card class get expiration date
    return Calendar(expirationDate); // return expiration date
}

double CreditCard::getCardLimit() {
    // credit card get card limit. returns card limit
    return static_cast<int>(limit); // return card limit
}

double CreditCard::getCreditCharge(){
    // Credit card get credit charge method. returns that amount charged
    return creditCharge; // return credit charge
}

string CreditCard::printCreditChargeAmount(){
    // Credit card print charge amount. prints a formatted string of the 
    // charge amount
    ostringstream charge;  // write string stream
    charge << "$" << fixed << setprecision(2) << creditCharge;
    // convert to string
    string formattedBalance = charge.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }
    
    return formattedBalance; // return balance
}

string CreditCard::getCardLevel(){
    // Credit card get card level. Returns card level
    switch (limit) {
        // Basic = $500
        case CardLevel::BASIC:
            return "Basic"; // return basic
        // Gold = $ 2000
        case CardLevel::GOLD:
            return "Gold"; // return gold
        // Platinum = $5000
        case CardLevel::PLATINUM:
            return "Platinum"; // return platinum
        default:
            return "Unknown"; // error handling
    }
}

/* Credit Card unit testing series */
static void testCard(){
    CreditCard testCard(
        111111, // account number
        Calendar(2,1,2026), // 2/2006
        CardLevel::BASIC, // cardlevel
        200.00 // charge amount
    );
    // Assert
    ASSERT(testCard.getAccountNumber() == 111111);
    ASSERT(testCard.getExpirationDate().getMonth() == 1);
    ASSERT(testCard.getExpirationDate().getDay() == 31);
    ASSERT(testCard.getExpirationDate().getYear() == 2026);
    ASSERT(testCard.getCardLevel() == "Basic");
    ASSERT(testCard.getCardLimit() == 500);    
    ASSERT(testCard.getChargeAmount() == 200.00);
}

void testCreditCard(){
    // Unit test for credit card class
    TEST(testCard);
}
