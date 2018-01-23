#include <iostream>

#include "node.h"
#include "input.h"

using namespace std;

Input::Input(): Node(input)			// the :Node() after the constructor calls the parent
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
