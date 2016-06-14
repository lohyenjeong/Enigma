#include <iostream>
#include <fstream>
using namespace std;

#include "errors.h"
#include "plugboard.h"


//Function that calls other helper parameters to check the validity of the data
//Returns the relevant error_code if there is an error
//Else returns NO_ERROR
int Plugboard :: check_file(ifstream &data_map){
  int error_code = NO_ERROR;

  int data_point;
  vector<int> data_inputs;
  while(data_map >> skipws >> data_point)
    data_inputs.push_back(data_point); 
  int data_size = data_inputs.size();

  data_map.clear();
  data_map.seekg(0);  
  
  //Checks for non-numerials in the input file
  error_code = check_non_numeric(data_map);
  if(error_code)
    return error_code;

  //Checks for invalid index (negative numbers of numbers larger than 25)
  error_code = check_valid_index(data_inputs, data_size);
  if(error_code)
    return error_code;

  //Checks whether each of the plugboard's parameters are paired
  if(check_odd(data_inputs, data_size)){
    error_code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    return error_code;
  }    

  //Checks whether there are less than 26 parameters
  if(check_size(data_inputs, data_size)){
    error_code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    return error_code;
  }

  //Checks whether there is a repeat in the data
  if(check_repeat(data_inputs, data_size)){
    error_code = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    return error_code;
  }

  return error_code; 
}


//Helper function that checks that the data size is not more than 26
//Returns 1 if there is          
//Else returns 0    
bool Plugboard :: check_size(vector<int>data_inputs, int data_size){
  if(data_size > 26){
    cerr << "Incorrect number of parameters in ";
    return true;
  }
  else
    return false;
} 
