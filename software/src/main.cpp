#include <iostream>

#include "network.hpp"

using namespace std;

int main()
{
   // create a network;
   Network *net1 = new Network();

   bool stagnant = false;
   while(!stagnant)
   {
      net1->run();
      stagnant = net1->fitness();
   }

   net1->mutate();


   delete net1;
}