#ifndef NEXT_FIT_CPP
#define NEXT_FIT_CPP

#include <vector>

#include "extraFunctions.cpp"

void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  // binIndex == current bin to fill
  int binIndex = 0;
  for (int i = 0; i < items.size(); i++ )
  {
    // If no bins allocated yet make a new bin and place inside
    if ( free_space.empty() )
    {
      free_space.push_back( 1.0 - items[i] );
      assignment[i] = 0;
      binIndex = 0;
    }
    // If current bin has enough free space, place item inside
    else if (free_space[binIndex] >= items[i])
    {
      free_space[binIndex] = free_space[binIndex] - items[i];
      assignment[i] = binIndex;
    }
    // If current bin does not have enough free space, make a new bin and move binIndex marker over
    else //if (free_space[binIndex] < items[i])
    {
      free_space.push_back( 1.0 - items[i] );
      binIndex++;
      assignment[i] = binIndex;
    }
  }

  return;
}

#endif
