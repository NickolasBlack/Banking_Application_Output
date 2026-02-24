#include "Check.hpp"

using namespace std; 

// Check class constructor series
Check::Check(): // no args constructor
    accountNumber(000000), // account number
    checkAmount(0.0), // check amount
    dateOfCheck(Calendar()){} // time now

Check::Check(
    // Check Key word args constructor
    int accountNumber, // acountNumber
    double checkAmount, // check amount
    Calendar dateOfCheck // date of check
): accountNumber(accountNumber), // Set number
   checkAmount(checkAmount), // set amount
   dateOfCheck(dateOfCheck){} // set dat of check

Check::Check(
    // Check class copy constructor
    const Check& otherCheck // other check to copy
): accountNumber(otherCheck.accountNumber), // copy number
   checkAmount(otherCheck.checkAmount), // copy amount
   dateOfCheck(otherCheck.dateOfCheck){} // copy date

/* Check Class getter series */
int Check::getAccountNumber(){return accountNumber;} // return number
double Check::getCheckAmount(){return checkAmount;} // return amount
Calendar Check::getDateOfCheck(){return dateOfCheck;} // return date

/* Unit Testing Series*/
static void testchk(){
    // Unit Test for check creation
    Check testCheck = Check(
        // Initialize test check
        123456, // account number
        100.0, // check amount
        Calendar(01,04,2025) // calendar object
    );
    // Assert
    ASSERT(getAccountNumber() == 123456); 
    ASSERT(getCheckAmount() == 100.0);
    ASSERT(getDateOfCheck().getMonth() == 01);
    ASSERT(getDateOfCheck().getDay() == 04);
    ASSERT(getDateOfCheck().getYear() == 2025);
}

void testCheck(){
    // Unit test for check class
    TEST(testchk);
}