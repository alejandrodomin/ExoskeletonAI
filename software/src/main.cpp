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

int main(int argc, char **argv, char **env){
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

   cout << "[INFO][MAIN]:\t Entered main." << endl;

   list<Species *> exoAI;
   exoAI.push_back(new Species());
   exoAI.front()->add_network(new Network());


   while(true){
      info_proc << "Processor name: " << processor_name;
      info_proc << "\tWorld rank: " << world_rank;
      info_proc << "\tWorld size: " << world_size << endl;

      for(list<Species *>::iterator it = exoAI.begin(); it != exoAI.end(); ++it){
         (*it)->run_networks();

         if((*it)->is_stale()){
            (*it)->add_network((*it)->mutate());
         }

         if((*it)->get_networks().size() > 1){
            if((*it)->test_species()){
               exoAI.push_back((*it)->new_species());
            }
         }
      }
   }

   MPI_Finalize();
   info_proc.close();

   cout << "[INFO][MAIN]:\t Exiting main." << endl;
   return 0;
}
