#include <iostream>

#include "output.h"

using namespace std;

Output::Output(): Node(output){}

Output::~Output(){}

void Output::add_input(Node *node)
{
    inputs.push_back(node);
}

void Output::add_output(Node *node)
{
    outputs.push_back(node);
}
