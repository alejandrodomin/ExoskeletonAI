#include "network.h"
#include <iostream>

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

bool Network::rand_connection(){}