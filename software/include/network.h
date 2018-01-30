#include <iostream>
#include <thread>
#include <list>

#include "node.h"

using namespace std;

#ifndef NETWORK_H
#define NETWORK_H

class Network 
{
   private:
      int num_nodes;

      Node **in_nodes; // the input nodes
      list<Node *> hidden_nodes;
      Node **out_nodes; // output nodes

      thread **threads;
      // outputs
   protected:
      void input_run();
      void hidden_run();
      void output_run();

   public:
      Network();
      ~Network(); // destructor deletes heap memory

      Node** get_input();       // names for these can be changed later
      void use_output();

      void run();

      void set_num_nodes(int);
      int get_num_nodes();

      bool add_input_node(int);
      bool add_output_nodes(int);

      bool rand_node();
      bool rand_connection();
};

#endif
