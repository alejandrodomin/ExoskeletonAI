#include <iostream>

#include "species.hpp"
#include "network.hpp"

using namespace std;

static int global_innovation_id = 0; 

int main(int argc, char **argv, char **env){
   cout << "[INFO][MAIN_CPP]: Entered main." << endl;
   
   list<Species *> exoAI;
   exoAI.push_back(new Species());

   while(true){   
      for(list<Species *>::iterator it = exoAI.begin(); it != exoAI.end(); ++it){
         (*it)->add_network(new Network());
         (*it)->run_networks();

         if((*it)->is_stale()){
            (*it)->mutate();
         }

         if((*it)->test_species()){
            exoAI.push_back((*it)->new_species());
         }
      }
   }

   cout << "[INFO][MAIN_CPP]: Exiting main." << endl;
   return 0;
}