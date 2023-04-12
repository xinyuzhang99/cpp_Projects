#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "LIFOStackClass.h"

// Name: Xinyu Zhang (xyuzhang: 42192372)
// Purpose: Develop three common linked data structures: a sorted doubly-linked
// list, a simple queue and a simple stack
// Date: Apr 4th, 2023

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main()
{
  //This is just a placeholder main function - it does exceptionally
  //little actual testing, so you'll want to add your own tests here.
  //Feel free to leave your tests in the version of this file you
  //submit, but we will not be running your main function, so the
  //output, etc., of your main doesn't need to match anything from
  //a sample output, etc.
  
  // test SortedListClass
  cout << "-------------------------------------------" << endl; 
  cout << "Start to test SortedListClass" << endl;
  cout << "-------------------------------------------" << endl;
  SortedListClass testList;

  testList.printForward();
  testList.printBackward();
  testList.insertValue(42);
  testList.insertValue(10);
  testList.insertValue(50);
  testList.insertValue(1);
  testList.insertValue(43);
  testList.insertValue(30);
  testList.printForward();
  testList.printBackward();
  
  int headVal;
  int tailVal;
  cout << "Remove the front item: " << endl;
  testList.removeFront(headVal);
  testList.printForward(); 
  cout << "Remove the last item: " << endl;
  testList.removeLast(tailVal);
  // testList.removeFront(headVal);
  // testList.removeFront(headVal);
  // testList.removeFront(headVal);
  // testList.removeLast(headVal);
  // testList.printForward();
  cout << testList.getNumElems() << endl;
  
  // int outVal;
  // int index = 4;
  // testList.getElemAtIndex(index, outVal);
  // cout << "value at index " << index << ": " << outVal << endl; 
  
  // testList.clear();
  testList.printForward();
  
  SortedListClass testListSecond(testList);
  cout << "Print the second list: " << endl;
  testListSecond.printForward();

  cout << "-------------------------------------------" << endl;

  // test FIFOQueueClass
  cout << "Start to test FIFOQueueClass" << endl;
  cout << "-------------------------------------------" << endl;
  FIFOQueueClass testQueue;
  
  testQueue.print();
  cout << testQueue.getNumElems() << endl;
  testQueue.enqueue(5);
  testQueue.enqueue(10);
  testQueue.enqueue(12);
  testQueue.print();
  
  int outItem;
  testQueue.dequeue(outItem);
  cout << "Out item: " << outItem << endl;
  testQueue.dequeue(outItem); 
  cout << "Out item: " << outItem << endl; 
  cout << testQueue.getNumElems() << endl;
  
  testQueue.clear();
  testQueue.print();  
  cout << testQueue.dequeue(outItem) << endl;
  // cout << "Out item: " << outItem << endl; 
  
  cout << "-------------------------------------------" << endl; 

  // test LIFOStackClass
  cout << "Start to test LIFOStackClass" << endl;
  cout << "-------------------------------------------" << endl;
  LIFOStackClass testStack;

  testStack.print();
  cout << testStack.getNumElems() << endl;
  testStack.push(5);
  testStack.push(10);
  testStack.push(12);
  cout << testStack.getNumElems() << endl;
  testStack.print(); 

  int outS;
  testStack.pop(outS);
  cout << "Out item: " << outS << endl;
  testStack.print(); 
  testStack.pop(outS);
  cout << "Out item: " << outS << endl; 
  testStack.print(); 
  
  testStack.clear();
  cout << testStack.pop(outS) << endl;
  
  return 0;
}

#endif
