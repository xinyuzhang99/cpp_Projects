#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: Develop a class to be the data type for individual nodes of a doubly
// -linked data structure
// Date: Apr 4th, 2023

LinkedNodeClass::LinkedNodeClass(LinkedNodeClass *inPrev, const int &inVal,
                                 LinkedNodeClass *inNext)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

int LinkedNodeClass::getValue() const
{
  return nodeVal;
}

LinkedNodeClass* LinkedNodeClass::getNext() const
{
  return nextNode;
}

LinkedNodeClass* LinkedNodeClass::getPrev() const
{
  return prevNode;
}

void LinkedNodeClass::setNextPointerToNull()
{
  nextNode = 0;
}

void LinkedNodeClass::setPreviousPointerToNull()
{
  prevNode = 0;
}

void LinkedNodeClass::setBeforeAndAfterPointers()
{
  if (prevNode != 0)
  {
    prevNode->nextNode = this;
  }
 
  if (nextNode != 0)
  {
    nextNode->prevNode = this;
  }
}
