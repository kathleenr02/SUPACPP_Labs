#include "CustomFunctions.h"
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>


// ---------------------------------------------------------------------------------
// Read (x, y) values from a file
void readData(const std::string& filename, 
              std::vector<float>& x_vals,
              std::vector<float>& y_vals) // Vectors to store the x and y positions
{
    std::ifstream data_file(filename);
    std::string line; // Stores each new line

    std::getline(data_file, line); // Skip header when reading

    // Reads one line from thefile into the string
    while (std::getline(data_file, line))
    {
        int comma_pos = line.find(',');

        float x = std::stof(line.substr(0, comma_pos)); // x vals before comma
        float y = std::stof(line.substr(comma_pos + 1)); // y vals after comma

        // Stores values in two seperate vectors
        x_vals.push_back(x);
        y_vals.push_back(y);
    }
}

// ---------------------------------------------------------------------------------
// Calculate magnitudes
void Magnitudes(const std::vector<float>& x_vals,
                const std::vector<float>& y_vals,
                std::vector<float>& magnitudes) // Output vector for magnitudes
{
    // Loops over the number of (x, y) points
    for (size_t i = 0; i < x_vals.size(); i++) {
        float mag = std::sqrt(x_vals[i] * x_vals[i] +
                              y_vals[i] * y_vals[i]); // Magnitude equation

        // Stores magnitudes in vector
        magnitudes.push_back(mag);
    }
}

// ---------------------------------------------------------------------------------
// Fit straight line 
void fitLine(const std::vector<float>& x_vals,
             const std::vector<float>& y_vals,
             const std::string& output_filename) // Outputs fit function as string and a file
{
    // Stores the number of data points
    int n = x_vals.size();

    // Initialises sums for least squares
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    // Loops through each data point and adds them to their sums
    for (int i = 0; i < n; i++) {
        sum_x  += x_vals[i];
        sum_y  += y_vals[i];
        sum_xy += x_vals[i] * y_vals[i];
        sum_x2 += x_vals[i] * x_vals[i];
    }

    // Computes slope m and intercept c
    float m = (n * sum_xy - sum_x * sum_y) /
              (n * sum_x2 - sum_x * sum_x);

    float c = (sum_y - m * sum_x) / n;


    // Read the error file using the readData() function
    std::vector<float> err_x;
    std::vector<float> y_err;

    readData("error2D_float.txt", err_x, y_err);

    // Compute chi squared and chi sqaured/NDOF
    float chi2, chi2_ndof;
    ChiSquared(x_vals, y_vals, y_err, m, c, chi2, chi2_ndof);

    // Create the output string
    std::string result =
        "y = " + std::to_string(m) + "x + " + std::to_string(c) +
        "\nchi2 = " + std::to_string(chi2) +
        "\nchi2/NDOF = " + std::to_string(chi2_ndof);

    // Save to output file
    std::ofstream outfile(output_filename);
    outfile << result << std::endl;
    outfile.close();

    // Print to terminal
    printAnything(result);
}

// ---------------------------------------------------------------------------------
// Compute chi-squared
void ChiSquared(const std::vector<float>& x_vals,
                const std::vector<float>& y_vals, // Input data points
                const std::vector<float>& y_err, // Input y error 
                float m, float c, // Input fit parameters
                float& chi2, float& chi2_ndof) // Outputs passed by refernce
{
    // Initialise chi squared
    chi2 = 0.0f;

    // Retrieve number of data points
    int n = x_vals.size();
    int dof = n - 2; // Degrees of freedom = 2 from m and c

    // Loop over all data points
    for (int i = 0; i < n; i++)
    {
        float y_fit = m * x_vals[i] + c;
        float diff = y_vals[i] - y_fit;

        chi2 += (diff * diff) / (y_err[i] * y_err[i]); // Chi squared equation
    }

    chi2_ndof = chi2 / dof; // Chi sqaured/number of degrees of freedom equation
}

// ---------------------------------------------------------------------------------
// Printing overloads

// Print N (x, y) points
void printAnything(const std::vector<float>& x_vals,
                   const std::vector<float>& y_vals,
                   int N)
{
    // Check for N > number of lines in x or y
    if ((size_t)N > x_vals.size()) {
        std::cout << "N too large, printing first 5 lines.\n";
        N = 5; // Forces 5 lines to print instead
    }

    // Prints N lines 
    for (int i = 0; i < N; i++) {
        std::cout << x_vals[i] << ", " << y_vals[i] << std::endl;
    }
}

// Print vector of magnitudes
void printAnything(const std::vector<float>& magnitudes)
{
    std::cout << "Magnitudes:\n";
    for (float m : magnitudes) {
        std::cout << m << std::endl;
    }
}

// Print a string of function and chi squared
void printAnything(const std::string& fitted_line)
{
    std::cout << fitted_line << std::endl;
}

// ---------------------------------------------------------------------------------
// Compute x^y

// Calculates x^y for single value points with y rounded
float XY_noLoop(float x, float y)
{
    int y_int = std::round(y); // Round y
    return std::exp(y_int * std::log(x)); // Compute x^y using exp/log
}

// Calculates x^y for all vector pairs
void XY_noLoop(const std::vector<float>& x_vals,
               const std::vector<float>& y_vals,
               std::vector<float>& results)
{
    // Loops over all (x, y) pairs
    for (size_t i = 0; i < x_vals.size(); i++)
        results.push_back(XY_noLoop(x_vals[i], y_vals[i])); // Calls the single value function
}

// ---------------------------------------------------------------------------------
// Saving overloads

// Save vector of floats
void saveOutput(const std::string& filename,
                const std::vector<float>& data)
{
    std::ofstream f(filename);
    for (float v : data) f << v << "\n"; // Used for magnitudes and x^y
    f.close();
}

// Save a string
void saveOutput(const std::string& filename,
                const std::string& text)
{
    std::ofstream f(filename); // Used for anything text based
    f << text;
    f.close();
}