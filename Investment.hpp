#pragma once

#include "Stdafx.hpp"

/*
    Investment Interface
    describes the behavior of investment objects 
    has a number of shares and total value
*/
class Investment {
    public:
        // Investment Class destructor
        virtual ~Investment() = default;

        // Returns the number of shares
        virtual int getNumberOfShares() const = 0;
        // returns the total value 
        virtual double getTotalValue() const = 0;

        // Formatted print
        virtual std::string print() const = 0;

        /* Stock formatter series */
        std:: string printFormatedBalance(double amount) const;
};