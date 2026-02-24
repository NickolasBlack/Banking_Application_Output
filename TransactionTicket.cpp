#include "TransactionTicket.hpp"

using namespace std;

// Transaction Ticket constructor series
TransactionTicket::TransactionTicket():
    // transactionTicket no args constructor
    accountNumber(000000), transactionType(TransactionType::Balance),
    transactionAmount(0.0), transactionDate(Calendar()),
    cdTerm(0) {}

TransactionTicket::TransactionTicket(
    // transaction ticket key word args constructor
    TransactionType transactionType, // transaction type
    int accountNumber, // account Number
    double transactionAmount, // transaction amount
    Calendar transactionDate, // transaction date
    int cdTerm // cd term
):  
    transactionType (transactionType), // set type
    accountNumber (accountNumber), // set number
    transactionAmount(transactionAmount), // set amount
    transactionDate(transactionDate), // set date
    cdTerm (cdTerm) // set term
{}

TransactionTicket::TransactionTicket(
    // Transaction ticket copy constuctor
    const TransactionTicket& otherTransactionTicket // other ticket
): 
    transactionType(otherTransactionTicket.transactionType), // set type
    accountNumber(otherTransactionTicket.accountNumber), // set number
    transactionAmount(otherTransactionTicket.transactionAmount), // set amount
    transactionDate(otherTransactionTicket.transactionDate), // set date
    cdTerm (otherTransactionTicket.cdTerm) // set term
{}

// Transaction Ticket getter series
int TransactionTicket::getAccountNumber(){return accountNumber;}
double TransactionTicket::getTransactionAmount(){return transactionAmount;}
Calendar TransactionTicket::getTransactionDate(){return transactionDate;}
int TransactionTicket::getCDTerm(){return cdTerm;}
TransactionType TransactionTicket::getType(){return transactionType;}
string TransactionTicket::getTransactionType(){
    // Get transaction type. Returns a string of the transaction type
    switch(transactionType){
        // Get balance transactions
        case TransactionType::Balance:
            return "Balance"; // return balance
        // Make deposit transactions
        case TransactionType::Deposit:
            return "Deposit"; // return deposit
        // Make With drawls
        case TransactionType::Withdrawl:
            return "Withdrawl"; // return withdrawl
        // Open account
        case TransactionType::Open:
            return "Re-Open Account"; // return reopen account
        // Close account
        case TransactionType::Close:
            return "Close Account"; // return close account
        // Clear Check
        case TransactionType::ClearCheck:
            return "Clear Check"; // return clear check
        // Get Balance due
        case TransactionType::BalanceDue:
            return "Balance Due"; // return balance due
        // Pay Balance
        case TransactionType::PayBalance:
            return "Make Payment"; // return make payment
        // Credit Transaction
        case TransactionType::CreditTransaction:
            return "Credit Transaction";
        // Return Portfolio
        case TransactionType::Portfolio:
            return "Portolio";
        case TransactionType::TransactionHistory:
            return "Transaction History"; // return transaction history
        case TransactionType::ClientInfo:
            return "Client Information";
        default:
            return " ";
    }
}

// Transaction Ticket formatter series
string TransactionTicket::printTransactionAmount(){
    // Transaction Ticket print transaction method. Prints a fomatted
    // balance
    ostringstream amount;  // write string stream
    amount << "$" << fixed << setprecision(2) << transactionAmount;
    // convert to string
    string formattedBalance = amount.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }

    return formattedBalance; // return balance
}

// Unit Testing
static void testTicket(){
    // test ticket method. Tests the creation of a transaction ticket
    TransactionTicket transactionTicket = TransactionTicket(
        // Initialize transaction ticket
        TransactionType::Balance, // transaction ticket
        000000, // account number
        100.0, // transaction amount 
        Calendar(01,01,2001), // transaction date
        12 // CD term
    );
    // run assertions
    ASSERT(transactionTicket.getTransactionType() == "Balance");
    ASSERT(transactionTicket.getAccountNumber() == 000000);
    ASSERT(transactionTicket.getTransactionAmount() == 100.0);
    ASSERT(transactionTicket.getTransactionDate().printDate == "1/1/2001");
    ASSERT(transactionTicket.getCDTerm() == 12);
}

void testTransactionTicket(){
    // Unit test for transaction ticket class
    TEST(testTicket); // test ticket creation
}