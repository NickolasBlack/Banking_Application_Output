#include "CDAccount.hpp"

using namespace std;

/* CD Account constructor series */
CDAccount::CDAccount() : SavingsAccount (
    // CD Account No args constructor
    Depositor(), // null depositor
    000000, // account number
    0.0, // balance
    true // open
), maturityDate(Calendar()) {
    accountType = AccountType::CD;
}

CDAccount::CDAccount(
    // CD Account Key word args constructor
    Depositor depositor, // depositor
    int accountNumber, // account number
    double accountBalance, // account Balance
    bool accountStatus, // account status
    int cdTerm // cd term
) : SavingsAccount (
    depositor, // set depositor
    accountNumber, // set account number
    accountBalance, // set account balance
    accountStatus // set status
) {
    // Set account type
    accountType = AccountType::CD;
    // Compute maturity date
    Calendar today;
    maturityDate = Calendar(
        today.getMonth(), 
        today.getDay(), 
        today.getYear() + cdTerm
    );
}

CDAccount::CDAccount(
    // CD Account Key word args constructor with maturity date
    Depositor depositor, // depositor
    int accountNumber, // account number
    double accountBalance, // account Balance
    bool accountStatus, // account status
    Calendar maturityDate
) : SavingsAccount (
    depositor, // set depositor
    accountNumber, // set account number
    accountBalance, // set account balance
    accountStatus // set status
), maturityDate(maturityDate) {
    // Set account type
    accountType = AccountType::CD;
}

CDAccount::CDAccount(
    // CD Account copy constructor
    const CDAccount& otherCDAccount 
) : SavingsAccount(otherCDAccount){}

/* CD Account getter series */
Calendar CDAccount::getMaturityDate(){
    // CD account get maturity date. returns a calendar 
    // object of the maturity date
    return Calendar(maturityDate); // return copy
}

/* CD Account Transaction Series */
TransactionReceipt CDAccount::makeWithdrawl(
    // CD Account Make Withdrawl method. check for maturity date
    // returns a transaction receipt
    TransactionTicket transactionTicket
) {
    // Get todays date
    Calendar today; 
    double preTransactionBalance = accountBalance;

    // check for maturity
    if (today.before(maturityDate)){
        // throw maturity date exception
        throw CDMaturityDateException(maturityDate.printDate());
    }

    // Compute new Maturity Date
    maturityDate = Calendar(
        today.getMonth(), 
        today.getDay(), 
        today.getYear() + transactionTicket.getCDTerm()
    );
    // Perform withdrawl and append receipt
    SavingsAccount::makeWithdrawl(transactionTicket);
    TransactionReceipt transactionReceipt = TransactionReceipt(
        // Cd Transaction receipt
        transactionTicket, // transaction Ticket
        getAccountType(),
        preTransactionBalance, // pre balance
        accountBalance, // post balance
        true, // succes
        " ",
        Calendar(maturityDate) // new maturity date
    );
    return transactionReceipt; // return receupt
}

TransactionReceipt CDAccount::makeDeposit(
    // CD Make deposit method. Returns an Invalid Account Exception
    TransactionTicket transactionTicket
){
    Calendar today; // todays date
    double preTransactionBalance = accountBalance; // copy balance

    if (today.before(maturityDate)){
        // Throw invalid account error
        throw InvalidAccountException("Cannot deposit into a CD after opening");
    }

    // Compute new Maturity Date
    maturityDate = Calendar(
        today.getMonth(), 
        today.getDay(), 
        today.getYear() + transactionTicket.getCDTerm()
    );
    // Perform withdrawl and append receipt
    SavingsAccount::makeDeposit(transactionTicket);
    TransactionReceipt transactionReceipt = TransactionReceipt(
        // Cd Transaction receipt
        transactionTicket, // transaction Ticket
        getAccountType(),
        preTransactionBalance, // pre balance
        accountBalance, // post balance
        true, // succes
        " ",
        Calendar(maturityDate) // new maturity date
    );
    return transactionReceipt; // return receupt
}

/* CD Accoount Formmate Series */
string CDAccount::printAccount(){
    ostringstream cdAccountString; // initialize string stream
    cdAccountString << SavingsAccount::printAccount() 
                    << right << setw(15) 
                    << maturityDate.printDate();
    return cdAccountString.str();
}

string CDAccount::printAccountReceipt(){
    // CD account print account Receipt
    ostringstream cdAccountReceipt;
    cdAccountReceipt << BankAccount::printAccountReceipt()
                     << "\t\t\tMaturity Date: "
                     << maturityDate.printDate();
    return cdAccountReceipt.str();
}

// CD Account Unit Test
static void testCDAcct(){
    // unit test for CD Account creation
    CDAccount testCDAccount = CDAccount(
        // Test CD account
        Depositor(), // null depositor
        000000, // account number
        100.0 , // balance
        true, // account open
        Calendar(1,9,2026)
    );
    // Assert 
    ASSERT(testCDAccount.getDepositor() != nullptr);
    ASSERT(testCDAccount.getAccountNumber() == 000000);
    ASSERT(testCDAccount.getAccountBalance() == 100.0);
    ASSERT(testCDAccount.getAccountStatus() == true);
    ASSERT(testCDAccount.getMaturityDate().getDay() == 1);
    ASSERT(testCDAccount.getMaturityDate().getMonth() == 9);
    ASSERT(testCDAccount.getMaturityDate().getYear() == 2026);
}

void testCDAccount(){
    // Unit Test for CD Account Class
    TEST(testCDAcct);
}