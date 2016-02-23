#ifndef GRAPHMONTECARLO_H
#define GRAPHMONTECARLO_H

#include "Graph.h"
#include "GraphShortestPath.h"
#include <vector>
#include <iostream>

using namespace std;

class GraphMonteCarlo
{
    public:
        GraphMonteCarlo();
        GraphMonteCarlo(const unsigned int& num_nodes, const double& density, const double& min_dist, const double& max_dist);
        virtual ~GraphMonteCarlo();

        double calculate_average_shortest_path();
        double get_average_shortest_path();

    protected:

    private:
        unsigned int num_nodes;
        double density;
        double min_dist;
        double max_dist;
        double average;

        Graph graph;
};

#endif // GRAPHMONTECARLO_H
