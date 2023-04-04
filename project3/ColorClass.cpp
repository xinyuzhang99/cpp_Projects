#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "ColorClass.h"
#include "constants.h"

ColorClass::ColorClass(){;}

ColorClass::ColorClass(const int inRed, const int inGreen, const int inBlue)
{
  redVal = inRed;
  greenVal = inGreen;
  blueVal = inBlue;
  clipColor();
}

bool ColorClass::clipColor()
{
  int colorVal[COLOR_COMPONENT_NUMBER] = {redVal, greenVal, blueVal};
  bool doClip = false;    // a flag indicating if clipping is necessary
  for (int i = 0; i < COLOR_COMPONENT_NUMBER; i++)
  {
    if (colorVal[i] < MINIMUM_ALLOWED_COLOR)
    {
      colorVal[i] = MINIMUM_ALLOWED_COLOR;
      doClip = true;
    }
    if (colorVal[i] > MAXIMUM_ALLOWED_COLOR)
    {
      colorVal[i] = MAXIMUM_ALLOWED_COLOR;
      doClip = true;
    }
  }

  redVal = colorVal[RED_INDEX];
  greenVal = colorVal[GREEN_INDEX];
  blueVal = colorVal[BLUE_INDEX];
  return doClip; 
}

void ColorClass::setToBlack()
{
  redVal = MINIMUM_ALLOWED_COLOR;
  greenVal = MINIMUM_ALLOWED_COLOR;  
  blueVal = MINIMUM_ALLOWED_COLOR;
}

void ColorClass::setToRed()
{
  redVal = MAXIMUM_ALLOWED_COLOR;
  greenVal = MINIMUM_ALLOWED_COLOR;                                              
  blueVal = MINIMUM_ALLOWED_COLOR;
}

void ColorClass::setToGreen()
{
  redVal = MINIMUM_ALLOWED_COLOR;
  greenVal = MAXIMUM_ALLOWED_COLOR;
  blueVal = MINIMUM_ALLOWED_COLOR; 
}

void ColorClass::setToBlue()
{
  redVal = MINIMUM_ALLOWED_COLOR;
  greenVal = MINIMUM_ALLOWED_COLOR;
  blueVal = MAXIMUM_ALLOWED_COLOR;
}

void ColorClass::setToWhite()
{
  redVal = MAXIMUM_ALLOWED_COLOR;
  greenVal = MAXIMUM_ALLOWED_COLOR; 
  blueVal = MAXIMUM_ALLOWED_COLOR;
}

void ColorClass::setToYellow()
{
  redVal = MAXIMUM_ALLOWED_COLOR;
  greenVal = MAXIMUM_ALLOWED_COLOR;
  blueVal = MINIMUM_ALLOWED_COLOR;
}

void ColorClass::setToMagenta()
{
  redVal = MAXIMUM_ALLOWED_COLOR;
  greenVal = MINIMUM_ALLOWED_COLOR;
  blueVal = MAXIMUM_ALLOWED_COLOR;
}

void ColorClass::setToCyan()
{
  redVal = MINIMUM_ALLOWED_COLOR;
  greenVal = MAXIMUM_ALLOWED_COLOR;
  blueVal = MAXIMUM_ALLOWED_COLOR;
}

bool ColorClass::setTo(const int inRed, const int inGreen, const int inBlue)
{
  redVal = inRed;
  greenVal = inGreen;
  blueVal = inBlue;
  return clipColor();
}

bool ColorClass::setTo(const ColorClass &inColor)
{
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;
  return clipColor();
}

bool ColorClass::addColor(const ColorClass &rhsColor)
{
  redVal += rhsColor.redVal;
  greenVal += rhsColor.greenVal;
  blueVal += rhsColor.blueVal;
  return clipColor();
}

bool ColorClass::subtractColor(const ColorClass &rhsColor)
{
  redVal -= rhsColor.redVal; 
  greenVal -= rhsColor.greenVal;
  blueVal -= rhsColor.blueVal;
  return clipColor();
}

void ColorClass::printComponentValues() const
{
  cout << "R: " << redVal << " G: " << greenVal << " B: " << blueVal;
}

bool ColorClass::readColor(ifstream &inFile)
{
  bool validInputFound = false;

  // check if red value is valid
  if (inFile.eof())
  {
    cout << "Error: EOF before reading red value" << endl;
    return validInputFound;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    inFile.ignore(200, '\n');
    cout << "Error: Failing to read red value" << endl;
    return validInputFound;
  }
  inFile >> redVal;
  
  // check if green is valid
  if (inFile.eof())
  {
    cout << "Error: EOF before reading green value" << endl;
    return validInputFound;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    inFile.ignore(200, '\n');
    cout << "Error: Failing to read green value" << endl;
    return validInputFound;
  }
  inFile >> greenVal;

  // check if blue is valid
  if (inFile.eof())
  {
    cout << "Error: EOF before reading blue value" << endl;
    return validInputFound;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    inFile.ignore(200, '\n');
    cout << "Error: Failing to read blue value" << endl;
    return validInputFound; 
  }
  inFile >> blueVal;

  validInputFound = true;
  return validInputFound;
}

void ColorClass::encodeRGB(string redEnc, string greenEnc, string blueEnc)
{
  // encode red value
  if (redEnc == "Even" && redVal % 2 != 0)
  {
    redVal -= 1;
  }
  else if (redEnc == "Odd" && redVal % 2 == 0)
  {
    redVal += 1;
  }

  // encode green value
  if (greenEnc == "Even" && greenVal % 2 != 0)
  {
    greenVal -= 1;
  }
  else if (greenEnc == "Odd" && greenVal % 2 == 0)
  {
    greenVal += 1;
  }

  // encode blue value
  if (blueEnc == "Even" && blueVal % 2 != 0)
  {
    blueVal -= 1;
  }
  else if (blueEnc == "Odd" && blueVal % 2 == 0)
  {
    blueVal += 1;
  }
}

bool ColorClass::encodePixel(int encodingVal)
{
  bool validEnc = true;

  switch (encodingVal)
  {
    case ENCODING_BLACK:
      encodeRGB("Even", "Even", "Even");
      break;
    case ENCODING_RED:
      encodeRGB("Odd", "Even", "Even");
      break;
    case ENCODING_GREEN:
      encodeRGB("Even", "Odd", "Even");
      break;
    case ENCODING_BLUE:
      encodeRGB("Even", "Even", "Odd");
      break;
    case ENCODING_WHITE:
      encodeRGB("Odd", "Odd", "Odd");
      break;
    case ENCODING_YELLOW:
      encodeRGB("Odd", "Odd", "Even");
      break;
    case ENCODING_MAGENTA:
      encodeRGB("Odd", "Even", "Odd");
      break;
    case ENCODING_CYAN:
      encodeRGB("Even","Odd", "Odd");
      break;
    default:
      cout << "Error: Expecting to find encoding value from "
           << ENCODING_BLACK << " to " << ENCODING_CYAN
           << ", but find " << encodingVal << endl;
      validEnc = false;
  }
    return validEnc;
}

void ColorClass::decodePixel()
{
  if (redVal % 2 == 0 && greenVal % 2 == 0 && blueVal % 2 == 0)
  {
    setToBlack();
  }
  else if (redVal % 2 != 0 && greenVal % 2 == 0 && blueVal % 2 == 0)
  {
    setToRed();
  }
  else if (redVal % 2 == 0 && greenVal % 2 != 0 && blueVal % 2 == 0)
  {
    setToGreen();
  }
  else if (redVal % 2 == 0 && greenVal % 2 == 0 && blueVal % 2 != 0)
  {
    setToBlue();
  }
  else if (redVal % 2 != 0 && greenVal % 2 != 0 && blueVal % 2 != 0)
  {
    setToWhite();
  }
  else if (redVal % 2 != 0 && greenVal % 2 != 0 && blueVal % 2 == 0)
  {
    setToYellow();
  }
  else if (redVal % 2 != 0 && greenVal % 2 == 0 && blueVal % 2 != 0)
  {
    setToMagenta();
  }
  else if (redVal % 2 == 0 && greenVal % 2 != 0 && blueVal % 2 != 0)
  {
    setToCyan();
  }
}

void ColorClass::writePixel(ofstream &outFile)
{
  outFile << redVal << " " << greenVal << " " << blueVal << " ";
}
