#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>
#include "component.h"

//Inherits from the super class component
class Reflector : public Component{
  //Overrides the check_file function in the superclass Component
  int check_file(ifstream &data_file);

  //Helper function that checks whether the reflector has 13 pairs of parameters
  //Returns INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS if there isnt
  //Else returns NO_ERROR
  bool check_size(vector<int> data_inputs, int data_size);
};

#endif
