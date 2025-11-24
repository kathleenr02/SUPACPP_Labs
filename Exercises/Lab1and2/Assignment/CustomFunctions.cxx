#include "CustomFunctions.h"
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>


// Function to read x and y values from the file
void readData(const std::string& filename,
              std::vector<float>& x_vals,
              std::vector<float>& y_vals)
{
    std::ifstream data_file(filename);
    std::string line;

    std::getline(data_file, line); 

    while (std::getline(data_file, line))
    {
        int comma_pos = line.find(',');

        std::string x_str = line.substr(0, comma_pos);
        std::string y_str = line.substr(comma_pos + 1);

        float x = std::stof(x_str);
        float y = std::stof(y_str);

        x_vals.push_back(x);
        y_vals.push_back(y);
    }

    data_file.close();
}


// Function to print N rows of x and y values
void printData(const std::vector<float>& x_vals,
               const std::vector<float>& y_vals,
               int N)
{
    if (static_cast<size_t>(N) > x_vals.size()) {
        std::cout << "N is too large, printing first 5 lines instead.\n";
        N = 5;
    }

    for (int i = 0; i < N; i++) {
        std::cout << x_vals[i] << ", " << y_vals[i] << std::endl;
    }
}


// Function to compute magnitudes of all (x, y) points
void computeMagnitudes(const std::vector<float>& x_vals,
                       const std::vector<float>& y_vals,
                       std::vector<float>& magnitudes)
{
    for (size_t i = 0; i < x_vals.size(); i++) {
        float mag = std::sqrt(x_vals[i]*x_vals[i] + y_vals[i]*y_vals[i]);
        magnitudes.push_back(mag);
    }
}


// Function to fit a straight line y = mx + c using least squares
void fitLine(const std::vector<float>& x_vals,
             const std::vector<float>& y_vals,
             const std::string& output_filename)
{
    int n = x_vals.size();

    // Compute sums needed for least squares
    float sum_x = 0;
    float sum_y = 0;
    float sum_xy = 0;
    float sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x  += x_vals[i];
        sum_y  += y_vals[i];
        sum_xy += x_vals[i] * y_vals[i];
        sum_x2 += x_vals[i] * x_vals[i];
    }

    // Compute m and c
    float m = (n * sum_xy - sum_x * sum_y) /
              (n * sum_x2 - sum_x * sum_x);

    float c = (sum_y - m * sum_x) / n;

    // Create output string
    std::string result = "y = " + std::to_string(m)
                       + "x + " + std::to_string(c);

    std::cout << "Fitted line: " << result << std::endl;

    // Save to new file
    std::ofstream outfile(output_filename);
    outfile << result << std::endl;
    outfile.close();
}
