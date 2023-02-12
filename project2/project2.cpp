#include <iostream>

using namespace std;

// Name: Xinyu Zhang(xyuzhang: 42192372)
// Purpose: 
// Date: Feb 8th, 2023

const int MAXIMUM_ALLOWED_COLOR = 1000;
const int MINIMUM_ALLOWED_COLOR = 0;
const int COLOR_COMPONENT_NUMBER = 3;
const int DEFAULT_INDEX = -99999;

class ColorClass
{
  private:
    int redVal;
    int greenVal;
    int blueVal;

    // Clip RGB values to keep them inside the range [0, 1000]
    // Return true if clipping is implemented; otherwise return false
    bool clipColor();

  public:

    // Default constructor: set the RGB values to the color full white
    // Full red, full green and full blue
    ColorClass();        

    // Value constructor
    // Implement clipping operation if the values are outside the color range
    ColorClass(
      const int inRed,     // initial red value provided
      const int inGreen,   // initial green value provided
      const int inBlue     // initial blue value provided
    );

    // Set the color's component color values to form black color
    // No red, no green and no blue
    void setToBlack();

    // Set the color's component color values to form red color 
    // Full red, no green and no blue
    void setToRed();
    
    // Set the color's component color values to form green color
    // No red, full green and no blue 
    void setToGreen();

    // Set the color's component color values to form blue color 
    // No red, no green and full blue
    void setToBlue();

    // Set the color's component color values to form white color  
    // Full red, full green and full blue
    void setToWhite();

    // Set the color object's RGB values to the provided values
    // Clip any input value outside the color value range [0, 1000]
    // Return true if clipping is needed, otherwise return false 
    bool setTo(
      const int inRed,
      const int inGreen,
      const int inBlue
    ); 

    // Copy the RGB values of another object of ColorClass
    // Return true if any clipping is necessary, otherwise return false
    bool setTo(
      const ColorClass &inColor
    );

    // Add RGB values of the rhsColor object to the current object
    // Return true if any clipping is necessary, otherwise return false
    bool addColor(
      const ColorClass &rhsColor
    );

    // Subtract RGB values of the rhsColor object from the current object 
    // Return true if any clipping is necessary, otherwise return false
    bool subtractColor(
      const ColorClass &rhsColor
    );

    // Multiply each RGB value by the provided adjustment factor
    // Return true if any clipping is necessary, otherwise return false
    bool adjustBrightness(
      const double adjFactor
    );

    // Print the RGB component values to the console 
    // The format is "R: <red> G: <green> B: <blue>"
    void printComponentValues() const;   // a const member function
};

class RowColumnClass
{
  private:
    int rowIndex;
    int colIndex;

  public:

    // Default constructor: set default row and column values
    RowColumnClass();

    // Value constructor: set the row and column values
    RowColumnClass(
      const int inRow,    // the row value provided
      const int inCol     // the column value provided
    );

    // Setter function: set the row and column attribute values
    void setRowCol(
      const int inRow,
      const int inCol
      );

    // Setter function: set the row attribute value
    void setRow(
      const int inRow
      );

    // Setter function: set the column attribute value 
    void setCol(
      const int inCol
      );

    // Getter function: return the row attribute value
    int getRow() const;

    // Getter function: return the column attribute value
    int getCol() const;

    // Add the row and column index values in the input parameter to the object
    // Use getter function to get the values of another object
    void addRowColTo(
      const RowColumnClass &inRowCol
    );

    // Print the objects's attributes in the format "[<row>,<col>]"
    void printRowCol() const;
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;
  return 0;
}
#endif

ColorClass::ColorClass()
{
  redVal = MAXIMUM_ALLOWED_COLOR;
  greenVal = MAXIMUM_ALLOWED_COLOR; 
  blueVal = MAXIMUM_ALLOWED_COLOR;
}

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

bool ColorClass::adjustBrightness(const double adjFactor)
{
  redVal = int(redVal * adjFactor);
  greenVal = int(greenVal * adjFactor);
  blueVal = int(blueVal * adjFactor);
  return clipColor();
}

void ColorClass::printComponentValues() const
{
  cout << "R: " << redVal << " G: " << greenVal << " B: " << blueVal;
}

RowColumnClass::RowColumnClass()
{
  rowIndex = DEFAULT_INDEX;
  colIndex = DEFAULT_INDEX;
}

RowColumnClass::RowColumnClass(const int inRow, const int inCol)
{
  rowIndex = inRow;
  colIndex = inCol; 
}

void RowColumnClass::setRowCol(const int inRow, const int inCol)
{
  rowIndex = inRow;                                                              
  colIndex = inCol;
}

void RowColumnClass::setRow(const int inRow)
{
  rowIndex = inRow; 
}

void RowColumnClass::setCol(const int inCol)
{
  colIndex = inCol;
}

int RowColumnClass::getRow() const
{
  return rowIndex;
}

int RowColumnClass::getCol() const
{
  return colIndex;
}

void RowColumnClass::addRowColTo(const RowColumnClass &inRowCol)
{
  rowIndex += inRowCol.getRow();
  colIndex += inRowCol.getCol();
}

void RowColumnClass::printRowCol() const
{
  cout << "[" << rowIndex << "," << colIndex << "]";
}
