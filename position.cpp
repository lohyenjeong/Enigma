#include <iostream>
#include <fstream>

using namespace std;

#include "errors.h"
#include "position.h"

//Initialises the various helper functions to check the validity of data
//Returns the relevant error_code if there is
//Else returns NO_ERROR
int Position :: check_file(ifstream &data_map){
  int error_code = NO_ERROR;

  int data_point;
  vector<int> data_inputs;
  while(data_map >> skipws >> data_point)
    data_inputs.push_back(data_point);
  int data_size = data_inputs.size();

  data_map.clear();
  data_map.seekg(0);

  //Checks for non numerics in the input file
  error_code = check_non_numeric(data_map);
  if(error_code)
    return error_code;

  //Checks whether there are numeric characters larger than 25 or negative in value
  error_code =check_valid_index(data_inputs, data_size);
  if(error_code)
    return error_code;

  return NO_ERROR;
}
