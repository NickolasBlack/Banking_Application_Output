#include "Investment.hpp"

using namespace std;

string Investment::printFormatedBalance(double amount) const {
    // Print total value method. returns a formatted string of the total 
    // value
    ostringstream value;  // write string stream
    value << "$" << fixed << setprecision(2) << amount;
    // convert to string
    string formattedBalance = value.str();

    // Insert commas manually
    int dot = formattedBalance.find('.');
    for (int i = dot - 3; i > 1; i -= 3){
        formattedBalance.insert(i, ",");
    }
    return formattedBalance; // return balance
}