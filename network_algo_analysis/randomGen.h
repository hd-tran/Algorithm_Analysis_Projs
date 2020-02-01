#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>
#include <chrono>

std::mt19937 getMTGenWithCurrentTimeSeed();

void reseedGenerator(std::mt19937 & mt);

std::uniform_real_distribution<double> getUniformRealDistribution( double lb, double ub );

std::uniform_int_distribution<int> getUniformIntDistribution( int lb, int ub );

double randDouble( std::mt19937 mt, double lb, double ub );


#endif
