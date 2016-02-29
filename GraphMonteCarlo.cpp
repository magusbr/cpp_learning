#include "GraphMonteCarlo.h"

GraphMonteCarlo::GraphMonteCarlo(const unsigned int& num_nodes, const double& density, const double& min_dist, const double& max_dist):
    num_nodes(num_nodes), density(density), min_dist(min_dist), max_dist(max_dist), graph(num_nodes, density, min_dist, max_dist)
{
    //ctor
    cout << "[GraphMonteCarlo] creating a Graph with: [" << num_nodes << "] nodes, density [" << density;
    cout << "] and distance interval [" << min_dist << "," << max_dist << "]" << endl;

    graph.print();
}

GraphMonteCarlo::GraphMonteCarlo():
    GraphMonteCarlo(50, 0.4, 1.0, 10.0)
{}

GraphMonteCarlo::~GraphMonteCarlo()
{
    //dtor
}

double GraphMonteCarlo::calculate_average_shortest_path()
{
    double sum = 0.0;
    double average = 0.0;

    if (!graph.is_connected())
    {
        cout << "[GraphMonteCarlo] can't continue. Graph is disconnected" << endl;
        return (this->average = 0.0);
    }

    GraphShortestPath gsp = GraphShortestPath(graph, 0);
    gsp.dijkstra_all();

    for (unsigned int i = 1; i < num_nodes; i++)
    {
        sum += gsp.path_size(i);
        cout << "[GraphMonteCarlo] calculating shortest path from 0->" << i << endl;
        cout << "[GraphMonteCarlo] distance from 0->" << i << "=" << gsp.path_size(i) << endl;
    }

    average = sum / (num_nodes - 1);

    return (this->average = average);
}


double GraphMonteCarlo::get_average_shortest_path()
{
    cout << "[GraphMonteCarlo] average distance is [" << average << "]." << endl;
    return average;
}
