#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

#ifndef NODE_H
#define NODE_H

enum gyro {gyroX = 0, gyroY, gyroZ};
enum type {input = 0, hidden, output};

class Node 
{
    private:
        Node **inputs;
        Node **outputs;

        float output_func;
        float *weights_input;
        float bias;
        
        int node_id;
        int type;

        mutex out_mut;
    protected:
        
    public:
        Node();
        Node(int type);
        ~Node();

        thread* spawn_thread();
        void out_func();

        int get_nodeid();
        int get_type();

        float get_outputfunc();
        void set_outputfunc(float);

        virtual void add_input(Node *)=0;
        virtual void add_output(Node *)=0;
};
#endif