#include <iostream>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node 
{
    private:
        Node **inputs;
        Node **outputs;
        float output_func;
        float *weights_input;
        float bias;
        int node_id;
    protected:
        
    public:
        Node();
        ~Node();

        void out_func();

        int get_nodeid();

        float get_outputfunc();
        void set_outputfunc(float);

        virtual void add_input(Node *)=0;
        virtual void add_output(Node *)=0;
};
#endif