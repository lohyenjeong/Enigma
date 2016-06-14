#ifndef POSITION_H
#define POSITION_H

#include <fstream>
#include "component.h"

//Inherits from the superclass Component
class Position : public Component{
 public:
  //Overrides check_file function in superclass Component
  //Returns the relevant error_code if there is one
  //Else returns NO_ERROR
  int check_file(ifstream &data_map);

};

#endif
