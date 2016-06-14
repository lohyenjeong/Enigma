#ifndef ROTOR_H
#define ROTOR_H
#include <vector>
#include <fstream>
#include "constants.h"
#include "component.h"

class Rotor: public Component{
  //Vector that contains whether there is a notch at a particular position
  vector<int> rotor_notches;

  //Initialies all file checking functions relevant to the rotor.
  //Returns the relevant error_code if there is an error
  //Else returns NO_ERROR
  int check_file(ifstream &the_file);

  //Checks whether there are repeats in the input or that not all inputs are mapped
  //Returns INVALID_ROTOR_MAPPING if there is
  //Else returns NO_ERROR
  bool check_size(vector<int> data_inputs, int data_size);
 
 public:
  //Overrides the default constructor
  Rotor();

  //Initialises the set up of a rotor at its starting position as indicated by the position file
  //Returns an error_code if there was any found
  //Else returns NO_ERROR
  int set_up(char* rotor_file_name, vector<int> position_data, int rotor_number, int no_of_rotors);

  //Increments the rotation of the current rotor by 1
  //Increments the rotation of the neighbouring rotor by 1 if a notch is hit
  void rotate();
  
};

#endif
