#include <stdexcept>
#include <string>

class CheckTooOldException : public std::runtime_error{
    /*
        CheckTooOldException 
        get through if a check is too old to clear
    */
   public:
        // Check Too old Exception constructor
        CheckTooOldException(std::string checkDate)
            : runtime_error(
                // Write error
                checkDate + " was more than 6 months ago"
            ){}
};