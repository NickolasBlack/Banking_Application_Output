#include <stdexcept>

/*
    Spending Limit exception
    gets thrown when a credit card limit is reached
*/
class SpendingLimitException: public std::runtime_error {
    public:
        // Spending limit exception constructor
        SpendingLimitException(std::string limitLevel): std::runtime_error(
            // Write error message
            "Over spending limit reached for card level: " + limitLevel
        ){}
};