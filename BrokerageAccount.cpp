#include "BrokerageAccount.hpp"
#include "RandomGenerator.hpp"

using namespace std;

/* Brokerage Account Constructor */
BrokerageAccount::BrokerageAccount():
    // Brokerage Account no args constructor
    CommercialAccount(CommercialAccount())
{
    // Set Account type
    accountType = AccountType::Brokerage;
}

BrokerageAccount::BrokerageAccount(
    // Brokerage account Key word args constructor
    CommercialAccount brokerageCommercialAccount
): CommercialAccount(brokerageCommercialAccount)
{
    // Set Account Type
    accountType = AccountType::Brokerage;
}

/* Brokerage account getter series */
void BrokerageAccount::addInvestment(
    unique_ptr<Investment> investment
) {
    // Brokerage account add investment. add an investment to the portfolio
    investmentPortfolio.emplace_back(std::move(investment));
}

double BrokerageAccount::getTotalValue() const {
    // Brokerage account get total value. Aggregates all the 
    // investment values
    double total = 0.0; // total counter
    for (const auto& inv : investmentPortfolio) {
        // loop through pointers and add total value
        total += inv->getTotalValue(); // add value
    }
    return total; // return total
}

int BrokerageAccount::getTotalShares() const {
    // Brokerage account get total shares. aggregates the total
    // number of shares
    int total = 0; // counter
    for (const auto& inv : investmentPortfolio) {
        // Loop through pointers and add shares
        total += inv->getNumberOfShares(); // add shares
    }
    return total; // return total shares
}


/* Brokerage account print Series */
string BrokerageAccount::printPortfolio() {
    // Brokerage account print account method. returns the
    // account string
    ostringstream portfolioString; // intialize string stream
    // Build string with boiler plate            
    portfolioString << left
                    << setw(21) << "\nClient Name"
                    << setw(12) << "SSN"
                    << setw(10) << "Acct Num"
                    << setw(15) << "Acct Type"
                    << setw(10) << "Status"
                    << right
                    << setw(12) << "Balance"
                    << setw(15) << "Balance Due"
                    << "\n"
                    << printAccount() 
                    << setw(15) 
                    << CommercialAccount::getCreditAccount().printAccountBalance()
                    << "\n\n\t\t" 
                    << string(20, '*') << " Investment Portfolio " 
                    << string(20, '*') << "\n"; 
    for (const auto& inv: investmentPortfolio){
        // loop through portfolio and print
        portfolioString << inv->print() << "\n";
    }
    portfolioString << string(100, '*')
                    << "\n\t\t\t\t\t\tTotal Value: " 
                    << printTotalValue() // print total value
                    << "\n\t\t\t\t\t\tTotal Number of Shares: "
                    << getTotalShares() << "\n" // print total shares
                    << string(100, '*') << "\n\n"
                    // Print transaction histor
                    << "\t\t\t\tTransaction History\n\n"
                    << setw(10) << "Date" 
                    << setw(20) << "Transaction"
                    << setw(15) << "Amount"
                    << setw(10) << "Status"
                    << setw(12) << "Balance"
                    << setw(25) << "Reason for Failure\n";
    for (TransactionReceipt receipt: transactionReceipts){
        // print receipt
        portfolioString << receipt.printReceipt();
    }
    return portfolioString.str(); // return string
}

string BrokerageAccount::printTotalValue() const {
    ostringstream totalValue;  // write string stream
    totalValue << "$" << fixed << setprecision(2) << getTotalValue();
    // convert to string
    string formattedBalance = totalValue.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }
    return formattedBalance; // return balance
}

/* Unit Testing Series */
static void testInvestment(){
    // Unit test for investment polymorphism
    unique_ptr<Investment> investment =
        make_unique<Stock>(
            "MSFT", // Microsoft
            5, // number of share
            200 // price per share
        );
    // ASSERT
    ASSERT(investment->getNumberOfShares() == 5);
    ASSERT_APPROX_EQUAL(
        investment->getTotalValue(), // total value
        1000.00, 
        0.001
    );
}

static void testBrokerageAccountTotals(){
    // Unit test for the aggregation of investsments
    BrokerageAccount testBrokerageAccount; // test account
    // ADD investments
    testBrokerageAccount.addInvestment(
        // Add apple share
        make_unique<Stock>(
            "APPL", // Apple
            10, // 10 shares
            150.00 // price per share
        )
    );
    testBrokerageAccount.addInvestment(
        // Add google share
        make_unique<Stock>(
            "GOOG", // google
            2, // 2 shares
            1000.00 // per share
        )
    );
    // ASSERT
    ASSERT(testBrokerageAccount.getTotalShares() == 12);
    ASSERT_APPROX_EQUAL(
        testBrokerageAccount.getTotalValue(),
        3500.00,
        0.001
    );
}

static void testMixedPortfolio(){
    // Unit test for portfolio with different investments
    BrokerageAccount testBrokerageAccount; // test account

    // Add test investments
    testBrokerageAccount.addInvestment(
        // Test stock
        make_unique<Stock>(
            // Test stock
            "AAPL", // apple
            10, // number of shares
            100.0 // price per share
        )
    );
    testBrokerageAccount.addInvestment(
        // Test bond
        make_unique<Bond>(
            1, // one bond
            1000.0, // face value
            0.05, // coupon
            3 // years to maturity
        )
    );
    // Assert
    ASSERT_APPROX_EQUAL(
        testBrokerageAccount.getTotalValue(),
        2000.0, // expected
        0.001 // tolerance
    );
}

void testBrokerageAccount(){
    // Unit test for brokerage account class
    TEST(testInvestment);
    TEST(testBrokerageAccountTotals);
    TEST(testMixedPortfolio);
}