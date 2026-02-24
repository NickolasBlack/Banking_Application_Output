#include "CommercialAccount.hpp"

using namespace std;

// Commercial Account Constructor Series
CommercialAccount::CommercialAccount():
    // Commercial Account no args constructor
    CheckingAccount(CheckingAccount()), // Null checking account
    creditAccount(CreditAccount(CheckingAccount())) {
        accountType = AccountType::Commercial; // set account type to commerical
    } // Null credit account

CommercialAccount::CommercialAccount(
    // Commercial Account key word args constructor
    CheckingAccount commercialCheckingAccount // Checking account
) : CheckingAccount(commercialCheckingAccount), // set checking
    creditAccount(commercialCheckingAccount){
        accountType = AccountType::Commercial; // set account type to commercial
    } 

CommercialAccount::CommercialAccount(
    const CommercialAccount& otherCommercialAccount
) : CheckingAccount(otherCommercialAccount), // bank account copy constructor
    creditAccount(otherCommercialAccount.creditAccount){} // credit account

/* Commercial Account Getter Series */
CreditAccount CommercialAccount::getCreditAccount(){
    return CreditAccount(creditAccount); // return copy
}

/* Commercial Account Logging Series */
void CommercialAccount::addTransactionReceipt(
    const TransactionReceipt& transactionReceipt
){
    // Overriden add transaction receipts method adds transaction receipts to
    // one account as single location 
    CheckingAccount::addTransactionReceipt(transactionReceipt); // add receipt to checking
}

/* Unit Testing */
static void testCommercialAcct(){
    // Commercial account unit test. tests commercial account creation
    CommercialAccount testCommercialAccount = CommercialAccount(
        CheckingAccount(
            Depositor(), // depositor
            000000, // account Number
            100.0, // account balance
            true // acount open
        )
    );
    // test add transaction receipt
    testCommercialAccount.addTransactionReceipt(
        //Add transaction receipt
        TransactionReceipt()
    );
    testCommercialAccount.addTransactionReceipt(
        // Add transaction receipt
        TransactionReceipt()
    );
    // Assertions
    ASSERT(testCommercialAccount.getDepositor() != nullptr);
    ASSERT(testCommercialAccount.getAccountStatus());
    ASSERT(testCommercialAccount.getAccountNumber() == 000000);
    ASSERT(testCommercialAccount.getAccountBalance() == 100.0);
    ASSERT(testCommercialAccount.getAccountType() == "Commercial");
    ASSERT(testCommercialAccount.creditAccount.getDepositor() != nullptr);
    ASSERT(testCommercialAccount.creditAccount.getAccountNumber() == 000000);
    ASSERT(testCommercialAccount.creditAccount.getAccountType() == "Commercial");
    ASSERT(testCommercialAccount.creditAccount.getAccountBalance() == 0.0);
    ASSERT(testCommercialAccount.creditAccount.getAccountStatus());
    ASSERT(testCommercialAccount.getTransactionReceipts() == 2);
}

void testCommercialAccount(){
    // Unit Test for commercial account
    TEST(testCommercialAcct);
}