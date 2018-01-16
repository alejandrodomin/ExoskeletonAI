#include "node.h"
#include <iostream>

using namespace std;

Node::Node()
{

}

Node::~Node()
{

}

void Node::out_func(Node *inputs, float *weights_input, float bias)
{
    int index = 0;
    float total = 0;
    
    while (inputs[i] != NULL) 
    {
       total += input[index].output_func * weights_input[index];
       index++;
    }

    total += bias;
    this.output_func = total;
}