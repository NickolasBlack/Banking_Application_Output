#pragma once

#include "Stdafx.hpp"
#include "BankAccount.hpp"

/*
    Bank Class
    Reads accounts from a txt file, contains an array of bank account,
    commercial accounts and brokerage accounts. Can perform withdrawls,
    deposits, transfers, brokerage transactions
*/
class Bank{
    public:
        // Constructor Series
        Bank(int numberOfTransactions); 

        /* Bank Class Transaction Series */
        TransactionReceipt bankAccountTransaction(BankAccount* randomAccount);
        TransactionReceipt checkingAccountTransaction(BankAccount* checkingAccount);
        TransactionReceipt commercialAccountTransaction(BankAccount* commercialAccount);
        TransactionReceipt brokerageAccountTransaction(BankAccount* brokerageAccount);


        void loadAccounts(const std::string& fileName); // load accounts
        void writeDataBase(std::ofstream& out); // write account

        TransactionReceipt transactionHistory(BankAccount* bankAccount);
        TransactionReceipt clientInformation(BankAccount* BankAccount);


        // Fommatter
        std::string printFormattedBalance(double balance);

    private:
        std::vector<std::unique_ptr<BankAccount>> accountDatabase; // data base of accounts
        // Static Variables
        static int totalNumberOfAccounts; // total number of accounts
        static double valueOfAllAccounts; // value of all accounts
        static int totalNumberOfCheckingAccounts; // total number of checking accounts
        static double valueOfAllCheckingAccounts; // value of all checking accounts
        static int totalNumberOfSavingsAccounts; // number of savings accounts
        static double valueOfAllSavingsAccounts; // value of all saving accounts
        static int totalNumberOfCDAccounts; // number of cd accounts
        static double valueOfAllCDAccounts; // value of all cd account
        static int totalNumberOfCommercialAccounts; // number of commerical accounts
        static double valueOfAllCommercialAccounts; // value of all commercial accounts
        static int totalNumberOfBrokerageAccounts; // number of brokerage accounts
        static double valueOfAllBrokerageAccounts; // value of all brokerage accounts
        static int totalNumberOfCreditAccounts; // total number of credit accounts
        static double valueOfAllCreditAccounts; // value of all credit accounts

        BankAccount* findAccountByNumber(std::string socialSecurityNumber);
};