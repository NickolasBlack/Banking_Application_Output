#pragma once

#include "Stdafx.hpp"
#include "CommercialAccount.hpp"
#include "Investment.hpp"
#include "Stock.hpp"
#include "Bond.hpp"
#include "Option.hpp"

/*
    Brokerage Account Class
    extends Commercial account. also contains a portfolio vector of
    stock, bonds, and options investment interface objects
*/
class BrokerageAccount: public CommercialAccount{
    public:
        // Brokerage account constructor series
        BrokerageAccount(); 
        BrokerageAccount(
            // Brokerage Key word args constructor
            CommercialAccount brokerageCommercialAccount
        );
        // Deep clone
        BrokerageAccount(
            const BrokerageAccount&
        ) = delete; 
       

        // Brokerage Helper functions
        void addInvestment(std::unique_ptr<Investment> investment);

        /* Brokerage account transaction series */
        double getTotalValue() const; // returns total value
        int getTotalShares() const; // return total shares

        // Print Account
        std::string printPortfolio(); // returns account string
        std::string printTotalValue() const; // returns formatted value
    private:
        std::vector<std::unique_ptr<Investment>> investmentPortfolio; // portfolio
};

// Unit Test
void testBrokerageAccount();