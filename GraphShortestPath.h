#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Graph.h"
#include "GraphSortedNodeDistanceList.h"

class GraphShortestPath
{
    public:
        GraphShortestPath(const Graph& graph, const unsigned int& node_fro, const unsigned int& node_to);
        virtual ~GraphShortestPath();
        bool is_connected(); // return true if graph is connect and false if not
        unsigned int dijkstra(); // find the least cost path between node_fro and node_to
        void path_print() const; // print the path found, if any
        int path_size() const; // return the least cost path distance
        void path_size_print() const; // print the path distance, if found

    protected:

    private:
        Graph graph;
        unsigned int node_fro;
        unsigned int node_to;
        int min_distance;
        GraphSortedNodeDistanceList open_set;
        GraphSortedNodeDistanceList closed_set;
};

#endif // SHORTESTPATH_H
