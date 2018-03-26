#include <iostream>
#include <cstdlib>
#include <thread>

#include <common.hpp>
#include <network.hpp>

using namespace std;

/**Network constructor initializes input nodes,
 * output nodes, and threads.
 */
Network::Network(){
    crashes = 0;
    fitness = 0;
    num_nodes = 0;

    for(int i = 0; i < NUM_INPUTS; i++){
        in_nodes.push_back(new Node(input, num_nodes));
    }

    for(int i = 0; i < NUM_INPUTS; i++){
        out_nodes.push_back(new Node(output, num_nodes));
    }
}

/**Network destructor deletes memory allocated to
 * input nodes, output nodes, threads, hidden nodes,
 * and genes.
 */ 
Network::~Network(){
    for(list<Node *>::iterator it = in_nodes.begin(); it != in_nodes.end(); it++){
        if(*it != NULL){
            delete *it;
            *it = NULL;
        }   
    }
    in_nodes.clear();

    for(list<Node *>::iterator it = out_nodes.begin(); it != out_nodes.end(); it++){
        if(*it != NULL){
            delete *it;
            *it = NULL;
        }   
    }
    out_nodes.clear();

    for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); it++){
        if(*it != NULL){
            delete *it;
            *it = NULL;
        }   
    }
    threads.clear();
   
    for(list<Node *>::iterator it = hidden_nodes.begin(); it != hidden_nodes.end(); it++){
        if(*it != NULL){
            delete *it;
            *it = NULL;
        }
    }
    hidden_nodes.clear();

    for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); it++){
        if(*it != NULL){
            delete *it;
            *it = NULL;
        }
    }
    genes.clear();
}

/**Network run function runs the input,
 * hidden, and output nodes.
 */ 
void Network::run(){				// there is alot of safety measures that need to be put into here
    input_run();
    hidden_run();
    output_run();
}

/**Network mutate assigns a random value.
 */ 
void Network::mutate(){
    int num = (rand() % 3) + 1;

    if(num % 3 == 0)
        rand_node();
    else rand_connection();
}

/**Network use_output has not been implemented.
 */ 
void Network::use_output(){
}

void Network::calculate_fit(){
    if(crashes == 0)
        fitness = walk_distance;
    else fitness = walk_distance / crashes;
}

/**Network set_num_nodes sets the number of nodes.
 * @param num_nodes the number of nodes.
 */ 
void Network::add_num_nodes(int num_nodes){
    this->num_nodes += num_nodes;
}

/**Network set_compatibility_distance sets the compatibility distance.
 * @param newcomp_distance the new compatibility distance.
 */ 
void Network::set_compatibility_distance(float newcomp_distance){
    compatibility_distance = newcomp_distance;
}

/** My function doing something...
    @param snode* pointer to the starting node
    @param onode* pointer to the output node usually the node that 
                    calls this function.
*/
void Network::add_gene(Node *snode, Node *onode){
    for(list<Gene *>::iterator it = unique_genes.begin(); it != unique_genes.end(); ++it){
        if((*it)->get_in_node() == snode->get_nodeid() && (*it)->get_out_node() == onode->get_nodeid()){
            genes.push_back(new Gene(snode, onode, (*it)->get_inov_id()));
            return;
        }
    }

    genes.push_back(new Gene(snode, onode, innovation_number));
    unique_genes.push_back(new Gene(snode, onode, innovation_number));

    innovation_number++;
}

/** Returns fitness value.
 * @return int type.
 */ 
int Network::get_fitness() const{
    return fitness;
}

int Network::get_maxlayer() const{
    int maxlayer = 0;
    for(list<Node *>::const_iterator it = hidden_nodes.begin(); it != hidden_nodes.end(); it++){
        if((*it)->get_layer() > maxlayer){
            maxlayer = (*it)->get_layer();
        }
    }

    return maxlayer;
}

/** Returns number of nodes.
 * @return int type.
 */ 
int Network::get_num_nodes() const{
    return in_nodes.size() + out_nodes.size() + hidden_nodes.size();
}

float Network::get_compatibility_distance() const{
    return compatibility_distance;
}

/** Network rand_node creates a random hidden node.
 */ 
bool Network::rand_node(){
    num_nodes++;
    hidden_nodes.push_back(new Node(hidden, num_nodes));
}

/** Network rand_connection creates a random connection between two nodes.
 */ 
bool Network::rand_connection(){
    int node_one, node_two;

    node_one = rand() % num_nodes + 1;
    node_two = rand() % num_nodes + 1;

    Node *nodeOne, *nodeTwo;

    for(list<Node *>::iterator it = in_nodes.begin(); it != in_nodes.end(); ++it){
        if((*it)->get_nodeid() == node_one){
            nodeOne = *it;
        }
        else if((*it)->get_nodeid() == node_two){
            nodeTwo = *it;
        }
    }
    for(list<Node *>::iterator it = hidden_nodes.begin(); it != hidden_nodes.end(); ++it){
        if((*it)->get_nodeid() == node_one){
            nodeOne = *it;
        }
        else if((*it)->get_nodeid() == node_two){
            nodeTwo = *it;
        }
    }
    for(list<Node *>::iterator it = out_nodes.begin(); it != out_nodes.end(); ++it){
        if((*it)->get_nodeid() == node_one){
            nodeOne = *it;
        }
        else if((*it)->get_nodeid() == node_two){
            nodeTwo = *it;
        }
    }

    for(list<Gene *>::iterator it = unique_genes.begin(); it != unique_genes.end(); ++it){
        if((*it)->get_in_node() == node_one && (*it)->get_out_node() == node_two){
            genes.push_back(new Gene(nodeOne, nodeTwo, (*it)->get_inov_id()));
            return true;
        }
    }

    genes.push_back(new Gene(nodeOne, nodeTwo, innovation_number));
    unique_genes.push_back(new Gene(nodeOne, nodeTwo, innovation_number));

    innovation_number++;

    return true;    
}

/** Network compare checks if layer of first node is 
 * less than layer of second node.
 * @param Node *one first node
 * @param Node *two second node
 * @return bool
 */ 
bool Network::compare(const Node *one, const Node *two){
    return one->get_layer() < two->get_layer();
}

/** Network input_run spawns threads that run the input nodes.
 */ 
void Network::input_run(){
    for(list<Node *>::iterator itr = in_nodes.begin(); itr != in_nodes.end(); itr++){
        threads.push_back((*itr)->spawn_thread(genes));

        if(threads.size() >= MAX_THREADS){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){
                    // cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                    (*it)->join();
                    if(*it != NULL){
                        delete *it;
                        *it = NULL;
                    }
                }
            }
            threads.clear();
        }
    }

    if(threads.size() >= 0){
        for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
            if((*it)->joinable()){
                // cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                (*it)->join();
                if(*it != NULL){
                    delete *it;
                    *it = NULL;
                }
            }
        }
        threads.clear();
    }
}

/**Network hidden_run sorts the hidden nodes by layer and runs them.
 */ 
void Network::hidden_run(){
    int last_layer = 1;

    if(hidden_nodes.size() > 0){
        hidden_nodes.sort(compare);

        for (list<Node* >::iterator itr = hidden_nodes.begin(); itr != hidden_nodes.end(); ++itr){
            if(threads.size() >= MAX_THREADS || (*itr)->get_layer() > last_layer){
                last_layer = (*itr)->get_layer();

                for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                    if((*it)->joinable()){
                        // cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                        (*it)->join();
                        if(*it != NULL){
                            delete *it;
                            *it = NULL;
                        }
                    }
                }
                threads.clear();
            }
            else threads.push_back((*itr)->spawn_thread(genes));
        }

        if(threads.size() >= 0){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){
                    // cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                    (*it)->join();
                    if(*it != NULL){
                        delete *it;
                        *it = NULL;
                    }
                }
            }
            threads.clear();
        }
    }
}

/**Network output_run spawns threads that run the output nodes.
 */ 
void Network::output_run(){
    for(list<Node *>::iterator itr = out_nodes.begin(); itr != out_nodes.end(); itr++){
        threads.push_back((*itr)->spawn_thread(genes));

        if(threads.size() >= MAX_THREADS){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){    
                    // cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                    (*it)->join();
                    if(*it != NULL){
                        delete *it;
                        *it = NULL;
                    }
                }
            }
            threads.clear();
        }
    }

    if(threads.size() >= 0){
        for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
            if((*it)->joinable()){
                // cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                (*it)->join();
                if(*it != NULL){
                    delete *it;
                    *it = NULL;
                }
            }
        }
        threads.clear();
    }
}

/** Returns the number of input nodes.
 * @return Node**
 */ 
list<Node *>* Network::get_input(){
    return &in_nodes;
}

list<Node *>* Network::get_output(){
    return &out_nodes;
}

/** Returns the list of gene pointers.
 * @return list<Gene *>
 */ 
list<Gene *>* Network::get_genes(){
    return &genes;
}

/** Returns the hidden nodes.
 * @return list<Node *>
 */ 
list<Node *>* Network::get_hiddennodes(){
    return &hidden_nodes;
}
