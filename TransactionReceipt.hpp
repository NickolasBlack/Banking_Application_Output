#pragma once

#include "Stdafx.hpp"
#include "TransactionTicket.hpp"


class TransactionReceipt{
    /*
        Transaction Receipt Class
        contains a transaction ticket, success Indicator flag
        reason for failure, account type, preTransaction Balance,
        post transaction balance, post transaction maturity date
    */
   public:
        // Transaction Receipt constructor series
        TransactionReceipt(); // No args constructor
        TransactionReceipt(
            // Transaction Receipt Key work args constructor
            const TransactionTicket& transactionTicket, 
            std::string accountType, // account type
            double preTransactionBalance, // pre transaction balance
            double postTransactionBalance, // post Transaction balance
            bool transactionSuccess, // transaction success indicator
            std::string reasonForFailure // reason for failure
        );
        TransactionReceipt(
            // Transaction Receipt Key work args constructor
            const TransactionTicket& transactionTicket, 
            std::string accountType, // account type
            double preTransactionBalance, // pre transaction balance
            double postTransactionBalance, // post Transaction balance
            bool transactionSuccess, // transaction success indicator
            std::string reasonForFailure, // reason for failure
            Calendar newMaturityDate // new maturity date
        );
        TransactionReceipt(
            // Transaction Receipt copy constructor
            const TransactionReceipt& otherTransactionReceipt
        );

        // Transaction Receipt getter series
        TransactionTicket getTransactionTicket(); // return ticket
        std::string getAccountType(); // return account type
        double getPreTransactionBalance(); // return pre balance
        double getPostTransactionBalance(); // return post balance
        bool getTransactionSuccess(); // return transaction success
        Calendar getMaturityDate(); // return maturity date
        std::string getReasonForFailure(); // return failure reason

        // Transaction Receipt Formatter
        std::string printReceipt(); // prints the receipt
        std::string printSuccess(); // prints success
        std::string printTransactionBalance(double amount); // print balance
        std::string printTransactionReceipt();
        
   private:
        TransactionTicket transactionTicket; // transaction ticket
        std::string accountType; // account type
        double preTransactionBalance; // pre transaction balance
        double postTransactionBalance; // post transaction balance
        std::string reasonForFailure; // reason for failure
        bool transactionSuccess; // success indicator flag
        Calendar newMaturityDate; // new Maturity date
};

// Unit testing 
void testTransactionReceipt();