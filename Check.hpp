#pragma once

#include "Stdafx.hpp"

/*
    Check class
    contains an account number, check amount, and date of
    check
*/
class Check{
    public:
        // Check class constructor series
        Check(); // no args constructor
        Check(
            int accountNumber, // account number
            double checkAmount, // check amount
            Calendar dateOfCheck // date of check
        );
        Check(const Check& otherCheck);

        // Check Getter series
        int getAccountNumber(); // return account number
        double getCheckAmount(); // returns check amount
        Calendar getDateOfCheck(); // returns date of check

    private:
        int accountNumber; // account number
        double checkAmount; // check amount
        Calendar dateOfCheck; // date of check
};

// unit testing 
void testCheck();