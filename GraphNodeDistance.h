#ifndef GRAPHNODEDISTANCE_H
#define GRAPHNODEDISTANCE_H


class GraphNodeDistance
{
    public:
        // constructor / destructor
        GraphNodeDistance(unsigned int node_orig, unsigned int node_dest, unsigned int node_dist, bool closed = false):
            node_orig(node_orig), node_dest(node_dest), node_dist(node_dist), closed(closed) { }
        virtual ~GraphNodeDistance();

        // getter / setters
        unsigned int get_origin() const { return node_orig; } ;
        unsigned int get_destiny() const { return node_dest; } ;
        unsigned int get_distance() const { return node_dist; } ;
        bool is_closed() const { return closed; } ;
        void set_origin(unsigned int orig) { node_orig = orig; }
        void set_destiny(unsigned int dest) { node_dest = dest; }
        void set_distance(unsigned int dist) { node_dist = dist; }

        void set_closed();
        void set_opened();
        // return true if the current GraphNodeDistance is less than graph_node_distance
        bool compare(const GraphNodeDistance& graph_node_distance) const;

        // overloaded operators
        // cast int gets the destiny node
        operator int();

    protected:

    private:
        unsigned int node_orig;
        unsigned int node_dest;
        unsigned int node_dist;
        bool closed;
};

#endif // GRAPHNODEDISTANCE_H
