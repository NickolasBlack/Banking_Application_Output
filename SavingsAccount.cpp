#include "SavingsAccount.hpp"

using namespace std;

// Savings Account constructor seris
SavingsAccount::SavingsAccount(): BankAccount(
    // Savings Account No Args Constructor
    Depositor(), // null depositor
    000000, // account number
    AccountType::Savings, // account type
    0.0, // no balance
    true // account open
){}

SavingsAccount::SavingsAccount(
    // Savings Account key word args constructor
    Depositor depositor, // depositor
    int accountNumber, // account number
    double accountBalance, // account balance
    bool accountStatus // account Status
) : BankAccount(
    // Bank Account constructor
    depositor, // set depositor
    accountNumber, // set number
    AccountType::Savings, // set account type
    accountBalance, // set account balance
    accountStatus // set account status
){}

SavingsAccount::SavingsAccount(
    // Savings Account copy constructor
    const SavingsAccount& otherSavingsAccount
) : BankAccount(otherSavingsAccount){}

/* Unit Testing Series */
static void testSavingsAcct(){
    // Unit test for savings account construction
    SavingsAccount testSavingsAccount = SavingsAccount(
        Depositor(), // initialize depositor
        123456, // account number
        100.0, // account balance
        true // account open
    );
    // Assert
    ASSERT(testSavingsAccount.getDepositor() != nullptr);
    ASSERT(testSavingsAccount.getAccountNumber() == 123456);
    ASSERT(testSavingsAccount.getAccountType() == "Savings");
    ASSERT(testSavingsAccount.getAccountBalance() == 100.0);
    ASSERT(testSavingsAccount.getAccountStatus() == true);
}

void testSavingsAccount(){
    // Unit test for savings account class
    TEST(testSavingsAcct);
}
