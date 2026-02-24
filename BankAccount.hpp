#pragma once

#include "Stdafx.hpp"
#include "Depositor.hpp"
#include "TransactionReceipt.hpp"

/*
    AccountType Enum
    returns the account type
*/
enum class AccountType {
    Checking, // checking account
    Savings, // savings account
    CD, // CD account
    Commercial, // Commercial account
    Brokerage, // brokerage account
    Credit // credit account
};

class BankAccount{
    /*
        Bank Account Class
        serves as the base for all accounts. contains a Depositor, account number,
        account type, account balance, account status, and a record of transaction
        receipts
    */
    public:
        // Bank Account constructor series
        BankAccount(); // No args constructor
        BankAccount(
            // Bank Account Key word args constructor
            Depositor depositor, // depositor
            int accountNumber, // account number
            AccountType accountType, // account type
            double accountBalance, // account balance
            bool accountStatus // account status
        );
        // Bank Account copy constructor
        BankAccount(const BankAccount& otherBankAccount);

        // Bank Account Getter Series
        Depositor getDepositor(); // return depositor
        int getAccountNumber(); // return account number
        std::string getAccountType(); // return account type string
        AccountType getType(); // returns account type enum
        double getAccountBalance(); // return account balance
        bool getAccountStatus(); // return account status
        // return all transaction receipts
        std::vector<TransactionReceipt> getTransactionReceipts();

        // Bank Account Transaction Series
        virtual TransactionReceipt getBalance(TransactionTicket transactionTicket);
        virtual TransactionReceipt makeDeposit(TransactionTicket transactionTicket);
        virtual TransactionReceipt makeWithdrawl(TransactionTicket transctionTicket);
        TransactionReceipt reOpenAccount(TransactionTicket transactionTicket);
        TransactionReceipt closeAccount(TransactionTicket transactionTicket);

        // Bank Account helper methods
        virtual void addTransactionReceipt(const TransactionReceipt& transactionReceipt);

        // Bank Account formatted Series
        virtual std::string printAccount(); // formated print
        std::string printAccountBalance(); // format balance
        std::string printAccountStatus(); // format account status
        std::string printTransactionHistory(); // print receipts
        virtual std::string printAccountReceipt(); // format for receipts

        
    protected:
        Depositor depositor; // client name and ssn
        int accountNumber; // account number
        AccountType accountType; // account Type
        double accountBalance; // account balance
        bool accountStatus; // account Status
        std::vector<TransactionReceipt> transactionReceipts; // transaction receipts
        BankAccount* receiptMemoryAddress = nullptr; // Bank Account memory address
       


};

// Unit Testing 
void testBankAccount();