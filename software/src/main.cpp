#include <mpi.h>

#include <iostream>
#include <fstream>
#include <thread>

#include <common.hpp>
#include <species.hpp>
#include <network.hpp>
#include <node.hpp>
#include <gene.hpp>

#define COIN_FLIP 2
#define QUARTER_KILL 0.25

#define INIT_SPECIES 5
#define INIT_NETWORK 5

using namespace std;

void kill_unfit(list<Network *>*);

bool compareGenes(const Gene *, const Gene *);
bool compareNets(const Network *, const Network *);

Network* breed(Network *, Network *);

int main(int argc, char **argv, char **env){
   cout << "[INFO][MAIN]:\t Entered main." << endl;
   
   int size_of_nets;
   Network *fitNet;
   Network *child;
   list<Network *>::iterator it;
   list<Network *>::iterator itr;
   list<Species *>::iterator iter;
   list<Network *>::iterator next_itr;
   list<Network *>::iterator next_iter;


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

   for(int index = 0; index < INIT_SPECIES; index++){
      ExoSpec.push_back(new Species());
   }
   for(list<Species *>::iterator species_iter= ExoSpec.begin(); species_iter!= ExoSpec.end(); ++species_iter){
      for(int index = 0; index < INIT_NETWORK; index++){
         (*species_iter)->add_network(new Network());
      }
   }

  int x = 5;
   while(x > 0){
     x--;

      for(list<Species *>::iterator species_iter= ExoSpec.begin(); species_iter!= ExoSpec.end(); ++species_iter){
        for(list<Network *>::iterator network_iter = (*species_iter)->get_networks()->begin(); network_iter != (*species_iter)->get_networks()->end(); ++network_iter){
          (*network_iter)->run(); 
          (*network_iter)->calculate_fit();
        }

         if((*species_iter)->is_stale())
          (*species_iter)->mutate();

        (*species_iter)->get_networks()->sort(compareNets);

        size_of_nets = (*species_iter)->get_networks()->size();
        itr = (*species_iter)->get_networks()->begin();
        for(int index = 0; index < size_of_nets; index++){
          next_itr = itr;
          if(++next_itr != (*species_iter)->get_networks()->end()){
            child = breed(*itr, *next_itr);
            if(child != NULL)
              (*species_iter)->get_networks()->push_back(child);
          }
          itr++;
        }

        kill_unfit((*species_iter)->get_networks());

        FitNets.push_back((*species_iter)->get_fittest_net());
      }

      // if(FitNets.size() > 0 && ExoSpec.size() > 0){
      //   it = FitNets.begin();
      //   iter = ExoSpec.begin();

      //   while(it != FitNets.end() || iter != ExoSpec.end()){   
      //     next_iter = it;
      //     if(++next_iter != FitNets.end())
      //       fitNet = breed(*it, *next_iter);

      //     if(fitNet != NULL){
      //       (*iter)->get_networks()->push_back(fitNet);
      //       (*(iter++))->get_networks()->push_back(fitNet);
      //     }

      //     it++;
      //     iter++;
      //   }
      // }
   }

   /***************************************************
   * This is where the neural network ends.           *   
   ***************************************************/

  if(ExoSpec.size() > 0)
    ExoSpec.clear();
  if(ExoSpec.size() > 0) 
    FitNets.clear();

   MPI_Finalize();
   info_proc.close();

   cout << "[INFO][MAIN]:\t Exiting main." << endl;
   return 0;
}


void kill_unfit(list<Network *> *net){
   if(net->size() > 0)
     net->sort(compareNets);

   int size = net->size() * QUARTER_KILL;

   list<Network *>::iterator from = net->begin();
   list<Network *>::iterator to = net->begin();

   for(int index = 0; index < size; index++){
     to++;
   }

   net->erase(from,to);
}

bool compareGenes(const Gene *one, const Gene *two){
  return one->get_inov_id() < two->get_inov_id();
}

bool compareNets(const Network *one, const Network *two){ // sorts less fit first to more fit later.
   return one->get_fitness() < two->get_fitness();
}

Network* breed(Network *one, Network *two){
   if(one == NULL || two == NULL)
    return NULL;

   if(one->get_genes() != NULL && two->get_genes() != NULL){
      if(one->get_genes()->size() > 1 && two->get_genes()->size() > 1){
        one->get_genes()->sort(compareGenes);
        two->get_genes()->sort(compareGenes);
      }
      else return NULL;
   }
   else return NULL;

   list<Gene *>::iterator itone = one->get_genes()->begin();
   list<Gene *>::iterator ittwo = two->get_genes()->begin();

   int randNum;
   Network *newNet = NULL;

   while(itone != one->get_genes()->end() || ittwo != two->get_genes()->end()){
      randNum = rand() % COIN_FLIP;

      if(randNum)
         newNet->add_gene((*ittwo)->get_input_node(), (*ittwo)->get_output_node());
      else newNet->add_gene((*itone)->get_input_node(), (*itone)->get_output_node());

      itone++;
      ittwo++;
   }

   return newNet;
}