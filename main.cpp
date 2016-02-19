#include <iostream>
#include "Graph.h"
#include "homework1.h"

using namespace std;

void GraphIraPohl(Graph& g)
{
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
}

void GraphEasiest(Graph& g)
{
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
    g.add_edge(5, 8, 5);
    g.add_edge(6, 8, 5);
    g.add_edge(7, 8, 3);
}

void GraphHarder(Graph& g)
{
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    // original g.add_edge(0, 4, 7);
    g.add_edge(0, 4, 8);
    g.add_edge(1, 3, 1);
    // original g.add_edge(2, 4, 4);
    g.add_edge(2, 4, 5);
    g.add_edge(3, 4, 3);
    g.add_edge(3, 5, 1);
    g.add_edge(4, 5, 1);
    g.add_edge(4, 6, 5);
    g.add_edge(4, 8, 3);
    g.add_edge(5, 7, 2);
    // orignal: g.add_edge(5, 8, 4);
    g.add_edge(5, 8, 5);
    g.add_edge(6, 8, 5);
    g.add_edge(7, 8, 3);
}


void GraphMST2ndClass(Graph& g)
{
    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(7, 8, 7);
    g.add_edge(6, 7, 1);
    g.add_edge(6, 8, 6);
    g.add_edge(1, 2, 8);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(5, 6, 2);
    g.add_edge(2, 3, 7);
    g.add_edge(3, 5, 14);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(4, 5, 10);
}

int main(int argc, char** argv)
{
    /*Graph g(5);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 1);
    g.add_edge(2, 4, 1);
    g.add_edge(3, 4, 1);
    if (g.Isconnected())
        cout << "connected" << endl;
    else
        cout << "unconnected" << endl;
    //cout << "Hello world!" << endl;
    g.DjikstraShortestPath(0, 3);
    */
    Graph g(9);
    GraphIraPohl(g);
    //GraphEasiest(g);
    //GraphHarder(g);
    //GraphMST2ndClass(g);

    //g.DjikstraShortestPath(0, 8);
    //g.JarnikPrimMST();

    homework1::main();

    return 0;
}


