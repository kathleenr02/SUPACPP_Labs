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

    std::cout << "Choose an option:\n";
    std::cout << "1. Print N lines of data\n";
    std::cout << "2. Print magnitudes\n";
    std::cout << "3. Fit straight line\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        int N;
        std::cout << "Enter N: ";
        std::cin >> N;
        printData(x_vals, y_vals, N);
    }
    else if (choice == 2) {
        std::vector<float> magnitudes;
        computeMagnitudes(x_vals, y_vals, magnitudes);

        for (size_t i = 0; i < magnitudes.size(); i++) {
            std::cout << magnitudes[i] << std::endl;
        }
    }
    else if (choice == 3) {
        // Call your new line-fitting function
        fitLine(x_vals, y_vals, "fit_output.txt");
    }

    return 0;
}
