#include "Option.hpp"

using namespace std;

/* Option class constructor series */
Option::Option():
    // Option no args constructor
    optionType(OptionType::Call), // call
    contract(0),// contracts
    premium(0.0), // premium
    contractSize(0)  // contract size
{}

Option::Option(
    // Option Key word args contructor
    OptionType optionType, // option type
    int contracts, // contracts
    double premium, // premium
    int contractSize // size
): optionType(optionType),
   contract(contracts),
   premium(premium), // premium
   contractSize(contractSize)
{}

Option::Option(const Option& otherOption):
    // Option Copy constructor
    optionType(otherOption.optionType), // copy type
    contract(otherOption.contract), // copy contract
    premium(otherOption.premium), // copy premium
    contractSize(otherOption.contractSize) // copy size
{}

// Option class investment functions
int Option::getNumberOfShares() const {
    // Option get number of shares method. returns the number of 
    // shares
    return contract * contractSize; // num of shares
}

double Option::getTotalValue() const {
    // Option class get total value method. returns the total
    // value of the contract
    return contract * premium * contractSize; 
}

OptionType Option::getOptionType() const{
    // Option class get option type method. returns the option type
    return optionType; // return type
}

// Option formatted 
string Option::print() const{
    // Option class print method. Prints the option
    stringstream optionString; // intalize string
    // Build String
    optionString << "Option: " 
                << (optionType == OptionType::Call ? "Call" : "Put")
                << "\nContracts: " << contract // contract
                << "\nPremium: " << printFormatedBalance(
                    premium // price per share
                ) << "\t\tTotal Value: " << printFormatedBalance(
                    getTotalValue()
                ) << "\n"; // total value
    return optionString.str(); // return string
}

/* Unit Testing Series */
static void testOptionInvestment(){
    // Unit test for option creation
    Option testOption = Option(
        OptionType::Call, 
        1, // contracts
        100.00, // premium
        10 // size
    );
    // Assert 
    ASSERT(testOption.getOptionType() == "Call");
    ASSERT_APPROX_EQUAL(
        // test number of shares
        testOption.getNumberOfShares(),
        1 * 10, 
        0.001
    );
    ASSERT_APPROX_EQUAL(
        // Test total value
        testOption.getTotalValue(),
        1 * 100 * 10, 
        0.001
    );
}

void testOption(){
    // Unit test for the option class
    TEST(testOptionInvestment);
}