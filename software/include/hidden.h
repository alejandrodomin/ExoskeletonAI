#include <iostream>

#include "node.h"

using namespace std;

#ifndef HIDDEN_H
#define HIDDEN_H

class Hidden: public Node 
{
    private:
        int layer;

    public:
        Hidden();
        ~Hidden();

        void find_layer();

        int get_layer();

        virtual void add_input(Node *node);
        virtual void add_output(Node *node);    
};

#endif