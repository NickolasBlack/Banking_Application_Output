#include <stdexcept>

/*
    Card Expired Exception
    Gets thrown when a credit card expires
*/
class CardExpiredException: public std::runtime_error{
    public:
    // CardExpired Exception constructor
    CardExpiredException(): std::runtime_error{
        // Write error message
        "Card Expired"
    }{}
};