#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph g(5);
    g.Addedge(1, 0, 1);
    g.Addedge(1, 1, 2);
    g.Addedge(1, 2, 4);
    g.Addedge(1, 3, 4);
    if (g.Isconnected())
        cout << "connected" << endl;
    else
        cout << "unconnected" << endl;
    cout << "Hello world!" << endl;
    return 0;
}
