#ifndef NODE_HPP
#define NODE_HPP

/** @brief Class for the nodes in a network.

    This class will hold of the functions that deal
    with nodes, and their necessary actions.
    @author Dominguez, Alejandro
    @date Feburary, 2018
    */

#include <iostream>
#include <mutex>
#include <thread>
#include <list>

#include <boost/thread.hpp>

#include <common.hpp>
#include <gene.hpp>
class Gene;

using namespace std;

class Node{
private:
    int type;       /**<The type of node it is depending on the enum type. */
    int layer;      /**<If it is a hidden node this says which layer it is in. */
    int node_id;    /**<The identification number for the node. */

    float bias;         /**<The weight we put on a node in the network. */
    float output_func;  /**<The output of the node after we apply forward propogation. */

    static mutex mtx;  /**<Locks the functions that the threads will be accessing to avoid seg faults. */
protected:
public:
    Node();
    Node(int,int);
    ~Node();

    bool set_layer(int);
    bool set_outputfunc(float);
    bool out_func(list<Gene *>);
    bool find_layer(list<Gene *>);

    int get_layer() const;
    int get_type() const;
    int get_nodeid() const;

    float get_bias() const;
    float get_outputfunc() const;

    boost::thread* spawn_thread(list<Gene *>);
};
#endif
