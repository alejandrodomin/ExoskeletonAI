#include <iostream>
#include "global.h"

using namespace std;
#ifndef OUTPUT_H
#define OUTPUT_H

class Output: public Node 
{
public:
    virtual void add_input(Node *node);
    virtual void add_output(Node *node);
};
#endif