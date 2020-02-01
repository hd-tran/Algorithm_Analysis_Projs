#ifndef BARABASI_ALBERT_CPP
#define BARABASI_ALBERT_CPP

#include "barabasi_albert.h"

/*
#include "graph.h"
#include "randomGen.h"

//#include "randomGen.cpp"

//#include <vector>
//#include <utility>
//#include <random>

//#include <iostream>
*/

Graph create_barabasi_albert_graph(int n, int d)
{
  std::mt19937 generator = getMTGenWithCurrentTimeSeed();

  std::vector<int> m;
  m.reserve(2*n*d);
  //Graph initGraph = make_graph(n, std::vector<Node>{}, std::vector<Node>{});
  for (int v = 0; v < n; v++)
  {
    for (int i = 0; i < d; i++)
    {
      m[ 2*( (v*d) + i ) ] = v+1; // vertex numbers are 1-indexed
      std::uniform_int_distribution<int> distribution = getUniformIntDistribution( 0, 2*((v*d)+i) );
      int r = distribution(generator);
      //std::cout << "Random Num... " << r <<std::endl;
      m[ (2*( (v*d) + i) ) + 1] = m[r];
    }
  }

  for (int j = 0; j < (m.size()/2); j++)
  {
    std::cout << m[2*j] << "--" << m[2*j+1] << "\n";
  }

  std::set< std::pair<int, int> > edges;
  // edge List = empty;
  ///*

  for (int i = 0; i < ( (n*d)-1 ); i++)
  {
    //if edge (m[2i],m[2i+1]) or (m[2i+1],m[2i]) NOT IN edge list
    std::pair<int,int> edge1{ m[2*i], m[(2*i)+1] };
    std::pair<int,int> edge2{ m[(2*i)+1], m[2*i] };

    //std::cout << "Candidate Edge: (" << edge1.first << "," << edge1.second << ")\n";

    if (edges.find(edge1) == edges.end() && edges.find(edge2) == edges.end() && m[2*i] != m[(2*i)+1] )
    {
      edges.insert(edge1);
    }

    //if (e1[i] == m[2*i] && e2[i] == m[2*i+1])
      // add edge (m[2i],m[2i+1]) into edge List
  }
  //*/
  std::vector<int> e1;
  std::vector<int> e2;
  for (std::set< std::pair<int,int> >::iterator it = edges.begin(); it != edges.end(); it++)
  {
    //std::cout << it->first << "--" << it->second << "\n";
    e1.push_back(it->first);
    e2.push_back(it->second);
  }

  Graph g = make_graph( n, e1, e2 );
  return g;
}


#endif
