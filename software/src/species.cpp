#include <iostream>
#include <iterator>

#include "species.hpp"

using namespace std;

Species::Species(){
   stale = 0;
   max_fitness = 0;
}

Species::~Species(){

}

void Species::mutate(){
   for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
      (*it)->mutate();
   }
}

void Species::run_networks(){
   for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
      (*it)->run();
   }
}

void Species::add_network(Network *net){
   networks.push_back(net);
}

bool Species::stale(){
   for(list<Network *>::iterator it = networks.begin(); it != networks.edn(), ++it){
      if((*it)->get_fitness() > max_fitness){
         stale = 0;
         return false;
      }
   }

   stale++;
   if(stale >= 15)
      return true;
   else return false;
}

bool Species::test_species(){
   float c1, c2, c3;
   float disjoint_genes, excess_genes;
   float compatibility_distance = 0.0;

   for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
      if(++it != networks.end()){
         disjoint_genes = compute_disjoint(*it, *(++it));
         excess_genes = compute_excess(*it, *(++it));
      }

      if((*it)->get_num_nodes() > (*(++it))->get_num_nodes())
         compatibility_distance = ((c1 * excess_genes)/(*it)->get_num_nodes()) + ((c2 * disjoint_genes)/(*it)->get_num_nodes()) + (c3 * weight_diff_match_genes(*it, *(++it)));
      else compatibility_distance = ((c1 * excess_genes)/(*++it)->get_num_nodes()) + ((c2 * disjoint_genes)/(*++it)->get_num_nodes()) + (c3 * weight_diff_match_genes(*it, *(++it)));

      (*it)->set_compatibility_distance(compatibility_distance);
   }
}

Species* Species::new_species(){

}

float Species::compute_excess(Network *net1, Network *net2){
   return 0.0;
}

float Species::compute_disjoint(Network *net1, Network *net2){
   return 0.0;
}

float Species::weight_diff_match_genes(Network *net1, Network *net2){
   return 0.0;
}