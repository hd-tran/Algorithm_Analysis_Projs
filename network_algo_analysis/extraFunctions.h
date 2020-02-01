#ifndef EXTRAFUNCTIONS_H
#define EXTRAFUNCTIONS_H

#include "graph.h"

#include <vector>
#include <map>
#include <list>
#include <utility>
#include <queue>
#include <iostream>

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v);

void printNodeIDs( std::vector<Node*> nodes);

void printNodeMap( std::map<int, Node> nodes);

void printDLists( std::map< int, std::list<Node> > d);

#endif
