#include <iterator>

#include <ecosystem.hpp>

#define COIN_FLIP 2
#define QUARTER_KILL 0.25

using namespace std;

Ecosystem::Ecosystem(int num_species, int num_nets){
  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::Ecosystem(int)." << endl;

  for(int index = 0; index < num_species; index++){
    organisms.push_back(new Species());
  }
  for(list<Species *>::iterator it = organisms.begin(); it != organisms.end(); it++){
    for(int index = 0; index < num_nets; index++)
      (*it)->add_network(new Network());
  }

  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::Ecosystem(int)." << endl;
}

Ecosystem::~Ecosystem(){
  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::~Ecosystem()." << endl;

  for(list<Species *>::iterator it = organisms.begin(); it != organisms.end(); it++){
    if(*it != NULL){
      delete [] *it;
      *it = NULL;
    }
  }
  organisms.clear();

  for(list<Network *>::iterator it = strongest.begin(); it != strongest.end(); it++){
    if(*it != NULL){
      delete [] *it;
      *it = NULL;
    }
  }
  strongest.clear();

  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::~Ecosystem()." << endl;
}

bool Ecosystem::live(){
  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::live()." << endl;

  int size_of_nets = 0;

  Network *child;

  list<Network * >::iterator itr;
  list<Network * >::iterator next_itr;

  for(list<Species *>::iterator species_iter= organisms.begin(); species_iter!= organisms.end(); ++species_iter){
    for(list<Network *>::iterator network_iter = (*species_iter)->get_networks()->begin(); network_iter != (*species_iter)->get_networks()->end(); ++network_iter){
      (*network_iter)->run(); 
      (*network_iter)->calculate_fit();
    }

    if((*species_iter)->is_stale())
      (*species_iter)->mutate();

    (*species_iter)->get_networks()->sort(compareNets);

    size_of_nets = (*species_iter)->get_networks()->size();
    itr = (*species_iter)->get_networks()->begin();
    for(int index = 0; index < size_of_nets; index++){
      next_itr = itr;
      if(++next_itr != (*species_iter)->get_networks()->end()){
        child = breed(*itr, *next_itr);
        if(child != NULL)
          (*species_iter)->get_networks()->push_back(child);
        }
        itr++;
    }

    kill_unfit((*species_iter)->get_networks());

    strongest.push_back((*species_iter)->get_fittest_net());
  }


  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::live()." << endl;

  return true;
}

bool Ecosystem::kill_unfit(list<Network *> *unfit){
  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::kill_unfit(list<Network*>*)." << endl;

  if(unfit->size() > 0)
    unfit->sort(compareNets);
  else return false;

  int size = unfit->size() * QUARTER_KILL;

  list<Network *>::iterator from = unfit->begin();
  list<Network *>::iterator to = unfit->begin();

  for(int index = 0; index < size; index++){
    to++;
  }

  unfit->erase(from,to);

  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::kill_unfit(list<Network*>*)." << endl;

  return true;
}

bool Ecosystem::compareGenes(const Gene * one, const Gene * two){
  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::compareGenes(const Gene *, const Gene *)." << endl;
  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::compareGenes(const Gene *, const Gene *)." << endl;

  return one->get_inov_id() < two->get_inov_id();
}

bool Ecosystem::compareNets(const Network * one, const Network * two){ // sorts less fit first to more fit later.
  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::compareNets(const Network *, const Network *)." << endl;
  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::compareNets(const Network *, const Network *)." << endl;

  return one->get_fitness() < two->get_fitness();
}

Network* Ecosystem::breed(Network *one, Network *two){

  cout << "[INFO][ECOSYSTEM]: Entered Ecosystem::breed(Network *, Network *)." << endl;
   
  if(one == NULL || two == NULL)
    return NULL;

  if(one->get_genes() != NULL && two->get_genes() != NULL){
    if(one->get_genes()->size() > 1 && two->get_genes()->size() > 1){
      one->get_genes()->sort(compareGenes);
      two->get_genes()->sort(compareGenes);
    }
    else return NULL;
  }
  else return NULL;

  list<Gene *>::iterator itone = one->get_genes()->begin();
  list<Gene *>::iterator ittwo = two->get_genes()->begin();

  int randNum;
  Network *newNet = new Network();

  while(itone != one->get_genes()->end() && ittwo != two->get_genes()->end()){
    randNum = rand() % COIN_FLIP;

    if(randNum)
      newNet->add_gene((*ittwo)->get_input_node(), (*ittwo)->get_output_node());
    else newNet->add_gene((*itone)->get_input_node(), (*itone)->get_output_node());

    itone++;
    ittwo++;
  }

  cout << "[INFO][ECOSYSTEM]: Exiting Ecosystem::breed(Network *, Network *)." << endl;

  return newNet;
}