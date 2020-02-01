#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"

//#include <iostream>

Graph::Graph()
{
  return;
}
Graph::~Graph()
{
  return;
}

int Graph::get_num_nodes()
{
  return nodeMap.size();
}

int Graph::get_num_edges()
{
  return edgeList.size();
}

bool Graph::is_neighbor(Node u, Node v)
{
  //printNodeMap(nodeMap);

  //printNodeIDs(adjacencyMap[u.id]);

  for (int i = 0; i < adjacencyMap[u.id].size(); i++)
  {
    if ( (adjacencyMap[u.id][i]) == v )
    {
      //std::cout << "---------------My Stuff\n";
      //std::cout << "---------------" << u.id << " vs " << (adjacencyMap[u.id][i])->id << std::endl;
      //std::cout << "---------------" << (u.id == adjacencyMap[u.id][i]->id) << std::endl;
      return true;
    }
  }

  return false;
}

std::vector<Node> Graph::get_neighbors(Node u)
{
  std::vector<Node> output;

  for (int i = 0; i < adjacencyMap[u.id].size() ; i++)
  {
    output.push_back( (adjacencyMap[u.id][i]) );
  }

  return output;
}

std::map<int, Node> Graph::get_id_to_node_map()
{
  return nodeMap;
}

std::map<int, int> Graph::bfsWithNodeDistance(Node start)
{
  std::map<int, int> nodeDistances;

  std::map<int, bool> visitedMap;
  for (std::map<int, Node>::iterator i = nodeMap.begin(); i != nodeMap.end(); i++)
  {
    visitedMap[i->first] = false;
  }

  std::queue<Node> q;

  visitedMap[start.id] = true;
  q.push(start);
  nodeDistances[start.id] = 0;

  while( !q.empty() )
  {
    Node s = q.front();
    q.pop();

    for (int n = 0; n < adjacencyMap[s.id].size(); n++)
    {
      if ( !(visitedMap[ adjacencyMap[s.id][n].id ]) )
      {
        visitedMap[ adjacencyMap[s.id][n].id ] = true;
        nodeDistances[ (adjacencyMap[s.id][n]).id ] = nodeDistances[s.id] + 1;
        q.push( (adjacencyMap[s.id][n]) );
      }
    }
  }

  return nodeDistances;
}


// Extra Stuff

#endif
