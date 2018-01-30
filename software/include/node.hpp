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
        list<Node *> inputs;
        list<Node *> outputs;

        float output_func;
        float *weights_input;
        float bias;
        
        int node_id;
        int type;

        mutex out_mut;
    protected:
        
    public:
        Node();
        Node(int);
        ~Node();

        thread* spawn_thread();
        void out_func();

        int get_nodeid();
        int get_type();

        float get_outputfunc();
        void set_outputfunc(float);

        void add_input(Node *);
        void add_output(Node *);
};
#endif