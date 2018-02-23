#ifndef GENE_HPP
#define GENE_HPP

/** @brief Class for the genes in a network.

    This class will hold of the functions that deal
    with genes, and their necessary actions.
    @author Dominguez, Alejandro
    @date Feburary, 2018
    */

#include <iostream>

using namespace std;

#include "node.hpp"
class Node;

class Gene{
private:
    int innovation_number;  /**<The number in which the gene poped up. */

    float weight;

    int input_node;   /**<A pointer corresponding to the node that holds this gene. */
    int output_node; /**<A pointer to the Node that is connected to the you_node. */
protected:
public:
    Gene(int,int,int);
    ~Gene();

    int get_inov_id() const;

    float get_weight() const;

    int get_input_node() const;
    int get_output_node() const;
};

#endif
