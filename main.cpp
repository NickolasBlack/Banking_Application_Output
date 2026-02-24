#include "Bank.hpp"
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    // Initialize clock
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now(); // start timer

    // Banking Application
    Bank bankingApplication(10);

    // Stop timer
    auto end = clock::now();   

    // Print time results
    auto elapsed = std::chrono::duration<double>(end - start);
    std::cout << "\nTotal execution time: "
              << elapsed.count()
              << " seconds\n";
}

