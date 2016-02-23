#include <iostream>
#include "Graph.h"
#include "homework1.h"
#include "GraphShortestPath.h"
#include "GraphSortedNodeDistanceList.h"

using namespace std;

int main(int argc, char** argv)
{
    Graph g = Graph(50, 0.4, 1, 10);
    g.print();
    return 0;
}
