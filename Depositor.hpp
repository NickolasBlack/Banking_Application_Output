#pragma once

#include "Stdafx.hpp"
#include "Name.hpp"

class Depositor{
    /*
        Depositor class
        contains the Name of a depositor and their ssn,
    */
    public:
        // Despositor no Args constructor
        Depositor();
        // Depositor keyword args constructor
        Depositor(const Name& depositorName, std::string ssn);
        // Depositor copy constructor
        Depositor(const Depositor& otherDepositor);

        // Depositor getter series
        Name getDepositorName(); // returns depositor name
        std::string getDepositorSSN(); // returns depositor ssn

        // Print depositor
        std::string printDepositor(); // returns {name} \t\t {ssn}
    private:
        Name depositorName; // Depositor Name
        std::string socialSecurityNumber; // ssn
};

// Unit testing
void testDepositor();