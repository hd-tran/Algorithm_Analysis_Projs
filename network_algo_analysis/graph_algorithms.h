#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "graph.h"
#include "randomGen.h"

#include <vector>
#include <list>
#include <unordered_set>
#include <map>
#include <algorithm>

#include <iostream>

std::pair< std::list<int>, std::map<int, std::list<Node> > >findDegeneracyOrdering(Graph graph);
float countTriangles( Graph graph );


int get_diameter(Graph graph);

float get_clustering_coefficient(Graph graph);

std::map<int, int> get_degree_distribution(Graph graph);

#endif
