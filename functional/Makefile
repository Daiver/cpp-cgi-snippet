.PHONY: all clean .FORCE

#CPP = clang++
CPP = g++

bin/test: .FORCE 
		$(CPP) -o bin/tests tests.cpp && ./bin/tests

clean:
		-rm bin/tests  bin/*.o 

.FORCE:
		make clean
		-mkdir bin
