#include <stdexcept>
#include <string>

class CDMaturityDateException : public std::runtime_error {
    /*
        CD Maturity Date Exception
        get thrown whenever there is a transaction before the
        CD maturity date
    */
   public:
        // CD Maturity Date Exception Constructor
        CDMaturityDateException(std::string maturityDate)
            : std::runtime_error(
                // write error message
                "Maturity Date: " + maturityDate +
                " not reached yet."
        ){}
};