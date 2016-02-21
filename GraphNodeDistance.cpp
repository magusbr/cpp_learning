#include "GraphNodeDistance.h"

GraphNodeDistance::~GraphNodeDistance()
{
    //dtor
}


void GraphNodeDistance::set_closed()
{
    closed = true;
}

void GraphNodeDistance::set_opened()
{
    closed = false;
}

// cast int gets the destiny node
GraphNodeDistance::operator int()
{
    return node_dest;
}

// const method won't change object state
// compare two distances for sorting them
bool GraphNodeDistance::compare(const GraphNodeDistance& graph_node_distance) const
{
    return (this->node_dist < graph_node_distance.node_dist);
}
