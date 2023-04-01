#include <iostream>
#include <string>

using namespace std;

#include "RowColumnClass.h"
#include "constants.h"

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
