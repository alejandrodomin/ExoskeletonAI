#include <iostream>
#include "global.h"

using namespace std;

#ifndef NETWORK_H
#define NETWORK_H
class Node;

class Network 
{
   private:
      Node **inputs;
      Node **outputs;
      int num_nodes;
      // outputs
   protected:
      Node **nodes;     // points to all the nodes in a network
   public:
      Network();
      ~Network(); // destructor deletes heap memory

      void get_input();       // names for these can be changed later
      void use_output();

      bool rand_node();
      bool rand_connection();
};

#endif