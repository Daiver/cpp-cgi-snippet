.PHONY: all clean .FORCE

CPP = clang++
#CPP = g++

bin/main: .FORCE bin/requesthandler.o bin/common.o bin/getpost.o bin/templateengine.o bin/responsehandler.o bin/mysqlworker.o bin/orm.o bin/database.o bin/ormfield.o bin/modelscheme.o
	$(CPP) -o bin/main main.cpp bin/*.o \
		mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/lib/libmysqlclient.so.18.3.0 \
		-Imysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include
	$(CPP) -o bin/tests tests.cpp bin/*.o \
		mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/lib/libmysqlclient.so.18.3.0 \
		-Imysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include \
			 && ./bin/tests

bin/requesthandler.o: bin/getpost.o
	$(CPP) -c -o bin/requesthandler.o requesthandler.cpp 

bin/templateengine.o:
	$(CPP) -c -o bin/templateengine.o templateengine.cpp

bin/common.o:
	$(CPP) -c -o bin/common.o common.cpp

bin/getpost.o:
	$(CPP) -c -o bin/getpost.o getpost.cpp

bin/responsehandler.o:
	$(CPP) -c -o bin/responsehandler.o responsehandler.cpp

bin/mysqlworker.o:
	$(CPP) -c -o bin/mysqlworker.o mysqlworker.cpp -Imysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include

bin/orm.o:
	$(CPP) -c -o bin/orm.o orm/orm.cpp

bin/ormfield.o:
	$(CPP) -c -o bin/ormfield.o orm/ormfield.cpp

bin/database.o:
	$(CPP) -c -o bin/database.o orm/database.cpp

bin/modelscheme.o:
	$(CPP) -c -o bin/modelscheme.o orm/modelscheme.cpp

clean:
	-rm bin/main  bin/*.o 
	-mkdir bin/

.FORCE:
	make clean

