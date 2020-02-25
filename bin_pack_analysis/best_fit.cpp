#ifndef BEST_FIT_CPP
#define BEST_FIT_CPP

#include <vector>
#include <algorithm>
#include <iostream>

#include "extraFunctions.cpp"

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
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
      int smallestFit = -1; // bin # for the bin in which item[i] fits the smallest: -1 == no valid bins found
      for (int n = 0; n < free_space.size(); n++)
      {
        if ( free_space[n] >= items[i])
        {
          if ( smallestFit == -1) // no candidates found yet, but valid one exists (bin#: n)
          {
            smallestFit = n;
          }
          else if ( free_space[n] < free_space[smallestFit])
          {
            smallestFit = n;
          }
          else
          {
            continue;
          }
        }
      }

      if (smallestFit != -1) // smallest bin found
      {
        free_space[smallestFit] = free_space[smallestFit] - items[i];
        assignment[i] = smallestFit;
      }
      else // if smallestFit == -1, no valid bins found: add a new one
      {
        free_space.push_back( 1.0 - items[i]);
        assignment[i] = free_space.size()-1;
      }
    }
  }


  return;
}

struct ItemWithIndex
{
  double item;
  int index;
  ItemWithIndex(double val, int index)
  {
    this->item = val;
    this->index = index;
  }

};

bool itemLessThan(const ItemWithIndex & lhs, const ItemWithIndex & rhs)
{
  if (lhs.item < rhs.item)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  std::vector<ItemWithIndex> sortedItems;
  for (int j = 0; j < items.size(); j++)
  {
    sortedItems.push_back( ItemWithIndex(items[j],j) );
  }

  //std::vector<double> sortedItems = items;
  std::sort( sortedItems.begin(), sortedItems.end(), itemLessThan );
  std::reverse( sortedItems.begin(), sortedItems.end() );
/*
  for (int j = 0; j < sortedItems.size(); j++)
  {
    std::cout << "(" << sortedItems[j].item << ", " << sortedItems[j].index << "), ";
  }
  std::cout << "\n";
  std::cout << ( 0.8+0.2 == 1.0 ) << "\n";
  //printDoubleVector(sortedItems);
*/
  for (int i = 0; i < sortedItems.size(); i++)
  {
    if (free_space.empty())
    {
      free_space.push_back(1.0 - sortedItems[i].item);
      assignment[sortedItems[i].index] = 0;
      continue;
    }
    else
    {
      int smallestFit = -1; // bin # for the bin in which item[i] fits the smallest: -1 == no valid bins found
      for (int n = 0; n < free_space.size(); n++)
      {
        if ( free_space[n] >= sortedItems[i].item )
        {
          if ( smallestFit == -1) // no candidates found yet, but valid one exists (bin#: n)
          {
            smallestFit = n;
          }
          else if ( free_space[n] < free_space[smallestFit])
          {
            smallestFit = n;
          }
          else
          {
            continue;
          }
        }
      }

      if (smallestFit != -1) // smallest bin found
      {
        free_space[smallestFit] = free_space[smallestFit] - sortedItems[i].item;
        assignment[sortedItems[i].index] = smallestFit;
      }
      else // if smallestFit == -1, no valid bins found: add a new one
      {
        free_space.push_back( 1.0 - sortedItems[i].item);
        assignment[sortedItems[i].index] = free_space.size()-1;
      }
    }
  }
  //std::cout << free_space[0] << "vs" << sortedItems[5].item << "\n";
  //std::cout << (free_space[0] == sortedItems[5].item) << "\n";
  return;
}

#endif
