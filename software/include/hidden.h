#include <iostream>
#include "global.h"

using namespace std;
#ifndef HIDDEN_H
#define HIDDEN_H

class Hidden: public Node 
{
private:
    Node **inputs;
    Node ** outputs;
public:
    virtual void add_input(Node *node);
    virtual void add_output(Node *node);

    
};
#endif