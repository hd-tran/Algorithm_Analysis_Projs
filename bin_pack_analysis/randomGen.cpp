#ifndef RANDOMGEN_CPP
#define RANDOMGEN_CPP

#include <random>
#include <chrono>

std::mt19937 getMTGenWithCurrentTimeSeed()
{
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        return std::mt19937(seed);
}

void reseedGenerator(std::mt19937 & mt)
{
  mt.seed(std::chrono::system_clock::now().time_since_epoch().count());
  return;
}

std::uniform_real_distribution<double> getUniformRealDistribution( double lb, double ub )
{
  return std::uniform_real_distribution<double>(lb, ub);
}

double randDouble( std::mt19937 mt, double lb, double ub )
{
  return std::uniform_real_distribution<double>(lb, ub) (mt);
}

#endif
