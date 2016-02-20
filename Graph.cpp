#include "Graph.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <assert.h>
#include <algorithm>
using namespace std;

#define DEBUG 1
#define DEBUG_ITER 1


Graph::Graph(unsigned int num_nodes):dist_matrix(num_nodes, vector<int>(num_nodes, 0))
{
    //ctor
    this->num_nodes = num_nodes;

    #ifdef DEBUG
        cout << "[Graph] created graph of size " << num_nodes << endl;
    #endif
}

Graph::~Graph()
{
    //dtor
    num_nodes = 0;
    num_edges = 0;
    dist_matrix.clear();

    #ifdef DEBUG
    cout << "[Graph] deleted all" << endl;
    #endif
}

Graph::Graph(const Graph& other)
{
    //copy ctor
    num_nodes = other.num_nodes;
    num_edges = other.num_edges;
    dist_matrix = other.dist_matrix;

    #ifdef DEBUG
    cout << "[Graph] called copy constructor" << endl;
    #endif // DEBUG
}

Graph& Graph::operator=(const Graph& other)
{
    //assignment operator
    #ifdef DEBUG
    cout << "[Graph] called assignment operator= overload" << endl;
    #endif // DEBUG

    if (this == &other) return *this; // handle self assignment
    else
    {
        num_nodes = other.num_nodes;
        num_edges = other.num_edges;
        dist_matrix = other.dist_matrix;
    }
    return *this;
}

//C++11 move constructor
Graph::Graph(Graph&& other):num_nodes(0), num_edges(0), dist_matrix()
{
    //move ctor
    #ifdef DEBUG
    cout << "[Graph] called move constructor" << endl;
    #endif // DEBUG

    // two steps
    // pilfer other's resources
    // reset other

    num_nodes = other.num_nodes;
    num_edges = other.num_edges;
    dist_matrix = other.dist_matrix;

    other.num_nodes = 0;
    other.num_edges = 0;
    other.dist_matrix.clear();
}

//C++11 move assignment operator
Graph& Graph::operator=(Graph&& other)
{
    //move operator
    #ifdef DEBUG
    cout << "[Graph] called move operator= overload" << endl;
    #endif // DEBUG

    // four steps
    // release current object resources
    // pilfer other's resources
    // reset other
    // return *this

    if (this!=&other)
    {
        num_nodes = 0;
        num_edges = 0;
        dist_matrix.clear();

        num_nodes = other.num_nodes;
        num_edges = other.num_edges;
        dist_matrix = other.dist_matrix;

        other.num_nodes = 0;
        other.num_edges = 0;
        other.dist_matrix.clear();
    }

    return *this;
}

unsigned int Graph::get_num_nodes()
{
    return num_nodes;
}

unsigned int Graph::get_num_edges()
{
    return num_edges;
}

bool Graph::adjacent_nodes(const unsigned int& x, const unsigned int& y)
{
    if ((dist_matrix[x][y] > 0) || (dist_matrix[y][x]))
        return true;
    else
        return false;
}

unsigned int Graph::add_node()
{
    unsigned int new_size = dist_matrix.size();
    vector<int> temp(new_size, 0);

    dist_matrix.push_back(temp);

    return 0;
}

bool Graph::rem_node(const unsigned int& node)
{
    if (node >= dist_matrix.size())
        return false;

    // update number of edges
    // each edge going out of "node" will be subtracted
    for (vector<int>::iterator it = (dist_matrix.begin()+node)->begin(); it != (dist_matrix.begin()+node)->end(); it++)
        if ((*it) > 0) num_edges--;

    // each line will have one less column at the position of node
    for (vector<vector<int>>::iterator it = dist_matrix.begin(); it != dist_matrix.end(); it++)
    {
        (*it).erase((*it).begin()+node);
    }

    // then, remove the line for the node we want to remove
    dist_matrix.erase(dist_matrix.begin()+node);

    // update number of nodes
    num_nodes--;

    #ifdef DEBUG
    cout << "[Graph] removed node " << node << " from graph" << endl;
    #endif // DEBUG

    return true;
}

bool Graph::add_edge(const unsigned int& x, const unsigned int& y, const unsigned int& distance)
{
    // consistency checks
    if (x == y)
        return false;
    if ((x > num_nodes)
        || (y > num_nodes))
        return false;

    num_edges++;

    dist_matrix[x][y] = distance;
    dist_matrix[y][x] = distance;

    #ifdef DEBUG
    cout << "[Graph] added edge from " << x << " to " << y << endl;
    #endif // DEBUG

    return true;
}

bool Graph::rem_edge(const unsigned int& x, const unsigned int& y)
{
    if (dist_matrix[x][y] == 0)
        return false;

    dist_matrix[x][y] = 0;
    dist_matrix[y][x] = 0;
    num_edges--;

    return true;
}

unsigned int Graph::get_edge_value(const unsigned int& x, const unsigned int& y)
{
    if ((x >= num_nodes) || (y >= num_nodes))
        return 0;

    return dist_matrix[x][y];
}

bool Graph::set_edge_value(const unsigned int& x, const unsigned int& y, const unsigned int& distance)
{
    if ((x >= num_nodes) || (y >= num_nodes))
        return false;

    dist_matrix[x][y] = distance;

    return true;
}
