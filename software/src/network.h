#include <iostream>

using namespace std;

#ifndef NETWORK_H
#define NETWORK_H

class Network: public Species
{
   private:
      Node **inputs;
      Node **outputs;
      // outputs
   protected:
      Node **nodes;
   public:
      Network();
      ~Network(); // destructor deletes heap memory

      void get_input();       // names for these can be changed later
      void use_output();

      bool rand_node();
      bool rand_connection();
};

#endif