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
  #if DEBUG
    cout << "[INFO][MAIN]: Entered main." << endl;
  #endif

  int index = 0;
  while(index + 1 != argc){
    index++;

    if(strcmp(argv[index],"--help") == 0){
      cout << "ExoAI 2.0" << endl;
      cout << "Usage: ExoAI [Options]" << endl;
      cout << "OPTIONS:" << endl;
      cout << "   --help:       Shows the help page." << endl;
      cout << "   --comments:   Displays the cout comments in the program." << endl;
      cout << "   --hardware:   Run the program with the hardware." << endl;

      return 0;
    }
    else if(strcmp(argv[index],"--comments") == 0){
      #undef DEBUG
      #define DEBUG 1
    }
    else if(strcmp(argv[index],"--hardware") == 0){
      #undef HARDWARE
      #define HARDWARE 1
    }
  }

  bool alive = true;
  Ecosystem *life = new Ecosystem(INIT_SPECIES, INIT_NETWORK);

  while(alive){
      alive = life->live();
  }

  if(life != NULL){
    delete life;
    life = NULL;
  }
    
  #if DEBUG
    cout << "[INFO][MAIN]: Exiting main." << endl;
  #endif

  return 0;
}
