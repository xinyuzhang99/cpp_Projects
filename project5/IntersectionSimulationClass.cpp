#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  EventClass carArrival;
  int occurTime;
  int arrivalTime;

  // create the car arrival event based on the direction
  if (travelDir == EAST_DIRECTION)
  {
    occurTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
    arrivalTime = currentTime + occurTime;
    carArrival = EventClass(arrivalTime, EVENT_ARRIVE_EAST);
  }
  else if (travelDir == WEST_DIRECTION)
  {
    occurTime = getPositiveNormal(westArrivalMean, westArrivalStdDev);
    arrivalTime = currentTime + occurTime; 
    carArrival = EventClass(arrivalTime, EVENT_ARRIVE_WEST);
  }
  else if (travelDir == NORTH_DIRECTION)
  {
    occurTime = getPositiveNormal(northArrivalMean, northArrivalStdDev);
    arrivalTime = currentTime + occurTime;
    carArrival = EventClass(arrivalTime, EVENT_ARRIVE_NORTH);
  }
  else if (travelDir == SOUTH_DIRECTION)
  {
    occurTime = getPositiveNormal(southArrivalMean, southArrivalStdDev);
    arrivalTime = currentTime + occurTime;
    carArrival = EventClass(arrivalTime, EVENT_ARRIVE_SOUTH);
  }

  // add the event into the list
  eventList.insertValue(carArrival);
  cout << "Time: " << currentTime << " Scheduled " << carArrival << endl;
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
  EventClass lightChange;
  int lightChangeTime;

  if (currentLight == LIGHT_GREEN_EW)          // change to Yello East-West
  {
    lightChangeTime = currentTime + eastWestGreenTime;
    lightChange = EventClass(lightChangeTime, EVENT_CHANGE_YELLOW_EW);
  }
  else if (currentLight == LIGHT_YELLOW_EW)   // change to Green North-South
  {
    lightChangeTime = currentTime + eastWestYellowTime;
    lightChange = EventClass(lightChangeTime, EVENT_CHANGE_GREEN_NS);
    
  }
  else if (currentLight == LIGHT_GREEN_NS)    // change to Yellow North-South
  {
    lightChangeTime = currentTime + northSouthGreenTime;
    lightChange = EventClass(lightChangeTime, EVENT_CHANGE_YELLOW_NS);
  }
  else if (currentLight == LIGHT_YELLOW_NS)   // change to Green East-West
  {
    lightChangeTime = currentTime + northSouthYellowTime;
    lightChange = EventClass(lightChangeTime, EVENT_CHANGE_GREEN_EW);
  }

  cout << "Time: " << currentTime << " Scheduled " <<  lightChange << endl; 
  eventList.insertValue(lightChange);
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  // check if the event scheduled time occurs after the simulation end time
  bool isHandled = false;

  // handle the event based on its type
  EventClass nextEvent;
  eventList.removeFront(nextEvent);    
  int eventType = nextEvent.getType();
  currentTime = nextEvent.getTimeOccurs();

  if (currentTime > timeToStopSim)
  {
    cout << "Next event occurs AFTER the simulation end time (" 
         << nextEvent <<"!)" << endl;
    return isHandled;
  }

  cout << "Handling " << nextEvent << endl;
  if (eventType == EVENT_ARRIVE_EAST)
  {  
    // add the car to the east-bound queue
    CarClass inEastCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(inEastCar);
    cout << "Time: " << currentTime << " Car #" << inEastCar.getId() 
         << " arrives east-bound - queue length: " << eastQueue.getNumElems() 
         << endl;  
    // schedule the next east-bound arrival event
    scheduleArrival(EAST_DIRECTION);

    // compare the current queue length with maxEastQueueLength
    if (eastQueue.getNumElems() > maxEastQueueLength)
    {
      maxEastQueueLength = eastQueue.getNumElems();
    } 
  } 
  else if (eventType == EVENT_ARRIVE_WEST)
  { 
    CarClass inWestCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(inWestCar);
    cout << "Time: " << currentTime << " Car #" << inWestCar.getId()
         << " arrives west-bound - queue length: " << westQueue.getNumElems()
         << endl;
   
    scheduleArrival(WEST_DIRECTION);
    if (westQueue.getNumElems() > maxWestQueueLength)
    {
      maxWestQueueLength = westQueue.getNumElems();
    }
  }
  else if (eventType == EVENT_ARRIVE_NORTH)
  {
    CarClass inNorthCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(inNorthCar);
    cout << "Time: " << currentTime << " Car #" << inNorthCar.getId()
         << " arrives north-bound - queue length: " << northQueue.getNumElems()
         << endl; 

    scheduleArrival(NORTH_DIRECTION);
    if (northQueue.getNumElems() > maxNorthQueueLength)
    {
      maxNorthQueueLength = northQueue.getNumElems();
    }
  }
  else if (eventType == EVENT_ARRIVE_SOUTH)
  {
    CarClass inSouthCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(inSouthCar);
    cout << "Time: " << currentTime << " Car #" << inSouthCar.getId()
         << " arrives south-bound - queue length: " << southQueue.getNumElems()
         << endl;

    scheduleArrival(SOUTH_DIRECTION);
    if (southQueue.getNumElems() > maxSouthQueueLength)
    {
      maxSouthQueueLength = southQueue.getNumElems();
    }
  }
  else if (eventType == EVENT_CHANGE_GREEN_EW)
  {
    cout << "Advancing cars on north-south yellow" << endl;
    
    int advanceNorth = 0;
    int advanceSouth = 0;
    int advancePercent;

    // handle car advancing in the north-bound through the intersection
    int northQueueLength = northQueue.getNumElems();
    bool doesStop = false;
    if (northQueueLength == 0)
    {
      cout << "  No north-bound cars waiting to advance on yellow" << endl;
    }
    else
    {
      while (northQueue.getNumElems() != 0 && !doesStop 
             && advanceNorth < northSouthYellowTime)
      {
        // determine if the north car advances on yellow
        advancePercent = getUniform(1, 100);
        if (advancePercent > percentCarsAdvanceOnYellow)    // not advance
        {
          cout << "  Next north-bound car will NOT advance on yellow" << endl;
          doesStop = true;
        }
        else                                                // advance
        {
          CarClass northCar;
          northQueue.dequeue(northCar);
          cout << "  Car #" << northCar.getId() << " advances north-bound" 
               << endl;
          advanceNorth += 1;
        }
      }
    }
    
    // handle car advancing in the south-bound through the intersection
    doesStop = false;
    if (southQueue.getNumElems() == 0)
    {
      cout << "  No south-bound cars waiting to advance on yellow" << endl;
    }
    else
    {
      while(southQueue.getNumElems() != 0 && !doesStop
            && advanceSouth < northSouthYellowTime)
      {
        advancePercent = getUniform(1, 100); 
        if (advancePercent > percentCarsAdvanceOnYellow)
        {
          cout << "  Next south-bound car will NOT advance on yellow" << endl;
          doesStop = true;
        }
        else
        {
          CarClass southCar;
          southQueue.dequeue(southCar);
          cout << "  Car #" << southCar.getId() << " advances south-bound" 
               << endl;
          advanceSouth += 1;
        }
      }
    }

    // output summary
    cout << "North-bound cars advanced on yellow: " << advanceNorth 
         << " Remaining queue: " << northQueue.getNumElems() << endl;  
    cout << "South-bound cars advanced on yellow: " << advanceSouth
         << " Remaining queue: " << southQueue.getNumElems() << endl; 

    // schedule the next light change event
    currentLight = LIGHT_GREEN_EW;
    scheduleLightChange();

    // update the total number of cars advanced
    numTotalAdvancedNorth += advanceNorth;
    numTotalAdvancedSouth += advanceSouth;
  }
  else if (eventType == EVENT_CHANGE_YELLOW_EW)
  {
    cout << "Advancing cars on east-west green" << endl;

    int advanceEast = 0;
    int advanceWest = 0;
    
    if (eastQueue.getNumElems() == 0)
    {
      cout << "  No east-bound cars waiting to advance on green" << endl;
    }
    else
    {
      while (eastQueue.getNumElems() != 0 && advanceEast < eastWestGreenTime)
      { 
        CarClass eastCar;
        eastQueue.dequeue(eastCar);
        cout << "  Car #" << eastCar.getId() << " advances east-bound" << endl;
        advanceEast += 1;
      }
    }

    if (westQueue.getNumElems() == 0) 
    {
      cout << "  No west-bound cars waiting to advance on green" << endl;
    }
    else
    {
      while (westQueue.getNumElems() != 0 && advanceWest < eastWestGreenTime)
      {
        CarClass westCar; 
        westQueue.dequeue(westCar);
        cout << "  Car #" << westCar.getId() << " advances west-bound" << endl;
        advanceWest += 1;
      }
    }

    cout << "East-bound cars advanced on green: " << advanceEast
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on green: " << advanceWest
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    
    currentLight = LIGHT_YELLOW_EW;
    scheduleLightChange();

    numTotalAdvancedEast += advanceEast;
    numTotalAdvancedWest += advanceWest;
  }
  else if (eventType == EVENT_CHANGE_GREEN_NS)
  {
    cout << "Advancing cars on east-west yellow" << endl;

    int advanceEast = 0;
    int advanceWest = 0;
    int advancePercent;
 
    bool doesStop = false;
    if (eastQueue.getNumElems() == 0)
    {
      cout << "  No east-bound cars waiting to advance on yellow" << endl;
    }
    else
    {
      while (eastQueue.getNumElems() != 0 && !doesStop
             && advanceEast < eastWestYellowTime)
      {
        advancePercent = getUniform(1, 100);
        if (advancePercent > percentCarsAdvanceOnYellow)
        {
          cout << "  Next east-bound car will NOT advance on yellow" << endl;
          doesStop = true;
        }
        else
        {
          CarClass eastCar;
          eastQueue.dequeue(eastCar);
          cout << "  Car #" << eastCar.getId() << " advances east-bound" 
               << endl;
          advanceEast += 1;
        }
      }
    }
    
    doesStop = false;
    if (westQueue.getNumElems() == 0)
    {
      cout << "  No west-bound cars waiting to advance on yellow" << endl; 
    }
    else
    {
      while (westQueue.getNumElems() != 0 && !doesStop
             && advanceWest < eastWestYellowTime)
      {
        advancePercent = getUniform(1, 100);
        if (advancePercent > percentCarsAdvanceOnYellow)
        {
          cout << "  Next west-bound car will NOT advance on yellow" << endl;
          doesStop = true;
        }
        else
        {
          CarClass westCar;
          westQueue.dequeue(westCar);
          cout << "  Car #" << westCar.getId() << " advances west-bound" 
               << endl;
          advanceWest += 1;
        }
      }
    }
    
    cout << "East-bound cars advanced on yellow: " << advanceEast  
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on yellow: " << advanceWest
         << " Remaining queue: " << westQueue.getNumElems() << endl;

    currentLight = LIGHT_GREEN_NS;
    scheduleLightChange();

    numTotalAdvancedEast += advanceEast;
    numTotalAdvancedWest += advanceWest;
  }
  else if (eventType == EVENT_CHANGE_YELLOW_NS)
  {
    cout << "Advancing cars on north-south green" << endl;

    int advanceNorth = 0;
    int advanceSouth = 0; 

    if (northQueue.getNumElems() == 0) 
    {
      cout << "  Next north-bound car will NOT advance on green" << endl;
    }
    else
    {
      while (northQueue.getNumElems() != 0 
             && advanceNorth < northSouthGreenTime) 
      {
        CarClass northCar;
        northQueue.dequeue(northCar);
        cout << "  Car #" << northCar.getId() << " advances north-bound" 
             << endl;
        advanceNorth += 1;
      }
    }

    if (southQueue.getNumElems() == 0) 
    {
      cout << "  No south-bound cars waiting to advance on green" << endl;
    }
    else
    {
      while (southQueue.getNumElems() != 0
             && advanceSouth < northSouthGreenTime)
      {
        CarClass southCar;
        southQueue.dequeue(southCar);
        cout << "  Car #" << southCar.getId() << " advances south-bound" 
             << endl;
        advanceSouth += 1;
      }
    }

    cout << "North-bound cars advanced on green: " << advanceNorth
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on green: " << advanceSouth
         << " Remaining queue: " << southQueue.getNumElems() << endl;

    currentLight = LIGHT_YELLOW_NS;
    scheduleLightChange(); 

    numTotalAdvancedNorth += advanceNorth;
    numTotalAdvancedSouth += advanceSouth; 
  }

  cout << endl;
  isHandled = true;
  return isHandled;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
