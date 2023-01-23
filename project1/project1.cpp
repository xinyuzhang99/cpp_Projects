#include <iostream>  //Need for Cout, Cin
using namespace std;

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose:
// Date: Jan 23rd, 2023

// Print out the possible choices the user has in a menu format
// No input and output
void printMenu();

// Compute the power of the input parameter "val", and returns the result
double toThePower(const double val, const int power);

// Calculate the height
bool evaluateCubicFormula(
  const double aCoeff,
  const double bCoeff, 
  const double cCoeff, 
  const double dCoeff, 
  const double xValue, 
  double &resultVal);

double approximateAreaWithRectangles(
  const double aCoeff, 
  const double bCoeff, 
  const double cCoeff, 
  const double dCoeff, 
  const double startX, 
  const double endX, 
  const int numRects);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main(){

  return 0;
}
#endif
