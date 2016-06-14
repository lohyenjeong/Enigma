#include <iostream>
#include <fstream>

using namespace std;
#include <vector>
#include "errors.h"
#include "reflector.h"

//Main error checking function for the reflector object
//Calls helper functions for individual test
//Returns an error pre-specified in the errors.h file if there is an error
//Else returns 0
int Reflector :: check_file(ifstream &data_map){
  int error_code = NO_ERROR;
  
  int data_point;
  vector<int> data_inputs;
  while(data_map >> skipws >> data_point)
    data_inputs.push_back(data_point);
  int data_size =data_inputs.size();
  
  data_map.clear();
  data_map.seekg(0);  

  //Checks for non-numerials in the input file
  error_code = check_non_numeric(data_map);
  if(error_code)
    return error_code;

  //Checks for invalid index (negative numbers or numbers larger than 25)
  error_code = check_valid_index(data_inputs, data_size);
  if(error_code)
    return error_code;

  //Checks whether there is an odd number of parameters
  if(check_odd(data_inputs, data_size)){
    error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    return error_code;
  }

  //Checks whether there are exactly 13 pairs of parameters
  if(check_size(data_inputs, data_size)){
    error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    return error_code; 
  }

  //Checks whether there is a repeat in the numbers
  if(check_repeat(data_inputs, data_size)){
    error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    return error_code;
  }


  return error_code;
}


//Helper function to test whether there are 13 pairs of parameters
//Returns 1 if there is an error
//Else returns 0
bool Reflector :: check_size(vector<int> data_inputs, int data_size){
  if(data_size < NO_OF_ALPHABET){
    cerr << "Insufficient number of mappings in ";
    return true;
  }
  if(data_size > NO_OF_ALPHABET){
    cerr << "Too many mappings in ";
  }
  return false;
}
