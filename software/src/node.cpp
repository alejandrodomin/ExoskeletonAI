#include "node.h"
#include <iostream>

using namespace std;

Node::Node()
{

}

Node::~Node()
{

}

void Node::out_func(Node **inputs, float *weights_input, float bias)
{
    int index = 0;
    float total = 0;
    
    while (inputs[index] != NULL) 
    {
       total += inputs[index]->get_outputfunc() * weights_input[index];
       index++;
    }

    total += bias;
    this->set_outputfunc(total);
}

int Node::get_nodeid()
{
    return node_id;
}

void Node::set_nodeid(int newid)
{
    node_id = newid;
}

float Node::get_outputfunc()
{
    return output_func;
}

void Node::set_outputfunc(float num)
{
    output_func = num;
}

void Node::add_input(Node *node)
{

}

void Node::add_output(Node *node)
{
    
}