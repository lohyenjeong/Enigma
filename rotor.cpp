#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

#include "errors.h"
#include "constants.h"
#include "rotor.h"
#include <vector>

//Overrides the default constructor
//Initialises all notches to null
Rotor :: Rotor(){
  vector<int> rotor_notches;
}

//Initialises all file checking methods relevant to the rotor
int Rotor :: check_file(ifstream &data_map){
  int error_code = NO_ERROR;
  
  int data_point;
  vector<int> data_inputs;
  while(data_map >>skipws >> data_point)
    data_inputs.push_back(data_point);
  int data_size = data_inputs.size();

  data_map.clear();
  data_map.seekg(0); 

  //Checks for non-numerics in the input file
  error_code = check_non_numeric(data_map);
  if(error_code)
    return error_code;

  //Checks for invalid index (negative numbers larger than 25)
  error_code = check_valid_index(data_inputs, data_size);
  if(error_code)  
    return error_code;

 //Checks whether the size of the file is less than 26
  if(check_size(data_inputs, data_size)){
    error_code = INVALID_ROTOR_MAPPING;
    return error_code;
  }

  //Checks whether there are repeats
  if(check_repeat(data_inputs, NO_OF_ALPHABET)){
    error_code = INVALID_ROTOR_MAPPING;
    return error_code;
   }
 
  return error_code;
}


//Helper function that checks whether the rotor file has at least 26 parameters
//Returns true if there isnt
//Else returns false 
bool Rotor :: check_size(vector<int> data_inputs, int data_size){   
  if(data_size < NO_OF_ALPHABET){
    cerr << "Not all inputs mapped in rotor file: ";
    return true;  
  } 
  return false;
}

//Sets up the rotor with its relevant starting position and data inputs 
int Rotor :: set_up(char* rotor_file_name, vector<int> position_data, int rotor_no, int no_of_rotors){
  int error_code;
  ifstream rotor_file;
  rotor_file.open(rotor_file_name);

  if(!rotor_file){
    cout<< "Error occured while opening ";
    assert(rotor_file);
    rotor_file.close();
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  //Checks the rotor file for errors 
  error_code = check_file(rotor_file);
  if(error_code)
    return error_code;
  
  //Inputs the data of the rotor file in the mapper array
  for(int i = 0; i < NO_OF_ALPHABET; i++)
    rotor_file >> mapper[i];

  //Reads from file where the notches are and set the notches
  int rotor_notch;
  while(rotor_file >> skipws >> rotor_notch && !rotor_file.eof())
    rotor_notches.push_back(rotor_notch);

  // Checks that there are as more paramters in the position file then there are rotors
  if(static_cast<int>(position_data.size()) < no_of_rotors){
    cerr << "No starting position for rotor "<< rotor_no - 1 << " in rotor position file for "; 
    return NO_ROTOR_STARTING_POSITION;
  } 

  //Sets the starting position of the rotor files
  rotation = position_data[rotor_no - 1];

  rotor_file.close();
  return NO_ERROR;
}

//Increments the rotation of the current rotor by 1 when called
//Increments the rotation of the neighbouring rotor by 1 when a notch is hit
void Rotor :: rotate(){
  rotation = (rotation + 1) % 26;
  for(unsigned int i =0; i < rotor_notches.size(); i++){
    if(rotation == rotor_notches[i])
      next->rotate();
  }
}
