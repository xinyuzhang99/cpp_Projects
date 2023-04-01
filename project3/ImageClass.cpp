#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "ImageClass.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "MessageClass.h"
#include "constants.h"

ImageClass::ImageClass()
{
  imageRowCol = RowColumnClass();
}

bool ImageClass::isLocationValid(const RowColumnClass &inRowCol) const
{
  int row = inRowCol.getRow();
  int col = inRowCol.getCol();
  return (row >= 0 && row < imageRowCol.getRow() 
          && col >= 0 && col < imageRowCol.getCol());
}

int ImageClass::getImageRow() const
{
  return imageRowCol.getRow();
}

int ImageClass::getImageCol() const
{
  return imageRowCol.getCol();
}

bool ImageClass::checkMagicNumber(ifstream &inFile)
{
  string magicNumber;

  bool validInputFound = false;
  if (inFile.eof())
  {
    cout << "Error: EOF before reading Magic Number" << endl;
    return validInputFound;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    cout << "Error: Failing to read Magic Number" << endl;
    return validInputFound;
  }
  else
  {
    validInputFound = true;
  }

  inFile >> magicNumber;
  if (magicNumber != MAGIC_NUMBER)
  {
    cout << "Error: Expecting to find Magic Number " << MAGIC_NUMBER.c_str() 
         << ", but find " << magicNumber.c_str();
    validInputFound = false;
  } 
  return validInputFound;
}

bool ImageClass::checkWidthHeight(ifstream &inFile)
{
  int inRow;
  int inCol;

  // check if the width is in proper format 
  bool validInputFound = false;
  if (inFile.eof())  
  {
    cout << "Error: EOF before reading the width of the image" << endl;
    return validInputFound;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    cout << "Error: Failing to read the width of the image" << endl;
    return validInputFound;
  }

  inFile >> inCol;
  if (inCol < MINIMUM_SIZE || inCol > MAXIMUM_SIZE)
  {
    cout << "Error: Expecting to find the width of the image from "
         << MINIMUM_SIZE << " to " << MAXIMUM_SIZE << ", but find: "
         << inCol << endl;
    return validInputFound; 
  }

  // check if the height is in proper format
  validInputFound = false;
  if (inFile.eof())
  {
    cout << "Error: EOF before reading the height of the image" << endl;
    return validInputFound;
  }
  else if (inFile.fail())
  {
    inFile.clear(); 
    cout << "Error: Failing to read the height of the image" << endl;
    return validInputFound;
  }
  
  inFile >> inRow;
  if (inRow < MINIMUM_SIZE || inRow > MAXIMUM_SIZE)
  {
    cout << "Error: Expecting to find the height of the image from "
         << MINIMUM_SIZE << " to " << MAXIMUM_SIZE << ", but find: "
         << inRow << endl;
    return validInputFound;
  }

  imageRowCol.setRowCol(inRow, inCol);
  validInputFound = true;
  return validInputFound;
}

bool ImageClass::checkMaxColor(ifstream &inFile)
{
  int inputMax;

  bool validInputFound = false;
  if (inFile.eof()) 
  {
    cout << "Error: EOF before reading the maximum color value" << endl;
    return validInputFound;
  } 
  else if (inFile.fail())
  {
    inFile.clear(); 
    cout << "Error: Failing to read the maximum color value" << endl;
    return validInputFound; 
  }
  else
  {
    validInputFound = true;
  }

  inFile >> inputMax;
  if (inputMax != MAXIMUM_ALLOWED_COLOR)
  {
    cout << "Error: Expecting to find maximum color value " 
         << MAXIMUM_ALLOWED_COLOR << ", but find: " << inputMax << endl;;
    validInputFound = false;
  } 

  return validInputFound;
}

bool ImageClass::checkPixel(ifstream &inFile)
{
  bool validInputFound = false;
  if (inFile.eof())
  {
    cout << "Error: EOF before reading the pixel values" << endl;
    return validInputFound;
  }

  int inRow = imageRowCol.getRow();
  int inCol = imageRowCol.getCol();
  pixelMatrix = new ColorClass*[inRow];

  // dynamically allocate the according memory needed
  for (int rInd = 0; rInd < inRow; rInd++)
  {
    pixelMatrix[rInd] = new ColorClass[inCol];
  }  

  // put pixels into the matrix
  for (int rInd = 0; rInd < inRow; rInd++)
  {
    for (int cInd = 0; cInd < inCol; cInd++)
    {  
      if (inFile.eof())
      {
        cout << "Error: EOF before reading the pixel at row: " << rInd
             << " col: " << cInd << endl;
      }
      else if (inFile.fail())
      {
        inFile.clear(); 
        cout << "Error: Reading image pixel at row: " << rInd 
             << " col: " << cInd << endl;
        return validInputFound;
      }
      
      if (!pixelMatrix[rInd][cInd].readColor(inFile))
      {
        cout << "Error: Reading image pixel at row: " << rInd 
             << " col: " << cInd << endl;
        return validInputFound;
      }
    }
  }
  
  // check if there are more image pixels in the original file
  string test;
  inFile >> test;
  if (test != "")
  {
    cout << "Error: More image pixels than expected" << endl; 
    return validInputFound;
  }   

  inFile.close();
  validInputFound = true;
  return validInputFound;
}

bool ImageClass::checkInput(const string &initialFileName)
{
  ifstream inFile;

  inFile.open(initialFileName.c_str());

  bool validInputFound = false;
  if (inFile.fail())
  {
    cout << "Error: Opening file " << initialFileName.c_str() << endl;
    return validInputFound;  
  }

  if (!checkMagicNumber(inFile) || !checkWidthHeight(inFile) ||
      !checkMaxColor(inFile) || !checkPixel(inFile))
  { 
    return validInputFound;
  }
  validInputFound = true;
  return validInputFound;
}

bool ImageClass::encodeMessage(const string &msgFileName, 
                               const RowColumnClass &msgPos)
{
  ifstream msgFile;
  msgFile.open(msgFileName.c_str());
  MessageClass msg;

  bool validMsgFound = false;
  if (msgFile.fail())
  {
    cout << "Error: Opening message file: " << msgFileName.c_str() << endl;
    return validMsgFound;
  }
  
  // check if the width, height and pixel values are valid
  if (!msg.checkWidthHeight(msgFile) 
      || !msg.checkValue(msgFile))
  {
    return validMsgFound;
  }
 
  // check and encode each pixel
  int msgRow = msgPos.getRow();   // starting positions of the message
  int msgCol = msgPos.getCol();
  int inRow = msg.getMsgRow();    // row and col of the message
  int inCol = msg.getMsgCol();
  // row and col bounds of the initial image
  int rowBound = imageRowCol.getRow();
  int colBound = imageRowCol.getCol();
  int encodingVal;

  for (int rInd = msgRow; rInd < min(msgRow + inRow, rowBound); rInd++)
  {
    for (int cInd = msgCol; cInd < min(msgCol + inCol, colBound); cInd++)
    {
      encodingVal = msg.getValue(rInd - msgRow, cInd - msgCol);
      if (!pixelMatrix[rInd][cInd].encodePixel(encodingVal))
      { 
        return validMsgFound;
      }
    } 
  } 

  msgFile.close();
  validMsgFound = true;
  return validMsgFound;
}

void ImageClass::decodeMessage()
{
    int inRow = imageRowCol.getRow();
    int inCol = imageRowCol.getCol();
    for (int rInd = 0; rInd < inRow; rInd++)
    {
      for (int cInd = 0; cInd < inCol; cInd++)
      {
        pixelMatrix[rInd][cInd].decodePixel();
      }
    }
    cout << "Image modified to decoded image contents" << endl;
}

void ImageClass::writeImage(const string &writtenFileName)
{
  ofstream outFile;
  outFile.open(writtenFileName.c_str());

  if (outFile.fail())
  {
    cout << "Unable to open file, automatically create a new file" << endl;
  }

  // write to file Magic Number
  outFile << MAGIC_NUMBER.c_str() << endl;
  
  // write to file the width and height of the image
  int outRow = imageRowCol.getRow();
  int outCol = imageRowCol.getCol();
  outFile << outCol << " "  << outRow << endl;
  
  // write to file the maximum color value
  outFile << MAXIMUM_ALLOWED_COLOR << endl;

  // write to file the pixel values 
  for (int rInd = 0; rInd < outRow; rInd++)
  {
    for (int cInd = 0; cInd < outCol; cInd++)
    {
      pixelMatrix[rInd][cInd].writePixel(outFile);
    }
  }
  
  outFile.close();
}
