#include "GraphFileRead.h"
#include "Graph.h"

using namespace std;

GraphFileRead::GraphFileRead(string graph_file_name):
    graph_file_name(graph_file_name), graph_file(graph_file_name), graph()
{
    //ctor
}

GraphFileRead::~GraphFileRead()
{
    //dtor
}
