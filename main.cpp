#include <iostream>
#include "Graph.h"

using namespace std;

void IraPohlGraph(Graph& g)
{
    g.Addedge(4, 0, 1);
    g.Addedge(3, 0, 2);
    // original g.Addedge(7, 0, 4);
    g.Addedge(7, 0, 4);
    g.Addedge(1, 1, 3);
    // original g.Addedge(4, 2, 4);
    g.Addedge(4, 2, 4);
    g.Addedge(3, 3, 4);
    g.Addedge(1, 3, 5);
    g.Addedge(1, 4, 5);
    g.Addedge(5, 4, 6);
    g.Addedge(3, 4, 8);
    g.Addedge(2, 5, 7);
    // orignal: g.Addedge(4, 5, 8);
    g.Addedge(4, 5, 8);
    g.Addedge(5, 6, 8);
    g.Addedge(3, 7, 8);
}

void GraphEasiest(Graph& g)
{
    g.Addedge(4, 0, 1);
    g.Addedge(3, 0, 2);
    // original g.Addedge(7, 0, 4);
    g.Addedge(7, 0, 4);
    g.Addedge(1, 1, 3);
    // original g.Addedge(4, 2, 4);
    g.Addedge(4, 2, 4);
    g.Addedge(3, 3, 4);
    g.Addedge(1, 3, 5);
    g.Addedge(1, 4, 5);
    g.Addedge(5, 4, 6);
    g.Addedge(3, 4, 8);
    g.Addedge(2, 5, 7);
    // orignal: g.Addedge(4, 5, 8);
    g.Addedge(5, 5, 8);
    g.Addedge(5, 6, 8);
    g.Addedge(3, 7, 8);
}

void GraphHarder(Graph& g)
{
    g.Addedge(4, 0, 1);
    g.Addedge(3, 0, 2);
    // original g.Addedge(7, 0, 4);
    g.Addedge(8, 0, 4);
    g.Addedge(1, 1, 3);
    // original g.Addedge(4, 2, 4);
    g.Addedge(5, 2, 4);
    g.Addedge(3, 3, 4);
    g.Addedge(1, 3, 5);
    g.Addedge(1, 4, 5);
    g.Addedge(5, 4, 6);
    g.Addedge(3, 4, 8);
    g.Addedge(2, 5, 7);
    // orignal: g.Addedge(4, 5, 8);
    g.Addedge(5, 5, 8);
    g.Addedge(5, 6, 8);
    g.Addedge(3, 7, 8);
}


void GraphMST2ndClass(Graph& g)
{
    g.Addedge(4, 0, 1);
    g.Addedge(8, 0, 7);
    g.Addedge(11, 1, 7);
    g.Addedge(7, 7, 8);
    g.Addedge(1, 6, 7);
    g.Addedge(6, 6, 8);
    g.Addedge(8, 1, 2);
    g.Addedge(2, 2, 8);
    g.Addedge(4, 2, 5);
    g.Addedge(2, 5, 6);
    g.Addedge(7, 2, 3);
    g.Addedge(14, 3, 5);
    g.Addedge(4, 2, 5);
    g.Addedge(9, 3, 4);
    g.Addedge(10, 4, 5);
}

int main()
{
    /*Graph g(5);
    g.Addedge(1, 0, 1);
    g.Addedge(1, 1, 2);
    g.Addedge(1, 2, 4);
    g.Addedge(1, 3, 4);
    if (g.Isconnected())
        cout << "connected" << endl;
    else
        cout << "unconnected" << endl;
    //cout << "Hello world!" << endl;
    g.DjikstraShortestPath(0, 3);
    */
    Graph g(9);
    //GraphEasiest(g);
    GraphMST2ndClass(g);

    //g.DjikstraShortestPath(0, 8);
    g.JarnikPrimMST();

    return 0;
}


