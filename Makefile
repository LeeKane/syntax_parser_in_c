lr.o: lr.h lr.cpp
	g++ -c lr.cpp
main: main.cpp lr.o
	g++ -o main main.cpp lr.o
run: main
	./main
clean:
	rm lr.o main
