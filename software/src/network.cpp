#include "network.h"
#include <iostream>
#include <cstdlib>

#define NUM_INPUTS  9
#define NUM_OUTPUTS 6

using namespace std;

Network::Network()
{
   inputs  = new Node*[NUM_INPUTS];
   outputs = new Node*[NUM_OUTPUTS];
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

void Network::get_input(){
    return **inputs;
} 

void Network::use_output(){}

bool Network::rand_node(){}

bool Network::rand_connection()
{
   int node_one = rand()% num_nodes;
   int node_two = rand()% num_nodes;

   if(node_one == node_two) 
      node_two = rand()% num_nodes;
   
   int index = 0;
   Node *one, *two;
   while (nodes[index] != NULL)
   {
      if (nodes[index]->get_nodeid() == node_one)
         one = nodes[index];
      else if (nodes[index]->get_nodeid() == node_two)
         two = nodes[index];

      index++;
   }

   one->add_output(two);
   two->add_input(one);  
}