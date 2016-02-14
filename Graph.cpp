#include "Graph.h"

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

#define DEBUG 1
#define DEBUG_ITER 1

Graph::Graph(unsigned int val)
{
    //ctor
    m_nodes = val;
    m_graph = new int*[val];
    for (unsigned int i = 0; i < val; ++i)
    {
        m_graph[i] = new int[val];

        for (unsigned int j = 0; j < val; ++j)
            m_graph[i][j] = 0;
    }

    #ifdef DEBUG
        cout << "[Graph] created graph of size " << val << endl;
    #endif
}

Graph::~Graph()
{
    //dtor
    for (unsigned int i = 0; i < m_nodes; ++i)
    {
        delete [] *m_graph;
        #ifdef DEBUG
        cout << "[Graph] deleted " << i << endl;
        #endif
    }
    delete [] m_graph;
    #ifdef DEBUG
    cout << "[Graph] deleted all" << endl;
    #endif
}

Graph::Graph(const Graph& other)
{
    //copy ctor
}

Graph& Graph::operator=(const Graph& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


int Graph::Addedge(unsigned int val, unsigned int node1, unsigned int node2)
{
    // consistency checks
    if (node1 == node2)
        return -1;
    if ((node1 > m_edges)
        || (node2 > m_edges))
        return -1;

    m_edges++;

    m_graph[node1][node2] = val;
    m_graph[node2][node1] = val;

    #ifdef DEBUG
    cout << "[Graph] added edge from " << node1 << "to" << node2 << endl;
    #endif // DEBUG

    return 0;
}

bool Graph::Isconnected()
{
    int old_size = 0, c_size = 0;
    const int size = m_nodes;

    bool* close = new bool[size];
    bool* open = new bool[size];

    for (int i = 0; i < size; ++i)
        open[i] = close[i] = false;

    open[0] = true;

    while (c_size < size)
    {
        for (int i = 0; i < size; ++i)
        {
            old_size = c_size;
            if (open[i] && (close[i] == false))
            {
                close[i] = true;
                c_size++;

                for (int j = 0; j < size; ++j)
                    open[j] = open[j] || m_graph[i][j];
            }

        }

        #ifdef DEBUG_ITER
        cout << "c_size: " << c_size << " size: " << size << endl;
        #endif // DEBUG_ITER
        if (c_size == size)
        {
            delete [] open;
            delete [] close;
            return true; // connected
        }
        if (old_size == c_size)
        {
            delete [] open;
            delete [] close;
            return false; // unconnected
        }
    }

    delete [] open;
    delete [] close;
    return false;
}

/*
closed nodes - nodes with known shortest path
open set - what's reachable - select open node with least cost


origin, destiny
closed set, open set
shortest path

- initial
closed:
origin = 0
open
whats reachable by origin with distance

- steps
pick least cost in open set and add node to closed set
add new reachables to open set updating values if less than current (except whats already in closed set)
if no advance, pick another least cost

- end
destiny reaches the closed set
*/
int Graph::DjikstraShortestPath(unsigned int fro, unsigned int to)
{
    typedef struct node_distance_t
    {
        unsigned int node;
        int distance;
    } node_distance_t;

    vector<node_distance_t> close;
    vector<node_distance_t> open;
    vector<node_distance_t> shortest_path;

    // make sure nodes are valid
    assert(fro < m_nodes && fro >= 0);
    assert(to < m_nodes && to >= 0);

    // initialize closed set with origin and its distance: 0
    close.push_back({fro, 0});

    // initialize open set with reachable nodes from origin
    for (unsigned int i = 0; i < m_nodes; ++i)
        if (m_graph[fro][i] > 0)
            open.push_back({i, m_graph[fro][i]});

    // loop until open set is overrun or destiny reaches closed set
    while (true)
    {

    }

    return -1;
}
