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

        // methods
        unsigned int get_num_nodes(); // returns the number of nodes in the graph
        unsigned int get_num_edges(); // returns the number of edges in the graph
        bool adjacent_nodes(unsigned int& x, unsigned int& y); //tests whether there is an edge from node x to node y
        unsigned int add_node(); // add node to graph
        bool rem_node(unsigned int& node); // remove node from graph
        //bool add_edge(unsigned int x, unsigned int y, unsigned int distance); // adds to graph the edge from x to y, if it is not there.
        bool add_edge(const unsigned int& x, const unsigned int& y, const unsigned int& distance); // adds to graph the edge from x to y, if it is not there.
        bool rem_edge(unsigned int& x, unsigned int& y); // removes the edge from x to y, if it is there.
        unsigned int get_edge_value(unsigned int& x, unsigned int& y); // returns the value associated to the edge (x,y).
        bool set_edge_value(unsigned int& x, unsigned int& y, unsigned int& distance); // sets the value associated to the edge (x,y) to distance.

        bool Isconnected();
        int DjikstraShortestPath(unsigned int fro, unsigned int to);
        int JarnikPrimMST();
        // TODO
        // implement copy constructor, operator
        // implement move constructor, operator
        // test "explicit" keyword
        // conversion to basic data type overloading ()
        // friend functions

        //C++11
        //nullptr
        //move constructor

    protected:
        typedef struct node_distance_t
        {
            unsigned int from;
            unsigned int to;
            int distance;
            bool visited;
        } node_distance_t;

        struct compare_node_distance_t
        {
            inline bool operator() (const node_distance_t& struct1, const node_distance_t& struct2)
            {
                return (struct1.distance < struct2.distance);
            }
        };
    private:
        unsigned int m_nodes;
        unsigned int m_edges;
        int** m_graph;
};

#endif // GRAPH_H
