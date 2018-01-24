#include <iostream>

#include "hidden.h"

using namespace std;

Hidden::Hidden(): Node(hidden){}

Hidden::~Hidden(){}

void Hidden::find_layer()
{
   int index = 0;
   while(inputs[index] != NULL)
   {
      if(inputs[index]->get_type() == hidden)
      {
         layer = inputs[index]->layer++;
      }
      else layer = 1;
   }
}

void Hidden::add_input(Node *node){}

void Hidden::add_output(Node *node){}
