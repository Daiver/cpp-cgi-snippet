bin/main: bin/requesthandler
	g++ -o bin/main main.cpp

bin/requesthandler:
	g++ -c -o bin/requesthandler requesthandler.cpp
