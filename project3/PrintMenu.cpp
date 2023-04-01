#include <iostream>  //Need for Cout, Cin

using namespace std;

#include "constants.h"
#include "PrintMenu.h"

void PrintMenu()
{
  cout << ENCODE_MESSAGE_OPTION << ". Encode a message from file" << endl;
  cout << DECODE_OPTION << ". Perform decode" << endl;
  cout << WRITE_IMAGE_OPTION << ". Write current image to file" << endl;
  cout << EXIT_PROGRAM_OPTION << ". Exit the program" << endl;
};
