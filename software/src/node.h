#include <iostream>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node 
{
    private:
        Node *inputs;
        Node *outputs;
        float output_func;
        float *weights_input;
        float bias;
        int node_id;

    public:
        Node();
        ~Node();

        void out_func(Node *, float *, float);

};
#endif