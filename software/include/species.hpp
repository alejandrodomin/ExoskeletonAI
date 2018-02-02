#include <iostream>

#include "network.hpp"

using namespace std;

#ifndef SPECIES_H
#define SPECIES_H

class Species
{
   private:
      int max_fitness;
      int** net_fitness;

      Network* fittest_net;

      list<Network *> networks;
   protected:
      float compute_excess(Network *, Network *);
      float compute_disjoint(Network *, Network *);
      float weight_diff_match_genes(Network *, Network *);
   public:
      Species();
      ~Species();

      void mutate();
      void run_networks();
      void add_network(Network *);

      bool stale();
      bool test_species();

      Species* new_species();
};

#endif