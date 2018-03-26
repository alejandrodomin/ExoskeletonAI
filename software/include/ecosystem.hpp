#ifndef ECOSYSTEM_HPP
#define ECOSYSTEM_HPP

#include <list>

#include <common.hpp>
#include <species.hpp>
#include <network.hpp>
#include <gene.hpp>

using namespace std;

class Ecosystem{
private:
   list<Species *> organisms;
   list<Network *> strongest;
protected:
public:
   Ecosystem(int,int);
   ~Ecosystem();

   bool live();
   bool kill_unfit(list<Network *> *);
   
   static bool compareGenes(const Gene *, const Gene *);
   static bool compareNets(const Network *, const Network *);

   Network* breed(Network *, Network *);

   list<Species *>* get_organisms();
};

#endif 