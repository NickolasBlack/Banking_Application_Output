#pragma once

#include "Stdafx.hpp"
#include "Depositor.hpp"
#include "CheckingAccount.hpp"
#include "CreditAccount.hpp"

/*
    Commercial account class
    The extends checking account, can performing checking transactions
    and contains a credit account.
*/
class CommercialAccount : public CheckingAccount { 
    public:
        // Commercial Account constructor series
        CommercialAccount(); // no args constructor
        CommercialAccount(
            // Commercial Account key word args constructor
            CheckingAccount checkingAccount // checking account
        );
        // Commercial account copy constructor
        CommercialAccount(
            const CommercialAccount& otherCommercialAccount // copy
        );

        // Commercial Account getter Series
        CreditAccount getCreditAccount(); // return credit account
        
        /* Commercial Account Logging Series */
        void addTransactionReceipt(
            const TransactionReceipt& transactionReceipt // receipt
        ) override;

    private:
        CreditAccount creditAccount; // credit account
};

// Unit Testing
void testCommercialAccount();