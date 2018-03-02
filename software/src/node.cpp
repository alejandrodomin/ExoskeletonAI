#include <iostream>
#include <thread>
#include <list>
#include <iterator>

#include <node.hpp>
#include <common.hpp>

using namespace std;

mutex Node::mtx;    // because it is static this tells the compiler it exists.

/** Constructor that sets the type of node it is.
    @param new_type type of node it is, based on the enum list.    
*/
Node::Node(int new_type, int id){
    cout << "[INFO][NODE]: Entered Node::Node(int)." << endl;
    
    output_func = 0;
	type = new_type;
    node_id = id;
    
    cout << "[INFO][NODE]: Exiting Node::Node(int)." << endl;
}

/** Destructor dealocates memory from the heap related to this class.
*/
Node::~Node(){
    cout << "[INFO][NODE]: Entered Node::~Node()." << endl;
    cout << "[INFO][NODE]: Exiting Node::~Node()." << endl;
}

void Node::set_layer(int layer){
    this->layer = layer;
}

/** My function doing something...
    @return thread* returns a pointer to a new thread.
*/
thread* Node::spawn_thread(list<unique_ptr<Gene>> genes){
    cout << "[INFO][NODE]: Entered Node::spawn_thread()" << endl;
    cout << "[INFO][NODE]: Exiting Node::spawn_thread()" << endl;

    return new thread(&Node::out_func, this, genes);
}

/** Calculates the value of the node
 *  based on the forward propagation function.
*/
void Node::out_func(list<unique_ptr<Gene>> genes){
    cout << "[INFO][NODE]: Entered Node::out_func()" << endl;

    std::lock_guard<std::mutex> lock(mtx); // doesn't need to be unlocked, will automatically unlock when out of function scope

    int index = 0;
    double total = 0;

    if(genes.size() > 0){
        for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); ++it)
            total += (*it)->get_input_node()->get_outputfunc() * (*it)->get_weight();

        total += get_bias();
        set_outputfunc(total);      // problem in seg fault lies here goes out of scope mutex is unlocked others try to acces the same data, seg fault
    }

    cout << "[INFO][NODE]: Exiting Node::out_func()." << endl;
}

/** Returns the node identification number.
    @return int identification number
*/
int Node::get_nodeid() const{
    cout << "[INFO][NODE]: Entered Node::get_nodeid()." << endl;
    cout << "[INFO][NODE]: Exiting Node::get_nodeid()." << endl;
   
	return node_id;
}

/** Returns what type of node it is.
 *  @return int type
*/
int Node::get_type() const{
    cout << "[INFO][NODE]: Entered Node::get_type()." << endl;
    cout << "[INFO][NODE]: Exiting Node::get_type()." << endl;
    
    return type; 
}

/** Returns the layer.
 * @return int type
 */ 
int Node::get_layer() const{
    cout << "[INFO][NODE]: Entered Node::get_layer()." << endl;
    cout << "[INFO][NODE]: Exiting Node::get_layer()." << endl;
   
	return layer;	 
}

/** Returns the ouput value of a node
 *  based on forward propogation.
    @return float output value of the node
*/
float Node::get_outputfunc() const{
    cout << "[INFO][NODE]: Entered Node::get_outputfunc()." << endl;
    cout << "[INFO][NODE]: Exiting Node::get_outputfunc()." << endl;
   
	return output_func; 
}

/** Sets the value of the variable output_func
    @param num the number for the output_func
*/
void Node::set_outputfunc(float num){
    cout << "[INFO][NODE]: Entered Node::set_outputfunc(float)." << endl;

    output_func = num;

    cout << "[INFO][NODE]: Exiting Node::set_outputfunc(float)." << endl;
}

/** Finds the layer the node is located in, 
 *  if it is a hidden node.
*/
void Node::find_layer(list<unique_ptr<Gene>> genes){   // the logic in this function seems iffy check it later
    cout << "[INFO][NODE]: Entered Node::find_layer(list<Gene*>)." << endl;
   
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

    cout << "[INFO][NODE]: Exiting Node::find_layer(list<Gene*>)." << endl;
}

/** Returns the bias.
 * @return float output value of bias.
 */ 
float Node::get_bias() const{
    cout << "[INFO][NODE]: Entered Node::get_bias()." << endl;
    cout << "[INFO][NODE]: Exiting Node::get_bias()." << endl;
    
    return bias;
}
