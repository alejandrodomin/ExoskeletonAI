#include <iostream>

using namespace std;

#ifndef SPECIES_H
#define SPECIES_H

class Species
{
   private:
   protected:
      int **   gen_fitness;
      int      max_fitness;
      Net **   net_ptr;
      Net *    fittest_net;
   public:
      Species();
      ~Species();
};

#endif