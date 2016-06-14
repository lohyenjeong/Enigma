#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>
#include "component.h"

//Inherits from the superclass Component
class Plugboard : public Component{
  //Overrides the check_file function in the superclass Component
  int check_file(ifstream &data_map);

  //Checks that the number of plugboard parameters is less than 26
  bool check_size(vector<int>data_inputs, int data_size);

};

#endif
