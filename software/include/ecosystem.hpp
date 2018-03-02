#ifndef ECOSYSTEM_HPP
#define ECOSYSTEM_HPP

#include <list>
#include <memory>

#include <common.hpp>
#include <species.hpp>
#include <network.hpp>
#include <gene.hpp>

using namespace std;

class Ecosystem{
private:
   list<unique_ptr<Species>> organisms;
   list<unique_ptr<Network>> strongest;
protected:
public:
   Ecosystem(int,int);
   ~Ecosystem();

   bool live();

   bool kill_unfit(list<unique_ptr<Network>>*);
   
   static bool compareGenes(const unique_ptr<Gene>, const unique_ptr<Gene>);
   static bool compareNets(const unique_ptr<Network>, const unique_ptr<Network>);

   Network* breed(Network *, Network *);
};

#endif 