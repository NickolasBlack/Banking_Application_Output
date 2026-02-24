#include <stdexcept>
#include <string>

class InvalidAmountException : public std::runtime_error {
    /*
        Invalid amount exception 
        gets thrown on transactions with an invalid amount
    */
   public:
        // Invalid amount exception constructor
        InvalidAmountException(std::string transactionAmount)
                : std::runtime_error(
                    transactionAmount + " is an invalid amount."
                ){}
};