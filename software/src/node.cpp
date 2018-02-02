#include <iostream>
#include <thread>
#include <list>
#include <iterator>

#include "node.hpp"

using namespace std;

Node::Node(){

}

Node::Node(int new_type{
    type = new_type;
}

Node::~Node(){

}

thread* Node::spawn_thread(){
    cout << "Entering Node::spawn_thread" << endl;
    cout << "Exiting Node::spawn_thread" << endl;
    return new thread(&Node::out_func, this);
}

void Node::out_func(){
    cout << "Entering Node::out_func" << endl;
    out_mut.lock();

    int index = 0;
    float total = 0;

    for(list<Node *>::iterator it = inputs.begin(); it != inputs.end(); ++it)
        total += (*it)->get_outputfunc() * weights_input[index];

    total += bias;
    set_outputfunc(total);

    out_mut.unlock();
    cout << "Exiting Node::out_func()" << endl;
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

void Node::add_input(Node *node){
    inputs.push_back(node);
}

void Node::add_output(Node *node){
    outputs.push_back(node);
}

void Node::find_layer(){   // the logic in this function seems iffy check it later
    bool allInput = true;
    int maxLayer = 0;
    int index = 0;
   
    for(list<Node *>::iterator it = inputs.begin(); it != inputs.end(); ++it){
        if((*it)->get_type() == hidden){
            allInput = false;
         
            if (maxLayer < (*it)->layer)
                maxLayer = (*it)->layer;
        }
        index++;
    }
    
    if (allInput)
        layer = 1;
    else layer = maxLayer + 1;
}
