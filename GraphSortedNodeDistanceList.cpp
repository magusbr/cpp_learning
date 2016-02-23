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
        {
            return true;
        }
    }

    return false;
}

bool GraphSortedNodeDistanceList::contains(const unsigned int& node)
{
    // check if element destiny is already on sorted list
    for (auto element : distance_queue)
    {
        if ((node == element.get_destiny())
            || (node == element.get_origin()))
        {
            return true;
        }
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
        sort(distance_queue.begin(), distance_queue.end(), GraphSortedNodeDistanceList());
    }
}

// return the least distance element and remove it from list
GraphNodeDistance GraphSortedNodeDistanceList::pop()
{
    if (distance_queue.size() > 0)
    {
        vector<GraphNodeDistance>::iterator it = distance_queue.begin();
        GraphNodeDistance ret = (*it);
        distance_queue.erase(it);
        return ret;
    }
    else
    {
        // return null GraphNodeDistance if not found
        GraphNodeDistance ret = GraphNodeDistance(0, 0, 0);
        return ret;
    }
}

// return the most costly element and remove it from list
GraphNodeDistance GraphSortedNodeDistanceList::bottom()
{
    if (distance_queue.size() > 0)
    {
        vector<GraphNodeDistance>::iterator it = distance_queue.begin() + (distance_queue.size()-1);
        GraphNodeDistance ret = (*it);
        distance_queue.erase(it);
        return ret;
    }
    else
    {
        // return null GraphNodeDistance if not found
        GraphNodeDistance ret = GraphNodeDistance(0, 0, 0);
        return ret;
    }
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

void GraphSortedNodeDistanceList::requeue_on_less_distance(const GraphNodeDistance& node_distance)
{
    // only makes sense when element is already in list
    for (auto it = distance_queue.begin(); it != distance_queue.end(); it++)
    {
        if (node_distance.get_destiny() == (*it).get_destiny())
        {
            if ((*it).get_distance() > node_distance.get_distance())
            {
                distance_queue.erase(it);
                push(node_distance);
            }
            break;
        }
    }
}

unsigned int GraphSortedNodeDistanceList::size()
{
    return distance_queue.size();
}

void GraphSortedNodeDistanceList::print() const
{
    for (auto element : distance_queue)
    {
        cout << element.get_origin() << "->" << element << "(" << element.get_distance() << ") ";
    }
    cout << endl;
}

void GraphSortedNodeDistanceList::clear()
{
    distance_queue.clear();
}
