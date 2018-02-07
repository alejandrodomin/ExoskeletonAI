#include <iostream>

#include "gene.hpp"

using namespace std;

Gene::Gene(){
   cout << "[INFO][GENE]: Entered Gene::Gene()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::Gene()." << endl;
}

Gene::Gene(Node* newinput_node, Node* newyou_node){
   cout << "[INFO][GENE]: Entered Gene::Gene(Node *, Node *)." << endl;

   input_node = newinput_node;
   you_node = newyou_node;

   cout << "[INFO][GENE]: Exited  Gene::Gene(Node *, Node *)." << endl;
}

Gene::~Gene(){
   cout << "[INFO][GENE]: Entered Gene::~Gene()." << endl;

    if(input_node != NULL){
        delete [] input_node;
        input_node = NULL;
    }
    if(you_node != NULL){
        delete [] you_node;
        you_node = NULL;
    }

   cout << "[INFO][GENE]: Exited  Gene::~Gene()." << endl;
}

void Gene::set_weight(float newweight){
   cout << "[INFO][GENE]: Entered Gene::set_weight(float)." << endl;

   weight = newweight;

   cout << "[INFO][GENE]: Exited  Gene::set_weight(float)." << endl;
}

float Gene::get_weight(){
   cout << "[INFO][GENE]: Entered Gene::get_weight()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::get_weight()." << endl;
   return weight;
}

Node* Gene::get_input_node(){
   cout << "[INFO][GENE]: Entered Gene::get_input_node()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::get_input_node()." << endl;
   return input_node;
}

Node* Gene::get_you_node(){
   cout << "[INFO][GENE]: Entered Gene::get_you_node()." << endl;
   cout << "[INFO][GENE]: Exited  Gene::get_you_node()." << endl;
   return you_node;
}
