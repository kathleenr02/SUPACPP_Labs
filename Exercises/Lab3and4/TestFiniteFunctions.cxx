#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

// This program will:
// 1) Read mystery data from the text file
// 2) Plot the all defined functions
// 3) Plot the chosen data on the same axes

int main(int argc, char* argv[]) {

  srand(time(NULL)); // random seed for non-reproducable runs

  // Check command line arguments
  if (argc < 2) {
    std::cout << "Usage: ./TestFiniteFunctions <MysteryDataFile.txt>" << std::endl;
    return 1;
  }

  std::string dataFile = argv[1];


  // Read data points into a vector
  std::ifstream infile(dataFile.c_str());
  if (!infile.is_open()) {
    std::cout << "Error: could not open data file " << dataFile << std::endl;
    return 1;
  }

  std::vector<double> dataPoints;
  double value;

  while (infile >> value) {
    dataPoints.push_back(value);
  }

  infile.close();

  if (dataPoints.size() == 0) {
    std::cout << "Error: no data points read from file " << dataFile << std::endl;
    return 1;
  }


  // Work out sensible plotting range from the data
  double xmin = dataPoints[0];
  double xmax = dataPoints[0];

  for (int i = 1; i < static_cast<int>(dataPoints.size()); ++i) {
    if (dataPoints[i] < xmin) xmin = dataPoints[i];
    if (dataPoints[i] > xmax) xmax = dataPoints[i];
  }


  // Add some space around the data range
  double padding = 0.1 * (xmax - xmin);
  xmin -= padding;
  xmax += padding;

  // If the data is narrow, fall back to a default range
  if (xmin == xmax) {
    xmin = -5.0;
    xmax = 5.0;
  }


  int Nbins = 50; // histogram bins for data

  // -------------------------
  // 1) Default 1/(1+x^2) function
  // -------------------------
  FiniteFunction defaultFunc(xmin, xmax, "Normalised");
  defaultFunc.integral(1000);
  defaultFunc.plotFunction();
  defaultFunc.plotData(dataPoints, Nbins, true);
  defaultFunc.printInfo();

  // -------------------------
  // 2) Normal (Gaussian) guess
  // -------------------------
  NormalFunction gaussFunc(xmin, xmax, -2, 2, "NormalSampled");
  gaussFunc.integral(1000);
  gaussFunc.plotFunction();
  gaussFunc.plotData(dataPoints, Nbins, true);
  gaussFunc.printInfo();

  // -------------------------
  // Metropolis sampling from the best-fit Normal
  // -------------------------
  int Nsamples = 10000;      // how many points to generate
  double proposalSigma = 1.0; // width of proposal normal

  std::vector<double> samples = gaussFunc.sampleMetropolis(Nsamples, proposalSigma);

  // Plot sampled data as "samples" (blue) on the same axes
  gaussFunc.plotData(samples, Nbins, false); // isdata = false, treated as sampled points

  // -------------------------
  // Save sampled data to file with random ID
  // -------------------------

  int fileID = rand() % 90000 + 10000; // random 5-digit number (10000–99999)

  std::string outname =
    "./Outputs/data/MysteryData" + std::to_string(fileID) + ".txt";

  std::ofstream outfile(outname.c_str());

  if (!outfile.is_open()) {
    std::cout << "Error: could not open output file " << outname << std::endl;
  } else {
    for (double x : samples) {
      outfile << x << std::endl;
    }
    outfile.close();
    std::cout << "Sampled data written to " << outname << std::endl;
  }


  // -------------------------
  // 3) Cauchy–Lorentz guess
  // -------------------------
  CauchyFunction cauchyFunc(xmin, xmax, -2, 2.1, "Cauchy");
  cauchyFunc.integral(1000);
  cauchyFunc.plotFunction();
  cauchyFunc.plotData(dataPoints, Nbins, true);
  cauchyFunc.printInfo();

  // -------------------------
  // 4) Crystal Ball guess
  // -------------------------
  CrystalBallFunction cbFunc(xmin, xmax,
                            -2, 2,   // mean, sigma
                            2, 4.0,    // alpha, n
                            "CrystalBall");
  cbFunc.integral(1000);
  cbFunc.plotFunction();
  cbFunc.plotData(dataPoints, Nbins, true);
  cbFunc.printInfo();

  // Creating pngs
  return 0;
}
