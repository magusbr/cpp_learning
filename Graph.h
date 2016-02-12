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
        // TODO
        // implement copy constructor, operator
        // implement move constructor, operator

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
