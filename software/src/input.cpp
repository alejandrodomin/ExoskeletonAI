#include <iostream>

#include "node.h"
#include "input.h"

using namespace std;

Input::Input(): Node(input)			// the :Node() after the constructor calls the parent
{                                   // constructor implicitly
   hardware_inputs = new float[3];
}

Input::~Input()
{
   if(hardware_inputs != NULL){
      delete [] hardware_inputs;
      hardware_inputs = NULL;
   }
}


