#include "GraphShortestPath.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;

GraphShortestPath::GraphShortestPath(const Graph& graph, const unsigned int& node_fro, const unsigned int& node_to):
    graph(graph), node_fro(node_fro), node_to(node_to), min_distance(-1)
{
    //ctor
    // make sure nodes are valid
    assert(node_fro < this->graph.get_num_nodes() && node_fro >= 0);
    assert(node_to < this->graph.get_num_nodes() && node_to >= 0);
}

GraphShortestPath::~GraphShortestPath()
{
    //dtor
}

bool GraphShortestPath::is_connected()
{
    int old_size = 0, c_size = 0;
    const int size = graph.get_num_nodes();

    vector<bool> close(size, false);
    vector<bool> open(size, false);

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
                    open[j] = open[j] || graph.get_edge_value(i, j);
            }

        }

        #ifdef DEBUG_ITER
        cout << "c_size: " << c_size << " size: " << size << endl;
        #endif // DEBUG_ITER
        if (c_size == size)
        {
            return true; // connected
        }
        if (old_size == c_size)
        {
            return false; // unconnected
        }
    }

    return false;
}

double GraphShortestPath::dijkstra()
{
    double local_distance = 0.0;
    GraphNodeDistance current(0, 0, 0);
    double distance = 0.0;
    open_set.clear();
    closed_set.clear();

    // initialize open set with reachable nodes from origin
    for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
    {
        local_distance = graph.get_edge_value(node_fro, i);
        if (local_distance > 0.0)
            open_set.push(GraphNodeDistance(node_fro, i, local_distance));
    }

    // loop until open set is overrun or destiny reaches closed set
    while (true)
    {
        #ifdef DEBUG
        cout << "[Graph] ordered open: ";
        open_set.print();
        #endif // DEBUG

        // get the non-visited with least distance on open set
        current = open_set.pop();

        // if top is empty, there is no way to get to destination
        if ((current.get_destiny() == 0) && (current.get_origin() == 0) && (current.get_distance() == 0))
            return (min_distance = -1.0);

        // set visited
        distance = current.get_distance();

        // insert current node on closed set
        closed_set.push(current);

        #ifdef DEBUG
        cout << "[Graph] " << current.get_origin() << "->" << current << "(" << current.get_distance() << ")" << endl;
        #endif // DEBUG

        // did we get to destination? then stop
        if (current == node_to)
            break;

        // add adjacent nodes to open set
        // if already there, just update distance
        for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
        {
            // is "i" already reached by any other node?
            // if still opened it can be updated
            local_distance = graph.get_edge_value(current, i);
            if (local_distance > 0)
            {
                GraphNodeDistance current_to_node(current, i, distance+local_distance);

                // check if there is a way from current -> i or i -> current_node on open set
                // if there is, update distance and origin from current_node -> i
                // if there is not, add it
                if (!closed_set.contains(i))
                {
                    if (open_set.contains(i))
                    {
                        // update distance if opened and less than current
                        open_set.requeue_on_less_distance(current_to_node);
                    }
                    else
                    {
                        // "i" is not on open (or closed) set. add it to open
                        open_set.push(current_to_node);
                    }
                }
            }
        }

    }

    return (min_distance = distance);
}

void GraphShortestPath::path_print() const
{
    vector<int> path;
    GraphSortedNodeDistanceList set = closed_set;
    GraphNodeDistance node_distance = GraphNodeDistance(0, 0, 0);
    // print only if min distance was actually found
    if (min_distance != -1)
    {
        cout << "Minimum path from " << node_fro << " to " << node_to << " is:" << endl;
        unsigned int current = node_to;

        // loop over closed set getting origin from current node, starting from destination node until source node
        while (true)
        {
            node_distance = set.bottom();
            // if no more items on closed_set, end loop
            if ((node_distance.get_origin() == 0) && (node_distance.get_destiny() == 0) && (node_distance.get_distance() == 0))
                break;

            // if found origin node, get next origin and add current node to path
            if (node_distance == current)
            {
                current = node_distance.get_origin();
                path.push_back(node_distance);
            }
        }
        // end path with source node
        path.push_back(node_fro);

        // reverse loop over path to print it
        for (auto it = path.rbegin(); it != path.rend(); it++)
        {
            if ((it+1) != (path.rend()))
                cout << (*it) << " -> ";
            else
                cout << (*it);
        }
        cout << endl;
    }
    else
    {
        cout << "Minimum path from" << node_fro << " to " << node_to << " could not be found." << endl;
    }
}

double GraphShortestPath::path_size() const
{
    return min_distance;
}

void GraphShortestPath::path_size_print() const
{
    if (min_distance < 0.0)
    {
        cout << "Distance from " << node_fro << " to " << node_to << " is: " << min_distance << endl;
    }
    else
    {
        cout << "Distance from " << node_fro << " to " << node_to << " could not be found." << endl;
    }
}
