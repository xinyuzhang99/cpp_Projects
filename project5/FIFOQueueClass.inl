#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: build a class to implement a "first-in-first-out" queue data 
// structure
// Date: Apr 9th, 2023

template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

FIFOQueueClass< T >::~FIFOQueueClass()
{
  clear();
}

void FIFOQueueClass< T >::enqueue(const T &newItem)
{
  LinkedNodeClass *enqueItem;  // create the new node

  if (head == 0 && tail == 0)
  {
    enqueItem = new LinkedNodeClass(0, newItem, 0);
    enqueItem->setBeforeAndAfterPointers();
    head = enqueItem;
    tail = enqueItem;
  }
  else
  {
    enqueItem = new LinkedNodeClass(tail, newItem, 0);
    enqueItem->setBeforeAndAfterPointers();  
    tail = enqueItem; 
  }
}

bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  // remove the node at the head
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
  else
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

void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass *temp;

  if (head == 0 && tail == 0)
  {
    cout << "Queue is empty!" << endl;
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

int FIFOQueueClass< T >::getNumElems() const
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

void FIFOQueueClass< T >::clear()
{
  LinkedNodeClass *temp = head;
  LinkedNodeClass *toDelete;

  while (temp != 0)
  {
    toDelete = head->getNext();
    delete temp;
    temp = toDelete;
  }

  head = 0;
  tail = 0;
}
