#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: Develop a templated class to be the data type for individual nodes 
// of a doubly-linked data structure
// Date: Apr 9th, 2023

template < class T >
LinkedNodeClass< T >::LinkedNodeClass(LinkedNodeClass *inPrev, const T &inVal,
                                 LinkedNodeClass *inNext)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

int LinkedNodeClass< T >::getValue() const
{
  return nodeVal;
}

LinkedNodeClass* LinkedNodeClass< T >::getNext() const
{
  return nextNode;
}

LinkedNodeClass* LinkedNodeClass< T >::getPrev() const
{
  return prevNode;
}

void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = 0;
}

void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = 0;
}

void LinkedNodeClass< T >::setBeforeAndAfterPointers()
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
