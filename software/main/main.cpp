// #include <mpi.h>

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

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
  int index = 0;
  while(index + 1 != argc){
    index++;

    if(strcmp(argv[index],"-h") == 0){
      cout << "ExoAI 2.0" << endl;
      cout << "Usage: ExoAI [Options]" << endl;
      cout << "OPTIONS:" << endl;
      cout << "   -h:   Shows the help page." << endl;
      cout << "   -c:   Displays the cout comments in the program." << endl;
      cout << "   -nc:  Doesn't display the cout comments in the program." << endl;

      return 0;
    }
    else if(strcmp(argv[index],"-c") == 0){
      comment = true;
    }
    else if(strcmp(argv[index],"-nc") == 0){
      comment = false;
    }
  }

  bool alive = true;
  Ecosystem *life = new Ecosystem(INIT_SPECIES, INIT_NETWORK);

  // while(alive){
  for(int i = 0; i < 10; i++)
    alive = life->live();
  // }

  if(life != NULL){
    delete life;
    life = NULL;
  }
    
  return 0;
}
