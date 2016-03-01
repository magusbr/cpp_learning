#ifndef GRAPHMINIMUMSPANNINGTREE_H
#define GRAPHMINIMUMSPANNINGTREE_H

#include "Graph.h"
#include "GraphShortestPath.h"
#include <vector>
#include <iostream>

using namespace std;

class GraphMinimumSpanningTree : public GraphShortestPath
{
    public:
        GraphMinimumSpanningTree(const Graph& graph, const unsigned int& node_fro);
        virtual ~GraphMinimumSpanningTree();

        double jarnik_prim();
        // override inherited path_print and path_size function
        void path_print(const unsigned int&) const;
        double path_size() const;
        void path_size_print() const;

    protected:
        double mst_distance;

    private:
};

#endif // GRAPHMINIMUMSPANNINGTREE_H

