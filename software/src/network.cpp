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
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered constructor." << endl;
    #endif

    crashes = 0;
    fitness = 0;

    #if HARDWARE
        gyro = new float*[NUM_GYROS];
        accel = new float*[NUM_GYROS];
        magno = new float*[NUM_GYROS];

        gyros = new LSM9DS1[NUM_GYROS];
        for(int i = 0; i < NUM_GYROS; i++){
            gyros[i] = imuInit(gyro[i], accel[i], magno[i], i);
        }
    #endif

    for(int i = 0; i < NUM_INPUTS; i++){
        in_nodes.push_back(new Node(input, get_num_nodes()));
    }

    for(int i = 0; i < NUM_OUTPUTS; i++){
        out_nodes.push_back(new Node(output, get_num_nodes()));
    }

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting constructor." << endl;
    #endif
}

/**Network destructor deletes memory allocated to
 * input nodes, output nodes, threads, hidden nodes,
 * and genes.
 */ 
Network::~Network(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered de-constructor." << endl;
    #endif

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

    #if HARDWARE
        if(gyro != NULL){
            delete [] gyro;
            gyro = NULL;
        }
        if(accel != NULL){
            delete [] accel;
            accel = NULL;
        }
        if(magno != NULL){
            delete [] magno;
            magno = NULL;
        }

        if(gyros != NULL){
            delete gyros;
            gyros = NULL;
        }
    #endif

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting de-constructor." << endl;
    #endif
}

/**Network run function runs the input,
 * hidden, and output nodes.
 */ 
void Network::run(){				// there is alot of safety measures that need to be put into here
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered run." << endl;
    #endif
    
    input_run();
    hidden_run();
    output_run();

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting run." << endl;
    #endif
}

/**Network mutate assigns a random value.
 */ 
void Network::mutate(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered mutate." << endl;
    #endif

    int num = (rand() % 3) + 1;

    if(num % 3 == 0)
        rand_node();
    else rand_connection();

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting mutate." << endl;
    #endif
}

/**Network use_output has not been implemented.
 */ 
void Network::use_output(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered use_output." << endl;
        cout << "[INFO][NETWORK]: Exiting use_output." << endl;
    #endif
}

void Network::calculate_fit(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered calculate_fit." << endl;
    #endif

    if(crashes == 0)
        fitness = walk_distance;
    else fitness = walk_distance / crashes;

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting calculate_fit." << endl;
    #endif
}

/**Network set_compatibility_distance sets the compatibility distance.
 * @param newcomp_distance the new compatibility distance.
 */ 
void Network::set_compatibility_distance(float newcomp_distance){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered set_compatibility_distance." << endl;
    #endif

    compatibility_distance = newcomp_distance;

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting set_compatibility_distance." << endl;
    #endif
}

/** My function doing something...
    @param snode* pointer to the starting node
    @param onode* pointer to the output node usually the node that 
                    calls this function.
*/
void Network::add_gene(Node *snode, Node *onode){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered add_gene." << endl;
    #endif

    for(list<Gene *>::iterator it = unique_genes.begin(); it != unique_genes.end(); ++it){
        if((*it)->get_in_node() == snode->get_nodeid() && (*it)->get_out_node() == onode->get_nodeid()){
            genes.push_back(new Gene(snode, onode, (*it)->get_inov_id()));
            return;
        }
    }

    genes.push_back(new Gene(snode, onode, innovation_number));
    unique_genes.push_back(new Gene(snode, onode, innovation_number));

    innovation_number++;

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting add_gene." << endl;
    #endif
}

/** Returns fitness value.
 * @return int type.
 */ 
int Network::get_fitness() const{
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_fitness." << endl;
        cout << "[INFO][NETWORK]: Exiting get_fitness." << endl;
    #endif

    return fitness;
}

int Network::get_maxlayer() const{
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_maxlayer." << endl;
    #endif

    int maxlayer = 0;
    for(list<Node *>::const_iterator it = hidden_nodes.begin(); it != hidden_nodes.end(); it++){
        if((*it)->get_layer() > maxlayer){
            maxlayer = (*it)->get_layer();
        }
    }

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting get_maxlayer." << endl;
    #endif

    return maxlayer;
}

/** Returns number of nodes.
 * @return int type.
 */ 
int Network::get_num_nodes() const{
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_num_nodes." << endl;
        cout << "[INFO][NETWORK]: Exiting get_num_nodes." << endl;
    #endif

    return in_nodes.size() + out_nodes.size() + hidden_nodes.size();
}

float Network::get_compatibility_distance() const{
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_compatibility_distance." << endl;
        cout << "[INFO][NETWORK]: Exiting get_compatibility_distance." << endl;
    #endif

    return compatibility_distance;
}

/** Network rand_node creates a random hidden node.
 */ 
bool Network::rand_node(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered rand_node." << endl;
    #endif

    hidden_nodes.push_back(new Node(hidden, get_num_nodes()));

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting rand_node." << endl;
    #endif

    return true;
}

/** Network rand_connection creates a random connection between two nodes.
 */ 
bool Network::rand_connection(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered rand_connection." << endl;
    #endif

    int node_one, node_two;

    node_one = rand() % get_num_nodes() + 1;
    node_two = rand() % get_num_nodes() + 1;

    Node *nodeOne = NULL;
    Node *nodeTwo = NULL;

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

    if(nodeOne == NULL || nodeTwo == NULL){
        #if DEBUG
            cout << "\033[31m[ERROR]\033[0m[NETWORK]: Exiting rand_connection." << endl;
        #endif
        return false;
    }

    for(list<Gene *>::iterator it = unique_genes.begin(); it != unique_genes.end(); ++it){
        if((*it)->get_in_node() == node_one && (*it)->get_out_node() == node_two){
           genes.push_back(new Gene(nodeOne, nodeTwo, (*it)->get_inov_id()));

            #if DEBUG
                cout << "[INFO][NETWORK]: Exiting rand_connection." << endl;
            #endif    

            return true;
        }
    }

    genes.push_back(new Gene(nodeOne, nodeTwo, innovation_number));
    unique_genes.push_back(new Gene(nodeOne, nodeTwo, innovation_number));

    innovation_number++;

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting rand_connection." << endl;
    #endif

    return true;    
}

/** Network compare checks if layer of first node is 
 * less than layer of second node.
 * @param Node *one first node
 * @param Node *two second node
 * @return bool
 */ 
bool Network::compare(const Node *one, const Node *two){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered compare." << endl;
        cout << "[INFO][NETWORK]: Exiting compare." << endl;
    #endif

    return one->get_layer() < two->get_layer();
}

/** Network input_run spawns threads that run the input nodes.
 */ 
void Network::input_run(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered input_run." << endl;
    #endif

    for(list<Node *>::iterator itr = in_nodes.begin(); itr != in_nodes.end(); itr++){
        threads.push_back((*itr)->spawn_thread(genes));

        if(threads.size() >= MAX_THREADS){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){
                    #if DEBUG
                        cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                    #endif

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
                #if DEBUG
                    cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                #endif

                (*it)->join();
                if(*it != NULL){
                    delete *it;
                    *it = NULL;
                }
            }
        }
        threads.clear();
    }

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting input_run." << endl;
    #endif
}

/**Network hidden_run sorts the hidden nodes by layer and runs them.
 */ 
void Network::hidden_run(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered hidden_run." << endl;
    #endif

    int last_layer = 1;

    if(hidden_nodes.size() > 0){
        hidden_nodes.sort(compare);

        for (list<Node* >::iterator itr = hidden_nodes.begin(); itr != hidden_nodes.end(); ++itr){
            if(threads.size() >= MAX_THREADS || (*itr)->get_layer() > last_layer){
                last_layer = (*itr)->get_layer();

                for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                    if((*it)->joinable()){
                        #if DEBUG
                            cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                        #endif

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
                    #if DEBUG
                        cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                    #endif

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

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting hidden_run." << endl;
    #endif
}

/**Network output_run spawns threads that run the output nodes.
 */ 
void Network::output_run(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered output_run." << endl;
    #endif

    for(list<Node *>::iterator itr = out_nodes.begin(); itr != out_nodes.end(); itr++){
        threads.push_back((*itr)->spawn_thread(genes));

        if(threads.size() >= MAX_THREADS){
            for(list<boost::thread *>::iterator it = threads.begin(); it != threads.end(); ++it){
                if((*it)->joinable()){    
                    #if DEBUG
                        cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                    #endif

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
                #if DEBUG
                    cout << "\033[33m[THREAD]\033[0m[NETWORK]: Waiting for thread, " << (*it)->get_id() << " to join." << endl;
                #endif

                (*it)->join();
                if(*it != NULL){
                    delete *it;
                    *it = NULL;
                }
            }
        }
        threads.clear();
    }

    #if DEBUG
        cout << "[INFO][NETWORK]: Exiting output_run." << endl;
    #endif
}

/** Returns the number of input nodes.
 * @return Node**
 */ 
list<Node *>* Network::get_input(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_input." << endl;
        cout << "[INFO][NETWORK]: Exiting get_input." << endl;
    #endif

    return &in_nodes;
}

list<Node *>* Network::get_output(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_output." << endl;
        cout << "[INFO][NETWORK]: Exiting get_output." << endl;
    #endif

    return &out_nodes;
}

/** Returns the list of gene pointers.
 * @return list<Gene *>
 */ 
list<Gene *>* Network::get_genes(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_genes." << endl;
        cout << "[INFO][NETWORK]: Exiting get_genes." << endl;
    #endif

    return &genes;
}

/** Returns the hidden nodes.
 * @return list<Node *>
 */ 
list<Node *>* Network::get_hiddennodes(){
    #if DEBUG
        cout << "[INFO][NETWORK]: Entered get_hiddennodes." << endl;
        cout << "[INFO][NETWORK]: Exiting get_hiddennodes." << endl;
    #endif

    return &hidden_nodes;
}
