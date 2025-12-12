// Classes from FiniteFunction for different shapes

#pragma once

#include <string>
#include "FiniteFunctions.h"

// -------------------------
// Normal (Gaussian) function
// -------------------------
class NormalFunction : public FiniteFunction {

public:
  NormalFunction(double range_min, double range_max,
                 double mu, double sigma,
                 std::string outfile);

  virtual double callFunction(double x);
  virtual void printInfo();

private:
  double m_mu;
  double m_sigma;
};

// -------------------------
// Cauchy–Lorentz function
// -------------------------
class CauchyFunction : public FiniteFunction {

public:
  CauchyFunction(double range_min, double range_max,
                 double x0, double gamma,
                 std::string outfile);

  virtual double callFunction(double x);
  virtual void printInfo();

private:
  double m_x0;
  double m_gamma;
};

// -------------------------
// Crystal Ball function
// -------------------------
class CrystalBallFunction : public FiniteFunction {

public:
  CrystalBallFunction(double range_min, double range_max,
                      double mean, double sigma,
                      double alpha, double n,
                      std::string outfile);

  virtual double callFunction(double x);
  virtual void printInfo();

private:
  double m_mean;
  double m_sigma;
  double m_alpha;
  double m_n;

  double m_A;
  double m_B;
  double m_N;
  double m_C;
  double m_D;

  void updateConstants();
};
