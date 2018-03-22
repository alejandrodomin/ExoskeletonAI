#include <iostream>
#include <thread>
#include <list>
#include <iterator>

#include <node.hpp>
#include <common.hpp>

using namespace std;

mutex Node::mtx;    // because it is static this tells the compiler it exists.

Node::Node(){}

/** Constructor that sets the type of node it is.
    @param new_type type of node it is, based on the enum list.    
*/
Node::Node(int new_type, int id){
    output_func = 0;
	type = new_type;
    node_id = id;
}

/** Destructor dealocates memory from the heap related to this class.
*/
Node::~Node(){
}

bool Node::set_layer(int layer){
    this->layer = layer;
    return true;
}

/** My function doing something...
    @return thread* returns a pointer to a new thread.
*/
boost::thread * Node::spawn_thread(list<Gene *> genes){
    return new boost::thread (&Node::out_func, this, genes);
}

/** Calculates the value of the node
 *  based on the forward propagation function.
*/
bool Node::out_func(list<Gene *> genes){
    std::lock_guard<std::mutex> lock(mtx); // doesn't need to be unlocked, will automatically unlock when out of function scope

    int index = 0;
    double total = 0;

    if(genes.size() > 0){
        for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); ++it)
            total += (*it)->get_input_node()->get_outputfunc() * (*it)->get_weight();

        total += get_bias();
        set_outputfunc(total);      
        return true;
    }
    else return false;
}

/** Returns the node identification number.
    @return int identification number
*/
int Node::get_nodeid() const{
	return node_id;
}

/** Returns what type of node it is.
 *  @return int type
*/
int Node::get_type() const{
    return type; 
}

/** Returns the layer.
 * @return int type
 */ 
int Node::get_layer() const{
	return layer;	 
}

/** Returns the ouput value of a node
 *  based on forward propogation.
    @return float output value of the node
*/
float Node::get_outputfunc() const{
	return output_func; 
}

/** Sets the value of the variable output_func
    @param num the number for the output_func
*/
bool Node::set_outputfunc(float num){
    output_func = num;
}

/** Finds the layer the node is located in, 
 *  if it is a hidden node.
*/
bool Node::find_layer(list<Gene *> genes){   // the logic in this function seems iffy check it later
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

    return true;
}

/** Returns the bias.
 * @return float output value of bias.
 */ 
float Node::get_bias() const{
    return bias;
}
