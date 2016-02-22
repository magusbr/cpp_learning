#include "GraphShortestPath.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;

GraphShortestPath::GraphShortestPath(const Graph& graph, const unsigned int& node_fro, const unsigned int& node_to):
    graph(graph), node_fro(node_fro), node_to(node_to)
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

bool GraphShortestPath::Isconnected()
{
    int old_size = 0, c_size = 0;
    const int size = graph.get_num_nodes();

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
                    open[j] = open[j] || graph.get_edge_value(i, j);
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
int GraphShortestPath::DjikstraShortestPath(unsigned int fro, unsigned int to)
{
    vector<node_distance_t> open;
    //priority_queue type could be used maybe

    // make sure nodes are valid
    assert(fro < graph.get_num_nodes() && fro >= 0);
    assert(to < graph.get_num_nodes() && to >= 0);

    // initialize open set with reachable nodes from origin
    for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
        if (graph.get_edge_value(fro, i) > 0)
            open.push_back({fro, i, graph.get_edge_value(fro, i), false});

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
        //cout << "[Graph] current " << current_node << " distance " << (*visit).distance << endl;
        cout << "[Graph] " << (*visit).from << "->" << (*visit).to << "(" << (*visit).distance << ")" << endl;
        #endif // DEBUG

        if (current_node == to)
            break;

        // add adjacent nodes to open set
        // if already there, just update distance
        for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
        {
            if (graph.get_edge_value(current_node, i) > 0)
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

                        // do not update visited distance
                        if ((*it2).visited) break;

                        if (distance + graph.get_edge_value(current_node, i) < (*it2).distance)
                        {
                            #ifdef DEBUG_ITER
                            cout << "[Graph] Update " << (*it2).from << "->" << (*it2).to << "(" << (*it2).distance << ") ";
                            cout << "to " << current_node << "->" << i << "(" << distance+graph.get_edge_value(current_node, i) << ")" << endl;
                            #endif // DEBUG_ITER
                            (*it2).distance = distance + graph.get_edge_value(current_node, i);
                            (*it2).from = current_node;
                            break;
                        }
                    }
                }

                // if not found, add it
                if (!already_on_open)
                {
                    open.push_back({current_node, i, graph.get_edge_value(current_node, i)+distance, false});
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






int GraphShortestPath::JarnikPrimMST()
{
    vector<node_distance_t> open;
    //priority_queue type could be used maybe

    // initialize open set with reachable nodes from origin
    for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
        if (graph.get_edge_value(0, i) > 0)
            open.push_back({0, i, graph.get_edge_value(0, i), false});

    // loop until open set is overrun or destiny reaches closed set
    unsigned int current_node = 0;
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
            break;

        // set visited
        (*visit).visited = true;
        current_node = (*visit).to;
        distance = (*visit).distance;
        #ifdef DEBUG
        //cout << "[Graph] current " << current_node << " distance " << (*visit).distance << endl;
        cout << "[Graph] " << (*visit).from << "->" << (*visit).to << "(" << (*visit).distance << ")" << endl;
        #endif // DEBUG

        // add adjacent nodes to open set
        // if already there, just update distance
        for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
        {
            if (graph.get_edge_value(current_node, i) > 0)
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

                        // do not update visited distance
                        if ((*it2).visited) break;

                        if (graph.get_edge_value(current_node, i) < (*it2).distance)
                        {
                            #ifdef DEBUG_ITER
                            cout << "[Graph] Update " << (*it2).from << "->" << (*it2).to << "(" << (*it2).distance << ") ";
                            cout << "to " << current_node << "->" << i << "(" << graph.get_edge_value(current_node, i) << ")" << endl;
                            #endif // DEBUG_ITER
                            (*it2).distance = graph.get_edge_value(current_node, i);
                            (*it2).from = current_node;
                            break;
                        }
                    }
                }

                // if not found, add it
                if (!already_on_open)
                {
                    open.push_back({current_node, i, graph.get_edge_value(current_node, i), false});
                }
            }
        }
    }

    for (auto it=open.begin(); it!=open.end(); ++it)
        cout << (*it).from << "->" << (*it).to << "(" << (*it).distance << ") ";
    cout << endl;

    return distance;
}











unsigned int GraphShortestPath::dijkstra()
{
    unsigned int local_distance = 0;
    GraphNodeDistance current(0, 0, 0);
    int distance = 0;

    // initialize open set with reachable nodes from origin

    for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
    {
        local_distance = graph.get_edge_value(node_fro, i);
        if (local_distance > 0)
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
            return -1;

        // set visited
        current.set_closed();
        distance = current.get_distance();

        // reinsert the current path to the ordered list, but now marked visited
        open_set.push(current);

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

                // check if there is a way from current -> i or i -> current_node on open list
                // if there is not, add it
                // if there is, update distance and origin from current_node -> i, if opened
                if (open_set.contains(i))
                {
                    // update distance if opened and less than current
                    open_set.requeue_opened(current_to_node);
                }
                else
                {
                    // "i" is not on open (or closed) set. add it to open
                    open_set.push(current_to_node);
                }
            }
        }

    }


/*    for (vector<node_distance_t>::iterator it=open.begin(); it!=open.end(); ++it)
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
*/
    return distance;
}
