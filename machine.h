#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include <fstream>
#include "component.h"
#include "plugboard.h"
#include "rotor.h"
#include "position.h"
#include "reflector.h"

//Machine class: intialises a full working machine and its various components
class Machine{
  int no_of_rotors;
  //Pointers to the various components
  vector<Rotor*> configured_rotors;
  Position* configured_position;
  Reflector* configured_reflector;
  Plugboard* configured_plugboard;
  
  //Helper function to set up the plugboard
  //Changes the error_code if there is any errors encountered in the process
  void set_up_plugboard(int argc, char **argv, int &error_code);

  //Helper function to set up the reflector
  //Changes the error_code if there are any errors encountered in the process
  void set_up_reflector(int argc, char **argv, int &error_code);

  //Helper function to set up the rotors and the position file
  //Changes the error_code if there are any errors encountered in the process
  void set_up_rotors(int argc, char **argv, int &error_code);

  //Helper function to link the various components together
  void link_components();

 public:
  //Constructor that initialises all the various components of the machine
  //Changes the error_code if any errors were encountered in the process
  Machine(int argc, char** argv, int &error_code);
  
  //Function to encrypt the input character by character
  //Returns an error_code != 0 if there is any errors encountered in the process                                   
  //Else returns NO_ERROR  
  int encryption(char &input);
};

#endif
