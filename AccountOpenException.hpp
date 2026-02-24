#include <stdexcept>

/*
    Account Open Exception
    Gets throwmn when an account that is already open is
    re-Opened
*/
class AccountOpenException: public std::runtime_error{
    public:
        // Account open Exception constructor
        AccountOpenException(): std::runtime_error(
            "Account already open."
        ){}
};