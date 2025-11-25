#include "CustomFunctions.h"
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>

// -------------------------------------------------------------
// Read (x, y) values from a file
// -------------------------------------------------------------
void readData(const std::string& filename,
              std::vector<float>& x_vals,
              std::vector<float>& y_vals)
{
    std::ifstream data_file(filename);
    std::string line;

    std::getline(data_file, line); // skip header

    while (std::getline(data_file, line))
    {
        int comma_pos = line.find(',');

        float x = std::stof(line.substr(0, comma_pos));
        float y = std::stof(line.substr(comma_pos + 1));

        x_vals.push_back(x);
        y_vals.push_back(y);
    }
}

// -------------------------------------------------------------
// Compute magnitudes
// -------------------------------------------------------------
void Magnitudes(const std::vector<float>& x_vals,
                const std::vector<float>& y_vals,
                std::vector<float>& magnitudes)
{
    for (size_t i = 0; i < x_vals.size(); i++) {
        float mag = std::sqrt(x_vals[i] * x_vals[i] +
                              y_vals[i] * y_vals[i]);
        magnitudes.push_back(mag);
    }
}

// -------------------------------------------------------------
// Fit straight line y = mx + c
// -------------------------------------------------------------
void fitLine(const std::vector<float>& x_vals,
             const std::vector<float>& y_vals,
             const std::string& output_filename)
{
    int n = x_vals.size();

    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x  += x_vals[i];
        sum_y  += y_vals[i];
        sum_xy += x_vals[i] * y_vals[i];
        sum_x2 += x_vals[i] * x_vals[i];
    }

    float m = (n * sum_xy - sum_x * sum_y) /
              (n * sum_x2 - sum_x * sum_x);

    float c = (sum_y - m * sum_x) / n;

    // ---------------------------------------------------------
    // Read the error file using readData()
    // ---------------------------------------------------------
    std::vector<float> err_x;   // ignored
    std::vector<float> y_err;   // we use only this

    readData("error2D_float.txt", y_err, err_x);

    if (y_err.size() != y_vals.size()) {
        std::cout << "Error file size mismatch\n";
        return;
    }

    // Compute chi^2 and chi^2/NDOF
    float chi2, chi2_ndof;
    ChiSquared(x_vals, y_vals, y_err, m, c, chi2, chi2_ndof);

    // Build output string
    std::string result =
        "y = " + std::to_string(m) + "x + " + std::to_string(c) +
        "\nchi2 = " + std::to_string(chi2) +
        "\nchi2/NDOF = " + std::to_string(chi2_ndof);

    // Save to file
    std::ofstream outfile(output_filename);
    outfile << result << std::endl;
    outfile.close();

    // Print to terminal
    printAnything(result);
}

// -------------------------------------------------------------
// Compute chi-squared
// -------------------------------------------------------------
void ChiSquared(const std::vector<float>& x_vals,
                const std::vector<float>& y_vals,
                const std::vector<float>& y_err,
                float m, float c,
                float& chi2, float& chi2_ndof)
{
    chi2 = 0.0f;

    int n = x_vals.size();
    int dof = n - 2; // m and c are fit parameters

    for (int i = 0; i < n; i++)
    {
        float y_fit = m * x_vals[i] + c;
        float diff = y_vals[i] - y_fit;

        chi2 += (diff * diff) / (y_err[i] * y_err[i]);
    }

    chi2_ndof = chi2 / dof;
}

// -------------------------------------------------------------
// Printing overloads
// -------------------------------------------------------------
void printAnything(const std::vector<float>& x_vals,
                   const std::vector<float>& y_vals,
                   int N)
{
    if ((size_t)N > x_vals.size()) {
        std::cout << "N too large, printing first 5 lines.\n";
        N = 5;
    }

    for (int i = 0; i < N; i++) {
        std::cout << x_vals[i] << ", " << y_vals[i] << std::endl;
    }
}

void printAnything(const std::vector<float>& magnitudes)
{
    for (float m : magnitudes) {
        std::cout << m << std::endl;
    }
}

void printAnything(const std::string& fitted_line)
{
    std::cout << fitted_line << std::endl;
}



float XY_noLoop(float x, float y)
{
    int y_int = std::round(y);
    return std::exp(y_int * std::log(x));
}

void XY_noLoop(const std::vector<float>& x_vals,
               const std::vector<float>& y_vals,
               std::vector<float>& results)
{
    for (size_t i = 0; i < x_vals.size(); i++)
        results.push_back(XY_noLoop(x_vals[i], y_vals[i]));
}

void saveOutput(const std::string& filename,
                const std::vector<float>& data)
{
    std::ofstream f(filename);
    for (float v : data) f << v << "\n";
    f.close();
}

void saveOutput(const std::string& filename,
                const std::string& text)
{
    std::ofstream f(filename);
    f << text;
    f.close();
}