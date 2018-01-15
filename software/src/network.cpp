#include "network.h"
#include <iostream>
#include <cstdlib>

#define NUM_INPUTS  9
#define NUM_OUTPUTS 6

using namespace std;

Network::Network()
{
   inputs  = new Node[NUM_INPUTS];
   outputs = new Node[NUM_OUTPUTS];
}

Network::~Network()
{
   if(inputs != NULL)
   {
      delete [] inputs;
      inputs = NULL;
   }
   if(outputs != NULL)
   {
      delete [] outputs;
      outputs = NULL;
   }

}

void Network::get_input(){}

void Network::use_output(){}

bool Network::rand_node(){}

bool Network::rand_connection()
{
   int node_one = rand()% numNodes;
   int node_two = rand()% numNodes;
   while(node_one == node_two) 
   {
      node_two = rand()% numNodes;
   }
   int i;
   Node one;
   Node two;
   while (nodes[i] != NULL)
   {
      if (nodes[i].node_id == node_one)
         one = nodes[i];
      else if (nodes[i].node_id == node_two)
         two = nodes[i];
   }

   one.outputs = two;
   two.inputs = one;  
}