#include <iostream>
#include <iterator>
#include <cmath>

#include <species.hpp>
#include <common.hpp>

#define MAX_SIZE 10000

using namespace std;

/**Constructor initializes stale and max_fitness variables.
 */ 
Species::Species(){
    if(comment == true)    
     cout << "[INFO][SPECIES]: Entered Species::Species()." << endl;
    
    stale = 0;
    fit_stale = 0;
    max_fitness = 0;

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::Species()." << endl;
}
    
/** Destructor deletes memory allocated to fittest_net and
 * list<Network *>.
 */ 
Species::~Species(){
    if(comment == true)    
     cout << "[INFO][SPECIES]: Entered Species::~Species()." << endl; 

    if(fittest_net != NULL){
        delete fittest_net;
        fittest_net = NULL;
    }
    for(list<Network *>::iterator it = this->networks.begin(); it != this->networks.end(); it++){
        if(*it != NULL){
            delete *it;
            *it = NULL;
        }
    }
    networks.clear();

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::~Species()." << endl;
}

/** Mutate function which mutates every item in list<Network *>
*/
void Species::mutate(){
    if(comment == true)    
     cout << "[INFO][SPECIES]: Entered Species::mutate()." << endl;
   
    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        (*it)->mutate();
    }

    if(comment == true)    
     cout << "[INFO][SPECIES]: Exiting Species::mutate()." << endl;
}

/** This function runs every item in list<Network *>
*/
void Species::run_networks(){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entered Species::run_networks()." << endl;
    
    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        (*it)->run();
    }

    if(comment == true)    
     cout << "[INFO][SPECIES]: Entered Species::run_networks()." << endl;
}

/** This function adds a network.
* @param Network *net net pointer
*/
bool Species::add_network(Network *net){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entered Species::add_network(Network*)." << endl;
    
    if(networks.size() < MAX_SIZE){
        networks.push_back(net);
        return true;
    }
    else return false;

    if(comment == true)    
     cout << "[INFO][SPECIES]: Exiting Species::add_network(Network*)." << endl;
}

/** This function checks if items in list<Network *>
 * are at maximum fitness.
 * @return bool 
 */ 
bool Species::is_stale(){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entered Species::is_stale()." << endl;
    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        if((*it)->get_fitness() > max_fitness){
            stale = 0;
            return false;
        }
    }

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::is_stale()." << endl;

    stale++;
    if(stale >= 15)
        return true;
    else return false;
}

/** This function tests a species for 
 * disjoint genes and excess genes.
 * @return bool
 */ 
bool Species::test_species(){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entered Species::test_species()." << endl;
    
    float c1 = 0.5, c2 = 0.5, c3 = 0.5;
    float disjoint_genes, excess_genes;
    float compatibility_distance = 0.0;

    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        if(++it != networks.end()){
            disjoint_genes = compute_disjoint(*it, *(++it));
            excess_genes = compute_excess(*it, *(++it));
        }

        if((*it)->get_num_nodes() < 20 && (*(++it))->get_num_nodes() < 20)
            compatibility_distance = (c1 * excess_genes) + (c2 * disjoint_genes) + (c3 * weight_diff_match_genes(*it, *(++it)));
        else if((*it)->get_num_nodes() > (*(++it))->get_num_nodes())
            compatibility_distance = ((c1 * excess_genes)/(*it)->get_num_nodes()) + ((c2 * disjoint_genes)/(*it)->get_num_nodes()) + (c3 * weight_diff_match_genes(*it, *(++it)));
        else compatibility_distance = ((c1 * excess_genes)/(*++it)->get_num_nodes()) + ((c2 * disjoint_genes)/(*++it)->get_num_nodes()) + (c3 * weight_diff_match_genes(*it, *(++it)));

        (*it)->set_compatibility_distance(compatibility_distance);
    }

    return true;

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::test_species()." << endl;
}

/** This function computes biggestnet1 and biggestnet2.
 * @param Network *net1
 * @param Network *net2
 * @return int excess
 */ 
int Species::compute_excess(Network *net1, Network *net2){
    if(comment == true)    
     cout << "[INFO][SPECIES]: Entered Species::compute_excess(Network*,Network*)." << endl;
    int excess = 0;
   
    int biggestnet1 = 0;
    int biggestnet2 = 0;
   
    for(list<Gene *>::iterator it = net1->get_genes()->begin(); it != net1->get_genes()->end(); ++it){
        if((*it)->get_inov_id() > biggestnet1)
            biggestnet1 = (*it)->get_inov_id();
    }
   
    for(list<Gene *>::iterator it = net2->get_genes()->begin(); it != net2->get_genes()->end(); ++it){
        if((*it)->get_inov_id() > biggestnet2)
            biggestnet2 = (*it)->get_inov_id();
    }

    int *net1Arry, *net2Arry; 

    if(biggestnet1 > biggestnet2){
        net1Arry = new int[biggestnet1];
        net2Arry = new int[biggestnet1];
    }
    else{
        net1Arry = new int[biggestnet2];
        net2Arry = new int[biggestnet2];
    }

    for(list<Gene *>::iterator it = net1->get_genes()->begin(); it != net1->get_genes()->end(); ++it){
        net1Arry[(*it)->get_inov_id()] = (*it)->get_inov_id(); 
    }
   
    for(list<Gene *>::iterator it = net2->get_genes()->begin(); it != net2->get_genes()->end(); ++it){
        net1Arry[(*it)->get_inov_id()] = (*it)->get_inov_id();
    }

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::compute_excess(Network*,Network*)." << endl;

    if(biggestnet1 > biggestnet2){
        if(net1Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else return excess;   
            }
        }
        else if(net2Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                    excess++;
                else return excess;   
            }
        }
    }
    else{
        if(net1Arry[biggestnet2] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else return excess;   
            }   
        }
        else if(net2Arry[biggestnet2] == 0){
            for(int index = biggestnet2; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                    excess++;
                else return excess;   
            }
        }
    }

    return excess;
}

/** This function computes disjointed networks.
 * @param Network *net1
 * @param Network *net2
 * @return int disjoint
 */ 
int Species::compute_disjoint(Network *net1, Network *net2){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entering Species::compute_disjoint(Network*,Network*)." << endl;
    
    int disjoint;
    int excess = 0;
    
    int biggestnet1 = 0;
    int biggestnet2 = 0;
    
    for(list<Gene *>::iterator it = net1->get_genes()->begin(); it != net1->get_genes()->end(); ++it){
        if((*it)->get_inov_id() > biggestnet1)
           biggestnet1 = (*it)->get_inov_id();
    }
    
    for(list<Gene *>::iterator it = net2->get_genes()->begin(); it != net2->get_genes()->end(); ++it){
        if((*it)->get_inov_id() > biggestnet2)
           biggestnet2 = (*it)->get_inov_id();
    }

    int *net1Arry, *net2Arry; 
    if(biggestnet1 > biggestnet2){
        net1Arry = new int[biggestnet1];
        net2Arry = new int[biggestnet1];
    }
    else{
        net1Arry = new int[biggestnet2];
        net2Arry = new int[biggestnet2];
    }

    for(list<Gene *>::iterator it = net1->get_genes()->begin(); it != net1->get_genes()->end(); ++it){
        net1Arry[(*it)->get_inov_id()] = (*it)->get_inov_id(); 
    }
    
    for(list<Gene *>::iterator it = net2->get_genes()->begin(); it != net2->get_genes()->end(); ++it){
        net1Arry[(*it)->get_inov_id()] = (*it)->get_inov_id();
    }

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::compute_disjoint(Network*,Network*)." << endl;
    if(biggestnet1 > biggestnet2){
        if(net1Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else if(net2Arry[index] != net1Arry[index]){
                    disjoint++;
                }
                else return disjoint;  
            }
        }
        else if(net2Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                  excess++;
                else if(net2Arry[index] != net1Arry[index]){
                   disjoint++;
                }
                else return disjoint;   
            }
        }
    }
    else{
        if(net1Arry[biggestnet2] == 0){
           for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else if(net2Arry[index] != net1Arry[index]){
                    disjoint++;
                }
               else return disjoint;  
            }
        }
        else if(net2Arry[biggestnet2] == 0){
            for(int index = biggestnet2; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                    excess++;
                else if(net2Arry[index] != net1Arry[index]){
                    disjoint++;
                }
               else return disjoint;   
            }
        }
    }

   return disjoint;
}

/** This function sums the weights of genes with the
 * same innovation number and then computes their average.
 * @param Network *net1
 * @param Network *net2
 * @return float average
 */ 
float Species::weight_diff_match_genes(Network *net1, Network *net2){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entering Species::weight_diff_math_genes(Network*,Network*)." << endl;
    int total;
    float sum;
    float average;

    list<Gene *>::iterator it  = net1->get_genes()->begin();
    list<Gene *>::iterator itr = net2->get_genes()->begin();

    while(it != net1->get_genes()->end() || itr != net2->get_genes()->end()){
        if((*it)->get_inov_id() == (*itr)->get_inov_id()){
            sum += abs((*it)->get_weight() - (*itr)->get_weight());
            total++;
        }

        it++;
        itr++;
    }

    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::weight_diff_math_genes(Network*,Network*)." << endl;
    return average;
}   

Network* Species::get_fittest_net(){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entered Species::get_fittest_net()." << endl;
    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::get_fittest_net()." << endl;

    return fittest_net;
}

list<Network *>* Species::get_networks(){
    if(comment == true)   
      cout << "[INFO][SPECIES]: Entered Species::get_networks()." << endl;
    if(comment == true)   
      cout << "[INFO][SPECIES]: Exiting Species::get_networks()." << endl;

    return &networks;
}