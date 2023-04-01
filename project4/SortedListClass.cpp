#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"

SortedListClass::SortedListClass()
{
  head = 0;
  tail = 0;
}

SortedListClass::SortedListClass(const SortedListClass &rhs)
{
  head = 0;
  tail = 0;
  
  int currVal;
  for (int i = 0; i < rhs.getNumElems(); i++)
  {
    rhs.getElemAtIndex(i, currVal);
    insertValue(currVal);
  } 
}

SortedListClass::~SortedListClass()
{
  clear();
}

void SortedListClass::clear()
{
  LinkedNodeClass *temp = head;
  LinkedNodeClass *toDelete;

  if (head == 0)
  {
    cout << "The list is already in empty state" << endl;
  }
  else
  {
    while (temp != 0)
    {
      toDelete = temp->getNext();
      delete temp;
      temp = toDelete;
    }

    head = 0;
    tail = 0;
  }
}

void SortedListClass::insertValue(const int &valToInsert)
{
  // create a temp node and find the correct position
  LinkedNodeClass *temp = head;
  while (temp->getValue() <= valToInsert && temp != 0)
  {
    temp = temp -> getNext();
  }

  // create the new node to be inserted
  LinkedNodeClass *insertNode;

  if (temp == head)      // minimum value --> insert at the head
  {
    insertNode = new LinkedNodeClass(0, valToInsert, head);
  }
  else if (temp == tail) // maximum value --> insert at the tail
  {
    insertNode = new LinkedNodeClass(tail, valToInsert, 0);
  }
  else
  {
    insertNode = new LinkedNodeClass(temp->getPrev(), valToInsert, 
                                     temp->getNext());
  }

  // insert the node at the corresponding position
  insertNode->setBeforeAndAfterPointers();
}

void SortedListClass::printForward() const
{
  cout << "Forward List Contents Follow:" << endl;

  LinkedNodeClass *temp = head;
  int count = 1;
  int numSpace;
  
  while (temp != 0)
  {
    // print put number of spaces
    numSpace = count * 2;
    for (int i = 0; i < numSpace; i++)
    {
      cout << " ";
    }
    
    // print out the current node value
    int tempVal = temp->getValue();
    cout << tempVal << endl;

    count++;
    temp = temp->getNext();
  }

  cout << "End Of List Contents" << endl;
}

void SortedListClass::printBackward() const
{
  cout << "Backward List Contents Follow:" << endl;

  LinkedNodeClass *temp = tail;
  int count = 1;
  int numSpace;
  
  while (temp != 0)
  {
    numSpace = count * 2;
    for (int i = 0; i < numSpace; i++)
    {
      cout << " ";
    }

    int tempVal = temp->getValue();
    cout << tempVal << endl;

    count ++;
    temp = temp->getPrev();   // move backward this time
  }

  cout << "End Of List Contents" << endl;
}

bool SortedListClass::removeFront(int &theVal)
{
  bool didDeleteItem;
  LinkedNodeClass *newHeadPtr;

  if (head == 0)
  {
    didDeleteItem = false;
  }
  else
  {
    theVal = head->getValue();
    newHeadPtr = head->getNext();
    delete head;
    head = newHeadPtr;

    didDeleteItem = true;
  }

  return didDeleteItem;
}

bool SortedListClass::removeLast(int &theVal)
{
  bool didDeleteItem;
  LinkedNodeClass *newTailPtr;

  if (head == 0)
  {
    didDeleteItem = false;
  }
  else
  {
    theVal = tail->getValue();
    newTailPtr = tail->getPrev();
    delete tail;
    tail = newTailPtr;

    didDeleteItem = true;
  }

  return didDeleteItem;
}

int SortedListClass::getNumElems() const
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

bool SortedListClass::getElemAtIndex(const int index, int &outVal) const
{
  bool didGetItem;
  LinkedNodeClass *temp = head; 

  if (head == 0 || index > getNumElems() - 1)
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

