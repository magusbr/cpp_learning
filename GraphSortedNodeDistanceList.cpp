#include "GraphSortedNodeDistanceList.h"

#include <algorithm>
#include <iostream>
#include "GraphNodeDistance.h"

using namespace std;

GraphSortedNodeDistanceList::GraphSortedNodeDistanceList()
{
    //ctor
}

GraphSortedNodeDistanceList::~GraphSortedNodeDistanceList()
{
    //dtor
}

// use compare function from GraphNodeDistance to compare which distance in list is the least one
bool GraphSortedNodeDistanceList::operator() (const GraphNodeDistance& graph_distance1, const GraphNodeDistance& graph_distance2)
{
    return graph_distance1.compare(graph_distance2);
}

bool GraphSortedNodeDistanceList::contains(const GraphNodeDistance& node_distance)
{
    // check if element destiny is already on sorted list
    for (auto element : distance_queue)
    {
        if (node_distance.get_destiny() == element.get_destiny())
            return true;
    }

    return false;
}

void GraphSortedNodeDistanceList::push(const GraphNodeDistance& node_distance)
{
    // add only if not already there
    if (!contains(node_distance))
    {
        distance_queue.push_back(node_distance);

        // sort after adding
        sort(distance_queue.rbegin(), distance_queue.rend(), GraphSortedNodeDistanceList());
    }
}

// return the least distance element which is not closed
GraphNodeDistance GraphSortedNodeDistanceList::top()
{
    for (auto element : distance_queue)
    {
        if (element.is_closed()) return element;
    }

    // undefined behavior when calling on an empty GraphSortedNodeDistanceList
    return GraphNodeDistance(0, 0, 0);
}

GraphNodeDistance GraphSortedNodeDistanceList::pop()
{

    for (auto it = distance_queue.begin(); it != distance_queue.end(); it++)
    {
        if ((*it).is_closed())
        {
            GraphNodeDistance ret = (*it);
            distance_queue.erase(it);
            return ret;
        }
    }

    // undefined behavior when calling on an empty GraphSortedNodeDistanceList
    return GraphNodeDistance(0, 0, 0);
}

void GraphSortedNodeDistanceList::requeue(const GraphNodeDistance& node_distance)
{
    // only makes sense when element is already in list
    for (auto it = distance_queue.begin(); it != distance_queue.end(); it++)
    {
        if (node_distance.get_destiny() == (*it).get_destiny())
        {
            distance_queue.erase(it);
            break;
        }
    }

    push(node_distance);
}

unsigned int GraphSortedNodeDistanceList::size()
{
    return distance_queue.size();
}

void GraphSortedNodeDistanceList::print()
{
    for (auto element : distance_queue)
    {
        cout << element.get_origin() << "->" << element << "(" << element.get_distance() << ") ";
    }
    cout << endl;
}
