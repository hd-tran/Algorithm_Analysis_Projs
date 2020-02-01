#ifndef BEST_FIT_OPTIMIZED_CPP
#define BEST_FIT_OPTIMIZED_CPP

#include <vector>
#include <algorithm>
#include <iostream>

#include "extraFunctions.cpp"
#include "AVLTree.hpp"



class bestFitNode : public forest::AVLTreeNodeBase<bestFitNode>
{
public:
  bestFitNode(int i, double s)
  {
    this->index = i;
    this->space = s;

  }

  int index;
  double space;

  bool operator < (const bestFitNode & n) const
  {
    std::cout << space << " vs " << n.space << std::endl;
    if ( space < n.space )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool operator > (const bestFitNode & n) const
  {
    if (space > n.space)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
/*
  bool operator < (const double & d) const
  {
    if (space < d)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
*/
};

void best_fit_optimized(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  forest::AVLTree<bestFitNode> bestFitBins;
  for (int i = 0; i < items.size(); i++)
  {
    if (free_space.empty())
    {
      free_space.push_back( 1.0 - items[i] );
      bestFitNode node( 0, free_space[0] );
      bestFitBins.Insert( node );
      assignment[i] = free_space.size()-1;
      //std::cout << "First Item Added: " << items[i] << std::endl;
      continue;
    }
    else
    {
      bestFitNode * leaf = bestFitBins.searchBestBin( bestFitNode(-1, items[i]) );
      //std::cout << (leaf != nullptr) << std::endl;
      //std::cout << "Item to Add: " << items[i] << std::endl;

      if (leaf != nullptr)
      {
        //std::cout << "First Bin Option Index and Space: " << leaf->index << ", " << leaf->space << std::endl;
        //std::cout << "Fit item into first bin?: " << (leaf->space >= items[i]) << std::endl;
        // edit Bins
          // extract bin info ( effectively removing it like pop() )
          // re-insert bin with updated space info
        bestFitNode newNode(leaf->index, leaf->space - items[i]);
        //std::cout << "Removing Old Bin...\n";
        bestFitBins.Remove( *leaf );
        //std::cout << "Smaller Tree Size... " << bestFitBins.Size() << std::endl;
        //std::cout << "Inserting Updated Bin...\n";
        bestFitBins.Insert( newNode );
        //std::cout << "Updated Tree Size... " << bestFitBins.Size() << std::endl;
        //std::cout << "New Bin Stats: " << newNode.index << ", " << newNode.space << std::endl;
        free_space[newNode.index] = newNode.space;
        assignment[i] = newNode.index;
      }
      else //if (leaf == nullptr)
      {
        // add a bin
        //std::cout << "Making New Bin...\n";
        free_space.push_back(1.0 - items[i]);
        bestFitNode node( free_space.size()-1, 1.0-items[i] );
        bestFitBins.Insert( node );
        assignment[i] = free_space.size()-1;
      }
    }
    //std::cout << "Tree Size: " << bestFitBins.Size() << std::endl;
  }
  //std::cout << "Final Tree Size: " << bestFitBins.Size() << std::endl;
  return;
}

void best_fit_decreasing_optimized(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  std::vector<ItemWithIndex> sortedItems;
  for (int j = 0; j < items.size(); j ++)
  {
    sortedItems.push_back( ItemWithIndex(items[j], j) );
  }

  //std::vector<double> sortedItems = items;
  std::sort( sortedItems.begin(), sortedItems.end(), itemLessThan );
  std::reverse( sortedItems.begin(), sortedItems.end() );


  for (int i = 0; i < items.size(); i++)
  {
    std::cout << "(" << sortedItems[i].item << ", " << sortedItems[i].index << "), ";
  }
  std::cout << "\n";


  forest::AVLTree<bestFitNode> bestFitBins;
  for (int i = 0; i < items.size(); i++)
  {
    if (free_space.empty())
    {
      free_space.push_back( 1.0 - sortedItems[i].item );
      bestFitNode node( sortedItems[i].index, free_space[0] );
      bestFitBins.Insert( node );
      assignment[sortedItems[i].index] = 0;
      //std::cout << "First Item Added: " << items[i] << std::endl;
      continue;
    }
    else
    {
      bestFitNode * leaf = bestFitBins.searchBestBin( bestFitNode(-1, sortedItems[i].item) );
      //std::cout << (leaf != nullptr) << std::endl;
      //std::cout << "Item to Add: " << items[i] << std::endl;

      if (leaf != nullptr)
      {
        //std::cout << "First Bin Option Index and Space: " << leaf->index << ", " << leaf->space << std::endl;
        //std::cout << "Fit item into first bin?: " << (leaf->space >= items[i]) << std::endl;
        // edit Bins
          // extract bin info ( effectively removing it like pop() )
          // re-insert bin with updated space info
        bestFitNode newNode(leaf->index, leaf->space - sortedItems[i].item);
        //std::cout << "Removing Old Bin...\n";
        bestFitBins.Remove( *leaf );
        //std::cout << "Smaller Tree Size... " << bestFitBins.Size() << std::endl;
        //std::cout << "Inserting Updated Bin...\n";
        bestFitBins.Insert( newNode );
        //std::cout << "Updated Tree Size... " << bestFitBins.Size() << std::endl;
        //std::cout << "New Bin Stats: " << newNode.index << ", " << newNode.space << std::endl;
        free_space[newNode.index] = newNode.space;
        assignment[sortedItems[i].index] = newNode.index;
      }
      else //if (leaf == nullptr)
      {
        // add a bin
        //std::cout << "Making New Bin...\n";
        free_space.push_back(1.0 - sortedItems[i].item);
        bestFitNode node( free_space.size()-1, 1.0 - sortedItems[i].item );
        bestFitBins.Insert( node );
        assignment[sortedItems[i].index] = free_space.size()-1;
      }
    }
    //std::cout << "Bins at item: " << i << " (" << sortedItems[i] << ")" << std::endl;
    //bestFitBins.InOrderTraversal([](auto & node) {std::cout << node.index << ", " << node.space << std::endl;});

    //std::cout << "Tree Size: " << bestFitBins.Size() << std::endl;
  }
  //std::cout << "Final Tree Size: " << bestFitBins.Size() << std::endl;
  //bestFitBins.InOrderTraversal([](auto & node) {std::cout << node.index << ", " << node.space << std::endl;});
  //std::cout << std::endl;
  return;
}

#endif
