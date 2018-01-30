#include <iostream>

#include "network.hpp"

using namespace std;

#ifndef SPECIES_H
#define SPECIES_H

class Species
{
   private:
   protected:
      int **   net_fitness;
      int      max_fitness;
      Network **   networks;
      Network *    fittest_net;
   public:
      Species();
      ~Species();
};

#endif