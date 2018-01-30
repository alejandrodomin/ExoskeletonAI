#include <iostream>

#include "node.h"

using namespace std;
#ifndef INPUT_H
#define INPUT_H

class Input: public Node 
{

private:
    float* hardware_inputs;
public:
    Input();
   ~Input();
};
#endif
