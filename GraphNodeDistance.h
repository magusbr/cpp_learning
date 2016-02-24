#ifndef GRAPHNODEDISTANCE_H
#define GRAPHNODEDISTANCE_H


class GraphNodeDistance
{
    public:
        // constructor / destructor
        GraphNodeDistance(const unsigned int& node_orig, const unsigned int& node_dest, const double& node_dist, const bool& closed = false):
            node_orig(node_orig), node_dest(node_dest), node_dist(node_dist) { }
        virtual ~GraphNodeDistance();

        // getter / setters
        inline unsigned int get_origin() const { return node_orig; } ;
        inline unsigned int get_destiny() const { return node_dest; } ;
        inline double get_distance() const { return node_dist; } ;
        void set_origin(unsigned int orig) { node_orig = orig; }
        void set_destiny(unsigned int dest) { node_dest = dest; }
        void set_distance(double dist) { node_dist = dist; }

        // return true if the current GraphNodeDistance is less than graph_node_distance
        bool compare(const GraphNodeDistance& graph_node_distance) const;

        // overloaded operators
        // cast int gets the destiny node
        operator unsigned int() const;

    protected:

    private:
        unsigned int node_orig;
        unsigned int node_dest;
        double node_dist;
};

#endif // GRAPHNODEDISTANCE_H
