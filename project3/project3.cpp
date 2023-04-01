#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

#include "constants.h"
#include "PrintMenu.h"
#include "ImageClass.h"
#include "RowColumnClass.h"
#include "ColorClass.h"
#include "MessageClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: Implement a steganography technique to enode messages into a image
// and decode with the hidden image 
// Date: March 31th, 2023

int main(int argc, char *argv[])
{  
  ifstream inFile;
  string initialFileName;
  int userChoice;
  bool doesQuit = false;       // check if the user quits the program
  int rowPos;                  // row position for message placement
  int colPos;                  // column position for message placement
  ImageClass initialImage;    
  RowColumnClass msgPos;       //row and column position for message  

  // Error check if the user provides correct input parameters
  if (argc != CORRECT_NUMBER_ARGUMENTS)
  {
    cout << "Usage: ./proj3.exe <startPPM.ppm>" << endl;
    exit(WRONG_NUMBER_ARGUMENTS_ERROR);
  }

  // Read in the ppm image provided by the user
  cout << "Reading initial image from: " << argv[1] << endl;
  initialFileName = argv[1];

  // Error check if the ppm image can be correctly read
  if (initialImage.checkInput(initialFileName))
  {
    cout << "Image read successful: Yes" << endl;
  }
  else
  {
    cout << "Image read successful: No" << endl;
    cout << "Error: While reading the image, an error was encountered. "
            "Exiting the program!" << endl;
    exit(WRONG_PPM_FORMAT_ERROR);
  }

  // Print menu for user to choose option
  while (!doesQuit)
  {
    PrintMenu();
    cout << "Enter your choice: ";  // Prompt
    cin >> userChoice;

    if (userChoice == ENCODE_MESSAGE_OPTION)
    {
      string messageFile;
      cout << "Enter name of file containing message: ";
      cin >> messageFile;

      cout << "Enter row and column for message placement: ";
      cin >> rowPos >> colPos;
      
      // check if row and column starting position are within the image
      msgPos.setRowCol(rowPos, colPos);
      if (!initialImage.isLocationValid(msgPos))
      {
        cout << "Error: Message starting position exceeds the boundary" << endl;
        cout << "Message encode successful: No" << endl;
        continue;
      }

      // encode the message to the initial ppm image
      if (initialImage.encodeMessage(messageFile, msgPos))
      {
        cout << "Message encode successful: Yes" << endl;
      }
      else
      {
        cout << "Message encode successful: No" << endl;
      }
    }
    else if (userChoice == DECODE_OPTION)
    {
      initialImage.decodeMessage(); 
    }
    else if (userChoice == WRITE_IMAGE_OPTION)
    {
      string writtenFile;
      cout << "Enter name of file to write image to: ";
      cin >> writtenFile;
      
      initialImage.writeImage(writtenFile);
      cout << "Image write successful: Yes" << endl;
    }
    else if (userChoice == EXIT_PROGRAM_OPTION)
    {
      doesQuit = true;       // stop the main function
      cout << "Thanks for using this program!" << endl;
    }
    else
    { 
      cout << "Error: Please enter the valid choice" << endl;
      continue; 
    }
  } 

  return 0;
}
