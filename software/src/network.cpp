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
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::Network()." << endl;
    crashes = 0;
    fitness = 0;
    num_nodes = 0;

    for(int i = 0; i < NUM_INPUTS; i++){
        in_nodes.push_back(new Node(input, num_nodes));
    }

    for(int i = 0; i < NUM_INPUTS; i++){
        out_nodes.push_back(new Node(output, num_nodes));
    }

    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::Network()." << endl;
}

/**Network destructor deletes memory allocated to
 * input nodes, output nodes, threads, hidden nodes,
 * and genes.
 */ 
Network::~Network(){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::~Network()." << endl;

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

    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::~Network()." << endl;
}

/**Network run function runs the input,
 * hidden, and output nodes.
 */ 
void Network::run(){				// there is alot of safety measures that need to be put into here
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::run()." << endl;
    
    input_run();
    hidden_run();
    output_run();
    
    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::run()." << endl;
}

/**Network mutate assigns a random value.
 */ 
void Network::mutate(){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::mutate()." << endl;
    
    int num = (rand() % 3) + 1;

    if(num % 3 == 0)
        rand_node();
    else rand_connection();

    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::mutate()." << endl;
}

/**Network use_output has not been implemented.
 */ 
void Network::use_output(){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::use_output()." << endl;
    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::use_output()." << endl;
}

void Network::calculate_fit(){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::calculate_fit()." << endl;

    if(crashes == 0)
        fitness = walk_distance;
    else fitness = walk_distance / crashes;

    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::calculate_fit()." << endl;
}

/**Network set_num_nodes sets the number of nodes.
 * @param num_nodes the number of nodes.
 */ 
void Network::add_num_nodes(int num_nodes){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::set_num_nodes(int)." << endl;
    
    this->num_nodes += num_nodes;

    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::set_num_nodes(int)." << endl;
}

/**Network set_compatibility_distance sets the compatibility distance.
 * @param newcomp_distance the new compatibility distance.
 */ 
void Network::set_compatibility_distance(float newcomp_distance){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::set_compatibility_distance(float)." << endl;

    compatibility_distance = newcomp_distance;

    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::set_compatibility_distance(float)." << endl;
}

/** My function doing something...
    @param snode* pointer to the starting node
    @param onode* pointer to the output node usually the node that 
                    calls this function.
*/
void Network::add_gene(Node *snode, Node *onode){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::add_gene(Node*,Node*)" << endl;

    for(list<Gene *>::iterator it = unique_genes.begin(); it != unique_genes.end(); ++it){
        if((*it)->get_in_node() == snode->get_nodeid() && (*it)->get_out_node() == onode->get_nodeid()){
            genes.push_back(new Gene(snode, onode, (*it)->get_inov_id()));
            return;
        }
    }

    genes.push_back(new Gene(snode, onode, innovation_number));
    unique_genes.push_back(new Gene(snode, onode, innovation_number));

    innovation_number++;
    
    if(comment == true)    
     cout << "[INFO][NETOWRK]: Exiting Network::add_gene(Node*,Node*)" << endl;
}

/** Returns fitness value.
 * @return int type.
 */ 
int Network::get_fitness() const{
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::get_fitness() const." << endl;
    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::get_fitness() const." << endl;

    return fitness;
}

/** Returns number of nodes.
 * @return int type.
 */ 
int Network::get_num_nodes() const{
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::get_num_nodes() const." << endl;
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::get_num_nodes() const." << endl;

    int number = in_nodes.size() + out_nodes.size() + hidden_nodes.size();

    return number;
}

float Network::get_compatibility_distance() const{
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::get_compatibility_distance() const." << endl;
    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::get_compatibility_distance() const." << endl;

    return compatibility_distance;
}

/** Network rand_node creates a random hidden node.
 */ 
bool Network::rand_node(){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::rand_node()." << endl;

    num_nodes++;
    hidden_nodes.push_back(new Node(hidden, num_nodes));
    
    if(comment == true)   
      cout << "[INFO][NETWORK]: Exiting Network::rand_node()." << endl;
}

/** Network rand_connection creates a random connection between two nodes.
 */ 
bool Network::rand_connection(){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::rand_connection()." << endl;

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

    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::rand_connection()." << endl;
    
    return true;    
}

/** Network compare checks if layer of first node is 
 * less than layer of second node.
 * @param Node *one first node
 * @param Node *two second node
 * @return bool
 */ 
bool Network::compare(const Node *one, const Node *two){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::compare(const Node*,const Node*)." << endl;
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::compare(const Node*,const Node*)." << endl;

    return one->get_layer() < two->get_layer();
}
/** Network input_run spawns threads that run the input nodes.
 */ 
void Network::input_run(){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::input_run()" << endl;
     
    for(list<Node *>::iterator itr = in_nodes.begin(); itr != in_nodes.end(); itr++){
        threads.push_back((*itr)->spawn_thread(genes));

        if(threads.size() >= MAX_THREADS){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){
                    if(comment == true)     cout << "\033[1;33m[THREAD][NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join.\033[0m" << endl;
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
                if(comment == true)     cout << "\033[1;33m[THREAD][NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join.\033[0m" << endl;
                (*it)->join();
                if(*it != NULL){
                    delete *it;
                    *it = NULL;
                }
            }
        }
        threads.clear();
    }
    	
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::input_run()" << endl;
}

/**Network hidden_run sorts the hidden nodes by layer and runs them.
 */ 
void Network::hidden_run(){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::hidden_run()." << endl;

    int last_layer = 1;

    if(hidden_nodes.size() > 0){
        hidden_nodes.sort(compare);

        for (list<Node* >::iterator itr = hidden_nodes.begin(); itr != hidden_nodes.end(); ++itr){
            if(threads.size() >= MAX_THREADS || (*itr)->get_layer() > last_layer){
                last_layer = (*itr)->get_layer();

                for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                    if((*it)->joinable()){
                        if(comment == true)     cout << "\033[1;33m[THREAD][NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join.\033[0m" << endl;
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
                    if(comment == true)     cout << "\033[1;33m[THREAD][NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join.\033[0m" << endl;
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

    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::hidden_run()." << endl;
}

/**Network output_run spawns threads that run the output nodes.
 */ 
void Network::output_run(){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::output_run()." << endl;

    for(list<Node *>::iterator itr = out_nodes.begin(); itr != out_nodes.end(); itr++){
        threads.push_back((*itr)->spawn_thread(genes));

        if(threads.size() >= MAX_THREADS){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){
                    if(comment == true)    
                     cout << "\033[1;33m[THREAD][NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join.\033[0m" << endl;
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
                if(comment == true)    
                 cout << "\033[1;33m[THREAD][NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join.\033[0m" << endl;
                (*it)->join();
                if(*it != NULL){
                    delete *it;
                    *it = NULL;
                }
            }
        }
        threads.clear();
    }
    
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::output_run()." << endl;
}

/** Returns the number of input nodes.
 * @return Node**
 */ 
list<Node *>* Network::get_input(){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::get_input()." << endl;
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::get_input()." << endl;

    return &in_nodes;
}

/** Returns the list of gene pointers.
 * @return list<Gene *>
 */ 
list<Gene *>* Network::get_genes(){
    if(comment == true)    
     cout << "[INFO][NETWORK]: Entered Network::get_genes()." << endl;
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::get_genes()." << endl;

    return &genes;
}

/** Returns the hidden nodes.
 * @return list<Node *>
 */ 
list<Node *>* Network::get_hiddennodes(){
    if(comment == true)   
      cout << "[INFO][NETWORK]: Entered Network::get_hiddennnodes()." << endl;
    if(comment == true)    
     cout << "[INFO][NETWORK]: Exiting Network::get_hiddennnodes()." << endl;
    
    return &hidden_nodes;
}
