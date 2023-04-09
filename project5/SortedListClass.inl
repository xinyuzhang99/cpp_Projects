#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: build a class to store a doubly-linked list in an always-sorted way
// Date: Apr 9th, 2023

template < class T >
SortedListClass< T >::SortedListClass()
{
  head = 0;
  tail = 0;
}

SortedListClass< T >::SortedListClass(const SortedListClass &rhs)
{
  head = 0;
  tail = 0;
  
  T currVal;
  for (int i = 0; i < rhs.getNumElems(); i++)
  {
    rhs.getElemAtIndex(i, currVal);
    insertValue(currVal);
  } 
}

SortedListClass< T >::~SortedListClass()
{
  clear();
}

void SortedListClass< T >::clear()
{
  LinkedNodeClass *temp = head;
  LinkedNodeClass *toDelete;

  while (temp != 0)
  {
    toDelete = temp->getNext();
    delete temp;
    temp = toDelete;
  }

  head = 0;
  tail = 0;
}

void SortedListClass< T >::insertValue(const T &valToInsert)
{
  // create a temp node and find the correct position
  LinkedNodeClass *temp = head;
  // create the new node to be inserted 
  LinkedNodeClass *newNodePtr;

  if (head == 0 && tail == 0)
  {
    newNodePtr = new LinkedNodeClass(0, valToInsert, 0);
    newNodePtr->setBeforeAndAfterPointers();
    head = newNodePtr;
    tail = newNodePtr;
  }
  else
  {
    while (temp != 0 && temp->getValue() <= valToInsert)
    {
      temp = temp->getNext();
    }

    if (temp == head)      // minimum value --> insert at the head
    {
      newNodePtr = new LinkedNodeClass(0, valToInsert, head);
      newNodePtr->setBeforeAndAfterPointers(); 
      head = newNodePtr;
    }
    else if (temp == 0)    // maximum value --> insert at the tail
    {
      newNodePtr = new LinkedNodeClass(tail, valToInsert, 0);
      newNodePtr->setBeforeAndAfterPointers(); 
      tail = newNodePtr;
    }
    else
    {
      newNodePtr = new LinkedNodeClass(temp->getPrev(), valToInsert, temp);
      newNodePtr->setBeforeAndAfterPointers(); 
    }
  }

}

void SortedListClass< T >::printForward() const
{
  cout << "Forward List Contents Follow:" << endl;

  LinkedNodeClass *temp = head;
  
  while (temp != 0)
  {
    cout << "  ";
    
    // print out the current node value
    T tempVal = temp->getValue();
    cout << tempVal << endl;
    temp = temp->getNext();
  }

  cout << "End Of List Contents" << endl;
}

void SortedListClass< T >::printBackward() const
{
  cout << "Backward List Contents Follow:" << endl;

  LinkedNodeClass *temp = tail;
  
  while (temp != 0)
  {
    cout << "  ";

    T tempVal = temp->getValue();
    cout << tempVal << endl;
    temp = temp->getPrev();   // move backward this time
  }

  cout << "End Of List Contents" << endl;
}

bool SortedListClass< T >::removeFront(T &theVal)
{
  bool didDeleteItem;
  LinkedNodeClass *newHeadPtr;

  if (head == 0 && tail == 0)
  {
    didDeleteItem = false;
  }
  else if (getNumElems() == 1)  // only have one node
  {
    theVal = head->getValue();
    delete head;
    head = 0;
    tail = 0;
    didDeleteItem = true;
  }
  else
  {
    theVal = head->getValue();
    newHeadPtr = head->getNext();
    delete head;
    head = newHeadPtr;
    head->setPreviousPointerToNull(); 

    didDeleteItem = true;
  }

  return didDeleteItem;
}

bool SortedListClass< T >::removeLast(T &theVal)
{
  bool didDeleteItem;
  LinkedNodeClass *newTailPtr;

  if (head == 0 && tail == 0)
  {
    didDeleteItem = false;
  }
  else if (getNumElems() == 1)  // only have one node
  {
    theVal = tail->getValue();
    delete tail;
    head = 0;
    tail = 0;
    didDeleteItem = true;
  }
  else
  {
    theVal = tail->getValue();
    newTailPtr = tail->getPrev();
    delete tail;
    tail = newTailPtr;
    tail->setNextPointerToNull();

    didDeleteItem = true;
  }

  return didDeleteItem;
}

int SortedListClass< T >::getNumElems() const
{
  int count = 0;
  LinkedNodeClass *temp = head;

  while (temp != 0)
  {
    count += 1;
    temp = temp->getNext(); 
  }
  return count;
}

bool SortedListClass< T >::getElemAtIndex(const int index, T &outVal) const
{
  bool didGetItem;
  LinkedNodeClass *temp = head; 

  if ((head == 0 && tail == 0) || index > getNumElems() - 1)
  {
    didGetItem = false;
  }
  else
  {
    int currInd = 0;
    while (currInd < index)
    {
      temp = temp->getNext();
      currInd += 1;
    }

    outVal = temp->getValue();
    didGetItem = true;
  }

  return didGetItem;
}

