#include <iostream>
#include "Graph.h"
#include "homework1.h"
#include "GraphShortestPath.h"
#include "GraphSortedNodeDistanceList.h"
#include "GraphMonteCarlo.h"

using namespace std;

int main(int argc, char** argv)
{
    GraphMonteCarlo gmc_02 = GraphMonteCarlo(50, 0.2, 1.0, 10.0);

    gmc_02.calculate_average_shortest_path();
    gmc_02.get_average_shortest_path();

    GraphMonteCarlo gmc_04 = GraphMonteCarlo(50, 0.4, 1.0, 10.0);

    gmc_04.calculate_average_shortest_path();
    gmc_04.get_average_shortest_path();
}
