CC = g++
RMV = del

clean : 
	$(RMV) bin\* 

run_unit_tests : unit_tests
	.\bin\unit.exe

run_funcional_tests: funcional_tests 
	.\bin\funcional.exe

run_handle_tests : handle_tests
	.\bin\handleTest.exe

handle_tests : bin\model.o bin\flow.o bin\system.o
	$(CC) test\main.cpp bin\system.o bin\model.o bin\flow.o -o bin\handleTest.exe

funcional_tests : bin\model.o bin\system.o bin\flow.o bin\myVensim.dll
	$(CC) test\funcional\main.cpp test\funcional\funcional_tests.cpp  -o bin\funcional.exe -L./bin/ -lmyVensim -Wall

unit_tests : bin\model.o bin\system.o bin\flow.o bin\myVensim.dll
	$(CC) test\unit\main.cpp test\unit\unit_flow.cpp test\unit\unit_system.cpp test\unit\unit_model.cpp -o bin\unit.exe -L./bin/ -lmyVensim -Wall


bin\myVensim.dll : bin\model.o bin\system.o bin\flow.o
	$(CC) -shared bin\model.o bin\system.o bin\flow.o -o bin\myVensim.dll -Wall -fPIC

bin\model.o: src\ModelImpl.h src\ModelImpl.cpp
	$(CC) src\ModelImpl.cpp -c -o bin\model.o -Wall -fPIC

bin\flow.o: src\FlowImpl.h src\FlowImpl.cpp
	$(CC) src\FlowImpl.cpp -c -o bin\flow.o -Wall -fPIC

bin\system.o: src\SystemImpl.h src\SystemImpl.cpp
	$(CC) src\SystemImpl.cpp  -c -o bin\system.o -Wall -fPIC