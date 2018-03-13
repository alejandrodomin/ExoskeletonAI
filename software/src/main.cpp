#include <mpi.h>

#include <iostream>
#include <fstream>
#include <thread>

#include <common.hpp>
#include <ecosystem.hpp>
#include <species.hpp>
#include <network.hpp>
#include <node.hpp>
#include <gene.hpp>

#define INIT_SPECIES 5
#define INIT_NETWORK 5

using namespace std;

int main(int argc, char **argv, char **env){
  cout << "[INFO][MAIN]: Entered main." << endl;

  bool alive = true;
  Ecosystem *life = new Ecosystem(INIT_SPECIES, INIT_NETWORK);

  while(alive){
    alive = life->live();
  }

  if(life != NULL){
    delete life;
    life = NULL;
  }

  cout << "[INFO][MAIN]: Exiting main." << endl;
  return 0;
}
