#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;
#include <vector>
#include "errors.h"
#include "constants.h"
#include "component.h"

//Default Constructor where all attributes are initialised to null
Component :: Component(){
  next = NULL;
  previous = NULL;
  rotation = 0;
  //Initalises all data maps points to their absolute position 
  for(int i = 0; i < NO_OF_ALPHABET; i++) 
    mapper[i] = i;
}


//Helper function that checks whether there is any non-numeric data
//Returns NON_NUMERIC CHARACTER if there is
//Else returns NO_ERROR
int Component :: check_non_numeric(ifstream &data_map){    
  char character_point;
  int int_point;
  while((data_map >> skipws >> character_point) && !data_map.eof()){
    int_point = static_cast<int>(character_point);
    if(int_point < 48 || int_point > 57){
      cerr <<"Non-numeric character in ";
      return NON_NUMERIC_CHARACTER;
    }
  }
  data_map.clear();
  data_map.seekg(0);
  return NO_ERROR;
}


//Helper function that checks whether there are numeric characters larger than 25 or negative in value
//Returns INVALID_INDEX if there is
//Else returns NO_ERROR
int Component :: check_valid_index(vector<int> data_inputs, int data_size){
  for(int i =0; i < data_size; i++){   
    if(data_inputs[i] >= NO_OF_ALPHABET || data_inputs[i] < 0){
      cerr << "Invalid index (larger than 25 or negative) in " << endl;
      return INVALID_INDEX;
    }
  }
  return NO_ERROR;
}


//Helper function that checks that they are no repeats in the data
//Used to check whether the data in the rotors, reflector and plugboard subclasses are valid 
//Returns 1 if there is 
//Else returns 0
bool Component :: check_repeat(vector<int> data_inputs, int size_constraint){
 for(int i = 0; i < size_constraint; i++){
    for(int j = 0; j < size_constraint; j++){
      if(data_inputs[i] == data_inputs[j] && i !=j){
	cerr << "Invalid mapping of input " << j << " to output " << data_inputs[i] << " (output ";
	cerr << data_inputs[i] << " is already mapped to from input " << i << ") in ";
	return true;
      }
    }
  }
  return false;
}


//Helper function to check whether there is an odd number of parameters
//Returns 1 if there is
//Else returns 0
bool Component :: check_odd(vector<int>data_inputs, int data_size){
  if(data_size%2){
    cerr << "Incorrect (odd) number of parameters in ";
    return true;
  }
  else
    return false;
}


//Sets up the components to reflect its rotation and data map                                                      
//Used by the plugboard and the reflector subclasses                                                               
//Overridden by the rotor subclass 
int Component :: set_up(char* &data_file){
  int error_code = NO_ERROR;
  ifstream data_map;
  data_map.open(data_file);
  if(!data_map){
    assert(data_map);
    cerr << "Error occured while opening ";
    error_code = ERROR_OPENING_CONFIGURATION_FILE;
    return error_code;
  }

  //Initialises the checking of the component's file
  error_code = check_file(data_map);
  if(error_code)
    return error_code;
  
  //Reads the data from the component file and set its data map
  int switch_1, switch_2;
  data_map >> skipws >> switch_1 >> switch_2;
  while(!data_map.eof()){
    mapper[switch_1] = switch_2;
    mapper[switch_2] = switch_1;
    data_map >> skipws >> switch_1 >> switch_2;
  }

  data_map.close();
  return error_code;
}


//Function to forward encrypt the message (plugboard to reflector)                                                  
//Used by the Plugboard, Rotor and Reflector subclasses                                                            
int Component :: encrypt(int &message_int){
  message_int = (mapper[(message_int + rotation) % NO_OF_ALPHABET] - rotation + NO_OF_ALPHABET) % NO_OF_ALPHABET;
  if(next){
     message_int = next->encrypt(message_int);
  }
  return message_int;
}


//Function to reverse encrypt the message (after the reflector to the plugboard) 
//Used by the Plugboard, Rotor and Reflector subclasses                                                            
int Component :: reverse_encrypt(int &message_int){
  if(previous){
    message_int = (message_int + previous->rotation) % NO_OF_ALPHABET;
    for(int i =0; i < NO_OF_ALPHABET; i++){
      if(previous->mapper[i]==message_int){
	message_int = (i - previous->rotation + NO_OF_ALPHABET) % NO_OF_ALPHABET;
	message_int = previous->reverse_encrypt(message_int);
	break;
      }
    }
  }
  return message_int;
}

