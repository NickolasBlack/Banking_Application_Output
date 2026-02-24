#include "Stock.hpp"

using namespace std;

Stock::Stock(): 
    // Stock no args constructor
    tickerSymbol("#-"), shares(0), pricePerShare(0.0){}

Stock::Stock(
    // Stock key word args constructor
    string tickerSymbol, // ticket symbol
    int shares, // shares
    double pricePerShare // price per share
) : tickerSymbol(tickerSymbol), // set symbol
    shares(shares), // set shares
    pricePerShare(pricePerShare) // set price per share
{}

Stock::Stock(const Stock& otherStock):
    // Stock copy constructor
    tickerSymbol(otherStock.tickerSymbol), // copy ticker
    shares(otherStock.shares), // copy shares
    pricePerShare(otherStock.pricePerShare) // copy price per share
{}

/* Stock getter series */
int Stock::getNumberOfShares() const {
    // Get number of shares returns the number of shares
    return shares; // return shares
}

double Stock::getTotalValue() const {
    // Get Total value. returns the # of shares * price
    return shares * pricePerShare; // total value
}

string Stock::getTickerSymbol() const {
    // Get ticker symbol. return the ticker
    return tickerSymbol; // return symbol
}

string Stock::print() const{
    ostringstream stockString; // intalize string
    // Build String
    stockString << "Ticker: #" << tickerSymbol << "\n" // Ticker
                << "Shares: " << shares // shares
                << "\nPrice: " << printFormatedBalance(
                    pricePerShare
                ) // price per share
                << "\t\t\tTotal Value: " << printFormatedBalance(
                    // Formated balance
                    getTotalValue()
                ) << "\n"; // total value
    return stockString.str(); // return string
}

/* Unit Testing Series */
static void testStockInvestment(){
    // unit test for stock class
    Stock testStock(
        // test stock
        "AAPL", // ticker
        10, // number of shares
        100.0 // price per share
    );
    // ASSERT
    ASSERT(testStock.getTickerSymbol() == "AAPL");
    ASSERT(testStock.getNumberOfShares() == 10);
    ASSERT_APPROX_EQUAL(
        testStock.getTotalValue(), // 10 * 1000
        1000.0, // 100
        0.001
    );
}

void testStock(){
    // Unit test for stock class
    TEST(testStockInvestment);
}
