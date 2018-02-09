#include <iostream>
#include <cstdlib>
#include <thread>

#include "common.hpp"
#include "network.hpp"

using namespace std;

Network::Network(){
   cout << "[INFO][NETWORK]: Entered Network::Network()." << endl;
   in_nodes  = new Node*[NUM_INPUTS];
   out_nodes = new Node*[NUM_OUTPUTS];
   threads   = new thread*[MAX_THREADS];
   cout << "[INFO][NETWORK]: Exiting Network::Network()." << endl;
}

Network::~Network(){
   cout << "[INFO][NETWORK]: Entered Network::~Network()." << endl;

   if(in_nodes != NULL){
      delete [] in_nodes;
      in_nodes = NULL;
   }
   if(out_nodes != NULL){
      delete [] out_nodes;
      in_nodes = NULL;
   }
   if(threads != NULL){
       delete [] threads;
       threads = NULL;
   }
   for(list<Node *>::iterator it = hidden_nodes.begin(); it != hidden_nodes.end(); ++it){
       if(*it != NULL){
           delete [] *it;
           *it = NULL;
       }
   }
   for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); ++it){
        if(*it != NULL){
            delete [] *it;
            *it = NULL;
        }
    }

   cout << "[INFO][NETWORK]: Exiting Network::~Network()." << endl;
}

void Network::run(){				// there is alot of safety measures that need to be put into here
    cout << "[INFO][NETWORK]: Entered Network::run()." << endl;
    input_run();
    hidden_run();
    output_run();
    cout << "[INFO][NETWORK]: Exiting Network::run()." << endl;
}

void Network::input_run(){
    cout << "[INFO][NETWORK]: Entering Network::input_run()" << endl;
    int index;
    for (index = 0; index < NUM_INPUTS; index++){
        threads[index] = in_nodes[index]->spawn_thread(genes);
    }

    int found = 0;          // checks to see if the above threads are done executing
    index = 0;
    while(found < NUM_INPUTS){
        if(in_nodes[index]->get_outputfunc() != 0){
            found++;
        }

        index++;
    }

    if(threads != NULL){
        delete [] threads;
        threads = NULL;
    }

    cout << "[INFO][NETWORK]: Exiting Network::intput_run()" << endl;
}

void Network::hidden_run(){
    cout << "[INFO][NETWORK]: Entered Network::hidden_run()." << endl;
    cout << "[INFO][NETWORK]: Exiting Network::hidden_run()." << endl;
}

void Network::output_run(){
    cout << "[INFO][NETWORK]: Entered Network::output_run()." << endl;
    for (int index = 0; index < NUM_OUTPUTS; index++){
        threads[index] = out_nodes[index]->spawn_thread(genes);
    }

    int found = 0, index = 0;          // checks to see if the above threads are done executing
    while(found < NUM_INPUTS){
        if(out_nodes[index]->get_outputfunc() != 0){
            found++;
        }

        index++;
    }

    if(threads != NULL){
        delete [] threads;
        threads = NULL;
    }
    cout << "[INFO][NETWORK]: Exiting Network::output_run()." << endl;
}

void Network::mutate(){
    cout << "[INFO][NETWORK]: Entered Network::mutate()." << endl;
    int num = (rand() % 3) + 1;

    if(num % 3 == 0)
        rand_node();
    else rand_connection();
    cout << "[INFO][NETWORK]: Exiting Network::mutate()." << endl;
}

void Network::use_output(){
    cout << "[INFO][NETWORK]: Entered Network::use_output()." << endl;
    cout << "[INFO][NETWORK]: Exiting Network::use_output()." << endl;
}

void Network::set_num_nodes(int num_nodes){
    cout << "[INFO][NETWORK]: Entered Network::set_num_nodes(int)." << endl;
    this->num_nodes = num_nodes;
    cout << "[INFO][NETWORK]: Exiting Network::set_num_nodes(int)." << endl;
}

void Network::set_compatibility_distance(float newcomp_distance){
    cout << "[INFO][NETWORK]: Entered Network::set_compatibility_distance(float)." << endl;
    compatibility_distance = newcomp_distance;
    cout << "[INFO][NETWORK]: Exiting Network::set_compatibility_distance(float)." << endl;
}

/** My function doing something...
    @param snode* pointer to the starting node
    @param onode* pointer to the output node usually the node that 
                    calls this function.
*/
void Network::add_gene(Node *snode, Node * onode){
    cout << "[INFO][NETWORK]: Entered Network::add_gene(Node*, Node*)" << endl;
    genes.push_back(new Gene(snode, onode));
    cout << "[INFO][NETOWRK]: Exiting Network::add_gene(Node*, Node*)" << endl;
}

int Network::get_fitness(){
    cout << "[INFO][NETWORK]: Entered Network::get_fitness()." << endl;
    cout << "[INFO][NETWORK]: Exiting Network::get_fitness()." << endl;
    return fitness;
}

int Network::get_num_nodes(){
    cout << "[INFO][NETWORK]: Entered Network::get_num_nodes()." << endl;
    cout << "[INFO][NETWORK]: Exiting Network::get_num_nodes()." << endl;
    return num_nodes;
}

bool Network::rand_node(){
    cout << "[INFO][NETWORK]: Entered Network::rand_node()." << endl;
    hidden_nodes.push_back(new Node(hidden));
    cout << "[INFO][NETWORK]: Exiting Network::rand_node()." << endl;
}

bool Network::rand_connection(){
    cout << "[INFO][NETWORK]: Entered Network::rand_connection()." << endl;
   int node_one = rand()% num_nodes;
   int node_two = rand()% num_nodes;

   if(node_one == node_two)
      node_two = rand()% num_nodes;

   int index = 0;
   Node *one, *two;
   while (in_nodes[index] != NULL){
      if (in_nodes[index]->get_nodeid() == node_one)
         one = in_nodes[index];
      else if (in_nodes[index]->get_nodeid() == node_two)
         two = in_nodes[index];

      index++;
   }

   add_gene(one, two);
   cout << "[INFO][NETWORK]: Exiting Network::rand_connection()." << endl;
}

bool Network::add_input_node(int num_nodes){
    cout << "[INFO][NETWORK]: Entered Network::add_input_node(int)." << endl;
    int index = 0;
    while(num_nodes > 0){
        in_nodes[index] = new Node(input);

        num_nodes--;
        index++;
    }

    cout << "[INFO][NETWORK]: Exiting Network::add_input_node(int)." << endl;
    return true;
}

bool Network::add_output_nodes(int num_nodes){
    cout << "[INFO][NETWORK]: Entered Network::add_output_nodes(int)." << endl;
    int index = 0;
    while(num_nodes > 0){
        out_nodes[index] = new Node(output);

        num_nodes--;
        index++;
    }

    cout << "[INFO][NETWORK]: Exiting Network::add_output_nodes(int)." << endl;
    return true;
}

Node** Network::get_input(){
    cout << "[INFO][NETWORK]: Entered Network::get_input()." << endl;
    cout << "[INFO][NETWORK]: Exiting Network::get_input()." << endl;
    return in_nodes;
}

list<Gene *> Network::get_genes(){
    cout << "[INFO][NETWORK]: Entered Network::get_genes()." << endl;
    cout << "[INFO][NETWORK]: Exiting Network::get_genes()." << endl;
    return genes;
}