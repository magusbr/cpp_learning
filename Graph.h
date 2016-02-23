#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Graph
{
    public:
        // constructors and destructors
        Graph():num_nodes(0),num_edges(0),dist_matrix(0) {}; // create an empty graph
        Graph(unsigned int num_nodes); // create a graph with number of nodes
        virtual ~Graph(); // delete graph and clean its internal memory
        Graph(const Graph& other); // copy constructor
        Graph& operator=(const Graph& other); // assignment operator
        Graph(Graph&& other); // move constructor (C++11)
        Graph& operator=(Graph&& other); // assignment move operator (C++11)

        // methods
        unsigned int get_num_nodes(); // returns the number of nodes in the graph
        unsigned int get_num_edges(); // returns the number of edges in the graph
        bool adjacent_nodes(const unsigned int& x, const unsigned int& y); //tests whether there is an edge from node x to node y
        unsigned int add_node(); // add node to graph
        bool rem_node(const unsigned int& node); // remove node from graph
        bool add_edge(const unsigned int& x, const unsigned int& y, const unsigned int& distance); // adds to graph the edge from x to y, if it is not there.
        bool rem_edge(const unsigned int& x, const unsigned int& y); // removes the edge from x to y, if it is there.
        unsigned int get_edge_value(const unsigned int& x, const unsigned int& y); // returns the value associated to the edge (x,y).
        bool set_edge_value(const unsigned int& x, const unsigned int& y, const unsigned int& distance); // sets the value associated to the edge (x,y) to distance.
        void print(); // print internal representation of the graph (distance matrix)
        void randomize(const unsigned int& num_nodes, const unsigned int& min_distance, const unsigned int& max_distance); // generate graph with size num_nodes with random edges with size [min_distance, max_distance]
        unsigned int operator () (const unsigned int& node_from, const unsigned int& node_to);


    protected:

    private:
        unsigned int num_nodes;
        unsigned int num_edges;
        vector<vector<int>> dist_matrix;
};

#endif // GRAPH_H
