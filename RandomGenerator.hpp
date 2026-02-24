#pragma once

#include <random>
#include "Investment.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "CommercialAccount.hpp"
#include "BrokerageAccount.hpp"
#include "CreditAccount.hpp"
#include "CDAccount.hpp"
#include "TransactionTicket.hpp"

/*
    Random Generator class
    this class generate random numbers to be used on accounts an
    transactions. It also generates random accounts, and transactions
    for the simulation
*/
class RandomGenerator{
    public:
        // Seeding function
        static std::mt19937& randomNumberGenerator();
        // Random Double
        double randomDouble(double min, double max);
        // random Integer
        int randomInteger(int min, int max);
        // generate account number
        int generateAccountNumber();
        // Generate random account
        std::unique_ptr<BankAccount> generateAccount(
            // Generate an account
            const Depositor& depositor
        );
        // Random Investment generator
        std::unique_ptr<Investment> generateRandomInvestment();
        // Generate random Portfolio
        void generateRandomPortfolio(
            // generate random portfolio
            BrokerageAccount& brokerageAccount, // account
            int size // size of portfolio
        );
        // Generate Card level
        CardLevel generateCardLevel();
        // Transaction generator series
        TransactionTicket generateBankAccountTransaction(int accountNumber);
        Check generateCheckingTransaction(int accountNumber);
        CreditCard generateCreditAccountTransaction(int accountNumber);
};

// Unit test
void testRandomGenerator();