#include <vector>
#include <string>


// ---------------------------------------------------------------------------------
// Read (x, y) values from a file
void readData(const std::string& filename,
              std::vector<float>& x_vals,
              std::vector<float>& y_vals);

// ---------------------------------------------------------------------------------
// Calculate magnitudes
void Magnitudes(const std::vector<float>& x_vals,
                       const std::vector<float>& y_vals,
                       std::vector<float>& magnitudes);

// ---------------------------------------------------------------------------------
// Fit straight line 
void fitLine(const std::vector<float>& x_vals,
             const std::vector<float>& y_vals,
             const std::string& output_filename);

// ---------------------------------------------------------------------------------
// Compute chi-squared
void ChiSquared(const std::vector<float>& x_vals,
                       const std::vector<float>& y_vals,
                       const std::vector<float>& y_err,
                       float m, float c,
                       float& chi2, float& chi2_ndof);

// ---------------------------------------------------------------------------------
// Printing overloads
void printAnything(const std::vector<float>& x_vals,
                   const std::vector<float>& y_vals,
                   int N);
void printAnything(const std::vector<float>& magnitudes);
void printAnything(const std::string& fitted_line);

// ---------------------------------------------------------------------------------
// Compute x^y
float XY_noLoop(float x, float y);
void XY_noLoop(const std::vector<float>& x_vals,
               const std::vector<float>& y_vals,
               std::vector<float>& results);

// ---------------------------------------------------------------------------------
// Saving overloads
void saveOutput(const std::string& filename,
                const std::vector<float>& data);
void saveOutput(const std::string& filename,
                const std::string& text);

