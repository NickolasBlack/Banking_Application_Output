#pragma once

#include "Stdafx.hpp"

class Name{
    /*
        Name Class
        Contains the first and last name of a depositor
    */
   public:
        // No args constructor
        Name();
        // Keyword Args constructor
        Name(std::string firstName, std::string lastName);
        // Copy constructor
        Name(const Name& otherName);

        // Name Getter functions
        std::string getFirstName(); // returns first name
        std::string getLastName(); // returns last name

        // Name Print
        std::string printName(); // returns {firstName} {lastName}
   private:
        std::string firstName; // first name
        std::string lastName; // last name
};

// Unit Testing
void testName();