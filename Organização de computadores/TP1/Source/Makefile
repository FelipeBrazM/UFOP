all: main.o cpu.o generator.o
	@gcc main.o cpu.o generator.o -o exe
	rm -r *.o
main.o: main.c
	@gcc main.c -c -Wall
cpu.o: cpu.c
	@gcc cpu.c -c -Wall
generator.o: generator.c
	@gcc generator.c -c -Wall
run:
	@./exe
