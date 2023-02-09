#include <iostream>

using namespace std;

// Name: Xinyu Zhang(xyuzhang: 42192372)
// Purpose: 
// Date: Feb 8th, 2023

class ColorClass
{
  private:
    int redVal;
    int greenVal;
    int blueVal;

    // clip RGB values to keep them inside the range [0, 1000]
    void clipColor();

  public:

    // Default constructor
    ColorClass();        

    // Value constructor
    // Implement clipping operation if the values are outside the color range
    ColorClass(
      const int inRed,     // initial red value provided
      const int inGreen,   // initial green value provided
      const int inBlue     // initial blue value provided
    );

    // Set the color's component color values to form black color
    void setToBlack();

    // Set the color's component color values to form red color 
    void setToRed();
    
    // Set the color's component color values to form green color
    void setToGreen();

    // Set the color's component color values to form blue color 
    void setToBlue();

    // Set the color's component color values to form white color  
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
    int columnIndex;

  public:

    // Default constructor
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
    void addRowColTo(
      const RowColumnClass &inRowCol
    )

    // Print the objects's attributes in the format "[<row>,<col>]"
    void printRowCol() const;
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  return 0;
}
#endif


