bin/main: bin/main.o
	g++ -g -o bin/main bin/*.o

bin/main.o: bin/requesthandler.o bin/common.o bin/getpost.o
	g++ -c -o bin/main.o main.cpp 

bin/requesthandler.o: bin/getpost.o
	g++ -c -o bin/requesthandler.o requesthandler.cpp 

bin/common.o:
	g++ -c -o bin/common.o common.cpp

bin/getpost.o:
	g++ -c -o bin/getpost.o getpost.cpp
