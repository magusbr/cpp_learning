#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Graph.h"
#include "GraphSortedNodeDistanceList.h"

class GraphShortestPath
{
    public:
        GraphShortestPath(const Graph& graph, const unsigned int& node_fro, const unsigned int& node_to);
        virtual ~GraphShortestPath();
        double dijkstra(); // find the least cost path between node_fro and node_to
        double dijkstra_all(); // find the least cost path between node_fro and all other nodes
        void path_print() const; // print the path found, if any
        double path_size() const; // return the least cost path distance
        void path_size_print() const; // print the path distance, if found

    protected:

    private:
        Graph graph;
        unsigned int node_fro;
        unsigned int node_to;
        double min_distance;
        GraphSortedNodeDistanceList open_set;
        GraphSortedNodeDistanceList closed_set;
};

#endif // SHORTESTPATH_H
