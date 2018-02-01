#include <iostream>
#include <cstdlib>
#include <thread>

#include "network.hpp"

#define NUM_INPUTS  9
#define NUM_OUTPUTS 6
#define MAX_THREADS 10

using namespace std;

Network::Network()
{
   cout << "Entered network constructor." << endl;
   in_nodes  = new Node*[NUM_INPUTS];
   out_nodes = new Node*[NUM_OUTPUTS];
   threads   = new thread*[MAX_THREADS];
   cout << "Exiting network constructor." << endl;
}

Network::~Network()
{
   cout << "Entering network destrcutor." << endl;
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

  cout << "Exiting network destructor." << endl;
}

void Network::run()					// there is alot of safety measures that need to be put into here
{
    cout << "Entering Network::run" << endl;
    input_run();
    hidden_run();
    output_run();
    cout << "Exiting Network::run" << endl;
}

void Network::input_run()
{
    cout << "Entering Network::input_run" << endl;
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

    cout << "Exiting Network::intput_run()" << endl;
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

void Network::mutate()
{

}

void Network::use_output(){}

void Network::set_num_nodes(int num_nodes)
{
    this->num_nodes = num_nodes;
}

int Network::get_num_nodes()
{
    return num_nodes;
}

bool Network::fitness()
{

}

bool Network::rand_node(){}

bool Network::rand_connection()
{
   int node_one = rand()% num_nodes;
   int node_two = rand()% num_nodes;

   if(node_one == node_two) 
      node_two = rand()% num_nodes;
   
   int index = 0;
   Node *one, *two;
   while (in_nodes[index] != NULL)
   {
      if (in_nodes[index]->get_nodeid() == node_one)
         one = in_nodes[index];
      else if (in_nodes[index]->get_nodeid() == node_two)
         two = in_nodes[index];

      index++;
   }

   one->add_output(two);
   two->add_input(one);  
}

bool Network::add_input_node(int num_nodes)
{
    int index = 0;
    while(num_nodes > 0)
    {
        in_nodes[index] = new Node(input);
        
        num_nodes--;
        index++;
    }

    return true;
}

bool Network::add_output_nodes(int num_nodes)
{
    int index = 0;
    while(num_nodes > 0)
    {
        out_nodes[index] = new Node(output);
        
        num_nodes--;
        index++;
    }

    return true;
}

Node** Network::get_input()
{
    return in_nodes;
} 

list<Network*> Network::reproduce()
{

}
