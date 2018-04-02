#include <iostream>
#include <iterator>
#include <cmath>

#include <species.hpp>
#include <common.hpp>

#define MAX_SIZE 100

using namespace std;

/**Constructor initializes stale and max_fitness variables.
 */ 
Species::Species(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered constructor." << endl;
    #endif

    stale = 0;
    fit_stale = 0;
    max_fitness = 0;

    fittest_net = NULL;

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting constructor." << endl;
    #endif
}
    
/** Destructor deletes memory allocated to fittest_net and
 * list<Network *>.
 */ 
Species::~Species(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered de-constructor." << endl;
    #endif

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

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting de-constructor." << endl;
    #endif
}

/** Mutate function which mutates every item in list<Network *>
*/
void Species::mutate(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered mutate." << endl;
    #endif

    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        (*it)->mutate();
    }

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting mutate." << endl;
    #endif
}

/** This function runs every item in list<Network *>
*/
void Species::run_networks(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered run_networks." << endl;
    #endif

    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        (*it)->run();
    }

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting run_networks." << endl;
    #endif
}

/** This function adds a network.
* @param Network *net net pointer
*/
bool Species::add_network(Network *net){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered add_network." << endl;
    #endif

    if(networks.size() < MAX_SIZE){
        networks.push_back(net);

        #if DEBUG
            cout << "[INFO][SPECIES]: Exiting add_network." << endl;
        #endif

        return true;
    }
    else {
        #if DEBUG
            cout << "\033[31m[ERROR]\033[0m[SPECIES]: Exiting add_network." << endl;
        #endif
        return false;
    }
}

/** This function checks if items in list<Network *>
 * are at maximum fitness.
 * @return bool 
 */ 
bool Species::is_stale(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered is_stale." << endl;
    #endif

    for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it){
        if((*it)->get_fitness() > max_fitness){
            stale = 0;

            #if DEBUG
                cout << "[INFO][SPECIES]: Exiting is_stale." << endl;
            #endif
            return false;
        }
    }
    
    stale++;
    if(stale >= 15){
        #if DEBUG
            cout << "[INFO][SPECIES]: Exiting is_stale." << endl;
        #endif
        return true;
    }
    else {
        #if DEBUG
            cout << "[INFO][SPECIES]: Exiting is_stale." << endl;
        #endif
        return false;
    }
}

/** This function tests a species for 
 * disjoint genes and excess genes.
 * @return bool
 */ 
bool Species::test_species(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered test_species." << endl;
    #endif

    float c1 = 0.5, c2 = 0.5, c3 = 0.5;
    float disjoint_genes = 0, excess_genes = 0;
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

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting test_species." << endl;
    #endif

    return true;
}

/** This function computes biggestnet1 and biggestnet2.
 * @param Network *net1
 * @param Network *net2
 * @return int excess
 */ 
int Species::compute_excess(Network *net1, Network *net2){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered compute_excess." << endl;
    #endif

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

    if(biggestnet1 > biggestnet2){
        if(net1Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_excess." << endl;
                    #endif
                    return excess;   
                }
            }
        }
        else if(net2Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                    excess++;
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_excess." << endl;
                    #endif
                    return excess;   
                }
            }
        }
    }
    else{
        if(net1Arry[biggestnet2] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_excess." << endl;
                    #endif
                    return excess;   
                }
            }   
        }
        else if(net2Arry[biggestnet2] == 0){
            for(int index = biggestnet2; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                    excess++;
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_excess." << endl;
                    #endif
                    return excess;   
                }
            }
        }
    }

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting compute_excess." << endl;
    #endif
    return excess;
}

/** This function computes disjointed networks.
 * @param Network *net1
 * @param Network *net2
 * @return int disjoint
 */ 
int Species::compute_disjoint(Network *net1, Network *net2){   
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered compute_disjoint." << endl;
    #endif 
    int disjoint = 0;
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

    if(biggestnet1 > biggestnet2){
        if(net1Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net1Arry[index] != net2Arry[index] && net1Arry[index] == 0)
                    excess++;
                else if(net2Arry[index] != net1Arry[index]){
                    disjoint++;
                }
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_disjoint." << endl;
                    #endif
                    return disjoint;  
                }
            }
        }
        else if(net2Arry[biggestnet1] == 0){
            for(int index = biggestnet1; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                  excess++;
                else if(net2Arry[index] != net1Arry[index]){
                   disjoint++;
                }
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_disjoint." << endl;
                    #endif
                    return disjoint;   
                }
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
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_disjoint." << endl;
                    #endif
                    return disjoint;  
                }
            }
        }
        else if(net2Arry[biggestnet2] == 0){
            for(int index = biggestnet2; index > 0; index--){
                if(net2Arry[index] != net1Arry[index] && net2Arry[index] == 0)
                    excess++;
                else if(net2Arry[index] != net1Arry[index]){
                    disjoint++;
                }
                else {
                    #if DEBUG
                        cout << "[INFO][SPECIES]: Exiting compute_disjoint." << endl;
                    #endif
                    return disjoint;   
                }
            }
        }
    }

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting compute_disjoint." << endl;
    #endif
    return disjoint;
}

/** This function sums the weights of genes with the
 * same innovation number and then computes their average.
 * @param Network *net1
 * @param Network *net2
 * @return float average
 */ 
float Species::weight_diff_match_genes(Network *net1, Network *net2){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered weight_diff_match_genes." << endl;
    #endif

    int total = 0;
    float sum = 0;

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

    #if DEBUG
        cout << "[INFO][SPECIES]: Exiting weight_diff_match_genes." << endl;
    #endif
    return sum / total;
}   

Network* Species::get_fittest_net(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered get_fittest_net." << endl;
        cout << "[INFO][SPECIES]: Exiting get_fittest_net." << endl;
    #endif
    return fittest_net;
}

list<Network *>* Species::get_networks(){
    #if DEBUG
        cout << "[INFO][SPECIES]: Entered get_networks." << endl;
        cout << "[INFO][SPECIES]: Exiting get_networks." << endl;
    #endif
    return &networks;
}