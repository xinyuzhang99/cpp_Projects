all: proj5.exe

project5.o: project5.cpp IntersectionSimulationClass.h 
	g++ -std=c++98 -Wall -c -g project5.cpp -o project5.o

random.o: random.cpp random.h
	g++ -std=c++98 -Wall -c -g random.cpp -o random.o

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -std=c++98 -Wall -c -g CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -std=c++98 -Wall -c -g EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h SortedListClass.h SortedListClass.inl EventClass.h FIFOQueueClass.h FIFOQueueClass.inl CarClass.h
	g++ -std=c++98 -Wall -c -g IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

proj5.exe: random.o CarClass.o EventClass.o IntersectionSimulationClass.o project5.o
	g++ -std=c++98 -Wall -g random.o CarClass.o EventClass.o IntersectionSimulationClass.o project5.o -o proj5.exe 

clean:
	rm -f *.o *.exe
