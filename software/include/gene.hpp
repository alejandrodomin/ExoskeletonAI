#ifndef GENE_HPP
#define GENE_HPP

/** @brief Class for the genes in a network.

    This class will hold of the functions that deal
    with genes, and their necessary actions.
    @author Dominguez, Alejandro
    @date Feburary, 2018
    */

#include <iostream>
#include <memory>

using namespace std;

#include "node.hpp"
class Node;

class Gene{
private:
    int in_node;
    int out_node;
    int innovation_number;  /**<The number in which the gene poped up. */

    float weight;

    Node* input_node;   /**<A pointer corresponding to the node that holds this gene. */
    Node* output_node; /**<A pointer to the Node that is connected to the you_node. */
protected:
public:
    Gene(unique_ptr<Node>,unique_ptr<Node>,int);
    ~Gene();

    int get_inov_id() const;
    int get_in_node() const;
    int get_out_node() const;

    float get_weight() const;


    Node* get_input_node() const;
    Node* get_output_node() const;
};

#endif
