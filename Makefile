.PHONY: all clean .FORCE

#CPP = clang++
CPP = g++

bin/main: .FORCE bin/requesthandler.o bin/common.o bin/getpost.o bin/templateengine.o
	$(CPP) -o bin/main main.cpp bin/*.o
	$(CPP) -o bin/tests tests.cpp bin/*.o && ./bin/tests

bin/requesthandler.o: bin/getpost.o
	$(CPP) -c -o bin/requesthandler.o requesthandler.cpp 

bin/templateengine.o:
	$(CPP) -c -o bin/templateengine.o templateengine.cpp

bin/common.o:
	$(CPP) -c -o bin/common.o common.cpp

bin/getpost.o:
	$(CPP) -c -o bin/getpost.o getpost.cpp

clean:
	-rm bin/main  bin/*.o 

.FORCE:
	make clean

