#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

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
    void setRow(const int inRow);

    // Setter function: set the column attribute value 
    void setCol(const int inCol);

    // Getter function: return the row attribute value
    int getRow() const;

    // Getter function: return the column attribute value
    int getCol() const;

    // Add the row and column index values in the input parameter to the object
    // Use getter function to get the values of another object
    void addRowColTo(const RowColumnClass &inRowCol);

    // Print the objects's attributes in the format "[<row>,<col>]"
    void printRowCol() const;
};

#endif
