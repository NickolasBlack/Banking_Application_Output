#include <stdexcept>

class AccountClosedException : public std::runtime_error {
    /*
        Account Closed Exception class
        Gets thrown when an account that is closed get closed 
        again
    */
   public:
        // AccountClosedException constructor
        AccountClosedException(): std::runtime_error(
            "Account is already closed."
        ){}
};