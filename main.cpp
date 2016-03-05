#include <iostream>
#include "Graph.h"
//#include "homework1.h"
#include "GraphShortestPath.h"
#include "GraphSortedNodeDistanceList.h"
#include "GraphMonteCarlo.h"
#include "GraphMinimumSpanningTree.h"

using namespace std;

int main(int argc, char** argv)
{
/*
    // Homework 2 - 0.2 Density Graph
    GraphMonteCarlo gmc_02 = GraphMonteCarlo(50, 0.2, 1.0, 10.0);

    gmc_02.calculate_average_shortest_path();
    gmc_02.get_average_shortest_path();

    // Homework 2 - 0.4 Density Graph
    GraphMonteCarlo gmc_04 = GraphMonteCarlo(50, 0.4, 1.0, 10.0);

    gmc_04.calculate_average_shortest_path();
    gmc_04.get_average_shortest_path();
*/

    // Homework 3 - MST
    Graph graph_from_file("mst_data");
    graph_from_file.print();
    GraphMinimumSpanningTree gmst(graph_from_file, 0);
    gmst.jarnik_prim();
    gmst.path_size_print();

    for (unsigned int i = 1; i < graph_from_file.get_num_nodes(); i++)
    {
        gmst.path_print(i);
    }


    return 0;
}
