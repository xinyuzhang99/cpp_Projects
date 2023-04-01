#ifndef _IMAGECLASS_H_
#define _IMAGECLASS_H_

#include <fstream>
#include <string>

#include "ColorClass.h"
#include "RowColumnClass.h"
#include "constants.h"

class ImageClass
{
  private:
    RowColumnClass imageRowCol;
    ColorClass **pixelMatrix;

  public:
    // Default constructor: set all image pixels to be full black
    // No red, no green and no blue
    ImageClass();
    
    // Check if the provided row/col in &inRowCol is in the image range
    bool isLocationValid(const RowColumnClass &inRowCol) const; 

    // Return the number of rows of the image
    int getImageRow() const;

    // Return the number of columns of the image
    int getImageCol() const;

    // Check if the input image has the correct magic number
    // If the magic number is correct, return true; otherwise return false
    bool checkMagicNumber(ifstream &inFile);

    // Check if the input image has the valid width and height
    // If the width and height are valid, return true; otherwise return false
    // Store width and height in imageRowCol
    bool checkWidthHeight(ifstream &inFile);

    // Check if the input image has the correct maximum color value
    // If the maximum color value is correct, return true;
    // otherwise return false
    bool checkMaxColor(ifstream &inFile);

    // Check if the input pixel has the valid RGB values
    // If the RGB values are valid, return true; otherwise return false
    bool checkPixel(ifstream &inFile);

    // Check if the input file has the correct format
    // If all formats are valid, return true; otherwise return false
    bool checkInput(const string &initialFileName);

    // Encode the message to the initial image
    // Return true if the encoding succeeds, otherwise return false
    bool encodeMessage(const string &msgFileName, const RowColumnClass &msgPos);
    
    // Decode the encoded image to show the information    
    void decodeMessage();
 
    // Write the encoded image to the file
    void writeImage(const string &writtenFileName);

};

#endif
