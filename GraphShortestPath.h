#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Graph.h"

class GraphShortestPath
{
    public:
        GraphShortestPath(Graph* graph_ptr);
        virtual ~GraphShortestPath();
        bool Isconnected();
        int DjikstraShortestPath(unsigned int fro, unsigned int to);
        int JarnikPrimMST();

    protected:

    private:
        Graph* graph_ptr;

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
