#ifndef GRAPH_H
#define GRAPH_H

#include "project3.h"
#include "node.h"

#include "randomGen.h"
#include "extraFunctions.h"

#include <vector>
#include <set>
#include <map>
#include <list>
#include <utility>
#include <queue>
#include <iostream>

class Graph: public AbstractGraph
{
public:
  Graph();
  ~Graph();

  int get_num_nodes();
  int get_num_edges();
  bool is_neighbor(Node u, Node v);
  std::vector<Node> get_neighbors(Node u);

  std::map<int, Node> get_id_to_node_map();

  std::map<int, int> bfsWithNodeDistance(Node start);

  std::set< std::pair<int, int> > edgeList;

  std::map< int, Node > nodeMap;

  std::map< int, std::vector<Node> > adjacencyMap;
};

/*
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v)
{
  Graph g;
  for (int i = 1; i <= num_nodes; i++)
  {
    Node n;
    n.id = i;
    g.nodeMap[i] = n;
  }

  for (int k = 0; k < u.size(); k++)
  {
    //std::cout << "Making Edges..." << std::endl;
    g.edgeList.push_back( std::pair<int, int> { (g.nodeMap[u[k]].id), (g.nodeMap[v[k]].id) } );

    //Node * vPointer = &(g.nodeMap[ v[k] ] );
    //Node * uPointer = &(g.nodeMap[ u[k] ] );

    //std::cout << vPointer->id << " vs " << v[k] << " vs " << g.nodeMap[v[k]].id << std::endl;
    //std::cout << uPointer->id << " vs " << u[k] << " vs " << g.nodeMap[u[k]].id << std::endl;

    g.adjacencyMap[u[k]].push_back( g.nodeMap[v[k]] );
    g.adjacencyMap[v[k]].push_back( g.nodeMap[u[k]] );
  }

  return g;
}

void printNodeIDs( std::vector<Node*> nodes)
{
  for (int i = 0; i < nodes.size(); i++)
  {
    std::cout << nodes[i]->id << std::endl;
  }
  return;
}

void printNodeMap( std::map<int, Node> nodes)
{
  for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
  {
    std::cout << it->first << ", " << it->second.id << std::endl;
  }
  return;
}

void printDLists( std::map< int, std::list<Node> > d)
{
  for (std::map<int, std::list<Node>>::iterator it = d.begin(); it != d.end(); it++)
  {
    std::cout << it->first << ": ";
    for (std::list<Node>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      std::cout << it2->id << ", ";
    }
    std::cout << "\n";
  }

  return;
}

*/
#endif
