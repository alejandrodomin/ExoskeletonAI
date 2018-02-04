#include <iostream>
#include <mutex>
#include <thread>
#include <list>

using namespace std;

#ifndef NODE_HPP
#define NODE_HPP

enum gyro {gyroX = 0, 
            gyroY, gyroZ};
enum type {input = 0, 
            hidden, output};

class Node{
    private:
        int type;
        int layer;
        int node_id;

        float bias;
        float output_func;

        mutex out_mut;
    protected:
    public:
        Node();
        Node(int);
        ~Node();

        void out_func();
        void find_layer();
        void set_outputfunc(float);

        int get_type();
        int get_nodeid();

        float get_outputfunc();

        thread* spawn_thread();
};
#endif