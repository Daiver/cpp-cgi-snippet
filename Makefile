.PHONY: all clean .FORCE

bin/main: .FORCE bin/main.o
	g++ -g -o bin/main bin/*.o

bin/main.o: bin/requesthandler.o bin/common.o bin/getpost.o bin/templateengine.o
	g++ -c -o bin/main.o main.cpp 

bin/requesthandler.o: bin/getpost.o
	g++ -c -o bin/requesthandler.o requesthandler.cpp 

bin/templateengine.o:
	g++ -c -o bin/templateengine.o templateengine.cpp

bin/common.o:
	g++ -c -o bin/common.o common.cpp

bin/getpost.o:
	g++ -c -o bin/getpost.o getpost.cpp

clean:
	-rm bin/main  bin/*.o 

.FORCE:
	make clean

