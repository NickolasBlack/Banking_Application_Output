#include "Bank.hpp"
#include "RandomGenerator.hpp"
#include "Name.hpp"
#include "Depositor.hpp"
#include "BankAccount.hpp"
#include "TransactionReceipt.hpp"
#include "Check.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"
#include "CDAccount.hpp"
#include "CreditAccount.hpp"
#include "CommercialAccount.hpp"
#include "BrokerageAccount.hpp"

using namespace std;

void unitTest(){
    testName(); // test Name
    testDepositor(); // test depositor
    testTransactionReceipt(); // test transaction receipt
    testTransactionTicket(); // test Transaction Ticket
    testBankAccount(); // test bank Account
    testCalendar(); // test calendar
    testCheck(); // test Check
    testSavingsAccount(); // Test Savings aAccount
    testCheckingAccount(); // test checking Account
    testCDAccount(); // test CD Account
    testCreditAccount(); // test Credit Account
    testCommercialAccount(); // test Commercial Account
    testStock(); // test stock
    testBond(); // test bon
    testOption();// test option
    testBrokerageAccount(); // test brokerage account
    testRandomGenerator(); // test random generator
}

// Intialize static variables 
int Bank::totalNumberOfAccounts = 0;
int Bank::totalNumberOfSavingsAccounts = 0;
int Bank::totalNumberOfBrokerageAccounts = 0;
int Bank::totalNumberOfCDAccounts = 0;
int Bank::totalNumberOfCheckingAccounts = 0;
int Bank::totalNumberOfCommercialAccounts = 0;
int Bank::totalNumberOfCreditAccounts = 0;
double Bank::valueOfAllAccounts = 0.0;
double Bank::valueOfAllBrokerageAccounts = 0.0;
double Bank::valueOfAllCDAccounts = 0.0;
double Bank::valueOfAllCommercialAccounts = 0.0;
double Bank::valueOfAllCheckingAccounts = 0.0;
double Bank::valueOfAllSavingsAccounts = 0.0;
double Bank::valueOfAllCreditAccounts = 0.0;

/* Vank Constructor Series */
Bank::Bank(int numberOfTransactions){
    // Perform unit test
    unitTest();
    // Initialize output file name
    string outputFileName = "BankApplicationOutput.html";
    // Load Accounts
    loadAccounts("bankAccounts.txt");

    // Re open file to append
    ofstream programOutput(outputFileName);
    if (!programOutput){
        throw runtime_error("Could not open output file");
    }

    // Write HTML Header
    programOutput << "<!DOCTYPE html>\n"
                  << "<html>\n"
                  << "<head>\n"
                  << "<title>Bank Database</title>\n"
                  << "<style>\n"
                  << "body { font-family: monospace; }\n"
                  << "pre { margin-bottom: 30px; }\n"
                  << "</style>\n"
                  << "</head>\n"
                  << "<body>\n";
    programOutput << "<b>Number Of Transactions: </b>"
                  << numberOfTransactions << "\n\n";

    // Print database
    writeDataBase(programOutput);

     // Random Generator 
    RandomGenerator randomGenerator;
    for (int i = 0; i < numberOfTransactions; i++){
        size_t index = randomGenerator.randomInteger(
            0,
            accountDatabase.size() - 1
        );
        // Ge random account
        BankAccount* randomAccount = accountDatabase[index].get();
        // Initialize transaction receipt 
        TransactionReceipt transactionReceipt;

        TransactionTicket transactionTicket = randomGenerator.generateBankAccountTransaction(
            randomAccount->getAccountNumber()
        );

        if (transactionTicket.getType() == TransactionType::Balance){
            transactionReceipt = randomAccount->getBalance(transactionTicket);
        } else {
            switch (randomAccount->getType()){
                case AccountType::Commercial:
                    transactionReceipt = commercialAccountTransaction(
                        randomAccount
                    );
                    break;
                case AccountType::Brokerage:
                    transactionReceipt = brokerageAccountTransaction(
                        randomAccount
                    );
                    break;
                case AccountType::Checking:
                    transactionReceipt = checkingAccountTransaction(
                        randomAccount
                    );
                    break;
                default:
                    transactionReceipt = bankAccountTransaction(
                        randomAccount
                    );
            }

        }

        // Addjust bank statistics
        if (transactionReceipt.getTransactionSuccess()){
            // Copy ticket and account type
            TransactionTicket ticket = transactionReceipt.getTransactionTicket();
            string accountType = transactionReceipt.getAccountType();
            // Adjust individual account Balances
            switch(transactionReceipt.getTransactionTicket().getType()){
                case TransactionType::Withdrawl:
                case TransactionType::ClearCheck:
                // Decerement all accounts
                    valueOfAllAccounts-= ticket.getTransactionAmount();
                    if (accountType == "Savings"){
                        // adjust savings
                        valueOfAllSavingsAccounts-=ticket.getTransactionAmount();
                    } else if (accountType == "Checking"){
                        // adjust checking
                        valueOfAllCheckingAccounts-=ticket.getTransactionAmount();
                    } else if (accountType == "CD"){
                        // Adjust CD
                        valueOfAllCDAccounts -= ticket.getTransactionAmount();
                    } else if (accountType == "Commercial"){
                        // Addjust commercial
                        valueOfAllCommercialAccounts-=ticket.getTransactionAmount();
                    } else if (accountType == "Brokerage"){
                        // Adjust Brokerage
                        valueOfAllBrokerageAccounts -= ticket.getTransactionAmount();
                    }
                    break;
                case TransactionType::Deposit:
                    // Increment all accounts
                    valueOfAllAccounts+= ticket.getTransactionAmount();
                    if (accountType == "Savings"){
                        // Increment savings
                        valueOfAllSavingsAccounts+=ticket.getTransactionAmount();
                    } else if (accountType == "Checking"){
                        // increment checking
                        valueOfAllCheckingAccounts+=ticket.getTransactionAmount();
                    } else if (accountType == "CD"){
                        // incremengt CD
                        valueOfAllCDAccounts += ticket.getTransactionAmount();
                    } else if (accountType == "Commercial"){
                        // Increment Commercial
                        valueOfAllCommercialAccounts+=ticket.getTransactionAmount();
                    } else if (accountType == "Brokerage"){
                        // increment brokerage
                        valueOfAllBrokerageAccounts += ticket.getTransactionAmount();
                    }
                    break; // stop
                case TransactionType::PayBalance:
                    // Increment credit balance
                    valueOfAllCreditAccounts-=ticket.getTransactionAmount();
                    valueOfAllAccounts+=ticket.getTransactionAmount(); // incremant all account value
                    break;
                case TransactionType::CreditTransaction:
                    // decrement credit balance
                    valueOfAllCreditAccounts+=ticket.getTransactionAmount();
                    valueOfAllAccounts-=ticket.getTransactionAmount();
                    break;
                default:
                    break;
            }
        }

        // write receipt to the HTML file using print method
        programOutput << "<pre>\n"
                      << "Transaction Requested: " 
                      << transactionReceipt.getTransactionTicket().getTransactionType() << "\n"
                      << randomAccount->printAccountReceipt() << "\n"
                      << transactionReceipt.printTransactionReceipt()
                      << "\n</pre>\n";
    
    }
    // Print the data base
    writeDataBase(programOutput); 

    programOutput << "\n</body>\n</html>\n";
    programOutput.close();
}

TransactionReceipt Bank::bankAccountTransaction(BankAccount* randomAccount){
    // Bank class bank account transaction method. Performs a regular transaction
    RandomGenerator randomGenerator; // initialize random generator
    TransactionReceipt transactionReceipt;
    TransactionTicket transactionTicket = randomGenerator
        // Generate Transaction Ticket
                        .generateBankAccountTransaction(
                            randomAccount->getAccountNumber()
                        );
    
    
    // Perform transaction 
    switch(transactionTicket.getType()){
        case TransactionType::Balance:
            // Get balance
            return transactionReceipt = randomAccount -> getBalance(
                transactionTicket
            );
        case TransactionType::Withdrawl:
            try {
                return transactionReceipt = randomAccount->makeWithdrawl(
                    // Make Withdrawl
                    transactionTicket
                );
            } catch (const InvalidAmountException& e){
                return transactionReceipt = TransactionReceipt(
                    transactionTicket, // transaction ticket
                    randomAccount->getAccountType(), // account type
                    randomAccount->getAccountBalance(), // account balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // fasle
                    e.what() // error message
                );
            } catch (const InsufficientFundsException& e) {
                return transactionReceipt = TransactionReceipt(
                    transactionTicket, // transaction ticket
                    randomAccount->getAccountType(), // account type
                    randomAccount->getAccountBalance(), // pre balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // false
                    e.what() // error message
                );
            } catch (const CDMaturityDateException& e) {
                return transactionReceipt = TransactionReceipt(
                    // maturitty date exception
                    transactionTicket, // transactionTicket
                    randomAccount->getAccountType(), // account type
                    randomAccount->getAccountBalance(), // pre balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // failure
                    e.what() // error message
                );
            }
        case TransactionType::Deposit:
            try {
                return transactionReceipt = randomAccount->makeDeposit(
                    // Make deposit
                    transactionTicket
                );
            } catch (const InvalidAmountException& e) {
                return transactionReceipt = TransactionReceipt(
                    transactionTicket, // transaction Ticket
                    randomAccount->getAccountType(), // account type
                    randomAccount->getAccountBalance(), // pre balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // false
                    e.what() // error message
                );
            } catch (const InvalidAccountException& e) {
                return transactionReceipt = TransactionReceipt(
                    transactionTicket, // transaction ticket
                    randomAccount->getAccountType(), // random account type
                    randomAccount->getAccountBalance(), // pre balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // faled
                    e.what() // error
                );
            }
        case TransactionType::Close:
            try {
                return transactionReceipt = randomAccount->closeAccount(
                    // close account 
                    transactionTicket
                );
            } catch (const AccountClosedException& e){
                return transactionReceipt = TransactionReceipt(
                    transactionTicket, // transaction tikcet
                    randomAccount->getAccountType(), // account type
                    randomAccount->getAccountBalance(), // pre balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // failure
                    e.what() // error message
                );
            }
            break;
        case TransactionType::Open:
            try {
                return transactionReceipt = randomAccount -> reOpenAccount(
                    // open account
                    transactionTicket
                );
            } catch (const AccountOpenException& e){
                return transactionReceipt = TransactionReceipt(
                    transactionTicket, // tranastion ticket
                    randomAccount->getAccountType(), // account type
                    randomAccount->getAccountBalance(), // pre balance
                    randomAccount->getAccountBalance(), // post balance
                    false, // failed
                    e.what() // error message
                );
            }
            break;
        case TransactionType::TransactionHistory:
            // return transaction history
            return transactionHistory(randomAccount);
        case TransactionType::ClientInfo:
            // return client info
            return clientInformation(randomAccount);
        default: 
            return TransactionReceipt(); // return null receipt
    }
}

TransactionReceipt Bank::checkingAccountTransaction(BankAccount* checkingAccount){
    // Bank Account Checking Account transaction either runs a regular transaction
    // clear check
    CheckingAccount* randomCheckingAccount = // dynamic cast
        dynamic_cast<CheckingAccount*>(checkingAccount);

    // Perform checks
    if(!randomCheckingAccount ||
        randomCheckingAccount->getType() != AccountType::Checking){
            return TransactionReceipt(); // return null receipt
        }
    
    // Initialize random generator
    RandomGenerator randomGenerator;
    int transaction = randomGenerator.randomInteger(1, 2);
    Check checkToClear = randomGenerator.generateCheckingTransaction(
        // generate check to clear
        randomCheckingAccount->getAccountNumber()
    );

    if (transaction == 1){
        try{
            // return clear check transaction receipt
            return randomCheckingAccount->clearCheck(
                checkToClear // check to clear
            );
        } catch (const CheckTooOldException& e) {
            return TransactionReceipt(
                TransactionTicket(
                    TransactionType::ClearCheck,
                    randomCheckingAccount->getAccountNumber(),
                    checkToClear.getCheckAmount(),
                    Calendar(), // time now
                    0
                ),
                randomCheckingAccount->getAccountType(), // account type
                randomCheckingAccount->getAccountBalance(), // pre balance
                randomCheckingAccount->getAccountBalance(), // post balance
                false, // failed
                e.what() // error
            );
        } catch (const InsufficientFundsException& e){
            return TransactionReceipt(
                // Return in sufficient funds receipt
                TransactionTicket(
                    TransactionType::ClearCheck, // transaction type
                    randomCheckingAccount->getAccountNumber(), // account number
                    checkToClear.getCheckAmount(), // transaction amount
                    Calendar(), // time now
                    0
                ),
                randomCheckingAccount->getAccountType(), // account type
                randomCheckingAccount->getAccountBalance(), // pre balance
                randomCheckingAccount->getAccountBalance(), // post balance
                false, // failed
                e.what() // error 
            );
        } catch (const PostDatedCheckException& e) {
            return TransactionReceipt(
                // Return post dated check exception
                TransactionTicket(
                    TransactionType::ClearCheck, // transaction type
                    randomCheckingAccount->getAccountNumber(), // account number
                    checkToClear.getCheckAmount(), // check amount
                    Calendar(), // time now
                    0
                ),
                randomCheckingAccount->getAccountType(), // account type
                randomCheckingAccount->getAccountBalance(), // pre balance
                randomCheckingAccount->getAccountBalance(), // post balance
                false, // failed
                e.what() // error
            );
        }
    }
    // Return regular transaction
    return bankAccountTransaction(randomCheckingAccount);
}

TransactionReceipt Bank::commercialAccountTransaction(BankAccount* commercialAccount){
    // Bank Class commercial account Transaction. generates a transaction
    // for a commercial account
    RandomGenerator randomGenerator;
    TransactionReceipt transactionReceipt;
    int type = randomGenerator.randomInteger(1, 3);
    CommercialAccount* randomCommercialAccount =
        dynamic_cast<CommercialAccount*>(commercialAccount);
        
    if(!randomCommercialAccount){
        return TransactionReceipt(); // return null receipt
    }

    if (type == 1){
        // Perform checking transaction
        return checkingAccountTransaction(
            randomCommercialAccount
        );
    } 

    if (type == 2){
        // Perform regular banking transaction
        return bankAccountTransaction(
            randomCommercialAccount
        );
    }
    // Generate Credit transaction
    CreditCard creditCard = randomGenerator
        .generateCreditAccountTransaction(
            randomCommercialAccount->getAccountNumber() // account number
        );  
    
    try {
        if (randomCommercialAccount->getCreditAccount().getBalanceDue() > 0){
            creditCard = CreditCard(
                randomCommercialAccount->getAccountNumber(),
                Calendar(
                    randomGenerator.randomInteger(1, 12),
                    randomGenerator.randomInteger(
                        2025,
                        2030
                    )
                ),
                randomGenerator.generateCardLevel(),
                randomGenerator.randomDouble(
                    0,
                    randomCommercialAccount->getCreditAccount().getBalanceDue()
                )
            );
            return randomCommercialAccount->getCreditAccount()
                    .payBalanceDue(
                        creditCard);
        } else {
            return randomCommercialAccount->getCreditAccount()
                    .creditTransaction(creditCard);
        }
    } catch (const InvalidAmountException& e){
        return TransactionReceipt(
            TransactionTicket(
                // return invalid amount receipt
                TransactionType::PayBalance, // transaction type
                randomCommercialAccount->getAccountNumber(), // get account number
                creditCard.getCreditCharge(), // transaction amount
                Calendar(), // time now
                0 // no term
            ),
            randomCommercialAccount->getAccountType(), // account type
            randomCommercialAccount->getAccountBalance(), // prebalance
            randomCommercialAccount->getAccountBalance(), // post balance
            false, // faled
            e.what() // error message
        );
    } catch (const SpendingLimitException& e){
        return TransactionReceipt(
            TransactionTicket(
                // Return spending limit exception
                TransactionType::CreditTransaction, // trans type
                    randomCommercialAccount->getAccountNumber(), // account number
                    creditCard.getCreditCharge(), // transaction amount
                    Calendar(), // now
                    0 // no term
                ),
                randomCommercialAccount->getAccountType(),
                randomCommercialAccount->getAccountBalance(), // pre balance
                randomCommercialAccount->getAccountBalance(), // post balance
                false, // failed
                e.what() // error
            );
    } catch (const CardExpiredException& e){
        return TransactionReceipt(
            // Return card expired exception
            TransactionTicket(
                TransactionType::CreditTransaction, // transaction type
                randomCommercialAccount->getAccountNumber(),
                creditCard.getCreditCharge(), // transaction amount
                Calendar(), // time now
                0
            ),
            randomCommercialAccount->getAccountType(), // account type
            randomCommercialAccount->getAccountBalance(), // pre balance
            randomCommercialAccount->getAccountBalance(), // post balance
            false, // failed
            e.what() // error
        );
    }
}

TransactionReceipt Bank::brokerageAccountTransaction(BankAccount* bankAccount){
    // Bank Brokerage account Transaction generator. Returns a transaction 
    // receipt of a brokerage transaction. Could print portfolio
    BrokerageAccount* brokerageAccount = // Dynamic cast
        dynamic_cast<BrokerageAccount*>(bankAccount);

    // Perform checks
    if (!brokerageAccount || 
        brokerageAccount->getType() != AccountType::Brokerage){
        return TransactionReceipt(); // return null receipt
    }

    // Initialize random generator
    RandomGenerator randomGenerator;
    int transaction = randomGenerator.randomInteger(1, 2);

    if (transaction == 1){
        // Print portfolio
        TransactionTicket transactionTicket(
            TransactionType::Portfolio, // transaction type
            brokerageAccount->getAccountNumber(),
            0.0,
            Calendar(), // time now
            0
        );

        return TransactionReceipt(
            transactionTicket, // transactionticket
            brokerageAccount->getAccountType(), // account type
            brokerageAccount->getAccountBalance(), // pre balance
            brokerageAccount->getAccountBalance(), // post balance
            true, // true
            brokerageAccount->printPortfolio() // portfolio
        );
    }

    // else return nomarl commercial potential
    return commercialAccountTransaction(brokerageAccount);
}

BankAccount* Bank::findAccountByNumber(string socialSecurityNumber){
    // Bank Find account by number method. finds an account 
    // by the account number
    for (const auto& bankAccount: accountDatabase){
        if (bankAccount->getDepositor().getDepositorSSN() 
                    == socialSecurityNumber){
            return bankAccount.get(); // return address
        }
    }
    return nullptr; // not found
}
void Bank::loadAccounts(const string& fileName){
    // Bank Load accounts method. Reads the first name,
    // last name and ssn of an account form a file
    // generates an account and loads it into the bank database
    ifstream inFile(fileName); // intialize file
    RandomGenerator RandomGenerator; // intialize random generator
    if (!inFile){
        // Error handling
        throw runtime_error("Could not open input file");
    }

    string firstName, lastName, ssn;

    while (inFile >> firstName >> lastName >> ssn){
        // Initialize depositor
        Depositor depositor(
            Name(
                firstName, // first name
                lastName // last name
            ),
            ssn // social security number
        );
        // Generate account
        auto account = RandomGenerator.generateAccount(
            depositor // depositor
        );

        // Compute bank statistics
        totalNumberOfAccounts++; // increment total
        valueOfAllAccounts += account->getAccountBalance(); // increment total balance

        switch(account->getType()){
            case AccountType::Savings:
                totalNumberOfSavingsAccounts++; // increment total number of savings accounts
                valueOfAllSavingsAccounts += account->getAccountBalance(); // add to savings total
                break;
            case AccountType::Checking:
                totalNumberOfCheckingAccounts++; // increment total number of checking
                valueOfAllCheckingAccounts += account->getAccountBalance();
                break;
            case AccountType::CD:
                // increment CD total
                totalNumberOfCDAccounts++; // total number of CD account
                // Increment total balance
                valueOfAllCDAccounts += account->getAccountBalance();
                break;
            case AccountType::Brokerage:
                // Increment brokereage total 
                totalNumberOfBrokerageAccounts++;
                totalNumberOfCreditAccounts++;
                // Increment brokerage balance
                valueOfAllBrokerageAccounts += account->getAccountBalance();
                break;
            case AccountType::Commercial:
                // increment total number of commercial accounts
                totalNumberOfCommercialAccounts++;
                // commercial account balance 
                valueOfAllCommercialAccounts += account->getAccountBalance();
                break;
            case AccountType::Credit:
                break;
        }


        accountDatabase.emplace_back(std::move(account)); // std needed
    }
}

void Bank::writeDataBase(ofstream& out){
    // Bank Class write database. Writes the bank data bas and 
    // transactions to a webpage
    // Headline
    out << "<h1>Bank Database</h1>\n";
    out << "<pre>\n";
    out << left
        << setw(27) << "<b>Name</b>"
        << setw(19) << "<b>SSN</b>"
        << setw(20) << "<b>Account#</b>"
        << setw(22) << "<b>Type</b>"
        << setw(16) << "<b>Status</b>"
        << setw(22) << "<b>Balance</b>"
        << setw(15) << "<b>Maturity Date</b>"
        << "\n";
    out << string(100, '*') << "\n";    

     // Accounts (polymorphic)
    for (const auto& account : accountDatabase){
        out << account->printAccount(); // account should return a single line string
        out << "\n"; // single newline, no extra spacing
    }

    // padding
    out << string(100, '*') << "\n";
    // Print bank account statistics
    out << "Total Number of Checking Accounts: "
        << totalNumberOfCheckingAccounts << "\n"
        << "Total Number of Savings Accounts: "
        << totalNumberOfSavingsAccounts << "\n"
        << "Total Number of CD Accounts: "
        << totalNumberOfCDAccounts << "\n"
        << "Total Number of Commercial Accounts: "
        << totalNumberOfCommercialAccounts << "\n"
        << "Total Number of Brokerage Accounts: "
        << totalNumberOfBrokerageAccounts << "\n"
        << "Total Number of Credit Accounts: "
        << totalNumberOfCreditAccounts << "\n\n";;
    // Print bank account balances
    out << right
        << "\t\t\t\t\t\t\tChecking Account Total Balance: "
        << printFormattedBalance(valueOfAllCheckingAccounts) << "\n"
        << "\t\t\t\t\t\t\tSavings Account Total Balance: "
        << printFormattedBalance(valueOfAllSavingsAccounts) << "\n"
        << "\t\t\t\t\t\t\tCD Account Total Balance: "
        << printFormattedBalance(valueOfAllCDAccounts) << "\n"
        << "\t\t\t\t\t\t\tCommercial Account Total Balance: "
        << printFormattedBalance(valueOfAllCommercialAccounts) << "\n"
        << "\t\t\t\t\t\t\tBrokerage Account Total Balance: "
        << printFormattedBalance(valueOfAllBrokerageAccounts) << "\n"
        << "\t\t\t\t\t\t\tCredit Account Total Balance: "
        << printFormattedBalance(valueOfAllCreditAccounts) << "\n";
    // Print Bank Totals
    out << string(100, '*') << "\n";
    out << "\t\t\t\t\t\t\tTotal Number of Accounts: "
        << totalNumberOfAccounts << "\n"
        << "\t\t\t\t\t\t\tTotal Assests Under Management: "
        << printFormattedBalance(valueOfAllAccounts) << "\n"
        << string(100, '*') << "\n";
}

TransactionReceipt Bank::transactionHistory(BankAccount* bankAccount){
    // Bank Calls transaction history. Returns the account receipts
    if (!bankAccount){
        return TransactionReceipt(); // return null receipt
    }

    TransactionTicket transactionTicket(
        TransactionType::TransactionHistory, // transaction type
        bankAccount->getAccountNumber(), // account number
        0.0, // no transaction Amount
        Calendar(), // time now
        0
    );

    // Return transaction receipt
    TransactionReceipt transactionReceipt = TransactionReceipt(
        transactionTicket, // transaction ticket
        bankAccount->getAccountType(), // account Type
        bankAccount->getAccountBalance(), // pre balance
        bankAccount->getAccountBalance(), // post balance
        true, // success
        bankAccount->printTransactionHistory()
    );
    bankAccount->addTransactionReceipt(transactionReceipt);
    return transactionReceipt;
}

TransactionReceipt Bank::clientInformation(BankAccount* bankAccount){
    // Bank class client information. returns the accounts of a 
    // particular client
    if (!bankAccount){
        return TransactionReceipt(); // return null receipt
    }
    string depositorSSN = bankAccount->getDepositor().getDepositorSSN();

    // Initialize transaction ticket
    TransactionTicket transactionTicket(
        TransactionType::ClientInfo, // transaction type
        bankAccount->getAccountNumber(), // accou8nt number
        0.0, // no amount
        Calendar(), // time now
        0 // no term
    );

    vector<BankAccount*> clientAccounts; // vector of client accounts
    for (const auto& account: accountDatabase){
        // Check ssn for every account
        if (account->getDepositor().getDepositorSSN() 
                    == depositorSSN){
            // append to client accounts array
            clientAccounts.push_back(account.get());
        }
    }

    ostringstream clientInfo; // Initialize string object
    clientInfo << left
               << setw(20) << "Name"
               << setw(12) << "SSN"
               << setw(10) << "Acct Num"
               << setw(15) << "Type"
               << setw(13) << "Status"
               << setw(13) << "Balance"
               << setw(15) << "Maturity Date"
               << "\n"
               << string(100, '*') << "\n"; 

    for (const auto& clientAcct: clientAccounts){
        // Print account Transaction histor
        clientInfo << clientAcct->printAccount() << "\n";
    }
    clientInfo << string(100, '*') << "\n"
               << "\t\t\t\t\t\tNumber of Accounts: "  // Number of Accounts
               << to_string(clientAccounts.size());

    // Initialize Transaction receipt
    TransactionReceipt transactionReceipt = TransactionReceipt(
        transactionTicket, // transaction ticket
        bankAccount->getAccountType(), // account type
        bankAccount->getAccountBalance(), // pre balance
        bankAccount->getAccountBalance(), // post balance
        true, // succes
        clientInfo.str() // transaction histories
    );
    // Append and return 
    bankAccount->addTransactionReceipt(transactionReceipt);
    return transactionReceipt;
}


string Bank::printFormattedBalance(double balance){
    // Bank Class print formmated balance
    // Bank account print account balance method. Prints a fomatted
    // balance
    ostringstream bankAccountBalance;  // write string stream
    bankAccountBalance << "$" << fixed << setprecision(2) << balance;
    // convert to string
    string formattedBalance = bankAccountBalance.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }

    return formattedBalance; // return balance
}



