#include <iostream>
#include <cstdlib>
#include <thread>

#include "network.h"
#include "input.h"
#include "output.h"

#define NUM_INPUTS  9
#define NUM_OUTPUTS 6

using namespace std;

Network::Network()
{
   in_nodes  = new Input*[NUM_INPUTS];
   out_nodes = new Output*[NUM_OUTPUTS];
   threads   = new thread*[NUM_INPUTS];
}

Network::~Network()
{
   if(this->in_nodes != NULL)
   {
      delete [] this->in_nodes;
      in_nodes = NULL;
   }
   if(out_nodes != NULL)
   {
      delete [] out_nodes;
      in_nodes = NULL;
   }

}

Input** Network::get_input()
{
    return in_nodes;
} 

int Network::get_num_nodes()
{
    return num_nodes;
}

void Network::set_num_nodes(int num_nodes)
{
    this->num_nodes = num_nodes;
}

bool Network::add_input_node(int num_nodes)
{
    int index = 0;
    while(num_nodes > 0)
    {
        Input* ptr = new Input();
        in_nodes[index] = ptr;
        
        num_nodes--;
        index++;
        
        if (ptr != NULL)
        {
            delete [] ptr;
            ptr = NULL;
        }
    }

    return true;
}

bool Network::add_output_nodes(int num_nodes)
{
    int index = 0;
    while(num_nodes > 0)
    {
        Output* ptr = new Output();
        out_nodes[index] = ptr;
        
        num_nodes--;
        index++;
        
        if (ptr != NULL)
        {
            delete [] ptr;
            ptr = NULL;
        }
    }

    return true;
}

void Network::run()					// there is alot of safety measures that need to be put into here
{
    for (int index = 0; index < 9; index++)
    {
        threads[index] = in_nodes[index]->spawn_thread();
    }
    
}


void Network::use_output(){}

bool Network::rand_node(){}

bool Network::rand_connection()
{
//    int node_one = rand()% num_nodes;
//    int node_two = rand()% num_nodes;

//    if(node_one == node_two) 
//       node_two = rand()% num_nodes;
   
//    int index = 0;
//    Node *one, *two;
//    while (nodes[index] != NULL)
//    {
//       if (nodes[index]->get_nodeid() == node_one)
//          one = nodes[index];
//       else if (nodes[index]->get_nodeid() == node_two)
//          two = nodes[index];

//       index++;
//    }

//    one->add_output(two);
//    two->add_input(one);  
}
