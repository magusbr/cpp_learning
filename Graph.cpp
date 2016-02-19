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


Graph::Graph(unsigned int number)
{
    //ctor
    m_nodes = number;
    m_graph = new int*[number];
    for (unsigned int i = 0; i < number; ++i)
    {
        m_graph[i] = new int[number];

        for (unsigned int j = 0; j < number; ++j)
            m_graph[i][j] = 0;
    }

    #ifdef DEBUG
        cout << "[Graph] created graph of size " << m_nodes << endl;
    #endif
}

Graph::~Graph()
{
    //dtor
    delete_graph();

    #ifdef DEBUG
    cout << "[Graph] deleted all" << endl;
    #endif
}

Graph::Graph(const Graph& other)
{
    //copy ctor
    m_nodes = 0;
    m_edges = 0;
    m_graph = nullptr;

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
    return *this;
}

//C++11 move constructor
Graph::Graph(Graph&& other):m_nodes(0), m_edges(0), m_graph(nullptr)
{
    //move ctor
    #ifdef DEBUG
    cout << "[Graph] called move constructor" << endl;
    #endif // DEBUG

    // two steps
    // pilfer other's resources
    // reset other

    m_nodes = other.m_nodes;
    m_edges = other.m_edges;
    m_graph = other.m_graph;

    other.m_nodes = 0;
    other.m_edges = 0;
    other.m_graph = nullptr;
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
        m_nodes = 0;
        m_edges = 0;
        delete_graph();
        m_graph = nullptr;

        m_nodes = other.m_nodes;
        m_edges = other.m_edges;
        m_graph = other.m_graph;

        other.m_nodes = 0;
        other.m_edges = 0;
        other.m_graph = nullptr;
    }

    return *this;
}

void Graph::delete_graph()
{
    for (unsigned int i = 0; i < m_nodes; ++i)
    {
        delete [] *m_graph;
        #ifdef DEBUG
        cout << "[Graph] deleted " << i << endl;
        #endif
    }
    delete [] m_graph;

    m_nodes = 0;
    m_edges = 0;
}

unsigned int Graph::get_num_nodes()
{
    return m_nodes;
}

unsigned int Graph::get_num_edges()
{
    return m_edges;
}

bool Graph::adjacent_nodes(const unsigned int& x, const unsigned int& y)
{
    if ((m_graph[x][y] > 0) || (m_graph[y][x]))
        return true;
    else
        return false;
}

unsigned int Graph::add_node()
{

    return 0;
}

bool Graph::rem_node(const unsigned int& node)
{

    return 0;
}

bool Graph::add_edge(const unsigned int& x, const unsigned int& y, const unsigned int& distance)
{
    // consistency checks
    if (x == y)
        return false;
    if ((x > m_nodes)
        || (y > m_nodes))
        return false;

    m_edges++;

    m_graph[x][y] = distance;
    m_graph[y][x] = distance;

    #ifdef DEBUG
    cout << "[Graph] added edge from " << x << " to " << y << endl;
    #endif // DEBUG

    return true;
}

bool Graph::rem_edge(const unsigned int& x, const unsigned int& y)
{
    if (m_graph[x][y] == 0)
        return false;

    m_graph[x][y] = 0;
    m_graph[y][x] = 0;
    m_edges--;

    return true;
}

unsigned int Graph::get_edge_value(const unsigned int& x, const unsigned int& y)
{
    if ((x >= m_nodes) || (y >= m_nodes))
        return 0;

    return m_graph[x][y];
}

bool Graph::set_edge_value(const unsigned int& x, const unsigned int& y, const unsigned int& distance)
{
    if ((x >= m_nodes) || (y >= m_nodes))
        return false;

    m_graph[x][y] = distance;

    return true;
}
