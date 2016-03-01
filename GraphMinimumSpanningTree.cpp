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
        cout << "[GraphMinimumSpanningTree] ordered open: ";
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
        cout << "[GraphMinimumSpanningTree] " << current.get_origin() << "->" << current << "(" << current.get_distance() << ")" << endl;
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

void GraphMinimumSpanningTree::path_print(const unsigned int& to_node) const
{
    vector<int> path;
    GraphSortedNodeDistanceList set = closed_set;
    GraphNodeDistance node_distance = GraphNodeDistance(0, 0, 0);
    bool retry = false;
    #ifdef DEBUG
    cout << "[GraphMinimumSpanningTree] Closed set to reorder: ";
    set.print();
    #endif
    // print only if min distance was actually found
    if (min_distance[to_node] != -1.0)
    {
        cout << node_fro << " to " << to_node << " [";
        unsigned int current = to_node;

        // loop over closed set getting origin from current node, starting from destination node until source node
        while (true)
        {
            node_distance = set.bottom();
            // if no more items on closed_set, retry once
            if ((node_distance.get_origin() == 0) && (node_distance.get_destiny() == 0) && (node_distance.get_distance() == 0))
            {
                // already retried, exit
                if (retry)
                    break;
                else
                {
                    // restore set to closed_set because maybe we have already (wrongly) discarded the node we need to get to
                    #ifdef DEBUG_ITER
                    cout << "[GraphMinimumSpanningTree] retry: " << retry << " current: " << current << endl;
                    #endif
                    retry = true;
                    set = closed_set;
                }
            }

            // if found origin node, get next origin and add current node to path
            if (node_distance == current)
            {
                current = node_distance.get_origin();
                path.push_back(node_distance);
                // node distance origin is the initial node, so we can add it and finish already
                if (current == node_fro)
                {
                    path.push_back(node_fro);
                    break;
                }
                retry = false;
            }
        }

        // reverse loop over path to print it
        for (auto it = path.rbegin(); it != path.rend(); it++)
        {
            if ((it+1) != (path.rend()))
                cout << (*it) << "->";
            else
                cout << (*it);
        }
        cout << "]" << endl;
    }
    else
    {
        cout << node_fro << " to " << to_node << " could not be found." << endl;
    }
}

