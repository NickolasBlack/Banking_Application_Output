#include "Bond.hpp"

using namespace std;

/* Bond Class constructor series */
Bond::Bond(): 
    // Bond class no args constructor
    quantity(0),
    faceValue(0.0),
    couponRate(0.0),
    maturityDate(Calendar())
{} 

Bond::Bond(
    // Bond class keyword args constructor
    int quantity, // quantity
    double faceValue, // face value
    double couponRate, // coupon rate
    int yearsToMaturity // years to maturity
): quantity(quantity), // set quantity
   faceValue(faceValue), // set face value
   couponRate(couponRate) { // set coupon rate
    // Compute maturity date
    Calendar today = Calendar(); // get todday date
    maturityDate = Calendar(
        today.getMonth(), // present month
        today.getDay(), // present day
        today.getYear() + yearsToMaturity // future yeat
    );
}

Bond::Bond(const Bond& otherBond):
    // Bond class copy constructor
    quantity(otherBond.quantity), // copy quantity
    faceValue(otherBond.faceValue), // copy faceValue
    couponRate(otherBond.couponRate), // copy coupon rate
    maturityDate(otherBond.maturityDate) // copy maturity date
{}

/* Bond Investment Series */
int Bond::getNumberOfShares()const {
    // Bond class get number of shares. returns total number
    // of bonds
    return quantity; // return quantity
}

double Bond::getTotalValue() const {
    // Bond class get total value. Return the total value
    return quantity * faceValue; // return total value
}

double Bond::getAnnualYield() const {
    // Bond class get annual yeild. return the annual yield
    return quantity * faceValue * couponRate; // annual yield
}

Calendar Bond::getMaturityDate() const {
    // Bond get maturity date. returns the maturity date
    return maturityDate; // return maturity date
}

/* Bond class formatter */
string Bond::print() const {
    // Bond print function. return a formatted string
    stringstream bondString; // intalize string
    // Build String 
    bondString << "Bond\n" 
                << "Quantity: " << quantity
                << "\nFace Value: " 
                << printFormatedBalance(faceValue)
                << "\nCoupon: "
                << (couponRate * 100) << "%"
                << "\nMaturity Date: " << getMaturityDate().printDate()
                << "\tTotal Value: " << printFormatedBalance(
                    getTotalValue()
                ) << "\n"; // total value
    return bondString.str(); // return string
}

/* Bond Unit Test */
static void testBondInvestment(){
    // Unit test for bond creation
    Bond testBond = Bond(
        1, // quantity
        100, // face value
        .09, // coupon rate
        2 // 2028
    );
    ASSERT(testBond.getMaturityDate().getYear() == 2028);
    ASSERT(testBond.getNumberOfShares() == 1);
    ASSERT_APPROX_EQUAL(
        testBond.getAnnualYield(),
        9, 
        0.001
    );
    ASSERT_APPROX_EQUAL(
        testBond.getTotalValue(),
        100,
        0.001
    );
}

void testBond(){
    // test bond class unit test
    TEST(testBondInvestment);
}

