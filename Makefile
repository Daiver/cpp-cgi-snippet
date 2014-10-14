bin/main: bin/requesthandler.o
	g++ -o bin/main main.cpp

bin/requesthandler.o:
	g++ -c -o bin/requesthandler.o requesthandler.cpp
