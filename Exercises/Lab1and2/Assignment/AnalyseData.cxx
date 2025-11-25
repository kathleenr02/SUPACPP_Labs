#include <iostream>
#include <vector>
#include <string>
#include "CustomFunctions.h"

int main(int argc, char* argv[])
{
    std::string filename = argv[1];

    std::vector<float> x_vals;
    std::vector<float> y_vals;

    readData(filename, x_vals, y_vals);

    while (true)
    {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Print N lines of data\n";
        std::cout << "2. Print magnitudes\n";
        std::cout << "3. Fit and print straight line\n";
        std::cout << "4. Compute x^y (y rounded)\n";
        std::cout << "5. Exit\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            int N;
            std::cout << "Enter N: ";
            std::cin >> N;
            printAnything(x_vals, y_vals, N);
        }

        else if (choice == 2) {
            std::vector<float> magnitudes;
            Magnitudes(x_vals, y_vals, magnitudes);
            printAnything(magnitudes);
            saveOutput("magnitudes_output.txt", magnitudes);
        }

        else if (choice == 3) {
            fitLine(x_vals, y_vals, "fit_output.txt");
        }

        else if (choice == 4) {
            std::vector<float> results;
            XY_noLoop(x_vals, y_vals, results);
            printAnything(results);
            saveOutput("xy_output.txt", results);
        }

        else if (choice == 5) {
            break;
        }

        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}