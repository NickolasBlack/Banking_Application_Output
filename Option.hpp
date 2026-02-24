#pragma once

#include "Investment.hpp"

/*
    Option Type enum
    options can be either put of call in this app
*/
enum class OptionType {
    Call, // Call Option
    Put // Put option
};

/*
    Option Class 
    extends investment. contains a type enum, 
    dumber of contracts, premium, and contract Size
*/
class Option: public Investment {
    public:
        // Option Class Constructor Series 
        Option(); // no args constructor
        Option(
            OptionType optionType, // option type
            int contracts, // contracts
            double premium, // premium
            int contractSize // contract size
        );
        // Copy constructor
        Option(const Option& otherOption);

        // Option required methods
        int getNumberOfShares() const override; 
        double getTotalValue() const override;
        OptionType getOptionType() const;

        // Option Print method
        std::string print() const override;

    private:
        OptionType optionType; // option type
        int contract; // number of contact
        double premium; // cost
        int contractSize; // contact size
};

// Unit test
void testOption();