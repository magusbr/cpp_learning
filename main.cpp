#include <iostream>
#include "Graph.h"

using namespace std;

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
    g.Addedge(4, 0, 1);
    g.Addedge(3, 0, 2);
    // original g.Addedge(7, 0, 4);
    g.Addedge(7, 0, 4);
    //g.Addedge(8, 0, 4);
    g.Addedge(1, 1, 3);
    // original g.Addedge(4, 2, 4);
    g.Addedge(4, 2, 4);
    //g.Addedge(5, 2, 4);
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

    g.DjikstraShortestPath(0, 8);
    return 0;
}
