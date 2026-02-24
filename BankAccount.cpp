#include "BankAccount.hpp"


using namespace std;

// Bank Account constructor series
BankAccount::BankAccount():
    // Bank Account No args constructor
    depositor(Depositor()), // depositor
    accountNumber(000000), // account Number
    accountType(AccountType::Checking), // account type
    accountBalance(0.0), // account balance
    accountStatus(false) // account status
{}

BankAccount::BankAccount(
    // Bank Account Key word args cnstructor
    Depositor depositor, // depositor
    int accountNumber, // account number
    AccountType accountType, // account type
    double accountBalance, // account Balance
    bool accountStatus // account status
): 
    depositor(depositor), // set depositor
    accountNumber(accountNumber), // set accound number
    accountType(accountType), // set account type
    accountBalance(accountBalance), // set account balance
    accountStatus(accountStatus) // set account status
{}

BankAccount::BankAccount(
    // Bank Account copy constructor
    const BankAccount& otherBankAccount // other bank account
): 
    depositor(otherBankAccount.depositor), // copy depositor
    accountNumber(otherBankAccount.accountNumber), // copy number
    accountType(otherBankAccount.accountType), // copy type
    accountBalance(otherBankAccount.accountBalance), // copy balance
    accountStatus(otherBankAccount.accountStatus), // copy status
    transactionReceipts(otherBankAccount.transactionReceipts) // copy receipts
{}

// Bank account Getter Series
Depositor BankAccount::getDepositor(){
    // Bank Account Get depositor function. returns depoitor copy
    return Depositor(depositor); // return depositor
}

int BankAccount::getAccountNumber(){
    // Bank account get account number. returns account number
    return accountNumber; // return account number
}

string BankAccount::getAccountType(){
    // Bnak Account get account Type. returns the account Type
    switch(accountType){
        // Checking account 
        case AccountType::Checking:
            return "Checking";
        case AccountType::Savings:
        // Savings account
            return "Savings"; // return savings
        case AccountType::CD:
        // CD account
            return "CD"; // return CD
        case AccountType::Commercial:
        // Commercial Account
            return "Commercial"; // return commercial
        case AccountType::Brokerage:
        // Brokerage Account
            return "Brokerage"; // return brokerage
        default:
            return "Unknown";
    }
}

AccountType BankAccount::getType(){
    // Bank Account return account type. returns just the type
    return accountType;  // return account type
}

double BankAccount::getAccountBalance(){
    // bank account get account balance. returns the account balance
    return accountBalance; // return account balance
}

bool BankAccount::getAccountStatus(){
    // bank account get account Status. returns account status
    return accountStatus; // return status
}

vector<TransactionReceipt> BankAccount::getTransactionReceipts(){
    // bank Account ghet transaction receipt. returns record of 
    // receipts
    return transactionReceipts; // return all receipts
}

// BankAccount Helper Series
void BankAccount::addTransactionReceipt(const TransactionReceipt& transactionReceipt){
    // Bank Account add transaction receipt method. adds a transaction 
    // receipt to the record
    transactionReceipts.emplace_back(transactionReceipt); // add receipt
}

/* Bank Account Transaction Series */
TransactionReceipt BankAccount::getBalance(TransactionTicket transactionTicket){
    // Bank Account get balance. returns the account balance
    TransactionReceipt transactionReceipt = TransactionReceipt(
        // create transaction receipt
        transactionTicket, // transaction ticket
        getAccountType(), // account type
        accountBalance, // account balance
        accountBalance, // account balance
        true, // success
        " "
    ); 

    // add receipt to record
    addTransactionReceipt(transactionReceipt);
    return transactionReceipt; // return receipt
}

TransactionReceipt BankAccount::makeDeposit(TransactionTicket transactionTicket){
    // Bank Account make deposit. deposits funds into an account
    if (transactionTicket.getTransactionAmount() < 0){
        // if transaction amount is less than 0
        throw InvalidAmountException(
            // throw invalid amount exception
            transactionTicket.printTransactionAmount()
        );
    } else {
        // Copy balance and perform valid deposit
        double preTransactionBalance = accountBalance; 
        accountBalance += transactionTicket.getTransactionAmount();

        // Creat transaction Receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            transactionTicket, // transaction ticket
            getAccountType(), // account type
            preTransactionBalance, // pre balance
            accountBalance, // account balance
            true, // succes
            " "
        );

        // Add transaction to record and return receipt
        addTransactionReceipt(transactionReceipt);
        return transactionReceipt; // return receipt
    }
}

TransactionReceipt BankAccount::makeWithdrawl(TransactionTicket transactionTicket){
    // Bank Account make withdrawl method. withdraws funds from an account
    if (transactionTicket.getTransactionAmount() < 0){
        // If transaction amount is less than 0
        throw InvalidAmountException(
            // Throw invalid amount exception
            to_string(transactionTicket.getTransactionAmount())
        );
    } else if (transactionTicket.getTransactionAmount() > accountBalance){
        // if transaction amount is greater than the balance
        throw InsufficientFundsException(
            // throw insufficient funds exception
            printAccountBalance()
        );
    } else {
        // copy balance and perform transaction 
        double preTransactionBalance = accountBalance; // copy balance
        accountBalance -= transactionTicket.getTransactionAmount();

        // Create Transaction Receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            transactionTicket, // transaction ticket
            getAccountType(), // account type
            preTransactionBalance, // pre transaction balance
            accountBalance, // post transaction balance
            true, // success
            " " // no reason
        );

        // Add receipt to record and return
        addTransactionReceipt(transactionReceipt);
        return transactionReceipt; // return receipt
    }
}

TransactionReceipt BankAccount::closeAccount(TransactionTicket transactionTicket){
    // Bank Account close account function. closes an account and withdraws the 
    // balance
    if (accountStatus){
        accountStatus = false; // close account
        accountBalance = 0.0; // set balance to 0

        // generate receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            transactionTicket, // transaction ticket
            getAccountType(), // account type
            accountBalance, // acount balance
            accountBalance, // account balance
            true, // success
            " " // no reason
        );

        // add receipt
        addTransactionReceipt(transactionReceipt);
        return transactionReceipt; // return receipt
    } else {
        throw AccountClosedException();
    }
}
TransactionReceipt BankAccount::reOpenAccount(TransactionTicket transactionTicket){
    // ReOpenAccount function. re-opens a closed account
    if(!accountStatus) {
        accountStatus = true; // re open account

        // Generate receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            transactionTicket, // transaction ticket
            getAccountType(), // account Type
            accountBalance, // pre balance
            accountBalance, // post balance
            true, // success
            " " // no reason
        );
        
        // Add transaction receipt to record
        addTransactionReceipt(transactionReceipt);
        return transactionReceipt; // return receipt
    } else {
        // Throw account open exception
        throw AccountOpenException();
    }
}

/* Bank Account Formmetter Series */
string BankAccount::printAccount(){
    // Bank Account print Account. returns a formatted string of account
    ostringstream accountString; // initialize stream string
    // Build string
    accountString << left << setw(20) << 
                  depositor.getDepositorName().printName()
                  << setw(12) << depositor.getDepositorSSN()
                  << setw(10) << accountNumber
                  << setw(15) << getAccountType()
                  << setw(7) << printAccountStatus()
                  << right << setw(15) <<
                  printAccountBalance();
    return accountString.str(); // return string
}

string BankAccount::printAccountBalance(){
    // Bank account print account balance method. Prints a fomatted
    // balance
    ostringstream balance;  // write string stream
    balance << "$" << fixed << setprecision(2) << accountBalance;
    // convert to string
    string formattedBalance = balance.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }

    return formattedBalance; // return balance
}

string BankAccount::printAccountStatus(){
    // Print account Status. Returns a formatted string of the 
    // account status
    if (accountStatus){
        // return open if true
        return "Open";
    } else {
        // return closed if flase
        return "Closed";
    }
}

string BankAccount::printTransactionHistory(){
    // Bank Account print Transaction history. Returns the long of 
    // receipts
    ostringstream transactionHistory;
    transactionHistory << left
                       << setw(21) << "\nClient Name" // client name
                       << setw(12) << "SSN" // ssn
                       << setw(10) << "Acct Num" // account number
                       << setw(15) << "Acct Type" // account type
                       << setw(7) << "Status" // account status
                       << right
                       << setw(12) << "Balance"; // balance
    if (accountType == AccountType::CD){
        // If maturity date write maturity date headline
        transactionHistory << setw(15) << "Maturity Date";
    }
    transactionHistory << "\n"
                       << printAccount() << "\n"
                       << "\n\n\t\t" 
                       << string(20, '*') << " Transaction History " 
                       << string(20, '*') << "\n"
                       << setw(5) << "Date" // transaction date
                       << setw(20) << "Transaction" // transaction type
                       << setw(15) << "Amount" // transaction amount
                       << setw(10) << "Status" // status
                       << setw(12) << "Balance" // post balance
                       << setw(25) << "Reason for Failure\n"; // error
    for (TransactionReceipt receipt: transactionReceipts){
        // print receipt
        transactionHistory << receipt.printReceipt() << "\n";
    }
    return transactionHistory.str(); // return string
}

string BankAccount::printAccountReceipt(){
    // Print Account prints accounts for receipts
    ostringstream receiptString;
    receiptString << left  
                  << "Client Name: " 
                  << depositor.getDepositorName().printName()
                  << "\t\t\tAccount Number: " 
                  << to_string(accountNumber)
                  << "\nAccount Type: "
                  << getAccountType();
    // return receipt string 
    return receiptString.str();
}

// Unit testing series
static BankAccount generateTestAccount(){
    // Generate test account. generates a test account
    BankAccount testBankAccount = BankAccount(
        // Initialize test account
        Depositor(
            Name("Nickolas", "Black"),
            "123456789"
        ), 000000, AccountType::Savings, 100.00, true
    );
    return testBankAccount; // return test account
}

static void testAccount(){
    // Unit test for bank account creation
    BankAccount testBankAccount = generateTestAccount();
    // Run Assertions
    ASSERT(testBankAccount
            .getDepositor().getDepositorName().printName() ==
            "Nickolas Black");
    ASSERT(testBankAccount
            .getDepositor().getDepositorSSN() ==
            "123456789");
    ASSERT(testBankAccount.getAccountNumber() == 000000);
    ASSERT(testBankAccount.getAccountType() == "Account Type");
    ASSERT(testBankAccount.getAccountBalance() == 100.00);
    ASSERT(testBankAccount.getAccountStatus() == true);
}

static void testGetBalance(){
    // Unit Test for Bank Account get balance function
    BankAccount testBankAccount = generateTestAccount();
    // Generate test transaction ticket
    TransactionTicket testTransactionTicket = TransactionTicket(
        TransactionType::Balance, // transaction type
        testBankAccount.getAccountNumber(), // account Number
        0.0, // transaction amount
        Calendar(01,01,2001), // transaction date
        0 // cd term
    );
    // Generate Transaction receipt
    TransactionReceipt testTransactionReceipt = testBankAccount.getBalance(
        testTransactionTicket // Test ticket
    );
    // Run Assertions
    ASSERT(testTransactionReceipt.getPostTransactionBalance() == 100.00);
}

static void testMakeDeposit(){
    // Unit Test for Bank Account make deposit function 
    BankAccount testBankAccount = generateTestAccount();
    // Generat test Transaction ticket
    TransactionTicket testTransactionTicket = TransactionTicket(
        TransactionType::Deposit, // transaction type
        testBankAccount.getAccountNumber(), // account number
        20.0, // transaction amount
        Calendar(01,01,2001), // transaction date
        0 // cd term
    );
    // Generate test receipt
    TransactionReceipt testTransactionReceipt = testBankAccount.makeDeposit(
        testTransactionTicket // test ticket
    );
    // Run Assertion 
    ASSERT(testTransactionReceipt.getPostTransactionBalance() == 120.0);
}

static void testMakeWithdrawl(){
    // Unit test for bank Account make withdrawl function
    BankAccount testBankAccount = generateTestAccount();
    // Generate test transaction Ticket
    TransactionTicket testTransactionTicket = TransactionTicket(
        TransactionType::Withdrawl, // transaction type
        testBankAccount.getAccountNumber(), // account number
        50.0, // transaction amount
        Calendar(01,01,2001), // transaction date
        0 // cd term
    );
    // Generate transaction Receipt
    TransactionReceipt testTransactionReceipt = testBankAccount.makeWithdrawl(
        testTransactionTicket // test ticket
    );
    // Run Assertions 
    ASSERT(testTransactionReceipt.getPostTransactionBalance() == 50.0);
}

static void testCloseOpenAccount(){
    // Unit test for reopen account
    BankAccount testBankAccount = generateTestAccount();
    // Generate transaction ticket
    TransactionTicket testTransactionTicket = TransactionTicket(
        TransactionType::Close, // transaction type
        testBankAccount.getAccountNumber(), // test account number
        0.0, // transaction amount
        Calendar(01,01,2001), // transaction date
        0 // cd term
    );
    // Generate transaction receipt
    TransactionReceipt testTransactionReceipt = testBankAccount.closeAccount(
        testTransactionTicket // test ticket
    );
    // run assertion
    ASSERT(testBankAccount.getAccountStatus() == false);

    // Generate ticket to re open account
    testTransactionTicket = TransactionTicket(
        TransactionType::Open, // transaction type
        testBankAccount.getAccountNumber(), // account number
        0.0, // transaction amount 
        Calendar(01,01,2001), // transaction date
        0 // cd term
    );
    // Generate transaction Receipt 
    testTransactionReceipt = testBankAccount.reOpenAccount(
        testTransactionTicket // test ticket
    );
    // run assertion 
    ASSERT(testBankAccount.getAccountStatus() == true);
}

static void testBankAccountGetTransactionReceipts(){
    // get transaction receipt unit test
    BankAccount testBankAccount = generateTestAccount();
    // Add a transaction receipt
    testBankAccount.addTransactionReceipt(
        TransactionReceipt() // test receipt
    );
    // assert
    ASSERT(testBankAccount.getTransactionReceipts() != nullptr);
}

static void testAddTransactionReceipt(){
    // Test add transaction Receipt unit test
    BankAccount testBankAccount = generateTestAccount();
    // Add receipts
    testBankAccount.addTransactionReceipt(
        TransactionReceipt() // null receipt
    );
    testBankAccount.addTransactionReceipt(
        TransactionReceipt() // null receipt
    );
    // Run Assertion
    ASSERT(testBankAccount.getTransactionReceipts().size() == 2);
}

static void testPrintAccount(){
    // Unit test for print account
    BankAccount account = BankAccount(
        // Initialize test account
        Depositor(
            // Initialize depositor
            Name(
                // Initialize name
                "Nickolas", "Black"), 
                "123456789"
        ), 
        123456, // Account Number
        AccountType::Checking, // Account Type
        100000000, // account Balance
        true // account status
    );
    // Run Assertion
    ASSERT(account.printAccount() ==
        "Nickolas Black      123456789   123456    Checking     Open      $100,000,000.00");
}

void testBankAccount(){
    // Test account unit test
    TEST(testAccount); // test account creation
    TEST(testPrintAccount); // test print
    TEST(testGetBalance); // test get balance
    TEST(testMakeDeposit); // test make deposit
    TEST(testMakeWithdrawl); // test make withdrawl
    TEST(testCloseOpenAccount); // test close & open account
    TEST(testBankAccountGetTransactionReceipts); // test get receipts
    TEST(testAddTransactionReceipt); // test add receipt
}


