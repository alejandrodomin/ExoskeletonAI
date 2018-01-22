#include <iostream>

#include "node.h"

using namespace std;

Node::Node()
{

}

Node::~Node()
{

}

void Node::out_func()
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


float Node::get_outputfunc()
{
    return output_func;
}

void Node::set_outputfunc(float num)
{
    output_func = num;
}

