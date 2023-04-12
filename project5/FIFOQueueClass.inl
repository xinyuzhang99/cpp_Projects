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

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
{
  clear();
}

template < class T > 
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
  LinkedNodeClass< T > *enqueItem;  // create the new node

  if (head == 0 && tail == 0)
  {
    enqueItem = new LinkedNodeClass< T >(0, newItem, 0);
    enqueItem->setBeforeAndAfterPointers();
    head = enqueItem;
    tail = enqueItem;
  }
  else
  {
    enqueItem = new LinkedNodeClass< T >(tail, newItem, 0);
    enqueItem->setBeforeAndAfterPointers();  
    tail = enqueItem; 
  }
}

template < class T > 
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  // remove the node at the head
  bool didDeleteItem;
  LinkedNodeClass< T > *newHeadPtr;

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

template < class T > 
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T > *temp;

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

template < class T > 
int FIFOQueueClass< T >::getNumElems() const
{
  int count = 0;
  LinkedNodeClass< T > *temp = head;

  while (temp != 0)
  {
    count += 1;
    temp = temp->getNext();
  }
  return count;
}

template < class T > 
void FIFOQueueClass< T >::clear()
{
  LinkedNodeClass< T > *temp = head;
  LinkedNodeClass< T > *toDelete;

  while (temp != 0)
  {
    toDelete = temp->getNext();
    delete temp;
    temp = toDelete;
  }

  head = 0;
  tail = 0;
}
