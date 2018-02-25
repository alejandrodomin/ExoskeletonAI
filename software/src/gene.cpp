#include <iostream>
#include <cstdlib>

#include <common.hpp>
#include <gene.hpp>

using namespace std;

/** Gene constructor, creates a Gene
 *  that knows which two nodes it ties together.
*/
Gene::Gene(Node* input_node, Node* output_node, int inov_number){
    cout << "[INFO][GENE]:\t Entered Gene::Gene(Node *, Node *)." << endl;

    in_node = input_node->get_nodeid();
    out_node = output_node->get_nodeid();

    this->input_node = input_node;
    this->output_node = output_node;

    innovation_number = inov_number;

    weight = ((float)(rand() % 100 + 1)) / 100.0;

    std::ofstream exoAIStats;
    exoAIStats.open("exoAIStats.txt", ios::out | ios::app);
    
    exoAIStats << "Number of Species: " << num_species << endl;
    exoAIStats << "Number of Networks: " << num_networks << endl;
    exoAIStats << "Number of Nodes: " << num_nodes << endl;
    exoAIStats << "Number of Genes: " << num_genes << endl;
    
    exoAIStats.close();

    cout << "[INFO][GENE]:\t Exited  Gene::Gene(Node *, Node *)." << endl;
}

/** Destructor, deletes memory allocated 
 *  by the class in the heap.
*/
Gene::~Gene(){
    cout << "[INFO][GENE]:\t Entered Gene::~Gene()." << endl;

    if(input_node != NULL){
        delete input_node;
        input_node = NULL;
    }
    if(output_node != NULL){
        delete output_node;
        output_node = NULL;
    }

    cout << "[INFO][GENE]:\t Exited  Gene::~Gene()." << endl;
}

/** Sets the weight variable to a new value.
    @param newweight the new weight
*/
// void Gene::set_weight(float newweight){
//     cout << "[INFO][GENE]:\t Entered Gene::set_weight(float)." << endl;
//     weight = newweight;
//     cout << "[INFO][GENE]:\t Exited  Gene::set_weight(float)." << endl;
// }

/** Returns the value of the innovation number variable.
 * @return int returns innovation_number
 */
int Gene::get_inov_id() const{
    return innovation_number;
}

int Gene::get_in_node() const{
    return in_node;
}

int Gene::get_out_node() const{
    return out_node;
}

/** Returns the value of the weight variable.
    @return float returns weight 
*/
float Gene::get_weight() const{
    cout << "[INFO][GENE]:\t Entered Gene::get_weight()." << endl;
    cout << "[INFO][GENE]:\t Exited  Gene::get_weight()." << endl;
    return weight;
}

/** Returns a node pointer to the input node.
    @return Node* node pointer
*/
Node* Gene::get_input_node() const{
    cout << "[INFO][GENE]:\t Entered Gene::get_input_node()." << endl;
    cout << "[INFO][GENE]:\t Exited  Gene::get_input_node()." << endl;
    return input_node;
}

/** Returns a node pointer to the node that called this
 *  gene function.
    @return Node* node pointer
*/
Node* Gene::get_output_node() const{
   cout << "[INFO][GENE]:\t Entered Gene::get_you_node()." << endl;
   cout << "[INFO][GENE]:\t Exited  Gene::get_you_node()." << endl;
   return output_node;
}
