#include <iostream>
#include "global.h"

using namespace std;
#ifndef INPUT_H
#define INPUT_H

class Input: public Node 
{
public:
    virtual void add_input(Node *node);
    virtual void add_output(Node *node);
};
#endif
