#include <iostream>

#include "gene.hpp"

using namespace std;

Gene::Gene(Node* newstarting_gene, Node* newoutput_gene){
   starting_gene = newstarting_gene;
   output_gene = newoutput_gene;
}

Gene::~Gene(){

}

void Gene::set_weight(float newweight){
   weight = newweight;
}

float Gene::get_weight(){
   return weight;
}

Node* Gene::get_output_gene(){
   return output_gene;
}

Node* Gene::get_starting_gene(){
   return starting_gene;
}
