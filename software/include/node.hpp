#include <iostream>
#include <mutex>
#include <thread>
#include <list>

using namespace std;

#ifndef NODE_H
#define NODE_H

enum gyro {gyroX = 0, gyroY, gyroZ};
enum type {input = 0, hidden, output};

class Node 
{
    private:
        int node_id;
        int type;
        int layer;

        float bias;
        float output_func;
        
        float* weights_input;

        mutex out_mut;

        list<Node *> inputs;
        list<Node *> outputs;
    protected:
    public:
        Node();
        Node(int);
        ~Node();

        void out_func();
        void find_layer();
        void add_input(Node *);
        void add_output(Node *);
        void set_outputfunc(float);

        int get_type();
        int get_nodeid();

        float get_outputfunc();

        thread* spawn_thread();
};
#endif