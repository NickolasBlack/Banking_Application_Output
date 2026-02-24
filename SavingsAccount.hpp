#pragma once

#include "Stdafx.hpp"
#include "BankAccount.hpp"

/*
    Savings Account Class
    this class extends bank account. A client can perform deposits
    and withdraws at any time
*/
class SavingsAccount: public BankAccount{
    public:
        // Savings Account constructor series
        SavingsAccount(); // no args constructor
        SavingsAccount(
            // Savings Account no args constructir
            Depositor depositor, // depositor
            int accountNumber, // account number
            double accountBalance, // account balance
            bool accountStatus // account status
        );
        SavingsAccount(const SavingsAccount& otherSavingsAccount);
};

// Unit Test
void testSavingsAccount();