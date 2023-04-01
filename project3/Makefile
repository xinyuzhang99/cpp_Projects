all: proj3.exe

project3.o: project3.cpp constants.h PrintMenu.h RowColumnClass.h ColorClass.h ImageClass.h MessageClass.h
	g++ -std=c++98 -Wall -c -g project3.cpp -o project3.o

PrintMenu.o: PrintMenu.cpp PrintMenu.h constants.h
	g++ -std=c++98 -Wall -c -g PrintMenu.cpp -o PrintMenu.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -std=c++98 -Wall -c -g RowColumnClass.cpp -o RowColumnClass.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -std=c++98 -Wall -c -g ColorClass.cpp -o ColorClass.o

ImageClass.o: ImageClass.cpp ImageClass.h ColorClass.h RowColumnClass.h MessageClass.h constants.h
	g++ -std=c++98 -Wall -c -g ImageClass.cpp -o ImageClass.o

MessageClass.o: MessageClass.cpp RowColumnClass.h MessageClass.h constants.h
	g++ -std=c++98 -Wall -c -g MessageClass.cpp -o MessageClass.o

proj3.exe: PrintMenu.o RowColumnClass.o ColorClass.o ImageClass.o MessageClass.o project3.o
	g++ -std=c++98 -g PrintMenu.o RowColumnClass.o ColorClass.o ImageClass.o MessageClass.o project3.o -o proj3.exe

clean:
	rm -f *.o *.exe
