#include <random>
#include <iostream>
#include <fstream>
#include <vector>


#include "randomGen.cpp"
#include "extraFunctions.cpp"
#include "AVLTree.hpp"

#include "project2.h"
#include "next_fit.cpp"
#include "first_fit.cpp"
#include "best_fit.cpp"
//#include "first_fit_optimized.cpp"
//#include "best_fit_optimized.cpp"

void testAlgorithms(int arraySize, std::mt19937 mt, std::uniform_real_distribution<double> distribution,
  std::ofstream & nextFitFS, std::ofstream & firstFitFS, std::ofstream & bestFitFS, std::ofstream & firstFitDecFS,std::ofstream & bestFitDecFS)
{

  std::vector<double> items1;
  std::vector<double> items2;
  std::vector<double> items3;
  std::vector<double> items4;
  std::vector<double> items5;
  //std::vector<double> items6;
  //std::vector<double> items7;
  //std::vector<double> items8;
  //std::vector<double> items9;


  for (int i = 0; i < arraySize; i++)
  {
    //std::cout << i << ": " << distribution(generator) << ", ";
    items1.push_back( distribution(mt) );
  }
  // each algorithm tests on the same set of values
  items2 = items1;
  items3 = items1;
  items4 = items1;
  items5 = items1;
  //items6 = items1;
  //items7 = items1;
  //items8 = items1;
  //items9 = items1;

  std::vector<int> assignment1(items1.size(), 0);
  std::vector<int> assignment2(items2.size(), 0);
  std::vector<int> assignment3(items3.size(), 0);
  std::vector<int> assignment4(items4.size(), 0);
  std::vector<int> assignment5(items5.size(), 0);
  //std::vector<int> assignment6(items6.size(), 0);
  //std::vector<int> assignment7(items7.size(), 0);
  //std::vector<int> assignment8(items8.size(), 0);
  //std::vector<int> assignment9(items9.size(), 0);


  std::vector<double> free_space1;
  std::vector<double> free_space2;
  std::vector<double> free_space3;
  std::vector<double> free_space4;
  std::vector<double> free_space5;
  //std::vector<double> free_space6;
  //std::vector<double> free_space7;
  //std::vector<double> free_space8;
  //std::vector<double> free_space9;

  // Call Algorithms
  next_fit(items1, assignment1, free_space1);

  first_fit(items2, assignment2, free_space2);
  //first_fit_optimized(items6, assignment6, free_space6);

  best_fit(items3, assignment3, free_space3);
  //best_fit_optimized(items7, assignment7, free_space7);

  first_fit_decreasing(items4, assignment4, free_space4);
  //first_fit_decreasing_optimized(items8, assignment8, free_space8);

  best_fit_decreasing(items5, assignment5, free_space5);
  //best_fit_decreasing_optimized(items9, assignment9, free_space9);
/*
  ///*
  // Printing Results
  std::cout << "==================================================================================\n";
  std::cout << "== arraySize: " << arraySize << " ==\n";

  std::cout << "############\n";
  std::cout << "# next_fit #\n";
  std::cout << "############\n";
///*
  //std::cout << "----Assignments: ";
  //printIntVector(assignment1);
  std::cout << "----Number of Bins: " << free_space1.size() << std::endl;
//
  std::cout << "----Waste: ";
  std::cout << calculateWaste(free_space1, items1) << std::endl;
*/
  nextFitFS.open("nextFitWaste.csv", std::ofstream::app);
  nextFitFS << arraySize << "," << calculateWaste(free_space1, items1) << "\n";
  nextFitFS.close();
  //---------------------------------------------------------------------------------------
/*
  std::cout << "#############\n";
  std::cout << "# first_fit #\n";
  std::cout << "#############\n";
*/
/*
  //std::cout << "----Assignments: ";
  //printIntVector(assignment2);
  std::cout << "----Number of Bins: " << free_space2.size() << std::endl;
*/
/*
  std::cout << "----Waste: ";
  std::cout << calculateWaste(free_space2, items2) << std::endl;
*/
  firstFitFS.open("firstFitWaste.csv", std::ofstream::app);
  firstFitFS << arraySize << "," << calculateWaste(free_space2, items2) << "\n";
  firstFitFS.close();

  //---------------------------------------------------------------------------------------
/*
  std::cout << "############\n";
  std::cout << "# best_fit #\n";
  std::cout << "############\n";
*/
/*
  std::cout << "----Assignments: ";
  printIntVector(assignment3);
  std::cout << "----Number of Bins: " << free_space3.size() << std::endl;
*/
/*
  std::cout << "----Waste: ";
  std::cout << calculateWaste(free_space3, items3) << std::endl;
*/
  bestFitFS.open("bestFitWaste.csv", std::ofstream::app);
  bestFitFS << arraySize << "," << calculateWaste(free_space3, items3) << "\n";
  bestFitFS.close();

  //---------------------------------------------------------------------------------------
/*
  std::cout << "########################\n";
  std::cout << "# first_fit_decreasing #\n";
  std::cout << "########################\n";
*/
/*
  //std::cout << "----Assignments: ";
  //printIntVector(assignment4);
  std::cout << "----Number of Bins: " << free_space4.size() << std::endl;
*/
/*
  std::cout << "----Waste: ";
  std::cout << calculateWaste(free_space4, items4) << std::endl;
*/
  firstFitDecFS.open("firstFitDecWaste.csv", std::ofstream::app);
  firstFitDecFS << arraySize << "," << calculateWaste(free_space4, items4) << "\n";
  firstFitDecFS.close();

  //---------------------------------------------------------------------------------------
/*
  std::cout << "#######################\n";
  std::cout << "# best_fit_decreasing #\n";
  std::cout << "#######################\n";
*/
/*
  std::cout << "--Items being packed: ";
  printDoubleVector(items5);

  std::cout << "----Bin Sizes: ";
  printDoubleVector(free_space5);

  std::cout << "----Assignments: ";
  printIntVector(assignment5);
  std::cout << "----Number of Bins: " << free_space5.size() << std::endl;
*/
/*
  std::cout << "----Waste: ";
  std::cout << calculateWaste(free_space5, items5) << std::endl;
*/
  bestFitDecFS.open("bestFitDecWaste.csv", std::ofstream::app);
  bestFitDecFS << arraySize << "," << calculateWaste(free_space5, items5) << "\n";
  bestFitDecFS.close();

  //---------------------------------------------------------------------------------------

  return;
}


int main()
{
  // Random Number Generator Setup
  std::mt19937 generator = getMTGenWithCurrentTimeSeed();
  std::uniform_real_distribution<double> distribution = getUniformRealDistribution(0.0, 1.0);

  std::ofstream nextFitFS;
  std::ofstream firstFitFS;
  std::ofstream bestFitFS;
  std::ofstream firstFitDecFS;
  std::ofstream bestFitDecFS;

  for (int i = 0; i < 5; i++)
  {
    reseedGenerator(generator);
    testAlgorithms(10, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(20, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(50, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(100, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(200, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(500, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(1000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(2000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(5000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(10000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(20000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(50000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(100000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);

    reseedGenerator(generator);
    testAlgorithms(200000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);
    //testAlgorithms(1000000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);
    //testAlgorithms(5000000, generator, distribution, nextFitFS, firstFitFS, bestFitFS, firstFitDecFS, bestFitDecFS);
  }



  return 0;
}
