#include <iostream>

#include "node.h"

using namespace std;
#ifndef INPUT_H
#define INPUT_H

class Input: public Node 
{

private:
    float* inputs;

    typedef Node super;
public:
    Input();
   ~Input();

    virtual void add_input(Node *node);
    virtual void add_output(Node *node);
};
#endif
