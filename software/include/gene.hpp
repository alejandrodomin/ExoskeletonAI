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

      float weight;     /**<The weight a gene carries in the forward propagation function. */

      Node* you_node;   /**<A pointer corresponding to the node that holds this gene. */
      Node* input_node; /**<A pointer to the Node that is connected to the you_node. */
   protected:
   public:
      Gene();
      Gene(Node *, Node *);
      ~Gene();

      void set_weight(float);

      float get_weight();

      Node* get_you_node();
      Node* get_input_node();
};

#endif
