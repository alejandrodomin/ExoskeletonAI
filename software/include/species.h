#include <iostream>
#include "global.h"

using namespace std;

#ifndef SPECIES_H
#define SPECIES_H
class Net;

class Species
{
   private:
   protected:
      int **   net_fitness;
      int      max_fitness;
      Net **   networks;
      Net *    fittest_net;
   public:
      Species();
      ~Species();
};

#endif