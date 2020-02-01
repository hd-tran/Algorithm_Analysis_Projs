#ifndef RANDOMGEN_CPP
#define RANDOMGEN_CPP

#include <random>
#include <chrono>

std::mt19937 getMTGenWithCurrentTimeSeed()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	return std::mt19937(seed);
}

#endif
