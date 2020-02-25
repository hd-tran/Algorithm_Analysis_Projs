#include <vector>
#include <map>

#ifndef PROJECT3_H
#define PROJECT3_H

/******* NODE CLASS ********/
class Node;  // define/implement in node.h

/*
Node must
    have a default constructor
    have a public member int 'id' which uniquely identifies a node (no two nodes have the same id).
           id must be set in the constructor and thereafter not modified
    have the following method:
        bool operator==(const Node& other) const {return id == other.id;}

You may add whatever other members you like to Node
*/

/******* GRAPH BASE CLASS TO OVERRIDE********/
class AbstractGraph
{
    public: // all methods must be overriden
        virtual int get_num_nodes() = 0; // number of nodes
        virtual int get_num_edges() = 0; // number of edges
        virtual bool is_neighbor(Node u, Node v) = 0 ;
        virtual std::vector<Node> get_neighbors(Node u) = 0;

        // allows lookup of nodes from ids
        virtual std::map<int, Node> get_id_to_node_map() = 0;
};

class Graph; // define interface in graph.h, implement in graph.cpp (see below)
             // should #include "node.h"

// construct a graph using num_nodes nodes and edges (ui, vi) for all i
// u and v will be the same length
// (ui, vi) are pairs of integers which can be mapped uniquely to (ui', vi'), pairs of Nodes
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v);

/* graph.h
class Graph : public AbstractGraph
{
    ... // list all methods to override
    ... // list any other constructors, members, and member functions you may want to use
}
*/

/* graph.cpp
// implement all of your members declared in graph.h
...
bool Graph::is_neighbor(Node u, Node v)
{
    ...
}
...
*/

/******* ALGORITHMS TO IMPLEMENT ********/
// implement all 3 in graph_algorithms.cpp
// should include graph.h
int get_diameter(Graph graph);
float get_clustering_coefficient(Graph graph);
std::map<int, int> get_degree_distribution(Graph graph);

/******* GRAPH GENERATION FUNCTIONS ********/

Graph create_barabasi_albert_graph(int n, int d); // implement in barabasi_albert.cpp

/******* FILE SUMMARY (SORTED BY DEPENDENCIES)
    project_head.h
    node.h
    graph.h
    graph.cpp
    graph_algorithms.cpp
    barabasi_albert.cpp
    run.sh
*/
#endif
