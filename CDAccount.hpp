#pragma once

#include "Stdafx.hpp"
#include "SavingsAccount.hpp"

/*
    CD Account Class 
    Extends Savings Account. Clients make an intial deposit
    but cannot withdrawl or deposit until maturity date
*/
class CDAccount : public SavingsAccount{
    public:
        // CD Account class constructor series
        CDAccount(); // No args constructor
        CDAccount(
            // CD Account key args constructor
            Depositor depositor, // depositor
            int accountNumber, // account number
            double accountBalance, // account balance
            bool accountStatus, // account status
            int cdTerm
        );
        CDAccount(
            // CD Account key args constructor
            Depositor depositor, // depositor
            int accountNumber, // account number
            double accountBalance, // account balance
            bool accountStatus, // account status
            Calendar maturityDate
        );
        // CD Account copy constructor
        CDAccount(const CDAccount& otherCDAccount);

        /* CDAccount getter series */
        Calendar getMaturityDate(); // return maturity date

        /* CD Account Transaction Series */
        TransactionReceipt makeWithdrawl(
            // Make withdrawl method overrides withdraw
            TransactionTicket transactionTicket // transaction ticket
        ) override;

        TransactionReceipt makeDeposit(
            // Make deposit method overrides deposit
            TransactionTicket transactionTicket // transaction ticket
        ) override;

        // CD Account print series
        std::string printAccount() override;
        std::string printAccountReceipt() override;

    private:
        Calendar maturityDate; // maturity date
};

// Unit test 
void testCDAccount();