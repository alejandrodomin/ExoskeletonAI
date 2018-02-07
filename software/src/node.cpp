#include <iostream>
#include <thread>
#include <list>
#include <iterator>

#include "node.hpp"

using namespace std;

/** Constructor with no parameters.
 *  Creates a new node with nothing initialized.
*/
Node::Node(){

}

/** Constructor that sets the type of node it is.
    @param new_type type of node it is, based on the enum list.    
*/
Node::Node(int new_type){
    type = new_type;
}

/** Destructor dealocates memory from the heap related to this class.
*/
Node::~Node(){

}

/** My function doing something...
    @return thread* returns a pointer to a new thread.
*/
thread* Node::spawn_thread(){
    cout << "[INFO][NODE]:\t Entered Node::spawn_thread()" << endl;
    cout << "[INFO][NODE]:\t Exiting Node::spawn_thread()" << endl;
    return new thread(&Node::out_func, this);
}

/** Calculates the value of the node
 *  based on the forward propagation function.
*/
void Node::out_func(){
    cout << "[INFO][NODE]:\t Entered Node::out_func()" << endl;
    out_mut.lock();

    int index = 0;
    float total = 0;

    for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); ++it)
        total += (*it)->get_input_node()->get_outputfunc() * (*it)->get_weight();

    total += bias;
    set_outputfunc(total);

    out_mut.unlock();
    cout << "[INFO][NODE]:\t Exiting Node::out_func()" << endl;
}

/** My function doing something...
    @param snode* pointer to the starting node
    @param onode* pointer to the output node usually the node that 
                    calls this function.
*/
void Node::add_gene(Node *snode, Node * onode){
    genes.push_back(new Gene(snode, onode));
}

/** Returns the node identification number.
    @return int identification number
*/
int Node::get_nodeid(){
    return node_id;
}

/** Returns what type of node it is.
 *  @return int type
*/
int Node::get_type(){
    return type;
}

/** Returns the ouput value of a node
 *  based on forward propogation.
    @return float output value of the node
*/
float Node::get_outputfunc(){
    cout << "Entering Node::get_outputfunc" << endl;
    cout << "Exiting Node::get_outputfunc" << endl;
    return output_func;
}

/** Sets the value of the variable output_func
    @param num the number for the output_func
*/
void Node::set_outputfunc(float num){
    output_func = num;
}

/** Finds the layer the node is located in, 
 *  if it is a hidden node.
*/
void Node::find_layer(){   // the logic in this function seems iffy check it later
    bool allInput = true;
    int maxLayer = 0;
    int index = 0;
   
    for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); ++it){
        if((*it)->get_input_node()->get_type() == hidden){
            allInput = false;
         
            if (maxLayer < (*it)->get_input_node()->layer)
                maxLayer = (*it)->get_input_node()->layer;
        }
        index++;
    }
    
    if (allInput)
        layer = 1;
    else layer = maxLayer + 1;
}
