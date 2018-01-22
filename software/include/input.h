#include <iostream>
#include "global.h"

using namespace std;
#ifndef INPUT_H
#define INPUT_H

enum gyro {gyroX, gyroY, gyroZ} gyro_values;

class Input: public Node 
{

private:
    float* inputs;
public:
    Input();
   ~Input();
    virtual void add_input(Node *node);
    virtual void add_output(Node *node);
};
#endif
