#include "Graph.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <assert.h>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <iterator>
using namespace std;

Graph::Graph(const unsigned int& num_nodes):dist_matrix(num_nodes, vector<double>(num_nodes, 0.0))
{
    //ctor
    this->num_nodes = num_nodes;

    #ifdef DEBUG
        cout << "[Graph] created graph of size " << num_nodes << endl;
    #endif
}

Graph::Graph(const unsigned int& num_nodes, const double& edge_density, const double& min_distance, const double& max_distance):
    num_nodes(num_nodes), dist_matrix(num_nodes, vector<double>(num_nodes, 0))
{
    //ctor
    randomize(edge_density, min_distance, max_distance);

    #ifdef DEBUG
        cout << "[Graph] created graph of size [" << num_nodes << "], edge density [" << edge_density;
        cout << "], distance range [" << min_distance << "," << max_distance << "]" << endl;
    #endif
}

Graph::Graph(string graph_file_name)
{
    int num_nodes = 0, src_node, dst_node;
    double dist;

    // graph_file from file name in parameter
    ifstream graph_file(graph_file_name.c_str());

    // read first line indicating number of nodes
    graph_file >> num_nodes;

    #ifdef DEBUG
    cout << "[Graph] [File] number of nodes: " << num_nodes << "\n";
    #endif

    add_node(num_nodes);

    // while not end-of-file, get origin node, destination node and distance
    while(graph_file)
    {
        graph_file >> src_node >> dst_node >> dist;

        #ifdef DEBUG
        cout << "[Graph] [File] " << src_node << "->" << dst_node << "=" << dist << "\n";
        #endif

        add_edge(src_node, dst_node, dist);
    }

    graph_file.close();
}

Graph::~Graph()
{
    //dtor
    num_nodes = 0;
    num_edges = 0;
    dist_matrix.clear();

    #ifdef DEBUG
    cout << "[Graph] deleted all" << endl;
    #endif
}

Graph::Graph(const Graph& other)
{
    //copy ctor
    num_nodes = other.num_nodes;
    num_edges = other.num_edges;
    dist_matrix = other.dist_matrix;

    #ifdef DEBUG
    cout << "[Graph] called copy constructor" << endl;
    #endif // DEBUG
}

Graph& Graph::operator=(const Graph& other)
{
    //assignment operator
    #ifdef DEBUG
    cout << "[Graph] called assignment operator= overload" << endl;
    #endif // DEBUG

    if (this == &other) return *this; // handle self assignment
    else
    {
        num_nodes = other.num_nodes;
        num_edges = other.num_edges;
        dist_matrix = other.dist_matrix;
    }
    return *this;
}

//C++11 move constructor
Graph::Graph(Graph&& other):num_nodes(0), num_edges(0), dist_matrix()
{
    //move ctor
    #ifdef DEBUG
    cout << "[Graph] called move constructor" << endl;
    #endif // DEBUG

    // two steps
    // pilfer other's resources
    // reset other

    num_nodes = other.num_nodes;
    num_edges = other.num_edges;
    dist_matrix = other.dist_matrix;

    other.num_nodes = 0;
    other.num_edges = 0;
    other.dist_matrix.clear();
}

//C++11 move assignment operator
Graph& Graph::operator=(Graph&& other)
{
    //move operator
    #ifdef DEBUG
    cout << "[Graph] called move operator= overload" << endl;
    #endif // DEBUG

    // four steps
    // release current object resources
    // pilfer other's resources
    // reset other
    // return *this

    if (this!=&other)
    {
        num_nodes = 0;
        num_edges = 0;
        dist_matrix.clear();

        num_nodes = other.num_nodes;
        num_edges = other.num_edges;
        dist_matrix = other.dist_matrix;

        other.num_nodes = 0;
        other.num_edges = 0;
        other.dist_matrix.clear();
    }

    return *this;
}

unsigned int Graph::get_num_nodes() const
{
    return num_nodes;
}

unsigned int Graph::get_num_edges() const
{
    return num_edges;
}

bool Graph::adjacent_nodes(const unsigned int& x, const unsigned int& y)
{
    if ((dist_matrix[x][y] > 0) || (dist_matrix[y][x]))
        return true;
    else
        return false;
}

unsigned int Graph::add_node()
{
    unsigned int new_size = dist_matrix.size();
    vector<double> temp(new_size, 0);

    dist_matrix.push_back(temp);

    return 0;
}

unsigned int Graph::add_node(const unsigned int& num_nodes)
{
    this->num_nodes = num_nodes;

    // resize vector to the new number of rows
    dist_matrix.resize(num_nodes);

    // initialize each row with zero values
    for (unsigned int i = 0; i < num_nodes; i++)
        dist_matrix[i].assign(num_nodes, 0.0);

    return 0;
}


bool Graph::rem_node(const unsigned int& node)
{
    if (node >= dist_matrix.size())
        return false;

    // update number of edges
    // each edge going out of "node" will be subtracted
    for (vector<double>::iterator it = (dist_matrix.begin()+node)->begin(); it != (dist_matrix.begin()+node)->end(); it++)
        if ((*it) > 0) num_edges--;

    // each line will have one less column at the position of node
    for (vector<vector<double>>::iterator it = dist_matrix.begin(); it != dist_matrix.end(); it++)
    {
        (*it).erase((*it).begin()+node);
    }

    // then, remove the line for the node we want to remove
    dist_matrix.erase(dist_matrix.begin()+node);

    // update number of nodes
    num_nodes--;

    #ifdef DEBUG
    cout << "[Graph] removed node " << node << " from graph" << endl;
    #endif // DEBUG

    return true;
}

bool Graph::add_edge(const unsigned int& x, const unsigned int& y, const double& distance)
{
    // consistency checks
    if (x == y)
        return false;
    if ((x > num_nodes)
        || (y > num_nodes))
        return false;
    if (distance < 0.0)
        return false;

    num_edges++;

    dist_matrix[x][y] = distance;
    dist_matrix[y][x] = distance;

    #ifdef DEBUG
    cout << "[Graph] added edge from " << x << " to " << y << " = " << distance << endl;
    #endif // DEBUG

    return true;
}

bool Graph::rem_edge(const unsigned int& x, const unsigned int& y)
{
    if (dist_matrix[x][y] == 0)
        return false;

    dist_matrix[x][y] = 0;
    dist_matrix[y][x] = 0;
    num_edges--;

    return true;
}

double Graph::get_edge_value(const unsigned int& x, const unsigned int& y) const
{
    if ((x >= num_nodes) || (y >= num_nodes))
        return 0;

    return dist_matrix[x][y];
}

bool Graph::set_edge_value(const unsigned int& x, const unsigned int& y, const double& distance)
{
    if ((x >= num_nodes) || (y >= num_nodes))
        return false;
    if (distance < 0.0)
        return false;

    dist_matrix[x][y] = distance;

    return true;
}

void Graph::print() const
{
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);

    for (vector<vector<double>>::const_iterator line_it = dist_matrix.begin(); line_it != dist_matrix.end(); line_it++)
    {
        for (vector<double>::const_iterator col_it = (*line_it).begin(); col_it != (*line_it).end(); col_it++)
        {
            cout << setw(5) << *col_it << " ";
        }
        cout << endl;
    }
}

double Graph::operator () (const unsigned int& node_from, const unsigned int& node_to)
{
    return dist_matrix[node_from][node_to];
}

double Graph::prob()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

double Graph::prob_range(const double& min_distance, const double& max_distance)
{
    return static_cast<double>(min_distance + static_cast <double> (rand()) / (static_cast<double>(RAND_MAX / (max_distance - min_distance))));
}

void Graph::randomize(const double& edge_density, const double& min_distance, const double& max_distance)
{
	srand(time(0)); // seed rand()

	for (unsigned int i = 0; i < num_nodes; ++i)
	{
		for (unsigned int j = i; j < num_nodes; ++j)
		{
			if (i == j) dist_matrix[i][j] = 0.0; // no loops
			else if (prob() < edge_density)
            {
                num_edges++;
                dist_matrix[i][j] = dist_matrix[j][i] = prob_range(min_distance, max_distance);
            }
		}
	}
}


bool Graph::is_connected()
{
    int old_size = 0, c_size = 0;
    const int size = get_num_nodes();

    vector<bool> close(size, false);
    vector<bool> open(size, false);

    open[0] = true;

    while (c_size < size)
    {
        for (int i = 0; i < size; ++i)
        {
            old_size = c_size;
            if (open[i] && (close[i] == false))
            {
                close[i] = true;
                c_size++;

                for (int j = 0; j < size; ++j)
                    open[j] = open[j] || (get_edge_value(i, j) > 0.0);
            }

        }

        #ifdef DEBUG_ITER
        cout << "c_size: " << c_size << " size: " << size << endl;
        #endif // DEBUG_ITER
        if (c_size == size)
        {
            return true; // connected
        }
        if (old_size == c_size)
        {
            return false; // unconnected
        }
    }

    return false;
}
