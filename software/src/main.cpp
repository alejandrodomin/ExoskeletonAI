#include <mpi.h>

#include <iostream>
#include <fstream>
#include <thread>

#include "common.hpp"
#include "species.hpp"
#include "network.hpp"
#include "node.hpp"
#include "gene.hpp"

#define COIN_FLIP 2
#define QUARTER_KILL 0.25

using namespace std;

void kill_unfit(list<Network *>);

bool compareGenes(Gene *one, Gene *two);
bool compareNets(Network *, Network *);

Network* breed(Network *, Network *);

int main(int argc, char **argv, char **env){
   cout << "[INFO][MAIN]:\t Entered main." << endl;
   
   ofstream info_proc;
   info_proc.open("info_proc.txt", ios::trunc | ios::out);

   MPI_Init(NULL, NULL);
   int world_size;
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   int world_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
   char processor_name[MPI_MAX_PROCESSOR_NAME];
   int name_len;
   MPI_Get_processor_name(processor_name, &name_len);
   
   /***************************************************
   * This is where the neural network begins.         *   
   ***************************************************/

   list<Species *> ExoSpec;
   list<Network *> FitNets;
   ExoSpec.push_back(new Species());
   ExoSpec.front()->add_network(new Network()); 

   while(true){
      for(list<Species *>::iterator it = ExoSpec.begin(); it != ExoSpec.end(); ++it){
         for(list<Network *>::iterator itr = (*it)->get_networks().begin(); itr != (*it)->get_networks().end(); ++itr){
            (*itr)->run();
            (*itr)->calculate_fit();
         }

         if((*it)->is_stale())
            (*it)->mutate();

         (*it)->get_networks().sort(compareNets);
         for(list<Network *>::iterator itr = (*it)->get_networks().begin(); itr != (*it)->get_networks().end(); ++itr){
            (*it)->get_networks().push_back(breed(*itr, *(itr++)));
         }
         kill_unfit((*it)->get_networks());

         FitNets.push_back((*it)->get_fittest_net());
      }

      list<Network *>::iterator it = FitNets.begin();
      list<Species *>::iterator itr = ExoSpec.begin();

      while(it != FitNets.end() && itr != ExoSpec.end()){   
         Network *fitNet = breed(*it, *(it++));

         (*itr)->get_networks().push_back(fitNet);
         (*(itr++))->get_networks().push_back(fitNet);

         it++;
         itr++;
      }
   }

   /***************************************************
   * This is where the neural network ends.           *   
   ***************************************************/

   MPI_Finalize();
   info_proc.close();

   cout << "[INFO][MAIN]:\t Exiting main." << endl;
   return 0;
}


void kill_unfit(list<Network *> net){
   net.sort(compareNets);

   int size = net.size() * QUARTER_KILL;

   list<Network *>::iterator it = net.begin();
   for(int index = 0; index < size; index++){
      net.erase(it);
      it++; 
   }
}

bool compareGenes(Gene *one, Gene *two){
   return one->get_inov_id() < two->get_inov_id();
}

bool compareNets(Network *one, Network *two){
   return one->get_fitness() < two->get_fitness();
}

Network* breed(Network *one, Network *two){
   one->get_genes().sort(compareGenes);
   two->get_genes().sort(compareGenes);

   list<Gene *>::iterator itone = one->get_genes().begin();
   list<Gene *>::iterator ittwo = two->get_genes().begin();

   int randNum;
   Network *newNet = new Network();

   while(itone != one->get_genes().end() && ittwo != two->get_genes().end()){
      randNum = rand() % COIN_FLIP;

      if(randNum)
         newNet->add_gene((*ittwo)->get_input_node(), (*ittwo)->get_output_node());
      else newNet->add_gene((*itone)->get_input_node(), (*itone)->get_output_node());

      itone++;
      ittwo++;
   }

   return newNet;
}