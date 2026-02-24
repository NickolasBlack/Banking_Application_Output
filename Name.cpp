#include "Name.hpp"

using namespace std;

// Name No Args constructor
Name::Name() : firstName(" "), lastName (" "){}
// Name Keyword args constructor
Name::Name(string firstName, string lastName) :
    firstName(firstName), lastName(lastName) {}
// Name copy constructor
Name::Name(const Name& otherName) :
    firstName(otherName.firstName), lastName(otherName.lastName) {}

// Name getter functions
string Name::getFirstName(){return firstName;} // return first name
string Name::getLastName(){return lastName;} // return last name

// Name print function
string Name::printName(){
    // return {firstName} {lastName}
    return firstName + " " + lastName;
}

// Unit Testing Series
static void testGetFirstName(){
    // Get first name unit test
    Name testFirstName = Name("Nickolas", "Black");
    ASSERT(testFirstName.getFirstName() == "Nickolas");
}

static void testGetLastName(){
    // Get last name unit test
    Name testLastName = Name("Nickolas", "Black");
    ASSERT(testLastName.getLastName() == "Black");
}

static void testPrintName(){
    // Print Name unit test
    Name testName = Name("Nickolas", "Black");
    ASSERT(testName.printName() == "Nickolas Black");
}

void testName() {
    TEST(testGetFirstName); // Test get first Name
    TEST(testGetLastName); // test get last name
    TEST(testPrintName); // test print name
}