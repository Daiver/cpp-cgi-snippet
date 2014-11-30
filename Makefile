.PHONY: all framework clean .FORCE coffeescripts

INCLUDE_PATH = mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include
SHARED_LINK_PATH = mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/lib/libmysqlclient.so.18.3.0 

#CPP = clang++
CPP = g++

bin/blog: framework bin/tests
	$(CPP) -o bin/blog blog.cpp build/*.o -I$(INCLUDE_PATH) $(SHARED_LINK_PATH) && ./bin/blog migrate

bin/main: framework bin/tests
	$(CPP) -o bin/main main.cpp build/*.o -I$(INCLUDE_PATH) $(SHARED_LINK_PATH)

bin/tests: framework
	$(CPP) -o bin/tests tests.cpp build/*.o -I$(INCLUDE_PATH) $(SHARED_LINK_PATH) && ./bin/tests

framework: .FORCE build/requesthandler.o build/common.o build/getpost.o build/templateengine.o build/responsehandler.o build/mysqlworker.o build/orm.o build/database.o build/ormfield.o build/modelscheme.o
	echo "<<<<<C++ Nano Web Framework By Dark_Daiver>>>>>"

coffeescripts: # USELESS NOW
	coffee --compile --output js/coffeecompiled js/coffee

build/requesthandler.o: build/getpost.o
	$(CPP) -c -o build/requesthandler.o requesthandler.cpp 

build/templateengine.o:
	$(CPP) -c -o build/templateengine.o templateengine.cpp

build/common.o:
	$(CPP) -c -o build/common.o common.cpp

build/getpost.o:
	$(CPP) -c -o build/getpost.o getpost.cpp

build/responsehandler.o:
	$(CPP) -c -o build/responsehandler.o responsehandler.cpp

build/mysqlworker.o:
	$(CPP) -c -o build/mysqlworker.o mysqlworker.cpp -Imysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include

build/orm.o:
	$(CPP) -c -o build/orm.o orm/orm.cpp

build/ormfield.o:
	$(CPP) -c -o build/ormfield.o orm/ormfield.cpp

build/database.o:
	$(CPP) -c -o build/database.o orm/database.cpp

build/modelscheme.o:
	$(CPP) -c -o build/modelscheme.o orm/modelscheme.cpp

clean:
	-rm bin/main bin/*.o build/*.o 
	-mkdir build/
	-mkdir bin/

.FORCE: 
	make clean
