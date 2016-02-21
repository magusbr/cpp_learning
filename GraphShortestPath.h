#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Graph.h"
#include "GraphSortedNodeDistanceList.h"

class GraphShortestPath
{
    public:
        GraphShortestPath(const Graph& graph, const unsigned int& node_fro, const unsigned int& node_to);
        virtual ~GraphShortestPath();
        bool Isconnected();
        int DjikstraShortestPath(unsigned int fro, unsigned int to);
        int JarnikPrimMST();
        unsigned int dijkstra();

    protected:

    private:
        Graph graph;
        unsigned int node_fro;
        unsigned int node_to;
        GraphSortedNodeDistanceList open_set;

        typedef struct node_distance_t
        {
            unsigned int from;
            unsigned int to;
            unsigned int distance;
            bool visited;
        } node_distance_t;

        struct compare_node_distance_t
        {
            inline bool operator() (const node_distance_t& struct1, const node_distance_t& struct2)
            {
                return (struct1.distance < struct2.distance);
            }
        };
};

#endif // SHORTESTPATH_H
