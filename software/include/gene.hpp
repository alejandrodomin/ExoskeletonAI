#ifndef GENE_HPP
#define GENE_HPP

#include <iostream>

using namespace std;

#include "node.hpp"
class Node;

class Gene{
   private:
      int innovation_number;

      float weight;

      Node* you_node;
      Node* input_node;
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
