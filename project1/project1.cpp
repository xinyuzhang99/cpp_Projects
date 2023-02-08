#include <iostream>  //Need for Cout, Cin
using namespace std;

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: To approximate the area between a curve and the X-axis by fitting a
// number of rectangles
// Date: Jan 24rd, 2023

const int APPROXIMATE_INTEGRAL_OPTION = 1;
const int EXPERIMENT_PRECISION_OPTION = 2;
const int QUIT_PROGRAM_OPTION = 3;
const int CUBED_POWER = 3;
const int SQUARED_POWER = 2;
const int MAX_ITERATION_NUM = 100;

// Print out the possible choices the user has in a menu format
// No input and output
void printMenu();

// Compute the power of the input parameter "val", and returns the result
double toThePower(const double val, const int power);

// Calculate the y-value of the curve at a certain point "xValue"
// Return false if the resulting y is negative
// Return true if the resulting value is non-negative
// Store the return value into a reference parameter &resultVal
bool evaluateCubicFormula(
  const double aCoeff,    // coefficients of the formula
  const double bCoeff, 
  const double cCoeff, 
  const double dCoeff, 
  const double xValue, 
  double &resultVal);    

// Compute the approximated area between the X-axis and the curve
// The curve is defined by the evaluateCubicFormula with four coeffients
// The area of interest's interval is from "startX" to "endX"
double approximateAreaWithRectangles(
  const double aCoeff, 
  const double bCoeff, 
  const double cCoeff, 
  const double dCoeff, 
  const double startX,    // start of the interval on the X-axis
  const double endX,      // end of the interval on the X-axis
  const int numRects);    // number of rectangles to fit within the interval 

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  int userChoice;             
  double aCoeff;
  double bCoeff;
  double cCoeff;
  double dCoeff;
  double startX;
  double endX;
  int numRects;
  double resultArea;
  bool doesQuit = false;      // determine if the main function stops

  while (!doesQuit)
  {
    printMenu();
    cout << "YOUR CHOICE: "; //Prompt
    cin >> userChoice;

    if (userChoice == APPROXIMATE_INTEGRAL_OPTION)
    {
      cout << "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
      cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;

      cout << "Now enter x start and end values: ";
      cin >> startX >> endX;

      cout << "Enter the number of rectangles to use: ";
      cin >> numRects;

      resultArea = approximateAreaWithRectangles(aCoeff, bCoeff, cCoeff, dCoeff,
                                                 startX, endX, numRects);
      cout << "Rectangle result is: " << resultArea << endl;
    }
    else if (userChoice == EXPERIMENT_PRECISION_OPTION)
    {
      double correctAnswer;  // provided correct answer by the user
      double precision;      // required tolerance by the user
      double error;          // error between correct answer and current area

      cout << "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
      cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;

      cout << "Now enter x start and end values: ";
      cin >> startX >> endX;

      cout << "Enter correct answer: ";
      cin >> correctAnswer;

      cout << "Enter precision to reach: ";
      cin >> precision;

      // Initialization
      // start with zero rectanges to fit the curve
      numRects = 0;
      resultArea = approximateAreaWithRectangles(aCoeff, bCoeff, cCoeff,       
                                                 dCoeff, startX, endX,         
                                                 numRects);
      error = resultArea - correctAnswer;   // Initialize the error    
    
      while (((error > precision) || (error < -precision)) 
            && (numRects < MAX_ITERATION_NUM)) 
      {
        numRects += 1; 
        resultArea = approximateAreaWithRectangles(aCoeff, bCoeff, cCoeff,
                                                   dCoeff, startX, endX,
                                                   numRects);
        error = resultArea - correctAnswer;
      }

      if (numRects < MAX_ITERATION_NUM)  // result area satisfies the condition
      {
        cout << "Rectangles needed to reach precision: " << numRects
             << endl;
      }
      else                         // cannot achieve the tolerance in 100 loops
      {
        cout << "Tried 100 rectangles without reaching precision" << endl;
      }
    }
    else if (userChoice == QUIT_PROGRAM_OPTION)
    {
      doesQuit = true;       // stop the main function
      cout << "Thanks for using this program" << endl;
    }
  }

  return 0;
}
#endif

void printMenu()
{
  cout << APPROXIMATE_INTEGRAL_OPTION 
       << ". Approximate Integral Using Rectangles" << endl;
  cout << EXPERIMENT_PRECISION_OPTION 
       << ". Experiment With Rectangle Precision" << endl;
  cout << QUIT_PROGRAM_OPTION << ". Quit The Program" << endl;
}

double toThePower(const double val, const int power)
{
  double result = 1;
  
  for (int i = 1; i <= power; i++)
  {
    result *= val;
  }

  return result;
}

bool evaluateCubicFormula(const double aCoeff, const double bCoeff, 
                          const double cCoeff, const double dCoeff, 
                          const double xValue, double &resultVal)
{
  double y = aCoeff * toThePower(xValue, CUBED_POWER)
           + bCoeff * toThePower(xValue, SQUARED_POWER)
           + cCoeff * xValue + dCoeff;

  resultVal = y;

  if (y >= 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

double approximateAreaWithRectangles(const double aCoeff, const double bCoeff,
                                     const double cCoeff, const double dCoeff, 
                                     const double startX, const double endX, 
                                     const int numRects)
{
  double area = 0;
  double width = (endX - startX) / numRects;
  double coordinateX = startX + width / 2.0;

  for (int i = 1; i <= numRects; i++)
  {
    double height;
    bool isPositive = evaluateCubicFormula(aCoeff, bCoeff, cCoeff, dCoeff,
                                           coordinateX, height);

    if (isPositive)
    {
      area += height * width;
    }
    else if (!isPositive)
    {
      area -= height * width;
    }

    coordinateX += width;
  }
  
  return area;  
}
