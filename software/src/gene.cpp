#include <iostream>

#include "gene.hpp"

using namespace std;

extern static int global_innovation_id;

/** Empty constructor, creates a Gene object.
*/
Gene::Gene(){
   cout << "[INFO][GENE]: Entered Gene::Gene()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::Gene()." << endl;

   innovation_number = global_innovation_id;
   global_innovation_id++;
}

/** Gene constructor, creates a Gene
 *  that knows which two nodes it ties together.
*/
Gene::Gene(Node* newinput_node, Node* newyou_node){
   cout << "[INFO][GENE]: Entered Gene::Gene(Node *, Node *)." << endl;

   input_node = newinput_node;
   you_node = newyou_node;

   cout << "[INFO][GENE]: Exited  Gene::Gene(Node *, Node *)." << endl;
}

/** Destructor, deletes memory allocated 
 *  by the class in the heap.
*/
Gene::~Gene(){
   cout << "[INFO][GENE]: Entered Gene::~Gene()." << endl;

    if(input_node != NULL){
        delete [] input_node;
        input_node = NULL;
    }
    if(you_node != NULL){
        delete [] you_node;
        you_node = NULL;
    }

   cout << "[INFO][GENE]: Exited  Gene::~Gene()." << endl;
}

/** Sets the weight variable to a new value.
    @param neweight the new weight
*/
void Gene::set_weight(float newweight){
   cout << "[INFO][GENE]: Entered Gene::set_weight(float)." << endl;

   weight = newweight;

   cout << "[INFO][GENE]: Exited  Gene::set_weight(float)." << endl;
}

/** Returns the value of the weight variable.
    @return float returns weight 
*/
float Gene::get_weight(){
   cout << "[INFO][GENE]: Entered Gene::get_weight()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::get_weight()." << endl;
   return weight;
}

/** Returns a node pointer to the input node.
    @return Node* node pointer
*/
Node* Gene::get_input_node(){
   cout << "[INFO][GENE]: Entered Gene::get_input_node()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::get_input_node()." << endl;
   return input_node;
}

/** Returns a node pointer to the node that called this
 *  gene function.
    @return Node* node pointer
*/
Node* Gene::get_you_node(){
   cout << "[INFO][GENE]: Entered Gene::get_you_node()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::get_you_node()." << endl;
   return you_node;
}
