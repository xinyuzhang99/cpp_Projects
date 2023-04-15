#include <iostream>

using namespace std;

#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "CarClass.h"
#include "constants.h"

int main()
{
  FIFOQueueClass< CarClass > testQueue;
  testQueue.print();

  int currentTime = 1;
  CarClass testCarE(EAST_DIRECTION, currentTime);
  CarClass testCarW(WEST_DIRECTION, currentTime);
  testQueue.enqueue(testCarE);  
  testQueue.print();
  testQueue.enqueue(testCarW);
  testQueue.print();
  cout << "Finish adding cars" << endl;

  // dequeue
  CarClass outCar;
  testQueue.dequeue(outCar);
  testQueue.print();
}
