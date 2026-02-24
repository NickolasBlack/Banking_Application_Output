#pragma once

#include "Stdafx.hpp"
#include "BankAccount.hpp"
#include "Check.hpp"

/*
    Checking account class
    contains a clear check method. Clients can make deposits and 
    withdrawls when they want to. Charges an over draft free if account
    is over drawn
*/
class CheckingAccount: public BankAccount {
    public:
        // Checking Account constructor series
        CheckingAccount(); // no args constructor
        CheckingAccount(
            // Checking account key word args constructor
            Depositor depositor, // depositor
            int accountNumber, // account number
            double accountBalance, // account balance
            bool accountStatus // account Status
        );
        CheckingAccount(const CheckingAccount& otherCheckingAccount);

        // Checking Account Transaction Series
        TransactionReceipt clearCheck(Check checkToClear);
};

// Unit Test
void testCheckingAccount();