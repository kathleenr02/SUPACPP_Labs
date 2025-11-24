#include <vector>
#include <string>

void readData(const std::string& filename,
              std::vector<float>& x_vals,
              std::vector<float>& y_vals);

void printData(const std::vector<float>& x_vals,
               const std::vector<float>& y_vals,
               int N);

void computeMagnitudes(const std::vector<float>& x_vals,
                       const std::vector<float>& y_vals,
                       std::vector<float>& magnitudes);

void fitLine(const std::vector<float>& x_vals,
             const std::vector<float>& y_vals,
             const std::string& output_filename);

