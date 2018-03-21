#include <iostream>
#include <cstdlib>

#include <common.hpp>
#include <gene.hpp>

using namespace std;

/** Gene constructor, creates a Gene
 *  that knows which two nodes it ties together.
*/
Gene::Gene(Node *input_node, Node *output_node, int inov_number){
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::Gene(Node*,Node*,int)." << endl;

    this->input_node = input_node;
    this->output_node = output_node;
    
    in_node = input_node->get_nodeid();
    out_node = output_node->get_nodeid();

    innovation_number = inov_number;
    weight = ((float)(rand() % 100 + 1)) / 100.0;

    if(comment == true)   
      cout << "[INFO][GENE]: Exited Gene::Gene(Node*,Node*,int)." << endl;
}

/** Destructor, deletes memory allocated 
 *  by the class in the heap.
*/
Gene::~Gene(){
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::~Gene()." << endl;

    if(input_node != NULL){
        delete input_node;
        input_node = NULL;
    }
    if(output_node != NULL){
        delete output_node;
        output_node = NULL;
    }

    if(comment == true)   
      cout << "[INFO][GENE]: Exited Gene::~Gene()." << endl;
}

/** Returns the value of the innovation number variable.
 * @return int returns innovation_number
 */
int Gene::get_inov_id() const{
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::get_inov_id() const." << endl;
    if(comment == true)   
      cout << "[INFO][GENE]: Exiting Gene::get_inov_id() const." << endl;

    return innovation_number;
}

int Gene::get_in_node() const{
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::get_in_node() const." << endl;
    if(comment == true)   
      cout << "[INFO][GENE]: Exiting Gene::get_in_node() const." << endl;

    return in_node;
}

int Gene::get_out_node() const{
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::get_out_node() const." << endl;
    if(comment == true)   
      cout << "[INFO][GENE]: Exiting Gene::get_out_node() const." << endl;

    return out_node;
}

/** Returns the value of the weight variable.
    @return float returns weight 
*/
float Gene::get_weight() const{
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::get_weight() const." << endl;
    if(comment == true)   
      cout << "[INFO][GENE]: Exited  Gene::get_weight() const." << endl;

    return weight;
}

/** Returns a node pointer to the input node.
    @return Node* node pointer
*/
Node* Gene::get_input_node() const{
    if(comment == true)   
      cout << "[INFO][GENE]: Entered Gene::get_input_node() const." << endl;
    if(comment == true)   
      cout << "[INFO][GENE]: Exited  Gene::get_input_node() const." << endl;

    return input_node;
}

/** Returns a node pointer to the node that called this
 *  gene function.
    @return Node* node pointer
*/
Node* Gene::get_output_node() const{
   if(comment == true)   
     cout << "[INFO][GENE]: Entered Gene::get_output_node() const." << endl;
   if(comment == true)   
     cout << "[INFO][GENE]: Exited  Gene::get_output_node() const." << endl;
   
   return output_node;
}
