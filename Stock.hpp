#pragma once 

#include "Investment.hpp"

/*
    Stock Class 
    extends investment contains a ticker smbol, shares,
     and price per share
*/
class Stock : public Investment {
    public:
        // Stock constructor series
        Stock(); // no args constructor
        Stock(
            // Stock key work args constructor
            std::string ticketSymbol, // ticket
            int shares, // shares
            double pricePerShare // price per share
        );
        Stock(const Stock& otherStock);

        // Stock Investment getter series
        int getNumberOfShares() const override; // number of shares
        double getTotalValue() const override; // total value
        std::string getTickerSymbol() const; // ticker

        /* Printer series */
        virtual std::string print() const override; 

    private:
        std::string tickerSymbol; // ticker symbol
        int shares; // shares
        double pricePerShare; // price pershare
};

// Unit test
void testStock();