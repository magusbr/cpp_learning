#include <iostream>
#include "Graph.h"
#include "homework1.h"
#include "GraphShortestPath.h"
#include "GraphSortedNodeDistanceList.h"
#include "GraphMonteCarlo.h"

using namespace std;

int main(int argc, char** argv)
{
    GraphMonteCarlo gmc = GraphMonteCarlo();

    gmc.calculate_average_shortest_path();
    gmc.get_average_shortest_path();
}
