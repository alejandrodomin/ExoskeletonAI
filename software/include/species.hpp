#ifndef SPECIES_HPP
#define SPECIES_HPP

/** @brief Class for the species.

    This class will hold of the functions that deal
    with species, and their necessary actions.
    @author Dominguez, Alejandro
    @date Feburary, 2018
    */

#include <iostream>
#include <list>

#include <network.hpp>

using namespace std;

class Species{
private:
    int stale;/**< Indicates how long a function has been stale.*/
    int fit_stale;
    int max_fitness;/**<The maximum fitness of a species.*/

    Network* fittest_net;/**<Network pointer to the fittest network.*/

    list<Network *> networks;/**<A list of network pointers that stores networks.*/
protected:
    int compute_excess(Network *, Network *);
    int compute_disjoint(Network *, Network *);
      
    float weight_diff_match_genes(Network *, Network *);
public:
    Species();
    ~Species();

    void mutate();
    void run_networks();
    void add_network(Network *);

    bool is_stale();
    bool test_species();

    Network* get_fittest_net();  

    Species* new_species();

    list<Network *>* get_networks();
};

#endif