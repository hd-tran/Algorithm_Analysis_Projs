/*
project3.h
node.h
graph.h
graph.cpp
graph_algorithms.cpp
barabasi_albert.cpp
*/
#include "project_head.h"
#include "node.h"
#include "graph.h"
//#include "graph.cpp"
#include "graph_algorithms.h"
//#include "graph_algorithms.cpp"

#include "barabasi_albert.h"
//#include "barabasi_albert.cpp"

//#include "tests.h"
#include "randomGen.h"
#include "extraFunctions.h"
//#include "extraFunctions.cpp"

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

void testClusterAndDiameter(int n)
{
  //std::cout << "Testing Barabasi Generation...\n";
  std::ofstream clusterCSV;
  std::ofstream diameterCSV;

  Graph barabasiGraph = create_barabasi_albert_graph(n, 5);
  std::cout << "Successful barabasi creation...\n";
  std::cout << "Number of edges: " << barabasiGraph.get_num_edges() << "\n";

  // Record Clustering Coefficient
  clusterCSV.open("clustering.csv", std::ofstream::app);

  float bClust = get_clustering_coefficient(barabasiGraph);
  std::cout << "Clustering Coefficient of barabasiGraph: " << bClust << "\n";

  clusterCSV << n << "," << bClust << "\n";

  clusterCSV.close();

  // Record Diameter
  diameterCSV.open("diameter.csv", std::ofstream::app);

  int bDiameter = get_diameter(barabasiGraph);
  std::cout << "Diameter of barabasiGraph: " << bDiameter << "\n";

  diameterCSV << n << "," << bDiameter << "\n";

  diameterCSV.close();
  return;
}

void testDegreeDistribution(int n)
{
  std::ofstream degreeCSV;
  std::string fileName = "degreeHist" + std::to_string(n) + ".csv";
  //std::cout << "FileName: " << fileName << "\n";

  Graph barabasiGraph = create_barabasi_albert_graph(n, 5);

  // Record Degree Distribution
  degreeCSV.open(fileName, std::ofstream::app);
  std::map<int,int> bDegreeDist = get_degree_distribution(barabasiGraph);
  for (std::map<int,int>::iterator it = bDegreeDist.begin(); it != bDegreeDist.end(); it++ )
  {
    std::cout << it->second << " Nodes with Degree " << it->first << std::endl;
    // x=Degree , y=Count or Freq
    degreeCSV << it->first << "," << it->second << "\n";
  }

  degreeCSV.close();

  return;
}

int main()
{
  //run_tests();
  //Graph g = create_barabasi_albert_graph(10, 5);

  //std::vector<int> v = {1,1,1,1,2,4,3};
  //std::vector<int> u = {2,3,4,5,4,5,6};
  //std::vector<int> v = {1,1,2,2,4,4,5};
  //std::vector<int> u = {2,3,3,4,5,6,6};
  //Graph g = make_graph(6, v, u);
  /*
  // Smallish Test
  std::vector<int> v = {1,1,2,2,2,3,5,5,7,6,6,8,6 ,3,3 ,5};
  std::vector<int> u = {2,4,4,3,5,5,7,8,8,8,9,9,10,6,10,6};
  Graph g = make_graph(10, v, u);

  // Testing Clustering Coefficient

  //std::vector<int> v = {1,1,1,1};
  //std::vector<int> u = {2,3,4,5};
  //Graph g = make_graph(5, v, u);

  float clust = get_clustering_coefficient(g);
  std::cout << "Clustering Coefficient of g: " << clust << std::endl;

  std::map<int,int> degreeDist = get_degree_distribution(g);
  for (std::map<int,int>::iterator i = degreeDist.begin(); i != degreeDist.end(); i++)
  {
    std::cout << i->second << " Nodes with Degree " << i->first << std::endl;
  }

  int diameter = get_diameter(g);
  std::cout << "Diameter of graph: " << diameter << "\n";

  std::cout << "\n\n";
  std::cout << "Testing Barabasi Generation...\n";
  */

  testClusterAndDiameter(10);
  testClusterAndDiameter(10);
  testClusterAndDiameter(10);
  testClusterAndDiameter(10);
  testClusterAndDiameter(10);

  testClusterAndDiameter(100);
  testClusterAndDiameter(100);
  testClusterAndDiameter(100);
  testClusterAndDiameter(100);
  testClusterAndDiameter(100);

  testClusterAndDiameter(1000);
  testClusterAndDiameter(1000);
  testClusterAndDiameter(1000);
  testClusterAndDiameter(1000);
  testClusterAndDiameter(1000);

  testClusterAndDiameter(10000);
  testClusterAndDiameter(10000);
  testClusterAndDiameter(10000);
  testClusterAndDiameter(10000);
  testClusterAndDiameter(10000);

  //testClusterAndDiameter(100000);
  //testClusterAndDiameter(100000);
  //testClusterAndDiameter(100000);
  //testClusterAndDiameter(100000);
  //testClusterAndDiameter(100000);


  //testDegreeDistribution(10);
  //testDegreeDistribution(100);
  testDegreeDistribution(1000);
  testDegreeDistribution(10000);
  testDegreeDistribution(100000);

  return 0;
}
