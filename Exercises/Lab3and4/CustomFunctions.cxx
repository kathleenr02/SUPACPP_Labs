// Implementation of classes inheriting from FiniteFunction

#include "CustomFunctions.h"
#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;

// -------------------------
// Normal (Gaussian) function
// -------------------------

NormalFunction::NormalFunction(double range_min, double range_max,
                               double mu, double sigma,
                               std::string outfile)
  : FiniteFunction(range_min, range_max, outfile)
{
  m_mu    = mu;
  m_sigma = sigma;
}

double NormalFunction::callFunction(double x) {
  double t    = (x - m_mu) / m_sigma;
  double norm = 1.0 / (m_sigma * std::sqrt(2.0 * PI));
  return norm * std::exp(-0.5 * t * t);
}

void NormalFunction::printInfo() {
  std::cout << "NormalFunction" << std::endl;
  std::cout << "  rangeMin: " << m_RMin << std::endl;
  std::cout << "  rangeMax: " << m_RMax << std::endl;
  std::cout << "  mu:       " << m_mu << std::endl;
  std::cout << "  sigma:    " << m_sigma << std::endl;
  std::cout << "  integral: " << m_Integral
            << ", calculated using " << m_IntDiv << " divisions" << std::endl;
}

// -------------------------
// Cauchy–Lorentz function
// -------------------------

CauchyFunction::CauchyFunction(double range_min, double range_max,
                               double x0, double gamma,
                               std::string outfile)
  : FiniteFunction(range_min, range_max, outfile)
{
  m_x0    = x0;
  m_gamma = gamma;
}

double CauchyFunction::callFunction(double x) {
  double t = (x - m_x0) / m_gamma;
  return 1.0 / (PI * m_gamma * (1.0 + t * t));
}

void CauchyFunction::printInfo() {
  std::cout << "CauchyFunction" << std::endl;
  std::cout << "  rangeMin: " << m_RMin << std::endl;
  std::cout << "  rangeMax: " << m_RMax << std::endl;
  std::cout << "  x0:       " << m_x0 << std::endl;
  std::cout << "  gamma:    " << m_gamma << std::endl;
  std::cout << "  integral: " << m_Integral
            << ", calculated using " << m_IntDiv << " divisions" << std::endl;
}

// -------------------------
// Crystal Ball function
// -------------------------

void CrystalBallFunction::updateConstants() {
  double absAlpha = std::fabs(m_alpha);

  m_A = std::pow(m_n / absAlpha, m_n) * std::exp(-0.5 * absAlpha * absAlpha);
  m_B = m_n / absAlpha - absAlpha;

  m_C = (m_n / absAlpha) * (1.0 / (m_n - 1.0))
        * std::exp(-0.5 * absAlpha * absAlpha);

  m_D = std::sqrt(PI / 2.0) *
        (1.0 + std::erf(absAlpha / std::sqrt(2.0)));

  m_N = 1.0 / (m_sigma * (m_C + m_D));
}

CrystalBallFunction::CrystalBallFunction(double range_min, double range_max,
                                         double mean, double sigma,
                                         double alpha, double n,
                                         std::string outfile)
  : FiniteFunction(range_min, range_max, outfile)
{
  m_mean  = mean;
  m_sigma = sigma;
  m_alpha = alpha;
  m_n     = n;

  updateConstants();
}

double CrystalBallFunction::callFunction(double x) {
  double t = (x - m_mean) / m_sigma;

  if (t > -m_alpha) {
    // Gaussian part
    return m_N * std::exp(-0.5 * t * t);
  } else {
    // Power-law tail
    double term = m_B - t;
    return m_N * m_A * std::pow(term, -m_n);
  }
}

void CrystalBallFunction::printInfo() {
  std::cout << "CrystalBallFunction" << std::endl;
  std::cout << "  rangeMin: " << m_RMin << std::endl;
  std::cout << "  rangeMax: " << m_RMax << std::endl;
  std::cout << "  mean:     " << m_mean << std::endl;
  std::cout << "  sigma:    " << m_sigma << std::endl;
  std::cout << "  alpha:    " << m_alpha << std::endl;
  std::cout << "  n:        " << m_n << std::endl;
  std::cout << "  integral: " << m_Integral
            << ", calculated using " << m_IntDiv << " divisions" << std::endl;
}
