#include <iostream>

#include "common.hpp"
#include "gene.hpp"

using namespace std;

/** Gene constructor, creates a Gene
 *  that knows which two nodes it ties together.
*/
Gene::Gene(Node* newinput_node, Node* newoutput_node){
   cout << "[INFO][GENE]:\t Entered Gene::Gene(Node *, Node *)." << endl;

   input_node = newinput_node;
   output_node = newoutput_node;

   innovation_number = global_innovation_id;
   global_innovation_id++;

std::ofstream exoAIStats;
   exoAIStats.open("exoAIStats.txt", ios::out | ios::app);
   exoAIStats << "New Gene." << endl;
   exoAIStats.close();

   cout << "[INFO][GENE]:\t Exited  Gene::Gene(Node *, Node *)." << endl;
}

/** Destructor, deletes memory allocated 
 *  by the class in the heap.
*/
Gene::~Gene(){
   cout << "[INFO][GENE]:\t Entered Gene::~Gene()." << endl;

    if(input_node != NULL){
        delete [] input_node;
        input_node = NULL;
    }
    if(output_node != NULL){
        delete [] output_node;
        output_node = NULL;
    }

   cout << "[INFO][GENE]:\t Exited  Gene::~Gene()." << endl;
}

/** Sets the weight variable to a new value.
    @param newweight the new weight
*/
void Gene::set_weight(float newweight){
   cout << "[INFO][GENE]:\t Entered Gene::set_weight(float)." << endl;

   weight = newweight;

   cout << "[INFO][GENE]:\t Exited  Gene::set_weight(float)." << endl;
}

/** Returns the value of the innovation number variable.
 * @return int returns innovation_number
 */
int Gene::get_inov_id() const{
    return innovation_number;
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
Node* Gene::get_ouput_node() const{
   cout << "[INFO][GENE]:\t Entered Gene::get_you_node()." << endl;
   cout << "[INFO][GENE]:\t Exited  Gene::get_you_node()." << endl;
   return output_node;
}
