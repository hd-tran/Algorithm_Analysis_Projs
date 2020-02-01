#ifndef FIRST_FIT_OPTIMIZED_CPP
#define FIRST_FIT_OPTIMIZED_CPP

#include <vector>
#include <algorithm>
#include <iostream>

#include "extraFunctions.cpp"
#include "AVLTree.hpp"

class firstFitNode : public forest::AVLTreeNodeBase<firstFitNode>
{
public:
  firstFitNode(int i, double s)
  {
    this->index = i;
    this->space = s;
    this->maxChild = 0.0;
  }

  int index;
  double space;
  double maxChild;

  bool operator < (const firstFitNode & n) const
  {
    if ( index < n.index )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

};

void first_fit_optimized(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  forest::AVLTree<firstFitNode> firstFitBins;
  for (int i = 0; i < items.size(); i++)
  {
    if ( free_space.empty() )
    {
      free_space.push_back( 1.0 - items[i]);
      firstFitNode node( 0, free_space[0] );
      firstFitBins.Insert(node);
      assignment[i] = free_space.size()-1;
      continue;
    }

  }
  std::cout << "Tree Size: " << firstFitBins.Size() << std::endl;

  return;
}

void first_fit_decreasing_optimized(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  return;
}

#endif
