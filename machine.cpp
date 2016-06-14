#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;
#include "errors.h"
#include "machine.h"
#include <vector>
#include "component.h"

//Constructor with input parameters
//Initialises the set up of all the components of the machine
//Changes the error_code if there is an error encountered in any of the proceses
Machine :: Machine(int argc, char**argv, int&error_code){  
  set_up_plugboard(argc, argv, error_code);
  if(error_code)
    return;

  set_up_reflector(argc, argv, error_code);
  if(error_code)
    return;

  //Checks whether there are any rotors and set them and the position file up if there is any
  no_of_rotors = 0;
  if(argc > 3){
    no_of_rotors = argc - 4; 
    set_up_rotors(argc, argv, error_code);
    if(error_code)
      return;
  }
  link_components();
}


//Sets up the plugboard file and checks for relevant errors
void Machine :: set_up_plugboard(int argc, char **argv, int &error_code){
  configured_plugboard = new Plugboard();
  error_code = configured_plugboard->set_up(argv[1]);
  if(error_code){
    cerr << "plugboard file " << argv[1] << endl;
    return;
  }
}

//Sets up the reflector file and checks for relevant errors
void Machine :: set_up_reflector(int argc, char **argv, int &error_code){
  configured_reflector = new Reflector();
  error_code = configured_reflector->set_up(argv[2]);
  if(error_code){
    cerr << "reflector file " << argv[2] << endl;
    return;
  }
}


//Sets up the rotors and the position files and checks for relevant errors
void Machine :: set_up_rotors(int argc, char **argv, int &error_code){
  //cout << "The number of rotors in set_up_rotors is " << no_of_rotors << endl;
  ifstream position_file;
  position_file.open(argv[argc-1]);
  if(!position_file){
    cerr << "Error occured while opening the rotor positions file " << argv[argc-1] << endl;
    assert(position_file);
    error_code = ERROR_OPENING_CONFIGURATION_FILE;
    return;
  }

  //Sets up position file and checks for errors
  configured_position = new Position;
  error_code = configured_position->set_up(argv[argc-1]);
  if(error_code){
    cerr << "rotor positions file "<< argv[argc-1] <<endl;
    return;
  }

  //Checks that the number of rotor files is as indicated by the position file
  vector<int> position_data;
  int position_point;
  while(!position_file.eof() && (position_file >> skipws >> position_point)){
    position_data.push_back(position_point);
  }

  //Sets up the rotors files and checks for errors
  for(int i = 0; i < (argc-4); ++i){
    int rotor_no = i +1;
    Rotor* new_rotor;
    new_rotor = new Rotor();
    error_code = new_rotor->set_up(argv[i+3], position_data, rotor_no, no_of_rotors);
    if(error_code){
      cerr << "rotor file " << argv[i+3] << endl;
      return;
    }
  
  //Check whether there is too many position files
  if(static_cast<int>(position_data.size()) > no_of_rotors){
    cerr << "There are more starting positions than there are rotors." << endl;
    error_code = NO_ROTOR_STARTING_POSITION;
    return;
    }
    configured_rotors.push_back(new_rotor);
  }
  position_file.close();
}


//Helper function to link the various components together
void Machine :: link_components(){
  if(no_of_rotors){
    configured_plugboard->next = configured_rotors[no_of_rotors-1];
    configured_rotors[no_of_rotors-1]->previous = configured_plugboard;  
    for(int i = no_of_rotors-1; i > 0; i--){
      configured_rotors[i]->next = configured_rotors[i-1];
    }
    for(int i = 0; i < no_of_rotors - 1; i++){
      configured_rotors[i]->previous = configured_rotors[i+1];
    }
    configured_rotors[0]->next = configured_reflector;
    configured_reflector->previous = configured_rotors[0];
  }else{
    configured_plugboard->next = configured_reflector;
    configured_reflector->previous = configured_plugboard;
  }
}

 
//Function to encrypt the input character by character
//Returns an error_code != 0 if there is any errors encountered in the process
//Else returns NO_ERROR
int Machine :: encryption(char &message){
  int message_int = message - DIFF_ASCII;
  //Sets off the rotation of the rotors
  if(no_of_rotors){
    configured_rotors[no_of_rotors-1]->rotate();
  }

  message_int = configured_plugboard->encrypt(message_int);
  message_int = configured_reflector->reverse_encrypt(message_int);

  //Change the output from a digit to the corresponding alphabet and output it to the screen
  message = message_int + DIFF_ASCII;
  return NO_ERROR;
}

