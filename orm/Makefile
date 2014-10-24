.PHONY: all clean .FORCE

bin/tests: .FORCE bin/orm.o
	g++ -o bin/tests tests.cpp bin/orm.o

bin/orm.o:
	g++ -c -o bin/orm.o orm.cpp

clean:
	-rm bin/tests  bin/*.o 
	-mkdir bin/

.FORCE:
	make clean


