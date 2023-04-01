#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

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

    // Set the color's component color values to form yellow color
    // Full red, full green and no blue
    void setToYellow();

    // Set the color's component color values to form magenta color
    // Full red, no green and full blue
    void setToMagenta();

    // Set the color's component color values to form cyan color
    // No red, full green and full blue 
    void setToCyan();

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
    bool setTo(const ColorClass &inColor);

    // Add RGB values of the rhsColor object to the current object
    // Return true if any clipping is necessary, otherwise return false
    bool addColor(const ColorClass &rhsColor);

    // Subtract RGB values of the rhsColor object from the current object 
    // Return true if any clipping is necessary, otherwise return false
    bool subtractColor(const ColorClass &rhsColor);

    // Multiply each RGB value by the provided adjustment factor
    // Return true if any clipping is necessary, otherwise return false
    bool adjustBrightness(const double adjFactor);

    // Print the RGB component values to the console 
    // The format is "R: <red> G: <green> B: <blue>"
    void printComponentValues() const;   // a const member function

    // Read the RGB values of a pixel and check if they are valid
    // If the RGB values are valid, return true; otherwise return false
    bool readColor(ifstream &inFile);
    
    // Encode RGB values based on encoding requirements provided
    void encodeRGB(string redEnc, string greenEnc, string blueEnc);

    // Encode the image based on the encoding value read from the message
    // Reture true if the image can be encoded; otherwise return false;
    bool encodePixel(int encodingVal);

    // Decode the encoded image to show the information
    void decodePixel();

    // Write the RGB values of a pixel to the file
    void writePixel(ofstream &outFile);
};

#endif
