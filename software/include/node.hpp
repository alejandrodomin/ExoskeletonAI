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

#include "gene.hpp"
class Gene;

using namespace std;

enum gyro {gyroX = 0, 
            gyroY, gyroZ};   /**<Enumerated list for 
                             the x,y, and z positions for the gyro. */
enum type {input = 0, 
            hidden, output}; /**<Enumerated list for 
                             the different kinds of nodes.*/ 

class Node{
    private:
        int type;       /**<The type of node it is depending on the enum type. */
        int layer;      /**<If it is a hidden node this says which layer it is in. */
        int node_id;    /**<The identification number for the node. */

        float bias;         /**<The weight we put on a node in the network. */
        float output_func;  /**<The output of the node after we apply forward propogation. */

        mutex out_mut;  /**<Locks the functions that the threads will be accessing to avoid seg faults. */

        list<Gene *> genes; /**<List for all of the genes associated with the node. */
    protected:
    public:
        Node();
        Node(int);
        ~Node();

        void out_func();
        void find_layer();
        void set_outputfunc(float);
        void add_gene(Node *, Node *);

        int get_type();
        int get_nodeid();

        float get_outputfunc();

        thread* spawn_thread();
};
#endif