#include <iostream>

#include "hidden.h"

using namespace std;

Hidden::Hidden(): Node(hidden)
{
    
}

Hidden::~Hidden(){}

void Hidden::find_layer()   // the logic in this function seems iffy check it later
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

int Hidden::get_layer()
{
    return layer;
}

void Hidden::add_input(Node *node)
{
    inputs.push_back(node);
}

void Hidden::add_output(Node *node)
{
    outputs.push_back(node);
}
