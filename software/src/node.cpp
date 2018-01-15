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
    int i;
    float total = 0;
    while (inputs[i] != NULL) 
    {
       total += input[i].output_func * weights_input[i];
       i++;
    }

    total += bias;
    this.output_func = total;
}