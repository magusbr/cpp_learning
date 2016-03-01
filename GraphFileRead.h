#ifndef GRAPHFILEREAD_H
#define GRAPHFILEREAD_H

#include "Graph.h"
#include "GraphShortestPath.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class GraphFileRead
{
    public:
        GraphFileRead(string graph_file_name);
        virtual ~GraphFileRead();

        Graph& get_graph();

    protected:
        string graph_file_name;
        ifstream graph_file;
        Graph graph;

    private:
};

#endif // GRAPHFILEREAD_H

