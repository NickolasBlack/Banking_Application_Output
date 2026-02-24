#include <stdexcept>
#include <string>

class InvalidAccountException : public std::runtime_error {
    /*
        Invalid Account Error
        Gets thrown when the user attempts to perform 
        a transaction on the wrong account
    */
   public:
        // Invalid Account Exception Constructor
        InvalidAccountException(): std::runtime_error(
            // write error message
            "Invalid account for this transaction."
        ){}

        InvalidAccountException(std::string errorMessage): std::runtime_error(
            // Invalid Account Exception error message constructor
            errorMessage // print error message
        ){}
};