CC = g++
RMV = rm

clean:
	$(RMV) bin/*

run_funcionalTests:
	./bin/funcional.exe

run_unitTests:
	./bin/unit.exe

funcionalTests: bin/funcional_main.o bin/funcional_test.o bin/myVensim.dll
	$(CC) -o bin/funcional.exe bin/funcional_main.o bin/funcional_test.o bin/myVensim.dll -Wall

unitTests: bin/unit_main.o bin/unit_system.o bin/unit_flow.o bin/unit_model.o bin/unit_test.o bin/myVensim.dll
	$(CC) -o bin/unit.exe bin/unit_test.o bin/unit_main.o bin/unit_system.o bin/unit_flow.o bin/unit_model.o bin/myVensim.dll -Wall


bin/myVensim.dll: bin/System.o bin/Flow.o bin/Model.o
	$(CC) -shared -o bin/myVensim.dll bin/System.o bin/Flow.o bin/Model.o -Wall


bin/System.o: src/AbstractSystem.h src/System.h src/System.cpp
	$(CC) -fPIC src/System.cpp -c -o bin/System.o -Wall

bin/Flow.o: src/AbstractFlow.h src/Flow.h src/Flow.cpp src/AbstractSystem.h
	$(CC) -fPIC src/Flow.cpp -c -o bin/Flow.o -Wall

bin/Model.o: src/AbstractModel.h src/Model.h src/Model.cpp src/AbstractSystem.h src/AbstractFlow.h
	$(CC) -fPIC src/Model.cpp -c -o bin/Model.o -Wall


bin/funcional_main.o: test/funcional/main.cpp test/funcional/funcional_test.h
	$(CC) test/funcional/main.cpp -c -o bin/funcional_main.o -Wall

bin/funcional_test.o: test/funcional/funcional_test.cpp test/funcional/funcional_test.h
	$(CC) test/funcional/funcional_test.cpp -c -o bin/funcional_test.o -Wall


bin/unit_main.o: test/unit/main.cpp test/unit/unit_system.h test/unit/unit_flow.h test/unit/unit_model.h test/unit/unit_test.h
	$(CC) test/unit/main.cpp -c -o bin/unit_main.o -Wall

bin/unit_test.o: test/unit/unit_test.h test/unit/unit_test.cpp
	$(CC) test/unit/unit_test.cpp -c -o bin/unit_test.o -Wall

bin/unit_system.o: test/unit/unit_system.cpp test/unit/unit_system.h
	$(CC) test/unit/unit_system.cpp -c -o bin/unit_system.o -Wall

bin/unit_flow.o: test/unit/unit_flow.cpp test/unit/unit_flow.h
	$(CC) test/unit/unit_flow.cpp -c -o bin/unit_flow.o -Wall

bin/unit_model.o: test/unit/unit_model.cpp test/unit/unit_model.h
	$(CC) test/unit/unit_model.cpp -c -o bin/unit_model.o -Wall