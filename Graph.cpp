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
    if ((node1 > m_nodes)
        || (node2 > m_nodes))
        return -1;

    m_edges++;

    m_graph[node1][node2] = val;
    m_graph[node2][node1] = val;

    #ifdef DEBUG
    cout << "[Graph] added edge from " << node1 << " to " << node2 << endl;
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
    vector<node_distance_t> open;
    //priority_queue type could be used maybe

    // make sure nodes are valid
    assert(fro < m_nodes && fro >= 0);
    assert(to < m_nodes && to >= 0);

    // initialize open set with reachable nodes from origin
    for (unsigned int i = 0; i < m_nodes; ++i)
        if (m_graph[fro][i] > 0)
            open.push_back({fro, i, m_graph[fro][i], false});

    // loop until open set is overrun or destiny reaches closed set
    unsigned int current_node = fro;
    int distance = 0;
    bool any_visit = false;
    bool already_on_open = false;
    while (true)
    {
        // sort open set
        sort(open.begin(), open.end(), compare_node_distance_t());
        #ifdef DEBUG
        cout << "[Graph] ordered open: ";
        for (vector<node_distance_t>::iterator it=open.begin(); it!=open.end(); ++it)
            if(!(*it).visited) cout << (*it).from << "->" << (*it).to << "(" << (*it).distance << ") ";
        cout << endl;
        #endif // DEBUG


        // get the non-visited least distance on open set
        any_visit = false;
        vector<node_distance_t>::iterator visit;
        for (vector<node_distance_t>::iterator it=open.begin(); it!=open.end(); ++it)
        {
            if ((*it).visited) continue;
            any_visit = true;

            visit = it;
            break;
        }

        if (!any_visit)
            return -1;

        // set visited
        (*visit).visited = true;
        current_node = (*visit).to;
        distance = (*visit).distance;
        #ifdef DEBUG
        cout << "[Graph] current " << current_node << " distance " << (*visit).distance << endl;
        #endif // DEBUG

        if (current_node == to)
            break;

        // add adjacent nodes to open set
        // if already there, just update distance
        for (unsigned int i = 0; i < m_nodes; ++i)
        {
            if (m_graph[current_node][i] > 0)
            {
                // if already on open set, update distance
                already_on_open = false;
                // automatically detect iterator type
                for (auto it2=open.begin(); it2!=open.end(); ++it2)
                {
                    // ignore inverted path (0->1) or (1->0) because both were already visited
                    if ((((*it2).from == i) && ((*it2).to == current_node)))
                    {
                        already_on_open = true;
                        break;
                    }

                    // if already on open set, just update
                    if ((*it2).to == i)
                    {
                        already_on_open = true;

                        if (distance + m_graph[current_node][i] < (*it2).distance)
                        {
                            #ifdef DEBUG
                            cout << "i " << i << " current_node " << current_node << endl;
                            cout << "from " << (*it2).from << " to " << (*it2).to << endl;
                            cout << "new distance " << distance + m_graph[current_node][i] << " curr (*it2).distance " << (*it2).distance << endl;
                            #endif // DEBUG
                            (*it2).distance = distance + m_graph[current_node][i];
                            (*it2).from = current_node;
                            break;
                        }
                    }
                }

                // if not found, add it
                if (!already_on_open)
                {
                    open.push_back({current_node, i, m_graph[current_node][i]+distance, false});
                }
            }
        }
    }


    for (vector<node_distance_t>::iterator it=open.begin(); it!=open.end(); ++it)
        cout << (*it).from << "->" << (*it).to << endl;
    cout << endl;

    int current = current_node;
    cout << "shortest path: ";
    for (vector<node_distance_t>::reverse_iterator it=open.rbegin(); it!=open.rend(); ++it)
    {
        if ((*it).to == (unsigned int)current)
        {
            current = (*it).from;
            cout << (*it).to << " ";
        }
    }
    cout << fro << endl;

    return distance;
}
