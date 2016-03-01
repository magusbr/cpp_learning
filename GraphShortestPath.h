#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Graph.h"
#include "GraphSortedNodeDistanceList.h"

class GraphShortestPath
{
    public:
        GraphShortestPath(const Graph& graph, const unsigned int& node_fro, const unsigned int& node_to);
        GraphShortestPath(const Graph& graph, const unsigned int& node_fro);
        virtual ~GraphShortestPath();
        double dijkstra(); // find the least cost path between node_fro and node_to
        void dijkstra_all(); // find the least cost path between node_fro and all other nodes
        void path_print(const unsigned int& to_node) const; // print the path found, if any
        double path_size() const; // return the least cost path distance
        double path_size(const unsigned int& to_node) const; // return the least cost path distance to to_node
        void path_size_print() const; // print the path distance, if found
        void path_size_print(const unsigned int& to_node) const;

    protected:
        Graph graph;
        unsigned int node_fro;
        unsigned int node_to;
        vector<double> min_distance;
        GraphSortedNodeDistanceList open_set;
        GraphSortedNodeDistanceList closed_set;

    private:
};

#endif // SHORTESTPATH_H
