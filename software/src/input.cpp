#include <iostream>

#include "input.h"

using namespace std;

enum gyro {gyroX = 0, 
            gyroY,
            gyroZ};

Input::Input():Node()			// the :Node() after the constructor calls the parent
					// constructor implicitly
{
   this->inputs = new float[3];
}

Input::~Input()
{
   if(this->inputs != NULL){
      delete [] this->inputs;
      this->inputs = NULL;
   }
}

void Input::add_input(Node *node){}

void Input::add_output(Node *node){}
