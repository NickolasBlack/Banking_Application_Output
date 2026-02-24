#pragma once

#include "Stdafx.hpp"
#include "Depositor.hpp"
#include "CreditCard.hpp"
#include "BankAccount.hpp"
#include "TransactionReceipt.hpp"


/*
    Credit Account Class
    works like a bank account but in reverse. Depositors 
    have a balance and payments to the account decrease the balance
    depositors can also use the credit cards to make payments.
    contains an depositor, account number, balance due, account type, 
    account status, and an interest rate
*/
class CreditAccount{
    public:
        // Credit Account Constructor series
        CreditAccount(); // no Args constructor
        CreditAccount(
            // Credit Account key word args constructor
            Depositor creditor, // creditor
            int accountNumber, // account number
            double balanceDue, // balance due
            bool accountStatus // account status
        );
        // Credit account Bank Account Constructor
        CreditAccount(BankAccount bankAccount);
        // Credit account copy constructor
        CreditAccount(const CreditAccount& otherCreditAccount);

        // Credit Account getter seres
        Depositor getDepositor(); // return depositor
        int getAccountNumber(); // return account number
        std::string getAccountType(); // returns account type
        AccountType getType(); // return the type
        double getBalanceDue(); // returns account balance
        bool getAccountStatus(); // return account status
        // Return transaction receipts
        std::vector<TransactionReceipt> getTransactionReceipts();

        // Credit Account formatter 
        std::string printAccount(); // formated print of the account
        std::string printAccountBalance(); // formated string of the balance
        std::string printAccountStatus(); // formated print of the account status

        /* Credit Account Transaction Series */
        TransactionReceipt getBalanceDue(CreditCard creditCard);
        TransactionReceipt payBalanceDue(CreditCard creditCard);
        TransactionReceipt creditTransaction(CreditCard creditCard);
        TransactionReceipt reOpenAccount(TransactionTicket transactionTicket);
        TransactionReceipt closeAccount(TransactionTicket transactionTicket);

        // Credit Account Log series
        void addTransactionReceipt(TransactionReceipt transactionReceipt);

    private:
        Depositor creditor; // creditor
        int accountNumber; // account Number
        AccountType accountType; // account type
        double balanceDue; // balance due
        bool accountStatus; // account status
        double interestRate = 0.07; // interest Rate
        // transaction receipts
        std::vector<TransactionReceipt> transactionReceipts; 
};

// Unit Testing 
void testCreditAccount();