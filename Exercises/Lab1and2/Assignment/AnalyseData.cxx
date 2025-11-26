#include <iostream>
#include <vector>
#include <string>
#include "CustomFunctions.h"


// Main function entry point for compiling
int main(int argc, char* argv[])
{
    std::string filename = argv[1]; // Read the first command line argument ie. the file
    std::vector<float> x_vals;
    std::vector<float> y_vals; // Vectors to store x and y vals

    // Call readData function
    readData(filename, x_vals, y_vals);

    // Start and infite loop until 5. Exit is selected by user
    while (true)
    {
        // Print menu to terminal after compiling
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Print N lines of data\n";
        std::cout << "2. Print magnitudes\n";
        std::cout << "3. Fit and print straight line\n";
        std::cout << "4. Compute x^y (y rounded)\n";
        std::cout << "5. Exit\n";

        // Reads user selection
        int choice;
        std::cin >> choice;

        // 1. Print N lines 
        if (choice == 1) {
            int N;
            std::cout << "Enter N: ";
            std::cin >> N;
            printAnything(x_vals, y_vals, N);
        }

        // 2. Compute, print and save magnitudes
        else if (choice == 2) {
            std::vector<float> magnitudes;
            Magnitudes(x_vals, y_vals, magnitudes);
            printAnything(magnitudes);
            saveOutput("magnitudes_output.txt", magnitudes);
        }

        // 3. Fit line, print and save function
        else if (choice == 3) {
            fitLine(x_vals, y_vals, "fit_output.txt");
        }

        // 4. Compute, print and save x^y for all pointa
        else if (choice == 4) {
            std::vector<float> results;
            XY_noLoop(x_vals, y_vals, results);
            printAnything(results);
            saveOutput("xy_output.txt", results);
        }

        // 5. Exit loop and end program
        else if (choice == 5) {
            break;
        }

        // Handle an invalid choice
        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0; // Ends the program too
}