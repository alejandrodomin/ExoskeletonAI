#include <iostream>
#include <thread>
#include <list>
#include <iterator>

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
    
    for(list<Node *>::iterator it = inputs.begin(); it != inputs.end(); ++it)
        total += (*it)->get_outputfunc() * weights_input[index];

    total += bias;
    set_outputfunc(total);

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

void Node::add_input(Node *node)
{
    inputs.push_back(node);
}

void Node::add_output(Node *node)
{
    outputs.push_back(node);
}

