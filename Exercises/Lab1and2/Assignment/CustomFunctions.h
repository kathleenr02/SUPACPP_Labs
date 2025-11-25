#include <vector>
#include <string>

void readData(const std::string& filename,
              std::vector<float>& x_vals,
              std::vector<float>& y_vals);

void Magnitudes(const std::vector<float>& x_vals,
                       const std::vector<float>& y_vals,
                       std::vector<float>& magnitudes);

void fitLine(const std::vector<float>& x_vals,
             const std::vector<float>& y_vals,
             const std::string& output_filename);

void ChiSquared(const std::vector<float>& x_vals,
                       const std::vector<float>& y_vals,
                       const std::vector<float>& y_err,
                       float m, float c,
                       float& chi2, float& chi2_ndof);

float XY_noLoop(float x, float y);
void XY_noLoop(const std::vector<float>& x_vals,
               const std::vector<float>& y_vals,
               std::vector<float>& results);

void saveOutput(const std::string& filename,
                const std::vector<float>& data);

void saveOutput(const std::string& filename,
                const std::string& text);

void printAnything(const std::vector<float>& x_vals,
                   const std::vector<float>& y_vals,
                   int N);

void printAnything(const std::vector<float>& magnitudes);

void printAnything(const std::string& fitted_line);
