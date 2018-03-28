#ifndef NETWORK_HPP
#define NETWORK_HPP

/** @brief Class for the Networks in a species.

    This class will hold of the functions that deal
    with networks, and their necessary actions.
    @author Dominguez, Alejandro
    @date Feburary, 2018
    */

#include <iostream>
#include <thread>
#include <list>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <LSM9DS1_Types.hpp>
#include <LSM9DS1.hpp>
#include <gyrscope.hpp>

#include <common.hpp>
#include <node.hpp>
#include <gene.hpp>

using namespace std;

class Network{
private:
    int crashes; 
    int fitness; /**<The fitness level of a set of input nodes.*/
    int num_nodes; /**<The number of nodes.*/ 

    float walk_distance;  
    float compatibility_distance;/**<Measures how compatible a set of nodes is.*/

    float **gyro;
    float **accel;
    float **magno;

    LSM9DS1 *gyros;

    list<Gene *> genes; /**<List for all of the genes associated with the node. */

    list<Node *> in_nodes; /**<the input nodes*/
    list<Node *> out_nodes; /**<output nodes*/
    list<Node *> hidden_nodes; /**<hidden nodes*/

    list<boost::thread *> threads;/**<A double pointer to the threads that have been created.*/  
protected:
    void input_run();
    void hidden_run();
    void output_run();
public:
    Network();
    ~Network(); // destructor deletes heap memory

    void run();
    void mutate();
    void use_output();
    void calculate_fit();
    void add_num_nodes(int);
    void set_compatibility_distance(float);
    void add_gene(Node *, Node *);

    int get_fitness() const;
    int get_maxlayer() const;
    int get_num_nodes() const;

    float get_compatibility_distance() const;

    bool rand_node();
    bool rand_connection();
      
    static bool compare(const Node *, const Node *);

    list<Gene *>* get_genes(); 

    list<Node *>* get_input();       // names for these can be changed later
    list<Node *>* get_output();
    list<Node *>* get_hiddennodes(); 
};

#endif
