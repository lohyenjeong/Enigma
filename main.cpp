#include <iostream>

using namespace std;

#include "machine.h"
#include "constants.h"
#include "errors.h"

//Checks if there is a sufficient number of input parameters (at least 3)
//Changes the int error_code to INSUFFICIENT_NO_OF_PARAMETERS if there isnt
void check_input_parameters(int argc, int &error_code){
  if(argc < 3){
    //cout << "Error: There is an insufficient number of parameters." << endl;
    //cout << "You need to have at least a plugboard file and a reflector file." << endl;
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl; 
    error_code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }  
}

//Function to check whether the message is a valid input(Upper case alphabet)
void check_valid_input(char message, int &error_code){
  if(message < DIFF_ASCII || message > DIFF_ASCII + NO_OF_ALPHABET - 1){
    cerr << message << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
    error_code = INVALID_INPUT_CHARACTER;
    return;
  }
}

//Prompts users to input messages 
//Initialises the encryption process
//Outputs the encrypted message to the screen
void start_user_interface(Machine &configured_machine, int &error_code){
  //cout << "This is the enigma machine. Please input your message in capital letters." << endl;
  //cout << "Press Ctrl-D to quit the program." << endl;
  
  char message;
  cin >> message;
  while(!cin.eof()){
    check_valid_input(message, error_code);
    if(error_code)
      return;
    error_code = configured_machine.encryption(message);
    if(error_code)
      return;
    cout << message;
    cin >> message;
  }
}

//Calls other functions to execute the programme
int main(int argc, char **argv){
  int error_code = NO_ERROR; 

  check_input_parameters(argc, error_code);
  if(error_code)
    return error_code;

  //Initialises a new machine
  Machine configured_machine(argc, argv, error_code);
  if(error_code)
    return error_code;
  
  start_user_interface(configured_machine, error_code);

  return error_code;
}
