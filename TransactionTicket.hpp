#pragma once

#include "Stdafx.hpp"

/*
    Transaction Type enum
    Defines all the types of transactions
*/
enum TransactionType {
    Deposit, // Deposit
    Withdrawl, // withdrawl
    Balance, // balance
    Close, // close account
    Open, // open account
    BalanceDue, // Balance Due
    PayBalance, // Pay Balance
    CreditTransaction, // credit Transaction
    ClearCheck, // clear check
    Portfolio, // Portfolio
    TransactionHistory, // transaction History
    ClientInfo // client info
};

class TransactionTicket{
    /*
        Transaction Ticket class
        contains an accountNumber, transaction date, transaction type,
        amount of transaction and term of cd
    */
   public:
        // Transaction Ticket constructor series
        TransactionTicket(); // No args constructor
        TransactionTicket(
            // Transaction Ticket Keyword args constructor 
            TransactionType transactionType, // Transaction type
            int accountNumber, // account Number
            double transactionAmount, // transaction amount
            Calendar transactionDate, // tranaction date
            int cdTerm // cd term
        );
        // TransactionTicket copy constructor
        TransactionTicket(const TransactionTicket& otherTransactionTicket);

        // Transaction ticket getter series
        int getAccountNumber(); // return ticket
        std::string getTransactionType(); // return transaction type
        TransactionType getType(); // returns transaction type enum
        double getTransactionAmount(); // return amount
        Calendar getTransactionDate(); // return date
        int getCDTerm(); // return cd term

        // Transaction Ticket formatter series
        std::string printTransactionAmount();

    private:
        int accountNumber; // account number
        TransactionType transactionType; // transaction type
        double transactionAmount; // transaction amount
        Calendar transactionDate; // transaction date
        int cdTerm; // Term of CD
};

// Unit testing 
void testTransactionTicket();