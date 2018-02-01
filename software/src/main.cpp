#include <iostream>

#include "network.hpp"

using namespace std;

void network_run(Network *net);
static bool deleteAll(Network * theElement); 

int main()
{
   cout << "Entered main." << endl;
   // create a network;
   Network *net1 = new Network();

   network_run(net1);

   net1->mutate();
   list<Network *> networks = net1->reproduce();

   for(list<Network *>::iterator it = networks.begin(); it != networks.end(); ++it)
      network_run(*it);

   delete net1;
   networks.remove_if(deleteAll);

   cout << "Exiting main." << endl;
   return 0;
}

void network_run(Network *net)
{
   int stagnantCount = 0;

   while(stagnantCount < 15)
   {
      net->run();
      
      if(net->fitness())
         stagnantCount++;
      else stagnantCount = 0;
   }
}

static bool deleteAll(Network * theElement ) 
{ 
   delete theElement; 
   return true; 
}
