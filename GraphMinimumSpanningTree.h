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

    protected:

    private:
};

#endif // GRAPHMINIMUMSPANNINGTREE_H

