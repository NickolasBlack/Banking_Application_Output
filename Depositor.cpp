#include "Depositor.hpp"

using namespace std;

// Depositor Constructor series
Depositor::Depositor():
    // Depositor no args constructor
     depositorName(Name()), socialSecurityNumber(" "){}

Depositor::Depositor(
    // Depositor key word Args constructor
    const Name& depositorName, // depositor name
    string ssn // social security number
): depositorName(depositorName), socialSecurityNumber(ssn){}

Depositor::Depositor(const Depositor& otherDepositor):
    // Depositor copy constuctor
    depositorName(otherDepositor.depositorName), // copy depositor name
    socialSecurityNumber(otherDepositor.socialSecurityNumber){} // copy ssn

// Depositor getter series
Name Depositor::getDepositorName(){return Name(depositorName);} // return depositor name
string Depositor::getDepositorSSN(){return socialSecurityNumber;} // return ssn

// Depositor print function
string Depositor::printDepositor(){
    return "Client Name: " + depositorName.printName() + // Client Name:
            "\t\tSSN: " + socialSecurityNumber; // SSN:
}

/* Unit Testing Series */
static void testGetDepositorName(){
    // Get despoitor name unit test
    Name testName = Name("Nickolas", "Black");
    Depositor testDepositor = Depositor(testName, "123456789");
    ASSERT(testDepositor.getDepositorName() == "Nickolas Black");
}

static void testGetDepositorSSN(){
    // get depositor ssn unit test
    Depositor testDepositor = Depositor(
        Name(), // null name
        "123456789" // ssn
    );
    ASSERT(testDepositor.getDepositorSSN == "123456789");
}

static void testPrintDepositor(){
    // Print depositor unit test
    Depositor testDepositor = Depositor(
        Name("Nickolas", "Black"), // test name
        "123456789" // test ssn
    );
    ASSERT(testDepositor.printDepositor() == 
        "Client Name: Nickolas Black             SSN: 123456789"
    );
}

void testDepositor(){
    // Test Depositor unit test. Tests all functions
    TEST(testGetDepositorName); // test get name
    TEST(testGetDepositorSSN); // test get ssn
    TEST(testPrintDepositor); // test print depositor
}