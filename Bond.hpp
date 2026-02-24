#pragma once

#include "Investment.hpp"

/*
    Bond class
    implements investment. contains a quantity, face value, 
    coupon rate, and maturity date
*/
class Bond : public Investment {
    public:
        // Bond constructor series
        Bond(); // no args constructor
        Bond(
            // Bond key word args constructor
            int quantity, // quantity
            double faceValue, // face value
            double couponRate, // coupon rate
            int yearsToMaturity // years to maturity
        );
        // Bond copy constructor
        Bond(const Bond& otherBond);

        /* Bond Invesment series */
        int getNumberOfShares() const override; // return total shares
        double getTotalValue() const override; // return total value
        double getAnnualYield() const; // return annual yield
        Calendar getMaturityDate() const; // return maturity date

        // Bond formatted 
        std::string print() const override; // print

    private:
        int quantity; // quantity
        double faceValue; // face value
        double couponRate; // coupon rate
        Calendar maturityDate; // maturityDate
};

// Unit test
void testBond();