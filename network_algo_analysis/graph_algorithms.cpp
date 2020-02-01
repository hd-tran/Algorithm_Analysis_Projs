#ifndef GRAPH_ALGORITHMS_CPP
#define GRAPH_ALGORITHMS_CPP

#include "graph_algorithms.h"

/*
#include "graph.h"
#include "randomGen.h"

#include <vector>
#include <list>
#include <unordered_set>
#include <map>
#include <algorithm>

#include <iostream>
*/

// Extra stuf (declarations)
std::pair< std::list<int>, std::map<int, std::list<Node> > >findDegeneracyOrdering(Graph graph);
float countTriangles( Graph graph );


int get_diameter(Graph graph)
{
  // Heuristic 2
  std::mt19937 generator = getMTGenWithCurrentTimeSeed();
  std::uniform_int_distribution<int> distribution = getUniformIntDistribution( 1, graph.nodeMap.size() );

  int r = distribution(generator);
  //std::cout << "Random r: " << r << "\n";

  int dMax = 0;

  std::map<int, int> bfsDistances = graph.bfsWithNodeDistance( graph.nodeMap[r] );
  //std::cout << "Got bfsDistances...\n";

  int w = -1;
  for (std::map<int, int>::iterator it = bfsDistances.begin(); it != bfsDistances.end(); it++)
  {
    if ( (w == -1) || (it->second) > bfsDistances[w] )
    {
      w = it->first;
    }
  }

  //std::cout << "First dMax: " << dMax << "\n";
  //std::cout << "First bfsDistance: " << bfsDistances[w] << "\n";

  while ( bfsDistances[w] > dMax )
  {
    dMax = bfsDistances[w];

    r = w;
    //std::cout << "New r: " << r << "\n";

    bfsDistances = graph.bfsWithNodeDistance( graph.nodeMap[r] );

    for (std::map<int, int>::iterator it = bfsDistances.begin(); it != bfsDistances.end(); it++)
    {
      // If w not iniated OR the current Node has a farther distance
      if ( (w == -1) || (it->second) > bfsDistances[w] )
      {
        // set w to the new Node
        w = it->first;
      }
    }
    //std::cout << "Candidate dMax: " << bfsDistances[w] << "\n";
  }

  //std::cout << "Final dMax: " << dMax << "\n";

  return dMax;
}

float get_clustering_coefficient(Graph graph)
{
  // float c = 3*(# of Triangles) / # of 2-edge paths

  float denom = 0.0;
  for (std::map< int, std::vector<Node> >::iterator i = graph.adjacencyMap.begin(); i != graph.adjacencyMap.end(); i++)
  {
    denom += ( (i->second.size() * (i->second.size()-1)) / 2 );
  }

  //std::cout << denom << std::endl;

  float numer = 3.0 * countTriangles(graph);

  float c = numer / denom;
  return c;
}

std::map<int, int> get_degree_distribution(Graph graph)
{
  std::map<int,int> hist;
  for (std::map<int, Node>::iterator i = graph.nodeMap.begin(); i != graph.nodeMap.end(); i++)
  {
    hist[ graph.adjacencyMap[i->first].size() ] += 1;
  }

  return hist;
}


// Extra stuff
float countTriangles(Graph graph)
{
  std::pair< std::list<int>, std::map< int, std::list<Node> > > degenOrderAndNv = findDegeneracyOrdering(graph);

  std::list<int> degenOrder = degenOrderAndNv.first;
  std::map<int, std::list<Node>> Nv = degenOrderAndNv.second;

  /*
  std::cout << "Degen Ordering... \n";
  for (std::list<int>::iterator it = degenOrder.begin(); it != degenOrder.end(); it++)
  {
    std::cout << *it << ", ";
  }
  std::cout << "\n";
*/
  ///*
  float triangleCount = 0.0;
  //std::map< std::pair<int,int>, bool> edgeCounted;
  //std::vector< std::unordered_set<int> > triangles;
  for (std::list<int>::iterator it = degenOrder.begin(); it != degenOrder.end(); it++)
  {
    //std::cout << "Checking v = " << *it << "\n";
    for (std::list<Node>::iterator it2 = Nv[*it].begin(); it2 != Nv[*it].end(); it2++)
    {
      //std::cout << "Something exists in Nv[v]\n";
      //std::cout << "Nv[" << *it << "] = " << it2->id << "\n";
      for (std::list<Node>::iterator it3 = std::next(it2); it3 != Nv[*it].end(); it3++)
      {
        //std::cout << it2->id << " vs " << it3->id << "\n";

        std::pair<int, int> uw(it2->id, it3->id);
        //std::cout << "(" << it2->id << "," << it3->id << ") exists? " << ( std::find(g.edgeList.begin(), g.edgeList.end(), uw) != g.edgeList.end()) << std::endl;

        std::pair<int, int> wu(it3->id, it2->id);
        //std::cout << "(" << it3->id << "," << it2->id << ") exists? " << ( std::find(g.edgeList.begin(), g.edgeList.end(), wu) != g.edgeList.end()) << std::endl;

        if ( std::find(graph.edgeList.begin(), graph.edgeList.end(), uw) != graph.edgeList.end() || std::find(graph.edgeList.begin(), graph.edgeList.end(), wu) != graph.edgeList.end() )
        {
          //edgeCounted[uw] = true;
          //std::unordered_set<int> tri = {*it, it2->id, it3->id};
          //triangles.push_back(tri);
          triangleCount += 1.0;
        }
      }
    }
  }

  //std::cout << "Triangle Count: " << triangleCount << "\n";

  return triangleCount;
}

std::pair< std::list<int>, std::map<int, std::list<Node> > >findDegeneracyOrdering(Graph graph)
{
  // Initialize output L
  std::list<int> L;
  //std::cout << "Init. L...\n";
  // Hash for checking if v in L
  std::unordered_set<int> H;
  //std::cout << "Init. H...\n";

  // Compute each vertex's initial dv
  std::map<int, int> dv;
  for (std::map< int, std::vector<Node> >::iterator i = graph.adjacencyMap.begin(); i != graph.adjacencyMap.end(); i++)
  {
    dv[i->first] = i->second.size();
    //std::cout << i->first << ", " << i->second.size() << std::endl;
  }
  //std::cout << "Init. dv...\n";

  // Initialize D using dv vector
  std::map<int, std::list<Node> > D;
  for (std::map< int, int >::iterator i = dv.begin(); i != dv.end(); i++)
  {
    std::list<int>::iterator v = std::find(L.begin(), L.end(), i->first);

    if ( v == L.end() )
    {
      //Node n = (graph.nodeMap[i->first]);
      D[i->second].push_back( graph.nodeMap[i->first] );
      //std::cout << "i->first: " << i->first << std::endl;
      //std::cout << i->second << ", " << graph.nodeMap[i->first].id << std::endl;
    }
  }
  //printDLists(D);
  //std::cout << "Init. D...\n";

  // Init Nv (list of nieghbors of v that come before v in L)
  std::map<int, std::list<Node> > Nv;  // Initially empty for all Nv[v] lists
  //std::cout << "Init. Nv...\n";

  // Init k to 0
  //int k = 0;

  // Repeat n times...
  //int counter = 1;

  for (int i = 0; i < graph.nodeMap.size(); i++)
  {
    // Scan D for first non empty entry
    int entry;
    bool foundNonEmpty = false;

    ///*
    for (std::map<int, std::list<Node> >::iterator it = D.begin(); it != D.end(); it++)
    {
      //std::cout << "Iterator of D: " << it->first << std::endl;

      if ( !(it->second.empty()) )
      {
        //std::cout << it->first << std::endl;
        entry = it->first;
        //std::cout << entry << std::endl;
        foundNonEmpty = true;
        break;
      }

    }
    if (!foundNonEmpty)
    {
      break;
    }
    //*/

    //std::cout << "Finding entry (i)..." << entry << std::endl;
    // Set k to max(k,entry)
    //k = std::max(k, entry);

    // Select a vertex v from D[entry]
    //std::cout << "Selecting vertex from D[entry]...\n";
    Node v = D[entry].front();

    // Add vertex v to begin of L and remove from D[entry]
    //std::cout << "Adding v to L...\n";
    L.push_front(v.id);
    //std::cout << "Removing from D...\n";
    D[entry].pop_front();
    //std::cout << "Successfully removed from D...\n";

    // Mark vertex v being in L
    H.insert(v.id);

    // For Each: neighbor w of vertex v that is not already in L:
    for ( int x = 0; x < graph.adjacencyMap[v.id].size(); x++ )
    {
      Node wNode = graph.adjacencyMap[v.id][x];
      int w = wNode.id;
      if ( H.find(w) == H.end() )
      {
        // Subtract 1 from dv[w]
        dv[w] -= 1;

        // Move vertex w to D[ dv[w] ] (and remove from original position)
        D[ dv[w]+1 ].remove( wNode ); //(remove orig position)
        //std::cout << "Removing old W position...\n";
        D[ dv[w] ].push_back( wNode ); // move w Pointer to new pos
        //std::cout << "Moving W vertex to new D slot...\n";
        // Add w to Nv
        Nv[v.id].push_back(wNode);

      }
    }
    //std::cout << "Iteration " << counter << std::endl;
    //printDLists(D);
    //counter++;
  }


  return std::pair< std::list<int>, std::map< int, std::list<Node> >> {L, Nv};
}

#endif
