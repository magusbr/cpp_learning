#include <iostream>
#include "Graph.h"
#include "homework1.h"
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
    Graph g(9);    
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    // original g.add_edge(0, 4, 7);
    g.add_edge(0, 4, 7);
    g.add_edge(1, 3, 1);
    // original g.add_edge(2, 4, 4);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 4, 3);
    g.add_edge(3, 5, 1);
    g.add_edge(4, 5, 1);
    g.add_edge(4, 6, 5);
    g.add_edge(4, 8, 3);
    g.add_edge(5, 7, 2);
    // orignal: g.add_edge(5, 8, 4);
    g.add_edge(5, 8, 4);
    g.add_edge(6, 8, 5);
    g.add_edge(7, 8, 3);

    GraphShortestPath gsp(g, 0);
    gsp.dijkstra_all();
    for (unsigned int i = 1; i < g.get_num_nodes(); i++)
    {
        gsp.path_print(i);
    }

    cout << endl;

    GraphMinimumSpanningTree gmst(g, 0);
    gmst.jarnik_prim();
    gmst.path_size_print();

    for (unsigned int i = 1; i < g.get_num_nodes(); i++)
    {
        gmst.path_print(i);
    }


    Graph g2("mst_data");

    return 0;
}
