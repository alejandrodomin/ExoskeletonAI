#include "network.h"
#include <iostream>
#include <cstdlib>
#include <thread>

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

 Network::get_input(){
    return **inputs;
} 
void Network::set_input(**input)
{
    this.**inputs = **input;
}
int Network::get_num_nodes(){
    return num_nodes;
} 
void Network::set_num_nodes(int num_nodes)
{
    this.num_nodes = num_nodes;
}
bool Network::add_input_node(int num_nodes)
{
int index = 0;
while(num_nodes > 0)
{
    Node* ptr = new Node();
    inputs[index] = ptr;
    num_nodes--;
    index++;
    if (ptr != NULL)
    {
        delete [] ptr;
        ptr = NULL;
    }
}
}
bool Network::add_output_nodes(int num_nodes)
{
int index = 0;
while(num_nodes > 0)
{
    Node* ptr = new Node();
    outputs[index] = ptr;
    num_nodes--;
    index++;
    if (ptr != NULL)
    {
        delete [] ptr;
        ptr = NULL;
    }
}
}
void Network::run()
{
    for (int index = 0; index < 9; index++)
    {
        thread(inputs[index]->out_func());
        
    }
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