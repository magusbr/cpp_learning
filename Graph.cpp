#include "Graph.h"

#include <iostream>
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
    bool* aa = nullptr;

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
