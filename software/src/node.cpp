#include <iostream>
#include <thread>
#include <list>
#include <iterator>

#include <node.hpp>
#include <common.hpp>

using namespace std;

mutex Node::mtx;    // because it is static this tells the compiler it exists.

Node::Node()
{
    #if DEBUG
        cout << "[INFO][NODE]: Entered empty constructor." << endl;
        cout << "[INFO][NODE]: Exiting empty constructor." << endl;
    #endif
}

/** Constructor that sets the type of node it is.
    @param new_type type of node it is, based on the enum list.    
*/
Node::Node(int new_type, int id){
    #if DEBUG
        cout << "[INFO][NODE]: Entered constructor." << endl;
    #endif

    output_func = 0;
	type = new_type;
    node_id = id;

    #if DEBUG
        cout << "[INFO][NODE]: Exiting constructor." << endl;
    #endif
}

/** Destructor dealocates memory from the heap related to this class.
*/
Node::~Node(){
    #if DEBUG
        cout << "[INFO][NODE]: Entered empty de-constructor." << endl;
        cout << "[INFO][NODE]: Exiting empty de-constructor." << endl;
    #endif
}

bool Node::set_layer(int layer){
    #if DEBUG
        cout << "[INFO][NODE]: Entered set_layer." << endl;
    #endif

    this->layer = layer;

    #if DEBUG
        cout << "[INFO][NODE]: Exiting set_layer." << endl;
    #endif

    return true;
}

/** My function doing something...
    @return thread* returns a pointer to a new thread.
*/
boost::thread * Node::spawn_thread(list<Gene *> genes){
    #if DEBUG
        cout << "[INFO][NODE]: Entered spawn_thread." << endl;
        cout << "[INFO][NODE]: Exiting spawn_thread." << endl;
    #endif

    return new boost::thread (&Node::out_func, this, genes);
}

/** Calculates the value of the node
 *  based on the forward propagation function.
*/
bool Node::out_func(list<Gene *> genes){
    std::lock_guard<std::mutex> lock(mtx); // doesn't need to be unlocked, will automatically unlock when out of function scope

    #if DEBUG
        cout << "[INFO][NODE]: Entered out_func." << endl;
    #endif

    double total = 0;

    if(genes.size() > 0){
        for(list<Gene *>::iterator it = genes.begin(); it != genes.end(); ++it)
            total += (*it)->get_input_node()->get_outputfunc() * (*it)->get_weight();

        total += get_bias();
        set_outputfunc(total);
        
        #if DEBUG
            cout << "[INFO][NODE]: Exiting out_func." << endl;
        #endif

        return true;
    }
    else{
        #if DEBUG
            cout << "\033[31m[ERROR]\033[0m[NODE]: Exiting out_func." << endl;
        #endif

        return false;
    }
}

/** Returns the node identification number.
    @return int identification number
*/
int Node::get_nodeid() const{
    #if DEBUG
        cout << "[INFO][NODE]: Entered get_nodeid." << endl;
        cout << "[INFO][NODE]: Exiting get_nodeid." << endl;
    #endif

	return node_id;
}

/** Returns what type of node it is.
 *  @return int type
*/
int Node::get_type() const{
    #if DEBUG
        cout << "[INFO][NODE]: Entered get_type." << endl;
        cout << "[INFO][NODE]: Exiting get_type." << endl;
    #endif

    return type; 
}

/** Returns the layer.
 * @return int type
 */ 
int Node::get_layer() const{
    #if DEBUG
        cout << "[INFO][NODE]: Entered get_layer." << endl;
        cout << "[INFO][NODE]: Exiting get_layer." << endl;
    #endif

	return layer;	 
}

/** Returns the ouput value of a node
 *  based on forward propogation.
    @return float output value of the node
*/
float Node::get_outputfunc() const{
    #if DEBUG
        cout << "[INFO][NODE]: Entered get_outputfunc." << endl;
        cout << "[INFO][NODE]: Exiting get_outputfunc." << endl;
    #endif

	return output_func; 
}

/** Sets the value of the variable output_func
    @param num the number for the output_func
*/
bool Node::set_outputfunc(float num){
    #if DEBUG
        cout << "[INFO][NODE]: Entered set_outputfunc." << endl;
    #endif

    output_func = num;

    #if DEBUG
        cout << "[INFO][NODE]: Exiting set_outputfunc." << endl;
    #endif

    return true;
}

/** Finds the layer the node is located in, 
 *  if it is a hidden node.
*/
bool Node::find_layer(list<Gene *> genes){   // the logic in this function seems iffy check it later
    #if DEBUG
        cout << "[INFO][NODE]: Entered find_layer." << endl;
    #endif

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

    #if DEBUG
        cout << "[INFO][NODE]: Exiting find_layer." << endl;
    #endif

    return true;
}

/** Returns the bias.
 * @return float output value of bias.
 */ 
float Node::get_bias() const{
    #if DEBUG
        cout << "[INFO][NODE]: Entered get_bias." << endl;
        cout << "[INFO][NODE]: Exiting get_bias." << endl;
    #endif

    return bias;
}
