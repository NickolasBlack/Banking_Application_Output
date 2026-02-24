#include "CreditAccount.hpp"

using namespace std;

/*
    Credit Account Class has different base functions than bank account
    also will be stored in a different location in memory. Separate array
    for performance. Like searching through 100 or searching through 1000

    has a different base structure. has a balance due which always starts
    at zero. These are credit car transactions
*/

CreditAccount::CreditAccount() :
    // Credit Account no args constructor
    creditor(Depositor()), // depositor
    accountNumber(111111), // account number
    accountType(AccountType::Credit), // account type
    balanceDue(0.0), // balance due
    accountStatus(true) // account open
{}

CreditAccount::CreditAccount(
    // Credit account key word args constructor
    Depositor creditor, // creditor
    int accountNumber, // account number
    double balanceDue, // balance due
    bool accountStatus // account status
):  // Set parameters
    creditor(creditor), // depositor
    accountNumber(accountNumber), // account number
    accountType(AccountType::Credit), // account type
    balanceDue(balanceDue), // balance due
    accountStatus(accountStatus) // account status
{}

CreditAccount::CreditAccount(
    // Credit Account Bank Account constructor constructs a credit
    // account from a bank account
    BankAccount bankAccount
) : creditor(bankAccount.getDepositor()),
    accountNumber(bankAccount.getAccountNumber()),
    accountType(AccountType::Credit),
    balanceDue(0.0),
    accountStatus(true)
{}

CreditAccount::CreditAccount(
    // Credit Account copy constructor
    const CreditAccount& otherCreditAccount
) : // copy other credit account
    creditor(otherCreditAccount.creditor), // creditor
    accountNumber(otherCreditAccount.accountNumber), // account number
    accountType(otherCreditAccount.accountType), // account type
    balanceDue(otherCreditAccount.balanceDue), // balance due
    accountStatus(otherCreditAccount.accountStatus), // account status
    transactionReceipts(otherCreditAccount.transactionReceipts) // receipts
{}

/* credit account getter series */
Depositor CreditAccount::getDepositor(){
    // Credit account get depositor function. returns the creditors
    // depositor object
    return Depositor(creditor); // return copy
}

int CreditAccount::getAccountNumber(){
    // Credit Account get account number. returns the account number
    return accountNumber; // return account number
}

string CreditAccount::getAccountType(){
    // credit account get account type method. return the account type
    return "Credit"; // return account type
}

AccountType CreditAccount::getType(){
    // credit account get type. returns the account type
    return accountType; // return account type
}

double CreditAccount::getBalanceDue(){
    // Credit card get account balance. Returns the account balance
    return balanceDue; // return account balance
}

bool CreditAccount::getAccountStatus(){
    // Credit account get account status. return the account status
    return accountStatus; // return account status
}

vector<TransactionReceipt> CreditAccount::getTransactionReceipts(){
    // Credit Account get transaction receipts. Returns transaction 
    // receipts
    return transactionReceipts; // return transaction receipts
}

/* Credit Account logging series */
void CreditAccount::addTransactionReceipt(TransactionReceipt transactionReceipt){
    // Credit account add transaction receipt method. Add a transaction receipt 
    // to credit account transaction history
    transactionReceipts.emplace_back(transactionReceipt); // emplace back
}

/* Credit Account Formatter series */
string CreditAccount::printAccount(){
    // Credit Account print account method. Prints a formatted string of the account
    ostringstream creditAccountString; // initialize stream string
    // Build string
    creditAccountString << left << setw(20) << 
                  creditor.getDepositorName().printName() // name
                  << setw(12) << creditor.getDepositorSSN() // ssn
                  << setw(10) << accountNumber // account number
                  << setw(15) << getAccountType() // account type
                  << setw(10) << printAccountStatus() // account status
                  << right << setw(12) <<
                  printAccountBalance(); // balance
    return creditAccountString.str(); // return string
}

string CreditAccount::printAccountBalance(){
    // Credit Account print account Balance method. Prints the balance due
    ostringstream balance;  // write string stream
    balance << "$" << fixed << setprecision(2) << balanceDue;
    // convert to string
    string formattedBalance = balance.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }
    return formattedBalance; // return balance
}

string CreditAccount::printAccountStatus(){
    // Credit Account print account status method
    if (accountStatus) {
        // If account open
        return "Open"; // return open
    } else {
        // if account close
        return "Closed"; // return closed
    }
}

/* Credit Account Transaction Series */
TransactionReceipt CreditAccount::getBalanceDue(CreditCard creditCard){
    // Credit Account get balance method. Returns the balance due
    TransactionReceipt transactionReceipt = TransactionReceipt (
        // initialize transaction receipt
        TransactionTicket(
            // Intialize transaction Ticket
            TransactionType::BalanceDue, // get balance due
            accountNumber, // credit account Number
            balanceDue, // balance due
            Calendar(), // time now
            0 // no term
        ), // transaction ticket
        getAccountType(), // account Type
        balanceDue, // account balance
        balanceDue, // balance due
        true, // success
        " " // no reason
    );
    // Add transaction receipt
    addTransactionReceipt(transactionReceipt); // add receipt
    return transactionReceipt; // return transaction receipt   
}

TransactionReceipt CreditAccount::payBalanceDue(CreditCard creditCard){
    // Credit account class pay
    double paymentAmount = creditCard.getCreditCharge() -
                            (interestRate * balanceDue);
    if (creditCard.getCreditCharge() < 0) {
        // If transaction amount is less than zero or payment exceeds
        // balance
        throw InvalidAmountException(
            // throw invalid amount exception
            creditCard.printCreditChargeAmount()
        );
    } else {
        // Copy Balance due and perform valid payment
        double preTransactionBalance = balanceDue;
        balanceDue -= paymentAmount;
        // Generate transaction receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            TransactionTicket(
                // Transaction Ticket
                TransactionType::PayBalance, // Transaction type
                accountNumber, // account number
                creditCard.getCreditCharge(), // credit charge amount
                Calendar(), // time now
                0 // cd term
            ), // transaction ticket
            getAccountType(), // account type
            preTransactionBalance, // prebalance
            balanceDue, // balance due
            true, // success
            " "
        );
        // Append receipt and return
        addTransactionReceipt(transactionReceipt); // add receipt
        return transactionReceipt; // return receipt
    }
}

TransactionReceipt CreditAccount::creditTransaction(CreditCard creditCard){
    // Credit Account credit transaction method. Increases balance due
    if (creditCard.getCreditCharge() < 0) {
        // credit amount is less than 0
        throw InvalidAmountException(
            creditCard.printCreditChargeAmount() // print formatted amount
        );
    } else if (creditCard.getCreditCharge() > creditCard.getCardLimit() ||
               creditCard.getCreditCharge() + balanceDue > 
               creditCard.getCardLimit()){
        // If payment amount is over limit
        throw SpendingLimitException(creditCard.getCardLevel());
    } else {
        // Perform valid transaction
        double preCreditTransactionBalanceDue = balanceDue; // copy balance
        balanceDue += creditCard.getCreditCharge(); // add to balance due
        // Generate transaction receipt 
        TransactionReceipt transactionReceipt = TransactionReceipt(
            TransactionTicket(
                TransactionType::CreditTransaction, // transaction type
                accountNumber, // account number
                creditCard.getCreditCharge(), // transaction amount
                Calendar(), // time now
                0 // no term
            ),
            getAccountType(), // account type
            preCreditTransactionBalanceDue, // pre transaction balance
            balanceDue, // post transaction balance
            true, // success, 
            " " // no reason
        );
        // append and return receipt
        addTransactionReceipt(transactionReceipt);
        return transactionReceipt; // return receipt
    }
}

TransactionReceipt CreditAccount::reOpenAccount(TransactionTicket transactionTicket){
    // Credit account re open account. reopens a closed account
    if (accountStatus){
        // If account already open
        throw AccountOpenException();
    } else {
        // open account
        accountStatus = true; // open account
        // generate transaction receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            transactionTicket, // transaction ticket
            getAccountType(), // account type
            balanceDue, // pre balance
            balanceDue, // post balance
            true, // success
            " " // no reason
        );
        // Append receipt and return 
        addTransactionReceipt(transactionReceipt); // add receipt
        return transactionReceipt; // return receipt
    }
}

TransactionReceipt CreditAccount::closeAccount(TransactionTicket transactionTicket){
    // Credit Account close account. Closes a credit account
    if (!accountStatus){
        // If account already close 
        throw AccountClosedException();
    } else if (balanceDue > 0) {
        // Account has a balance
        throw InvalidAccountException(
            "Account has a balance due of " + printAccountBalance()
        );
    } else {
        // Close account
        accountStatus = false; 
        // Generate transaction receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            transactionTicket, // transaction Ticket
            getAccountType(), // account type
            balanceDue, // balance due should be $0.0
            balanceDue, // again 0.0
            true, // success 
            " " // no failure
        );
        // Append receipt and return 
        addTransactionReceipt(transactionReceipt); // add receipt
        return transactionReceipt; // return receipt
    }
}


/* Credit Account Unit testing series */
static void testCreditAcct(){
    // Unit test for Credit account Creation
    CreditAccount testCreditAccount = CreditAccount(
        // Test credit account
        Depositor(), // null depositor
        111111, // account number
        100.00, // balance due
        true // open
    );
    // Assert 
    ASSERT(testCreditAccount.getDepositor() != nullptr);
    ASSERT(testCreditAccount.getAccountNumber() == 111111);
    ASSERT(testCreditAccount.getAccountType() == "Credit");
    ASSERT(testCreditAccount.getAccountBalance() == 100.0);
    ASSERT(testCreditAccount.getAccountStatus() == true);
}

static void testGetBalanceDue(){
    // Credit Account unit test for get balance
    CreditAccount testCreditAccount = CreditAccount(
        Depositor(), // depositor
        111111, // acount number
        100.0, // balance due,
        true // account status
    );
    // Generate transaction ticket
    CreditCard testCreditCard = CreditCard(
        111111, // acount number
        Calendar(5, 2027), // date
        CardLevel::BASIC, // level
        0.0 // no charge
    );
    // Perform transaction 
    TransactionReceipt testTransactionReceipt = testCreditAccount.getBalanceDue(
        testCreditCard // test credit card
    );
    // Assert
    ASSERT(testTransactionReceipt.getPostTransactionBalance() == 100.0);
}

static void testPayBalanceDue(){
    // Unit Test for make payment
    CreditAccount testCreditAccount = CreditAccount(
        Depositor(), // depositor
        111111, // account number
        100.00, // balance due
        true // account Open
    );
    CreditCard testCreditCard = CreditCard(
        // Test credit card
        testCreditAccount.getAccountNumber(), // account number
        Calendar(3, 2026), // card expiration date
        CardLevel::BASIC, // card type
        100.00 // payment amount should be $7 left over (100 - (100 * 0.07))
    );
    TransactionReceipt testTransactionReceipt = testCreditAccount.payBalanceDue(
        testCreditCard // test card
    );
    // Assert
    ASSERT_APPROX_EQUAL(
        testTransactionReceipt.getPostTransactionBalance(),
        7.0, // $7.00
        0.0001
    );
}

static void testCreditAccountGetTransactionReceipts(){
    // Unit test for get transaction receipt
    CreditAccount testCreditAccount = CreditAccount();
    // Add receipts
    testCreditAccount.addTransactionReceipt(
        TransactionReceipt()
    );
    testCreditAccount.addTransactionReceipt(
        TransactionReceipt()
    );
    // Assert
    ASSERT(testCreditAccount.getTransactionReceipts().size() == 2);
}

static void testCreditTransaction(){
    // Unit test for test credit transaction
    CreditAccount testCreditAccount = CreditAccount(
        Depositor(), // depositor
        111111, // account number
        100.00, // balance due
        true // account Open
    );
    CreditCard testCreditCard = CreditCard(
        // Test credit card
        testCreditAccount.getAccountNumber(), // account number
        Calendar(10,2028), // 10/2028 epiry date
        CardLevel::BASIC, // basic charge level
        100.00 // transaction amount
    );
    // Perform Transaction
    TransactionReceipt testTransactionReceipt = testCreditAccount.creditTransaction(
        testCreditCard // test credit card
    );
    // ASSERT
    ASSERT_APPROX_EQUAL(
        testTransactionReceipt.getPostTransactionBalance(),
        200.00, // $200
        0.0001 
    );
}

static void testCreditAccountReOpenAccount(){
    // Unit Test for reOpen Account
    CreditAccount testCreditAccount = CreditAccount(
        Depositor(), // null depositor
        111111, // account number
        0.0, // no balance due
        false // account close
    );
    // Generate transaction ticket
    TransactionTicket testTransactionTicket = TransactionTicket(
        TransactionType::Open, // transaction type
        111111, // account number
        0.0, // no transaction amount
        Calendar(), // time now
        0 // no term
    );
    // Re open account
    TransactionReceipt testTransactionReceipt = testCreditAccount.reOpenAccount(
        testTransactionTicket // test receipt
    );
    // Assert 
    ASSERT(testCreditAccount.getAccountStatus());
}

static void testCreditAccountCloseAccount(){
    // Unit Test for close Account
    CreditAccount testCreditAccount = CreditAccount(
        Depositor(), // null depositor
        111111, // account number
        0.0, // no balance due
        true // account open
    );
    // Generate Transaction ticket
    TransactionTicket testTransactionTicket = TransactionTicket(
        TransactionType::Close, // transaction Type
        111111, // account number
        0.0, // no amount
        Calendar(), // time now
        0 // no term
    );
    // Close Account
    TransactionReceipt testTransactionReceipt = testCreditAccount.closeAccount(
        testTransactionTicket // test ticket
    );
    // ASSERT
    ASSERT(!testCreditAccount.getAccountStatus()); // closed
}

void testCreditAccount(){
    // Unit test for credit account class
    TEST(testCreditAcct);
    TEST(testGetBalanceDue);
    TEST(testCreditAccountGetTransactionReceipts);
    TEST(testPayBalanceDue);
    TEST(testCreditTransaction);
    TEST(testCreditAccountReOpenAccount);
    TEST(testCreditAccountCloseAccount);
}
