#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"
#include "LIFOStackClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: build a class to implement a "last-in-first-out" stack data
// structure
// Date: Apr 4th, 2023

LIFOStackClass::LIFOStackClass()
{
  head = 0;
  tail = 0;
}

LIFOStackClass::~LIFOStackClass()
{
  clear();
}

void LIFOStackClass::push(const int &newItem)
{
  LinkedNodeClass *newNodePtr;

  if (head == 0 && tail == 0)
  {
    newNodePtr = new LinkedNodeClass(0, newItem, 0);
    newNodePtr -> setPreviousPointerToNull();
    head = newNodePtr;
    tail = newNodePtr;
  }
  else   //push the new item to the head 
  {
    newNodePtr = new LinkedNodeClass(0, newItem, head);
    newNodePtr -> setPreviousPointerToNull();
    head = newNodePtr;
  }
}

bool LIFOStackClass::pop(int &outItem)
{
  bool didDeleteItem;
  LinkedNodeClass *newHeadPtr;

  if (head == 0 && tail == 0)
  {
    didDeleteItem = false;
  }
  else if (getNumElems() == 1)   // only have one node
  {
    outItem = head->getValue();
    delete head;
    head = 0;
    tail = 0;

    didDeleteItem = true;
  }
  else  // remove the item at the head
  {
    outItem = head->getValue();
    newHeadPtr = head->getNext();
    delete head;
    head = newHeadPtr;
    head->setPreviousPointerToNull();

    didDeleteItem = true;
  }

  return didDeleteItem;
}

void LIFOStackClass::print() const
{
  LinkedNodeClass *temp;

  if (head == 0 && tail == 0)
  {
    cout << "Stack is empty!" << endl;
  }
  else
  {
    temp = head;

    while (temp != 0)
    {
      cout << temp->getValue() << " ";
      temp = temp->getNext();
    }
    cout << endl;
  }
}

int LIFOStackClass::getNumElems() const
{
  LinkedNodeClass *temp = head;
  int count = 0;
  
  while (temp != 0)
  {
    count += 1;
    temp = temp->getNext(); 
  }

  return count;
}

void LIFOStackClass::clear()
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
