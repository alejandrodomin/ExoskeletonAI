#include <iostream>
#include <cstdlib>
#include <thread>

#include "network.h"
#include "input.h"
#include "output.h"

#define NUM_INPUTS  9
#define NUM_OUTPUTS 6
#define MAX_THREADS 10

using namespace std;

Network::Network()
{
   in_nodes  = new Input*[NUM_INPUTS];
   out_nodes = new Output*[NUM_OUTPUTS];
   threads   = new thread*[MAX_THREADS];
}

Network::~Network()
{
   if(in_nodes != NULL)
   {
      delete [] in_nodes;
      in_nodes = NULL;
   }
   if(out_nodes != NULL)
   {
      delete [] out_nodes;
      in_nodes = NULL;
   }
   if(threads != NULL)
   {
       delete [] threads;
       threads = NULL;
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
    input_run();
    hidden_run();
    output_run();

}

void Network::input_run()
{
    int index;
    for (index = 0; index < NUM_INPUTS; index++)
    {
        threads[index] = in_nodes[index]->spawn_thread();
    }

    int found = 0;          // checks to see if the above threads are done executing
    index = 0;
    while(found < NUM_INPUTS)
    {
        if(in_nodes[index]->get_outputfunc() != 0)
        {
            found++;
        }

        index++;
    }

    if(threads != NULL)
    {
        delete [] threads;
        threads = NULL;
    }
}

void Network::hidden_run()
{
    
}

void Network::output_run()
{
    for (int index = 0; index < NUM_OUTPUTS; index++)
    {
        threads[index] = out_nodes[index]->spawn_thread();
    }

    int found = 0, index = 0;          // checks to see if the above threads are done executing
    while(found < NUM_INPUTS)
    {
        if(out_nodes[index]->get_outputfunc() != 0)
        {
            found++;
        }

        index++;
    }

    if(threads != NULL)
    {
        delete [] threads;
        threads = NULL;
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
//    while (in_nodes[index] != NULL)
//    {
//       if (in_nodes[index]->get_nodeid() == node_one)
//          one = in_nodes[index];
//       else if (in_nodes[index]->get_nodeid() == node_two)
//          two = in_nodes[index];

//       index++;
//    }

//    one->add_output(two);
//    two->add_input(one);  
}
