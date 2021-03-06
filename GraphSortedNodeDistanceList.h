#ifndef GRAPHSORTEDNODEDISTANCELIST_H
#define GRAPHSORTEDNODEDISTANCELIST_H

#include <vector>
#include "GraphNodeDistance.h"

using namespace std;

class GraphSortedNodeDistanceList
{
    public:
        GraphSortedNodeDistanceList();
        virtual ~GraphSortedNodeDistanceList();

        void push(const GraphNodeDistance& node_distance); // insert element in the sorted list at adequate position
        GraphNodeDistance pop(); // remove top (less distance) from the sorted list
        GraphNodeDistance bottom(); // remove bottom (most costly) element from the sorted list
        unsigned int size(); // return number of elements in sorted list
        bool contains(const GraphNodeDistance& node_distance); // return true if element is in sorted list
        bool contains(const unsigned int& node); // return true if node is in sorted list, in any direction (node as origin or destiny)
        void requeue(const GraphNodeDistance& node_distance); // change priority of sorted list element, reordering its position
        void requeue_on_less_distance(const GraphNodeDistance& node_distance); // change priority of sorted list element, reordering its position
        bool operator() (const GraphNodeDistance& graph_distance1, const GraphNodeDistance& graph_distance2); // used to sort the list
        void print() const;
        void clear();

    protected:

    private:
        vector<GraphNodeDistance> distance_queue;
};

#endif // GRAPHSORTEDNODEDISTANCELIST_H
