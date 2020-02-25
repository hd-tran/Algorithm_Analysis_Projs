#ifndef FIRST_FIT_CPP
#define FIRST_FIT_CPP

#include <vector>
#include <algorithm>
#include <iostream>

#include "extraFunctions.cpp"

void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  for (int i = 0; i < items.size(); i++)
  {
    if (free_space.empty())
    {
      free_space.push_back(1.0 - items[i]);
      assignment[i] = 0;
      continue;
    }
    else
    {
      bool addBin = true;
      for (int n = 0; n < free_space.size(); n++)
      {
        if (free_space[n] >= items[i])
        {
          free_space[n] = free_space[n] - items[i];
          assignment[i] = n;
          addBin = false;
          break;
        }

      }

      // if no open bins, make new bin
      if (addBin)
      {
        free_space.push_back(1.0 - items[i]);
        assignment[i] = free_space.size()-1;
      }

    }
  }

  return;
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  std::vector<double> sortedItems = items;
  std::sort( sortedItems.begin(), sortedItems.end() );
  std::reverse( sortedItems.begin(), sortedItems.end() );

  //printDoubleVector(sortedItems);

  for (int i = 0; i < sortedItems.size(); i++)
  {
    if (free_space.empty())
    {
      free_space.push_back(1.0 - sortedItems[i]);
      assignment[i] = 0;
      continue;
    }
    else
    {
      bool addBin = true;
      for (int n = 0; n < free_space.size(); n++)
      {
        if (free_space[n] >= sortedItems[i])
        {
          free_space[n] = free_space[n] - sortedItems[i];
          assignment[i] = n;
          addBin = false;
          break;
        }

      }

      // if no open bins, make new bin
      if (addBin)
      {
        free_space.push_back(1.0 - sortedItems[i]);
        assignment[i] = free_space.size()-1;
      }

    }
  }

  return;
}

#endif
