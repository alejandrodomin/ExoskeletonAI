#include <iostream>
#include <list>

#include "network.hpp"

using namespace std;

#ifndef SPECIES_HPP
#define SPECIES_HPP

class Species{
   private:
      int stale;
      int max_fitness;

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