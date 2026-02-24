#include "RandomGenerator.hpp"

using namespace std;

/* Random Number generator Series */
std::mt19937& RandomGenerator::randomNumberGenerator(){
    // Random Generator random number sedding function
    // sets the seeding variable using the mt19937
    static std::mt19937 gen(random_device{}());
    return gen; // return gen
}

double RandomGenerator::randomDouble(
    // Random Generator random double generator
    // generates a random double number between a provided
    // random
    double min, // min number
    double max // max number
){
    return uniform_real_distribution<double>(
        // Uniform distribution
        min, // min 
        max // max
    )(randomNumberGenerator()); // random number generator
}

int RandomGenerator::randomInteger(
    // Random Generator Random Integer generator. Generate a random
    // interger number between two numbers
    int min, // min number
    int max // max number
) {
    // Uniform distribution
    return uniform_int_distribution<int>(
        min, // minimun number
        max // maximum number
    )(randomNumberGenerator()); // random number generator
}

int RandomGenerator::generateAccountNumber(){
    // Generate Account Number. Lowers the probability
    static int nextAccountNumber = 10000; // intial number
    return nextAccountNumber++; // return intial number plus one
}

unique_ptr<BankAccount>
RandomGenerator::generateAccount(const Depositor& client){
    // Random Generator. Random Account generator
    // account
    Depositor depositor(client); // copy depositor

    int randomAccountNumber = generateAccountNumber();
    double accountBalance = randomDouble(100.00, 100000.00);
    bool open = true;
    int type = randomInteger(1,5);

    switch (type){
        // Context switch on account type
        case 1:{
            // 1 for checking Account
            string accountNumber = "1" + to_string(randomAccountNumber);
            return make_unique<CheckingAccount>(
                // generate Checking account
                depositor, // depositor
                stoi(accountNumber), // account number
                accountBalance, // account balance
                open // account open
            );
        }
        case 2: {
            // 2 for savings account
            string accountNumber = "2" + to_string(randomAccountNumber);
            return make_unique<SavingsAccount>(
                // generate savings account
                depositor, // depositor
                stoi(accountNumber), // account number
                accountBalance, // account balance
                open // account open
            );
        }
        case 3:{
            // 3 for CD account
            string accountNumber = "3" + to_string(randomAccountNumber);
            return make_unique<CDAccount>(
                // generate CD account
                depositor, //depositor
                stoi(accountNumber), // account number
                accountBalance, // account balance
                open, // account Open
                Calendar(
                    // Random date
                    randomInteger(1, 12), // random month
                    randomInteger(1, 29), // random day
                    randomInteger(2019, 2029) // random year
                )
            );
        }
        case 4: {
            // 4 for Commercial account
            string accountNumber = "4" + to_string(randomAccountNumber);
            CheckingAccount checkingAccount(
                // Commercial Checking account
                depositor, // depositor
                stoi(accountNumber), // account number
                accountBalance, // acccount balance
                open // account open
            );
            // return commerical acount
            return make_unique<CommercialAccount>(checkingAccount);
        }
        case 5: {
            // 5 for brokerage account
            string accountNumber = "5" + to_string(randomAccountNumber);
            CheckingAccount checkingAccount(
                // Checking Account
                depositor, // depositor
                stoi(accountNumber), // account number
                accountBalance, // account balance
                open // account open
            );
            // Initalize commercial account
            CommercialAccount commercialAccount(checkingAccount);
            auto brokerageAccount = make_unique<BrokerageAccount>(commercialAccount);

            // generate portfolio
            generateRandomPortfolio(
                *brokerageAccount, // brokerage account
                randomInteger(1, 10)
            );
            // Return brokerage account
            return brokerageAccount;
        }
        default:
            // Return null account
            return make_unique<BankAccount>(); // not nullptr
    }
}

unique_ptr<Investment>
RandomGenerator::generateRandomInvestment(){
    // Random Generator generate raondom investment method. generates
    // a random investment transactions
    int type = randomInteger(1,3); // generate random int

    if (type == 1){
        // 1 for stock
        static const vector<string> tickers = {
            "AAPL", // apple
            "MSFT", // microsoft
            "GOOG", // google
            "AMZN", // amazon
            "CDNS", // cadence design
            "NFLX", // netflix
            "DIS", // disney
            "JPM", // jp morgan
            "AMD", // amd
            "BA", // boeing
            "BLK", // blackrock
            "MU", // micron technologies
            "VZ" // verizon
        };

        return make_unique<Stock>(
            // return stock ptr
            tickers[randomInteger(0, tickers.size() - 1)], // random ticker 
            randomInteger(1, 500), // random quantity
            randomDouble(50.0, 1000.0) // random price
        );
    }

    if (type == 2){
        // 2 for bond
        return make_unique<Bond>(
            randomInteger(1, 50), // quantity
            1000.0, // face Value
            randomDouble(0.02, 0.09), // coupon rate
            randomInteger(1, 30) // random years
        );
    }

    return make_unique<Option>(
        // Return option by default
        // Option type
        randomInteger(0, 1) ? OptionType::Call : OptionType::Put,
        randomInteger(1, 20), // number of contracts
        randomDouble(1.0, 15.0), // premium
        100 // contract size
    );
}

TransactionTicket RandomGenerator::generateBankAccountTransaction(int accountNumber){
    // Random Generates a random bank account transaction
    TransactionTicket transactionTicket; // initialize transaction ticket
    int transactionType = randomInteger(1,7);
    double transactionAmount = randomDouble(-50, 25000);

    switch(transactionType){
        // Balance
        case 1:
            return transactionTicket = TransactionTicket(
                TransactionType::Balance, // Balance
                accountNumber, // account Numbher
                0.0, // transaction amount
                Calendar(), // time not
                0
            );
        case 2:
            // Return Deposit transaction
            return transactionTicket = TransactionTicket(
                TransactionType::Deposit,  // deposit
                accountNumber, // account number
                transactionAmount, // transaction amount
                Calendar(), // time now
                randomInteger(6, 24) // no term
            );
        case 3:
            // Return Withdrawl Transaction
            return transactionTicket = TransactionTicket(
                TransactionType::Withdrawl, // withdrawl
                accountNumber, // account Number
                transactionAmount, // transaction amount
                Calendar(), // time now
                randomInteger(6, 24) // no new term
            );
        case 4:
            // Return Close Account
            return transactionTicket = TransactionTicket(
                TransactionType::Close, // transaction
                accountNumber, // account Number
                0.0, // transaction amount
                Calendar(), // time now
                0 // no new term
            );
        case 5:
            // Return Open Account
            return transactionTicket = TransactionTicket(
                TransactionType::Open, // transaction type
                accountNumber, // accountNumber
                0.0, // no amount
                Calendar(), // time now
                0 // no term
            );
        case 6:
            // Return transaction history
            return transactionTicket = TransactionTicket(
                TransactionType::TransactionHistory, // transaction type
                accountNumber, // account number
                0.0, // no amounty
                Calendar(), // time now
                0
            );
        case 7:
            // return Client Info
            return transactionTicket = TransactionTicket(
                TransactionType::ClientInfo, // transaction Type
                accountNumber, 
                0.0, // // no amount
                Calendar(),
                0
            );
        default:
            // return null ticket
            return TransactionTicket();
    }
}


void RandomGenerator::generateRandomPortfolio(
    // Random generator generate random portforlio. Generates a random
    // portfolio
    BrokerageAccount& brokerageAccount, // brokerage account
    int size // size
){
    for (int i = 0; i < size; i++){
        // Generate Random Investment
        brokerageAccount.addInvestment(generateRandomInvestment());
    }
}

Check RandomGenerator::generateCheckingTransaction(int accountNumber){
    // Random Generate Checking transaction function. Returns a check for 
    // a checking transaction
    Calendar today; // Get time now
    Check checkToClear = Check(
        accountNumber, // acount Number
        randomDouble(-10, 30000), // check amount
        Calendar(
            randomInteger(1, 12),
            randomInteger(1, 28),
            randomInteger(
                today.getYear() - 1,
                2026
            )
        )
    );
    return checkToClear; // return check to clear
}

CreditCard RandomGenerator::generateCreditAccountTransaction(int accountNumber){
    // Random Generator generate credit account transaction
    CardLevel cardLevel; // intialize card level
    int level = randomInteger(1, 3);

    // Determine cardlevel
    switch(level){
        case 1:
            // Random 1 
            cardLevel = CardLevel::BASIC; // set to basic
            break;
        case 2:
            // Random 2
            cardLevel = CardLevel::GOLD; // set to gold
            break;
        case 3:
            // random 3
            cardLevel = CardLevel::PLATINUM; // set platinum
            break;
    }

    CreditCard creditCard = CreditCard(
        accountNumber, // account Number
        Calendar(
            // Expiration Date
            randomInteger(1, 12),
            randomInteger(2024, 2030)
        ),
        cardLevel, // cardlevel
        randomDouble(-10.00, 5000)
    );
    // return credit card
    return creditCard;
}

CardLevel RandomGenerator::generateCardLevel(){
    // Random generator generate card level method. Generate
    // a random card level
    int level = randomInteger(1, 3);
    if (level == 1){
        // Return platnum if one
        return CardLevel::PLATINUM;
    }
    if (level == 2){
        // Return gold if 2
        return CardLevel::GOLD;
    }
    // Return basic
    return CardLevel::BASIC;
}


/* Unit Test Random Generator Class*/
static void testRandom(){
    RandomGenerator testRandomGenerator = RandomGenerator();
    double testRandomDouble = testRandomGenerator.randomDouble(
        // test random double
        5.0, // min 
        10.0 // max 
    );
    int testRandomInteger = testRandomGenerator.randomInteger(
        // Test Random Integer
        5, // min
        10 // max
    );
    // Assert
    ASSERT(testRandomDouble > 5.0 && testRandomDouble < 10.0);
    ASSERT(testRandomInteger > 5 && testRandomInteger < 10);
} 

static void testGenerateAccount(){
    // Unit test for test generate account
    Depositor testDepositor = Depositor(
        // Initialize test depositor
        Name(
            "Max", // first name
            "Mustermann" // last name
        ),
        "123456789" // social security number
    );
    // Initialize random generator
    RandomGenerator testRandomGenerator;
    unique_ptr<BankAccount> testRandomAccount = 
                testRandomGenerator.generateAccount(
                // generate test account
                    testDepositor
    );
    // ASSERT
    ASSERT(testRandomAccount->getDepositor()
                            .getDepositorName()
                            .printName() == "Max Mustermann");
    ASSERT(testRandomAccount->getDepositor().getDepositorSSN()
                            == "123456789");
    ASSERT(testRandomAccount->getAccountBalance() > 0.0);
    ASSERT(testRandomAccount->getAccountNumber() != nullptr);
    ASSERT(testRandomAccount->getAccountStatus() == true);
    ASSERT(testRandomAccount->getAccountType() != nullptr);
}

static void testGenerateRandomPortfolio(){
    // Unit test for generate random portfolio also tests
    // random investment
    RandomGenerator randomGenerator;
    auto brokerageAccount = make_unique<BrokerageAccount>(
        CommercialAccount()
    );
    // Generate random portfolio
    randomGenerator.generateRandomPortfolio(
        *brokerageAccount, 
        randomGenerator.randomInteger(3, 10)
    );
    // Assert
    ASSERT(brokerageAccount->getTotalShares() > 0);
    ASSERT(brokerageAccount->getTotalValue() > 0);
}

void testRandomGenerator(){
    // Unit test for random Generator
    TEST(testRandom);
    TEST(testGenerateAccount);
    TEST(testGenerateRandomPortfolio);
}