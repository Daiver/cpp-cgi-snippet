.PHONY: all clean .FORCE

#CPP = "g++"
CPP = "clang++"

bin/tests: .FORCE bin/orm.o bin/database.o bin/ormfield.o bin/modelscheme.o
	$(CPP) -o bin/tests tests.cpp bin/*.o

bin/orm.o:
	$(CPP) -c -o bin/orm.o orm.cpp

bin/database.o:
	$(CPP) -c -o bin/database.o database.cpp

bin/ormfield.o:
	$(CPP) -c -o bin/ormfield.o ormfield.cpp

bin/modelscheme.o:
	$(CPP) -c -o bin/modelscheme.o modelscheme.cpp

clean:
	-rm bin/tests  bin/*.o 
	-mkdir bin/

.FORCE:
	make clean


