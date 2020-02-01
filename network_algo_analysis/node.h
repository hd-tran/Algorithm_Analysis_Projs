#ifndef NODE_H
#define NODE_H

//#include <vector>

class Node
{
public:
  Node()
  {
    id = -1;
    //adjacencyList = std::vector<Node>{};
  }

  bool operator==(const Node & other) const
  {
    return id == other.id;
  }

  bool operator<(const Node & other) const
  {
    return id < other.id;
  }

  int id;
  //std::vector<Node> adjacencyList;

};


#endif
