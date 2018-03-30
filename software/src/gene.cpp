#include <iostream>
#include <cstdlib>

#include <common.hpp>
#include <gene.hpp>

using namespace std;

/** Gene constructor, creates a Gene
 *  that knows which two nodes it ties together.
*/
Gene::Gene(Node *input_node, Node *output_node, int inov_number){
    #if DEBUG
        cout << "[INFO][GENE]: Entered constructor." << endl;
    #endif

    this->input_node = input_node;
    this->output_node = output_node;
    
    in_node = input_node->get_nodeid();
    out_node = output_node->get_nodeid();

    innovation_number = inov_number;
    weight = ((float)(rand() % 100 + 1)) / 100.0;

    #if DEBUG
        cout << "[INFO][GENE]: Exiting constructor." << endl;
    #endif
}

/** Destructor, deletes memory allocated 
 *  by the class in the heap.
*/
Gene::~Gene(){
    #if DEBUG
        cout << "[INFO][GENE]: Entered de-constructor." << endl;
    #endif

    if(input_node != NULL){
        delete input_node;
        input_node = NULL;
    }
    if(output_node != NULL){
        delete output_node;
        output_node = NULL;
    }

    #if DEBUG
        cout << "[INFO][GENE]: Exiting de-constructor." << endl;
    #endif
}

/** Returns the value of the innovation number variable.
 * @return int returns innovation_number
 */
int Gene::get_inov_id() const{
    #if DEBUG
        cout << "[INFO][GENE]: Entered get_inov_id." << endl;
        cout << "[INFO][GENE]: Exiting get_inov_id." << endl;
    #endif

    return innovation_number;
}

int Gene::get_in_node() const{
    #if DEBUG
        cout << "[INFO][GENE]: Entered get_in_node." << endl;
        cout << "[INFO][GENE]: Exiting get_in_node." << endl;
    #endif

    return in_node;
}

int Gene::get_out_node() const{
    #if DEBUG
        cout << "[INFO][GENE]: Entered get_out_node." << endl;
        cout << "[INFO][GENE]: Exiting get_out_node." << endl;
    #endif

    return out_node;
}

/** Returns the value of the weight variable.
    @return float returns weight 
*/
float Gene::get_weight() const{
    #if DEBUG
        cout << "[INFO][GENE]: Entered get_weight." << endl;
        cout << "[INFO][GENE]: Exiting get_weight." << endl;
    #endif

    return weight;
}

/** Returns a node pointer to the input node.
    @return Node* node pointer
*/
Node* Gene::get_input_node() const{
    #if DEBUG
        cout << "[INFO][GENE]: Entered get_input_node." << endl;
        cout << "[INFO][GENE]: Exiting get_input_node." << endl;
    #endif

    return input_node;
}

/** Returns a node pointer to the node that called this
 *  gene function.
    @return Node* node pointer
*/
Node* Gene::get_output_node() const{
    #if DEBUG
        cout << "[INFO][GENE]: Entered get_output_node." << endl;
        cout << "[INFO][GENE]: Exiting get_output_node." << endl;
    #endif

    return output_node;
}
