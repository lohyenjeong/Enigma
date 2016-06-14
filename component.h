#ifndef COMPONENT_H
#define COMPONENT_H

#include "constants.h"
#include <vector>

//Superclass of the subclasses Plugboard, Rotor, Position and Reflector
class Component{

 protected:
  //Array to contain the data inputs for the Plugboard, Rotor and Reflector subclasses
  int mapper[NO_OF_ALPHABET], rotation;

  //Helper function that checks whether there is any non-numeric data
  //Used by all subclasses
  //Returns NON_NUMERIC CHARACTER if there is
  //Else returns NO_ERROR
  int check_non_numeric(ifstream &data_map);
  
  //Helper function that checks whether there are numeric characters larger than 25 or negative in value
  //Used by all subclasses
  //Returns INVALID_INDEX if there is
  //Else returns NO_ERROR
  int check_valid_index(vector<int> data_inputs, int data_size);

  //Helper function that checks that they are no repeats in the data 
  //Used to check whether the data in the rotors, reflector and plugboard subclasses are valid                     
  //Returns true if there is                                                                                     
  //Else returns false
  bool check_repeat(vector<int> data_inputs, int data_size);

  //Helper function that checks that the data size is not more than 26
  //Returns true if there is                                                                                        
  //Else returns false     
  bool check_size(vector<int> data_inputs, int data_size);

  //Helper function to check whether there is an odd number of paramters
  //Used by the plugboard and the reflector class to check that input/output pairing is valid
  //Returns true if there is
  //Else returns false
  bool check_odd(vector<int> data_inputs, int data_size);

  //Virtual helper function that is overridden in the Rotor, Reflector and Plugboard subclasses
  //Checks that the number of input file parameters is correct
  //virtual bool check_size(vector<int> data_inputs, int data_size);

  //Virtual helper function that initialises the checking of an input file
  //Overridden in all subclasses
  virtual int check_file(ifstream &data_map) = 0;

 public:
  //Pointer to the next Component
  Component* next;

  Component* previous;

  //Constructor
  Component();

  //Sets up the components to reflect its rotation and data map
  //Used by the plugboard and the reflector subclasses
  //Overridden by the rotor subclass
  int set_up(char* &data_file);

  //Function to forward encrypt the message (plugboard to reflector)
  //Used by the Plugboard, Rotor and Reflector subclasses
  int encrypt(int &message);

  //Function to reverse encrypt the message (after the reflector to the plugboard)
  //Used by the Plugboard, Rotor and Reflector subclasses
  int reverse_encrypt(int &message);
  
  //Overridden only in the rotor subclass
  //Called on all components but performs a function only on a rotor
  //Function in rotor subclass initialises rotation of the next rotor when a notch is hit
  virtual void rotate(){};

};

#endif
