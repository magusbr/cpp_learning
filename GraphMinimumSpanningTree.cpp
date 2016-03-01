#include "GraphMinimumSpanningTree.h"

using namespace std;

// constructor calls for GraphShortestPath constructor
// class GraphMinimumSpanningTree just add one member function to the inherited class
GraphMinimumSpanningTree::GraphMinimumSpanningTree(const Graph& graph, const unsigned int& node_fro):
    GraphShortestPath(graph, node_fro)
{ }

GraphMinimumSpanningTree::~GraphMinimumSpanningTree()
{
}

double GraphMinimumSpanningTree::jarnik_prim()
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

        // if top is empty, there is no way to get to any other destination
        if ((current.get_destiny() == 0) && (current.get_origin() == 0) && (current.get_distance() == 0))
            break;

        // set visited
        distance += current.get_distance();

        // insert current node on closed set
        closed_set.push(current);
	min_distance[current] = distance;

        #ifdef DEBUG
        cout << "[Graph] " << current.get_origin() << "->" << current << "(" << current.get_distance() << ")" << endl;
        #endif // DEBUG

        // add adjacent nodes to open set
        // if already there, just update distance
        for (unsigned int i = 0; i < graph.get_num_nodes(); ++i)
        {
            // is "i" already reached by any other node?
            // if still opened it can be updated
            local_distance = graph.get_edge_value(current, i);
            if (local_distance > 0)
            {
                GraphNodeDistance current_to_node(current, i, local_distance);

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

    return distance;
}
