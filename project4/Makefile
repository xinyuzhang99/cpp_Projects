all: project4.exe

project4.o: project4.cpp LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h LIFOStackClass.h
	g++ -std=c++98 -Wall -c -g project4.cpp -o project4.o

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
	g++ -std=c++98 -Wall -c -g LinkedNodeClass.cpp -o LinkedNodeClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c -g SortedListClass.cpp -o SortedListClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c -g FIFOQueueClass.cpp -o FIFOQueueClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c -g LIFOStackClass.cpp -o LIFOStackClass.o

project4.exe: LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o project4.o
	g++ -std=c++98 -Wall -g LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o project4.o -o project4.exe

clean:
	rm -f *.o *.exe
