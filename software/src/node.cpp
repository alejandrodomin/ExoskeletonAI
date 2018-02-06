#include <iostream>
#include <thread>
#include <list>
#include <iterator>

#include "node.hpp"

using namespace std;

Node::Node(){

}

Node::Node(int new_type){
    type = new_type;
}

Node::~Node(){

}

thread* Node::spawn_thread(){
    cout << "[INFO][NODE]:\t Entered Node::spawn_thread()" << endl;
    cout << "[INFO][NODE]:\t Exiting Node::spawn_thread()" << endl;
    return new thread(&Node::out_func, this);
}

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

void Node::add_gene(Node *snode, Node * onode){
    genes.push_back(new Gene(snode, onode));
}

int Node::get_nodeid(){
    return node_id;
}

int Node::get_type(){
    return type;
}

float Node::get_outputfunc(){
    cout << "Entering Node::get_outputfunc" << endl;
    cout << "Exiting Node::get_outputfunc" << endl;
    return output_func;
}

void Node::set_outputfunc(float num){
    output_func = num;
}

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
