#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    public:
        Graph(unsigned int val);
        virtual ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);

        int Addedge(unsigned int val, unsigned int node1, unsigned int node2);
        unsigned int Getnodes() { return m_nodes; }
        unsigned int Getedges() { return m_edges; }
        int** Getgraph() { return m_graph; }
        void Setgraph(int** val) { m_graph = val; }
        bool Isconnected();
        int DjikstraShortestPath(unsigned int fro, unsigned int to);
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
