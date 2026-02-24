#include "CheckingAccount.hpp"

using namespace std;

/* Checking account class constructor series */
CheckingAccount::CheckingAccount(): BankAccount(
    // Checking Account no args constructor
    Depositor(), // null depositor
    000000, // account number
    AccountType::Checking, // checking account
    0.0, // balance
    true // status
){}

CheckingAccount::CheckingAccount(
    // Checking account key word args constructor
    Depositor depositor, // depositor
    int accountNumber, // account number
    double accountBalance, // account balance
    bool accountStatus // account status
) : BankAccount(
    // Bank Account constructor
    depositor, // set depositor
    accountNumber, // set account number
    AccountType::Checking, // set checking
    accountBalance, // set account balance
    accountStatus // set account Status
){}

CheckingAccount::CheckingAccount(
    // Checking account copy constructor
    const CheckingAccount& otherCheckingAccount
) : BankAccount(otherCheckingAccount){}

/* Checking Account Transaction Series */
TransactionReceipt CheckingAccount::clearCheck(Check checkToClear){
    // Checking Account Clear Check Method. Withdraws from an account
    double preTransactionBalance = accountBalance; // copy balance
    // Get six months ago
    Calendar today = Calendar(); // today's date
    int presentMonth = today.getMonth();
    int presentYear = today.getYear();

    presentMonth -= 6; // subtract 6
    if(presentMonth <= 0) {
        presentMonth += 12; // add 12 to month
        presentYear -= 1; // subtract 1 from year
    }

    Calendar sixMonthsAgo = Calendar(
        // Six months ago object
        presentMonth, // month
        today.getDay(), // same day
        presentYear // year
    );

    if (checkToClear.getDateOfCheck().before(sixMonthsAgo)){
        // if older than 6 months ago
        throw CheckTooOldException(
            checkToClear.getDateOfCheck().printDate()
        );
    } else if (checkToClear.getCheckAmount() > accountBalance){
        accountBalance -= 2.50; // apply fee
        // Throw exception 
        throw InsufficientFundsException(to_string(preTransactionBalance));
    } else if (checkToClear.getDateOfCheck().after(today)) {
        // if check too old
        throw PostDatedCheckException();
    } else {
        // Valid check clear
        accountBalance -= checkToClear.getCheckAmount();
        // Generate transaction Receipt
        TransactionReceipt transactionReceipt = TransactionReceipt(
            TransactionTicket( // transaction ticket
                TransactionType::ClearCheck, // transaction type
                checkToClear.getAccountNumber(), // account number
                checkToClear.getCheckAmount(), // transaction amount
                today, // time of transaction
                0 // no term
            ), 
            getAccountType(), // account type
            preTransactionBalance, // pre balance
            accountBalance, // post balance
            true, // success
            " " // no failure
        );
        // append receipt and return
        addTransactionReceipt(transactionReceipt);
        return transactionReceipt; // return receipt
    }
}

/* Unit Testing Series */
static void testCheckingAcct(){
    // Unit test for checking account creation
    CheckingAccount testCheckingAccount = CheckingAccount(
        // test checking account
        Depositor(), // null depositor
        000000, // account number
        100.00, // account balance
        true // account open
    );
    // Assert
    ASSERT(testCheckingAccount.getDepositor() != nullptr);
    ASSERT(testCheckingAccount.getAccountNumber() == 000000);
    ASSERT(testCheckingAccount.getAccountType() == "Checking");
    ASSERT(testCheckingAccount.getAccountBalance() == 100.0);
    ASSERT(testCheckingAccount.getAccountStatus() == true);
}

static void testClearCheck(){
    // Unit test for clear check
    Check testCheck = Check(
        // Initialize test check
        000000, // account number
        50.00, // amount
        Calendar() // time now
    );
    // Initialize test Checking account
    CheckingAccount testCheckingAccount = CheckingAccount(
        Depositor(), // null depositor
        testCheck.getAccountNumber(), // account number
        100.00, // balance
        true // open
    ); 
    // Generate Transaction Receipt
    TransactionReceipt transactionReceipt = testCheckingAccount.clearCheck(
        testCheck // test check
    );
    // Assert
    ASSERT_APPROX_EQUAL(
        transactionReceipt.getPostTransactionBalance(), // transaction
        50.00, // expected
        0.001 // tolerance
    );
}

void testCheckingAccount(){
    // Unit test for checking account class
    TEST(testCheckingAcct);
    TEST(testClearCheck);
}

