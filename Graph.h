#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    public:
        // constructors and destructors
        Graph():m_nodes(0),m_graph(nullptr) {}; // create an empty graph
        Graph(unsigned int number); // create a graph with number of nodes
        virtual ~Graph(); // delete graph and clean its internal memory
        Graph(const Graph& other); // copy constructor
        Graph& operator=(const Graph& other); // assignment operator
        Graph(Graph&& other); // move constructor (C++11)
        Graph& operator=(Graph&& other); // assignment move operator (C++11)

        // methods
        unsigned int get_num_nodes(); // returns the number of nodes in the graph
        unsigned int get_num_edges(); // returns the number of edges in the graph
        bool adjacent_nodes(const unsigned int& x, const unsigned int& y); //tests whether there is an edge from node x to node y
        unsigned int add_node(); // add node to graph
        bool rem_node(const unsigned int& node); // remove node from graph
        bool add_edge(const unsigned int& x, const unsigned int& y, const unsigned int& distance); // adds to graph the edge from x to y, if it is not there.
        bool rem_edge(const unsigned int& x, const unsigned int& y); // removes the edge from x to y, if it is there.
        unsigned int get_edge_value(const unsigned int& x, const unsigned int& y); // returns the value associated to the edge (x,y).
        bool set_edge_value(const unsigned int& x, const unsigned int& y, const unsigned int& distance); // sets the value associated to the edge (x,y) to distance.
        void delete_graph(); // auxiliary function to destructor and move constructors

        // TODO
        // test "explicit" keyword
        // conversion to basic data type overloading ()
        // friend functions

        //C++11
        //nullptr
        //move constructor

    protected:

    private:
        unsigned int m_nodes;
        unsigned int m_edges;
        int** m_graph;
};

#endif // GRAPH_H
