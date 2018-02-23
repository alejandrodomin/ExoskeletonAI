#include <mpi.h>

#include <iostream>
#include <fstream>
#include <thread>

#include "common.hpp"
#include "species.hpp"
#include "network.hpp"
#include "node.hpp"
#include "gene.hpp"

using namespace std;

void kill_unfit(list<Network *>);

bool compare(Gene *one, Gene *two);
bool compare(Network *, Network *);

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
   ExoSpec.push_back(new Species());
   ExoSpec.front()->add_network(new Network());

   while(true){
      for(list<Species *>::iterator it = ExoSpec.begin(); it != ExoSpec; ++it){
         for(list<Network *>::iterator itr = (*it)->get_networks().begin(); itr != (*it)->get_networks().end(); ++itr){
            (*itr)->run();
            (*itr)->calculate_fit();
         }

         (*it)->get_networks().sort(compare);
         for(list<Network *>::iterator itr = (*it)->get_networks().begin(); itr != (*it)->get_networks().end(); ++itr){
            (*it)->get_networks().pushback(breed(itr, itr++));
         }
         kill_unfit((*it)->get_networks());
      }

      // compete the fittest nets from each species
   }

   /***************************************************
   * This is where the neural network ends.           *   
   ***************************************************/

   MPI_Finalize();
   info_proc.close();

   cout << "[INFO][MAIN]:\t Exiting main." << endl;
   return 0;
}


void kill_unfit(list<Network *> *net){
   (*it)->get_networks().sort(compare);

   int size = net.size() / 4;

   list<Network *>::iterator it = net.begin();
   for(int index = 0; index < size; index++){
      net.erase(it);
      it++; 
   }
}

bool compare(Gene *one, Gene *two){
   return one->get_inov_id() < two->get_inov_id();
}

bool compare(Network *one, Network *two){
   return one->get_fitness() < two->get_fitness();
}

Network* breed(Network *one, Network *two){
   one->get_genes().sort(compare);
   two->get_genes().sort(compare);

   list<Gene *>::iterator itone = one->get_genes().begin();
   list<Gene *>::iterator ittwo = two->get_genes().begin();

   int randNum;
   Network *newNet = new Network();

   while(itone != one->get_genes().end() && ittwo != two->get_genes().end()){
      randNum = rand() % 2;

      if(randNum)
         newNet.add_gene(ittwo.get_input_node(), ittwo.get_ouput_node());
      else newNet.add_gene(itone.get_input_node(), itone.get_ouput_node());

      itone++;
      ittwo++;
   }

   return newNet;
}