#include <iostream>
#include <thread>

#include "node.h"

using namespace std;

Node::Node()
{

}

Node::Node(int new_type)
{
    type = new_type;
}

Node::~Node()
{

}

thread* Node::spawn_thread()
{
    return new thread(&Node::out_func, this);
}

void Node::out_func()
{
    out_mut.lock();

    int index = 0;
    float total = 0;
    
    while (inputs[index] != NULL) 
    {
       total += inputs[index]->get_outputfunc() * weights_input[index];
       index++;
    }

    total += bias;
    this->set_outputfunc(total);

    out_mut.unlock();
}

int Node::get_nodeid()
{
    return node_id;
}

int Node::get_type()
{
    return type;
}

float Node::get_outputfunc()
{
    return output_func;
}

void Node::set_outputfunc(float num)
{
    output_func = num;
}

