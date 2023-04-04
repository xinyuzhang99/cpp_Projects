#include <iostream>
#include <fstream>

using namespace std; 

#include "RowColumnClass.h"
#include "MessageClass.h"
#include "constants.h"

MessageClass::MessageClass()
{
}

bool MessageClass::checkWidthHeight(ifstream &msgFile)
{
  // check if the width is in proper format 
  bool validMsgFound = false;
  if (msgFile.eof())
  {
    cout << "Error: EOF before reading the width of the message" << endl;
    return validMsgFound;
  }
  else if (msgFile.fail())
  {
    msgFile.clear();
    msgFile.ignore(200, '\n');
    cout << "Error: Failing to read the width of the message" << endl;
    return validMsgFound;
  }
  
  int msgCol;
  int msgRow;
  msgFile >> msgCol;

  // check if the height is in proper format
  validMsgFound = false;
  if (msgFile.eof())  
  {
    cout << "Error: EOF before reading the height of the message" << endl;
    return validMsgFound; 
  }
  else if (msgFile.fail()) 
  {
    msgFile.clear();
    msgFile.ignore(200, '\n'); 
    cout << "Error: Failing to read the height of the message" << endl;
    return validMsgFound;
  }

  msgFile >> msgRow;

  validMsgFound = true;
  msgRowCol.setRowCol(msgRow, msgCol);
  return validMsgFound;
}

bool MessageClass::checkValue(ifstream &msgFile)
{
  bool validMsgFound = false;
  if (msgFile.eof())
  {
    cout << "Error: EOF before reading the message values" << endl;
    return validMsgFound;
  }

  int msgRow = msgRowCol.getRow();
  int msgCol = msgRowCol.getCol();
  msgMatrix = new int*[msgRow];
  
  // dynamically allocate the according memory needed
  for (int rInd = 0; rInd < msgRow; rInd++)
  {
    msgMatrix[rInd] = new int[msgCol];
  }

  // put values into the matrix
  for (int rInd = 0; rInd < msgRow; rInd++)
  {
    for (int cInd = 0; cInd < msgCol; cInd++)
    {
      msgFile >> msgMatrix[rInd][cInd]; 
      if (msgFile.fail())
      {
        msgFile.clear();
        msgFile.ignore(200, '\n'); 
        cout << "Error: Reading message value at row: " << rInd
             << " col: " << cInd << endl;
        return validMsgFound;
      }
    }
  }
  validMsgFound = true;
  return validMsgFound;
}

int MessageClass::getValue(int rInd, int cInd)
{
  return msgMatrix[rInd][cInd];
}

int MessageClass::getMsgRow() const
{
  return msgRowCol.getRow();
}

int MessageClass::getMsgCol() const
{
  return msgRowCol.getCol();
}
