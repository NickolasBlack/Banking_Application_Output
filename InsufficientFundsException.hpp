#include <stdexcept>
#include <string>

class InsufficientFundsException : public std::runtime_error{
    /*
        Insufficient fund exception 
        gets throw when there is a withdral from the account
        but not enough funds in the account
    */
   public: 
        InsufficientFundsException(std::string balance):
            std::runtime_error(
                "Insufficient funds. Account has a balance of " + balance 
            ) {}
};