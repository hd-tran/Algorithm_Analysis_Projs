#ifndef EXTRAFUNCTIONS_CPP
#define EXTRAFUNCTIONS_CPP

#include <vector>
#include <iostream>

void printDoubleVector(std::vector<double> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    std::cout << v[i] << ", ";
  }
  std::cout << std::endl;
  return;
}

void printIntVector(std::vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    std::cout << v[i] << ", ";
  }
  std::cout << std::endl;
  return;
}

double calculateWaste(const std::vector<double> & free_space, const std::vector<double> & items)
{
  double weight = 0.0;
  for (int i = 0; i < items.size(); i++)
  {
    weight += items[i];
  }
  return free_space.size() - weight;
}

#endif
