#include <iostream>
#include <fstream>
#include <thread>

#include "common.hpp"
#include "species.hpp"
#include "network.hpp"
#include "node.hpp"
#include "gene.hpp"

using namespace std;

mutex stats_mutex;

void monitorAI(list<Species *>);

int main(int argc, char **argv, char **env){
   cout << "[INFO][MAIN]:\t Entered main." << endl;

   list<Species *> exoAI;
   exoAI.push_back(new Species());
   exoAI.front()->add_network(new Network());

   while(true){   

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
   
   cout << "[INFO][MAIN]:\t Exiting main." << endl;
   return 0;
}