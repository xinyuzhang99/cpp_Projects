#ifndef _MESSAGECLASS_H_
#define _MESSAGECLASS_H_

class MessageClass
{
  private:
    RowColumnClass msgRowCol;
    int **msgMatrix;  // message is a matrix of integers

  public:
    // Default constructor
    MessageClass();

    // Check if the message has the valid width and height
    // If the width and height are valid, return true; otherwise return false
    // Store the result in validMsgFound
    // Store width and height in msgRowCol
    bool checkWidthHeight(ifstream &msgFile);

    // Check if the message has the valid values
    // If all values are valid, return true; otherwise return false
    // Store the result in validMsgFound
    bool checkValue(ifstream &msgFile);

    // Getter function: return the encoding value at the given position
    int getValue(int rInd, int cInd);

    // Getter function: return the number of rows in the message
    int getMsgRow() const;

    // Getter function: return the number of columns in the message
    int getMsgCol() const;
};

#endif
