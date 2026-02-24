#include "TransactionReceipt.hpp"


using namespace std;

// Transaction receipt constructor series
TransactionReceipt::TransactionReceipt():
    // Transaction Receipt no args constructor
    transactionTicket(TransactionTicket()), // transaction ticket
    accountType(" "), // account type
    preTransactionBalance(0.0), // pre transaction balance
    postTransactionBalance(0.0), // prost transaction balance
    transactionSuccess(false), // transaction success
    reasonForFailure(" ") // reson for failure
{}

TransactionReceipt::TransactionReceipt(
    // Transaction Receipt key word args constructor
    const TransactionTicket& transactionTicket, // transaction ticket
    string accountType, // account type
    double preTransactionBalance, // pre transaction balance
    double postTransactionBalance, // post transaction balance
    bool transactionSuccess, // success indicator
    std::string reasonForFailure // reason for failure
) :
    transactionTicket(transactionTicket), // set transaction ticket
    accountType(accountType), // set account Tyoe
    preTransactionBalance(preTransactionBalance), // set pre balance
    postTransactionBalance(postTransactionBalance), // set post balance
    transactionSuccess(transactionSuccess), // set success
    reasonForFailure(reasonForFailure) // set reason for failure
{}

TransactionReceipt::TransactionReceipt(
    // Transaction Receipt key word args constructor
    const TransactionTicket& transactionTicket, // transaction ticket
    string accountType, // account type
    double preTransactionBalance, // pre transaction balance
    double postTransactionBalance, // post transaction balance
    bool transactionSuccess, // success indicator
    std::string reasonForFailure, // reason for failure
    Calendar newMaturityDate // new maturity date
) :
    transactionTicket(transactionTicket), // set transaction ticket
    accountType(accountType), // set account Tyoe
    preTransactionBalance(preTransactionBalance), // set pre balance
    postTransactionBalance(postTransactionBalance), // set post balance
    transactionSuccess(transactionSuccess), // set success
    reasonForFailure(reasonForFailure), // set reason for failure
    newMaturityDate(newMaturityDate) // new maturity date
{}

TransactionReceipt::TransactionReceipt(
    const TransactionReceipt& otherTransactionReceipt
): 
    transactionTicket(otherTransactionReceipt.transactionTicket), // copy ticket
    accountType(otherTransactionReceipt.accountType), // copy type
    preTransactionBalance(otherTransactionReceipt.preTransactionBalance), // pre
    postTransactionBalance(otherTransactionReceipt.postTransactionBalance), //post
    transactionSuccess(otherTransactionReceipt.transactionSuccess), // success
    reasonForFailure(otherTransactionReceipt.reasonForFailure) // failure reason
{}

// Transaction Receipt getter Series
TransactionTicket TransactionReceipt::getTransactionTicket(){
    // Transaction receipt get transaction ticket. return tranaction ticket
    return TransactionTicket(transactionTicket); // return ticket
}

string TransactionReceipt::getAccountType(){
    // Transaction Receipt get account type. return account type
    return accountType; // return account type
}

double TransactionReceipt::getPreTransactionBalance(){
    // get transaction balance. return pre transaction balance
    return preTransactionBalance; // return pre balance
}

double TransactionReceipt::getPostTransactionBalance(){
    // transaction receipt post transaction balance. return transaction
    // balance 
    return postTransactionBalance; // return post balance
}

bool TransactionReceipt::getTransactionSuccess(){
    // transaction receipt get transaction success
    return transactionSuccess; // return success
}

string TransactionReceipt::getReasonForFailure(){
    // transaction receipt get reason for failure. returns reason 
    // failure
    return reasonForFailure; // return failure reason
}

// Formatter series
string TransactionReceipt::printSuccess(){
    // Transaction Receipt print success method. returns done or
    // failed
    if (transactionSuccess){
        // if transaction successful
        return "Done"; // return done
    } else {
        // if transaction not successful
        return "Failed";
    }
}

string TransactionReceipt::printReceipt(){
    // Transaction Receipt print receipt method. prints
    // a formatted string of the receipt
    ostringstream receipt; // write string stream
    receipt << left << setw(13)
            << transactionTicket.getTransactionDate().printDate()
            << setw(20) << transactionTicket.getTransactionType()
            << setw(12) << printTransactionBalance(transactionTicket.getTransactionAmount())
            << setw(10) << printSuccess()
            << setw(10) << printTransactionBalance(postTransactionBalance);
            if (transactionTicket.getType() != TransactionType::Portfolio ||
                transactionTicket.getType() != TransactionType::TransactionHistory ||
                transactionTicket.getType() != TransactionType::ClientInfo){
                receipt << setw(20) << reasonForFailure;
            }
            
    return receipt.str(); // return receipt
}

string TransactionReceipt::printTransactionBalance(double amount){
    // Bank account print account balance method. Prints a fomatted
    // balance
    ostringstream transactionBalance;  // write string stream
    transactionBalance << "$" << fixed << setprecision(2) << amount;
    // convert to string
    string formattedBalance = transactionBalance.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }

    return formattedBalance; // return balance
}

string TransactionReceipt::printTransactionReceipt(){
    // Transaction Receipt print transaction receipt. Prints a receipt for a transaction
    ostringstream transactionReceipt;
    if (transactionSuccess){
        switch(transactionTicket.getType()){
            case TransactionType::Balance:
                transactionReceipt << "Current Balance: "
                               << printTransactionBalance(
                                postTransactionBalance
                               );
                break;
            case TransactionType::Deposit:
                transactionReceipt << "Account Balance: "
                               << printTransactionBalance(
                                preTransactionBalance
                               )
                               << "\t\t| Amount to Deposit: "
                               << printTransactionBalance(
                                transactionTicket.getTransactionAmount()
                               )
                               << "\nNew Balance: "
                               << printTransactionBalance(
                                postTransactionBalance
                               );
                break;
            case TransactionType::Withdrawl:
                transactionReceipt << "Account Balance: "
                               << printTransactionBalance(
                                preTransactionBalance
                               )
                               << "\t\t| Amount to Withdraw: "
                               << printTransactionBalance(
                                transactionTicket.getTransactionAmount()
                               )
                               << "\nNew Balance: "
                               << printTransactionBalance(
                                postTransactionBalance
                               );
                break;
            case TransactionType::Open:
                transactionReceipt << "Account Open";
                break;
            case TransactionType::Close:
                transactionReceipt << "Account Closed";
                break;
            case TransactionType::BalanceDue:
                transactionReceipt << "Balance Due: "
                                   << printTransactionBalance(
                                    postTransactionBalance
                                   );
                break;
            case TransactionType::ClearCheck:
                transactionReceipt << "Account Balance: "
                                   << printTransactionBalance(
                                    preTransactionBalance // pre balance
                                   )
                                   << "\t\t| Amount of Check: "
                                   << printTransactionBalance(
                                    transactionTicket.getTransactionAmount()
                                   )
                                   << "\nNew Balance: "
                                   << printTransactionBalance(
                                    postTransactionBalance // post balance
                                   );
                break;
            case TransactionType::CreditTransaction:
                transactionReceipt << "Credit Amount: "
                                   << printTransactionBalance(
                                    transactionTicket.getTransactionAmount()
                                   )
                                   << "\t\tBalance Due: "
                                   << printTransactionBalance(
                                    postTransactionBalance
                                   );
                break;
            case TransactionType::PayBalance:
                transactionReceipt << "Balance Due: "
                                   << printTransactionBalance(
                                    preTransactionBalance
                                   )
                                   << "\t\tNew Balance: "
                                   << printTransactionBalance(
                                    postTransactionBalance
                                   );
                break;
            case TransactionType::Portfolio:
                // print portfolio
                transactionReceipt << reasonForFailure;
                break;
            case TransactionType::TransactionHistory:
                // Print receipts
                transactionReceipt << reasonForFailure;
                break;
            case TransactionType::ClientInfo:
                transactionReceipt << "\n" + reasonForFailure;
                break;
                
        }
    } else{
        // write reason for failure
        transactionReceipt << "Current Balance: "
                           << printTransactionBalance(
                                // pre balance
                                preTransactionBalance
                           )
                           << "\t\t\tTransaction Amount: "
                           << printTransactionBalance(
                                // Transaction Amount
                                transactionTicket.getTransactionAmount()
                           ) << "\n";
        transactionReceipt << reasonForFailure;
    }
    
    // Return receipt string 
    return transactionReceipt.str();
}

static void testReceipt(){
    // initialize null transaction ticket
    TransactionTicket transactionTicket = TransactionTicket();
    // Initialize transaction receipt
    TransactionReceipt transactionReceipt = TransactionReceipt(
        transactionTicket, // null ticket
        "Account Type", // account type
        0.0, // pre balance
        0.0, // post balance
        true, // success
        " " // no reason
    );
    // Run Assertions
    ASSERT(transactionReceipt.getTransactionTicket() != nullptr);
    ASSERT(transactionReceipt.getAccountType() == "Account Type");
    ASSERT(transactionReceipt.getPreTransactionBalance() == 0.0);
    ASSERT(transactionReceipt.getPostTransactionBalance() == 0.0);
    ASSERT(transactionReceipt.getReasonForFailure() == " ");
}

void testTransactionReceipt(){
    // Unit test for transaction receipt class
    TEST(testReceipt); // test receipt
}
